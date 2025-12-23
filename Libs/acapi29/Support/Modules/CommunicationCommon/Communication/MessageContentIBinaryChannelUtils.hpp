
// *****************************************************************************
//
// Declaration of MessageContentIBinaryChannel related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_MESSAGECONTENTIBINARYCHANNELUTILS_HPP
#define COMMUNICATION_MESSAGECONTENTIBINARYCHANNELUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentIBinaryChannel.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {

// -----------------------------------------------------------------------------
// CheckMessageContentChannel
// -----------------------------------------------------------------------------

inline void		CheckMessageContentChannel (const MessageContentIBinaryChannelRef& inputChannel, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (inputChannel == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid message content input channel: channel is null.", sourceFile, sourceLine);
	}
}

}

#endif // COMMUNICATION_MESSAGECONTENTIBINARYCHANNELUTILS_HPP