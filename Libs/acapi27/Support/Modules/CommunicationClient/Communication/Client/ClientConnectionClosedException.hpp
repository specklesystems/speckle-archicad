
// *****************************************************************************
//
// Declaration of ClientConnectionClosedException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONCLOSEDEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONCLOSEDEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnectionException.hpp"



// --- ClientConnectionClosedException class -----------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientConnectionClosedException, ClientConnectionException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONCLOSEDEXCEPTION_HPP