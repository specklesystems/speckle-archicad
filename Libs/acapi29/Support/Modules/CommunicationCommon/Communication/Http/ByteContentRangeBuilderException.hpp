
// *****************************************************************************
//
// Declaration of ByteContentRangeBuilderException class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_BYTECONTENTRANGEBUILDEREXCEPTION_HPP
#define COMMUNICATION_HTTP_BYTECONTENTRANGEBUILDEREXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "GSException.hpp"



// --- ByteContentRangeBuilderException class ----------------------------------

namespace Communication {
namespace Http {

DECLARE_EXCEPTION_CLASS (ByteContentRangeBuilderException, GS::GeneralException, GS::Error, COMMUNICATIONCOMMON_API);

}
}

#endif // COMMUNICATION_HTTP_BYTECONTENTRANGEBUILDEREXCEPTION_HPP