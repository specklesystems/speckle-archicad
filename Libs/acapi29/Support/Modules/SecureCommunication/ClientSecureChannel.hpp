
// *****************************************************************************
//
// Declaration of ClientSecureChannel class
//
// Module:			SecureCommunication
// Namespace:		SecureCommunication::Client
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef SECURECOMMUNICATION_CLIENTSECURECHANNEL_HPP
#define SECURECOMMUNICATION_CLIENTSECURECHANNEL_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "SecureCommunicationExport.hpp"
#include "ClientSecureChannelParameter.hpp"

#include "IBinaryChannel.hpp"
#include "OBinaryChannel.hpp"


namespace SecureCommunication {
namespace Client {
  
class ClientSecureChannelImpl; typedef GS::Ref<ClientSecureChannelImpl, GS::AtomicCounter> ClientSecureChannelImplRef;

class SECURECOMMUNICATION_API ClientSecureChannel {

private:
	ClientSecureChannelImplRef		m_impl;

public:
	ClientSecureChannel (GS::IBinaryChannel* inputChannel, GS::OBinaryChannel* outputChannel, const ClientSecureChannelParameter& secureChannelParameter);
	~ClientSecureChannel ();

private:
	ClientSecureChannel (const ClientSecureChannel&);						// Disabled
	const ClientSecureChannel&	operator = (const ClientSecureChannel&);	// Disabled

public:
	GS::IBinaryChannel&		GetInputChannel ();
	GS::OBinaryChannel&		GetOutputChannel ();

	GS::UInt32				GetVerifyResult ();
};

typedef GS::Ref<ClientSecureChannel, GS::AtomicCounter> ClientSecureChannelRef;

}
}

#endif
