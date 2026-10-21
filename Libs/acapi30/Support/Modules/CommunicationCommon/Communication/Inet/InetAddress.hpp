
// *****************************************************************************
//
// Declaration of InetAddress class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Inet
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_INET_INETADDRESS_HPP
#define COMMUNICATION_INET_INETADDRESS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Address.hpp"

	// from Network
#include "InternetAddress.hpp"



// --- InetAddress class -------------------------------------------------------

namespace Communication {
namespace Inet {

class COMMUNICATIONCOMMON_API InetAddress : public Address {

// Data members:
private:
	Network::Socket::InternetAddressRef			m_address;
	GS::UniString								m_host;
	GS::UShort									m_port;

// Construction / destruction:
public:
	InetAddress (const Network::Socket::InternetAddressRef& address, const GS::UniString& host, GS::UShort port);
	InetAddress (const GS::UniString& host, GS::UShort port);

// Operator overloading:
public:
	bool										operator == (const InetAddress& rhs) const;
	bool										operator != (const InetAddress& rhs) const;

// Operations:
public:
	const Network::Socket::InternetAddressRef&	GetAddress () const;
	const GS::UniString&						GetHost () const;
	GS::UShort									GetPort () const;

	bool										IsResolved () const;

// Address interface implementation:
public:
	virtual bool								Equals (const Address& rhs) const override;

	virtual GS::UniString						ToString () const override;

	virtual Address*							Clone () const override;

};

typedef GS::Ref<InetAddress, GS::Counter> InetAddressRef;

////////////////////////////////////////////////////////////////////////////////
// InetAddress inlines

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		InetAddress::operator != (const InetAddress& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetAddress
// -----------------------------------------------------------------------------

inline const Network::Socket::InternetAddressRef&	InetAddress::GetAddress () const
{
	return m_address;
}

// -----------------------------------------------------------------------------
// GetHost
// -----------------------------------------------------------------------------

inline const GS::UniString&		InetAddress::GetHost () const
{
	return m_host;
}

// -----------------------------------------------------------------------------
// GetPort
// -----------------------------------------------------------------------------

inline GS::UShort	InetAddress::GetPort () const
{
	return m_port;
}

// -----------------------------------------------------------------------------
// IsResolved
// -----------------------------------------------------------------------------

inline bool		InetAddress::IsResolved () const
{
	return (m_address != nullptr);
}

}
}

#endif // COMMUNICATION_INET_INETADDRESS_HPP