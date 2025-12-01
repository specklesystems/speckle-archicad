
// *****************************************************************************
//
// Declaration of ClientConnectionStateException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONSTATEEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONSTATEEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnectionException.hpp"



// --- ClientConnectionStateException class ------------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientConnectionStateException, ClientConnectionException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONSTATEEXCEPTION_HPP