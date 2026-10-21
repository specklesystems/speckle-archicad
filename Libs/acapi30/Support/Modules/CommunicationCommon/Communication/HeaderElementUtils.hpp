
// *****************************************************************************
//
// Declaration of HeaderElement related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HEADERELEMENTUTILS_HPP
#define COMMUNICATION_HEADERELEMENTUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/HeaderElement.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {

// -----------------------------------------------------------------------------
// CheckHeaderElementName
// -----------------------------------------------------------------------------

inline void		CheckHeaderElementName (const GS::UniString& headerElementName, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (headerElementName.IsEmpty ())) {
		throw GS::IllegalArgumentException ("Invalid header element name: name is empty.", sourceFile, sourceLine);
	}
}

// -----------------------------------------------------------------------------
// CheckHeaderElements
// -----------------------------------------------------------------------------

inline void		CheckHeaderElements (const GS::PagedArray<HeaderElement>& headerElements, const char* sourceFile, GS::UInt32 sourceLine)
{
	for (const HeaderElement& headerElement : headerElements) {
		if (DBERROR (headerElement.IsValid () == false)) {
			throw GS::IllegalArgumentException ("Invalid header element list: list contains invalid header element.", sourceFile, sourceLine);
		}
	}
}

// -----------------------------------------------------------------------------
// CheckHeaderElement
// -----------------------------------------------------------------------------

inline void		CheckHeaderElement (const HeaderElement& headerElement, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (headerElement.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid header element: element is not valid.", sourceFile, sourceLine);
	}
}

}

#endif // COMMUNICATION_HEADERELEMENTUTILS_HPP