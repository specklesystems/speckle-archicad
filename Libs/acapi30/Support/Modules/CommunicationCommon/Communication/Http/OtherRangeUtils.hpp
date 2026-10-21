
// *****************************************************************************
//
// Declaration of OtherRange related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_OTHERRANGEUTILS_HPP
#define COMMUNICATION_HTTP_OTHERRANGEUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/OtherRange.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Http {

// -----------------------------------------------------------------------------
// CheckOtherRange
// -----------------------------------------------------------------------------

inline void		CheckOtherRange (const OtherRange& otherRange, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (otherRange.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid other range: range is not valid.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_HTTP_OTHERRANGEUTILS_HPP