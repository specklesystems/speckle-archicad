
// *****************************************************************************
//
// Declaration of IllegalMonitorStateException
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_ILLEGALMONITORSTATEEXCEPTION_HPP
#define GS_ILLEGALMONITORSTATEEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "SynchronizationException.hpp"



// --- IllegalMonitorStateException class --------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (IllegalMonitorStateException, SynchronizationException, Error, GSROOT_DLL_EXPORT)

}

#endif // GS_ILLEGALMONITORSTATEEXCEPTION_HPP
