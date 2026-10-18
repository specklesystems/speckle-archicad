
// *****************************************************************************
//
// Declaration of ClientRequestException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTREQUESTEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTREQUESTEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientException.hpp"



// --- ClientRequestException class --------------------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientRequestException, ClientException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTREQUESTEXCEPTION_HPP