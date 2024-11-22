
// *****************************************************************************
//
// Declaration of Socket class
//
// Module:			Network
// Namespace:		Network::Socket
// Contact person:	SN
//
// *****************************************************************************

#ifndef NETWORK_SOCKET_SOCKET_HPP
#define NETWORK_SOCKET_SOCKET_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "InternetAddress.hpp"
#include "SocketAddressAlreadyUsedException.hpp"
#include "SocketConnectException.hpp"
#include "SocketConnectionRefusedException.hpp"
#include "SocketTimeoutException.hpp"

	// from GSRoot
#include "IBinaryChannel.hpp"
#include "OBinaryChannel.hpp"
#include "Ref.hpp"



// --- Forward declarations ----------------------------------------------------

namespace Network {
namespace Socket {

class SocketImpl; typedef GS::Ref<SocketImpl, GS::AtomicCounter> SocketImplRef;

}
}



// --- Socket class ------------------------------------------------------------

namespace Network {
namespace Socket {

class NETWORK_DLL_EXPORT Socket {
	
// Friend classes:
friend class ServerSocket;

// Data members:
private:
	SocketImplRef			m_impl;

// Construction / destruction:
private:
	explicit Socket (const SocketImplRef& impl);
public:
			 Socket (const InternetAddress& address, GS::UShort port);
			 Socket (const InternetAddress& address, GS::UShort port, const InternetAddress& localAddress, GS::UShort localPort);
			 Socket (const char* hostName, GS::UShort port);
			 Socket (const char* hostName, GS::UShort port, const InternetAddress& localAddress, GS::UShort localPort);
			 Socket (const Socket& rhs);
			~Socket ();

// Operator overloading:
public:
	Socket&					operator = (const Socket& rhs);

	bool					operator == (const Socket& rhs) const;
	bool					operator != (const Socket& rhs) const;

// Operations:
public:
	InternetAddressRef		GetLocalInternetAddress () const;
	GS::UShort				GetLocalPort () const;

	InternetAddressRef		GetInternetAddress () const;
	GS::UShort				GetPort () const;

	GS::OBinaryChannel&		GetOutputChannel () const;
	GS::IBinaryChannel&		GetInputChannel () const;

	void					SetTimeout (GS::ULong timeout);
	GS::ULong				GetTimeout () const;

	void					SetReceiveBufferSize (GS::USize receiveBufferSize);
	GS::USize				GetReceiveBufferSize () const;

	void					SetSendBufferSize (GS::USize sendBufferSize);
	GS::USize				GetSendBufferSize () const;

	void					SetTrafficClass (GS::UInt8 trafficClass);
	GS::UInt8				GetTrafficClass () const;

	void					SetTCPNoDelay (bool tpcNoDelay);
	bool					GetTCPNoDelay () const;

	void					SetKeepAlive (bool keepAlive);
	bool					GetKeepAlive () const;

	void					SetLinger (int linger);
	int						GetLinger () const;

	void					Close ();
};

typedef	GS::Ref<Socket, GS::AtomicCounter>	SocketRef;

////////////////////////////////////////////////////////////////////////////////
// Socket inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		Socket::operator != (const Socket& rhs) const
{
	return !operator == (rhs);
}

}
}

#endif // NETWORK_SOCKET_SOCKET_HPP
