// *****************************************************************************
// File:			DGTabControl.hpp
//
// Description:		TabControl classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGTABCONTROL_HPP
#define DGTABCONTROL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "UniString.hpp"

#include "DGItemProperty.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class TabPage;
	class NormalTab;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- NormalTabChangeEvent ----------------------------------------------------

class DG_DLL_EXPORT NormalTabChangeEvent: public ItemChangeEvent
{
friend class NormalTabObserver;				// To access protected constructor

private:
	short	previousItem;

protected:
	explicit NormalTabChangeEvent (const ItemChangeEvent& ev);

public:
	~NormalTabChangeEvent ();

	NormalTab*	GetSource (void) const;

	short	GetPreviousItem (void) const;
};


// --- NormalTabClickEvent -----------------------------------------------------

class DG_DLL_EXPORT NormalTabClickEvent: public ItemClickEvent
{
friend class NormalTabObserver;				// To access protected constructor

private:
	short	requestedItem;

protected:
	explicit NormalTabClickEvent (const ItemClickEvent& ev);

public:
	~NormalTabClickEvent ();

	NormalTab*	GetSource (void) const;

	short	GetRequestedItem (void) const;
};


// --- NormalTabObserver -------------------------------------------------------

class DG_DLL_EXPORT NormalTabObserver: public ItemObserver
{
protected:
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual	short	SpecClicked (const ItemClickEvent& ev) override;

	virtual void	NormalTabChanged (const NormalTabChangeEvent& ev);
	virtual void	NormalTabClicked (const NormalTabClickEvent& ev, bool* denyChange);

public:
	NormalTabObserver ();
   ~NormalTabObserver ();
};


// --- TabControl --------------------------------------------------------------

class DG_DLL_EXPORT TabControl: public Item
{
protected:
	TabControl ();
	TabControl (const Panel& panel, short item);

public:
	enum ItemType {
		AllItems	= DG_TAB_ALLITEMS,
		FirstItem	= DG_TAB_FIRSTITEM,
		LastItem	= DG_TAB_LASTITEM
	};

	~TabControl ();

	bool	AppendItem (void);
	bool	InsertItem (short tabItem);
	bool	DeleteItem (short tabItem);
	short	GetItemCount (void) const;

	void	EnableItem (short tabItem);
	void	DisableItem (short tabItem);
	void	SetItemStatus (short tabItem, bool enable);
	bool	IsItemEnabled (short tabItem) const;

	void	SelectItem (short tabItem);
	short	GetSelectedItem (void) const;

	void	SetClientSize (short width, short height);
	void	SetClientWidth (short width);
	void	SetClientHeight (short height);

	Rect	GetClientRect (void) const;
	short	GetClientWidth (void) const;
	short	GetClientHeight (void) const;

	Rect	ClientRectFromFrameRect (const Rect& frameRect) const;
	short	ClientWidthFromFrameWidth (short frameWidth) const;
	short	ClientHeightFromFrameHeight (short frameHeight) const;

	Rect	FrameRectFromClientRect (const Rect& clientRect) const;
	short	FrameWidthFromClientWidth (short clientWidth) const;
	short	FrameHeightFromClientHeight (short clientHeight) const;

	TabPage*	GetTabPage (short tabItem) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- NormalTab ---------------------------------------------------------------

class DG_DLL_EXPORT NormalTab: public TabControl,
							   public ItemFontProperty
{
public:
	NormalTab (const Panel& panel, short item);
	NormalTab (const Panel& panel, const Rect& rect);
   ~NormalTab ();

	void	Attach (NormalTabObserver& observer);
	void	Detach (NormalTabObserver& observer);

	void		SetItemText (short tabItem, const GS::UniString& text);
	GS::UniString	GetItemText (short tabItem) const;

	void		SetItemIcon (short tabItem, const DG::Icon& icon);
	DG::Icon	GetItemIcon (short tabItem) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- SimpleTab ---------------------------------------------------------------

class DG_DLL_EXPORT SimpleTab: public TabControl
{
public:
	enum FrameType {
		NoFrame		= DG_STS_NOFRAME,
		Frame		= DG_STS_FRAME
	};

	SimpleTab (const Panel& panel, short item);
	SimpleTab (const Panel& panel, const Rect& rect, FrameType frame = NoFrame);
   ~SimpleTab ();

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};

}	// namespace DG

#endif
