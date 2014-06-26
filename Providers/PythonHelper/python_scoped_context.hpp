#ifndef INCLUDED_PYTHON_SCOPED_RESOURCE_HPP
#define INCLUDED_PYTHON_SCOPED_RESOURCE_HPP


#include <boost/python.hpp>


namespace scx
{


class PythonScopedContext
{
public:
    explicit /*ctor*/ PythonScopedContext (PyThreadState* const pNewContext);
    /*dtor*/ ~PythonScopedContext ();

private:
    /*ctor*/ PythonScopedContext (PythonScopedContext const&); // delete
    PythonScopedContext& operator = (PythonScopedContext const&); // delete

    PyThreadState* m_pNewContext;
    PyGILState_STATE m_GILState;
    PyThreadState* m_pOldContext;
};


} // namespace scx


#endif // INCLUDED_PYTHON_SCOPED_RESOURCE_HPP
