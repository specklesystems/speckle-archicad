// *****************************************************************************
//
// A memory barrier (also known as membar or memory fence or fence instruction)
// enforces in-order execution. See the following pages for details:
//
// http://en.wikipedia.org/wiki/Memory_ordering
// http://en.wikipedia.org/wiki/Memory_barrier
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	IZO
//
// *****************************************************************************

#pragma once

#ifndef GS_MEMORYBARRIER_HPP
#define GS_MEMORYBARRIER_HPP

#if defined (_MSC_VER)
#include <intrin.h>
#endif

namespace GS {

// Enforces in-order execution. You can call it from any place.
GS_FORCE_INLINE void MemoryBarrierForNonVolatile ()
{
#if defined (__GNUC__)
	#if defined GS_X86_64
		asm volatile("" ::: "memory");
	#elif defined GS_ARM64
		__sync_synchronize ();
	#else
		#error "To be implemented."
	#endif
#elif defined (_MSC_VER)
	_ReadWriteBarrier();
#else
#error "To be implemented."
#endif
}

// Enforces in-order execution when dealing with volatile variables. It allows
// for an optimization over the normal MemoryBarrier call on Windows. You should
// only call this function immediately before or after accessing a volatile
// variable.
GS_FORCE_INLINE void MemoryBarrierForVolatile ()
{
#if defined (__GNUC__)
	#if defined GS_X86_64
		asm volatile("" ::: "memory");
	#elif defined GS_ARM64
		__sync_synchronize ();
	#else
		#error "To be implemented."
	#endif
#elif defined (_MSC_VER)
	// In Visual C++, volatiles are implicit memory barriers, so wo do not have
	// to do anything.
#else
#error "To be implemented."
#endif
}

}

#endif // GS_MEMORYBARRIER_HPP
