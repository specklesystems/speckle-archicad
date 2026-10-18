
// *****************************************************************************
//
// Declaration of ClientSecureChannel class
//
// Module:			SecureCommunication
// Namespace:		SecureCommunication::Client
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef SECURECOMMUNICATION_CLIENT_CLIENTSECURECHANNEL_HPP
#define SECURECOMMUNICATION_CLIENT_CLIENTSECURECHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ClientSecureChannelParameter.hpp"

	// from GSRoot
#include "IBinaryChannel.hpp"
#include "OBinaryChannel.hpp"
#include "Owner.hpp"



// --- Forward declarations ----------------------------------------------------

namespace SecureCommunication {
namespace Client {

class ClientSecureChannelImpl;

}
}



// --- ClientSecureChannel class -----------------------------------------------

namespace SecureCommunication {
namespace Client {

class SECURECOMMUNICATION_API ClientSecureChannel {

// Data members:
private:
	GS::Owner<ClientSecureChannelImpl>	m_impl;

// Construction / destruction:
public:
	 ClientSecureChannel (GS::IBinaryChannel* inputChannel, GS::OBinaryChannel* outputChannel, const ClientSecureChannelParameter& secureChannelParameter);
	 ClientSecureChannel (ClientSecureChannel&) = delete;
	~ClientSecureChannel ();

// Operator overloading:
public:
	ClientSecureChannel&	operator = (ClientSecureChannel&) = delete;

public:
	GS::OBinaryChannel&		GetOutputChannel ();
	GS::IBinaryChannel&		GetInputChannel ();

	GS::UInt32				GetVerifyResult ();

};

typedef GS::Ref<ClientSecureChannel, GS::AtomicCounter> ClientSecureChannelRef;

}
}

#endif // SECURECOMMUNICATION_CLIENT_CLIENTSECURECHANNEL_HPP
