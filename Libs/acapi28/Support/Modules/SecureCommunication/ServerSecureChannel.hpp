
// *****************************************************************************
//
// Declaration of ServerSecureChannel class
//
// Module:			SecureCommunication
// Namespace:		SecureCommunication::Server
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef SECURECOMMUNICATION_SERVERSECURECHANNEL_HPP
#define SECURECOMMUNICATION_SERVERSECURECHANNEL_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "SecureCommunicationExport.hpp"
#include "ServerSecureChannelParameter.hpp"

#include "IBinaryChannel.hpp"
#include "OBinaryChannel.hpp"


namespace SecureCommunication {
namespace Server {
  
class ServerSecureChannelImpl; typedef GS::Ref<ServerSecureChannelImpl, GS::AtomicCounter> ServerSecureChannelImplRef;

class SECURECOMMUNICATION_API ServerSecureChannel {

private:
	ServerSecureChannelImplRef		m_impl;

public:
	ServerSecureChannel (GS::IBinaryChannel* inputChannel, GS::OBinaryChannel* outputChannel, const ServerSecureChannelParameter& secureChannelParameter);
	~ServerSecureChannel ();

private:
	ServerSecureChannel (const ServerSecureChannel&);						// Disabled
	const ServerSecureChannel&	operator = (const ServerSecureChannel&);	// Disabled

public:
	GS::IBinaryChannel&		GetInputChannel ();
	GS::OBinaryChannel&		GetOutputChannel ();

	GS::Int32				GetVerifyResult ();
};

typedef GS::Ref<ServerSecureChannel, GS::AtomicCounter> ServerSecureChannelRef;

}
}

#endif
