// *****************************************************************************
// File:			TrackerItemBase.hpp
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

#ifndef TRACKERITEMBASE_HPP
#define TRACKERITEMBASE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "ITrackerItem.hpp"
#include "Font.hpp"


namespace Tracking {

constexpr short				IconLeftGap		= 3;


// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT TrackerItemBase:	public ITrackerItem
{
friend class Tracker;

protected:
	Tracker*				parent;
	GS::UniString			text;
	DG::Icon				icon;
	GS::UniString			minimalEditText;
	bool					isPropertyValueSet;
	bool					visibility;
	bool					isEnabled;
	bool					acceptEnabled;
	bool					returnToRunningEnabled;

protected:
	// Functions called from derived classes
	DG::Rect				PlaceTrackerItem (DG::Palette& palette, short itemWidth[4]);
	void					DrawLine (const DG::Point& beg, const DG::Point& end, short width, const Gfx::Color& color, NewDisplay::NativeContext& context) const;
	void					DrawTextIntoRect (const GS::UniString& text, const TE::Font& font, const DG::Rect& textRect, NewDisplay::NativeContext& context) const;
	void					DrawIconIntoRect (const DG::Icon& icon, const Gfx::Color& color, const DG::Rect& iconRect, NewDisplay::NativeContext& context) const;
	short					MeasureTextWidth (const GS::UniString& text, const TE::Font& font) const;

	// Other protected methods
	virtual DG::Rect		GetActiveRectFromPoint (DG::Point point, short itemWidth[4], GS::UniString& toolTip) const override;
	virtual GS::UniString	GetToolTipText () const override;
	virtual DG::Icon		GetExtraIcon (short& width, short& height) const override;
	virtual void			ExtraIconClicked () override;

private:
	// Functions called from Tracker
	virtual void			SetParent (Tracker& tracker) override;
	virtual void			ClearParent () override;

public:
	TrackerItemBase ();
	virtual ~TrackerItemBase ();

	void					SetText (const GS::UniString& text);
	const GS::UniString&	GetText () const;
	void					SetIcon (const DG::Icon& icon);
	const DG::Icon&			GetIcon () const;

	void					Show (void);
	void					Hide (void);
	void					SetVisibility (bool show);
	virtual bool			IsVisible (void) const override;

	void					Enable (void);
	void					Disable (void);
	void					SetStatus (bool enable);
	virtual bool			IsEnabled (void) const override;

	void					BeginInput ();
	void					EndInput ();
	void					Activate ();

	virtual bool			AcceptEnabled (void) const override;
	virtual bool			ReturnToRunningEnabled (void) const override;

	void					SetAcceptEnabled (const bool value);
	void					SetReturnToRunningEnabled (const bool value);
};

}	//namespace Tracker

#endif
