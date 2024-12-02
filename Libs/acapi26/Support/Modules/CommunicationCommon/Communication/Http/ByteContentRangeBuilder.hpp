
// *****************************************************************************
//
// Declaration of ByteContentRangeBuilder class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_BYTECONTENTRANGEBUILDER_HPP
#define COMMUNICATION_HTTP_BYTECONTENTRANGEBUILDER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/ByteContentRange.hpp"
#include "Communication/Http/ByteContentRangeBuilderException.hpp"



// --- ByteContentRangeBuilder class -------------------------------------------

namespace Communication {
namespace Http {

class COMMUNICATIONCOMMON_API ByteContentRangeBuilder {

// Data members:
private:
	ByteContentRange			m_byteContentRange;

// Operations:
public:
	ByteContentRangeBuilder&	WithUnknownCompleteLength ();
	ByteContentRangeBuilder&	WithCompleteLength (GS::UInt64 completeLength);

	ByteContentRangeBuilder&	WithUnsatisifedRange ();
	ByteContentRangeBuilder&	WithBoundRange (GS::UInt64 firstBytePosition,
									GS::UInt64 lastBytePosition);

	ByteContentRange			Build ();

};

}
}

#endif // COMMUNICATION_HTTP_BYTECONTENTRANGEBUILDER_HPP