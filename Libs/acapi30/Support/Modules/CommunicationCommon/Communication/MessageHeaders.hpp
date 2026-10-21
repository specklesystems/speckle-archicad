
// *****************************************************************************
//
// Declaration of MessageHeaders class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_MESSAGEHEADERS_HPP
#define COMMUNICATION_MESSAGEHEADERS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "UniString.hpp"



// --- MessageHeaders class ----------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API MessageHeaders {

// Static constant members:
public:
	static const GS::UniString		ContentTransferEncodingLengthPrefixed;
	static const GS::UniString		ContentTransferEncodingChunked;

	static const GS::UniString		ContentTransferEncodingHeader;


	static const GS::UniString		ContentTransferCompressionDisabled;
	static const GS::UniString		ContentTransferCompressionEnabled;

	static const GS::UniString		ContentTransferCompressionLevelHeader;
	static const GS::UniString		ContentTransferCompressionHeader;


	static const GS::UniString		AcceptEncodingCompressed;

	static const GS::UniString		AcceptEncodingHeader;


};

}

#endif // COMMUNICATION_MESSAGEHEADERS_HPP