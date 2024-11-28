
// *****************************************************************************
//
// Declaration ClientConnectionAddressResolutionException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONADDRESSRESOLUTIONEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONADDRESSRESOLUTIONEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnectionException.hpp"



// --- ClientConnectionAddressResolutionException class ------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientConnectionAddressResolutionException, ClientConnectionException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONADDRESSRESOLUTIONEXCEPTION_HPP