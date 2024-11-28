/*==========================================================================**
**									GDLExport.h								**
**																			**
**				DEFINITIONS FOR EXPORTATION FROM THE GDL MODULE				**
**==========================================================================*/

#ifndef	GDLEXPORT_H
#define	GDLEXPORT_H

#pragma once

#include "PlatformDLLExport.hpp" /* from GSRoot */

#if defined (GDL_DLL_COMPILE)
	#define GDL_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define GDL_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#if defined (WINDOWS)
	#define	GDL_CALL			__stdcall
#else
	#define	GDL_CALL
#endif

#if defined (macintosh)
	#define	__ACGDEXPORT
	#define	__GDLEXT_CALL
#endif

#if defined	(WINDOWS)
	#if !defined (__GDLEXT_CALL)
		#define	__GDLEXT_CALL			__cdecl
	#endif
	#if defined	(COMP_API_DLL) || defined (COMP_API_VBDLL)
		#define	__ACGDEXPORT		PLATFORM_DLL_EXPORT
	#elif defined (USE_API_DLL) || defined (COMP_API_LIB)
		#define	__ACGDEXPORT		PLATFORM_DLL_IMPORT
	#else
		#define	__ACGDEXPORT
	#endif
#endif

#ifndef GPU_CALL
	#if	defined	(PlotMaker)
		#define	GPU_CALL
	#else
		#if defined (WINDOWS)
			#define	GPU_CALL				__stdcall
		#else
			#define	GPU_CALL
		#endif
	#endif
#endif

#endif
