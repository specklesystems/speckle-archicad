// *****************************************************************************
//
// Contact person: SN, PR
//
// *****************************************************************************

#ifndef GS_ATOMICDEFINITIONS_HPP
#define GS_ATOMICDEFINITIONS_HPP

#include "Definitions.hpp"

// from Standard Library
#include <atomic>
#include <cstddef>


namespace GS {


constexpr std::size_t CacheLineSize =
	#if defined GS_MAC && defined GS_ARM64
		128
	#else
		64
	#endif
;


// TODO C++20: Enable this when available on all platforms.
//template<typename T>
//using AtomicAligned = alignas (std::atomic_ref<T>::required_alignment) T;


} // namespace GS


#endif /* GS_ATOMICDEFINITIONS_HPP */
