/*============================================================================
 * Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *============================================================================
 */
#include "PythonHelper.hpp"
#include <iostream>
#include <stdlib.h>
#include <dlfcn.h>
#include <vector>
#include <sstream>

// This will contain the handle to the dlopen'ed python library.
void*     DL_PythonLib;

// These are function pointers and will be assigned to the python function symbols that we will get from the python libary through dlsym.
PyObject*  (*DL_PyImport_ImportModule)(const char *name);
PyObject*  (*DL_PyString_FromString)(const char *v);
char*      (*DL_PyString_AsString)(PyObject *string);
long       (*DL_PyLong_AsLong)(PyObject *io);
PyObject*  (*DL_PyLong_FromLong)(long ival);
PyObject*  (*DL_PyFloat_FromDouble)(double v);
PyObject*  (*DL_PyObject_GetAttrString)(PyObject *o, const char *attr_name);
int        (*DL_PyCallable_Check)(PyObject *o);
PyObject*  (*DL_PyObject_CallObject)(PyObject *callable_object, PyObject *args);
void       (*DL_Py_Initialize)();
void       (*DL_Py_Finalize)();     
PyObject*  (*DL_PyErr_Occurred)();
void       (*DL_PyErr_Print)();
int        (*DL_PyTuple_SetItem)(PyObject *p, Py_ssize_t pos, PyObject *o);
PyObject*  (*DL_PyTuple_New)(Py_ssize_t len);
Py_ssize_t (*DL_PyList_Size)(PyObject *list);
PyObject*  (*DL_PyList_GetItem)(PyObject *list, Py_ssize_t index);

int
initPython (
    char const* const programName,
    char const* const workingPath)
{
    std::vector<std::string> supportedPythonLibNames;
    supportedPythonLibNames.push_back("libpython3.4m.so.1.0");
    supportedPythonLibNames.push_back("libpython3.3m.so.1.0");
    supportedPythonLibNames.push_back("libpython3.2m.so.1.0");
    supportedPythonLibNames.push_back("libpython3.1.so.1.0");
    supportedPythonLibNames.push_back("libpython3.0.so.1.0");
    supportedPythonLibNames.push_back("libpython2.7.so.1.0");
    supportedPythonLibNames.push_back("libpython2.6.so.1.0");
    supportedPythonLibNames.push_back("libpython2.5.so.1.0");
    bool fullyLoaded = false;

    for (std::vector<std::string>::const_iterator it = supportedPythonLibNames.begin();
         it != supportedPythonLibNames.end(); ++it)
    {
        // Open python library and get the function pointers for the functions we need.
        std::cerr << "Trying to open Python library: " << *it << "... ";
        DL_PythonLib              = dlopen(it->c_str(), RTLD_NOW | RTLD_GLOBAL);
        if (DL_PythonLib == NULL)
        {
            std::cerr << "Failed" << std::endl;
            continue;
        }
        else
        {
            std::cerr << "Success!" << std::endl;
        }
        
        DL_PyImport_ImportModule  = (PyObject*  (*)(const char *name))                          dlsym(DL_PythonLib, "PyImport_ImportModule");

        DL_PyString_FromString    = (PyObject*  (*)(const char *v))                             dlsym(DL_PythonLib, "PyString_FromString");
        DL_PyString_AsString      = (char*      (*)(PyObject *string))                          dlsym(DL_PythonLib, "PyString_AsString");
        // The two functions above are renamed to PyBytes_ instead of PyString_ in python 3.x.  Let's try to get these symbols if the above fails.
        if (DL_PyString_FromString == NULL &&  DL_PyString_AsString == NULL)
        {
            DL_PyString_FromString    = (PyObject*  (*)(const char *v))                         dlsym(DL_PythonLib, "PyBytes_FromString");
            DL_PyString_AsString      = (char*      (*)(PyObject *string))                      dlsym(DL_PythonLib, "PyBytes_AsString");
        }
        
        DL_PyLong_AsLong          = (long       (*)(PyObject *io))                              dlsym(DL_PythonLib, "PyLong_AsLong");
        DL_PyLong_FromLong        = (PyObject*  (*)(long ival))                                 dlsym(DL_PythonLib, "PyLong_FromLong");
        DL_PyFloat_FromDouble     = (PyObject*  (*)(double v))                                  dlsym(DL_PythonLib, "PyFloat_FromDouble");
        DL_PyObject_GetAttrString = (PyObject*  (*)(PyObject *o, const char *attr_name))        dlsym(DL_PythonLib, "PyObject_GetAttrString");
        DL_PyCallable_Check       = (int        (*)(PyObject *o))                               dlsym(DL_PythonLib, "PyCallable_Check");
        DL_PyObject_CallObject    = (PyObject*  (*)(PyObject *callable_object, PyObject *args)) dlsym(DL_PythonLib, "PyObject_CallObject");
        DL_Py_Initialize          = (void       (*)())                                          dlsym(DL_PythonLib, "Py_Initialize");
        DL_Py_Finalize            = (void       (*)())                                          dlsym(DL_PythonLib, "Py_Finalize");
        DL_PyErr_Occurred         = (PyObject*  (*)())                                          dlsym(DL_PythonLib, "PyErr_Occurred");
        DL_PyErr_Print            = (void       (*)())                                          dlsym(DL_PythonLib, "PyErr_Print");
        DL_PyTuple_SetItem        = (int        (*)(PyObject *p, Py_ssize_t pos, PyObject *o))  dlsym(DL_PythonLib, "PyTuple_SetItem");
        DL_PyTuple_New            = (PyObject*  (*)(Py_ssize_t len))                            dlsym(DL_PythonLib, "PyTuple_New");
        DL_PyList_Size            = (Py_ssize_t (*)(PyObject *list))                            dlsym(DL_PythonLib, "PyList_Size");
        DL_PyList_GetItem         = (PyObject*  (*)(PyObject *list, Py_ssize_t index))          dlsym(DL_PythonLib, "PyList_GetItem");
        
        if (DL_PyImport_ImportModule == NULL)
        {
            std::cerr << "DL_PyImport_ImportModule" << std::endl;
            continue;
        }
        if (DL_PyString_FromString == NULL)
        {
            std::cerr << "DL_PyString_FromString" << std::endl;
            continue;
        }
        if (DL_PyString_AsString == NULL)
        {
            std::cerr << "DL_PyString_AsString" << std::endl;
            continue;
        }
        if (DL_PyLong_AsLong == NULL)
        {
            std::cerr << "DL_PyLong_AsLong" << std::endl;
            continue;
        }
        if (DL_PyLong_FromLong == NULL)
        {
            std::cerr << "DL_PyLong_FromLong" << std::endl;
            continue;
        }
        if (DL_PyFloat_FromDouble == NULL)
        {
            std::cerr << "DL_PyFloat_FromDouble" << std::endl;
            continue;
        }
        if (DL_PyObject_GetAttrString == NULL)
        {
            std::cerr << "DL_PyObject_GetAttrString" << std::endl;
            continue;
        }
        if (DL_PyCallable_Check == NULL)
        {
            std::cerr << "DL_PyCallable_Check" << std::endl;
            continue;
        }
        if (DL_PyObject_CallObject == NULL)
        {
            std::cerr << "DL_PyObject_CallObject" << std::endl;
            continue;
        }
        if (DL_Py_Initialize == NULL)
        {
            std::cerr << "DL_Py_Initialize" << std::endl;
            continue;
        }
        if (DL_Py_Finalize == NULL)
        {
            std::cerr << "DL_Py_Finalize" << std::endl;
            continue;
        }
        if (DL_PyErr_Occurred == NULL)
        {
            std::cerr << "DL_PyErr_Occurred" << std::endl;
            continue;
        }
        if (DL_PyErr_Print == NULL)
        {
            std::cerr << "DL_PyErr_Print" << std::endl;
            continue;
        }
        if (DL_PyTuple_SetItem == NULL)
        {
            std::cerr << "DL_PyTuple_SetItem" << std::endl;
            continue;
        }
        if (DL_PyTuple_New == NULL)
        {
            std::cerr << "DL_PyTuple_New" << std::endl;
            continue;
        }
        if (DL_PyList_Size == NULL)
        {
            std::cerr << "DL_PyList_Size" << std::endl;
            continue;
        }
        if (DL_PyList_GetItem == NULL)
        {
            std::cerr << "DL_PyList_GetItem" << std::endl;
            continue;
        }

        fullyLoaded = true;
        break;        
    }

    if (fullyLoaded == false)
    {
        return -1;
    }

    std::cerr << "Setting Python path to: " << workingPath << std::endl;
    setenv("PYTHONPATH", workingPath, 0); // #include <stdlib.h> to get the prototype
    DL_Py_Initialize ();
    
    return EXIT_SUCCESS;
}

void
closePython ()
{
    DL_Py_Finalize ();
    dlclose(DL_PythonLib);
}

PyObjPtr
loadModule (
    char const* const moduleName)
{
    PyObjPtr pModule;
    if (0 != moduleName)
    {
        pModule = DL_PyImport_ImportModule(moduleName);
        
        PyObjPtr error (DL_PyErr_Occurred());
        
        if ( error != NULL )
        {
            std::cerr << "IMPORT FAILED" << std::endl;
            DL_PyErr_Print();
        }
        if (pModule == NULL)
        {
            std::cerr << "pModule = NULL" << std::endl;
        }
    }
    return pModule;
}

PyObjPtr
loadFunctionFromModule (
    PyObjPtr const& pModule,
    char const* const functionName)
{
    PyObjPtr pFunc;
    if (pModule &&
        0 != functionName)
    {
      pFunc = DL_PyObject_GetAttrString (pModule, const_cast<char*>(functionName));
        if (pFunc &&
            !DL_PyCallable_Check (pFunc))
        {
            pFunc = 0;
        }
    }
    return pFunc;
}

long
callFunction (
    PyObjPtr const& pFunction,
    char const* const destinationPath,
    char const* const sourcePath,
    char const* const ensure,
    char const* const type,
    char const* const force,
    char const* const contents,
    char const* const checksum,
    char const* const recurse,
    char const* const links,
    char const* const owner,
    char const* const group,
    char const* const mode)
{
    long rval = EXIT_FAILURE;
    if (pFunction)
    {
        PyObjPtr pTuple;
        if (EXIT_SUCCESS == TupleCreator<
                char const* const,
                char const* const,
                char const* const,
                char const* const,
                char const* const,
                char const* const,
                char const* const,
                char const* const,
                char const* const,
                char const* const,
                char const* const,
                char const* const>::create (
                    &pTuple,
                    destinationPath,
                    sourcePath,
                    ensure,
                    type,
                    force,
                    contents,
                    checksum,
                    recurse,
                    links,
                    owner,
                    group,
                    mode))
        {
            PyObjPtr pOutVal (DL_PyObject_CallObject (pFunction, pTuple));
            
            PyObjPtr error (DL_PyErr_Occurred());
            if ( error != NULL )
            {
                DL_PyErr_Print();
            }

            rval = DL_PyLong_AsLong (pOutVal);
        }
    }
    return rval;
}


static int checkPythonError()
{
    PyObjPtr error(DL_PyErr_Occurred());
    if (error != NULL)
    {
        DL_PyErr_Print();
        return -1;
    }
    return 0;
}

int callPythonFunction(
    std::vector<std::string>& ret_strings,
    PyObjPtr const& pFunction,
    int n,
    ...)
{
    // ERROR CHECK: that n is valid number
    if (n < 0)
    {
        return -1;
    }

    // create a tuple out of the args
    va_list param_list;
    va_start(param_list, n);
    PyObjPtr pTuple(DL_PyTuple_New(n));
    for (int i = 0; i < n; ++i)
    {
        char* cur_arg = va_arg(param_list, char*);
        DL_PyTuple_SetItem(pTuple, i, DL_PyString_FromString(cur_arg));
    }
    va_end(param_list);

    // Call function
    PyObjPtr pOutVal (DL_PyObject_CallObject(pFunction, pTuple));
    if (checkPythonError() != 0)
    {
        return -1;
    }

    // pOutVal is a list. get return value
    int num_retvals = DL_PyList_Size(pOutVal);
    long exit_code = -1;

    if (num_retvals > 0)
    {
        PyObject* ret_item = DL_PyList_GetItem(pOutVal, 0);
        exit_code = DL_PyLong_AsLong(ret_item);
    }
    
    for (int i = 1; i < num_retvals; i++)
    {
        PyObject* ret_item = DL_PyList_GetItem(pOutVal, i);
        char * ret_arg = DL_PyString_AsString(ret_item);
        ret_strings.push_back(ret_arg);
    }

    return exit_code;
}

std::string GetScriptPath()
{
    char* sPath = getenv("OMI_HOME");
    std::string scriptPath;
    if (sPath == NULL)
    {
        std::cerr << "Error: Expected environment variable OMI_HOME is not defined.  Looking up scripts in /opt/omi-1.0.8/lib/Scripts" << std::endl;
        scriptPath = "/opt/omi-1.0.8";
    }
    else
    {
        scriptPath = sPath;
    }
    scriptPath += "/lib/Scripts";
    return scriptPath;
}
