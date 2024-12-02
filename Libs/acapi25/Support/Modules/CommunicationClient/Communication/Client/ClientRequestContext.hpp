
// *****************************************************************************
//
// Declaration of ClientRequestContext interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTREQUESTCONTEXT_HPP
#define COMMUNICATION_CLIENT_CLIENTREQUESTCONTEXT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequest.hpp"

	// from CommunicationClient
#include "Communication/Headers.hpp"
#include "Communication/Parameters.hpp"
#include "Communication/Properties.hpp"

	// from GSRoot
#include "PagedArray.hpp"



// --- ClientRequestContext class ----------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientRequestContext {

// Construction / destruction:
protected:
			 ClientRequestContext ();
			 ClientRequestContext (const ClientRequestContext&);
public:
	virtual ~ClientRequestContext ();

// Operator overloading:
protected:
	const ClientRequestContext&						operator = (const ClientRequestContext&);

// Operations:
public:
	virtual void									SetRequestContentChannel (const MessageContentOBinaryChannelRef& requestContentChannel) = 0;
	virtual const MessageContentOBinaryChannelRef&	GetRequestContentChannel () const = 0;

	virtual void									SetRequestParameters (const Parameters& requestParameters) = 0;
	virtual const Parameters&						GetRequestParameters () const = 0;
	virtual Parameters&								GetRequestParameters () = 0;

	virtual void									SetRequestHeaders (const Headers& requestHeaders) = 0;
	virtual const Headers&							GetRequestHeaders () const = 0;
	virtual Headers&								GetRequestHeaders () = 0;

	virtual void									SetRequestId (const GS::UniString& requestId) = 0;
	virtual const GS::UniString&					GetRequestId () const = 0;

	virtual void									SetProperties (const Properties& properties) = 0;
	virtual const Properties&						GetProperties () const = 0;
	virtual Properties&								GetProperties () = 0;

};

typedef GS::Ref<ClientRequestContext, GS::Counter> ClientRequestContextRef;

////////////////////////////////////////////////////////////////////////////////
// ClientRequestContext inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ClientRequestContext::ClientRequestContext ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline ClientRequestContext::ClientRequestContext (const ClientRequestContext&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const ClientRequestContext&	ClientRequestContext::operator = (const ClientRequestContext&)
{
	return *this;
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTREQUESTCONTEXT_HPP