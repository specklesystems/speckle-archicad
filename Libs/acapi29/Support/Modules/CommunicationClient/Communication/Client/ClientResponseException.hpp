
// *****************************************************************************
//
// Declaration of ClientResponseException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTRESPONSEEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTRESPONSEEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientException.hpp"



// --- ClientResponseException class -------------------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientResponseException, ClientException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTRESPONSEEXCEPTION_HPP