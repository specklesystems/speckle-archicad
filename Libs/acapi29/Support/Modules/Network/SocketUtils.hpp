
// *****************************************************************************
//
// Declaration of SocketUtils class
//
// Module:			Network
// Namespace:		Network::Socket
// Contact person:	SN
//
// *****************************************************************************

#ifndef NETWORK_SOCKET_SOCKETUTILS_HPP
#define NETWORK_SOCKET_SOCKETUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "SocketException.hpp"



// --- SocketUtils class -------------------------------------------------------

namespace Network {
namespace Socket {

class NETWORK_DLL_EXPORT SocketUtils {

// Static operations:
public:
	static bool			FindFreePort (GS::UShort startPort, GS::UShort endPort, GS::UShort& portFound);

	static GS::UShort	FindFreePort (GS::UShort startPort, GS::UShort endPort);

};

}
}

#endif // NETWORK_SOCKET_SOCKETUTILS_HPP