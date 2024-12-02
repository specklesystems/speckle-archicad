
// *****************************************************************************
//
// Declaration of ClientRequestFilter interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTREQUESTFILTER_HPP
#define COMMUNICATION_CLIENT_CLIENTREQUESTFILTER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequestContext.hpp"
#include "Communication/Client/ClientRequestFilterException.hpp"



// --- ClientRequestFilter class -----------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientRequestFilter {

// Construction / destruction:
protected:
			 ClientRequestFilter ();
			 ClientRequestFilter (const ClientRequestFilter&);
public:
	virtual ~ClientRequestFilter ();

// Operator overloading:
protected:
	const ClientRequestFilter&	operator = (const ClientRequestFilter&);

// Operations:
public:
	virtual void				Filter (ClientRequestContext& context) = 0;

};

typedef GS::Ref<ClientRequestFilter, GS::Counter> ClientRequestFilterRef;

////////////////////////////////////////////////////////////////////////////////
// ClientRequestFilter inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ClientRequestFilter::ClientRequestFilter ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline ClientRequestFilter::ClientRequestFilter (const ClientRequestFilter&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const ClientRequestFilter&	ClientRequestFilter::operator = (const ClientRequestFilter&)
{
	return *this;
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTREQUESTFILTER_HPP