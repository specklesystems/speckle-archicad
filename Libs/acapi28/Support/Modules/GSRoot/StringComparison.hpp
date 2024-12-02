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

GSROOT_DLL_EXPORT UniString::CompareResult	NaturalCompare (const UniString& leftOp, const UniString& rightOp, CaseComparison comp = CaseInsensitive);
GSROOT_DLL_EXPORT bool						NaturalIsEqual (const UniString& leftOp, const UniString& rightOp, CaseComparison comp = CaseInsensitive);
GSROOT_DLL_EXPORT bool						NaturalIsLess  (const UniString& leftOp, const UniString& rightOp, CaseComparison comp = CaseInsensitive);


// === SkipSet and SkipMap support =====================================================================================

class GSROOT_DLL_EXPORT NaturalComparator {
public:
	static bool IsEqual (const UniString& leftOp, const UniString& rightOp);
	static bool IsLess  (const UniString& leftOp, const UniString& rightOp);
};

struct GSROOT_DLL_EXPORT CaseInsensitiveComparator {
public:
	bool operator () (const GS::UniString& lhs, const GS::UniString& rhs) const;
};

}	// namespace GS


#endif
