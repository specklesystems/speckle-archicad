
// *****************************************************************************
//
// Import/export macro declarations for JSONConversion module
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	MB
//
// *****************************************************************************

#ifndef JSON_CONVERSION_EXPORT_HPP
#define JSON_CONVERSION_EXPORT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "PlatformDLLExport.hpp"


#if defined (JSON_CONVERSION_EXPORTS)
#define	JSON_CONVERSION_API		PLATFORM_DLL_EXPORT
#else
#define JSON_CONVERSION_API		PLATFORM_DLL_IMPORT
#endif


#endif
