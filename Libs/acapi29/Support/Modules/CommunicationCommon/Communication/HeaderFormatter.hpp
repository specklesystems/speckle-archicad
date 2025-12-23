
// *****************************************************************************
//
// Declaration of HeaderFormatter class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HEADERFORMATTER_HPP
#define COMMUNICATION_HEADERFORMATTER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/HeaderElement.hpp"



// --- HeaderFormatter class ---------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API  HeaderFormatter {

// Operations:
public:
	GS::UniString		Format (const GS::PagedArray<HeaderParameter>& headerParameters, bool quote = false) const;
	GS::UniString		Format (const HeaderParameter& headerParameter, bool quote = false) const;

	GS::UniString		Format (const GS::PagedArray<HeaderElement>& headerElements, bool quote = false) const;
	GS::UniString		Format (const HeaderElement& headerElement, bool quote = false) const;

// Implementation:
private:
	GS::UniString		FormatValue (const GS::UniString& value, bool quote = false,
							bool autoQuoteEnabled = true) const;


};

}

#endif // COMMUNICATION_HEADERFORMATTER_HPP