// *****************************************************************************
// File:			Tracker.hpp
//
// Description:
//
// Project:			ARCHICAD
//
// Namespace:
//
// Contact person:	NZ, DG, BL
//
// SG compatible
// *****************************************************************************

#ifndef TRACKER_HPP
#define TRACKER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "IDoubleProperty.hpp"

#include "Array.hpp"
#include "Color.hpp"

#include "DGItem.hpp"
#include "DGPanel.hpp"
#include "DGDialog.hpp"
#include "DGUtility.hpp"

#include "DGLowLevelKeyboardHandling.hpp"

#include "DisposableObject.hpp"

#include "Hint.hpp"

#include "TransparentWindow.hpp"

#if defined(_MSC_VER)
#pragma warning (disable: 4512)
#endif

// --- Predeclarations ---------------------------------------------------------

namespace Tracking {
	class TrackerEditPalette;
	class ITrackerItem;
	class LanderTracker;
}


namespace Tracking {

const short				IconLeftGap		= 3;


// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT Tracker:	public	TransparentWindow,
									private DG::PanelObserver,
									private DG::ItemObserver
{
friend class TrackerItemBase;
friend class ITrackerItem;

public:
	enum class ValueHandlingOnDeactivate {
		Accept,
		Reject
	};

	enum class PositionHandingOnDeactivate {
		KeepAsItIs,
		RemoveFromIdealPosition
	};


	typedef GS::ConstForwardIterator<ITrackerItem*>	ConstItemIterator;
	typedef GS::ForwardIterator<ITrackerItem*>		ItemIterator;

	class TRANSPARENTWINDOWLIB_DLL_EXPORT HintGuard {
	private:
		Tracker& trackerToGuard;
		Hint originalHint;

	public:
		HintGuard (Tracker& trackerToGuard, Hint newHint);
		virtual ~HintGuard ();
	};

private:
	class InEditKeyboardHandler: public DG::LowLevelKeyboardHandler
	{
	private:
		Tracker& tracker;

	protected:
		virtual	DG::EventHandlerResultType	KeyPressed (const DG::Key::Code& code, DG::Item** item) override;
		virtual DG::EventHandlerResultType	KeyPressed (const DG::Key::Modifier& modifier, DG::Item** item) override;

	public:
		InEditKeyboardHandler (Tracker& tracker);
		virtual ~InEditKeyboardHandler ();
	};

	class RunningModeKeyboardHandler: public DG::LowLevelKeyboardHandler
	{
	private:
		Tracker& tracker;

	protected:
		virtual	DG::EventHandlerResultType	KeyPressed (const DG::Key::Code& code, DG::Item** item) override;

	public:
		RunningModeKeyboardHandler (Tracker& tracker);
		virtual ~RunningModeKeyboardHandler ();
	};

	class TRANSPARENTWINDOWLIB_DLL_EXPORT IdleGuard {
	private:
		const Tracker& trackerToGuard;

	public:
		IdleGuard (const Tracker& trackerToGuard);
		virtual ~IdleGuard ();
	};

private:
	GS::Array<ITrackerItem*>	trackerItems;

	static Gfx::Color			foregroundColor;
	static Gfx::Color			backgroundColor;
	static Gfx::Color			frameColor;
	static float				opacity;
	static bool					drawFrame;
	static bool					smallFont;

	bool						useCustomBkgColor;
	bool						useCustomForeGroundColor;
	bool						useCustomFrameColor;
	bool						useCustomDrawFrame;
	Gfx::Color					customBkgColor;
	Gfx::Color					customForeGroundColor;
	Gfx::Color					customFrameColor;
	bool						customDrawFrame;

//////////////////////////////////////////////////
//	DG::Rect					rect;
//	DG::NativePoint				position;
//	short						width;	// Logical units
//	short						height;	// Logical units
//////////////////////////////////////////////////

	TrackerEditPalette*			palette;
	DG::Icon					acceptInput;
	DG::Icon					returnToRunnigMode;
	DG::Icon					maximalizeTracker;

	GS::UniString				acceptInputToolTipString;
	GS::UniString				returnToRunnigModeToolTipString;
	GS::UniString				maximalizeTrackerToolTipString;
	GS::UniString				nullToolTipString;

	short						itemWidth[4];

	ITrackerItem*				activeItemPtr;
	bool						hidden;
	bool						showParameterNames;
	bool						allwaysShowParameterNames;
	DG::Rect					hoverRect;
	GS::UniString				toolTipString;
	InEditKeyboardHandler		inEditKeyboardHandler;
	RunningModeKeyboardHandler	runningModeKeyboardHandler;
	Hint						hint;
	float						globalAlpha;

	bool						isEditTrackerMinimized;
	bool						showAll;
	DG::Rect					maximizeIconRect;
	mutable Int32				disableDeactivateOnFocusLost;
	bool						showReturnToRunningModeButton;
	ITrackerItem*				sendClickToWhileNextIdle;
	LanderTracker*				lander;

protected:
	GS::UniString		ToolTipTextRequested () const override;
	void				ShowReturnToRunningModeButton (bool show);
	void				RefreshSize ();

	// from TrackerImpl
	void				MouseMoveEventHandler (const DG::Point& point);
	void				MouseClickEventHandler (const DG::Point& point);
	void				MouseRClickEventHandler (const DG::Point& point);

private:
	DG::NativeRect		CalculatePaletteScreenRect () const;
	Tracker&			GetReference ();
	void				MoveTrackerAnimated (const DG::NativePoint& moveTo, short milliSec);
	void				Fade (const float endAlpha, short milliSec);
	void				CleanUpAfterEditMode ();
	void				DrawHoverRect (NewDisplay::NativeContext& context, const DG::Rect& hoverRect);
	void				Draw (NewDisplay::NativeContext& context, const DG::Rect& maximalizeIconRect);
	void				Draw ();
	void				AttachToAllPaletteItems ();
	void				DetachFromAllPaletteItems ();
	void				HandleActivableItemSetting ();

	// from KeyboardHandlers
	void				DeactivateActiveItemEditMode ();
	DG::Item*			ActivateActiveItemEditMode (DG::Palette& palette, short itemWidth[4]);

	// DG event handlers
	virtual void		PanelIdle (const DG::PanelIdleEvent& ev) override;
	virtual	void		PanelBackgroundPaint (const DG::PanelBackgroundPaintEvent& ev, bool* processed) override;
	virtual	short		SpecTrackEntered (const DG::ItemTrackEvent& ev) override;
	virtual	short		SpecTrackExited (const DG::ItemTrackEvent& ev) override;

	// from ITrackerItem
	bool				SelectItem (ITrackerItem* trackerItem);
	void				ItemDeleted (ITrackerItem* item);
	void				ShowAllItemsWhileEdit ();

	// from TrackerImpl
	DG::NativePoint		MapPointToScreen (const DG::Point& pointToMap) const;

	// Template methods to make user application being able to extend its functionality
	virtual void		OnInputAccept (const ITrackerItem* /*acceptedItem*/) const {}
	virtual void		OnActivateEditMode () const {}
	virtual void		OnDeactivateEditMode () const {}
	virtual void		OnContextMenuClicked () const {}
	virtual void		OnTrackerMaximalized () const {}

	virtual DG::NativePoint		GetIdealTrackerPosition (const DG::NativePoint& pos, short /*width*/, short /*height*/) const { return pos; }
	virtual DG::NativePoint		GetTrackerPosition (void) const { return GetPosition (); }

	virtual bool		IsDirectInputEnabled () const { return true; }
	virtual void		OnActiveItemChanged () const {}

	// Disable
	Tracker (const Tracker&);
	Tracker& operator= (const Tracker&);

public:
	Tracker (/*bool layered = true*/);
	virtual ~Tracker ();

	void				AddItem (ITrackerItem* trackerItem);
	void				SwapItems (ITrackerItem* trackerItem1, ITrackerItem* trackerItem2); // Mindkettonek hozza kell lennie adva
	ConstItemIterator	EnumerateAllItems () const;
	ItemIterator		EnumerateAllItems ();
	ConstItemIterator	EnumerateVisibleItems () const;
	ItemIterator		EnumerateVisibleItems ();
	const ITrackerItem*	GetSelectedItem () const;
	ITrackerItem*		GetSelectedItem ();

	virtual void		Synchronize ();
	virtual void		RefreshFade ();

	void				SetCustomBorders (short left, short right, short top, short bottom);

	DG::NativeRect			GetRect (void) const;
	void					SetPosition (const DG::NativePoint& point, bool animated = false, short milliSec = -1);

	void				MoveToVisiblePosition ();
	void				StayInVisiblePosition ();

	DG::Item* 			ActivateEditMode ();
	void				DeactivateEditMode (ValueHandlingOnDeactivate valueHandling, const GS::Optional<const ITrackerItem*>& acceptedItemPtr, PositionHandingOnDeactivate positiohHandling);
	bool				IsInEditMode () const;
	bool				IsTrackerEditWindowActive () const;
	void				SetNextActivableItem ();
	void				SetPrevActivableItem ();
	bool				IsFirstActivableItemActive ();
	bool				IsLastActivableItemActive ();
	void				SetFirstActivableItem ();
	void				SetLastActivableItem ();

	void				Hide () override;
	void				Show () override;
	bool				IsVisible () const override;

	void				SetGlobalOpacity (float opacity);
	void				SetShowParameterNames (bool showParameterNames);
	void				SetAllwaysShowParameterNames (bool allwaysShowParameterNames);
	void				SetEditTrackerSizePreference (bool isEditTrackerMinimizedParam);

	static void			SetForegroundColor (const Gfx::Color&);
	static void			SetBackgroundColor (const Gfx::Color&);
	static void			SetFrameColor (const Gfx::Color&);
	static Gfx::Color	GetDefaultForegroundColor ();
	static Gfx::Color	GetDefaultBackgroundColor ();
	static Gfx::Color	GetDefaultFrameColor ();
	static void			SetOpacity (float);
	static void			SetDrawFrame (bool);
	static void			SetSmallFont (bool);

	Gfx::Color			GetForegroundColor ();
	Gfx::Color			GetBackgroundColor ();
	Gfx::Color			GetFrameColor ();
	static float		GetOpacity ();
	bool				GetDrawFrame ();

	static bool			GetSmallFont ();

	void				SetCustomBackgroundColor (const Gfx::Color& color);
	void				SetCustomForeGroundColor (const Gfx::Color& color);
	void				SetCustomFrameColor (const Gfx::Color& color);
	void				SetCustomDrawFrame (bool drawFrameToSet);

	bool				IsDecimalSeparator (const DG::Key::Code& code) const;

	static	short		ReadTrackerTimesPref (const GS::UniString& name, Int32 defaultValue);
};

class	TrackerEditPalette: public DG::Palette,
							public GS::DisposableObject
{
public:
			 TrackerEditPalette ();
	virtual ~TrackerEditPalette ();
};

}	//namespace Tracker

#endif
