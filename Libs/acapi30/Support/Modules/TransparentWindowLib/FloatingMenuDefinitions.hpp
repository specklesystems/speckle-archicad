#ifndef GS_FLOATINGWINDOW_FLOATINGMENUDEFINITIONS_HPP
#define GS_FLOATINGWINDOW_FLOATINGMENUDEFINITIONS_HPP
#pragma once

namespace FloatingWindow {

enum class BoundingRectStyle {
	NORMALSTYLE,
	ROUNDEDSTYLE
};

enum class ArrowStyle {
	NOARROW,
	UPARROW,
	DOWNARROW,
	LEFTARROW,
	RIGHTARROW,
	UPLEFTARROW,
	DOWNLEFTARROW
};


enum class HighlightRefreshBehaviour {
	RefreshItemRectChanges,
	RefreshIfMouseMoved
};

}

#endif //GS_FLOATINGWINDOW_FLOATINGMENUDEFINITIONS_HPP
