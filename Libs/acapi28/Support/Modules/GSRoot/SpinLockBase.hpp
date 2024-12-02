
// *****************************************************************************
//
// Declaration of SpinLockBase abstract class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_SPINLOCKBASE_HPP
#define GS_SPINLOCKBASE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"

#if defined (WINDOWS)
#include "Win32Interface.hpp"
#endif

#if defined (__linux__)
#include <immintrin.h>
#endif



// --- SpinLockBase class ------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT SpinLockBase {

// Static constant members:
public:
	static constexpr GS::UInt64		CacheLineSize = 64;

	static void						Pause ();

// Static implementation:
protected:
	static void						Sleep ();

};

////////////////////////////////////////////////////////////////////////////////
// SpinLockBase inlines

////////////////////////////////////////////////////////////////////////////////
// Static implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Pause
// -----------------------------------------------------------------------------

inline void		SpinLockBase::Pause ()
{
#if defined (macintosh)
#if defined (GS_X86_64)
	asm volatile("pause");
#else
	asm volatile("wfe");
#endif
#endif
#if defined (__linux__)
    _mm_pause ();
#endif
#if defined (WINDOWS)
	YieldProcessor ();
#endif
}

}

#endif // GS_SPINLOCKBASE_HPP
