// *********************************************************************************************************************
// Description:     GS::ConstMemoryRange describes a piece of raw memory
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzoBe
//
// *********************************************************************************************************************


#ifndef MEMORYRANGE_HPP
#define MEMORYRANGE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"


namespace GS {


// === struct ConstMemoryRange =========================================================================================

struct ConstMemoryRange {
	const char*		data = nullptr;
	UInt64			length = 0;

	inline ConstMemoryRange () = default;
	inline ConstMemoryRange (const char* data, UInt64 length);
};


// === class ConstMemoryRangeSource =========================================================================================

class GSROOT_DLL_EXPORT ConstMemoryRangeSource {
public:
	virtual ConstMemoryRange GetMemoryRange () const = 0;
	virtual ~ConstMemoryRangeSource ();

};


// === struct ConstMemoryRange Implementation ==========================================================================


ConstMemoryRange::ConstMemoryRange (const char* data, UInt64 length) :
	data (data),
	length (length)
{
}


}	// namespace GS


#endif
