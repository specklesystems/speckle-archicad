
// *****************************************************************************
//
// Declaration of InternetAddress class
//
// Module:			Network
// Namespace:		Network::Socket
// Contact person:	SN
//
// *****************************************************************************

#ifndef NETWORK_SOCKET_INTERNETADDRESS_HPP
#define NETWORK_SOCKET_INTERNETADDRESS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "UnknownHostException.hpp"

	// from GSRoot
#include "Definitions.hpp"
#include "PagedArray.hpp"
#include "Ref.hpp"
#include "String.hpp"



// --- InternetAddress class ---------------------------------------------------

namespace Network {
namespace Socket {

class NETWORK_DLL_EXPORT InternetAddress { // TODO: replace GS::String with GS::UniString...

// Static constants:
public:
	static const InternetAddress	Loopback;
	static const InternetAddress	Any;

// Data members:
private:
	GS::UChar				m_address [4];

	bool					m_hostNameAcquired;
	GS::String				m_hostName;

// Construction / destruction:
private:
			 InternetAddress (GS::UChar address1, GS::UChar address2, GS::UChar address3, GS::UChar address4, const char* hostName);
			 InternetAddress (const GS::UChar* address, const char* hostName);
public:
			 InternetAddress (GS::UChar address1, GS::UChar address2, GS::UChar address3, GS::UChar address4);
	explicit InternetAddress (const GS::UChar* address);
			 InternetAddress (const InternetAddress& rhs);

// Operator overloading:
public:
	const InternetAddress&	operator =  (const InternetAddress& rhs);

	bool					operator == (const InternetAddress& rhs) const;
	bool					operator != (const InternetAddress& rhs) const;

// Operations:
public:
	const GS::UChar*		GetAddress () const;

	GS::String				GetHostAddress () const;
	GS::String				GetHostName ();

	bool					IsLinkLocalAddress () const;
	bool					IsMulticastAddress () const;
	bool					IsLoopbackAddress () const;
	bool					IsPrivateAddress () const;
	bool					IsAnyAddress () const;

// Static operations:
public:
	static GS::String		GetLocalHostName ();
	static InternetAddress	GetLocalHost ();

	static bool				ParseHostAddress (const GS::UniString& hostAddress, GS::UChar (&address) [4]);
	static bool				IsHostAddress (const GS::String& hostAddress);

	static GS::USize		GetAllByName (const GS::String& hostName, GS::PagedArray<InternetAddress>& hostAddresses);

	static InternetAddress	GetByAddress (const GS::String& hostAddress);
	static InternetAddress	GetByAddress (const GS::UChar* address);
	static InternetAddress	GetByName (const GS::String& hostName);

};

typedef GS::Ref<InternetAddress, GS::AtomicCounter>	InternetAddressRef;

////////////////////////////////////////////////////////////////////////////////
// InternetAddress inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		InternetAddress::operator == (const InternetAddress& rhs) const
{
	return (m_address [0] == rhs.m_address [0] &&
			m_address [1] == rhs.m_address [1] &&
			m_address [2] == rhs.m_address [2] &&
			m_address [3] == rhs.m_address [3]);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		InternetAddress::operator != (const InternetAddress& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetAddress
// -----------------------------------------------------------------------------

inline const GS::UChar*		InternetAddress::GetAddress () const
{
	return m_address;
}

// -----------------------------------------------------------------------------
// IsLinkLocalAddress
// -----------------------------------------------------------------------------

inline bool		InternetAddress::IsLinkLocalAddress () const
{
	return (m_address [0] == 169 && m_address [1] == 254);
}

// -----------------------------------------------------------------------------
// IsMulticastAddress
// -----------------------------------------------------------------------------

inline bool		InternetAddress::IsMulticastAddress () const
{
	return (m_address [0] > 223 && m_address [0] < 241);
}

// -----------------------------------------------------------------------------
// IsLoopbackAddress
// -----------------------------------------------------------------------------

inline bool		InternetAddress::IsLoopbackAddress () const
{
	return (m_address [0] == 127 &&
			m_address [1] == 0 &&
			m_address [2] == 0 &&
			m_address [3] == 1);
}

// -----------------------------------------------------------------------------
// IsPrivateAddress
// -----------------------------------------------------------------------------

inline bool		InternetAddress::IsPrivateAddress () const
{
	return (m_address [0] == 10 ||
			(m_address [0] == 172 && (m_address [1] >= 16 && m_address [1] <= 31)) ||
			(m_address [0] == 192 && m_address [1] == 168));
}

// -----------------------------------------------------------------------------
// IsAnyAddress
// -----------------------------------------------------------------------------

inline bool		InternetAddress::IsAnyAddress () const
{
	return (m_address [0] == 0 &&
			m_address [1] == 0 &&
			m_address [2] == 0 &&
			m_address [3] == 0);
}

}
}

#endif // NETWORK_SOCKET_INTERNETADDRESS_HPP
