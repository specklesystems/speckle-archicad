
// *****************************************************************************
//
// Declaration of SocketAddressAlreadyUsedException class
//
// Module:			Network
// Namespace:		Network::Socket
// Contact person:	SN
//
// *****************************************************************************

#ifndef NETWORK_SOCKET_SOCKETADDRESSALREADYUSEDEXCEPTION_HPP
#define NETWORK_SOCKET_SOCKETADDRESSALREADYUSEDEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "SocketException.hpp"



// --- SocketAddressAlreadyUsedException class ---------------------------------

namespace Network {
namespace Socket {

DECLARE_EXCEPTION_CLASS (SocketAddressAlreadyUsedException, SocketException, GS::Error, NETWORK_DLL_EXPORT)

}
}

#endif // NETWORK_SOCKET_SOCKETADDRESSALREADYUSEDEXCEPTION_HPP
