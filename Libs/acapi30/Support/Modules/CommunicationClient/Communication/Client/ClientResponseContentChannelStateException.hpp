
// *****************************************************************************
//
// Declaration of ClientResponseContentChannelStateException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTRESPONSECONTENTCHANNELSTATEEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTRESPONSECONTENTCHANNELSTATEEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientResponseStateException.hpp"



// --- ClientResponseContentChannelStateException class ------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientResponseContentChannelStateException, ClientResponseStateException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTRESPONSECONTENTCHANNELSTATEEXCEPTION_HPP