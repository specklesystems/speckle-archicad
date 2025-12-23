// *********************************************************************************************************************
// Callback functions for the VBElemDialogs module
//
// Module:			VBElemDialogs
// Namespace:		TBUI
// Contact person:	PT
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (VBELEMDIALOGSCALLBACKS_H)
#define VBELEMDIALOGSCALLBACKS_H

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace TBUI {
	class ToolBoxItemUIData;
}

namespace EDB {
	class Tool;
}


namespace TBUI {

// --- Type definitions	------------------------------------------------------------------------------------------------

extern "C" {
	typedef void	PostChangeRequestFromInfoBoxProc (const EDB::Tool &tool,
													  bool fromFavoriteApply,
													  bool applyFavoriteText,
													  bool applyToSelectionAndGlobalDefault);
}


struct CallBackTbl {
	PostChangeRequestFromInfoBoxProc*	postchangerequestfrominfobox;
};

}	// namespace TBUI

#endif
