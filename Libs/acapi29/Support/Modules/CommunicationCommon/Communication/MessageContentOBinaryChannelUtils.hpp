
// *****************************************************************************
//
// Declaration of MessageContentOBinaryChannel related utility functions
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_MESSAGECONTENTOBINARYCHANNELUTILS_HPP
#define COMMUNICATION_MESSAGECONTENTOBINARYCHANNELUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentOBinaryChannel.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {

// -----------------------------------------------------------------------------
// CheckMessageContentChannel
// -----------------------------------------------------------------------------

inline void		CheckMessageContentChannel (const MessageContentOBinaryChannelRef& outputChannel, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (outputChannel == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid message content output channel: channel is null.", sourceFile, sourceLine);
	}
}

}

#endif // COMMUNICATION_MESSAGECONTENTOBINARYCHANNELUTILS_HPP