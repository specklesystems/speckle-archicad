// *****************************************************************************
// File:			ITrackerItem.hpp
//
// Description:
//
// Project:			ARCHICAD
//
// Namespace:
//
// Contact person:	NZ, DG
//
// SG compatible
// *****************************************************************************

#ifndef ITRACKERITEM_HPP
#define ITRACKERITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "DGEditControl.hpp"
#include "DGModule.hpp"

#include "Hint.hpp"


namespace Tracking {

class Tracker;


// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT ITrackerItem
{
friend class Tracker;

protected:
	// Functions called from derived classes to access private data and methods in Tracker
	void					NotifyParentAboutBeingDeleted (Tracker& parent);
	void					SetParentShowAll (Tracker& parent);
	Hint					GetParentHint (Tracker& parent) const;
	bool					SelectInParent (Tracker& parent);

private:
	// Functions called from Tracker
	virtual void			SetParent (Tracker& tracker) = 0;
	virtual void			ClearParent () = 0;
	virtual void			Draw (NewDisplay::NativeContext& context, const DG::Rect& itemRect, bool selected, short itemWidth[4]) = 0;
	virtual void			Synchronize () const = 0;
	virtual DG::Item*		ActivateEditMode (DG::Palette& palette, short itemWidth[4]) = 0;
	virtual void			DeactivateEditMode () = 0;
	virtual short			GetColumnWidth (short (&itemWidth)[4]) const = 0;
	virtual DG::Rect		GetActiveRectFromPoint (DG::Point point, short itemWidth[4], GS::UniString& toolTip) const = 0;
	virtual void			FocusDefaultItem () = 0;
	virtual DG::Icon		GetExtraIcon (short& width, short& height) const = 0;
	virtual void			ExtraIconClicked () = 0;

public:
	virtual				   ~ITrackerItem ();

	virtual GS::UniString	GetToolTipText () const = 0;
	virtual short			GetHeight () const = 0;

	virtual bool			IsInInput () const = 0;
	virtual bool			IsVisible (void) const = 0;
	virtual bool			IsEnabled (void) const = 0;

	virtual bool			AcceptEnabled (void) const = 0;
	virtual bool			ReturnToRunningEnabled (void) const = 0;
};

}	//namespace Tracker

#endif
