
// *****************************************************************************
//
//                                  SkipContainer Common
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, KKr
//
// SG compatible
//
// *****************************************************************************


#if !defined SKIPCOMMON_HPP
#define SKIPCOMMON_HPP

#pragma once

namespace GS {

template <class Type>
struct DefaultComparator {
	static_assert (GS::HasOperatorEquals<Type> && GS::HasOperatorLess<Type>, "Type is not sortable: operator< and operator== are required");

	static bool IsEqual (const Type& t1, const Type& t2) { return t1 == t2; }
	static bool IsLess (const Type& t1, const Type& t2) { return t1 < t2; }
};

} // namespace GS

#endif
