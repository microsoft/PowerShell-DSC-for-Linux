#include "PythonProvider.hpp"


#include "debug_tags.hpp"


#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>


namespace
{


typedef util::unique_ptr<char[]> char_array;


char const OMI_PYTHON_VERSION_STR[] = "OMI_PYTHON_VERSION";
char const OMI_HOME_STR[] = "OMI_HOME";
char const DSC_SCRIPT_STR[] = "DSC_SCRIPT";
char const DEFAULT_PYTHON_VERSION[] = "python";
char const DEFAULT_OMI_PATH[] = "/opt/omi-1.0.8/";
char const SCRIPT_PATH_EXTENSION[] = "/lib/Scripts/";
char const DEFAULT_DSC_SCRIPT[] = "client";
char const PY_EXTENSION[] = ".py";


char_array::move_type
get_python_version ()
{
    char* sPath = getenv (OMI_PYTHON_VERSION_STR);
    char_array pyV;
    if (sPath == NULL)
    {
        pyV.reset (strcpy (new char[1 + strlen (DEFAULT_PYTHON_VERSION)],
                           DEFAULT_PYTHON_VERSION));
    }
    else
    {
        pyV.reset (strcpy (new char[1 + strlen (sPath)], sPath));
    }
    return pyV.move ();
}


char_array::move_type
get_script_path ()
{
    char const* pathName = getenv (OMI_HOME_STR);
    if (NULL == pathName)
    {
        pathName = DEFAULT_OMI_PATH;
    }
    size_t len = strlen (pathName) + 1;
    char_array fullPath (strcpy (new char[len], pathName));
    char const* fileName = getenv (DSC_SCRIPT_STR);
    if (NULL == fileName)
    {
        fileName = DEFAULT_DSC_SCRIPT;
    }
    len += strlen (SCRIPT_PATH_EXTENSION);
    len += strlen (fileName);
    len += strlen (PY_EXTENSION);
    fullPath.reset (strcpy (new char[len], fullPath.get ()));
    strcat (fullPath.get (), SCRIPT_PATH_EXTENSION);
    strcat (fullPath.get (), fileName);
    strcat (fullPath.get (), PY_EXTENSION);
    return fullPath.move ();
}


}


namespace scx
{


/*static*/ unsigned char const PythonProvider::MI_NULL_FLAG = 64;


/*dtor*/
PythonProvider::~PythonProvider ()
{
#if PRINT_BOOKENDS
    std::ostringstream strm;
    strm << " name=\"" << m_Name << '\"';
    SCX_BOOKEND_EX ("PythonProvider::dtor", strm.str ());
    strm.str ("");
    strm.clear ();
#endif
    if (INVALID_SOCKET != m_FD)
    {
        close (m_FD);
    }
}


int
PythonProvider::init ()
{
    int rval = EXIT_SUCCESS;
#if PRINT_BOOKENDS
    std::ostringstream strm;
    strm << " name=\"" << m_Name << '\"';
    SCX_BOOKEND_EX ("PythonProvider::init", strm.str ());
    strm.str ("");
    strm.clear ();
#endif
    if (INVALID_SOCKET == m_FD)
    {
        rval = forkExec ();
    }
    return rval;
}


int
PythonProvider::forkExec ()
{
    int rval = EXIT_SUCCESS;
    std::ostringstream strm;
#if PRINT_BOOKENDS
    strm << " name=\"" << m_Name << '\"';
    SCX_BOOKEND_EX ("PythonProvider::forkExec", strm.str ());
    strm.str ("");
    strm.clear ();
#endif
    if (INVALID_SOCKET == m_FD)
    {
        int sockets[2];
        int result = socketpair (AF_UNIX, SOCK_STREAM, 0, sockets);
        if (-1 != result)
        {
            // socketpair succeeded
            SCX_BOOKEND_PRINT ("socketpair - succeeded");
            int pid = fork ();
            if (0 == pid)
            {
                // fork succeded, this is the child process
                SCX_BOOKEND_PRINT ("fork - succeeded: this is the child");
                // close the parent socket
                close (sockets[1]);
                // create the argument list including the child socket name as a
                // command line arg
                size_t const SOCK_ID_BUF_LEN = 32;
                char socketID[SOCK_ID_BUF_LEN];
                snprintf (socketID, SOCK_ID_BUF_LEN, "%d", sockets[0]);
                char_array pyV (get_python_version ());
                char_array fullName (get_script_path ());
                char* args[] = { pyV.get (), fullName.get (), socketID, 0 };
                // exec
                execvp (args[0], args);
                SCX_BOOKEND_PRINT ("execvp - failed");
                // if we got here, exec failed!
                // check errno { EACCES, ENOEXEC }
                strm << "PythonProvider::forkExec - exec failed: " << errno
                     << ": \"" << errnoText << '\"';
                SCX_BOOKEND_PRINT (strm.str ());
                std::cerr << strm.str () << std::endl;
                strm.str ("");
                strm.clear ();
                rval = EXIT_FAILURE;
            }
            else if (-1 != pid)
            {
                // fork succeeded, this is the parent process
                SCX_BOOKEND_PRINT ("fork - succeeded: this is the parent");
                close (sockets[0]);
                m_FD = sockets[1];
                rval = EXIT_SUCCESS;
            }
            else
            {
                // fork failed
                // error (check errno { EAGAIN, ENOMEM })
                strm << "PythonProvider::forkExec - fork failed: " << errno
                     << ": \"" << errnoText << '\"';
                SCX_BOOKEND_PRINT (strm.str ());
                std::cerr << strm.str () << std::endl;
                strm.str ("");
                strm.clear ();
                rval = EXIT_FAILURE;
            }
        }
        else
        {
            // socketpair failed
            // error (check errno { EAFNOSUPPORT, EMFILE, EOPNOTSUPP,
            //    EPROTONOSUPPORT, EPROTOTYPE, EACCES, ENOBUFS, ENOMEM })
            strm << "PythonProvider::forkExec - socketpair_failed: " << errno
                 << ": \"" << errnoText << '\"';
            SCX_BOOKEND_PRINT (strm.str ());
            std::cerr << strm.str () << std::endl;
            strm.str ("");
            strm.clear ();
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("already initialized");
    }
    return rval;
}


void
PythonProvider::handleSocketClosed ()
{
    close (m_FD);
    m_FD = INVALID_SOCKET;
}


int
PythonProvider::send (
    char const* const str)
{
    //SCX_BOOKEND ("PythonProvider::send (str)");
    ssize_t const nStrLen = (0 == str) ? 0 : strlen (str);
    int rval = send (static_cast<int>(nStrLen));
    ssize_t nCharsSent = 0;
    while (EXIT_SUCCESS == rval &&
           nStrLen > nCharsSent)
    {
        ssize_t nSent = write (m_FD, str + nCharsSent, nStrLen - nCharsSent);
        if (-1 != nSent)
        {
            nCharsSent += nSent;
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
        }
    }
    return rval;
}


int
PythonProvider::send (
    MI_Datetime const& datetime)
{
    SCX_BOOKEND ("PythonProvider::send (MI_Datetime)");
    int rval = send (static_cast<unsigned char>(datetime.isTimestamp));
    if (EXIT_SUCCESS == rval)
    {
        if (datetime.isTimestamp)
        {
            if (EXIT_SUCCESS != send (datetime.u.timestamp.year) ||
                EXIT_SUCCESS != send (datetime.u.timestamp.month) ||
                EXIT_SUCCESS != send (datetime.u.timestamp.day) ||
                EXIT_SUCCESS != send (datetime.u.timestamp.hour) ||
                EXIT_SUCCESS != send (datetime.u.timestamp.minute) ||
                EXIT_SUCCESS != send (datetime.u.timestamp.second) ||
                EXIT_SUCCESS != send (datetime.u.timestamp.microseconds) ||
                EXIT_SUCCESS != send (datetime.u.timestamp.utc))
            {
                rval = EXIT_FAILURE;
            }
        }
        else
        {
            if (EXIT_SUCCESS != send (datetime.u.interval.days) ||
                EXIT_SUCCESS != send (datetime.u.interval.hours) ||
                EXIT_SUCCESS != send (datetime.u.interval.minutes) ||
                EXIT_SUCCESS != send (datetime.u.interval.seconds) ||
                EXIT_SUCCESS != send (datetime.u.interval.microseconds))
            {
                rval = EXIT_FAILURE;
            }
        }
    }
    return rval;
}


int
PythonProvider::recv (
    std::string* const pStrOut)
{
    //SCX_BOOKEND ("PythonProvider::recv (string)");
    int nStrLen = 0;
    int rval = recv (&nStrLen);
    if (EXIT_SUCCESS == rval)
    {
        if (0 != nStrLen)
        {
            ssize_t nCharsRead = 0;
            util::unique_ptr<char[]> pBuffer (new char[nStrLen]);
            while (EXIT_SUCCESS == rval &&
                   nStrLen > nCharsRead)
            {
                ssize_t nRead = read (m_FD, pBuffer.get () + nCharsRead,
                                      nStrLen - nCharsRead);
                if (0 < nRead)
                {
                    nCharsRead += nRead;
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
                pStrOut->assign (pBuffer.get (), nStrLen);
            }
            else
            {
                SCX_BOOKEND_PRINT ("unable to read string text");
                std::cerr << "unable to read string text" << std::endl;
            }
        }
        else
        {
            pStrOut->erase ();
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("unable to read string size");
        std::cerr << "unable to read string size" << std::endl;
    }
    return rval;
}


int
PythonProvider::recv (
    MI_Datetime* const pDatetimeOut)
{
    //SCX_BOOKEND ("PythonProvider::recv (MI_Datetime)");
    MI_Datetime tempVal;
    unsigned char isTimestamp;
    int rval = recv (&isTimestamp);
    if (EXIT_SUCCESS == rval)
    {
        if (isTimestamp)
        {
            tempVal.isTimestamp = MI_TRUE;
            if (EXIT_SUCCESS != recv (&(tempVal.u.timestamp.year)) ||
                EXIT_SUCCESS != recv (&(tempVal.u.timestamp.month)) ||
                EXIT_SUCCESS != recv (&(tempVal.u.timestamp.day)) ||
                EXIT_SUCCESS != recv (&(tempVal.u.timestamp.hour)) ||
                EXIT_SUCCESS != recv (&(tempVal.u.timestamp.minute)) ||
                EXIT_SUCCESS != recv (&(tempVal.u.timestamp.second)) ||
                EXIT_SUCCESS != recv (&(tempVal.u.timestamp.microseconds)) ||
                EXIT_SUCCESS != recv (&(tempVal.u.timestamp.utc)))
            {
                rval = EXIT_FAILURE;
            }
        }
        else
        {
            tempVal.isTimestamp = MI_FALSE;
            if (EXIT_SUCCESS != recv (&(tempVal.u.interval.days)) ||
                EXIT_SUCCESS != recv (&(tempVal.u.interval.hours)) ||
                EXIT_SUCCESS != recv (&(tempVal.u.interval.minutes)) ||
                EXIT_SUCCESS != recv (&(tempVal.u.interval.seconds)) ||
                EXIT_SUCCESS != recv (&(tempVal.u.interval.microseconds)))
            {
                rval = EXIT_FAILURE;
            }
        }
    }
    if (EXIT_SUCCESS == rval)
    {
        *pDatetimeOut = tempVal;
    }
    return rval;
}


int
PythonProvider::recvResult (
    MI_Boolean* const pResultOut)
{
    std::ostringstream strm;
    *pResultOut = MI_FALSE;
#if PRINT_BOOKENDS
    strm << " name=\"" << m_Name << '\"';
    SCX_BOOKEND_EX ("PythonProvider::recvResult", strm.str ());
    strm.str ("");
    strm.clear ();
#endif
    int result = -1;
    int rval = recv (&result);
    if (EXIT_SUCCESS == rval)
    {
        if (0 == result)
        {
            SCX_BOOKEND_PRINT ("recv'd POSITIVE");
            *pResultOut = MI_TRUE;
        }
        else
        {
            SCX_BOOKEND_PRINT ("recv'd NEGATIVE");
            std::string errorMsg;
            rval = recv (&errorMsg);
            if (EXIT_SUCCESS == rval)
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
    else
    {
        SCX_BOOKEND_PRINT ("failed to receive result");
    }
    return rval;
}


int
PythonProvider::recv_MI_Value (
    MI_Instance* const pInstanceOut)
{
    //SCX_BOOKEND ("PythonProvider::recv_MI_Value");
    std::string name;
    int rval = recv (&name);
    if (EXIT_SUCCESS == rval)
    {
        unsigned char type;
        rval = recv (&type);
        if (EXIT_SUCCESS == rval)
        {
            if (0 == (MI_NULL_FLAG & type))
            {
                std::ostringstream strm;
                std::string tempStr;
                util::unique_ptr<char[]> pArray;
                util::unique_ptr<std::string[]> pStrArray;
                MI_Value val;
                switch (type)
                {
                case MI_BOOLEAN:
                    {
                        //SCX_BOOKEND ("recv (BOOLEAN)");
                        unsigned char temp;
                        rval = recv (&temp);
                        if (EXIT_SUCCESS == rval)
                        {
                            val.boolean = temp ? MI_TRUE : MI_FALSE;
                        }
                    }
                    break;
                case MI_UINT8:
                    rval = TypeHelper<MI_Uint8>::recv (this, &(val.uint8));
                    break;
                case MI_SINT8:
                    rval = TypeHelper<MI_Sint8>::recv (this, &(val.sint8));
                    break;
                case MI_UINT16:
                    rval = TypeHelper<MI_Uint16>::recv (this, &(val.uint16));
                    break;
                case MI_SINT16:
                    rval = TypeHelper<MI_Sint16>::recv (this, &(val.sint16));
                    break;
                case MI_UINT32:
                    rval = TypeHelper<MI_Uint32>::recv (this, &(val.uint32));
                    break;
                case MI_SINT32:
                    rval = TypeHelper<MI_Sint32>::recv (this, &(val.sint32));
                    break;
                case MI_UINT64:
                    rval = TypeHelper<MI_Uint64>::recv (this, &(val.uint64));
                    break;
                case MI_SINT64:
                    rval = TypeHelper<MI_Sint64>::recv (this, &(val.sint64));
                    break;
                case MI_REAL32:
                    rval = TypeHelper<MI_Real32>::recv (this, &(val.real32));
                    break;
                case MI_REAL64:
                    rval = TypeHelper<MI_Real64>::recv (this, &(val.real64));
                    break;
                case MI_CHAR16:
                    rval = TypeHelper<MI_Char16>::recv (this, &(val.char16));
                    break;
                case MI_DATETIME:
                    rval = TypeHelper<MI_Datetime>::recv (this, &(val.datetime));
                    break;
                case MI_STRING:
                    rval = recv (&tempStr);
                    val.string = const_cast<MI_Char*>(tempStr.c_str ());
                    break;
                case MI_BOOLEANA:
                    {
                        SCX_BOOKEND ("recv (BOOLEANA)");
                        int length;
                        rval = recv (&length);
                        if (EXIT_SUCCESS == rval)
                        {
                            pArray.reset (
                                new char[length * sizeof (MI_Boolean)]);
                            MI_Boolean* const pTemp =
                                reinterpret_cast<MI_Boolean* const> (
                                    pArray.get ());
                            for (int i = 0;
                                 EXIT_SUCCESS == rval && length > i;
                                 ++i)
                            {
                                unsigned char temp;
                                rval = recv (&temp);
                                if (EXIT_SUCCESS == rval)
                                {
                                    pTemp[i] = temp ? MI_TRUE : MI_FALSE;
                                }
                            }
                            if (EXIT_SUCCESS == rval)
                            {
                                val.booleana.data = pTemp;
                                val.booleana.size =
                                    static_cast<MI_Uint32> (length);
                            }
                        }
                    }
                    break;
                case MI_UINT8A:
                    rval = TypeHelper<MI_Uint8>::recv_array (
                        this, &(val.uint8a), &pArray);
                    break;
                case MI_SINT8A:
                    rval = TypeHelper<MI_Sint8>::recv_array (
                        this, &(val.sint8a), &pArray);
                    break;
                case MI_UINT16A:
                    rval = TypeHelper<MI_Uint16>::recv_array (
                            this, &(val.uint16a), &pArray);
                    break;
                case MI_SINT16A:
                    rval = TypeHelper<MI_Sint16>::recv_array (
                            this, &(val.sint16a), &pArray);
                    break;
                case MI_UINT32A:
                    rval = TypeHelper<MI_Uint32>::recv_array (
                            this, &(val.uint32a), &pArray);
                    break;
                case MI_SINT32A:
                    rval = TypeHelper<MI_Sint32>::recv_array (
                            this, &(val.sint32a), &pArray);
                    break;
                case MI_UINT64A:
                    rval = TypeHelper<MI_Uint64>::recv_array (
                            this, &(val.uint64a), &pArray);
                    break;
                case MI_SINT64A:
                    rval = TypeHelper<MI_Sint64>::recv_array (
                            this, &(val.sint64a), &pArray);
                    break;
                case MI_REAL32A:
                    rval = TypeHelper<MI_Real32>::recv_array (
                            this, &(val.real32a), &pArray);
                    break;
                case MI_REAL64A:
                    rval = TypeHelper<MI_Real64>::recv_array (
                            this, &(val.real64a), &pArray);
                    break;
                case MI_CHAR16A:
                    rval = TypeHelper<MI_Char16>::recv_array (
                            this, &(val.char16a), &pArray);
                    break;
                case MI_DATETIMEA:
                    rval = TypeHelper<MI_Datetime>::recv_array (
                            this, &(val.datetimea), &pArray);
                    break;
                case MI_STRINGA:
                    {
                        SCX_BOOKEND ("recv (STRINGA)");
                        int length;
                        int rval = recv (&length);
                        if (EXIT_SUCCESS == rval)
                        {
                            pArray.reset (
                                new char[length * sizeof (MI_Char*)]);
                            MI_Char** const pTemp =
                                reinterpret_cast<MI_Char** const> (
                                    pArray.get ());
                            pStrArray.reset (new std::string[length]);
                            for (int i = 0;
                                 EXIT_SUCCESS == rval && length > i;
                                 ++i)
                            {
                                rval = recv (pStrArray.get () + i);
                                if (EXIT_SUCCESS == rval)
                                {
                                    pTemp[i] = const_cast<MI_Char*>(
                                        pStrArray[i].c_str ());
                                }
                            }
                            if (EXIT_SUCCESS == rval)
                            {
                                val.stringa.data = pTemp;
                                val.stringa.size =
                                    static_cast<MI_Uint32> (length);
                            }
                        }
                    }
                    break;
                case MI_REFERENCE:
                case MI_INSTANCE:
                case MI_REFERENCEA:
                case MI_INSTANCEA:
                    strm << __FILE__ << '[' << __LINE__ << ']'
                         << "encountered a non-standard param type: " << type;
                    SCX_BOOKEND_PRINT (strm.str ());
                    std::cerr << strm.str () << std::endl;
                    strm.str ("");
                    strm.clear ();
                    rval = EXIT_FAILURE;
                    break;
                default:
                    strm << __FILE__ << '[' << __LINE__ << ']'
                         << "encountered an unknown param type: " << type;
                    SCX_BOOKEND_PRINT (strm.str ());
                    std::cerr << strm.str () << std::endl;
                    strm.str ("");
                    strm.clear ();
                    rval = EXIT_FAILURE;
                    break;
                }
                if (EXIT_SUCCESS == rval)
                {
                    if (MI_RESULT_OK == MI_Instance_SetElement (
                            pInstanceOut, name.c_str (), &val,
                            static_cast<MI_Type>(type), 0))
                    {
                        strm << "value added - name: \"" << name
                             << "\" - type: " << static_cast<int>(type);
                        SCX_BOOKEND_PRINT (strm.str ());
                        strm.str ("");
                        strm.clear ();
                    }
                    else
                    {
                        SCX_BOOKEND_PRINT ("failed to add value to instance");
                        rval = EXIT_FAILURE;
                    }
                }
                else
                {
                    SCX_BOOKEND_PRINT ("Failed to read value");
                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("Value is NULL.");
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("Failed to read type");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("Failed to read name");
    }
    return rval;
}


} // namespace scx
