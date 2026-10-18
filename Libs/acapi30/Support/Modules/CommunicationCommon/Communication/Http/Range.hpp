
// *****************************************************************************
//
// Declaration of Range interface
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_RANGE_HPP
#define COMMUNICATION_HTTP_RANGE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/RangeUnit.hpp"

	// from GSRoot
#include "Owner.hpp"



// --- Range class -------------------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API Range {

// Construction / destruction:
protected:
			 Range () = default;
			 Range (const Range&) = default;
public:
	virtual ~Range ();

// Operator overloading:
protected:
	Range&					operator = (const Range&) = default;

// Operations:
public:
	virtual RangeUnit		GetUnit () const = 0;

	virtual bool			Equals (const Range& rhs) const = 0;

	virtual GS::UniString	ToString () const = 0;
	virtual GS::UniString	Format () const = 0;

	virtual bool			IsValid () const = 0;

// Static operations:
public:
	static bool				Parse (const GS::UniString& rangeString,
								GS::Owner<Range>& rangeParsed);

};

}
}

#endif // COMMUNICATION_HTTP_RANGE_HPP