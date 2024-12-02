#ifndef WINTOOLTIPHANDLER_HPP
#define WINTOOLTIPHANDLER_HPP
#pragma once

#include "DG.h"

struct DGDialData;
struct DGItemData;

namespace DG {
class WinToolBarImpl;
}


class DG_DLL_EXPORT LearningTooltipWinHandler {
public:
	LearningTooltipWinHandler ();
	virtual ~LearningTooltipWinHandler ();

	static LearningTooltipWinHandler& Instance ();

	void ShowTooltip (DGDialData* dgDial, DGItemData* dgItem, short item);
	void ShowTooltip (DG::WinToolBarImpl* winToolBarImpl);
	void ShowStatusbarTooltip (HWND statusBarWnd);
	
	bool MoveHandlingRequired (DGItemData* dgItem);
	
	void HandleMoveEvent (DGDialData* dgDial, DGItemData* dgItem, short item);
	void HandleHideMessages (UINT wMsg);
	void HandleHideInputMessages (UINT wMsg);
	void HideTooltipOnPop ();

private:
	void ResetHoveredRect ();

	RECT hoveredRect;
	bool isMoveTracked;
};

#endif
