#ifndef COMMONUSERINTERFACERESOURCES_HPP
#define COMMONUSERINTERFACERESOURCES_HPP

#pragma once

// from GSRoot
#include "RS.hpp"
#include "UniString.hpp"

// from DG
#include "DGDefs.h"

// from UD
#include "UDDefinitions.hpp"

namespace DG {
	class Icon;
}

namespace UD {
enum IconIds : short {
	TriangleClosedFilled = DG_FILLED_RIGHT_ICON,
	TriangleOpenFilled = DG_FILLED_DOWN_ICON,
#if defined (WINDOWS)
	OpenPopupIcon = DG_FILLED_RIGHT_ICON,
#else
	OpenPopupIcon = DG_FISHBONE_RIGHT_ICON,
#endif
	TreeViewIcon = 1101,
	ListViewIcon = 1112,
	FlatListViewIcon = 1102,
	MoreOptions = 1105,
	ImportIcon = 1107,
	ExportIcon = 1108,
	SmallWarning = 1109,
	HomeIcon = 1110,
	CheckIcon = 1111,
	SmallInfo = 1113,
	ColorPopupOriginalColorIcon = 1114,
	ClearSearchIcon = 2623,
};

enum CommonStringIds : short {
	OrString				= 1,
	MoreOptionsPopupString	= 2,
	OkString				= 3,
	CancelString			= 4,
	ChooseString			= 5,
	ContextMenuHelpString	= 6,
	AnyString				= 7,
	AnyStringInBrackets		= 8,
	VariousString			= 9,
	SearchString			= 10
};

enum CommonFixStringIds : short {
	OrFixString = 1
};

enum NameAlreadyExistsAlertString : short {
	NameAlreadyExistsAlertResId = 5010,
	NameAlreadyExistsAlertStrId = 4
};

	UD_DLL_EXPORT GS::UniString	GetResourceString (GSResID resID, Int32 index);
	UD_DLL_EXPORT GS::UniString	GetResourceCommonString (CommonStringIds index);
	UD_DLL_EXPORT GS::UniString	GetResourceCommonFixString (CommonFixStringIds index);
	UD_DLL_EXPORT short			GetResourceShortValue (GSResID resID, Int32 index, short defaultValue);
	UD_DLL_EXPORT DG::Icon		GetResourceIcon (IconIds index);
}


#endif
