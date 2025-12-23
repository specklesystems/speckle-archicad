/*==========================================================================**
**							PatternExport.h									**
**																			**
**		DEFINITIONS FOR EXPORTATION FROM THE PATTERN MODULE					**
**==========================================================================*/

#ifndef	PATTERNEXPORT_H
#define	PATTERNEXPORT_H


#pragma once

#include "PlatformDLLExport.hpp"

#if	defined	(PATTERN_NOT_DLL)
	#define PATTERN_DLL_EXPORT
#else
	#if defined (PATTERN_DLL_COMPILE)
		#define PATTERN_DLL_EXPORT				PLATFORM_DLL_EXPORT
	#else
		#define PATTERN_DLL_EXPORT				PLATFORM_DLL_IMPORT
	#endif
#endif

#endif
