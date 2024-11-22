// *********************************************************************************************************************
// Description:		ServerSocket
//
// Module:			Network
// Namespace:		Network::Socket
// Contact person:	MIJ
//
// SG compatible
// *********************************************************************************************************************

#ifndef NETWORK_SOCKET_SERVERSOCKET_HPP
#define NETWORK_SOCKET_SERVERSOCKET_HPP

#pragma once

#include "Socket.hpp"

namespace Network {
namespace Socket {

class NETWORK_DLL_EXPORT ServerSocket {

private:
	SocketImplRef	mImpl;

public:
	ServerSocket (UShort port, ULong backlog = 50, const InternetAddress& bindAddress = InternetAddress::Any);
	ServerSocket (const ServerSocket& source);
	~ServerSocket ();

public:
	const ServerSocket&	operator= (const ServerSocket& source);

	bool				operator== (const ServerSocket& other) const;
	bool				operator!= (const ServerSocket& other) const;

public:
	InternetAddressRef		GetInetAddress () const;
	unsigned short			GetLocalPort () const;

	UInt32			GetTimeout () const;
	void					SetTimeout (ULong timeout);

	bool					IsPending () const;
	SocketRef				Accept ();
	SocketRef				Accept (ULong timeout);

	void					Close ();

};

typedef GS::Ref <ServerSocket>	ServerSocketRef;

inline bool		ServerSocket::operator!= (const ServerSocket& other) const
{
	return !operator== (other);
}

}
}

#endif // NETWORK_SOCKET_SERVERSOCKET_HPP
