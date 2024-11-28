
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

namespace GS {

// TODO: CTC workaround, revisit when upgrading CTC (use these types directly in the macros)
using Guard_for_fast_lock = GS::Guard<GS::FastLock, GS::LockedLockingPolicy>;
using Guard_for_fast_unlock = GS::Guard<GS::FastLock, GS::UnlockedLockingPolicy>;

}

#define fast_lock(fastlock)		if (GS::Guard_for_fast_lock LINENAME(g) = fastlock) { for (;;); } else
#define fast_unlock(fastlock)	if (GS::Guard_for_fast_unlock LINENAME(g) = fastlock) { for (;;); } else

#endif // GS_FASTLOCKGUARD_HPP
