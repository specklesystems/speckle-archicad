
// *****************************************************************************
//
// Import/export macro declarations for CommunicationClient module
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_COMMUNICATIONCLIENTEXPORT_HPP
#define COMMUNICATION_CLIENT_COMMUNICATIONCLIENTEXPORT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

	// from GSRoot
#include "PlatformDLLExport.hpp"



// --- Macro definitions -------------------------------------------------------

#if defined (COMMUNICATIONCLIENT_EXPORTS)
#define COMMUNICATIONCLIENT_API		PLATFORM_DLL_EXPORT
#else
#define COMMUNICATIONCLIENT_API		PLATFORM_DLL_IMPORT
#endif

#endif // COMMUNICATION_CLIENT_COMMUNICATIONCLIENTEXPORT_HPP