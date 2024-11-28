
// *****************************************************************************
//
// Declaration of FastLockGuard
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_FASTLOCKGUARD_HPP
#define GS_FASTLOCKGUARD_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Guard.hpp"
#include "FastLock.hpp"



// --- Macro definitions -------------------------------------------------------

#define fast_lock(fastlock)		if (GS::Guard<GS::FastLock, GS::LockedLockingPolicy> LINENAME(g) = fastlock) { for (;;); } else
#define fast_unlock(fastlock)		if (GS::Guard<GS::FastLock, GS::UnlockedLockingPolicy> LINENAME(g) = fastlock) { for (;;); } else

#endif // GS_FASTLOCKGUARD_HPP
