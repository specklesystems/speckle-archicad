// *****************************************************************************
// File:			DGPopUp.hpp
//
// Description:		PopUp classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGPOPUP_HPP
#define DGPOPUP_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "UniString.hpp"

#include "DGItemProperty.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class PopUp;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- PopUpChangeEvent --------------------------------------------------------

class DG_DLL_EXPORT PopUpChangeEvent: public ItemChangeEvent
{
friend class PopUpObserver;					// To access protected constructor

private:
	short	previousSelection;

protected:
	explicit PopUpChangeEvent (const ItemChangeEvent& ev);

public:
	~PopUpChangeEvent ();

	PopUp*	GetSource (void) const;

	short	GetPreviousSelection (void) const;
};


// --- PopUpObserver -----------------------------------------------------------

class DG_DLL_EXPORT PopUpObserver: public ItemObserver
{
protected:
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;

	virtual void	PopUpChanged (const PopUpChangeEvent& ev);

public:
	PopUpObserver ();
   ~PopUpObserver ();
};


// --- PopUp -------------------------------------------------------------------

class DG_DLL_EXPORT PopUp: public Item,
						   public ItemFontProperty,
						   public PopUpNotifyHandler
{
public:
	enum ItemType {
		AllItems	= DG_ALL_ITEMS,
		TopItem		= DG_POPUP_TOP,
		BottomItem	= DG_POPUP_BOTTOM
	};

private:
	void 	InitNotifiers ();

	virtual short	NotifyChangeEvent (const FontPopUpChangeEventArg& eventArg) override;

public:
	PopUp (const Panel& panel, short item);
	PopUp (const Panel& panel, const Rect& rect, short vSize, short textOffset);
   ~PopUp ();

	EventNotifier<PopUp, const FontPopUpChangeEventArg, short> onChanged;

	void	Attach (PopUpObserver& observer);
	void	Detach (PopUpObserver& observer);

	void	AppendItem (void);
	void	InsertItem (short popupItem);
	void	DeleteItem (short popupItem);
	short	GetItemCount (void) const;

	void	AppendSeparator (void);
	void	InsertSeparator (short popupItem);
	bool	IsSeparator (short popupItem) const;

	void		SetItemText (short popupItem, const GS::UniString& text);
	GS::UniString GetItemText (short popupItem) const;

	void		SetItemFontStyle (short popupItem, Font::Style style);
	Font::Style	GetItemFontStyle (short popupItem) const;

	void		SetItemIcon (short popupItem, const DG::Icon& icon);
	DG::Icon	GetItemIcon (short popupItem) const;

	void	EnableItem (short popupItem);
	void	DisableItem (short popupItem);
	void	SetItemStatus (short popupItem, bool enable);
	bool	IsItemEnabled (short popupItem) const;

	void	SetItemValue (short popupItem, DGUserData value);
	DGUserData	GetItemValue (short popupItem) const;

	void	SetItemObjectData (short popupItem, GS::Ref<GS::Object> object);
	GS::Ref<GS::Object>	GetItemObjectData (short popupItem) const;

	void		SetItemCharCode (short popupItem, GSCharCode charCode);
	GSCharCode	GetItemCharCode (short popupItem) const;

	void	SelectItem (short popupItem);
	short	GetSelectedItem (void) const;

	void	DisableDraw (void);
	void	EnableDraw (void);

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};

}	// namespace DG

#endif
