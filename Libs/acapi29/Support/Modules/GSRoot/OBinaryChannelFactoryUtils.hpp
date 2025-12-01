
// *****************************************************************************
//
// Declaration of OBinaryChannelFactory related utility functions
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_OBINARYCHANNELFACTORYUTILS_HPP
#define GS_OBINARYCHANNELFACTORYUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "OBinaryChannelFactory.hpp"



// --- Inline utility functions ------------------------------------------------

namespace GS {

// -----------------------------------------------------------------------------
// CheckOutputChannelFactory
// -----------------------------------------------------------------------------

inline void		CheckOutputChannelFactory (const OBinaryChannelFactoryRef& outputChannelFactory, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (outputChannelFactory == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid output channel factory: factory is null.", sourceFile, sourceLine);
	}
}

}

#endif // GS_OBINARYCHANNELFACTORYUTILS_HPP