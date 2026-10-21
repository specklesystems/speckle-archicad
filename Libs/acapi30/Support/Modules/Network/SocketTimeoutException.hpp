
// *****************************************************************************
//
// Declaration of SocketTimeoutException class
//
// Module:			Network
// Namespace:		Network::Socket
// Contact person:	SN
//
// *****************************************************************************

#ifndef NETWORK_SOCKET_SOCKETTIMEOUTEXCEPTION_HPP
#define NETWORK_SOCKET_SOCKETTIMEOUTEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "SocketException.hpp"



// --- SocketTimeoutException class --------------------------------------------

namespace Network {
namespace Socket {

DECLARE_EXCEPTION_CLASS (SocketTimeoutException, SocketException, GS::Error, NETWORK_DLL_EXPORT)

}
}

#endif // NETWORK_SOCKET_SOCKETTIMEOUTEXCEPTION_HPP
