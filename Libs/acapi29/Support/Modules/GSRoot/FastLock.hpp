
// *****************************************************************************
//
// Declaration of FastLock class
//
// Module:          GSRoot
// Namespace:       GS
// Contact person:  SN
//
// *****************************************************************************

#ifndef GS_FASTLOCK_HPP
#define GS_FASTLOCK_HPP

#pragma once



// --- Includes ----------------------------------------------------------------

#if defined (WINDOWS)
	#if defined (GSTHREADING_USE_SPIN_LOCKS)
		#include "WinFastLockSpinImpl.hpp"
	#else
		#include "WinFastLockImpl.hpp"
	#endif
#elif defined (macintosh)
	#if defined (GSTHREADING_USE_SPIN_LOCKS)
		#include "MacFastLockSpinImpl.hpp"
	#else
		#include "MacFastLockImpl.hpp"
	#endif
#elif defined (__linux__)
	#if defined (GSTHREADING_USE_SPIN_LOCKS)
		#include "LnxFastLockSpinImpl.hpp"
	#else
		#include "LnxFastLockImpl.hpp"
	#endif
#endif

#endif // GS_FASTLOCK_HPP
