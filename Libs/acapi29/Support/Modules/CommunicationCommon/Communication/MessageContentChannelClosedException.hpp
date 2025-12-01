
// *****************************************************************************
//
// Declaration of MessageContentChannelClosedException class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_MESSAGECONTENTCHANNELCLOSEDEXCEPTION_HPP
#define COMMUNICATION_MESSAGECONTENTCHANNELCLOSEDEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "ChannelExceptions.hpp"



// --- MessageContentChannelClosedException class ------------------------------

namespace Communication {

DECLARE_EXCEPTION_CLASS (MessageContentChannelClosedException, GS::IOException, GS::Error, COMMUNICATIONCOMMON_API);

}

#endif // COMMUNICATION_MESSAGECONTENTCHANNELCLOSEDEXCEPTION_HPP