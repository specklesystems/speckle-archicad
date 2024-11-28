
// *****************************************************************************
//
// Declaration of ClientRequestFilterException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTREQUESTFILTEREXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTREQUESTFILTEREXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequestException.hpp"



// --- ClientRequestFilterException class --------------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientRequestFilterException, ClientRequestException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTREQUESTFILTEREXCEPTION_HPP