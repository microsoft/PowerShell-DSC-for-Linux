#include "palcommon.h"

#if defined(USE_PAL_ATEXIT)
# include <stdlib.h>
# include <common.h>
# include "lock.h"

typedef void (*AtexitFunc)();

/* Array of at-exit functions */
static AtexitFunc _funcs[PAL_ATEXIT_MAX];
static size_t _nfuncs;

/* Lock to synchronize access to _funcs and _nfuncs */
static Lock _lock = LOCK_INITIALIZER;

/* Used to detect re-entrancy errors */
static int _nesting;
static Lock _nestingLock = LOCK_INITIALIZER;

/* Non-zero once the system atexit() has been called */
static int _initialized;

static void _atexitFunc()
{
    PAL_AtexitCall();
}

int PAL_Atexit(void (*func)())
{
    /* Disallow if currently executing PAL_AtexitCall() */
    Lock_Acquire(&_nestingLock);
    {
        DEBUG_ASSERT(_nesting == 0);

        if (_nesting)
        {
            Lock_Release(&_nestingLock);
            return -1;
        }
    }
    Lock_Release(&_nestingLock);

    /* Install _atexitFunc() to be called on the first call */
    if (_initialized == 0)
    {
        Lock_Acquire(&_lock);
        {
            if (_initialized == 0)
            {
                if (atexit(_atexitFunc) != 0)
                {
                    Lock_Release(&_lock);
                    return -1;
                }

                _initialized = 1;
            }
        }
        Lock_Release(&_lock);
    }

    /* Add the function to the array of functions */
    Lock_Acquire(&_lock);
    {
        if (_nfuncs == PAL_ATEXIT_MAX)
        {
            Lock_Release(&_lock);
            return -1;
        }

        _funcs[_nfuncs++] = func;
    }
    Lock_Release(&_lock);

    return 0;
}

int PAL_AtexitCall()
{
    /* Disallow if currently executing PAL_AtexitCall() */
    Lock_Acquire(&_nestingLock);
    {
        DEBUG_ASSERT(_nesting == 0);

        if (_nesting)
        {
            Lock_Release(&_nestingLock);
            return -1;
        }

        _nesting = 1;
    }
    Lock_Release(&_nestingLock);

    /* Call all the functions and reset array to zero-size */
    Lock_Acquire(&_lock);
    {
        size_t i;

        for (i = 0; i < _nfuncs; i++)
            (*_funcs[i])();

        _nfuncs = 0;
    }
    Lock_Release(&_lock);

    /* Reset _nesting to zero */
    Lock_Acquire(&_nestingLock);
    {
        _nesting = 0;
    }
    Lock_Release(&_nestingLock);

    return 0;
}

#endif /* defined(USE_PAL_ATEXIT) */
