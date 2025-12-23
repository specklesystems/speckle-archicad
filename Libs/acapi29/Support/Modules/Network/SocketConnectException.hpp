
// *****************************************************************************
//
// Declaration of SocketConnectException class
//
// Module:			Network
// Namespace:		Network::Socket
// Contact person:	SN
//
// *****************************************************************************

#ifndef NETWORK_SOCKET_SOCKETCONNECTEXCEPTION_HPP
#define NETWORK_SOCKET_SOCKETCONNECTEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "SocketException.hpp"



// --- SocketConnectException class --------------------------------------------

namespace Network {
namespace Socket {

DECLARE_EXCEPTION_CLASS (SocketConnectException, SocketException, GS::Error, NETWORK_DLL_EXPORT)

}
}

#endif // NETWORK_SOCKET_SOCKETCONNECTEXCEPTION_HPP
