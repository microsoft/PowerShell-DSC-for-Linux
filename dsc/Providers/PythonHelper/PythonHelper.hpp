/*============================================================================
 * Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *============================================================================
 */
#ifndef INCLUDED_PYTHONHELPER_HPP
#define INCLUDED_PYTHONHELPER_HPP


#include "PyObjPtr.hpp"


#include <cstdlib>
#include <Python.h>
#include <string>
#include <vector>

extern PyObject* (*DL_PyString_FromString)(const char *v);
extern PyObject* (*DL_PyLong_FromLong)(long ival);
extern PyObject* (*DL_PyFloat_FromDouble)(double v);
extern int       (*DL_PyTuple_SetItem)(PyObject *p, Py_ssize_t pos, PyObject *o);
extern PyObject* (*DL_PyTuple_New)(Py_ssize_t len);

int callPythonFunction(
    std::vector<std::string>& ret_strings,
    PyObjPtr const& pFunction,
    int n,
    ...);

std::string GetScriptPath();

inline int
tupleSetItem (
    PyObjPtr const& pTuple,
    size_t const& pos,
    long const& val)
{
    return DL_PyTuple_SetItem (pTuple, pos, DL_PyLong_FromLong (val));
}

inline int
tupleSetItem (
    PyObjPtr const& pTuple,
    size_t const& pos,
    double const& val)
{
    return DL_PyTuple_SetItem (pTuple, pos, DL_PyFloat_FromDouble (val));
}

inline int
tupleSetItem (
    PyObjPtr const& pTuple,
    size_t const& pos,
    std::string const& val)
{
    return DL_PyTuple_SetItem (pTuple, pos, DL_PyString_FromString (val.c_str ()));
}

inline int
tupleSetItem (
    PyObjPtr const& pTuple,
    size_t const& pos,
    char const* const val)
{
    return DL_PyTuple_SetItem (pTuple, pos, DL_PyString_FromString (val));
}


class NullT {};


template<typename T1,
         typename T2 = NullT,
         typename T3 = NullT,
         typename T4 = NullT,
         typename T5 = NullT,
         typename T6 = NullT,
         typename T7 = NullT,
         typename T8 = NullT,
         typename T9 = NullT,
         typename T10 = NullT,
         typename T11 = NullT,
         typename T12 = NullT>
class TupleInserter
{
public:
    static int
    insert (
        PyObjPtr& pTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6,
        T7 const& val7,
        T8 const& val8,
        T9 const& val9,
        T10 const& val10,
        T11 const& val11,
        T12 const& val12)
    {
        int rval = TupleInserter<
                T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::insert (
                    pTuple, val1, val2, val3, val4, val5, val6, val7, val8,
                    val9, val10, val11);
        if (EXIT_SUCCESS == rval)
        {
            rval = tupleSetItem (pTuple, 11, val12);
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5,
         typename T6,
         typename T7,
         typename T8,
         typename T9,
         typename T10,
         typename T11>
class TupleInserter<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, NullT>
{
public:
    static int
    insert (
        PyObjPtr& pTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6,
        T7 const& val7,
        T8 const& val8,
        T9 const& val9,
        T10 const& val10,
        T11 const& val11)
    {
        int rval = TupleInserter<
                T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::insert (
                    pTuple, val1, val2, val3, val4, val5, val6, val7, val8,
                    val9, val10);
        if (EXIT_SUCCESS == rval)
        {
            rval = tupleSetItem (pTuple, 10, val11);
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5,
         typename T6,
         typename T7,
         typename T8,
         typename T9,
         typename T10>
class TupleInserter<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, NullT, NullT>
{
public:
    static int
    insert (
        PyObjPtr& pTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6,
        T7 const& val7,
        T8 const& val8,
        T9 const& val9,
        T10 const& val10)
    {
        int rval = TupleInserter<
                T1, T2, T3, T4, T5, T6, T7, T8, T9>::insert (
                    pTuple, val1, val2, val3, val4, val5, val6, val7, val8,
                    val9);
        if (EXIT_SUCCESS == rval)
        {
            rval = tupleSetItem (pTuple, 9, val10);
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5,
         typename T6,
         typename T7,
         typename T8,
         typename T9>
class TupleInserter<T1, T2, T3, T4, T5, T6, T7, T8, T9, NullT, NullT, NullT>
{
public:
    static int
    insert (
        PyObjPtr& pTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6,
        T7 const& val7,
        T8 const& val8,
        T9 const& val9)
    {
        int rval = TupleInserter<T1, T2, T3, T4, T5, T6, T7, T8>::insert (
                    pTuple, val1, val2, val3, val4, val5, val6, val7, val8);
        if (EXIT_SUCCESS == rval)
        {
            rval = tupleSetItem (pTuple, 8, val9);
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5,
         typename T6,
         typename T7,
         typename T8>
class TupleInserter<T1, T2, T3, T4, T5, T6, T7, T8, NullT, NullT, NullT, NullT>
{
public:
    static int
    insert (
        PyObjPtr& pTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6,
        T7 const& val7,
        T8 const& val8)
    {
        int rval = TupleInserter<T1, T2, T3, T4, T5, T6, T7>::insert (
                    pTuple, val1, val2, val3, val4, val5, val6, val7);
        if (EXIT_SUCCESS == rval)
        {
            rval = tupleSetItem (pTuple, 7, val8);
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5,
         typename T6,
         typename T7>
class TupleInserter<
    T1, T2, T3, T4, T5, T6, T7, NullT, NullT, NullT, NullT, NullT>
{
public:
    static int
    insert (
        PyObjPtr& pTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6,
        T7 const& val7)
    {
        int rval = TupleInserter<T1, T2, T3, T4, T5, T6>::insert (
                    pTuple, val1, val2, val3, val4, val5, val6);
        if (EXIT_SUCCESS == rval)
        {
            rval = tupleSetItem (pTuple, 6, val7);
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5,
         typename T6>
class TupleInserter<
    T1, T2, T3, T4, T5, T6, NullT, NullT, NullT, NullT, NullT, NullT>
{
public:
    static int
    insert (
        PyObjPtr& pTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6)
    {
        int rval = TupleInserter<T1, T2, T3, T4, T5>::insert (
                    pTuple, val1, val2, val3, val4, val5);
        if (EXIT_SUCCESS == rval)
        {
            rval = tupleSetItem (pTuple, 5, val6);
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5>
class TupleInserter<
    T1, T2, T3, T4, T5, NullT, NullT, NullT, NullT, NullT, NullT, NullT>
{
public:
    static int
    insert (
        PyObjPtr& pTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5)
    {
        int rval = TupleInserter<T1, T2, T3, T4>::insert (
                    pTuple, val1, val2, val3, val4);
        if (EXIT_SUCCESS == rval)
        {
            rval = tupleSetItem (pTuple, 4, val5);
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4>
class TupleInserter<
    T1, T2, T3, T4, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT>
{
public:
    static int
    insert (
        PyObjPtr& pTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4)
    {
        int rval = TupleInserter<T1, T2, T3>::insert (pTuple, val1, val2, val3);
        if (EXIT_SUCCESS == rval)
        {
            rval = tupleSetItem (pTuple, 3, val4);
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3>
class TupleInserter<
    T1, T2, T3, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT>
{
public:
    static int
    insert (
        PyObjPtr& pTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3)
    {
        int rval = TupleInserter<T1, T2>::insert (pTuple, val1, val2);
        if (EXIT_SUCCESS == rval)
        {
            rval = tupleSetItem (pTuple, 2, val3);
        }
        return rval;
    }
};

template<typename T1,
         typename T2>
class TupleInserter<
    T1, T2, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT,
    NullT>
{
public:
    static int
    insert (
        PyObjPtr& pTuple,
        T1 const& val1,
        T2 const& val2)
    {
        int rval = TupleInserter<T1>::insert (pTuple, val1);
        if (EXIT_SUCCESS == rval)
        {
            rval = tupleSetItem (pTuple, 1, val2);
        }
        return rval;
    }
};

template<typename T1>
class TupleInserter<
    T1, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT,
    NullT>
{
public:
    static int
    insert (
        PyObjPtr& pTuple,
        T1 const& val1)
    {
        return tupleSetItem (pTuple, 0, val1);
    }
};




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename T1,
         typename T2 = NullT,
         typename T3 = NullT,
         typename T4 = NullT,
         typename T5 = NullT,
         typename T6 = NullT,
         typename T7 = NullT,
         typename T8 = NullT,
         typename T9 = NullT,
         typename T10 = NullT,
         typename T11 = NullT,
         typename T12 = NullT>
class TupleCreator
{
public:
    static int
    create (
        PyObjPtr* ppTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6,
        T7 const& val7,
        T8 const& val8,
        T9 const& val9,
        T10 const& val10,
        T11 const& val11,
        T12 const& val12)
    {
        int rval = EXIT_FAILURE;
        if (ppTuple)
        {
            *ppTuple = DL_PyTuple_New (12);
            if (*ppTuple)
            {
                rval = TupleInserter<
                    T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::insert (
                        *ppTuple, val1, val2, val3, val4, val5, val6, val7,
                        val8, val9, val10, val11, val12);
                if (EXIT_SUCCESS != rval)
                {
                    ppTuple = 0;
                }
            }
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5,
         typename T6,
         typename T7,
         typename T8,
         typename T9,
         typename T10,
         typename T11>
class TupleCreator<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, NullT>
{
public:
    static int
    create (
        PyObjPtr* ppTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6,
        T7 const& val7,
        T8 const& val8,
        T9 const& val9,
        T10 const& val10,
        T11 const& val11)
    {
        int rval = EXIT_FAILURE;
        if (ppTuple)
        {
            *ppTuple = DL_PyTuple_New (11);
            if (*ppTuple)
            {
                rval = TupleInserter<
                    T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::insert (
                        *ppTuple, val1, val2, val3, val4, val5, val6, val7,
                        val8, val9, val10, val11);
                if (EXIT_SUCCESS != rval)
                {
                    ppTuple = 0;
                }
            }
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5,
         typename T6,
         typename T7,
         typename T8,
         typename T9,
         typename T10>
class TupleCreator<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, NullT, NullT>
{
public:
    static int
    create (
        PyObjPtr* ppTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6,
        T7 const& val7,
        T8 const& val8,
        T9 const& val9,
        T10 const& val10)
    {
        int rval = EXIT_FAILURE;
        if (ppTuple)
        {
            *ppTuple = DL_PyTuple_New (10);
            if (*ppTuple)
            {
                rval = TupleInserter<
                    T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::insert (
                        *ppTuple, val1, val2, val3, val4, val5, val6, val7,
                        val8, val9, val10);
                if (EXIT_SUCCESS != rval)
                {
                    ppTuple = 0;
                }
            }
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5,
         typename T6,
         typename T7,
         typename T8,
         typename T9>
class TupleCreator<T1, T2, T3, T4, T5, T6, T7, T8, T9, NullT, NullT, NullT>
{
public:
    static int
    create (
        PyObjPtr* ppTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6,
        T7 const& val7,
        T8 const& val8,
        T9 const& val9)
    {
        int rval = EXIT_FAILURE;
        if (ppTuple)
        {
            *ppTuple = DL_PyTuple_New (9);
            if (*ppTuple)
            {
                rval = TupleInserter<
                    T1, T2, T3, T4, T5, T6, T7, T8, T9>::insert (
                        *ppTuple, val1, val2, val3, val4, val5, val6, val7,
                        val8, val9);
                if (EXIT_SUCCESS != rval)
                {
                    ppTuple = 0;
                }
            }
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5,
         typename T6,
         typename T7,
         typename T8>
class TupleCreator<T1, T2, T3, T4, T5, T6, T7, T8, NullT, NullT, NullT, NullT>
{
public:
    static int
    create (
        PyObjPtr* ppTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6,
        T7 const& val7,
        T8 const& val8)
    {
        int rval = EXIT_FAILURE;
        if (ppTuple)
        {
            *ppTuple = DL_PyTuple_New (8);
            if (*ppTuple)
            {
                rval = TupleInserter<T1, T2, T3, T4, T5, T6, T7, T8>::insert (
                        *ppTuple, val1, val2, val3, val4, val5, val6, val7,
                        val8);
                if (EXIT_SUCCESS != rval)
                {
                    ppTuple = 0;
                }
            }
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5,
         typename T6,
         typename T7>
class TupleCreator<
    T1, T2, T3, T4, T5, T6, T7, NullT, NullT, NullT, NullT, NullT>
{
public:
    static int
    create (
        PyObjPtr* ppTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6,
        T7 const& val7)
    {
        int rval = EXIT_FAILURE;
        if (ppTuple)
        {
            *ppTuple = DL_PyTuple_New (7);
            if (*ppTuple)
            {
                rval = TupleInserter<T1, T2, T3, T4, T5, T6, T7>::insert (
                        *ppTuple, val1, val2, val3, val4, val5, val6, val7);
                if (EXIT_SUCCESS != rval)
                {
                    ppTuple = 0;
                }
            }
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5,
         typename T6>
class TupleCreator<
    T1, T2, T3, T4, T5, T6, NullT, NullT, NullT, NullT, NullT, NullT>
{
public:
    static int
    create (
        PyObjPtr* ppTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5,
        T6 const& val6)
    {
        int rval = EXIT_FAILURE;
        if (ppTuple)
        {
            *ppTuple = DL_PyTuple_New (6);
            if (*ppTuple)
            {
                rval = TupleInserter<T1, T2, T3, T4, T5, T6>::insert (
                        *ppTuple, val1, val2, val3, val4, val5, val6);
                if (EXIT_SUCCESS != rval)
                {
                    ppTuple = 0;
                }
            }
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4,
         typename T5>
class TupleCreator<
    T1, T2, T3, T4, T5, NullT, NullT, NullT, NullT, NullT, NullT, NullT>
{
public:
    static int
    create (
        PyObjPtr* ppTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4,
        T5 const& val5)
    {
        int rval = EXIT_FAILURE;
        if (ppTuple)
        {
            *ppTuple = DL_PyTuple_New (5);
            if (*ppTuple)
            {
                rval = TupleInserter<T1, T2, T3, T4, T5>::insert (
                        *ppTuple, val1, val2, val3, val4, val5);
                if (EXIT_SUCCESS != rval)
                {
                    ppTuple = 0;
                }
            }
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3,
         typename T4>
class TupleCreator<
    T1, T2, T3, T4, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT>
{
public:
    static int
    create (
        PyObjPtr* ppTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3,
        T4 const& val4)
    {
        int rval = EXIT_FAILURE;
        if (ppTuple)
        {
            *ppTuple = DL_PyTuple_New (4);
            if (*ppTuple)
            {
                rval = TupleInserter<T1, T2, T3, T4>::insert (
                        *ppTuple, val1, val2, val3, val4);
                if (EXIT_SUCCESS != rval)
                {
                    ppTuple = 0;
                }
            }
        }
        return rval;
    }
};

template<typename T1,
         typename T2,
         typename T3>
class TupleCreator<
    T1, T2, T3, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT>
{
public:
    static int
    create (
        PyObjPtr* ppTuple,
        T1 const& val1,
        T2 const& val2,
        T3 const& val3)
    {
        int rval = EXIT_FAILURE;
        if (ppTuple)
        {
            *ppTuple = DL_PyTuple_New (3);
            if (*ppTuple)
            {
                rval = TupleInserter<T1, T2, T3>::insert (
                    *ppTuple, val1, val2, val3);
                if (EXIT_SUCCESS != rval)
                {
                    ppTuple = 0;
                }
            }
        }
        return rval;
    }
};

template<typename T1,
         typename T2>
class TupleCreator<
    T1, T2, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT,
    NullT>
{
public:
    static int
    create (
        PyObjPtr* ppTuple,
        T1 const& val1,
        T2 const& val2)
    {
        int rval = EXIT_FAILURE;
        if (ppTuple)
        {
            *ppTuple = DL_PyTuple_New (2);
            if (*ppTuple)
            {
                rval = TupleInserter<T1, T2>::insert (*ppTuple, val1, val2);
                if (EXIT_SUCCESS != rval)
                {
                    ppTuple = 0;
                }
            }
        }
        return rval;
    }
};

template<typename T1>
class TupleCreator<
    T1, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT, NullT,
    NullT>
{
public:
    static int
    create (
        PyObjPtr* ppTuple,
        T1 const& val1)
    {
        int rval = EXIT_FAILURE;
        if (ppTuple)
        {
            *ppTuple = DL_PyTuple_New (1);
            if (*ppTuple)
            {
                rval = TupleInserter<T1>::insert (*ppTuple, val1);
                if (EXIT_SUCCESS != rval)
                {
                    ppTuple = 0;
                }
            }
        }
        return rval;
    }
};


int
initPython (
    char const* const programName,
    char const* const workingPath);

void
closePython ();

PyObjPtr
loadModule (
    char const* const moduleName);

PyObjPtr
loadFunctionFromModule (
    PyObjPtr const& pModule,
    char const* const functionName);

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
    char const* const mode);


#endif // INCLUDED_PYTHONHELPER_HPP
