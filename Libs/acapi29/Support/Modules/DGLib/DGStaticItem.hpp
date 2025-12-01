// *****************************************************************************
// File:			DGStaticItem.hpp
//
// Description:		StaticItem classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGSTATICITEM_HPP
#define DGSTATICITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGItemEventArgs.hpp"
#include "DGEventNotifier.hpp"
#include "DGItemProperty.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class StaticText;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- StaticItemEventProperty -------------------------------------------------

class DG_DLL_EXPORT StaticItemEventProperty
{
private:
	const DG::StaticItemMouseEventArg*	staticItemMsgData;

protected:
	explicit StaticItemEventProperty (const DG::EventArg& msgData);

public:
	virtual ~StaticItemEventProperty ();

	Point	GetMouseOffset (void) const;

	bool	IsCommandPressed (void) const;
	bool	IsOptionPressed (void) const;
	bool	IsShiftPressed (void) const;

	bool	IsLeftButtonPressed (void) const;
	bool	IsRightButtonPressed (void) const;
	bool	IsWheelButtonPressed (void) const;
};


// --- StaticTextClickEvent ----------------------------------------------------

class DG_DLL_EXPORT StaticTextClickEvent: public ItemClickEvent
{
friend class StaticTextObserver;			// To access protected constructor

protected:
	explicit StaticTextClickEvent (const ItemClickEvent& ev);

public:
	~StaticTextClickEvent ();

	StaticText*		GetSource (void) const;
};


// --- StaticTextDoubleClickEvent ----------------------------------------------

class DG_DLL_EXPORT StaticTextDoubleClickEvent: public ItemDoubleClickEvent
{
friend class StaticTextObserver;			// To access protected constructor

protected:
	explicit StaticTextDoubleClickEvent (const ItemDoubleClickEvent& ev);

public:
	~StaticTextDoubleClickEvent ();

	StaticText*		GetSource (void) const;
};


// --- StaticTextMouseMoveEvent ----------------------------------------------------------------------------------------

class DG_DLL_EXPORT StaticTextMouseMoveEvent:	public ItemMouseMoveEvent,
												public StaticItemEventProperty
{
friend class StaticTextObserver;				// To access protected constructor

protected:
	explicit StaticTextMouseMoveEvent (const ItemMouseMoveEvent& ev);

public:
	~StaticTextMouseMoveEvent ();

	StaticText*	GetSource (void) const;
};


// --- StaticTextObserver ------------------------------------------------------

class DG_DLL_EXPORT StaticTextObserver: public ItemObserver
{
protected:
	virtual	short	SpecClicked (const ItemClickEvent& ev) override;
	virtual	short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;
	virtual	short	SpecMouseMoved (const ItemMouseMoveEvent& ev) override;

	virtual void	StaticTextClicked (const StaticTextClickEvent& ev);
	virtual void	StaticTextDoubleClicked (const StaticTextDoubleClickEvent& ev);
	virtual void	StaticTextMouseMoved (const StaticTextMouseMoveEvent& ev, bool* noDefaultCursor);

public:
	StaticTextObserver ();
   ~StaticTextObserver ();
};


// --- StaticText --------------------------------------------------------------

class DG_DLL_EXPORT StaticText: public Item,
								public ItemFontProperty,
								public ItemTextProperty,
								public ItemColorProperty,
								public StaticItemNotifyHandler
{
public:
	enum VAlignType {
		VTop			= DG_IS_VTOP,
		VCenter			= DG_IS_VCENTER,
		VBottom			= DG_IS_VBOTTOM
	};

	enum Truncation {
		NoTruncate		= DG_IS_NOTRUNC,
		EndTruncate		= DG_IS_TRUNCEND,
		MiddleTruncate	= DG_IS_TRUNCMIDDLE
	};

	enum FrameType {
		NoFrame			= DG_FT_NONE,
		StaticFrame		= DG_FT_STATIC,
		ClientFrame		= DG_FT_CLIENT,
		ModalFrame		= DG_FT_MODAL
	};

private:
	void 	InitNotifiers ();

	virtual short	NotifyMouseMoveEvent (const StaticItemMouseEventArg& eventArg) override;

protected:
	StaticText ();
	StaticText (const Panel& panel, short item);

public:
	~StaticText ();

	EventNotifier<StaticText, const StaticItemMouseEventArg, short> onMouseMoved;

	void	Attach (StaticTextObserver& observer);
	void	Detach (StaticTextObserver& observer);

	void	EnableMouseMoveEvent (void);

	virtual Point	GetContentSize (void) const override;

	virtual GSErrCode Store (GS::ObjectState& os) const override;
};


// --- CenterText --------------------------------------------------------------

class DG_DLL_EXPORT CenterText: public StaticText
{
public:
	CenterText (const Panel& panel, short item);
	CenterText (const Panel& panel, const Rect& rect, FrameType type = NoFrame,
				VAlignType align = VTop, Truncation truncate = NoTruncate);
   ~CenterText ();

	virtual GSErrCode Store (GS::ObjectState& os) const override;
};


// --- LeftText ----------------------------------------------------------------

class DG_DLL_EXPORT LeftText: public StaticText
{
public:
	LeftText (const Panel& panel, short item);
	LeftText (const Panel& panel, const Rect& rect, FrameType type = NoFrame,
			  VAlignType align = VTop, Truncation truncate = NoTruncate);
   ~LeftText ();

	virtual GSErrCode Store (GS::ObjectState& os) const override;
};


// --- RightText ---------------------------------------------------------------

class DG_DLL_EXPORT RightText: public StaticText
{
public:
	RightText (const Panel& panel, short item);
	RightText (const Panel& panel, const Rect& rect, FrameType type = NoFrame,
			   VAlignType align = VTop, Truncation truncate = NoTruncate);
   ~RightText ();

	virtual GSErrCode Store (GS::ObjectState& os) const override;
};


// --- GroupBox ----------------------------------------------------------------

class DG_DLL_EXPORT GroupBox: public Item,
							  public ItemFontProperty,
							  public ItemTextProperty
{
public:
	enum GroupBoxType {
		Primary		= DG_GT_PRIMARY,
		Secondary	= DG_GT_SECONDARY
	};

	GroupBox (const Panel& panel, short item);
	GroupBox (const Panel& panel, const Rect& rect, GroupBoxType type);
   ~GroupBox ();

	virtual GSErrCode Store (GS::ObjectState& os) const override;
};


// --- Separator ---------------------------------------------------------------

class DG_DLL_EXPORT Separator: public Item
{
public:
	Separator (const Panel& panel, short item);
	Separator (const Panel& panel, const Rect& rect);
   ~Separator ();

	GSErrCode	Store (GS::ObjectState& os) const;
};

}	// namespace DG

#endif
