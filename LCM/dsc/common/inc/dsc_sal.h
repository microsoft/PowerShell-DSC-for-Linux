#ifndef _DSC_SAL_h
#define _DSC_SAL_h

#if !defined(_MSC_VER)

#if !defined(_Deref_pre_opt_z_)
# define _Deref_pre_opt_z_
#endif

#if !defined(_In_z_)
# define _In_z_
#endif

#if !defined(_In_z_count_)
# define _In_z_count_
#endif

#if !defined(MI_INLINE_CALL)
# define MI_INLINE_CALL
#endif

#if !defined(__in)
// Do not define __in since it'll create conflict with libstdc++ on Linux.
//# define __in
#endif

#if !defined(__in_z)
# define __in_z
#endif

#if !defined(__out)
// Do not define __out since it'll create conflict with libstdc++ on Linux.
//# define __out
#endif

#if !defined(__deref_out)
# define __deref_out
#endif

#if !defined(__in_z_opt)
# define __in_z_opt
#endif

#if !defined(__in_opt)
# define __in_opt
#endif

#endif

#endif


