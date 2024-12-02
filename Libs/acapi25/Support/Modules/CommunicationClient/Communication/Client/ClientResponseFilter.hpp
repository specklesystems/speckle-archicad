
// *****************************************************************************
//
// Declaration of ClientResponseFilter interface
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTRESPONSEFILTER_HPP
#define COMMUNICATION_CLIENT_CLIENTRESPONSEFILTER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequestContext.hpp"
#include "Communication/Client/ClientResponseContext.hpp"
#include "Communication/Client/ClientResponseFilterException.hpp"



// --- ClientResponseFilter class ----------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientResponseFilter {

// Construction / destruction:
protected:
			 ClientResponseFilter ();
			 ClientResponseFilter (const ClientResponseFilter&);
public:
	virtual ~ClientResponseFilter ();

// Operator overloading:
protected:
	const ClientResponseFilter&		operator = (const ClientResponseFilter&);

// Operations:
public:
	virtual void					Filter (const ClientRequestContext& requestContext,
											ClientResponseContext& responseContext) = 0;

};

typedef GS::Ref<ClientResponseFilter, GS::Counter> ClientResponseFilterRef;

////////////////////////////////////////////////////////////////////////////////
// ClientResponseFilter inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ClientResponseFilter::ClientResponseFilter ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline ClientResponseFilter::ClientResponseFilter (const ClientResponseFilter&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const ClientResponseFilter&	ClientResponseFilter::operator = (const ClientResponseFilter&)
{
	return *this;
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTRESPONSEFILTER_HPP