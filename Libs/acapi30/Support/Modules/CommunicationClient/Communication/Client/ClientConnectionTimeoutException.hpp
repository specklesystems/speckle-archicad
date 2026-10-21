
// *****************************************************************************
//
// Declaration of ClientConnectionTimeoutException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONTIMEOUTEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONTIMEOUTEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnectionException.hpp"



// --- ClientConnectionTimeoutException class ----------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientConnectionTimeoutException, ClientConnectionException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONTIMEOUTEXCEPTION_HPP