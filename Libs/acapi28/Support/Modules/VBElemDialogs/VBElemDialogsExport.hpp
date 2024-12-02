// *********************************************************************************************************************
// VBElemDialogs compiler environment
//
// Module:			VBElemDialogs
// Namespace:		-
// Contact person:	PT
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (VBELEMDIALOGSEXPORT_H)
#define VBELEMDIALOGSEXPORT_H

#pragma once


// --- Export/Import directives ----------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"

#if defined (VBELEMDIALOGS_NOT_DLL)
	#define VBELEMDIALOGS_DLL_EXPORT
#else
	#if defined (VBELEMDIALOGS_DLL_COMPILE)
		#define VBELEMDIALOGS_DLL_EXPORT		PLATFORM_DLL_EXPORT
	#else
		#define VBELEMDIALOGS_DLL_EXPORT		PLATFORM_DLL_IMPORT
	#endif
#endif

#endif
