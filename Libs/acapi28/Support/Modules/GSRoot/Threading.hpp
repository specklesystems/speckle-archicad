
// *****************************************************************************
//
// Declaration of threading initialization and termination routines
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADING_HPP
#define GS_THREADING_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "GSRootExport.hpp"



// -----------------------------------------------------------------------------

namespace GS {
namespace Threading {

GSROOT_DLL_EXPORT Int32	Initialize ();
GSROOT_DLL_EXPORT bool	IsInitialized ();
GSROOT_DLL_EXPORT Int32	Terminate ();

}
}

#endif // GS_THREADING_HPP
