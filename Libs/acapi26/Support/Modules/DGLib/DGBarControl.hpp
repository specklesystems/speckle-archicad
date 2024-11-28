// *****************************************************************************
// File:			DGBarControl.hpp
//
// Description:		BarControl classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGBARCONTROL_HPP
#define DGBARCONTROL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGItem.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class BarControl;
	class ScrollBar;
	class IntEdit;
	class PosIntEdit;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- BarControlChangeEvent ---------------------------------------------------

class DG_DLL_EXPORT BarControlChangeEvent: public ItemChangeEvent
{
friend class BarControlObserver;			// To access protected constructor

private:
	Int32	previousValue;

protected:
	explicit BarControlChangeEvent (const ItemChangeEvent& ev);

public:
	~BarControlChangeEvent ();

	BarControl*		GetSource (void) const;

	Int32	GetPreviousValue (void) const;
};


// --- BarControlTrackEvent ----------------------------------------------------

class DG_DLL_EXPORT BarControlTrackEvent: public ItemTrackEvent
{
friend class BarControlObserver;			// To access protected constructor

protected:
	explicit BarControlTrackEvent (const ItemTrackEvent& ev);

public:
	~BarControlTrackEvent ();

	BarControl*		GetSource (void) const;
};


// --- BarControlObserver ------------------------------------------------------

class DG_DLL_EXPORT BarControlObserver: public ItemObserver
{
protected:
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual	short	SpecTrackEntered (const ItemTrackEvent& ev) override;
	virtual	short	SpecTracked (const ItemTrackEvent& ev) override;
	virtual	short	SpecTrackExited (const ItemTrackEvent& ev) override;

	virtual void	BarControlChanged (const BarControlChangeEvent& ev);
	virtual void	BarControlTrackEntered (const BarControlTrackEvent& ev);
	virtual void	BarControlTracked (const BarControlTrackEvent& ev);
	virtual void	BarControlTrackExited (const BarControlTrackEvent& ev);

public:
	BarControlObserver ();
   ~BarControlObserver ();
};


// --- ScrollBarChangeEvent ----------------------------------------------------

class DG_DLL_EXPORT ScrollBarChangeEvent: public ItemChangeEvent
{
friend class ScrollBarObserver;				// To access protected constructor

private:
	Int32	previousValue;

protected:
	explicit ScrollBarChangeEvent (const ItemChangeEvent& ev);

public:
	~ScrollBarChangeEvent ();

	ScrollBar*		GetSource (void) const;

	Int32	GetPreviousValue (void) const;
};


// --- ScrollBarTrackEvent -----------------------------------------------------

class DG_DLL_EXPORT ScrollBarTrackEvent: public ItemTrackEvent
{
friend class ScrollBarObserver;				// To access protected constructor

protected:
	explicit ScrollBarTrackEvent (const ItemTrackEvent& ev);

public:
	~ScrollBarTrackEvent ();

	ScrollBar*	GetSource (void) const;

	bool	IsLineUp (void) const;
	bool	IsLineLeft (void) const;
	bool	IsLineDown (void) const;
	bool	IsLineRight (void) const;

	bool	IsPageUp (void) const;
	bool	IsPageLeft (void) const;
	bool	IsPageDown (void) const;
	bool	IsPageRight (void) const;

	bool	IsTop (void) const;
	bool	IsLeft (void) const;
	bool	IsBottom (void) const;
	bool	IsRight (void) const;

	bool	IsThumbTrack (void) const;
};


// --- ScrollBarObserver -------------------------------------------------------

class DG_DLL_EXPORT ScrollBarObserver: public ItemObserver
{
protected:
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual	short	SpecTrackEntered (const ItemTrackEvent& ev) override;
	virtual	short	SpecTracked (const ItemTrackEvent& ev) override;
	virtual	short	SpecTrackExited (const ItemTrackEvent& ev) override;

	virtual void	ScrollBarChanged (const ScrollBarChangeEvent& ev);
	virtual void	ScrollBarTrackEntered (const ScrollBarTrackEvent& ev);
	virtual void	ScrollBarTracked (const ScrollBarTrackEvent& ev);
	virtual void	ScrollBarTrackExited (const ScrollBarTrackEvent& ev);

public:
	ScrollBarObserver ();
   ~ScrollBarObserver ();
};


// --- BarControl --------------------------------------------------------------

class DG_DLL_EXPORT BarControl: public Item
{
protected:
	BarControl ();
	BarControl (const Panel& panel, short item);

public:
	~BarControl ();

	void	Attach (BarControlObserver& observer);
	void	Detach (BarControlObserver& observer);

	void	SetMin (Int32 min);
	void	SetMax (Int32 max);
	void	SetValue (Int32 value);

	Int32	GetMin (void) const;
	Int32	GetMax (void) const;
	Int32	GetValue (void) const;

    virtual GSErrCode Store (GS::ObjectState& os) const override;
};


// --- SingleSpin --------------------------------------------------------------

class DG_DLL_EXPORT SingleSpin: public BarControl
{
public:
	SingleSpin (const Panel& panel, short item);
	SingleSpin (const Panel& panel, const Rect& rect);
   ~SingleSpin ();
};


// --- EditSpin ----------------------------------------------------------------

class DG_DLL_EXPORT EditSpin: public BarControl
{
public:
	EditSpin (const Panel& panel, short item);
	EditSpin (const Panel& panel, const Rect& rect, const PosIntEdit& attachedEdit);
	EditSpin (const Panel& panel, const Rect& rect, const IntEdit& attachedEdit);
   ~EditSpin ();
};


// --- Slider ------------------------------------------------------------------

class DG_DLL_EXPORT Slider: public BarControl,
							public ItemTrackNotifier<Slider>
{
public:
	enum SliderType {
		BottomRight	= DG_SL_BOTTOMRIGHT,
		TopLeft		= DG_SL_TOPLEFT
	};

	Slider (const Panel& panel, short item);
	Slider (const Panel& panel, const Rect& rect, short ticks, SliderType type = BottomRight);
   ~Slider ();

	GSErrCode	Store (GS::ObjectState& os) const;
};


// --- ScrollBar ---------------------------------------------------------------

class DG_DLL_EXPORT ScrollBar: public Item,
							   public ItemTrackNotifier<ScrollBar>
{
public:
	enum ThumbType {
		Normal			= DG_SB_NORMAL,
		Proportional	= DG_SB_PROPORTIONAL
	};

	enum FocusableType {
		Focusable		= 0,
		NonFocusable	= DG_SB_NONFOCUSABLE
	};

	enum AutoScrollType {
		AutoScroll		= 0,
		NoAutoScroll	= DG_SB_NOAUTOSCROLL
	};

	ScrollBar (const Panel& panel, short item);
	ScrollBar (const Panel& panel, const Rect& rect, ThumbType thumb = Normal, FocusableType focus = Focusable,
			   AutoScrollType autoScroll = AutoScroll);
   ~ScrollBar ();

	void	Attach (ScrollBarObserver& observer);
	void	Detach (ScrollBarObserver& observer);

	void	SetMin (Int32 min);
	void	SetMax (Int32 max);
	void	SetValue (Int32 value);

	Int32	GetMin (void) const;
	Int32	GetMax (void) const;
	Int32	GetValue (void) const;

	void	SetPageSize (Int32 pageSize);
	Int32	GetPageSize (void) const;

	GSErrCode	Store (GS::ObjectState& os) const;
};


// --- ProgressBar -------------------------------------------------------------

class DG_DLL_EXPORT ProgressBar: public Item
{
public:
	enum FrameType {
		NoFrame		= DG_FT_NONE,
		StaticFrame	= DG_FT_STATIC,
		ClientFrame	= DG_FT_CLIENT,
		ModalFrame	= DG_FT_MODAL
	};

	ProgressBar (const Panel& panel, short item);
	ProgressBar (const Panel& panel, const Rect& rect, FrameType type = NoFrame);
   ~ProgressBar ();

	void	SetMin (Int32 min);
	void	SetMax (Int32 max);
	void	SetValue (Int32 value);

	Int32	GetMin (void) const;
	Int32	GetMax (void) const;
	Int32	GetValue (void) const;

	GSErrCode	Store (GS::ObjectState& os) const;
};

}	//	namespace DG

#endif
