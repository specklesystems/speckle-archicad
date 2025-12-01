
// *****************************************************************************
//
// Declaration of StatusLine related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_STATUSLINEUTILS_HPP
#define COMMUNICATION_HTTP_STATUSLINEUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/StatusLine.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Http {

// -----------------------------------------------------------------------------
// CheckStatusLine
// -----------------------------------------------------------------------------

inline void		CheckStatusLine (const StatusLine& statusLine, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (statusLine.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid status line: status line is not valid.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_HTTP_STATUSLINEUTILS_HPP