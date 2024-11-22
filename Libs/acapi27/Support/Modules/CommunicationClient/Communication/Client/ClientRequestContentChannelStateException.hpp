
// *****************************************************************************
//
// Declaration of ClientRequestContentChannelStateException class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTREQUESTCONTENTCHANNELSTATEEXCEPTION_HPP
#define COMMUNICATION_CLIENT_CLIENTREQUESTCONTENTCHANNELSTATEEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequestStateException.hpp"



// --- ClientRequestContentChannelStateException class -------------------------

namespace Communication {
namespace Client {

DECLARE_EXCEPTION_CLASS (ClientRequestContentChannelStateException, ClientRequestStateException, GS::Error, COMMUNICATIONCLIENT_API);

}
}

#endif // COMMUNICATION_CLIENT_CLIENTREQUESTCONTENTCHANNELSTATEEXCEPTION_HPP