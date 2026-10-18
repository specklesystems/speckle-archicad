#ifndef ISYMBOL_HPP
#define ISYMBOL_HPP

#pragma once

#include "Definitions.hpp"
#include "VectorImageExport.h"

// After version 36 this is only the version of the Sy_Head, all other symbols have an own version. The Sy_Head contains all the version informations.
#define Curr_Sy2DVersion 36		// 36: 2015.10.09 B-405 ExtendedPen (Initial version of non binary read/write)
								// 35: 2014.07.18 B-318 SkinArea in ProfileItem
								// 34: 2014.04.01 B-298
								// 33: 2014.09.17 DBASSERT(sy_fragmentIdx >= 1 && sy_fragmentIdx <= 16)
								// 32: 2013.08.21 B-270 M2
								// 31: 2013.06.13 VisibleCutEndLinesFlag in ProfileItem
								// 30: 2012.06.29 Building Material in SyHatch
								// 29: 2011.05.10 arcParam to SyHot
								// 28: 2008.09.25 add PolyLine to VectorImage
								// 27: 2008.09.25
								// 26: 2008.09.25
								// 25: 2008.09.11
								// 24: 2007.09.03
								// 23: 2005.06.24
								// 22: 2005.06.24
								// 20: 2005.06.24
								// 19: 2005.01.20.
								// 18: 2004.02.28.
								// 17: 2001.07.13.
								// 16: 1999.03.11.
								// 15: 1998.06.16.
								// 14: 1995.10.24.
								// 13: 1995.08.17.

enum {
	InitialVersionOfNonBinaryReadWrite = 36
};

enum Sy3DInformation {
	SySymbolic				= 0,
	SyProj					= 1,
	SyProj_WithHolerepl		= 2,
	SyProj_SectCut			= 3,
	SyProj_UseOwnerReno		= 4,
	SyProj_UseOppositeReno	= 5,
	SySide_Holerepl			= 6,
	SySide_SectCut			= 7,
	SySide_NonShadedShadow	= 8
};

enum SyHatchIsForSelection {
	SyNormalHatch			= 0, 
	SySelectionOnlyHatch	= 1
}; 


enum SyEnum : UInt8 {
	SyEnd			= 0,
	SyHead			= 1,
	SyHots			= 2,
	SyLine			= 3,
	SyArc			= 4,
	SyText			= 5,
	SyHatch			= 6,
	SySpline		= 7,
	SyFont			= 8,
	SyPicture		= 9,
	SyPixMap		= 10,
	SyRichText		= 11,
	SyPolyLine		= 12,
	SyPointCloud	= 13,
	SyInvalid		= 14		// Always the biggest!
};

/*
class ISymbol {

public:
	virtual SyEnum GetSyType () = 0;

	virtual GSErrCode ReadBin (GS::IChannel& oc, short version) = 0;

	virtual GSErrCode Write (GS::OChannel& oc, short version) const = 0;
	virtual GSErrCode Read (GS::IChannel& oc, short version) = 0;

	virtual GSErrCode WriteXML (GS::XMLOChannel& oc, short version) const = 0;
	virtual GSErrCode ReadXML (GS::XMLIChannel& oc, short version) = 0;
};
*/

#endif // ISYMBOL_HPP
