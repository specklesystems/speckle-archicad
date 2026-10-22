
// *****************************************************************************
//
// Import/export macro declarations for HTTP module
//
// Module:			HTTP
// Namespace:		HTTP
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_EXPORT_HPP
#define HTTP_EXPORT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "PlatformDLLExport.hpp"


#if defined (HTTP_EXPORTS)
#define	HTTP_API		PLATFORM_DLL_EXPORT
#elif defined (HTTP_STATIC_COMPILE)
#define	HTTP_API
#else
#define HTTP_API		PLATFORM_DLL_IMPORT
#endif


#endif
