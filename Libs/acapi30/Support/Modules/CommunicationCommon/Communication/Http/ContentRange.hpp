
// *****************************************************************************
//
// Declaration of ContentRange interface
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_CONTENTRANGE_HPP
#define COMMUNICATION_HTTP_CONTENTRANGE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/RangeUnit.hpp"

	// from GSRoot
#include "Owner.hpp"



// --- ContentRange class ------------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API ContentRange {

// Construction / destruction:
protected:
			 ContentRange () = default;
			 ContentRange (const ContentRange&) = default;
public:
	virtual ~ContentRange ();

// Operator overloading:
protected:
	ContentRange&			operator = (const ContentRange&) = default;

// Operations:
public:
	virtual RangeUnit		GetUnit () const = 0;

	virtual bool			Equals (const ContentRange& rhs) const = 0;

	virtual GS::UniString	ToString () const = 0;
	virtual GS::UniString	Format () const = 0;

	virtual bool			IsValid () const = 0;

// Static operations:
public:
	static bool				Parse (const GS::UniString& contentRangeString,
								GS::Owner<ContentRange>& contentRangeParsed);

};

}
}

#endif // COMMUNICATION_HTTP_CONTENTRANGE_HPP