
// *****************************************************************************
//
// Declaration of Message related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_MESSAGEUTILS_HPP
#define COMMUNICATION_MESSAGEUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

	// from GSRoot
#include "UniString.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {

// -----------------------------------------------------------------------------
// CheckMessageId
// -----------------------------------------------------------------------------

inline void		CheckMessageId (const GS::UniString& messageId, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (messageId.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid message id: id is empty.", sourceFile, sourceLine);
	}
}

}

#endif // COMMUNICATION_MESSAGEUTILS_HPP