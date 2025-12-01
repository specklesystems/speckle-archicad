/*==========================================================================**
**							GSUtilsPrivExp.h								**
**																			**
**		DEFINITIONS FOR PRIVATE EXPORTATION FROM THE GSUTILS MODULE			**
**==========================================================================*/

#ifndef	GSUTILSPRIVEXP_H
#define	GSUTILSPRIVEXP_H

#pragma once

// from GSRoot
#include "PlatformDLLExport.hpp"

#if defined (GSUTILS_DLL_COMPILE)
	#define GSUTILS_PRIVATE_EXPORT	PLATFORM_DLL_EXPORT
#elif defined (GSUTILS_STATIC_COMPILE)
	#define GSUTILS_PRIVATE_EXPORT
#else
	#define GSUTILS_PRIVATE_EXPORT	PLATFORM_DLL_IMPORT
#endif
#define GSU_PRIV

#endif
