
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
			 ClientResponseFilter () = default;
			 ClientResponseFilter (const ClientResponseFilter&) = default;
public:
	virtual ~ClientResponseFilter ();

// Operator overloading:
protected:
	ClientResponseFilter&	operator = (const ClientResponseFilter&) = default;

// Operations:
public:
	virtual void			Filter (const ClientRequestContext& requestContext,
								ClientResponseContext& responseContext) = 0;

};

typedef GS::Ref<ClientResponseFilter, GS::Counter> ClientResponseFilterRef;

}
}

#endif // COMMUNICATION_CLIENT_CLIENTRESPONSEFILTER_HPP