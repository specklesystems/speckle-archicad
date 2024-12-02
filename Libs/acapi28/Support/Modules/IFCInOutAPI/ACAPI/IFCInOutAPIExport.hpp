#ifndef IFCINOUTAPI_EXPORT
#define IFCINOUTAPI_EXPORT

#pragma once

#include "PlatformDLLExport.hpp"

#if defined (IFCINOUTAPI_DLL_COMPILE)
	#define IFCINOUTAPI_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define IFCINOUTAPI_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
