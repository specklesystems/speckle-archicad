// *********************************************************************************************************************
// File:			DGButton.hpp
//
// Description:		Button classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
// *********************************************************************************************************************

#ifndef DGBUTTON_HPP
#define DGBUTTON_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "DGItemProperty.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace DG {
	class ButtonItem;
	class SplitButton;
	class CustomSplitButton;
	class EventDispatcher;
}


// --- Class declarations ----------------------------------------------------------------------------------------------

namespace DG {

// --- ButtonClickEvent ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ButtonClickEvent: public ItemClickEvent
{
friend class ButtonItemObserver;			// To access protected constructor

protected:
	explicit ButtonClickEvent (const ItemClickEvent& ev);

public:
	~ButtonClickEvent ();

	ButtonItem*		GetSource (void) const;
};


// --- ButtonItemObserver ----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ButtonItemObserver: public ItemObserver
{
protected:
	virtual	short	SpecClicked (const ItemClickEvent& ev) override;
	virtual void	ButtonClicked (const ButtonClickEvent& ev);

public:
	ButtonItemObserver ();
   ~ButtonItemObserver ();
};


// --- ButtonItem ------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ButtonItem: public Item
{
protected:
	ButtonItem ();
	ButtonItem (const Panel& panel, short item);

public:
	~ButtonItem ();

	void	Attach (ButtonItemObserver& observer);
	void	Detach (ButtonItemObserver& observer);
};


// --- Button ----------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT Button: public ButtonItem,
							public ItemFontProperty,
							public ItemTextProperty,
							public ItemIconProperty
{
public:
	enum ButtonType {
		Normal				= DG_BA_NORMAL,
		BevelEdge			= DG_BA_BEVEL,
		RoundedBevelEdge	= DG_BA_ROUNDEDBEVEL
	};

	enum FrameType {
		NoFrame			= DG_BF_NOFRAME,
		Frame			= DG_BF_FRAME
	};

	enum Alignment {
		LeftAligned		= DG_BTA_LEFT,
		CenterAligned	= DG_BTA_CENTER,
		RightAligned	= DG_BTA_RIGHT
	};

	Button (const Panel& panel, short item);
	Button (const Panel& panel, const Rect& rect, ButtonType type = Normal, FrameType frameType = Frame);
	~Button ();

	void	SetAsDefault (void);
	void	SetAsCancel (void);

	void		SetAlignment (Alignment alignment);
	Alignment	GetAlignment (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- IconButton ------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT IconButton: public ButtonItem,
								public ItemIconProperty
{
public:
	enum ButtonForm {
		BevelEdge			= DG_BA_BEVEL,
		RoundedBevelEdge	= DG_BA_ROUNDEDBEVEL
	};

	enum FrameType {
		NoFrame			= DG_BF_NOFRAME,
		Frame			= DG_BF_FRAME
	};

	IconButton (const Panel& panel, short item);
	IconButton (const Panel& panel, const Rect& rect, ButtonForm form = BevelEdge, FrameType frameType = Frame);
	~IconButton ();

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- SplitButtonBase -------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT SplitButtonBase : public ButtonItem,
									  public ItemFontProperty,
									  public ItemTextProperty,
									  public ItemIconProperty
	{
public:
	enum ButtonForm {
		Normal				= DG_BA_NORMAL,
		BevelEdge			= DG_BA_BEVEL,
		RoundedBevelEdge	= DG_BA_ROUNDEDBEVEL
	};

	enum Alignment {
		LeftAligned		= DG_BTA_LEFT,
		CenterAligned	= DG_BTA_CENTER,
		RightAligned	= DG_BTA_RIGHT
	};

	SplitButtonBase (const Panel& panel, short item);
	SplitButtonBase (const Panel& panel, const Rect& rect, DG::SplitButtonBase::ButtonForm type = DG::SplitButtonBase::Normal);
	~SplitButtonBase ();

	void			SetButtonAlignment (Alignment alignment);
	Alignment		GetButtonAlignment (void) const;

	void			SetArrowPartWidth (short width);
	short			GetArrowPartWidth (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- SplitButtonChangeEvent ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT SplitButtonChangeEvent: public ItemChangeEvent
{
friend class SplitButtonObserver;

protected:
	explicit SplitButtonChangeEvent (const ItemChangeEvent& ev);

public:
	~SplitButtonChangeEvent ();

	SplitButton*	GetSource (void) const;
};


// --- SplitButtonObserver ---------------------------------------------------------------------------------------------

class DG_DLL_EXPORT SplitButtonObserver: public ButtonItemObserver
{
protected:
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual void	SplitButtonPopupChanged (const SplitButtonChangeEvent& ev);

public:
	SplitButtonObserver ();
	~SplitButtonObserver ();
};


// --- SplitButton -----------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT SplitButton: public SplitButtonBase
{
public:
	SplitButton (const Panel& panel, short item);
	SplitButton (const Panel& panel, const Rect& rect, DG::SplitButton::ButtonForm type = DG::SplitButton::Normal);
	~SplitButton ();

	void			Attach (SplitButtonObserver& observer);
	void			Detach (SplitButtonObserver& observer);

	void			AppendItem (const GS::UniString& itemText, const DG::Icon& itemIcon = DG::Icon ());
	void			AppendSeparator (void);
	void			InsertItem (short itemIndex, const GS::UniString& itemText, const DG::Icon& itemIcon = DG::Icon ());
	void			InsertSeparator (short itemIndex);
	void			DeleteItem (short itemIndex);
	void			DeleteAllItems (void);

	USize			GetItemCount (void) const;
	UIndex			GetSelectedItem (void) const;

	void			SetItemIcon (short popupItem, const DG::Icon& itemIcon);
	DG::Icon		GetItemIcon (short popupItem) const;

	void			SetItemText (short popupItem, const GS::UniString& text);
	GS::UniString	GetItemText (short popupItem) const;

	void			SetItemTextSize (short popupItem, DG::Font::Size size);
	DG::Font::Size	GetItemTextSize (short popupItem) const;

	void			SetItemTextStyle (short popupItem, DG::Font::Style style);
	DG::Font::Style	GetItemTextStyle (short popupItem) const;

	void			SetItemData (short popupItem, DGUserData value);
	DGUserData		GetItemData (short popupItem) const;

	void				SetItemObjectData (short popupItem, GS::Ref<GS::Object> object);
	GS::Ref<GS::Object>	GetItemObjectData (short popupItem) const;

	void			EnableItem (short popupItem);
	void			DisableItem (short popupItem);
	void			SetItemStatus (short popupItem, bool status);
	bool			IsItemEnabled (short popupItem) const;

	bool			IsSeparatorItem (short popupItem) const;

	void			EnableDraw (void);
	void			DisableDraw (void);

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- CustomSplitButtonOpenRequestedEvent -----------------------------------------------------------------------------

class DG_DLL_EXPORT CustomSplitButtonOpenRequestedEvent: public ItemEvent
{
friend class EventDispatcher;

protected:
	explicit CustomSplitButtonOpenRequestedEvent (CustomSplitButton& source);

public:
	~CustomSplitButtonOpenRequestedEvent ();

	CustomSplitButton*	GetSource (void) const;
};


// --- CustomSplitButtonObserver ---------------------------------------------------------------------------------------

class DG_DLL_EXPORT CustomSplitButtonObserver: public ButtonItemObserver
{
friend class EventDispatcher;

protected:
	virtual void	SplitButtonOpenRequested (const CustomSplitButtonOpenRequestedEvent& ev);

public:
	CustomSplitButtonObserver ();
	~CustomSplitButtonObserver ();
};


// --- CustomSplitButton -----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT CustomSplitButton: public SplitButtonBase
{
public:
	CustomSplitButton (const Panel& panel, short item);
	CustomSplitButton (const Panel& panel, const Rect& rect, DG::SplitButton::ButtonForm type = DG::SplitButton::Normal);
	~CustomSplitButton ();

	void			Attach (CustomSplitButtonObserver& observer);
	void			Detach (CustomSplitButtonObserver& observer);

	void			EnableArrowPart (void);
	void			DisableArrowPart (void);
	void			SetArrowPartStatus (bool status);
	bool			IsArrowPartEnabled (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};

}	// namespace DG

#endif
