
// *****************************************************************************
//
// Import/export macro declarations for JSON module
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef JSON_EXPORT_HPP
#define JSON_EXPORT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "PlatformDLLExport.hpp"


#if defined (JSON_EXPORTS)
#define	JSON_API		PLATFORM_DLL_EXPORT
#else
#define JSON_API		PLATFORM_DLL_IMPORT
#endif


#endif
