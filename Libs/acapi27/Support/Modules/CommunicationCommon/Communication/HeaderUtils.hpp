
// *****************************************************************************
//
// Declaration of Header related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HEADERUTILS_HPP
#define COMMUNICATION_HEADERUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Header.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {

// -----------------------------------------------------------------------------
// CheckHeaderName
// -----------------------------------------------------------------------------

inline void		CheckHeaderName (const GS::UniString& headerName, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (headerName.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid header name: name is empty.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckHeader
// -----------------------------------------------------------------------------

inline void		CheckHeader (const Header& header, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (header.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid header: header is not valid.", sourceFile, sourceLine);
	}
}

}

#endif // COMMUNICATION_HEADERUTILS_HPP