/*==========================================================================**
**									GSMSECTIONSExport.h						**
**																			**
**				DEFINITIONS FOR EXPORTATION FROM THE GSMSECTIONS MODULE		**
**==========================================================================*/

#ifndef	GSMSECTIONSEXPORT_H
#define	GSMSECTIONSEXPORT_H

#pragma once

#include "PlatformDLLExport.hpp" /* from GSRoot */

#if defined (GSMSECTIONS_DLL_COMPILE)
	#define GSMSECTIONS_DLL_EXPORT		extern "C"	PLATFORM_DLL_EXPORT
	#define GSMSECTIONS_CPP_DLL_EXPORT	PLATFORM_DLL_EXPORT
#else
	#define GSMSECTIONS_DLL_EXPORT		extern "C"	PLATFORM_DLL_IMPORT
	#define GSMSECTIONS_CPP_DLL_EXPORT	PLATFORM_DLL_IMPORT
#endif

#if	defined	(GSMSECTIONS_NOT_DLL)
	#define GSMSECTIONS_DLL_EXPORT
#else
	#if defined (WINDOWS)
		#define	GSMSECTIONS_CALL			__stdcall
	#else
		#define	GSMSECTIONS_CALL
	#endif
#endif


#endif
