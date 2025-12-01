
// *****************************************************************************
//
// Declaration of EntityTagBuilderException class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_ENTITYTAGBUILDEREXCEPTION_HPP
#define COMMUNICATION_HTTP_ENTITYTAGBUILDEREXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "GSException.hpp"



// --- EntityTagBuilderException class -----------------------------------------

namespace Communication {
namespace Http {

DECLARE_EXCEPTION_CLASS (EntityTagBuilderException, GS::GeneralException, GS::Error, COMMUNICATIONCOMMON_API);

}
}

#endif // COMMUNICATION_HTTP_ENTITYTAGBUILDEREXCEPTION_HPP