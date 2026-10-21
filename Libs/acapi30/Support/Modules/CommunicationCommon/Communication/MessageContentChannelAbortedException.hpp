
// *****************************************************************************
//
// Declaration of MessageContentChannelAbortedException class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_MESSAGECONTENTCHANNELABORTEDEXCEPTION_HPP
#define COMMUNICATION_MESSAGECONTENTCHANNELABORTEDEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "ChannelExceptions.hpp"



// --- MessageContentChannelAbortedException class -----------------------------

namespace Communication {

DECLARE_EXCEPTION_CLASS (MessageContentChannelAbortedException, GS::IOException, GS::Error, COMMUNICATIONCOMMON_API);

}

#endif // COMMUNICATION_MESSAGECONTENTCHANNELABORTEDEXCEPTION_HPP