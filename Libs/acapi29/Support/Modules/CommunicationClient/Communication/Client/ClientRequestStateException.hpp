
// *****************************************************************************
//
// Declaration of ClientRequestStateException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTREQUESTSTATEEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTREQUESTSTATEEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequestException.hpp"



// --- ClientRequestStateException class ---------------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientRequestStateException, ClientRequestException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTREQUESTSTATEEXCEPTION_HPP