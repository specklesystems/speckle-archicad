
// *****************************************************************************
//
// Declaration of ServerSecureChannel class
//
// Module:			SecureCommunication
// Namespace:		SecureCommunication::Server
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef SECURECOMMUNICATION_SERVER_SERVERSECURECHANNEL_HPP
#define SECURECOMMUNICATION_SERVER_SERVERSECURECHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ServerSecureChannelParameter.hpp"

	// from GSRoot
#include "IBinaryChannel.hpp"
#include "OBinaryChannel.hpp"
#include "Owner.hpp"



// --- Forward declarations ----------------------------------------------------

namespace SecureCommunication {
namespace Server {

class ServerSecureChannelImpl;

}
}



// --- ServerSecureChannel class -----------------------------------------------

namespace SecureCommunication {
namespace Server {

class SECURECOMMUNICATION_API ServerSecureChannel {

// Data members:
private:
	GS::Owner<ServerSecureChannelImpl>	m_impl;

// Construction / destruction:
public:
	 ServerSecureChannel (GS::IBinaryChannel* inputChannel, GS::OBinaryChannel* outputChannel, const ServerSecureChannelParameter& secureChannelParameter);
	 ServerSecureChannel (const ServerSecureChannel&) = delete;
	~ServerSecureChannel ();

// Operator overloading:
public:
	ServerSecureChannel&	operator = (const ServerSecureChannel&) = delete;

public:
	GS::OBinaryChannel&		GetOutputChannel ();
	GS::IBinaryChannel&		GetInputChannel ();

	GS::Int32				GetVerifyResult ();
	
};

typedef GS::Ref<ServerSecureChannel, GS::AtomicCounter> ServerSecureChannelRef;

}
}

#endif // SECURECOMMUNICATION_SERVER_SERVERSECURECHANNEL_HPP
