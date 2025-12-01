
// *****************************************************************************
//
// Declaration of SocketConnectionRefusedException class
//
// Module:			Network
// Namespace:		Network::Socket
// Contact person:	SN
//
// *****************************************************************************

#ifndef NETWORK_SOCKET_SOCKETCONNECTIONREFUSEDEXCEPTION_HPP
#define NETWORK_SOCKET_SOCKETCONNECTIONREFUSEDEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "SocketConnectException.hpp"



// --- SocketConnectionRefusedException class ----------------------------------

namespace Network {
namespace Socket {

DECLARE_EXCEPTION_CLASS (SocketConnectionRefusedException, SocketConnectException, GS::Error, NETWORK_DLL_EXPORT);

}
}

#endif // NETWORK_SOCKET_SOCKETCONNECTIONREFUSEDEXCEPTION_HPP