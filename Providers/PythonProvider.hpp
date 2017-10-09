/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
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

    MI_Result test (
        MI_Instance const& instance,
        MI_Boolean* const pTestResultOut);

    MI_Result set (
        MI_Instance const& instance,
        MI_Result* const pSetResultOut);

    MI_Result get (
        MI_Instance const& instance,
        MI_Context* const pContext,
        MI_Instance* const pInstanceOut);

    MI_Result inventory (
        MI_Instance const& instance,
        MI_Context* const pContext,
        MI_Instance* const pInstanceOut);

private:
    /*ctor*/ PythonProvider (PythonProvider const&); // = delete
    PythonProvider& operator = (PythonProvider const&); // = delete

    int forkExec ();

    int verifySocketState ();
    void handleSocketClosed ();
    static void handleChildSignal(int sig);

    template<typename T>
    int send (T const& val);
    int send (char const* const str);
    int send (std::string const& str);
    int send (MI_Datetime const& datetime);

    int send (MI_Value const& value,
              MI_Type const type);

    template<typename T>
    int send_array (T const& value);

    int send_str_array (MI_StringA const& strArray);

    int send (MI_Value const& value,
              MI_Type const type,
              MI_Uint32 const flags);

    int send (MI_Instance const& instance);

    int send (MI_Instance* const pInstance);

    int sendRequest (unsigned char const OpType,
                     MI_Instance const& instance);

    template<typename T>
    int recv (T* const pValOut);
    int recv (std::string* const pStrOut);
    int recv (MI_Datetime* const pDatetimeOut);
    
    int recvResult (
        MI_Boolean* const pResultOut);

    int recv_MI_Value (
        MI_Context* const pContext,
        MI_Instance* const pInstanceOut);

    int recv (
        MI_Context* const pContext,
        MI_Instance* const pInstanceOut);


    template<typename T>
    class TypeHelper
    {
    public:
        static int
        recv (
            PythonProvider* const pProvider,
            T* const pValueOut);

        template<typename Array_t>
        static int
        recv_array (
            PythonProvider* const pProvider,
            Array_t* const pValueOut,
            util::unique_ptr<char[]>* const pStorage);
    };

    template<typename T>
    static bool isInputParam (
        MI_PropertyDecl const* const pProperty,
        T const* const pResource);

    static unsigned char const TEST = 0;
    static unsigned char const SET = 1;
    static unsigned char const GET = 2;
    static unsigned char const INVENTORY = 3;
    static MI_Boolean CHILD_SIGNAL_REGISTERED;

    std::string const m_Name;
    int m_FD;
    int m_pid;
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
    , m_pid (-2)
{
    // empty
}


template<typename T>
int
PythonProvider::send (
    T const& val)
{
    //SCX_BOOKEND ("PythonProvider::send (template)");
    int rval = EXIT_SUCCESS;
    ssize_t nBytesSent = 0;
    ssize_t const nBytes = static_cast<ssize_t> (sizeof (T));
    char const* const pData = reinterpret_cast<char const*> (&val);
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
PythonProvider::send_array (
    T const& value)
{
    //SCX_BOOKEND ("PythonProvider::send_array");
    int rval = send<int> (value.size);
    for (MI_Uint32 n = 0;
         EXIT_SUCCESS == rval && n < value.size;
         ++n)
    {
        rval = send (value.data[n]);
    }
    return rval;
}


template<typename T>
int
PythonProvider::recv (
    T* const pValOut)
{
    //SCX_BOOKEND ("PythonProvider::recv (template)");
    int rval = EXIT_SUCCESS;
    ssize_t nBytesRead = 0;
    ssize_t const nBytes = static_cast<ssize_t> (sizeof (T));
    T temp = T ();
    char* const pData = reinterpret_cast<char*> (&temp);
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
            std::ostringstream strm;
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
