
// *****************************************************************************
//
// Declaration of ClientConnectionConnectTimeoutException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONCONNECTTIMEOUTEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONCONNECTTIMEOUTEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnectionTimeoutException.hpp"



// --- ClientConnectionConnectTimeoutException class ---------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientConnectionConnectTimeoutException, ClientConnectionTimeoutException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONCONNECTTIMEOUTEXCEPTION_HPP