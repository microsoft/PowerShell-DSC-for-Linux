#include <boost/filesystem.hpp>
#include <boost/python.hpp>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

#include <sstream>
#include <string>

#include "python_io_helpers.hpp"


class python_backtrace_parser
{
public:
    /*ctor*/ python_backtrace_parser (boost::python::object& backTrace)
        : m_BackTrace (backTrace)
    {
        // empty
    }

    template<typename charT,
             typename traits>
    std::basic_ostream<charT, traits>&
    operator () (
        std::basic_ostream<charT, traits>& strm) const
    {
        typedef SCX::PythonTextConstants<charT> Text;
        using boost::python::object;
        using boost::python::extract;

        if (m_BackTrace)
        {
            object lineNo (m_BackTrace.attr ("tb_lineno"));
            object frame (m_BackTrace.attr ("tb_frame"));
            object fCode (frame.attr ("f_code"));
            object filename (fCode.attr ("co_filename"));
            object fnName (fCode.attr ("co_name"));
            strm << extract<char const*> (filename) << Text::COLON <<
                extract<char const*> (fnName) << Text::OPEN_BRACE <<
                extract<long> (lineNo) << Text::CLOSE_BRACE;
            object next (m_BackTrace.attr ("tb_next"));
            if (next)
            {
                strm << std::endl << python_backtrace_parser (next);
            }
        }
        return strm;
    }

private:
    boost::python::object& m_BackTrace;
};


template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
operator << (
    std::basic_ostream<charT, traits>& strm,
    python_backtrace_parser const& backTrace)
{
    return backTrace (strm);
}


template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
_python_error_parser (
    std::basic_ostream<charT, traits>& strm)
{
    typedef SCX::PythonTextConstants<charT> Text;
    using boost::python::object;
    using boost::python::extract;
    
    PyObject* pType;
    PyObject* pValue;
    PyObject* pBackTrace;

    PyErr_Fetch (&pType, &pValue, &pBackTrace);

    object type (boost::python::handle<>(boost::python::allow_null (pType)));
    object value (
        boost::python::handle<>(boost::python::allow_null (pValue)));
    object backTrace (
        boost::python::handle<>(boost::python::allow_null (pBackTrace)));

    boost::python::extract<char const*> strVal (pValue);
    if (strVal.check ())
    {
        strm << boost::python::extract<char const*>(pValue) << std::endl;
    }
    else
    {
        strm << L"<pValue>" << std::endl;
        strm << pValue << std::endl;
        strm << L"</pValue>" << std::endl;
        strm << L"pValue failed test for char const* !!" << std::endl;
    }
//    if (backTrace)
//    {
//        strm << python_backtrace_parser (backTrace);
//    }
    return strm;
}






template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
python_error_parser_done (
    std::basic_ostream<charT, traits>& strm)
{
    typedef SCX::PythonTextConstants<charT> Text;
    using boost::python::object;
    using boost::python::extract;
    
    PyObject* pType;
    PyObject* pValue;
    PyObject* pBackTrace;

    PyErr_Fetch (&pType, &pValue, &pBackTrace);

    object type (boost::python::handle<>(boost::python::allow_null (pType)));
    object value (
        boost::python::handle<>(boost::python::allow_null (pValue)));
    object backTrace (
        boost::python::handle<>(boost::python::allow_null (pBackTrace)));


    object traceback (boost::python::import ("traceback"));
    object format_exception (traceback.attr ("format_exception"));
    if (PyCallable_Check (format_exception.ptr ()))
    {
    }

//    boost::python::extract<char const*> strVal (pValue);
//    if (strVal.check ())
//    {
//        strm << boost::python::extract<char const*>(pValue) << std::endl;
//    }
//    else
//    {
//        strm << L"<pValue>" << std::endl;
//        strm << pValue << std::endl;
//        strm << L"</pValue>" << std::endl;
//        strm << L"pValue failed test for char const* !!" << std::endl;
//    }
//    if (backTrace)
//    {
//        strm << python_backtrace_parser (backTrace);
//    }
    return strm;
}





template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
python_error_parser (
    std::basic_ostream<charT, traits>& strm)
{
    typedef SCX::PythonTextConstants<charT> Text;
    using boost::python::handle;
    using boost::python::object;
    using boost::python::import;
    using boost::python::extract;
    
    PyObject* pType;
    PyObject* pValue;
    PyObject* pBT;

    PyErr_Fetch (&pType, &pValue, &pBT);
    PyErr_NormalizeException (&pType, &pValue, &pBT);

    handle<> hType (pType);
    handle<> hValue (boost::python::allow_null (pValue));
    handle<> hBT (boost::python::allow_null (pBT));

    if (hValue)
    {
        object traceback(boost::python::import("traceback"));
        object format_exception(traceback.attr("format_exception"));
        object formatted_list (format_exception(hType, hValue, hBT));
        object formatted (boost::python::str ("").join (formatted_list));

//        if (hBT)
//        {
//            strm << "traceback is non-null" << std::endl;
//        }
//        if (!hBT)
//        {
//            strm << "traceback is null" << std::endl;
//        }
        strm << formatted;
    }
    else
    {
//        std::string text = extract<std::string>(boost::python::str (hType));
        strm << extract<char const*>(boost::python::str (hType));
    }


//    object type (boost::python::handle<>(boost::python::allow_null (pType)));
//    object value (
//        boost::python::handle<>(boost::python::allow_null (pValue)));
//    object backTrace (
//        boost::python::handle<>(boost::python::allow_null (pBackTrace)));
//
//
//    object traceback (boost::python::import ("traceback"));
//    object format_exception (traceback.attr ("format_exception"));
//    if (PyCallable_Check (format_exception.ptr ()))
//    {
//        object formatted_list
//        format_exception (pType, pValue, pBackTrace);
//
//        strm << formatted_list << std::endl;
//    }

//    boost::python::extract<char const*> strVal (pValue);
//    if (strVal.check ())
//    {
//        strm << boost::python::extract<char const*>(pValue) << std::endl;
//    }
//    else
//    {
//        strm << L"<pValue>" << std::endl;
//        strm << pValue << std::endl;
//        strm << L"</pValue>" << std::endl;
//        strm << L"pValue failed test for char const* !!" << std::endl;
//    }
//    if (backTrace)
//    {
//        strm << python_backtrace_parser (backTrace);
//    }
    return strm;
}







class PrintOnExit
{
public:
    /*ctor*/ PrintOnExit (std::wstring text) : m_Text () { m_Text.swap (text); }
    /*dtor*/ ~PrintOnExit () { std::wcout << m_Text << std::endl; }
private:
    std::wstring m_Text;
};


void
tryPythonFile (
    char const* const filename)
{
    std::wcout << L"<PythonFile>" << std::endl;
    PrintOnExit onExit (L"</PythonFile>");
    try
    {
        std::wcout << L"Opening file: \"" << filename << L"\"" << std::endl;
        boost::python::dict globals;
        boost::python::dict locals;
        boost::python::object result =
            boost::python::exec_file (filename, globals, locals);
        std::wcout << L"returned: " << result << std::endl;
        std::wcout << L"globals: " << globals << std::endl;
        std::wcout << L"locals: " << locals << std::endl;
    }
    catch (boost::python::error_already_set ex)
    {
        std::wcout << L"caught boost::python::error_already_set" <<
            std::endl;
        std::wcout << L"<error>" << std::endl;
        std::wcout << python_error_parser;
        std::wcout << L"</error>" << std::endl;

        std::wcout << L"<PyErr_Print>" << std::endl;
        PyErr_Print ();
        std::wcout << L"</PyErr_Print>" << std::endl;
    }
    catch (std::exception ex)
    {
        std::wcout << L"caught std::exception: \"" << ex.what () << L'\"' <<
            std::endl;
        std::wcout << L"PyErr_Print: \"";
        PyErr_Print ();
        std::wcout << L'\"' << std::endl;
    }
//    std::wcout << L"</PythonFile>" << std::endl;
}


int
main (
    int const argc,
    char const* const* argv)
{
//    std::wcout << SCX::PythonUnicodeInfo << std::endl;

    Py_Initialize ();

//    std::wcout << L"Prior PythonPath:" << std::endl;
//    std::wcout << SCX::PythonPath << std::endl;

    boost::filesystem::path workingDir =
        boost::filesystem::absolute ("./").normalize ();


    // look back at Creating boost::python::object from PyObject*

    PyObject* sysPath =
        PySys_GetObject (const_cast<char*>("path"));
    PyList_Insert (sysPath, 0, PyString_FromString (workingDir.string ().c_str ()));

//    std::wcout << L"Post PythonPath:" << std::endl;
//    std::wcout << SCX::PythonPath << std::endl;


    if (3 <= argc)
    {
#if (0)
        PyObject* moduleName = 0;
        try
        {
            boost::python::object module =
                boost::python::import (
                    boost::filesystem::path (argv[1]).stem ().c_str ());
                
            char methodName[] = "area";
            boost::python::object obj (module.attr (methodName));

            char* end;
            double val = strtod (argv[2], &end);
            if (0 != strlen (end))
            {
                throw std::invalid_argument ("argv[2] failed strtod");
            }
            boost::python::object inVal (val);
            boost::python::object resultVal = obj (inVal);

            std::wcout << L"resultVal (" << val << L"): " << resultVal <<
                std::endl;
            std::wcout << L"inVal (" << val << "): " << inVal << std::endl;
                
            std::wcout << obj << std::endl << std::endl;
                    
        }
        catch (std::exception ex)
        {
            std::wcout << L"caught std::exception: \"" << ex.what () << std::endl;
        }
        catch (boost::python::error_already_set)
        {
            std::wcout << L"caught boost::python::error_already_set" <<
                std::endl;
            PyErr_Print ();
        }
        catch (...)
        {
            std::wcout << L"caught some unknown exception" << std::endl;
            PyErr_Print ();
        }
        Py_XDECREF (moduleName);
        moduleName = 0;
#endif
        try
        {
            tryPythonFile (argv[1]);
//            boost::python::exec_file (argv[1]);
        }
        catch (boost::python::error_already_set ex)
        {
            std::wcout << L"Caught boost::python::error_already_set" << std::endl;
            std::wcout << L"<outer>" << std::endl;
            PyErr_Print ();
            std::wcout << L"</outer>" << std::endl;
        }
        catch (std::exception ex)
        {
            std::wcout << L"Caught std::exception: \"" << ex.what () << "\"" << std::endl;
        }
        catch (...)
        {
          
            std::wcout << L"Caught unexpected exception." << std::endl;
        }
    }
    else
    {
        std::wcout << L"usage a.out [filename.py] {args...}" << std::endl;
    }

    return EXIT_SUCCESS;
}
