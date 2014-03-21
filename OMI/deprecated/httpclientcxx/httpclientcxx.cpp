/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#include "httpclientcxx.h"

#include <common.h>
#include <pal/atomic.h>
#include <pal/sleep.h>
#include <http/httpclient.h>
#include <pal/thread.h>

using namespace std;

// callback for thread (run function)
BEGIN_EXTERNC
static void* MI_CALL _proc(void* );

// callback for user's funcitons executed in background thread
static void threadDelegation(void* self, Message* message);

// http callbacks
static void httpClientCallbackOnStatus(
    ::HttpClient* http,
    void* callbackData,
    MI_Result result);

static MI_Boolean httpClientCallbackOnResponse(
    ::HttpClient* http,
    void* callbackData,
    const HttpClientResponseHeader* headers,
    MI_Sint64 contentSize,
    MI_Boolean  lastChunk,
    Page** data);

END_EXTERNC

HTTPCLIENT_BEGIN


/* helper strucutre used to post messages from calling thread
    to background processing thread
*/
class NotifyItem
{
public:
    // data generic for all calls
    enum Type {
        CONNECT, START_REQUEST, DELETE_HTTP, SET_TIMEOUT
    } _type;
    class HttpClientRep* _rep;
    Message* _msg;

    /* Connect-specific */
    std::string _host;
    unsigned short _port;
    bool _secure;

    /* start-request- specific */
    std::string _verb;
    std::string _uri;
    std::map< std::string, std::string > _extraHeaders;
    std::vector< unsigned char > _data;

    // connect request
    NotifyItem(
        class HttpClientRep* rep,
        const char* host, 
        unsigned short port, 
        bool secure):
        _type(CONNECT),
        _rep(rep),
        _host(host),
        _port(port),
        _secure(secure)
    {
        _InitMsg();
    }

    // start-request
    NotifyItem(
        class HttpClientRep* rep,
        const char* verb,
        const char* uri,
        const std::map< std::string, std::string >& extraHeaders,
        const std::vector< unsigned char >& data):
        _type(START_REQUEST),
        _rep(rep),
        _port(0),
       _secure(false),
        _verb(verb),
        _uri(uri),
        _extraHeaders(extraHeaders),
        _data(data)
    {
        _InitMsg();
    }

    // delete-http item
    NotifyItem(
        class HttpClientRep* rep):
        _type(DELETE_HTTP),
        _rep(rep),
        _port(0),
       _secure(false)
    {
        _InitMsg();
    }

    // set Timeout item
    NotifyItem(
        class HttpClientRep* rep,
        int /*timeout*/):
        _type(SET_TIMEOUT),
        _rep(rep),
        _port(0),
       _secure(false)
    {
        _InitMsg();
    }


    ~NotifyItem()
    {
        Message_Release(_msg);
    }

private:
    NotifyItem(const NotifyItem&);
    void operator=(const NotifyItem&);

    void _InitMsg()
    {
        _msg =  __Message_New(
            NoOpReqTag, sizeof(NoOpReq), 0, 0);

        _msg->clientID = PtrToUint64(this);
    }
};

/* Helper class - background thread operations */
class IOThread
{
public:
    IOThread();
    ~IOThread();

    bool Start();

    /* delegate work to background thread */
    bool PostItem(NotifyItem*item);

//private:
    // not supported
    IOThread(const IOThread&);
    void operator = (const IOThread&);

    // impl

    // mirror funcitons for public API.
    // note: these functions are always called form context of background thread

    void ConnectTh(NotifyItem* item);
    void StartRequestTh(NotifyItem* item);
    void DeleteHttpTh(NotifyItem* item);
    void SetTimeoutTh(NotifyItem* item);

    // data
    ThreadHandle    _th;
    Selector        _selector;
};

/* thread handle - used to store ref-counted pointer to IOThread */
class IOThreadHandle
{
    struct Item {
        AtomicInt   ref;
        IOThread    t;

        Item() :ref(0){}
    };

    Item* _p;

    void _AddRef()
    {
        if (_p) 
            AtomicInc(&_p->ref);
    }

    void _Release()
    {
        if (_p && Atomic_Dec(&_p->ref) == 0)
        {
            delete _p;
        }
    }
public:

    // full set of ctors/dtors/assign operators
    ~IOThreadHandle() {_Release();}
    IOThreadHandle() : _p(0) {}
    IOThreadHandle(const IOThreadHandle& x) : _p(x._p) {_AddRef();}
    IOThreadHandle& operator =(const IOThreadHandle& x)
    {
        if (_p != x._p) 
        {
            _Release();
            _p = x._p;
            _AddRef();
        }
        return *this;
    }

    // accessor
    IOThread* operator ->() 
    {
        return &_p->t;
    }

    // allocator
    void Alloc()
    {
        _Release();
        _p = new Item;
        _AddRef();
    }
};




// forward declaration
static IOThreadHandle _GetThreadObj();

/* impl class   */
class HttpClientRep
{
public:
    HttpClientRep(HttpClientCallback* callback) : 
      _callback(callback),
      _timeoutMS(90 * 1000),
      _httpClient(0),
      _notify(false),
      _destroyed(false)
    {
        _th = _GetThreadObj();
    }

    ~HttpClientRep()
    {
        if (_httpClient)
            HttpClient_Delete(_httpClient);
    }

    // data
    HttpClientCallback* _callback;
    IOThreadHandle      _th;
    int _timeoutMS;
    ::HttpClient* _httpClient;
    bool    _notify;
    bool    _destroyed;
};


/* ****************************************************** */

IOThread::IOThread() :
    _th(0)
{
}

IOThread::~IOThread()
{
    // notify about stopping!
    Selector_StopRunning(&_selector);

    if (_th)
        Thread_Destroy(_th, MI_TRUE);

    // clean up 
    Selector_RemoveAllHandlers(&_selector);
    Selector_Destroy(&_selector);
}

bool IOThread::Start()
{
    if (MI_RESULT_OK != Selector_Init(&_selector))
        return false;

    Selector_SetAllowEmptyFlag(&_selector, MI_TRUE);

    if (MI_RESULT_OK != Thread_Create(_proc, this, &_th))
        return false;

    return true;
}


bool IOThread::PostItem(NotifyItem*item)
{
    MI_Result res = Selector_CallInIOThread(&_selector, threadDelegation, this, item->_msg);

    return res == MI_RESULT_OK;
}

void IOThread::ConnectTh(NotifyItem* item)
{
    MI_Result res = HttpClient_New_Connector(
        &item->_rep->_httpClient,
        &_selector,
        item->_host.c_str(),
        item->_port,
        item->_secure,
        httpClientCallbackOnStatus,
        httpClientCallbackOnResponse,
        item->_rep);

    if (MI_RESULT_OK != res)
    {
        item->_rep->_callback->OnStatus(httpclient::FAILED);
    }

    HttpClient_SetTimeout(item->_rep->_httpClient, ((MI_Uint64)item->_rep->_timeoutMS) * 1000);
}

void IOThread::StartRequestTh(NotifyItem* item)
{
    Page* c_data = 0;
    const char* c_verb = item->_verb.c_str();
    HttpClientRequestHeaders c_headers;
    std::vector< std::string > headers_strings;
    std::vector< const char* > headers_pointers;


    memset(&c_headers, 0, sizeof(c_headers));

    if (!item->_data.empty() > 0)
    {
        c_data = (Page*)PAL_Malloc(item->_data.size() + sizeof(Page));

        /* clear header */
        memset(c_data, 0, sizeof(Page));

        c_data->u.s.size = (unsigned int)item->_data.size();

        memcpy(c_data+1, &item->_data[0], item->_data.size());
    }

    if (!item->_extraHeaders.empty())
    {
        // create array of strings
        for (std::map< std::string, std::string >::const_iterator it = item->_extraHeaders.begin(); it != item->_extraHeaders.end(); it++)
        {
            std::string s = it->first;
            s += ": ";
            s += it->second;
            headers_strings.push_back(s);
        }

        // create array of pointers
        for (size_t i = 0; i < headers_strings.size(); i++)
        {
            headers_pointers.push_back(headers_strings[i].c_str());
        }

        // initialize c-struct:
        c_headers.size = headers_pointers.size();
        c_headers.data = &headers_pointers[0];
    }

    MI_Result res = HttpClient_StartRequest(
        item->_rep->_httpClient,
        c_verb,
        item->_uri.c_str(),
        &c_headers,
        &c_data);

    if (c_data)
        PAL_Free(c_data);

    if (MI_RESULT_OK != res)
    {
        item->_rep->_callback->OnStatus(httpclient::FAILED);
    }
}

void IOThread::DeleteHttpTh(NotifyItem* item)
{
    HttpClient_Delete(item->_rep->_httpClient);
    item->_rep->_httpClient = 0;

    item->_rep->_destroyed = true;
}

void IOThread::SetTimeoutTh(NotifyItem* item)
{
    HttpClient_SetTimeout(item->_rep->_httpClient, ((MI_Uint64)item->_rep->_timeoutMS) * 1000);
}

static IOThreadHandle _GetThreadObj()
{
    static IOThreadHandle s_obj;
    static int s_init = 0;
    static pthread_mutex_t s_mutex = PTHREAD_MUTEX_INITIALIZER;

    /* check if we may need to init */
    if (!s_init)
    {
        pthread_mutex_lock(&s_mutex);

        /* check if we really need to init or get here by race-condition */
        if (!s_init)
        {
            s_obj.Alloc();
            s_obj->Start();
            s_init = 1;
        }
    
        pthread_mutex_unlock(&s_mutex);

    }

    return s_obj;
}

/* ******************************************** */


HttpClient::~HttpClient()
{
    NotifyItem* item = new NotifyItem(_rep);

    if (_rep->_th->PostItem(item))
    {
        /* wait for thread to complete operation */
        while (!_rep->_destroyed)
            Time_Sleep(50);
    }

    delete _rep;
}

HttpClient::HttpClient(HttpClientCallback* callback)
{
    _rep = new HttpClientRep(callback);
}

Result HttpClient::Connect( 
    const char* host, 
    unsigned short port, 
    bool secure)
{
    NotifyItem* item = new NotifyItem(_rep, host, port, secure);

    if (!_rep->_th->PostItem(item))
    {
        delete item;
        return httpclient::FAILED;
    }

    return httpclient::OKAY;
}

Result HttpClient::StartRequest(
    const char* verb,
    const char* uri,
    const std::map< std::string, std::string >& extraHeaders,
    const std::vector< unsigned char >& data,
    bool blockUntilCompleted)
{
    NotifyItem* item = new NotifyItem(_rep, verb, uri, extraHeaders, data);

    if (!_rep->_th->PostItem(item))
    {
        delete item;
        return httpclient::FAILED;
    }

    /* wait for thread to complete operation */
    while (blockUntilCompleted && !_rep->_notify)
        Time_Sleep(50);

    if (blockUntilCompleted)
        _rep->_notify = false;

    return OKAY;
}

void HttpClient::SetOperationTimeout(
    int timeoutMS)
{
    _rep->_timeoutMS = timeoutMS;

    NotifyItem* item = new NotifyItem(_rep, timeoutMS);

    if (!_rep->_th->PostItem(item))
    {
        delete item;
    }
}

HTTPCLIENT_END



static void* _proc(void* self)
{
    httpclient::IOThread* pThis = (httpclient::IOThread*)self;
    // keep runnning until terminated
    Selector_Run(&pThis->_selector, TIME_NEVER);

    return 0;
}

static void threadDelegation(void* self, Message* message)
{
    httpclient::IOThread* pThis = (httpclient::IOThread*)self;
    httpclient::NotifyItem* item =(httpclient::NotifyItem*)Uint64ToPtr(message->clientID);

    switch (item->_type)
    {
    case httpclient::NotifyItem::CONNECT:
        pThis->ConnectTh(item);
        break;

    case httpclient::NotifyItem::START_REQUEST:
        pThis->StartRequestTh(item);
        break;

    case httpclient::NotifyItem::DELETE_HTTP:
        pThis->DeleteHttpTh(item);
        break;

    case httpclient::NotifyItem::SET_TIMEOUT:
        pThis->SetTimeoutTh(item);
        break;

    default:
        assert(!"unexpected item type");
        break;
    }

    delete item;
}

static void httpClientCallbackOnStatus(
    ::HttpClient* http,
    void* callbackData,
    MI_Result result)
{
    httpclient::HttpClientRep* rep = (httpclient::HttpClientRep*)callbackData;
    httpclient::Result user_res= httpclient::FAILED;

    if (MI_RESULT_OK == result)
        user_res= httpclient::OKAY;
    else if (MI_RESULT_TIME_OUT == result)
        user_res= httpclient::TIMEOUT;
    
    rep->_callback->OnStatus(user_res);

    rep->_notify = true;
}

static MI_Boolean httpClientCallbackOnResponse(
    ::HttpClient* http,
    void* callbackData,
    const HttpClientResponseHeader* headers,
    MI_Sint64 contentSize,
    MI_Boolean  lastChunk,
    Page** data)
{
    httpclient::HttpClientRep* rep = (httpclient::HttpClientRep*)callbackData;

    if (headers)
    {
        std::map< std::string, std::string > user_headers;

        for (MI_Uint32 i = 0; i < headers->sizeHeaders; i++)
        {
            user_headers[headers->headers[i].name] = headers->headers[i].value;
        }

        if (!rep->_callback->OnResponseHeader(
            headers->httpError,
            user_headers,
            (int)contentSize))
            return MI_FALSE;
    }

    if (data && *data)
    {
        std::vector< unsigned char > user_data(
            (unsigned char*) ((*data)+1), ((unsigned char*)((*data)+1)) + (*data)->u.s.size
            );

        if (!rep->_callback->OnResponseData(
            user_data,
            lastChunk))
            return MI_FALSE;
    }

    return MI_TRUE;
}


