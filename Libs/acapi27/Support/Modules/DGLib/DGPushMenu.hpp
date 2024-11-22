// *****************************************************************************
// File:			DGPushMenu.hpp
//
// Description:		PushMenu classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGPUSHMENU_HPP
#define DGPUSHMENU_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGItem.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class PushMenu;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- PushMenuCheckChangeEvent ------------------------------------------------

class DG_DLL_EXPORT PushMenuCheckChangeEvent: public ItemChangeEvent
{
friend class PushMenuObserver;				// To access protected constructor

private:
	bool	stateChanged;
	short	previousMenuItem;

protected:
	explicit PushMenuCheckChangeEvent (const ItemChangeEvent& ev);

public:
	~PushMenuCheckChangeEvent ();

	PushMenu*	GetSource (void) const;

	bool	WasStateChange (void) const;
	short	GetPreviousMenuItem (void) const;
};


// --- PushMenuRadioChangeEvent ------------------------------------------------

class DG_DLL_EXPORT PushMenuRadioChangeEvent: public ItemChangeEvent
{
friend class PushMenuObserver;				// To access protected constructor

private:
	bool	selectionChanged;
	Item*	previousSelection;
	short	previousMenuItem;

protected:
	explicit PushMenuRadioChangeEvent (const ItemChangeEvent& ev);

public:
	~PushMenuRadioChangeEvent ();

	PushMenu*	GetSource (void) const;

	bool	WasSelectionChange (void) const;
	Item*	GetPreviousGroupSelection (void) const;
	short	GetPreviousMenuItem (void) const;
};


// --- PushMenuDoubleClickEvent ------------------------------------------------

class DG_DLL_EXPORT PushMenuDoubleClickEvent: public ItemDoubleClickEvent
{
friend class PushMenuObserver;				// To access protected constructor

protected:
	explicit PushMenuDoubleClickEvent (const ItemDoubleClickEvent& ev);

public:
	~PushMenuDoubleClickEvent ();

	PushMenu*	GetSource (void) const;
};


// --- PushMenuObserver --------------------------------------------------------

class DG_DLL_EXPORT PushMenuObserver: public ItemObserver
{
protected:
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual	short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;

	virtual void	PushMenuChanged (const PushMenuCheckChangeEvent& ev);
	virtual void	PushMenuChanged (const PushMenuRadioChangeEvent& ev);
	virtual void	PushMenuDoubleClicked (const PushMenuDoubleClickEvent& ev);

public:
	PushMenuObserver ();
   ~PushMenuObserver ();
};


// --- PushMenu ----------------------------------------------------------------

class DG_DLL_EXPORT PushMenu: public Item
{
protected:
	PushMenu ();
	PushMenu (const Panel& panel, short item);

public:
	~PushMenu ();

	void	Attach (PushMenuObserver& observer);
	void	Detach (PushMenuObserver& observer);

	void	SetItemCount (short itemCount);
	short	GetItemCount (void) const;

	void	SelectItem (short menuItem);
	short	GetSelectedItem	(void) const;

	void	EnableItem (short menuItem);
	void	DisableItem (short menuItem);
	void	SetItemStatus (short menuItem, bool enable);
	bool	IsItemEnabled (short menuItem) const;

	void		SetItemIcon (short menuItem, const DG::Icon& icon);
	DG::Icon	GetItemIcon (short menuItem) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- PushMenuCheck -----------------------------------------------------------

class DG_DLL_EXPORT PushMenuCheck: public PushMenu
{
public:
	enum ButtonForm {
		BevelEdge			= DG_BA_BEVEL,
		RoundedBevelEdge	= DG_BA_ROUNDEDBEVEL
	};

	PushMenuCheck (const Panel& panel, short item);
	PushMenuCheck (const Panel& panel, const Rect& rect, ButtonForm form = BevelEdge);
   ~PushMenuCheck ();

	void	Check (void);
	void	Uncheck (void);
	void	SetState (bool check);
	bool	IsChecked (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- PushMenuRadio -----------------------------------------------------------

class DG_DLL_EXPORT PushMenuRadio: public PushMenu
{
public:
	PushMenuRadio (const Panel& panel, short item);
	PushMenuRadio (const Panel& panel, const Rect& rect, short groupId);
   ~PushMenuRadio ();

	void	Select (void);
	bool	IsSelected (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};

}	// namespace DG

#endif
