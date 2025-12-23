
// *****************************************************************************
//
// Declaration of ClientFilterSet class
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTFILTERSET_HPP
#define COMMUNICATION_CLIENT_CLIENTFILTERSET_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientRequestFilter.hpp"
#include "Communication/Client/ClientResponseFilter.hpp"



// --- ClientFilterSet class ---------------------------------------------------

namespace Communication {
namespace Client {

class COMMUNICATIONCLIENT_API ClientFilterSet {

// Type definitions:
public:
	typedef GS::PagedArray<ClientResponseFilterRef> ClientResponseFilters;
	typedef GS::PagedArray<ClientRequestFilterRef> ClientRequestFilters;

// Data members:
private:
	ClientResponseFilters			m_responseFilters;
	ClientRequestFilters			m_requestFilters;

// Operations:
public:
	GS::USize						GetSize () const;

	bool							IsEmpty () const;


	void							SetResponseFilters (const ClientResponseFilters& responseFilters);
	const ClientResponseFilters&	GetResponseFilters () const;
	ClientResponseFilters&			GetResponseFilters ();

	void							SetRequestFilters (const ClientRequestFilters& requestFilters);
	const ClientRequestFilters&		GetRequestFilters () const;
	ClientRequestFilters&			GetRequestFilters ();


	void							Swap (ClientFilterSet& rhs);

	bool							IsValid () const;

};

////////////////////////////////////////////////////////////////////////////////
// ClientFilterSet inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetSize
// -----------------------------------------------------------------------------

inline GS::USize	ClientFilterSet::GetSize () const
{
	return m_responseFilters.GetSize () + m_requestFilters.GetSize ();
}

// -----------------------------------------------------------------------------
// IsEmpty
// -----------------------------------------------------------------------------

inline bool		ClientFilterSet::IsEmpty () const
{
	return (GetSize () == 0);
}

// -----------------------------------------------------------------------------
// SetResponseFilters
// -----------------------------------------------------------------------------

inline void		ClientFilterSet::SetResponseFilters (const ClientResponseFilters& responseFilters)
{
	m_responseFilters = responseFilters;
}

// -----------------------------------------------------------------------------
// GetResponseFilters
// -----------------------------------------------------------------------------

inline const ClientFilterSet::ClientResponseFilters&	ClientFilterSet::GetResponseFilters () const
{
	return m_responseFilters;
}

// -----------------------------------------------------------------------------
// GetResponseFilters
// -----------------------------------------------------------------------------

inline ClientFilterSet::ClientResponseFilters&	ClientFilterSet::GetResponseFilters ()
{
	return m_responseFilters;
}

// -----------------------------------------------------------------------------
// SetRequestFilters
// -----------------------------------------------------------------------------

inline void		ClientFilterSet::SetRequestFilters (const ClientRequestFilters& requestFilters)
{
	m_requestFilters = requestFilters;
}

// -----------------------------------------------------------------------------
// GetRequestFilters
// -----------------------------------------------------------------------------

inline const ClientFilterSet::ClientRequestFilters&		ClientFilterSet::GetRequestFilters () const
{
	return m_requestFilters;
}

// -----------------------------------------------------------------------------
// GetRequestFilters
// -----------------------------------------------------------------------------

inline ClientFilterSet::ClientRequestFilters&	ClientFilterSet::GetRequestFilters ()
{
	return m_requestFilters;
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTFILTERSET_HPP