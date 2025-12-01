
// *****************************************************************************
//
// Declaration of UnknownHostException class
//
// Module:			Network
// Namespace:		Network::Socket
// Contact person:	SN
//
// *****************************************************************************

#ifndef NETWORK_SOCKET_UNKNOWNHOSTEXCEPTION_HPP
#define NETWORK_SOCKET_UNKNOWNHOSTEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "NetworkBase.hpp"

	// from GSRoot
#include "ChannelExceptions.hpp"



// --- UnknownHostException class ----------------------------------------------

namespace Network {
namespace Socket {

DECLARE_EXCEPTION_CLASS (UnknownHostException, GS::IOException, GS::Error, NETWORK_DLL_EXPORT)

}
}

#endif // NETWORK_SOCKET_UNKNOWNHOSTEXCEPTION_HPP
