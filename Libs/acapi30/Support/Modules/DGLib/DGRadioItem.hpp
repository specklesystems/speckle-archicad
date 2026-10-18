// *****************************************************************************
// File:			DGRadioItem.hpp
//
// Description:		RadioItem classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGRADIOITEM_HPP
#define DGRADIOITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGItemProperty.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class RadioItem;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- RadioDragSourceEvent ----------------------------------------------------

class DG_DLL_EXPORT RadioDragSourceEvent: public ItemDragSourceEvent
{
friend class RadioDragSourceObserver;		// To access protected constructor
friend class RadioItemObserver;				// To access protected constructor

protected:
	explicit RadioDragSourceEvent (const ItemDragSourceEvent& ev);

public:
	~RadioDragSourceEvent ();

	RadioItem*	GetSource (void) const;
};


// --- RadioDragSourceObserver -------------------------------------------------

class DG_DLL_EXPORT RadioDragSourceObserver
{
protected:
	RadioDragSourceObserver ();

public:
	virtual ~RadioDragSourceObserver ();

	virtual void	RadioItemDragStarting (const RadioDragSourceEvent& ev, bool* canStart);
	virtual void	RadioItemDragStarted (const RadioDragSourceEvent& ev, UShort* effect);
	virtual void	RadioItemDragStarted (const RadioDragSourceEvent& ev, UShort* effect, bool* rightDragMenu);
	virtual void	RadioItemDragEnded (const RadioDragSourceEvent& ev, DragDrop::Effect effect);
	virtual void	RadioItemDragSetDelayedData (const RadioDragSourceEvent& ev);
};


// --- RadioDropTargetEvent ----------------------------------------------------

class DG_DLL_EXPORT RadioDropTargetEvent: public ItemDropTargetEvent
{
friend class RadioItemObserver;				// To access protected constructor

protected:
	explicit RadioDropTargetEvent (const ItemDropTargetEvent& ev);

public:
	~RadioDropTargetEvent ();

	RadioItem*	GetSource (void) const;
};


// --- RadioDropTargetObserver -------------------------------------------------

class DG_DLL_EXPORT RadioDropTargetObserver
{
protected:
	RadioDropTargetObserver ();

public:
	virtual ~RadioDropTargetObserver ();

	virtual void	RadioItemDragEntered (const RadioDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour);
	virtual void	RadioItemDragEntered (const RadioDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour,
										  bool* rightDragMenu);
	virtual void	RadioItemDragMoved (const RadioDropTargetEvent& ev, DragDrop::Effect* effect, DragDrop::Feedback* denyFeedback);
	virtual void	RadioItemDragLeft (const RadioDropTargetEvent& ev, DragDrop::Effect* effect);
	virtual void	RadioItemDropped (const RadioDropTargetEvent& ev, DragDrop::Effect* effect);
};


// --- RadioItemChangeEvent ----------------------------------------------------

class DG_DLL_EXPORT RadioItemChangeEvent: public ItemChangeEvent
{
friend class RadioItemObserver;				// To access protected constructor

private:
	Item*	previousSelection;

protected:
	explicit RadioItemChangeEvent (const ItemChangeEvent& ev);

public:
	~RadioItemChangeEvent ();

	RadioItem*	GetSource (void) const;

	Item*	GetPreviousGroupSelection (void) const;
};


// --- RadioItemDoubleClickEvent -----------------------------------------------

class DG_DLL_EXPORT RadioItemDoubleClickEvent: public ItemDoubleClickEvent
{
friend class RadioItemObserver;				// To access protected constructor

protected:
	explicit RadioItemDoubleClickEvent (const ItemDoubleClickEvent& ev);

public:
	~RadioItemDoubleClickEvent ();

	RadioItem*	GetSource (void) const;
};


// --- RadioItemObserver -------------------------------------------------------

class DG_DLL_EXPORT RadioItemObserver: public ItemObserver,
									   public RadioDragSourceObserver,
									   public RadioDropTargetObserver
{
protected:
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual	short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;
	virtual short	SpecDragStarting (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragStarted (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragEnded (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragSetDelayedData (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragEntered (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDragMoved (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDragLeft (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDropped (const ItemDropTargetEvent& ev) override;

	virtual void	RadioItemChanged (const RadioItemChangeEvent& ev);
	virtual void	RadioItemDoubleClicked (const RadioItemDoubleClickEvent& ev);

public:
	RadioItemObserver ();
   ~RadioItemObserver ();
};


// --- RadioItem ---------------------------------------------------------------

class DG_DLL_EXPORT RadioItem: public Item,
							   public ItemDragDropNotifier<RadioItem>
{
protected:
	RadioItem ();
	RadioItem (const Panel& panel, short item);

public:
	~RadioItem ();

	void	Attach (RadioItemObserver& observer);
	void	Detach (RadioItemObserver& observer);

	void	Select (void);
	bool	IsSelected (void) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- RadioButton -------------------------------------------------------------

class DG_DLL_EXPORT RadioButton: public RadioItem,
								 public ItemFontProperty,
								 public ItemTextProperty
{
public:
	RadioButton (const Panel& panel, short item);
	RadioButton (const Panel& panel, const Rect& rect, short groupId);
   ~RadioButton ();

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- IconRadioButton ---------------------------------------------------------

class DG_DLL_EXPORT IconRadioButton: public RadioItem,
									 public ItemIconProperty
{
public:
	IconRadioButton (const Panel& panel, short item);
	IconRadioButton (const Panel& panel, const Rect& rect, short groupId);
   ~IconRadioButton ();

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- PushRadio ---------------------------------------------------------------

class DG_DLL_EXPORT PushRadio: public RadioItem,
							   public ItemFontProperty,
							   public ItemTextProperty,
							   public ItemIconProperty
{
public:
	PushRadio (const Panel& panel, short item);
	PushRadio (const Panel& panel, const Rect& rect, short groupId);
   ~PushRadio ();

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- IconPushRadio -----------------------------------------------------------

class DG_DLL_EXPORT IconPushRadio: public RadioItem,
								   public ItemIconProperty
{
public:
	IconPushRadio (const Panel& panel, short item);
	IconPushRadio (const Panel& panel, const Rect& rect, short groupId);
   ~IconPushRadio ();

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};

}	// namespace DG

#endif
