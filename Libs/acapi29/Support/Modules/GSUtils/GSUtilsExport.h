/*==========================================================================**
**								GSUtilsExport.h								**
**																			**
**			DEFINITIONS FOR EXPORTATION FROM THE GSUTILS MODULE				**
**==========================================================================*/

#ifndef	GSUTILSEXPORT_H
#define	GSUTILSEXPORT_H

#pragma once

// from GSRoot
#include "PlatformDLLExport.hpp"

#if defined (WINDOWS)
	#define	GSU_CALL				__stdcall
#else
	#define	GSU_CALL
#endif

#if defined (GSUTILS_DLL_COMPILE)
	#define GSUTILS_DLL_EXPORT		extern "C" PLATFORM_DLL_EXPORT
#elif defined (GSUTILS_STATIC_COMPILE)
	#define GSUTILS_DLL_EXPORT		extern "C"
#else
	#define GSUTILS_DLL_EXPORT		extern "C" PLATFORM_DLL_IMPORT
#endif

#if defined (GSUTILS_DLL_COMPILE)
	#define GSUTILS_DLL_EXPORT_CPP		PLATFORM_DLL_EXPORT
#elif defined (GSUTILS_STATIC_COMPILE)
	#define GSUTILS_DLL_EXPORT_CPP
#else
	#define GSUTILS_DLL_EXPORT_CPP		PLATFORM_DLL_IMPORT
#endif

#endif
