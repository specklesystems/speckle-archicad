
// *****************************************************************************
//
// Declaration and implementation of ExponentialBackoff class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_EXPONENTIALBACKOFF_HPP
#define GS_EXPONENTIALBACKOFF_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "BackoffBase.hpp"
#include "BaseAlgorithms.hpp"



// --- ExponentialBackoff class ------------------------------------------------

namespace GS {

template<UInt32 MinBackoffSpinCount, UInt32 MaxBackoffSpinCount>
class ExponentialBackoff : private BackoffBase {

// Constraints:
	static_assert (MinBackoffSpinCount < MaxBackoffSpinCount, "Min back off spin count must be less then max back off spin count.");

// Static operations:
public:
	static UInt32	GetNextBackoffSpinCount (UInt32 currentBackoffSpinCount);

};

////////////////////////////////////////////////////////////////////////////////
// ExponentialBackoff implementation

////////////////////////////////////////////////////////////////////////////////
// Static operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetNextBackoffSpinCount
// -----------------------------------------------------------------------------

template<UInt32 MinBackoffSpinCount, UInt32 MaxBackoffSpinCount>
inline UInt32	ExponentialBackoff<MinBackoffSpinCount, MaxBackoffSpinCount>::GetNextBackoffSpinCount (UInt32 currentBackoffSpinCount)
{
	if (currentBackoffSpinCount <= MinBackoffSpinCount) {
		return Max ((BackoffBase::GetSalt () + BackoffBase::Rand ()) % (MaxBackoffSpinCount >> 2), MinBackoffSpinCount);
	} else {
		return Min ((currentBackoffSpinCount << 1), MaxBackoffSpinCount);
	}
}

}

#endif // GS_EXPONENTIALBACKOFF_HPP