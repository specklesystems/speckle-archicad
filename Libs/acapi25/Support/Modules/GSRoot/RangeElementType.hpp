// *********************************************************************************************************************
// Description:		A traits class, that tells the element type of a range (i.e. container, C array, or any type that
//					can be enumerated with range-based for loop).
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	BIM
//
// *********************************************************************************************************************

#ifndef RANGEELEMENTTYPE_HPP
#define RANGEELEMENTTYPE_HPP

#pragma once


#include "TypeTraits.hpp"


namespace GS {


// === helper function =================================================================================================

namespace Imp {

template <class Range>
decltype (auto)   RangeElementType (const Range* range = nullptr)
{
	for (auto& element : *range)
		return element;

	throw 0;
}

}


// === RangeElementType ================================================================================================

template <class Range>
using RangeElementType = RemoveCV<RemoveReference<decltype (Imp::RangeElementType<Range> ())>>;


}	// namespace GS


#endif
