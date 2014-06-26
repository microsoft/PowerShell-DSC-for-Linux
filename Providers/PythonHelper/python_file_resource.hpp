#ifndef INCLUDED_PYTHON_FILE_RESOURCE_HPP
#define INCLUDED_PYTHON_FILE_RESOURCE_HPP


#include <boost/python.hpp>
#include <cstdlib>
#include <sstream>
#include <string>


#include "debug_tags.hpp"
#include "python_scoped_context.hpp"


namespace scx
{


class PythonFileResource
{
public:
    template<typename T>
    static int create (
        T** const ppInstance,
        char const* const moduleName);

    explicit /*ctor*/ PythonFileResource (PythonFileResource& ref);
    virtual /*dtor*/ ~PythonFileResource ();

    PyThreadState* getThreadState () const { return m_pThreadState; }
    boost::python::object const& getSetFn () const { return m_SetFn; }
    boost::python::object const& getTestFn () const { return m_TestFn; }
    boost::python::object const& getGetFn () const { return m_GetFn; }

private:
    /*ctor*/ PythonFileResource (
        PyThreadState* const pThreadState,
        boost::python::object const& module,
        boost::python::object const& setFn,
        boost::python::object const& testFn,
        boost::python::object const& getFn);

    static std::string get_script_path ();
    static int init_python ();
    static int set_working_path (char const* const workingPath);
    static int create_new_interpreter (PyThreadState** const ppInterpeterOut);
    static boost::python::object load_module (char const* const moduleName);
    static boost::python::object load_function_from_module (
        boost::python::object const& module,
        char const* const functionName);


    PyThreadState* m_pThreadState;
    boost::python::object const m_Module;
    boost::python::object const m_SetFn;
    boost::python::object const m_TestFn;
    boost::python::object const m_GetFn;
};


template<typename T>
/*static*/ int
PythonFileResource::create (
    T** const ppInstance,
    char const* const moduleName)
{
#if PRINT_BOOKENDS
    std::ostringstream name;
    name << " name=\"" << moduleName << '\"';
    SCX_BOOKEND_EX ("PythonFileResource::create", name.str ());
#endif
    int rval = EXIT_FAILURE;
    if (ppInstance &&
        !*ppInstance)
    {
        if (0 != moduleName &&
            0 < strlen (moduleName) &&
            EXIT_SUCCESS == init_python ())
        {
            PyThreadState* pThreadState;
            if (EXIT_SUCCESS == create_new_interpreter (&pThreadState))
            {
                PythonScopedContext lock (pThreadState);
                set_working_path (get_script_path ().c_str());
                boost::python::object module = load_module (moduleName);
                if (module)
                {
                    boost::python::object setFn =
                        load_function_from_module (module, "Set_Marshall");
                    boost::python::object testFn =
                        load_function_from_module (
                            module, "Test_Marshall");
                    boost::python::object getFn =
                        load_function_from_module (module, "Get_Marshall");
                    if (setFn && testFn && getFn)
                    {
                        PythonFileResource temp (
                            pThreadState, module, setFn, testFn, getFn);
                        *ppInstance = new T (temp);
                        rval = EXIT_SUCCESS;
                    }
                }
                if (EXIT_SUCCESS != rval)
                {
                    Py_EndInterpreter (pThreadState);
                }
            }
        }
    }
    return rval;
}


}


#endif // INCLUDED_PYTHON_FILE_RESOURCE_HPP
