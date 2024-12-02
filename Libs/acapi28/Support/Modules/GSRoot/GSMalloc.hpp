// *********************************************************************************************************************
// Description:		C Runtime heap management cover functions
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MM
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GSMALLOC_HPP)
#define GSMALLOC_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include "GSRootExport.hpp"

#include <stdlib.h>

#if defined (WINDOWS)
#include <string.h>
#endif

#if defined (__linux__)
#include <string.h>
#endif

// --- Macro definitions -----------------------------------------------------------------------------------------------

#ifndef	CCALL
	#if defined (macintosh) || defined (__linux__)
		#define	CCALL
	#else
		#define	CCALL	__cdecl
	#endif
#endif

// --- Function declarations -------------------------------------------------------------------------------------------

#if defined (__cplusplus)
extern "C" {
#endif

GSROOT_DLL_EXPORT void*		CCALL GS_calloc (size_t num, size_t size);
GSROOT_DLL_EXPORT void*		CCALL GS_malloc (size_t size);
GSROOT_DLL_EXPORT void		CCALL GS_free (void *userData);
GSROOT_DLL_EXPORT void*		CCALL GS_realloc (void *userData, size_t newSize);

#if defined (WINDOWS)
GSROOT_DLL_EXPORT void*		CCALL GS_recalloc (void* userData, size_t num, size_t size);
GSROOT_DLL_EXPORT void*		CCALL GS_aligned_recalloc (void* userData, size_t num, size_t size, size_t alignment);
GSROOT_DLL_EXPORT void*		CCALL GS_aligned_malloc (size_t size, size_t alignment);
GSROOT_DLL_EXPORT void		CCALL GS_aligned_free (void *userData);
GSROOT_DLL_EXPORT void*		CCALL GS_aligned_realloc (void* userData, size_t size, size_t alignment);
_Check_return_
GSROOT_DLL_EXPORT size_t	CCALL GS_msize (_Pre_notnull_ void *userData);
#elif defined (macintosh) || defined (__linux__)
GSROOT_DLL_EXPORT size_t	CCALL GS_msize (void *userData);
#endif

#if defined (WINDOWS)
_Check_return_
GSROOT_DLL_EXPORT int				CCALL GS_heapchk (void);
#endif

GSROOT_DLL_EXPORT char*				CCALL GS_strdup (const char* str);

#if defined (WINDOWS)
GSROOT_DLL_EXPORT wchar_t*			CCALL GS_wcsdup (const wchar_t* str);
GSROOT_DLL_EXPORT unsigned char*	CCALL GS_mbsdup (const unsigned char* str);
GSROOT_DLL_EXPORT char*				CCALL GS_getcwd (char* buffer, int maxlen);
GSROOT_DLL_EXPORT wchar_t*			CCALL GS_wgetcwd (wchar_t* buffer, int maxlen);
GSROOT_DLL_EXPORT char*				CCALL GS_fullpath (char* absPath, const char* relPath, size_t maxlen);
GSROOT_DLL_EXPORT wchar_t*			CCALL GS_wfullpath (wchar_t* absPath, const wchar_t* relPath, size_t maxlen);
GSROOT_DLL_EXPORT char*				CCALL GS_tempnam (const char* dir, const char* prefix);
GSROOT_DLL_EXPORT wchar_t*			CCALL GS_wtempnam (const wchar_t* dir, const wchar_t* prefix);
#elif defined (macintosh)
GSROOT_DLL_EXPORT char*				CCALL GS_getcwd (char* buf, size_t size);
#elif defined (__linux__)
GSROOT_DLL_EXPORT char*				CCALL GS_getcwd (char* buf, size_t size) __THROW __wur;
#endif

#if defined (macintosh) || defined (__linux__)
#if defined (__cplusplus)
namespace __cxxabiv1 {
GSROOT_DLL_EXPORT char*				CCALL GS_cxa_demangle (const char* mangledName, char* output, size_t* length, int* status);
}
#endif // #if defined (__cplusplus)
#endif // #if defined (macintosh) || defined (__linux))

#if defined (__cplusplus)
}
#endif


#if defined (__cplusplus)
namespace std {
inline void*		GS_calloc (size_t num, size_t size) { return ::GS_calloc (num, size); }
inline void*		GS_malloc (size_t size) { return ::GS_malloc (size); }
inline void			GS_free (void *userData) { return ::GS_free (userData); }
inline void*		GS_realloc (void *userData, size_t newSize) { return ::GS_realloc (userData, newSize); }
}
#endif


// --- Macro definitions -----------------------------------------------------------------------------------------------

#define	calloc(n, s)				GS_calloc(n, s)
#define	malloc(s)					GS_malloc(s)
#define	free(p)						GS_free(p)
#define	realloc(p, s)				GS_realloc(p, s)

#if defined (WINDOWS) && defined (DEBUVERS)
#define _calloc_dbg(n, s, t, f, l)	GS_calloc(n, s)
#define _malloc_dbg(s, t, f, l)		GS_malloc(s)
#define _free_dbg(p, t)				GS_free(p)
#define _realloc_dbg(p, s, t, f, l)	GS_realloc(p, s)
#endif

#if defined (WINDOWS)

// Windows specific "_offset" memory management functions are not implemented. They cause 
#if defined (__cplusplus)
// compile error on use
template<typename ReturnType, bool condition = false>
ReturnType GS_not_implemented_function ()
{
	static_assert(condition, "Not implemenmted!");
	return {};
}
#define GS_not_implemented_void_ptr_function GS_not_implemented_function<void*>
#define GS_not_implemented_size_t_function GS_not_implemented_function<size_t>
#else
// linker error on use
void* GS_not_implemented_void_ptr_function ();
size_t GS_not_implemented_size_t_function ();
#endif
#endif


#if defined (WINDOWS)
#define _recalloc(p, s1, s2)						GS_recalloc(p, s1, s2)
#define _aligned_recalloc(p, s1, s2, s3)			GS_aligned_recalloc(p, s1, s2, s3)
#define _aligned_offset_recalloc(p, s1, s2, s3, s4) GS_not_implemented_void_ptr_function()
#define _aligned_malloc(s1, s2)						GS_aligned_malloc(s1, s2)
#define _aligned_offset_malloc(s1, s2, s3)			GS_not_implemented_void_ptr_function()
#define _aligned_free(s)							GS_aligned_free(s)
#define _aligned_realloc(p, s1, s2)					GS_aligned_realloc(p, s1, s2)
#define _aligned_offset_realloc(p, s1, s2, s3)		GS_not_implemented_void_ptr_function()
#define	_msize(p)									GS_msize(p)
#define _aligned_msize(p, s1, s2)					GS_not_implemented_size_t_function()
#define	_heapchk									GS_heapchk
#endif

#define strdup(s)		GS_strdup(s)

#if defined (WINDOWS)
#define _strdup(s)			 GS_strdup(s)
#define _wcsdup(s)			 GS_wcsdup(s)
#define _mbsdup(s)			 GS_mbsdup(s)
#define _getcwd(s, i)		 GS_getcwd(s, i)
#define _wgetcwd(s, i)		 GS_wgetcwd(s, i)
#define _fullpath(s, cs, i)  GS_fullpath(s, cs, i)
#define _wfullpath(s, cs, i) GS_wfullpath(s, cs, i)
#define _tempnam(s1, s2)	 GS_tempnam(s1, s2)
#define _wtempnam(s1, s2)	 GS_wtempnam(s1, s2)
#elif defined (macintosh) || defined (__linux__)
#define getcwd(s, i)		 GS_getcwd(s, i)
#define __cxa_demangle		 GS_cxa_demangle
#endif

#endif // if !defined (GSMALLOC_HPP)
