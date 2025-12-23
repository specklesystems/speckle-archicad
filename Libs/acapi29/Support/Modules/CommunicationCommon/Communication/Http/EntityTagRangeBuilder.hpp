
// *****************************************************************************
//
// Declaration of EntityTagRangeBuilder class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_ENTITYTAGRANGEBUILDER_HPP
#define COMMUNICATION_HTTP_ENTITYTAGRANGEBUILDER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/EntityTagRange.hpp"



// --- EntityTagRangeBuilder class ---------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API EntityTagRangeBuilder {

// Data members:
private:
	EntityTagRange			m_entityTagRange;

// Operations:
public:
	EntityTagRangeBuilder&	WithEntityTag (const EntityTag& entityTag);

	EntityTagRangeBuilder&	Any ();

	EntityTagRange			Build ();

};

}
}

#endif // COMMUNICATION_HTTP_ENTITYTAGRANGEBUILDER_HPP