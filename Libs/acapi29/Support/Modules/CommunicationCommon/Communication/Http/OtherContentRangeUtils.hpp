
// *****************************************************************************
//
// Declaration of OtherContentRange related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_OTHERCONTENTRANGEUTILS_HPP
#define COMMUNICATION_HTTP_OTHERCONTENTRANGEUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/OtherContentRange.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Http {

// -----------------------------------------------------------------------------
// CheckOtherContentRange
// -----------------------------------------------------------------------------

inline void		CheckOtherContentRange (const OtherContentRange& otherContentRange, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (otherContentRange.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid other content rannge: range is not valid.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_HTTP_OTHERCONTENTRANGEUTILS_HPP