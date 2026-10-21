
// *****************************************************************************
//
// Declaration of ByteRangeBuilder class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_BYTERANGEBUILDER_HPP
#define COMMUNICATION_HTTP_BYTERANGEBUILDER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ByteRange.hpp"
#include "Communication/Http/ByteRangeBuilderException.hpp"



// --- ByteRangeBuilder class --------------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API ByteRangeBuilder {

// Data members:
private:
	ByteRange			m_byteRange;

// Operations:
public:
	ByteRangeBuilder&	AddLowerBoundRange (GS::UInt64 firstBytePosition);
	ByteRangeBuilder&	AddSuffixRange (GS::UInt64 suffixLength);
	ByteRangeBuilder&	AddBoundRange (GS::UInt64 firstBytePosition,
							GS::UInt64 lastBytePosition);

	ByteRange			Build ();

};

}
}

#endif // COMMUNICATION_HTTP_BYTERANGEBUILDER_HPP