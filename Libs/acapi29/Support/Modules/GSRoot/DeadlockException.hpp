
// *****************************************************************************
//
// Declaration of DeadlockException class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_DEADLOCKEXCEPTION_HPP
#define GS_DEADLOCKEXCEPTION_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "SynchronizationException.hpp"



// --- DeadlockException class -------------------------------------------------

namespace GS {

DECLARE_EXCEPTION_CLASS (DeadlockException, SynchronizationException, Error, GSROOT_DLL_EXPORT)

}

#endif // GS_DEADLOCKEXCEPTION_HPP
