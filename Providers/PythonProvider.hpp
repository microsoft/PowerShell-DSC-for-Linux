#ifndef INCLUDED_PYTHONPROVIDER_HPP
#define INCLUDED_PYTHONPROVIDER_HPP


#include "debug_tags.hpp"
#include "MI.h"
#include "unique_ptr.hpp"


#include <cstdlib>
#include <errno.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>


namespace scx
{


class PythonProvider
{
public:
    static int const INVALID_SOCKET = -1;
    static unsigned char const MI_NULL_FLAG;

    template<typename T>
    explicit /*ctor*/ PythonProvider (T const& name);

    virtual /*dtor*/ ~PythonProvider ();

    int init ();

    template<typename T>
    MI_Result test (
        T const* const pResource,
        MI_Boolean* const pTestResultOut);

    template<typename T>
    MI_Result set (
        T const* const pResource,
        MI_Result* const pSetResultOut);

    template<typename T>
    MI_Result get (
        T const* const pResource,
        MI_Instance* const pInstanceOut);

private:
    /*ctor*/ PythonProvider (PythonProvider const&); // = delete
    PythonProvider& operator = (PythonProvider const&); // = delete

    int forkExec ();

    void handleSocketClosed ();

    template<typename T>
    int sendRequest (
        unsigned char const opType,
        T const* const pResource);

    template<typename T>
    int send (T const& val);
    int send (char const* const str);
    int send (std::string const& str);
    template<typename T>
    int send (
        MI_PropertyDecl const& property,
        T const* const pResource);

    template<typename T>
    int recv (T* const pValOut);
    int recv (std::string* const pStrOut);
    
    int recvResult (
        MI_Boolean* const pResultOut);

    int recv_MI_Value (
        MI_Instance* const pInstanceOut);

    template<unsigned int>
    int recv (
        std::string const& name,
        MI_Instance* const pInstanceOut);


    template<typename T>
    class TypeHelper
    {
    public:
        template<typename TT>
        static int
        exists (
            MI_PropertyDecl const& property,
            TT const* const pResource)
        {
            return (reinterpret_cast<T const*>(
                        reinterpret_cast<char const*>(
                            pResource) + property.offset))->exists;
        }

        template<typename TT>
        static int
        send (
            PythonProvider* const pProvider,
            MI_PropertyDecl const& property,
            TT const* const pResource)
        {
            //SCX_BOOKEND ("TypeHelper::send");
            return pProvider->send ((
                reinterpret_cast<T const*>(
                    reinterpret_cast<char const*>(
                        pResource) + property.offset))->value);
        }

        template<typename resource_t, typename cast_t>
        static int
        send (
            PythonProvider* const pProvider,
            MI_PropertyDecl const& property,
            resource_t const* const pResource)
        {
            //SCX_BOOKEND ("TypeHelper::send");
            return pProvider->send (
                static_cast<cast_t>(
                    (reinterpret_cast<T const*>(
                        reinterpret_cast<char const*>(
                            pResource) + property.offset))->value));
        }
    };


    template<typename T>
    static bool exists (
        MI_PropertyDecl const& property,
        T const* const pResource);

    template<typename T>
    static bool isInputParam (
        MI_PropertyDecl const* const pProperty,
        T const* const pResource);

    static unsigned char const TEST = 0;
    static unsigned char const SET = 1;
    static unsigned char const GET = 2;

    std::string const m_Name;
    int m_FD;
};


template<typename char_t, typename traits_t>
std::basic_ostream<char_t, traits_t>& errnoText (
    std::basic_ostream<char_t, traits_t>& strm);


template<typename T>
/*ctor*/
PythonProvider::PythonProvider (
    T const& name)
    : m_Name (name)
    , m_FD (PythonProvider::INVALID_SOCKET)
{
    // empty
}


template<typename T>
MI_Result
PythonProvider::test (
    T const* const pResource,
    MI_Boolean* const pTestResultOut)
{
#if PRINT_BOOKENDS
    std::ostringstream strm;
    strm << " name=\"" << m_Name << '\"';
    SCX_BOOKEND_EX ("PythonProvider::test", strm.str ());
    strm.str ("");
    strm.clear ();
#endif
    MI_Result rval = MI_RESULT_FAILED;
    int result = sendRequest (TEST, pResource);
    if (EXIT_SUCCESS == result)
    {
        SCX_BOOKEND_PRINT ("send succeeded");
        result = recvResult (pTestResultOut);
        if (EXIT_SUCCESS == result)
        {
            SCX_BOOKEND_PRINT ("recv succeeded");
            rval = MI_RESULT_OK;
        }
        else
        {
            SCX_BOOKEND_PRINT ("recv failed");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("send failed");
    }
    return rval;
}


template<typename T>
MI_Result
PythonProvider::set (
    T const* const pResource,
    MI_Result* const pSetResultOut)
{
#if PRINT_BOOKENDS
    std::ostringstream strm;
    strm << " name=\"" << m_Name << '\"';
    SCX_BOOKEND_EX ("PythonProvider::set", strm.str ());
    strm.str ("");
    strm.clear ();
#endif
    MI_Result rval = MI_RESULT_FAILED;
    int result = sendRequest (SET, pResource);
    if (EXIT_SUCCESS == result)
    {
        SCX_BOOKEND_PRINT ("send succeeded");
        MI_Boolean boolResult = MI_FALSE;
        result = recvResult (&boolResult);
        if (EXIT_SUCCESS == result)
        {
            SCX_BOOKEND_PRINT ("recv succeeded");
            rval = MI_RESULT_OK;
            *pSetResultOut = boolResult ? MI_RESULT_OK : MI_RESULT_FAILED;
        }
        else
        {
            SCX_BOOKEND_PRINT ("recv failed");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("send failed");
    }
    return rval;
}


template<typename T>
MI_Result
PythonProvider::get (
    T const* const pResource,
    MI_Instance* const pInstanceOut)
{
    std::ostringstream strm;
#if PRINT_BOOKENDS
    strm << " name=\"" << m_Name << '\"';
    SCX_BOOKEND_EX ("PythonProvider::get", strm.str ());
    strm.str ("");
    strm.clear ();
#endif
#if (0)
    MI_PropertyDecl const* const* ppProperties =
        pInstanceOut->classDecl->properties;
    MI_Uint32 const numProperties =
        pInstanceOut->classDecl->numProperties;
    for (MI_PropertyDecl const* const* pPos = ppProperties,
             * const* const pEndPos = ppProperties + numProperties;
         pPos != pEndPos;
         ++pPos)
    {
        strm << "name: \"" << (*pPos)->name << "\" - type: " << (*pPos)->type
             << " - flags: " << std::hex << std::setfill ('0') << std::setw (10)
             << std::setiosflags (std::ios::internal | std::ios::showbase
                                  | std::ios::uppercase)
             << (*pPos)->flags << std::dec << " - offset: " << (*pPos)->offset;
        if ((*pPos)->value)
        {
            switch ((*pPos)->type)
            {
            case MI_STRING:
                {
                    strm << " - string:";
                    MI_ConstStringField const* strField =
                        reinterpret_cast<MI_ConstStringField const*>(
                            (*pPos)->type);
                    if (strField->exists)
                    {
                        strm << " \"" << strField->value << '\"';
                    }
                    else
                    {
                        strm << " [empty]";
                    }
                }
                break;
            case MI_BOOLEAN:
            case MI_DATETIME:
            default:
                strm << " - unhandled type with value";
                break;
            }
        }
        else
        {
            strm << " - [empty value]";
        }
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
    }
#endif
    // 1: send the request
    // 2: read (int) RESULT
    //     A: RESULT is affirmative (0)
    //         i: read (int) ARG_COUNT
    //         ii: read ARG
    //         iii: read ARG_TYPE
    //         iv: read ARG_VALUE
    //         v: add ARG to new instance
    //         iv: goto ii
    //     B: RESULT is negative (non-0)
    //         i: read (string) error msg
    //         ii: output error msg
    MI_Result rval = MI_RESULT_FAILED;
    int getResult = -1;
    int result = sendRequest (GET, pResource);
    if (EXIT_SUCCESS == result)
    {
        SCX_BOOKEND_PRINT ("send succeeded");
        result = recv (&getResult);
        if (EXIT_SUCCESS == result)
        {
            if (0 == getResult)
            {
                SCX_BOOKEND_PRINT ("recv'd POSITIVE");
                int nItems;
                result = recv (&nItems);
                for (int i = 0; EXIT_SUCCESS == result && i < nItems; ++i)
                {
                    result = recv_MI_Value (pInstanceOut);
                }
                if (EXIT_SUCCESS == result)
                {
                    SCX_BOOKEND_PRINT ("all values were received successfully");
                    rval = MI_RESULT_OK;
                }
                else
                {
                    SCX_BOOKEND_PRINT ("Failed while receiving values");
                    rval = MI_RESULT_FAILED;
                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("recv'd NEGATIVE");
                std::string errorMsg;
                result = recv (&errorMsg);
                if (EXIT_SUCCESS == result)
                {
                    if (0 != errorMsg.length ())
                    {
                        strm << ": error msg: \"" << errorMsg << '\"';
                        SCX_BOOKEND_PRINT (strm.str ());
                        std::cerr << strm.str () << std::endl;
                        strm.str ("");
                        strm.clear ();
                    }
                    else
                    {
                        SCX_BOOKEND_PRINT ("no error msg");
                    }
                }
                else 
                {
                    SCX_BOOKEND_PRINT ("failed to receive error msg");
                }
            }
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("send failed");
    }
    return rval;
}


template<typename T>
int
PythonProvider::sendRequest (
    unsigned char const opType,
    T const* pResource)
{
    int rval = EXIT_SUCCESS;
    std::ostringstream strm;
#if PRINT_BOOKENDS
    strm << " name=\"" << m_Name << '\"';
    SCX_BOOKEND_EX ("PythonProvider::sendRequest<template>", strm.str ());
    strm.str ("");
    strm.clear ();
#endif
    // 1: write the header
    //     a: (unsigned char) OP_TYPE
    //     b: (string) OP_NAME
    //     c: (int) ARG_COUNT
    // 2: write each ARG
    MI_PropertyDecl const* const* ppProperties =
        pResource->__instance.classDecl->properties;
    MI_Uint32 const numProperties =
        pResource->__instance.classDecl->numProperties;
    int result = EXIT_SUCCESS;
    if (EXIT_SUCCESS == result)
    {
        result = send (opType);
    }
    if (EXIT_SUCCESS == result)
    {
        result = send (m_Name);
    }
    if (EXIT_SUCCESS == result)
    {
        int nArgs = std::count_if (
            ppProperties,
            ppProperties + numProperties,
            std::bind2nd (std::ptr_fun (isInputParam<T>), pResource));
        result = send (nArgs);
        strm << "nArgs: " << nArgs;
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
    }
    for (MI_PropertyDecl const* const* pPos = ppProperties,
             * const* const pEndPos = ppProperties + numProperties;
         EXIT_SUCCESS == rval && pPos != pEndPos;
         ++pPos)
    {
        if (isInputParam (*pPos, pResource))
        {
            rval = send ((*pPos)->name);
            if (EXIT_SUCCESS == rval)
            {
                rval = send (**pPos, pResource);
            }
        }
    }
#if (0)
    for (MI_PropertyDecl const* const* pPos = ppProperties,
             * const* const pEndPos = ppProperties + numProperties;
         pPos != pEndPos;
         ++pPos)
    {
        strm << "name: \"" << (*pPos)->name << "\" - type: " << (*pPos)->type
             << " - flags: " << std::hex << std::setfill ('0') << std::setw (10)
             << std::setiosflags (std::ios::internal | std::ios::showbase
                                  | std::ios::uppercase)
             << (*pPos)->flags << std::dec << " - offset: " << (*pPos)->offset;
        SCX_BOOKEND_PRINT (strm.str ());
        strm.str ("");
        strm.clear ();
    }
#endif
    return rval;
}


template<typename T>
int
PythonProvider::send (
    T const& val)
{
    //SCX_BOOKEND ("PythonProvider::send (template)");
    int rval = EXIT_SUCCESS;
    ssize_t nBytesSent = 0;
    ssize_t const nBytes = static_cast<ssize_t>(sizeof (T));
    char const* const pData = reinterpret_cast<char const*>(&val);
    while (EXIT_SUCCESS == rval &&
           -1 != nBytesSent &&
           nBytes > nBytesSent)
    {
        ssize_t nSent = write (m_FD, pData + nBytesSent, nBytes - nBytesSent);
        if (-1 != nSent)
        {
            nBytesSent += nSent;
        }
        else if (EINTR != errno)
        {
            // error (check errno { EACCESS, EAGAIN, EWOULDBLOCK, EBADF,
            //                      ECONNRESET, EDESTADDRREQ, EFAULT, EINVAL,
            //                      EISCONN, EMSGSIZE, ENOBUFS, ENOMEM,
            //                      ENOTCONN, ENOTSOCK, EOPNOTSUPP, EPIPE })
            handleSocketClosed ();
            rval = EXIT_FAILURE;
            std::ostringstream strm;
            strm << "error on socket: (" << errno << ") \"" << errnoText
                 << '\"';
            SCX_BOOKEND_PRINT (strm.str ());
            std::cerr << strm.str () << std::endl;
            strm.str ("");
            strm.clear ();
        }
    }
    return rval;
}


inline int
PythonProvider::send (
    std::string const& str)
{
    return send (str.c_str ());
}


template<typename T>
int
PythonProvider::send (
    MI_PropertyDecl const& property,
    T const* const pResource)
{
    //SCX_BOOKEND ("PythonProvider::send (template)");
    int rval = EXIT_FAILURE;
    if (exists (property, pResource))
    {
        rval = send (static_cast<unsigned char>(property.type));
        if (EXIT_SUCCESS == rval)
        {
            std::ostringstream strm;
            switch (property.type)
            {
            case MI_BOOLEAN:
                rval =
                    TypeHelper<MI_ConstBooleanField>::send<T, unsigned char> (
                        this, property, pResource);
                break;
            case MI_STRING:
                rval = TypeHelper<MI_ConstStringField>::send (
                    this, property, pResource);
                break;
            case MI_DATETIME:
                //rval = TypeHelper<MI_ConstDatetimeField>::send (
                //    this, property, pResource);
                break;
            case MI_UINT8:
            case MI_SINT8:
            case MI_UINT16:
            case MI_SINT16:
            case MI_UINT32:
            case MI_SINT32:
            case MI_UINT64:
            case MI_SINT64:
            case MI_REAL32:
            case MI_REAL64:
            case MI_CHAR16:
            case MI_BOOLEANA:
            case MI_UINT8A:
            case MI_SINT8A:
            case MI_UINT16A:
            case MI_SINT16A:
            case MI_UINT32A:
            case MI_SINT32A:
            case MI_UINT64A:
            case MI_SINT64A:
            case MI_REAL32A:
            case MI_REAL64A:
            case MI_CHAR16A:
            case MI_DATETIMEA:
            case MI_STRINGA:
                strm << __FILE__ << '[' << __LINE__ << ']'
                     << "encountered an unhandled param type: "
                     << property.type;
                SCX_BOOKEND_PRINT (strm.str ());
                std::cerr << strm.str () << std::endl;
                strm.str ("");
                strm.clear ();
                break;
            case MI_REFERENCE:
            case MI_INSTANCE:
            case MI_REFERENCEA:
            case MI_INSTANCEA:
                strm << __FILE__ << '[' << __LINE__ << ']'
                     << "encountered a non-standard param type: "
                     << property.type;
            SCX_BOOKEND_PRINT (strm.str ());
            std::cerr << strm.str () << std::endl;
            strm.str ("");
            strm.clear ();
            break;
            default:
                strm << __FILE__ << '[' << __LINE__ << ']'
                     << "encountered an unknown param type: " << property.type;
                SCX_BOOKEND_PRINT (strm.str ());
                std::cerr << strm.str () << std::endl;
                strm.str ("");
                strm.clear ();
                break;
            }
        }
    }
    else
    {
        rval = send<unsigned char> (property.type | MI_NULL_FLAG);
    }
    return rval;
}


template<typename T>
int
PythonProvider::recv (
    T* const pValOut)
{
    std::ostringstream strm;
    //SCX_BOOKEND ("PythonProvider::recv (template)");
    int rval = EXIT_SUCCESS;
    ssize_t nBytesRead = 0;
    ssize_t const nBytes = static_cast<ssize_t>(sizeof (T));
    T temp = T ();
    char* const pData = reinterpret_cast<char*>(&temp);
    while (EXIT_SUCCESS == rval &&
           nBytes > nBytesRead)
    {
        ssize_t nRead = read (m_FD, pData + nBytesRead, nBytes - nBytesRead);
        if (0 < nRead)
        {
            nBytesRead += nRead;
        }
        else if (0 == nRead)
        {
            // socket closed
            handleSocketClosed ();
            rval = EXIT_FAILURE;
            SCX_BOOKEND_PRINT ("socket closed unexpectedly");
            std::cerr << "socket closed unexpectedly" << std::endl;
        }
        else if (EINTR != errno)
        {
            // Error - check errno { EAGAIN, EBADF, EFAULT, EINVAL, EIO,
            //                       EISDIR }
            handleSocketClosed ();
            rval = EXIT_FAILURE;
            strm << "error on socket: (" << errno << ") \"" << errnoText
                 << '\"';
            SCX_BOOKEND_PRINT (strm.str ());
            std::cerr << strm.str () << std::endl;
            strm.str ("");
            strm.clear ();
        }
    }
    if (EXIT_SUCCESS == rval)
    {
        *pValOut = temp;
    }
    else
    {
        SCX_BOOKEND_PRINT ("unable to read value");
        std::cerr << "unable to read value" << std::endl;
    }
    return rval;
}


template<typename T>
/*static*/ bool
PythonProvider::exists (
    MI_PropertyDecl const& property,
    T const* const pResource)
{
    bool rval = false;
    std::ostringstream strm;
    switch (property.type)
    {
    case MI_BOOLEAN:
        rval = TypeHelper<MI_ConstBooleanField>::exists (
            property, pResource);
        break;
    case MI_STRING:
        rval = TypeHelper<MI_ConstStringField>::exists (
            property, pResource);
        break;
    case MI_DATETIME:
        rval = TypeHelper<MI_ConstDatetimeField>::exists (
            property, pResource);
        break;
    case MI_UINT8:
    case MI_SINT8:
    case MI_UINT16:
    case MI_SINT16:
    case MI_UINT32:
    case MI_SINT32:
    case MI_UINT64:
    case MI_SINT64:
    case MI_REAL32:
    case MI_REAL64:
    case MI_CHAR16:
    case MI_BOOLEANA:
    case MI_UINT8A:
    case MI_SINT8A:
    case MI_UINT16A:
    case MI_SINT16A:
    case MI_UINT32A:
    case MI_SINT32A:
    case MI_UINT64A:
    case MI_SINT64A:
    case MI_REAL32A:
    case MI_REAL64A:
    case MI_CHAR16A:
    case MI_DATETIMEA:
    case MI_STRINGA:
        strm << __FILE__ << '[' << __LINE__ << ':'
             << "encountered an unhandled param type: " << property.type;
        SCX_BOOKEND_PRINT (strm.str ());
        std::cerr << strm.str () << std::endl;
        strm.str ("");
        strm.clear ();
        break;
    case MI_REFERENCE:
    case MI_INSTANCE:
    case MI_REFERENCEA:
    case MI_INSTANCEA:
        strm << __FILE__ << '[' << __LINE__ << ':'
                 << "encountered a non-standard param type: " << property.type;
        SCX_BOOKEND_PRINT (strm.str ());
        std::cerr << strm.str () << std::endl;
        strm.str ("");
        strm.clear ();
        break;
    default:
        strm << __FILE__ << '[' << __LINE__ << ':'
             << "encountered an unknown param type: " << property.type;
        SCX_BOOKEND_PRINT (strm.str ());
        std::cerr << strm.str () << std::endl;
        strm.str ("");
        strm.clear ();
        break;
    }
    return rval;
}


template<typename T>
/*static*/ bool
PythonProvider::isInputParam (
    MI_PropertyDecl const* const pProperty,
    T const* const pResource)
{
    return !(MI_FLAG_READONLY == (MI_FLAG_READONLY & pProperty->flags) &&
             MI_FLAG_KEY != (MI_FLAG_KEY & pProperty->flags));
}


template<typename char_t, typename traits_t>
std::basic_ostream<char_t, traits_t>& errnoText (
    std::basic_ostream<char_t, traits_t>& strm)
{
    static size_t const BUFFER_LEN = 256;
    char errorBuffer[BUFFER_LEN];
    int err = errno;
    char* pErrorText = strerror_r (err, errorBuffer, BUFFER_LEN);
    strm << pErrorText;
    errno = err;
    return strm;
}


} // namespace scx


#endif // INCLUDED_PYTHONPROVIDER_HPP
