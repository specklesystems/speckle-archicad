
// *****************************************************************************
//
// Declaration of SocketException class
//
// Module:			Network
// Namespace:		Network::Socket
// Contact person:	SN
//
// *****************************************************************************

#ifndef NETWORK_SOCKET_SOCKETEXCEPTION_HPP
#define NETWORK_SOCKET_SOCKETEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "NetworkBase.hpp"

	// from GSRoot
#include "ChannelExceptions.hpp"



// --- SocketException class ---------------------------------------------------

namespace Network {
namespace Socket {

DECLARE_EXCEPTION_CLASS (SocketException, GS::IOException, GS::Error, NETWORK_DLL_EXPORT)

}
}

#endif // NETWORK_SOCKET_SOCKETEXCEPTION_HPP
