// *****************************************************************************
// File:			DGTabPage.hpp
//
// Description:		Tab page class
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BM
//
// SG compatible
// *****************************************************************************

#ifndef DGTABPAGE_HPP
#define DGTABPAGE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGPanel.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class Dialog;
	class TabControl;
}


namespace DG {

// --- Class declarations ------------------------------------------------------

// --- TabPage -----------------------------------------------------------------

class DG_DLL_EXPORT TabPage: public Panel
{
private:
	bool				created;
	const TabControl*	parentControl;

	bool temporary = false;

	TabPage (const TabPage& tabPage);				// Disable
	TabPage&	operator= (const TabPage& tabPage);	// Disable

protected:
	TabPage ();

public:
	enum GrowType {
		NoGrow			= DG_DLG_NOGROW,
		HGrow			= DG_DLG_HGROW,
		VGrow			= DG_DLG_VGROW,
		HVGrow			= DG_DLG_HGROW | DG_DLG_VGROW
	};

	enum FixPoint {
		CenterPoint		= DG_CENTER,
		TopLeft			= DG_TOPLEFT,
		CenterLeft		= DG_CENTERLEFT,
		BottomLeft		= DG_BOTTOMLEFT,
		BottomCenter	= DG_BOTTOMCENTER,
		BottomRight		= DG_BOTTOMRIGHT,
		CenterRight		= DG_CENTERRIGHT,
		TopRight		= DG_TOPRIGHT,
		TopCenter		= DG_TOPCENTER
	};

	static short	GetOriginalWidth (GSResModule resModule, short resId);
	static short	GetOriginalHeight (GSResModule resModule, short resId);

	TabPage (const TabControl& tabControl, short tabItem, GSResModule resModule, short resId, GSResModule dialIconResModule);
	TabPage (const TabControl& tabControl, short tabItem, short width, short height);
	~TabPage ();

	Dialog*				GetParentDialog (void) const;
	const TabControl*	GetParentControl (void) const;

	void		SetGrowType (GrowType growType);
	GrowType	GetGrowType (void) const;

	void		SetFixPoint (FixPoint fixPoint);
	FixPoint	GetFixPoint (void) const;

	void		SetSize (short width, short height);
	void		SetWidth (short width);
	void		SetHeight (short height);

	Rect		GetRect (void) const;
	short		GetWidth (void) const;
	short		GetHeight (void) const;

	void		SetMinSize (short minWidth, short minHeight);
	void		SetMinWidth (short minWidth);
	void		SetMinHeight (short minHeight);

	short		GetMinWidth (void) const;
	short		GetMinHeight (void) const;

	bool		IsTabPage (void) const;

	virtual GSErrCode Store (GS::ObjectState& os) const;
};

}	// namespace DG

#endif
