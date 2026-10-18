
// *****************************************************************************
//
// Declaration of EntityTagRange related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_ENTITYTAGRANGEUTILS_HPP
#define COMMUNICATION_HTTP_ENTITYTAGRANGEUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/EntityTagRange.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Http {

// -----------------------------------------------------------------------------
// CheckEntityTagRange
// -----------------------------------------------------------------------------

inline void		CheckEntityTagRange (const EntityTagRange& entityTagRange, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (entityTagRange.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid entity tag range: range is not valid.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_HTTP_ENTITYTAGRANGEUTILS_HPP