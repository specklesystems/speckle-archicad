
// *****************************************************************************
//
// Declaration of ClientResponseStateException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTRESPONSESTATEEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTRESPONSESTATEEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientResponseException.hpp"



// --- ClientResponseStateException class --------------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientResponseStateException, ClientResponseException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTRESPONSESTATEEXCEPTION_HPP