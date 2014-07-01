#include <boost/python.hpp>
#include <boost/filesystem.hpp>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>


#include "python_io_helper.hpp"


namespace
{

char const FILENAME[] = "hello.py";
char const FUNCTION_NAME[] = "area";
double const DEFAULT_RADIUS = 4.0;


class PrintOnExit
{
public:
    /*ctor*/ PrintOnExit (std::wstring text) : m_Text () { m_Text.swap (text); }
    /*dtor*/ ~PrintOnExit () { std::wcout << m_Text << std::endl; }
private:
    std::wstring m_Text;
};


void
tryPythonFile ();

void 
tryPythonFunctionFromFile (
    double const radius);

} // unnamed namespace


int
main (
    int const argc,
    char const* const* argv)
{
    Py_Initialize ();

    boost::filesystem::path workingDir =
        boost::filesystem::absolute ("./").normalize ();
    PyObject* sysPath =
        PySys_GetObject (const_cast<char*>("path"));
    PyList_Insert (sysPath, 0,
                   boost::python::object (workingDir.string ()).ptr ());

    std::wcout << scx::python_unicode_info << std::endl;
    std::wcout << L"<python path>" << std::endl;
    std::wcout << scx::python_path << std::endl;
    std::wcout << L"</python path>" << std::endl;

    try
    {
        tryPythonFile ();
        double radius = DEFAULT_RADIUS;
        if (2 == argc)
        {
            char* end;
            double val = strtod (argv[1], &end);
            if (0 == strlen (end))
            {
                radius = val;
            }
        }
        tryPythonFunctionFromFile (radius);
    }
    catch (boost::python::error_already_set ex)
    {
        std::wcout << L"Caught boost::python::error_already_set" << std::endl;
        std::wcout << L"<outer excetion>" << std::endl;
        // in this case I call PyErr_Print to catch any errors that are
        // thrown from scx::python_error_parser
        PyErr_Print ();
        std::wcout << L"</outer exception>" << std::endl;
    }
    catch (std::exception ex)
    {
        std::wcout << L"Caught std::exception: \"" << ex.what () << "\"" <<
            std::endl;
    }
    catch (...)
    {
        std::wcout << L"Caught an unexpected exception." << std::endl;
    }
    return EXIT_SUCCESS;
}


namespace
{

void
tryPythonFile ()
{
    typedef scx::PythonTextConstants<wchar_t> Text;
    std::wcout << L"<PythonFile>" << std::endl;
    PrintOnExit onExit (L"</PythonFile>");
    try
    {
        std::wcout << Text::PATH_INDENT << L"Opening file: \"" << FILENAME <<
            L"\"" << std::endl;
        boost::python::dict globals;
        boost::python::dict locals;
        boost::python::object result =
            boost::python::exec_file (FILENAME, globals, locals);
        std::wcout << Text::PATH_INDENT << L"returned: " << result << std::endl;
        std::wcout << Text::PATH_INDENT << L"globals: " << globals << std::endl;
        std::wcout << Text::PATH_INDENT << L"locals: " << locals << std::endl;
    }
    catch (boost::python::error_already_set ex)
    {
        std::wcout << L"caught boost::python::error_already_set" <<
            std::endl;
        std::wcout << L"<error>" << std::endl;
        std::wcout << scx::python_error_parser;
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
}


void 
tryPythonFunctionFromFile (
    double const radius)
{
    typedef scx::PythonTextConstants<wchar_t> Text;
    std::wcout << L"<PythonFunctionFromFile>" << std::endl;
    PrintOnExit onExit (L"</PythonFunctionFromFile>");
    try
    {
        std::wcout << Text::PATH_INDENT << L"Opening file: \"" << FILENAME <<
            L"\"" << std::endl;
        boost::python::object module =
            boost::python::import (
                boost::filesystem::path (FILENAME).stem ().c_str ());
        std::wcout << Text::PATH_INDENT << L"Loading function: \"" <<
            FUNCTION_NAME << L"\"" << std::endl;
        boost::python::object fn (module.attr (FUNCTION_NAME));
        if (PyCallable_Check (fn.ptr ()))
        {
            std::wcout << Text::PATH_INDENT << L"Calling function" << std::endl;
            boost::python::object inVal (radius);
            boost::python::object resultVal = fn (inVal);
            std::wcout << Text::PATH_INDENT << FUNCTION_NAME << L"(" <<
                radius << L"): " << resultVal << std::endl;
        }
        else
        {
            std::wcout << Text::PATH_INDENT <<
                L"The loaded object is: \"" << fn << L"\"" << std::endl;
        }
    }
    catch (boost::python::error_already_set ex)
    {
        std::wcout << L"caught boost::python::error_already_set" <<
            std::endl;
        std::wcout << L"<error>" << std::endl;
        std::wcout << scx::python_error_parser;
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
}

} // unnamed namespace
