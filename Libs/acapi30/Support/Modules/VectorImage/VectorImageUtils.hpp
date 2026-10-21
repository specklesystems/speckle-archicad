#ifndef	_VectorImageUtils_H_
#define	_VectorImageUtils_H_

#pragma once

#include "Definitions.hpp"
#include "ProfileAdditionalInfo.hpp"

namespace AC22HatchAddInfo {

const Int32	AC22ProfileItemVersion = ProfileItemVersion_2;	// last version in AC22

struct ProfileEdgeData {
enum { IsVisibleLineFlag = 0x00000008 };

	short	material;
	short	pen;
	short	lineType;
	short	filler;			//not in use (AACS)
	Int32	flags;

	void	SetFlag			(bool value, Int32 flag) { flags = (value) ? flags | flag : flags & ~flag; }
	bool	IsVisibleLine	(void) const { return (flags & IsVisibleLineFlag) != 0; }
	void	SetVisibleLine	(bool value) { SetFlag (value, IsVisibleLineFlag); }
	void	IV	(GS::PlatformSign from, GS::PlatformSign to);
};

struct ProfileItem {
	Int32						profileItemVersion = AC22ProfileItemVersion;
	Int32						obsoletePriorityValue;
	Int32						flags;
	short						cutEndLinePen;
	short						cutEndLineType;
	SkinProjectionProperties	skinProjectionProperties;

	void	IV (GS::PlatformSign from, GS::PlatformSign to);
};

}

VI_DLL_EXPORT
GSErr VI_CALL	Convert22HatchAddInfo_To_23HatchAddInfo (GSPtr ac22AddInfo, GSPtr& ac23AddInfo, UInt32 profileEdgeCount);

#endif
