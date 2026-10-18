
// *****************************************************************************
//
// Declaration of ProtocolVersionsNotComparableException class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_PROTOCOLVERSIONSNOTCOMPARABLEEXCEPTION_HPP
#define COMMUNICATION_HTTP_PROTOCOLVERSIONSNOTCOMPARABLEEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationException.hpp"



// --- ProtocolVersionsNotComparableException class ----------------------------

namespace Communication {
namespace Http {

DECLARE_EXCEPTION_CLASS (ProtocolVersionsNotComparableException, CommunicationException, GS::Error, COMMUNICATIONCOMMON_API);

}
}

#endif // COMMUNICATION_HTTP_PROTOCOLVERSIONSNOTCOMPARABLEEXCEPTION_HPP