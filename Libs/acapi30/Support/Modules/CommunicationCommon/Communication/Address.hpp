
// *****************************************************************************
//
// Declaration of Address interface
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_ADDRESS_HPP
#define COMMUNICATION_ADDRESS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "Ref.hpp"
#include "UniString.hpp"



// --- Address class -----------------------------------------------------------

namespace Communication {
	
class COMMUNICATIONCOMMON_API Address {

// Construction / destruction:
protected:
			 Address () = default;
			 Address (const Address&) = default;
public:
	virtual ~Address ();

// Operator overloading:
protected:
	Address&				operator = (const Address&) = default;

// Operations:
public:
	virtual bool			Equals (const Address& rhs) const = 0;

	virtual GS::UniString	ToString () const = 0;

	virtual Address*		Clone () const = 0;

};

typedef GS::Ref<Address, GS::Counter> AddressRef;

}

#endif // COMMUNICATION_ADDRESS_HPP