#include "python_scoped_context.hpp"


#include "debug_tags.hpp"


#ifndef PRINT_LOCK_BOOKEND
#define PRINT_LOCK_BOOKEND (0)
#endif


#if (PRINT_LOCK_BOOKEND)
#define LOCK_BOOKEND(text) SCX_BOOKEND (text)
#else
#define LOCK_BOOKEND(text)
#endif


namespace scx
{


/*ctor*/
PythonScopedContext::PythonScopedContext (
    PyThreadState* pNewContext)
  : m_pNewContext (pNewContext)
  , m_GILState ()
  , m_pOldContext (0)
{
    LOCK_BOOKEND ("PyhonScopedContext::ctor (lock)");
    m_GILState = PyGILState_Ensure ();
    m_pOldContext = PyThreadState_Swap (m_pNewContext);
}

/*dtor*/
PythonScopedContext::~PythonScopedContext ()
{
    LOCK_BOOKEND ("PyhonScopedContext::dtor (unlock)");
    PyThreadState_Swap (m_pOldContext);
    PyGILState_Release (m_GILState);
}


} // namespace scx
