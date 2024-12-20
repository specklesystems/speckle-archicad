
// *****************************************************************************
//
// Declaration of ClientResponseContext interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTRESPONSECONTEXT_HPP
#define COMMUNICATION_CLIENT_CLIENTRESPONSECONTEXT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientResponse.hpp"

	// from CommunicationCommon
#include "Communication/Headers.hpp"
#include "Communication/Parameters.hpp"
#include "Communication/Properties.hpp"

	// from GSRoot
#include "PagedArray.hpp"



// --- ClientResponseContext class ---------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientResponseContext {

// Construction / destruction:
protected:
			 ClientResponseContext ();
			 ClientResponseContext (const ClientResponseContext&);
public:
	virtual ~ClientResponseContext ();

// Operator overloading:
protected:
	const ClientResponseContext&					operator = (const ClientResponseContext&);

// Operations:
public:
	virtual void									SetResponseContentChannel (const MessageContentIBinaryChannelRef& responseContentChannel) = 0;
	virtual const MessageContentIBinaryChannelRef&	GetResponseContentChannel () const = 0;

	virtual void									SetResponseParameters (const Parameters& responseParameters) = 0;
	virtual const Parameters&						GetResponseParameters () const = 0;
	virtual Parameters&								GetResponseParameters () = 0;

	virtual void									SetResponseHeaders (const Headers& responseHeaders) = 0;
	virtual const Headers&							GetResponseHeaders () const = 0;
	virtual Headers&								GetResponseHeaders () = 0;

	virtual void									SetResponseId (const GS::UniString& responseId) = 0;
	virtual const GS::UniString&					GetResponseId () const = 0;

	virtual void									SetProperties (const Properties& properties) = 0;
	virtual const Properties&						GetProperties () const = 0;
	virtual Properties&								GetProperties () = 0;

};

typedef GS::Ref<ClientResponseContext, GS::Counter> ClientResponseContextRef;

////////////////////////////////////////////////////////////////////////////////
// ClientResponseContext inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ClientResponseContext::ClientResponseContext ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline ClientResponseContext::ClientResponseContext (const ClientResponseContext&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const ClientResponseContext&		ClientResponseContext::operator = (const ClientResponseContext&)
{
	return *this;
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTRESPONSECONTEXT_HPP