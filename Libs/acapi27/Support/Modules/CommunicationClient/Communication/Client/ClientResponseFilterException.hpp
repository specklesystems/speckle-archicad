
// *****************************************************************************
//
// Declaration of ClientResponseFilterException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTRESPONSEFILTEREXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTRESPONSEFILTEREXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientResponseException.hpp"



// --- ClientResponseFilterException class -------------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientResponseFilterException, ClientResponseException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTRESPONSEFILTEREXCEPTION_HPP