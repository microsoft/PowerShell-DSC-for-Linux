#include "python_file_resource.hpp"


#include "debug_tags.hpp"
#include "python_io_helper.hpp"


#include <boost/filesystem.hpp>
#include <iostream>
#include <sstream>


namespace scx
{


/*ctor*/
PythonFileResource::PythonFileResource (
    PyThreadState* const pThreadState,
    boost::python::object const& module,
    boost::python::object const& setFn,
    boost::python::object const& testFn,
    boost::python::object const& getFn)
  : m_pThreadState (pThreadState)
  , m_Module (module)
  , m_SetFn (setFn)
  , m_TestFn (testFn)
  , m_GetFn (getFn)
{
    SCX_BOOKEND ("PythonFileResource::ctor (new)");
}

/*ctor*/
PythonFileResource::PythonFileResource (
        PythonFileResource& ref)
  : m_pThreadState (ref.m_pThreadState)
  , m_Module (ref.m_Module)
  , m_SetFn (ref.m_SetFn)
  , m_TestFn (ref.m_TestFn)
  , m_GetFn (ref.m_GetFn)
{
    SCX_BOOKEND ("PythonFileResource::ctor (copy)");
    ref.m_pThreadState = 0;
}

/*dtor*/
PythonFileResource::~PythonFileResource ()
{
    SCX_BOOKEND ("PythonFileResource::ctor");
    if (m_pThreadState)
    {
        PythonScopedContext lock (m_pThreadState);
        Py_EndInterpreter (m_pThreadState);
        m_pThreadState = 0;
    }
}

std::string
PythonFileResource::get_script_path ()
{
    char* sPath = getenv ("OMI_HOME");
    std::string scriptPath;
    if (sPath == NULL)
    {
        scriptPath = "/opt/omi-1.0.8";
    }
    else
    {
        scriptPath = sPath;
    }
    scriptPath += "/lib/Scripts";
    return scriptPath;
}

/*static*/ int
PythonFileResource::init_python ()
{
    SCX_BOOKEND ("PythonFileResource::init_python");
    if (!Py_IsInitialized ())
    {
        Py_InitializeEx (0);
        if (!PyEval_ThreadsInitialized ())
        {
            PyEval_InitThreads ();
            PyEval_ReleaseLock ();
        }
    }
    return EXIT_SUCCESS;
}

/*static*/ int
PythonFileResource::set_working_path (
    char const* const workingPath)
{
    SCX_BOOKEND ("PythonFileResource::set_working_path");
    PyObject* sysPath =
        PySys_GetObject (const_cast<char*>("path"));
    if (sysPath)
    {
        char const* startPos = workingPath;
        while (startPos)
        {
            char const* endPos = strchr (startPos, ':');
            if (endPos)
            {
                if ((endPos - startPos) > 1)
                {
                    boost::filesystem::path workingDir =
                        boost::filesystem::absolute (
                            boost::filesystem::path (
                                startPos, endPos - 1)).normalize ();
                    PyList_Insert (
                        sysPath, 0,
                        boost::python::object (workingDir.string ()).ptr ());
                }
                startPos = endPos + 1;
            }
            else
            {
                if (strlen (startPos) > 0)
                {
                    boost::filesystem::path workingDir =
                        boost::filesystem::absolute (startPos).normalize ();
                    PyList_Insert (
                        sysPath, 0,
                        boost::python::object (workingDir.string ()).ptr ());
                }
                startPos = endPos;
            }
        }
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/*static*/ int
PythonFileResource::create_new_interpreter (
    PyThreadState** const ppInterpreterOut)
{
    SCX_BOOKEND ("PythonFileResource::create_new_interpreter");
    if (ppInterpreterOut)
    {
        *ppInterpreterOut = Py_NewInterpreter ();
        if (*ppInterpreterOut)
        {
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

/*static*/ boost::python::object
PythonFileResource::load_module (
    char const* const moduleName)
{
#if PRINT_BOOKENDS
    std::ostringstream name;
    name << " name=\"" << moduleName << '\"';
    SCX_BOOKEND_EX ("PythonFileResource::load_module", name.str ());
#endif
    boost::python::object module;
    try
    {
        module = boost::python::import (
            boost::filesystem::path (moduleName).stem ().c_str ());
    }
    catch (boost::python::error_already_set)
    {
        // caught boost::python::error_already_set
        // use scx::python_error_parser to pass the details to a stream ie:
        std::wcerr << L"load_module failed on import[1]: \"" <<
            scx::python_error_parser << "\"" << std::endl;
    }
    catch (std::exception ex)
    {
        // caught a std::exception
        // use std::exception::what to get more details
        std::wcerr << L"load_module failed on import[2]: \"" << ex.what () <<
            "\"" << std::endl;
    }
    catch (...)
    {
        // caught a completely unexpected exception
        std::wcerr << L"load_module failed on import[3]" << std::endl;
    }
    return module;
}

/*static*/ boost::python::object
PythonFileResource::load_function_from_module (
    boost::python::object const& module,
    char const* const functionName)
{
#if PRINT_BOOKENDS
    std::ostringstream name;
    name << " name=\"" << functionName << '\"';
    SCX_BOOKEND_EX ("PythonFileResource::load_function_from_module",
                    name.str ());
#endif
    boost::python::object fn;
    try
    {
        if (module)
        {
            fn = module.attr (functionName);
            if (!PyCallable_Check (fn.ptr ()))
            {
                fn = boost::python::object ();
            }
        }
    }
    catch (boost::python::error_already_set)
    {
        // caught boost::python::error_already_set
        // use scx::python_error_parser to pass the details to a stream ie:
        std::wcerr << L"load_function_from_module failed on attribute: \"" <<
            scx::python_error_parser << std::endl;
    }
    catch (std::exception ex)
    {
        // caught a std::exception
        // use std::exception::what to get more details
        std::wcerr << L"load_function_from_module failed on attribute: \"" <<
            ex.what () << "\"" << std::endl;
    }
    catch (...)
    {
        // caught a completely unexpected exception
        std::wcerr << L"load_function_from_module failed on attribute" <<
            std::endl;
    }
    return fn;
}


} // namespace scx
