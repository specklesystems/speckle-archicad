// *********************************************************************************************************************
// Description:		String comparison algorithms
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	TBa
//
// *********************************************************************************************************************


#ifndef STRINGCOMPARISON_HPP
#define STRINGCOMPARISON_HPP

#pragma once


#include "UniString.hpp"


namespace GS {


// === Natural comparison ("item1" < "item2" < "item10") ===============================================================

GSROOT_DLL_EXPORT UniString::CompareResult	NaturalCompare (const UniString& leftOp, const UniString& rightOp, UniString::CaseComparison comp = UniString::CaseInsensitive);
GSROOT_DLL_EXPORT bool						NaturalIsEqual (const UniString& leftOp, const UniString& rightOp, UniString::CaseComparison comp = UniString::CaseInsensitive);
GSROOT_DLL_EXPORT bool						NaturalIsLess  (const UniString& leftOp, const UniString& rightOp, UniString::CaseComparison comp = UniString::CaseInsensitive);


// === SkipSet and SkipMap support =====================================================================================

class GSROOT_DLL_EXPORT NaturalComparator {
public:
	static bool IsEqual (const UniString& leftOp, const UniString& rightOp);
	static bool IsLess  (const UniString& leftOp, const UniString& rightOp);
};


}	// namespace GS


#endif
