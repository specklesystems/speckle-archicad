
// *****************************************************************************
//
// Declaration of ClientRespone interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTRESPONSE_HPP
#define COMMUNICATION_CLIENT_CLIENTRESPONSE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientResponseContentChannelStateException.hpp"

	// from CommunicationCommon
#include "Communication/Message.hpp"
#include "Communication/MessageContentIBinaryChannel.hpp"



// --- Forward declarations ----------------------------------------------------

namespace Communication {
namespace Client {

class ClientConnection; typedef GS::Ref<ClientConnection, GS::AtomicCounter> ClientConnectionRef;

}
}



// --- ClientResponse class ----------------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientResponse : public Message {

// Construction / destruction:
protected:
			 ClientResponse ();
			 ClientResponse (const ClientResponse& rhs);
public:
	virtual ~ClientResponse ();

// Operator overloading:
protected:
	const ClientResponse&						operator = (const ClientResponse& rhs);

// Operations:
public:
	virtual const ClientConnectionRef&			GetConnection () const = 0;

	virtual MessageContentIBinaryChannelRef		GetRawContentChannel () = 0;
	virtual MessageContentIBinaryChannelRef		GetContentChannel () = 0;

	virtual bool								IsStarted () const = 0;
	virtual bool								IsEnded () const = 0;

	virtual void								Start () = 0;
	virtual void								End () = 0;

};

typedef GS::Ref<ClientResponse, GS::Counter> ClientResponseRef;

////////////////////////////////////////////////////////////////////////////////
// ClientResponse inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ClientResponse::ClientResponse () :
	Message ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline ClientResponse::ClientResponse (const ClientResponse& rhs) :
	Message (rhs)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const ClientResponse&	ClientResponse::operator = (const ClientResponse& rhs)
{
	Message::operator = (rhs);

	return *this;
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTRESPONSE_HPP