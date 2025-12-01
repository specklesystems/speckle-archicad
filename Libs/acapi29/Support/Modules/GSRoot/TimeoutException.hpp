
// *****************************************************************************
//
// Declaration of TimeoutException
//
// Module:          GSRoot
// Namespace:       GS
// Contact person:  SN
//
// *****************************************************************************

#ifndef GS_TIMEOUTEXCEPTION_HPP
#define GS_TIMEOUTEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "SynchronizationException.hpp"



// --- TimeoutException class --------------------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (TimeoutException, SynchronizationException, Error, GSROOT_DLL_EXPORT)

}

#endif // GS_TIMEOUTEXCEPTION_HPP
