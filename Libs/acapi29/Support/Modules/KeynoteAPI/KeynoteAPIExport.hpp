#ifndef KEYNOTEAPI_EXPORT
#define KEYNOTEAPI_EXPORT

#pragma once

#include "PlatformDLLExport.hpp"

#if defined (KEYNOTEAPI_DLL_COMPILE)
	#define KEYNOTEAPI_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define KEYNOTEAPI_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
