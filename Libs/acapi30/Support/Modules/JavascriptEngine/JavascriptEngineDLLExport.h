#ifndef JE_DLL_EXPORT_H
#define JE_DLL_EXPORT_H

#pragma once

#include "PlatformDLLExport.hpp"


#if defined (JAVASCRIPT_ENGINE_DLL_COMPILE)
#define JAVASCRIPT_ENGINE_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
#define JAVASCRIPT_ENGINE_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
