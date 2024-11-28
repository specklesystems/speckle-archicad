// *********************************************************************************************************************
// File:			UCPopup.hpp
//
// Description:		Popup control classes (UC263)
//
// Project:			GRAPHISOFT User Control Library (UCLib)
//
// Namespace:		UC
//
// Contact person:	VM
//
// SG compatible
// *********************************************************************************************************************

#ifndef UCPOPUP_HPP
#define UCPOPUP_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "Array.hpp"
#include "DGModule.hpp"
#include "DGItemProperty.hpp"
#include "DGUserControl.hpp"
#include "UC.h"


namespace UC {

// === Popup item class ================================================================================================

// --- Class declaration -----------------------------------------------------------------------------------------------

class PopupItem
{
private:
	GS::UniString		itemText;
	DG::Icon			icon;
	bool				isChecked;
	bool				isEnabled;
	DG::Font::Size		textSize;
	DG::Font::Style		textStyle;
	bool				isSeparator;
	void*				itemData;
	GS::Ref<GS::Object>	userObject;

public:
	PopupItem (bool separatorItem = false);
   ~PopupItem ();

	void				SetIcon (DG::Icon icon);
	const DG::Icon		GetIcon (void) const;

	void				SetText (GS::UniString text);
	const GS::UniString	GetText (void) const;

	void				SetTextSize (DG::Font::Size size);
	DG::Font::Size		GetTextSize (void) const;

	void				SetTextStyle (DG::Font::Style style);
	DG::Font::Style		GetTextStyle (void) const;

	void				SetData (void* data);
	void*				GetData (void) const;

	void				SetObjectData (GS::Ref<GS::Object> object);
	GS::Ref<GS::Object>	GetObjectData (void) const;

	void				Check (void);
	void				Uncheck (void);
	bool				IsChecked (void) const;

	void				Enable (void);
	void				Disable (void);
	bool				IsEnabled (void) const;

	bool				IsSeparator (void) const;
};


// --- Inline implementation -------------------------------------------------------------------------------------------

inline const DG::Icon	PopupItem::GetIcon (void) const
{
	return icon;
}


inline const GS::UniString		PopupItem::GetText (void) const
{
	return itemText;
}


inline DG::Font::Size	PopupItem::GetTextSize (void) const
{
	return textSize;
}


inline DG::Font::Style	PopupItem::GetTextStyle (void) const
{
	return textStyle;
}


inline void*	PopupItem::GetData (void) const
{
	return itemData;
}


inline GS::Ref<GS::Object>	PopupItem::GetObjectData (void) const
{
	return userObject;
}

inline bool		PopupItem::IsChecked (void) const
{
	return isChecked;
}


inline bool		PopupItem::IsEnabled (void) const
{
	return isEnabled;
}


inline bool		PopupItem::IsSeparator (void) const
{
	return isSeparator;
}


// === Popup control base class ========================================================================================

class UC_DLL_EXPORT Popup: public DG::UserControl
{
protected:
	enum ControlKind {
		Menu = CK_POPUP_MENU,
		Control = CK_POPUP_CONTROL
	};

	Popup (const DG::Panel& panel, short item, ControlKind kind);
	Popup (const DG::Panel& panel, const DG::Rect& rect, ControlKind kind, DG::UserControl::FrameType frameType);

public:
	enum ButtonType {
		IconText  = BT_POPUP_ICONTEXT,
		IconOnly  = BT_POPUP_ICONONLY,
		TextOnly  = BT_POPUP_TEXTONLY,
		ArrowOnly = BT_POPUP_ARROWONLY
	};

	enum ItemHeight {
		Default = IH_POPUP_DEFAULT
	};

	enum TextAlignment {
		LeftAligned   = TA_POPUP_LEFT,
		RightAligned  = TA_POPUP_RIGHT,
		CenterAligned = TA_POPUP_CENTER
	};

   ~Popup ();

	void		SetButtonType (ButtonType type);
	ButtonType	GetButtonType (void) const;

	void	AppendItem (void);
	void	AppendSeparator (void);
	void	InsertItem (UIndex itemIndex);
	void	InsertSeparator (UIndex itemIndex);
	void	DeleteItem (UIndex itemIndex);
	void	DeleteAllItems (void);

	USize	GetItemCount (void) const;

	UIndex	GetSelectedItem (void) const;
	UIndex	GetTrackedItem (void) const;

	void		SetItemIcon (UIndex popupItem, const DG::Icon& icon);
	DG::Icon	GetItemIcon (UIndex popupItem) const;

	void			SetItemText (UIndex popupItem, const GS::UniString& text);
	GS::UniString	GetItemText (UIndex popupItem) const;

	void			SetItemTextSize (UIndex popupItem, DG::Font::Size size);
	DG::Font::Size	GetItemTextSize (UIndex popupItem) const;

	void			SetItemTextStyle (UIndex popupItem, DG::Font::Style style);
	DG::Font::Style	GetItemTextStyle (UIndex popupItem) const;

	void	SetItemData (UIndex popupItem, void* itemData);
	void*	GetItemData (UIndex popupItem) const;

	void				SetItemObjectData (UIndex popupItem, GS::Ref<GS::Object> itemData);
	GS::Ref<GS::Object>	GetItemObjectData (UIndex popupItem) const;

	void	EnableItem (UIndex popupItem);
	void	DisableItem (UIndex popupItem);
	void	SetItemStatus (UIndex popupItem, bool status);
	bool	IsItemEnabled (UIndex popupItem) const;

	bool	IsSeparatorItem (UIndex popupItem) const;

	void	SetItemHeight (UShort itemHeight);
	UShort	GetItemHeight (void) const;

	void	ShowAndTrackPopup (void);

	void	EnableDraw (void);
	void	DisableDraw (void);

	void			SetTextAlignment (TextAlignment alignment);
	TextAlignment	GetTextAlignment () const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- Inline implementation -------------------------------------------------------------------------------------------

inline Popup::ButtonType	Popup::GetButtonType (void) const
{
	return static_cast<Popup::ButtonType> (UCPopupGetButtonType (GetPanelId (), GetId ()));
}


inline USize	Popup::GetItemCount (void) const
{
	return UCPopupGetItemCount (GetPanelId (), GetId ());
}


inline UIndex	Popup::GetSelectedItem (void) const
{
	return UCPopupGetSelectedItem (GetPanelId (), GetId ());
}


inline UIndex	Popup::GetTrackedItem (void) const
{
	return UCPopupGetTrackedItem (GetPanelId (), GetId ());
}


inline DG::Icon		Popup::GetItemIcon (UIndex popupItem) const
{
	DG::Icon icon;
	UCPopupGetItemIcon (GetPanelId (), GetId (), popupItem, reinterpret_cast<void*> (&icon));

	return icon;
}


inline GS::UniString	Popup::GetItemText (UIndex popupItem) const
{
	return UCPopupGetItemText (GetPanelId (), GetId (), popupItem);
}


inline DG::Font::Size	Popup::GetItemTextSize (UIndex popupItem) const
{
	short fontStyle = UCPopupGetItemTextStyle (GetPanelId (), GetId (), popupItem);

	return static_cast<DG::Font::Size> (fontStyle & DG_IS_SIZEMASK);
}


inline DG::Font::Style		Popup::GetItemTextStyle (UIndex popupItem) const
{
	short fontStyle = UCPopupGetItemTextStyle (GetPanelId (), GetId (), popupItem);

	return static_cast<DG::Font::Style> (fontStyle & DG_IS_STYLEMASK);
}


inline void*	Popup::GetItemData (UIndex popupItem) const
{
	return UCPopupGetItemData (GetPanelId (), GetId (), popupItem);
}


inline GS::Ref<GS::Object>	Popup::GetItemObjectData (UIndex popupItem) const
{
	return UCPopupGetItemObjectData (GetPanelId (), GetId (), popupItem);
}


inline bool		Popup::IsItemEnabled (UIndex popupItem) const
{
	return UCPopupIsItemEnabled (GetPanelId (), GetId (), popupItem);
}


inline bool		Popup::IsSeparatorItem (UIndex popupItem) const
{
	return UCPopupIsSeparatorItem (GetPanelId (), GetId (), popupItem);
}


inline void		Popup::SetItemHeight (UShort itemHeight)
{
	UCPopupSetItemHeight (GetPanelId (), GetId (), itemHeight);
}


inline UShort	Popup::GetItemHeight (void) const
{
	return UCPopupGetItemHeight (GetPanelId (), GetId ());
}


inline void		Popup::ShowAndTrackPopup (void)
{
	UCPopupShowAndTrackPopup (GetPanelId (), GetId ());
}


// === Menu Popup class ================================================================================================

class UC_DLL_EXPORT PopupMenu: public UC::Popup
{
public:
	PopupMenu (const DG::Panel& panel, short item);
	PopupMenu (const DG::Panel& panel, const DG::Rect& rect, DG::UserControl::FrameType frameType = Frame);
   ~PopupMenu ();

	void		SetButtonIcon (const DG::Icon& icon);
	DG::Icon	GetButtonIcon (void) const;

	void		SetButtonText (const GS::UniString& text);
	GS::UniString	GetButtonText (void) const;

	void			SetButtonTextSize (DG::Font::Size size);
	DG::Font::Size	GetButtonTextSize (void) const;

	void			SetButtonTextStyle (DG::Font::Style style);
	DG::Font::Style	GetButtonTextStyle (void) const;

	void	CheckItem (UIndex popupItem);
	void	UncheckItem (UIndex popupItem);
	void	SetItemState (UIndex popupItem, bool state);
	bool	IsItemChecked (UIndex popupItem) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


inline DG::Icon		PopupMenu::GetButtonIcon (void) const
{
	DG::Icon icon;
	UCPopupGetButtonIcon (GetPanelId (), GetId (), reinterpret_cast<void*> (&icon));

	return icon;
}


inline GS::UniString	PopupMenu::GetButtonText (void) const
{
	return UCPopupGetButtonText (GetPanelId (), GetId ());
}


inline DG::Font::Size	PopupMenu::GetButtonTextSize (void) const
{
	short fontStyle = UCPopupGetButtonTextStyle (GetPanelId (), GetId ());

	return static_cast<DG::Font::Size> (fontStyle & DG_IS_SIZEMASK);
}


inline DG::Font::Style	PopupMenu::GetButtonTextStyle (void) const
{
	short fontStyle = UCPopupGetButtonTextStyle (GetPanelId (), GetId ());

	return static_cast<DG::Font::Style> (fontStyle & DG_IS_STYLEMASK);
}


inline bool		PopupMenu::IsItemChecked (UIndex popupItem) const
{
	return UCPopupIsItemChecked (GetPanelId (), GetId (), popupItem);
}


// === Control Popup class =============================================================================================

class UC_DLL_EXPORT PopupControl: public UC::Popup
{
public:
	PopupControl (const DG::Panel& panel, short item);
	PopupControl (const DG::Panel& panel, const DG::Rect& rect, DG::UserControl::FrameType frameType = Frame);
   ~PopupControl ();

	void	SelectItem (UIndex index);

	void			SetVariousState (bool isVarious);
	bool			GetVariousState (void) const;
	void			SetVariousText (const GS::UniString& text);
	GS::UniString	GetVariousText (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};

}	// namespace UC

#endif
