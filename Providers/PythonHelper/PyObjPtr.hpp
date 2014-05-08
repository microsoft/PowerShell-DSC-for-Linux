/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
 */
#ifndef INCLUDED_PYOBJPTR_HPP
#define INCLUDED_PYOBJPTR_HPP


#include <Python.h>


class PyObjPtr
{
public:
    /*ctor*/ PyObjPtr ()
      : m_pObj (0)
    {
        // empty
    }

    explicit /*ctor*/ PyObjPtr (PyObject* const pObj)
      : m_pObj (pObj)
    {
        // empty
    }

    /*ctor*/ PyObjPtr (PyObjPtr const& ref)
      : m_pObj (ref.m_pObj)
    {
        Py_XINCREF (m_pObj);
    }

    /*dtor*/ ~PyObjPtr ()
    {
        cleanUp ();
    }

    PyObject* get () const
    {
        return m_pObj;
    }

    /*PyObject* */ operator PyObject* () const
    {
        return get ();
    }

    PyObject* operator -> () const
    {
        return get ();
    }

    PyObjPtr& operator = (PyObject* const pObj)
    {
        return set (pObj);
    }

    PyObjPtr& operator = (PyObjPtr const& rhs)
    {
        Py_XINCREF (rhs.m_pObj);
        return set (rhs.m_pObj);
    }

private:
    PyObjPtr& set (PyObject* const pObj)
    {
        cleanUp ();
        m_pObj = pObj;
        return *this;
    }

    void cleanUp ()
    {
        Py_XDECREF (m_pObj);
        m_pObj = 0;
    }

    PyObject* m_pObj;

};




#endif // INCLUDED_PYOBJPTR_HPP
