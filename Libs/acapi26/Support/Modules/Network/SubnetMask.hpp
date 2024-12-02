// *********************************************************************************************************************
// Description:		Subnet Mask (IPv4)
//
// Module:			Network
// Namespace:		Network::Socket
// Contact person:	FAG
//
// SG compatible
// *********************************************************************************************************************

#if !defined NETWORK_SOCKET_SUBNETMASK_HPP
#define NETWORK_SOCKET_SUBNETMASK_HPP

#pragma once

	// from InputOutput
#include "NetworkBase.hpp"
#include "InternetAddress.hpp"

	// from GSRoot
#include "String.hpp"


namespace Network {
namespace Socket {

class NETWORK_DLL_EXPORT SubnetMask
{
private:
	short	ipPrefixLength;

public:
	SubnetMask (short	ipPrefixLength);

	bool	operator== (const SubnetMask& other) const;
	bool	operator!= (const SubnetMask& other) const;

	GS::String		GetSubnetMask () const;
	static short	GetPrefixLength (const GS::UniString&	subNetmask);

	InternetAddress	GetSubnetAddress (InternetAddress	ipAddress) const;
private:
	void			GetNumbers (UChar (&outIPNumbers) [4]) const;
};

inline bool	SubnetMask::operator== (const SubnetMask& other) const
{
	return (ipPrefixLength == other.ipPrefixLength);
}

inline bool	SubnetMask::operator!= (const SubnetMask& other) const
{
	return !operator== (other);
}

}	// namespace Socket
}	// namespace Network

#endif
