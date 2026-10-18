
// *****************************************************************************
//
// Declaration of ClientConnectionException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientException.hpp"



// --- ClientConnectionException class -----------------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientConnectionException, ClientException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONEXCEPTION_HPP