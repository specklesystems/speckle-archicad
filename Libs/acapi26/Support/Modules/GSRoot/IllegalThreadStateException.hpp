
// *****************************************************************************
//
// Declaration of IllegalThreadStateException class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_ILLEGALTHREADSTATEEXCEPTION_HPP
#define GS_ILLEGALTHREADSTATEEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ThreadingException.hpp"



// --- IllegalThreadStateException class ---------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (IllegalThreadStateException, ThreadingException, Error, GSROOT_DLL_EXPORT)

}

#endif // GS_ILLEGALTHREADSTATEEXCEPTION_HPP
