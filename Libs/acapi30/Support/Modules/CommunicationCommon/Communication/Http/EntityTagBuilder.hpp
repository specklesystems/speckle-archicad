
// *****************************************************************************
//
// Declaration of EntityTagBuilder class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_ENTITYTAGBUILDER_HPP
#define COMMUNICATION_HTTP_ENTITYTAGBUILDER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/EntityTag.hpp"
#include "Communication/Http/EntityTagBuilderException.hpp"



// --- EntityTagBuilder class --------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API EntityTagBuilder {

// Data members:
private:
	EntityTag			m_entityTag;

// Operations:
public:
	EntityTagBuilder&	WithTag (const GS::UniString& tag);
	
	EntityTagBuilder&	Strong ();
	EntityTagBuilder&	Weak ();

	EntityTag			Build ();

};

}
}

#endif // COMMUNICATION_HTTP_ENTITYTAGBUILDER_HPP