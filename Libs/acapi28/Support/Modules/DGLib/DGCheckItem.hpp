// *****************************************************************************
// File:			DGCheckItem.hpp
//
// Description:		CheckItem classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGCHECKITEM_HPP
#define DGCHECKITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGItemProperty.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class CheckItem;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- CheckItemChangeEvent ----------------------------------------------------

class DG_DLL_EXPORT CheckItemChangeEvent: public ItemChangeEvent
{
friend class CheckItemObserver;				// To access protected constructor

protected:
	explicit CheckItemChangeEvent (const ItemChangeEvent& ev);

public:
	~CheckItemChangeEvent ();

	CheckItem*	GetSource (void) const;
};


// --- CheckItemDoubleClickEvent -----------------------------------------------

class DG_DLL_EXPORT CheckItemDoubleClickEvent: public ItemDoubleClickEvent
{
friend class CheckItemObserver;				// To access protected constructor

protected:
	explicit CheckItemDoubleClickEvent (const ItemDoubleClickEvent& ev);

public:
	~CheckItemDoubleClickEvent ();

	CheckItem*	GetSource (void) const;
};


// --- CheckItemObserver -------------------------------------------------------

class DG_DLL_EXPORT CheckItemObserver: public ItemObserver
{
protected:
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual	short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;

	virtual void	CheckItemChanged (const CheckItemChangeEvent& ev);
	virtual void	CheckItemDoubleClicked (const CheckItemDoubleClickEvent& ev);

public:
	CheckItemObserver ();
   ~CheckItemObserver ();
};


// --- CheckItem ---------------------------------------------------------------

class DG_DLL_EXPORT CheckItem: public Item
{
protected:
	CheckItem ();
	CheckItem (const Panel& panel, short item);

public:
	~CheckItem ();

	void	Attach (CheckItemObserver& observer);
	void	Detach (CheckItemObserver& observer);

	void	Check (void);
	void	Uncheck (void);
	void	SetState (bool check);
	bool	IsChecked (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- CheckBox ----------------------------------------------------------------

class DG_DLL_EXPORT CheckBox: public CheckItem,
							  public ItemFontProperty,
							  public ItemTextProperty
{
public:
	CheckBox (const Panel& panel, short item);
	CheckBox (const Panel& panel, const Rect& rect);
   ~CheckBox ();

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- IconCheckBox ------------------------------------------------------------

class DG_DLL_EXPORT IconCheckBox: public CheckItem,
								  public ItemIconProperty
{
public:
	IconCheckBox (const Panel& panel, short item);
	IconCheckBox (const Panel& panel, const Rect& rect);
   ~IconCheckBox ();

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- PushCheck ---------------------------------------------------------------

class DG_DLL_EXPORT PushCheck: public CheckItem,
							   public ItemFontProperty,
							   public ItemTextProperty,
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

    enum Alignment {
        LeftAligned		= DG_BTA_LEFT,
        CenterAligned	= DG_BTA_CENTER,
        RightAligned	= DG_BTA_RIGHT
    };

	enum ArrowType {
		None			= DG_PCA_NONE,
		Right			= DG_PCA_RIGHT,
		Down			= DG_PCA_DOWN
	};

	PushCheck (const Panel& panel, short item);
	PushCheck (const Panel& panel, const Rect& rect, ButtonForm form = BevelEdge, FrameType frameType = Frame);
   ~PushCheck ();

    void		SetAlignment (Alignment alignment);
    Alignment	GetAlignment () const;

    void		SetArrowType (ArrowType arrowType);
    ArrowType	GetArrowType () const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- IconPushCheck -----------------------------------------------------------

class DG_DLL_EXPORT IconPushCheck: public CheckItem,
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

	IconPushCheck (const Panel& panel, short item);
	IconPushCheck (const Panel& panel, const Rect& rect, ButtonForm form = BevelEdge, FrameType frameType = Frame);
   ~IconPushCheck ();

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};

}	// namespace DG

#endif
