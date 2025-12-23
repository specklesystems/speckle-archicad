
// *****************************************************************************
//
// Declaration of ProtocolVersion related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_PROTOCOLVERSIONUTILS_HPP
#define COMMUNICATION_HTTP_PROTOCOLVERSIONUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ProtocolVersion.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Http {

// -----------------------------------------------------------------------------
// CheckProtocolVersion
// -----------------------------------------------------------------------------

inline void		CheckProtocolVersion (const ProtocolVersion& protocolVersion, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (protocolVersion.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid protocol version: protocol version is not valid.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_HTTP_PROTOCOLVERSIONUTILS_HPP