
// *****************************************************************************
//
// Declaration of SessionHandlerClientRequestFilter class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client::Filters
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_FILTERS_SESSIONHANDLERCLIENTREQUESTFILTER_HPP
#define COMMUNICATION_CLIENT_FILTERS_SESSIONHANDLERCLIENTREQUESTFILTER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequestFilter.hpp"



// --- SessionHandlerClientRequestFilter class ---------------------------------

namespace Communication {
namespace Client {
namespace Filters {

class COMMUNICATIONCLIENT_API SessionHandlerClientRequestFilter : public ClientRequestFilter {

// Type definitions:
public:
	enum Placement {
		InParameters,
		InHeaders
	};

// Data members:
private:
	GS::UniString		m_sessionIdParameterName;
	GS::UniString		m_sessionId;

	Placement			m_placement;

// Construction / destruction:
public:
	SessionHandlerClientRequestFilter (const GS::UniString& sessionIdParameterName, const GS::UniString& sessionId, Placement placement);

// ClientRequestFilter interface implementation:
public:
	virtual void		Filter (ClientRequestContext& context) override;

};

}
}
}

#endif // COMMUNICATION_CLIENT_FILTERS_SESSIONHANDLERCLIENTREQUESTFILTER_HPP