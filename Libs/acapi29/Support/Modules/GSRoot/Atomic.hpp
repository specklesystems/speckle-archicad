
// *****************************************************************************
//
// Declaration of atomic functions
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_ATOMIC_HPP
#define GS_ATOMIC_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"
#include "GSRootExport.hpp"



// --- Atomic functions --------------------------------------------------------

namespace GS {
GSROOT_DLL_EXPORT bool		AtomicCompareAndSwap (void* volatile* destination, void* exchange, void* comperand);
GSROOT_DLL_EXPORT bool		AtomicCompareAndSwap (Int32 volatile* destination, Int32 exchange, Int32 comperand);

GSROOT_DLL_EXPORT Int32		AtomicIncrement (Int32 volatile* value);
GSROOT_DLL_EXPORT Int64		AtomicIncrement (Int64 volatile* value);
GSROOT_DLL_EXPORT Int32		AtomicDecrement (Int32 volatile* value);
GSROOT_DLL_EXPORT Int64		AtomicDecrement (Int64 volatile* value);

GSROOT_DLL_EXPORT Int32		AtomicAdd (Int32 volatile* value, Int32 increment);
GSROOT_DLL_EXPORT Int64		AtomicAdd (Int64 volatile* value, Int64 increment);


}

#endif // GS_ATOMIC_HPP
