
// *****************************************************************************
//
// Declaration of ClientConnectionProgressListener related utility functions
//
// Module:			CommunicationClient
// Namespace:		Communication::Client
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CLIENT_CLIENTCONNECTIONPROGRESSLISTENERUTILS_HPP
#define COMMUNICATION_CLIENT_CLIENTCONNECTIONPROGRESSLISTENERUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Client/ClientConnectionProgressListener.hpp"



// --- Inline utility functions ------------------------------------------------

namespace Communication {
namespace Client {

// -----------------------------------------------------------------------------
// CheckConnectionProgressListener
// -----------------------------------------------------------------------------

inline void		CheckConnectionProgressListener (ClientConnectionProgressListener* progressListener, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (progressListener == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid client connection progress listener: listener is null.", sourceFile, sourceLine);
	}
}

}
}

#endif // COMMUNICATION_CLIENT_CLIENTCONNECTIONPROGRESSLISTENERUTILS_HPP