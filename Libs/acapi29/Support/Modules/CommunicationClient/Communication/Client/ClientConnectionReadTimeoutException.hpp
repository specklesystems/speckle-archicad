
// *****************************************************************************
//
// Declaration of ClientConnectionReadTimeoutException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONREADTIMEOUTEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONREADTIMEOUTEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnectionTimeoutException.hpp"



// --- ClientConnectionReadTimeoutException class ------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientConnectionReadTimeoutException, ClientConnectionTimeoutException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif //  COMMUNICATION_CLIENT_CLIENTCONNECTIONREADTIMEOUTEXCEPTION_HPP