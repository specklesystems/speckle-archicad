
// *****************************************************************************
//
// Declaration of EntityTag related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_ENTITYTAGUTILS_HPP
#define COMMUNICATION_HTTP_ENTITYTAGUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/EntityTag.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Http {

// -----------------------------------------------------------------------------
// CheckEntityTag
// -----------------------------------------------------------------------------

inline void		CheckEntityTag (const EntityTag& entityTag, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (entityTag.IsValid () == false)) {
		throw GS::IllegalArgumentException ("Invalid entity tag: tag is not valid.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_HTTP_ENTITYTAGUTILS_HPP