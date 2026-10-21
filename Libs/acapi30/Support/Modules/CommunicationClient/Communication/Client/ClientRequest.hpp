
// *****************************************************************************
//
// Declaration of ClientRequest interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTREQUEST_HPP
#define COMMUNICATION_CLIENT_CLIENTREQUEST_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequestContentChannelStateException.hpp"

	// from CommunicationCommon
#include "Communication/Message.hpp"
#include "Communication/MessageContent.hpp"
#include "Communication/MessageContentOBinaryChannel.hpp"



// --- Forward declarations ----------------------------------------------------

namespace Communication {
namespace Client {

class ClientConnection; typedef GS::Ref<ClientConnection, GS::AtomicCounter> ClientConnectionRef;

}
}



// --- ClientRequest class -----------------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientRequest : public Message {

// Construction / destruction:
protected:
			 ClientRequest () = default;
			 ClientRequest (const ClientRequest&) = default;
public:
	virtual ~ClientRequest ();

// Operator overloading:
protected:
	ClientRequest&								operator = (const ClientRequest&) = default;

// Operations:
public:
	virtual const ClientConnectionRef&			GetConnection () const = 0;

	virtual MessageContentOBinaryChannelRef		GetRawContentChannel () = 0;
	virtual MessageContentOBinaryChannelRef		GetContentChannel () = 0;

	virtual void								SetContent (const MessageContentRef& content) = 0;
	virtual const MessageContentRef&			GetContent () const = 0;

	virtual bool								IsStarted () const = 0;
	virtual bool								IsAborted () const = 0;
	virtual bool								IsEnded () const = 0;

	virtual void								Start () = 0;
	virtual void								Abort (const GS::UniString& message = GS::UniString ()) = 0;
	virtual void								End () = 0;

	virtual void								Send ();

};

typedef GS::Ref<ClientRequest, GS::Counter> ClientRequestRef;

}
}

#endif // COMMUNICATION_CLIENT_CLIENTREQUEST_HPP