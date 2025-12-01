
// *****************************************************************************
//
// Declaration of Property related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_PROPERTYUTILS_HPP
#define COMMUNICATION_PROPERTYUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

	// from GSRoot
#include "UniString.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {

// -----------------------------------------------------------------------------
// CheckPropertyName
// -----------------------------------------------------------------------------

inline void		CheckPropertyName (const GS::UniString& propertyName, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (propertyName.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid property name: name is empty.", sourceFile, sourceLine);
	}
}

}

#endif // COMMUNICATION_PROPERTYUTILS_HPP