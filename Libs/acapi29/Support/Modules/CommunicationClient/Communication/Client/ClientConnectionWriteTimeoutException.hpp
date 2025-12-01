
// *****************************************************************************
//
// Declaration ClientConnectionWriteTimeoutException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONWRITETIMEOUTEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONWRITETIMEOUTEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnectionTimeoutException.hpp"



// --- ClientConnectionWriteTimeoutException class -----------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientConnectionWriteTimeoutException, ClientConnectionTimeoutException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONWRITETIMEOUTEXCEPTION_HPP