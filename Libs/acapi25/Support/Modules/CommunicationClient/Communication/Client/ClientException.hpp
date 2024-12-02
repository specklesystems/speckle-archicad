
// *****************************************************************************
//
// Declaration of ClientException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/CommunicationClientExport.hpp"

	// from CommunicationCommon
#include "Communication/CommunicationException.hpp"



// --- ClientException class ---------------------------------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientException, CommunicationException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTEXCEPTION_HPP