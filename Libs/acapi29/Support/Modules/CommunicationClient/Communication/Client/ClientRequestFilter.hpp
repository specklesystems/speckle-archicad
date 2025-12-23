
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
			 ClientRequestFilter () = default;
			 ClientRequestFilter (const ClientRequestFilter&) = default;
public:
	virtual ~ClientRequestFilter ();

// Operator overloading:
protected:
	ClientRequestFilter&	operator = (const ClientRequestFilter&) = default;

// Operations:
public:
	virtual void			Filter (ClientRequestContext& context) = 0;

};

typedef GS::Ref<ClientRequestFilter, GS::Counter> ClientRequestFilterRef;

}
}

#endif // COMMUNICATION_CLIENT_CLIENTREQUESTFILTER_HPP