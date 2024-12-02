
// *****************************************************************************
//
// Import/export macro declarations for TWClient module
//
// Module:			TWClient
// Namespace:		-
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef TWCLIENTEXPORT_HPP
#define TWCLIENTEXPORT_HPP

#pragma once


// --- Includes -------------------------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"


// --- Module export defines ------------------------------------------------------------------------------------------

#if defined (TW_CLIENT_DLL_COMPILE)
	#define TWCLIENT_API		PLATFORM_DLL_EXPORT
#else
	#define TWCLIENT_API		PLATFORM_DLL_IMPORT
#endif

#endif
