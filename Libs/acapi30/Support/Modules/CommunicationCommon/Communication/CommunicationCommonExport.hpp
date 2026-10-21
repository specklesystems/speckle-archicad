
// *****************************************************************************
//
// Import/export macro declarations for CommunicationCommon module
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_COMMUNICATIONCOMMONEXPORT_HPP
#define COMMUNICATION_COMMUNICATIONCOMMONEXPORT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

	// from GSRoot
#include "PlatformDLLExport.hpp"



// --- Macro definitions -------------------------------------------------------

#if defined (COMMUNICATIONCOMMON_EXPORTS)
#define COMMUNICATIONCOMMON_API		PLATFORM_DLL_EXPORT
#else
#define COMMUNICATIONCOMMON_API		PLATFORM_DLL_IMPORT
#endif

#endif // COMMUNICATION_COMMUNICATIONCOMMONEXPORT_HPP