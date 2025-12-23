
// *****************************************************************************
//
// Declaration of IBinaryChannelFactory related utility functions
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_IBINARYCHANNELFACTORYUTILS_HPP
#define GS_IBINARYCHANNELFACTORYUTILS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "IBinaryChannelFactory.hpp"



// --- Inline utility functions ------------------------------------------------

namespace GS {

// -----------------------------------------------------------------------------
// CheckInputChannelFactory
// -----------------------------------------------------------------------------

inline void		CheckInputChannelFactory (const IBinaryChannelFactoryRef& inputChannelFactory, const char* sourceFile, GS::UInt32 sourceLine)
{
	if (DBERROR (inputChannelFactory == nullptr)) {
		throw GS::IllegalArgumentException ("Invalid input chnanel factory: factory is null.", sourceFile, sourceLine);
	}
}

}

#endif // GS_IBINARYCHANNELFACTORYUTILS_HPP