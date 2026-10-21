
// *****************************************************************************
//
// Declaration of HeaderParser class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HEADERPARSER_HPP
#define COMMUNICATION_HEADERPARSER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/HeaderElement.hpp"



// --- HeaderParser class ------------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API HeaderParser {

// Operations:
public:
	bool			Parse (const GS::UniString& headerValue, GS::PagedArray<HeaderParameter>& headerParameters) const;
	bool			Parse (const GS::UniString& headerValue, HeaderParameter& headerParameter) const;

	bool			Parse (const GS::UniString& headerValue, GS::PagedArray<HeaderElement>& headerElements) const;
	bool			Parse (const GS::UniString& headerValue, HeaderElement& headerElement) const;

// Implementation:
private:
	GS::UInt32		ParseValue (const GS::UniString& str, GS::UIndex from, GS::UIndex to, const GS::UniChar* delimiters,
						GS::USize delimitersCount, GS::UniString& value) const;
	GS::UInt32		ParseToken (const GS::UniString& str, GS::UIndex from, GS::UIndex to, const GS::UniChar* delimiters,
						GS::USize delimitersCount, GS::UniString& token) const;

	bool			ParseImpl (const GS::UniString& str, GS::UIndex from, GS::UIndex to,
						GS::PagedArray<HeaderParameter>& headerParameters,
						GS::UInt32& processed) const;
	bool			ParseImpl (const GS::UniString& str, GS::UIndex from, GS::UIndex to,
						HeaderParameter& headerParameter,
						GS::UInt32& processed) const;

	bool			ParseImpl (const GS::UniString& str, GS::UIndex from, GS::UIndex to,
						GS::PagedArray<HeaderElement>& headerElements,
						GS::UInt32& processed) const;
	bool			ParseImpl (const GS::UniString& str, GS::UIndex from, GS::UIndex to,
						HeaderElement& headerElement,
						GS::UInt32& processed) const;

};

}

#endif // COMMUNICATION_HEADERPARSER_HPP