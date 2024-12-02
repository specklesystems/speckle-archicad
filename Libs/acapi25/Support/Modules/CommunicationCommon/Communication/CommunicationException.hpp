
// *****************************************************************************
//
// Declaration of CommunicationException class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_COMMUNICATIONEXCEPTION_HPP
#define COMMUNICATION_COMMUNICATIONEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "ChannelExceptions.hpp"



// --- CommunicationException class --------------------------------------------

namespace Communication {

DECLARE_EXCEPTION_CLASS (CommunicationException, GS::IOException, GS::Error, COMMUNICATIONCOMMON_API);

}

#endif // COMMUNICATION_COMMUNICATIONEXCEPTION_HPP