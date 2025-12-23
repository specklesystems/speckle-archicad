
// *****************************************************************************
//
// Declaration of ByteRangeBuilderException class
//
// Module:			CommonunicationCommon
// Namespace:		Communication::Http
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_BYTERANGEBUILDEREXCEPTION_HPP
#define COMMUNICATION_HTTP_BYTERANGEBUILDEREXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "GSException.hpp"



// --- ByteRangeBuilderException class -----------------------------------------

namespace Communication {
namespace Http {

DECLARE_EXCEPTION_CLASS (ByteRangeBuilderException, GS::GeneralException, GS::Error, COMMUNICATIONCOMMON_API);

}
}

#endif // COMMUNICATION_HTTP_BYTERANGEBUILDEREXCEPTION_HPP