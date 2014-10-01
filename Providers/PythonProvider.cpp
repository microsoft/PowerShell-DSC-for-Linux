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


char const DEFAULT_PYTHON_VERSION[] = "python";
char const DEFAULT_OMI_PATH[] = "/opt/omi-1.0.8/";
char const SCRIPT_PATH_EXTENSION[] = "/lib/Scripts/";
char const PY_EXTENSION[] = ".py";


char_array::move_type
get_python_version ()
{
    char* sPath = getenv ("OMI_PYTHON_VERSION");
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
get_script_path (
    char const* const fileName)
{
    char* sPath = getenv ("OMI_HOME");
    char_array scriptPath;
    size_t len = strlen (SCRIPT_PATH_EXTENSION);
    len += strlen (fileName);
    len += strlen (PY_EXTENSION);
    len += 1; // null terminator
    if (sPath == NULL)
    {
        scriptPath.reset (new char[len + strlen (DEFAULT_OMI_PATH)]);
        strcpy (scriptPath.get (), DEFAULT_OMI_PATH);
    }
    else
    {
        scriptPath.reset (new char[len + strlen (sPath)]);
        strcpy (scriptPath.get (), sPath);
    }
    strcat (scriptPath.get (), SCRIPT_PATH_EXTENSION);
    strcat (scriptPath.get (), fileName);
    strcat (scriptPath.get (), PY_EXTENSION);
    return scriptPath.move ();
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
                char_array fullName (get_script_path ("test_client"));
                char* args[] = { pyV.get (), fullName.get (), socketID, NULL };
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
            strm.str ("");
            strm.clear ();
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
            std::ostringstream strm;
            std::string tempStr;
            MI_Value val;

            switch (type)
            {
            case MI_BOOLEAN:
                {
                    unsigned char temp;
                    rval = recv (&temp);
                    val.boolean = temp ? MI_TRUE : MI_FALSE;
                }
                break;
            case MI_STRING:
                rval = recv (&tempStr);
                val.string = const_cast<MI_Char*>(tempStr.c_str ());
                break;
            case MI_DATETIME:
                // working on this, it is not ready to check in
                //{
                //    time_t temp;
                //    rval = recv (&temp);
                //    tm localTM;
                //    tm gmTM;
                //    if (localtime_r (&temp, &localTM) &&
                //        gmtime_r (&temp, &gmTM))
                //    {
                //        val.datetime.isTimestamp = MI_TRUE;
                //        val.datetime.u.timestamp.year = localTM.tm_year + 1900;
                //        val.datetime.u.timestamp.month = localTM.tm_mon + 1;
                //        val.datetime.u.timestamp.day = localTM.tm_mday;
                //        val.datetime.u.timestamp.hour = localTM.tm_hour;
                //        val.datetime.u.timestamp.minute = localTM.tm_min;
                //        val.datetime.u.timestamp.second = localTM.tm_sec;
                //        time_t gmt = mktime (&gmTM);
                //        val.datetime.u.timestamp.utc =
                //            60 * static_cast<time_t>(difftime (gmt, temp));
                //    }
                //    else
                //    {
                //        rval = EXIT_FAILURE;
                //    }
                //}
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
                     << "encountered an unhandled param type: " << type;
                SCX_BOOKEND_PRINT (strm.str ());
                std::cerr << strm.str () << std::endl;
                strm.str ("");
                strm.clear ();
                rval = EXIT_FAILURE;
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
                    strm << "value added - name: \"" << name << "\" - type: "
                         << static_cast<int>(type);
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
