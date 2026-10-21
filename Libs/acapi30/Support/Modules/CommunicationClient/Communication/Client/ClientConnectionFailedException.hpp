
// *****************************************************************************
//
// Declaration of ClientConnectionFailedException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONFAILEDEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONFAILEDEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnectionException.hpp"



// --- ClientConnectionFailedException class -----------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientConnectionFailedException, ClientConnectionException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONFAILEDEXCEPTION_HPP