// *****************************************************************************
//
// Export/import macros for the HTTPClient module
//
// Contact person: EP
//
// *****************************************************************************

#ifndef HTTPCLIENTEXPORT_HPP
#define HTTPCLIENTEXPORT_HPP

#pragma once

// from GSRoot
#include "PlatformDLLExport.hpp"

#ifdef HTTPCLIENT_DLL_COMPILE
#define HTTPCLIENT_EXPORTED PLATFORM_DLL_EXPORT
#else
#define HTTPCLIENT_EXPORTED PLATFORM_DLL_IMPORT
#endif

#endif	// #ifndef HTTPCLIENTEXPORT_HPP