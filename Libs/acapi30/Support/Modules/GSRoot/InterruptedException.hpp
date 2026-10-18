
// *****************************************************************************
//
// Declaration of InterruptedException class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_INTERRUPTEDEXCEPTION_HPP
#define GS_INTERRUPTEDEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "SynchronizationException.hpp"



// --- InterruptedException class ----------------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (InterruptedException, SynchronizationException, Error, GSROOT_DLL_EXPORT)

}

#endif // GS_INTERRUPTEDEXCEPTION_HPP
