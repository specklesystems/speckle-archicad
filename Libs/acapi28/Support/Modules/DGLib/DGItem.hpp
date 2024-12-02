// *****************************************************************************
// File:			DGItem.hpp
//
// Description:		Item related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
// *****************************************************************************

#ifndef DGITEM_HPP
#define DGITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGItemEventArgs.hpp"
#include "DGItemNotifiers.hpp"
#include "DGUtility.hpp"
#include "Event.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"
#include "UniString.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class Item;
	class EventDispatcher;
}

class DGItemResourceData;

// --- Class declarations ------------------------------------------------------

namespace DG {

// --- ItemEvent ---------------------------------------------------------------

class DG_DLL_EXPORT ItemEvent: public GS::Event
{
private:
	const DG::EventArg&	msgData;

protected:
	ItemEvent (Item* source, const DG::EventArg& msgData);

	const DG::EventArg&	GetMessageData (void) const;
	DG::EventArg& 		GetMessageDataNonConst (void);

public:
	~ItemEvent ();

	Item*	GetSource (void) const;
};


// --- ItemChangeEvent ---------------------------------------------------------

class DG_DLL_EXPORT ItemChangeEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemChangeEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemChangeEvent ();
};


// --- ItemResizeEvent ---------------------------------------------------------

class DG_DLL_EXPORT ItemResizeEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemResizeEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemResizeEvent ();
};


// --- ItemCharEnterEvent ------------------------------------------------------

class DG_DLL_EXPORT ItemCharEnterEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemCharEnterEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemCharEnterEvent ();

	UShort	GetCharCode (void) const;
};


// --- ItemClickEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemClickEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemClickEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemClickEvent ();
};


// --- ItemMouseDownEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemMouseDownEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemMouseDownEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemMouseDownEvent ();
};


// --- ItemMouseUpEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemMouseUpEvent: public ItemEvent
{
	friend class Item;							// To access protected constructor

protected:
	ItemMouseUpEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemMouseUpEvent ();
};


// --- ItemContextMenuEvent ----------------------------------------------------

class DG_DLL_EXPORT ItemContextMenuEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

private:
	const DG::ContextMenuEventArg*	contextMenuMsgData;

protected:
	ItemContextMenuEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemContextMenuEvent ();

	NativePoint	GetPosition (void) const;
};


// --- ItemDoubleClickEvent ----------------------------------------------------

class DG_DLL_EXPORT ItemDoubleClickEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemDoubleClickEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemDoubleClickEvent ();
};


// --- ItemDragSourceEvent -----------------------------------------------------

class DG_DLL_EXPORT ItemDragSourceEvent: public ItemEvent,
										 public ItemDragDropData
{
friend class Item;							// To access protected constructor

private:
	DG::DragDropEventArg*	dragMsgData;

protected:
	ItemDragSourceEvent (Item* source, DG::EventArg& msgData);

public:
	~ItemDragSourceEvent ();

	DragSourceEventProperty*	GetDragData (void) const;
};


// --- ItemDropTargetEvent -----------------------------------------------------

class DG_DLL_EXPORT ItemDropTargetEvent: public ItemEvent,
										 public DropTargetEventProperty
{
friend class Item;							// To access protected constructor

protected:
	ItemDropTargetEvent (Item* source, DG::EventArg& msgData);

public:
	~ItemDropTargetEvent ();
};


// --- ItemFocusEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemFocusEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemFocusEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemFocusEvent ();
};


// --- ItemHelpEvent -----------------------------------------------------------

class DG_DLL_EXPORT ItemHelpEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemHelpEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemHelpEvent ();
	short GetSubItem (void) const;
	Int32 GetTreeItem (void) const;
	Int32 GetTabBarItemId (void) const;
};


// --- ItemMouseMoveEvent ------------------------------------------------------

class DG_DLL_EXPORT ItemMouseMoveEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemMouseMoveEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemMouseMoveEvent ();
};


// --- ItemMouseEnteredEvent ---------------------------------------------------
typedef ItemMouseMoveEvent ItemMouseEnteredEvent;

// --- ItemMouseExitedEvent ----------------------------------------------------
typedef ItemMouseMoveEvent ItemMouseExitedEvent;



// --- ItemTrackEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemTrackEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemTrackEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemTrackEvent ();
};


// --- ItemUpdateEvent ---------------------------------------------------------

class DG_DLL_EXPORT ItemUpdateEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemUpdateEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemUpdateEvent ();
};


// --- ItemWheelEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemWheelEvent: public ItemEvent
{
friend class Item;							// To access protected constructor

protected:
	const DG::WheelEventArg*		wheelMsgData;

	ItemWheelEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemWheelEvent ();
};


// --- ItemWheelTrackEvent -----------------------------------------------------

class DG_DLL_EXPORT ItemWheelTrackEvent: public ItemWheelEvent
{
friend class Item;							// To access protected constructor

protected:
	ItemWheelTrackEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemWheelTrackEvent ();

	short	GetXTrackValue (void) const;
	short	GetYTrackValue (void) const;

	Point	GetMouseOffset (void) const;

	bool	IsCommandPressed (void) const;
	bool	IsOptionPressed (void) const;
	bool	IsShiftPressed (void) const;

	bool	IsCommandProcessed (void) const;
	bool	IsOptionProcessed (void) const;
	bool	IsShiftProcessed (void) const;

	bool	IsFromTouchCapableDevice (void) const;
};


// --- ItemResolutionFactorChangeEvent -----------------------------------------------------

class DG_DLL_EXPORT ItemResolutionFactorChangeEvent: public ItemEvent
{
friend class Item;				// To access protected constructor

private:
	const DG::UserItemResolutionChangeEventArg*	resolutionFactorData;

protected:
	explicit ItemResolutionFactorChangeEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemResolutionFactorChangeEvent ();

	double	GetOldResolutionFactor (void) const;
};


// --- ItemHoverEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemHoverEvent : public ItemEvent
{
friend class Item;				// To access protected constructor

protected:
	ItemHoverEvent (Item* source, const DG::EventArg& msgData);

public:
	~ItemHoverEvent();
};


// --- ItemPressedEvent ----------------------------------------------------------

class DG_DLL_EXPORT ItemPressedEvent : public ItemEvent
{
	friend class Item;				// To access protected constructor

protected:
	ItemPressedEvent (Item* source, const DG::EventArg& msgData);

	explicit ItemPressedEvent (const ItemMouseDownEvent& ev);

public:
	~ItemPressedEvent();
};


// --- ItemObserver ------------------------------------------------------------

class DG_DLL_EXPORT ItemObserver: public GS::EventObserver
{
friend class Item;						// To access protected observer methods

protected:
	virtual void	ItemChangeRequested (const ItemMouseDownEvent& ev);
	virtual void	ItemChanged (const ItemChangeEvent& ev);
	virtual void	ItemCharEntered (const ItemCharEnterEvent& ev, bool* denyChar);
	virtual void	ItemClicked (const ItemClickEvent& ev);
	virtual void	ItemMouseDown (const ItemMouseDownEvent& ev, bool* processed);
	virtual void	ItemMouseUp (const ItemMouseUpEvent& ev, bool* processed);
	virtual void	ItemContextHelpRequested (const ItemHelpEvent& ev, GS::UniString* contextHelpAnchor);
	virtual void	ItemContextMenuRequested (const ItemContextMenuEvent& ev, bool* needHelp, bool* processed);
	virtual void	ItemDoubleClicked (const ItemDoubleClickEvent& ev);
	virtual void	ItemFocusGained (const ItemFocusEvent& ev);
	virtual void	ItemFocusLost (const ItemFocusEvent& ev);
	virtual void	ItemMouseMoved (const ItemMouseMoveEvent& ev);
	virtual void	ItemMouseEntered (const ItemMouseEnteredEvent& ev);
	virtual void	ItemMouseExited (const ItemMouseExitedEvent& ev);
	virtual void	ItemToolTipRequested (const ItemHelpEvent& ev, GS::UniString* toolTipText);
	virtual void	ItemTrackEntered (const ItemTrackEvent& ev);
	virtual void	ItemTracked (const ItemTrackEvent& ev);
	virtual void	ItemTrackExited (const ItemTrackEvent& ev);
	virtual void	ItemUpdate (const ItemUpdateEvent& ev);
	virtual void	ItemWheelTrackEntered (const ItemWheelEvent& ev, bool* processed);
	virtual void	ItemWheelTracked (const ItemWheelTrackEvent& ev, bool* processed);
	virtual void	ItemWheelTrackExited (const ItemWheelEvent& ev, bool* processed);
	virtual void	ItemResolutionFactorChanged (const ItemResolutionFactorChangeEvent& ev);
	virtual void	ItemHoverStarted (const ItemHoverEvent& ev);
	virtual void	ItemHoverEnded (const ItemHoverEvent& ev);
	virtual void	ItemPressed (const ItemPressedEvent& ev);
	virtual void	ItemOverlayUpdate (const ItemUpdateEvent& ev);

	virtual short	SpecChangeRequested (const ItemMouseDownEvent& ev);
	virtual short	SpecChanged (const ItemChangeEvent& ev);
	virtual short	SpecClicked (const ItemClickEvent& ev);
	virtual short	SpecMouseDown (const ItemMouseDownEvent& ev, bool* processed);
	virtual short	SpecMouseUp (const ItemMouseUpEvent& ev, bool* processed);
	virtual short	SpecContextMenuRequested (const ItemContextMenuEvent& ev);
	virtual short	SpecDoubleClicked (const ItemDoubleClickEvent& ev);
	virtual short	SpecDragStarting (const ItemDragSourceEvent& ev);
	virtual short	SpecDragStarted (const ItemDragSourceEvent& ev);
	virtual short	SpecDragEnded (const ItemDragSourceEvent& ev);
	virtual short	SpecDragSetDelayedData (const ItemDragSourceEvent& ev);
	virtual short	SpecDragEntered (const ItemDropTargetEvent& ev);
	virtual short	SpecDragMoved (const ItemDropTargetEvent& ev);
	virtual short	SpecDragLeft (const ItemDropTargetEvent& ev);
	virtual short	SpecDropped (const ItemDropTargetEvent& ev);
	virtual short	SpecMouseMoved (const ItemMouseMoveEvent& ev);
	virtual short	SpecMouseEntered (const ItemMouseEnteredEvent& ev);
	virtual short	SpecMouseExited (const ItemMouseExitedEvent& ev);
	virtual short	SpecTrackEntered (const ItemTrackEvent& ev);
	virtual short	SpecTracked (const ItemTrackEvent& ev);
	virtual short	SpecTrackExited (const ItemTrackEvent& ev);
	virtual short	SpecUpdate (const ItemUpdateEvent& ev);
	virtual short	SpecResolutionFactorChanged (const ItemResolutionFactorChangeEvent& ev);
	virtual short	SpecHoverStarted (const ItemHoverEvent& ev);
	virtual short	SpecHoverEnded (const ItemHoverEvent& ev);
	virtual short	SpecPressed (const ItemPressedEvent& ev);
	virtual short	SpecOverlayUpdate (const ItemUpdateEvent& ev);

public:
	ItemObserver ();
	~ItemObserver ();
};


// --- ItemBase ----------------------------------------------------------------

class DG_DLL_EXPORT ItemBase
{
private:
	short	panelId;
	short	itemId;
	bool	created;

protected:
	ItemBase ();

	void	Set (short panelId, short itemId, bool created);

public:
	virtual	~ItemBase ();

	bool	IsValid (void) const;

	Panel*	GetPanel (void) const;

	short	GetPanelId (void) const;
	short	GetId (void) const;
};


// --- Item --------------------------------------------------------------------

class DG_DLL_EXPORT Item: virtual public ItemBase,
								  public ItemNotifyHandler,
								  public virtual DG::DefaultEventTargetProvider,
								  public GS::EventSource
{
friend class EventDispatcher;			// To access private event processing methods
friend class PanelResizeBlock;

private:
	Item (const Item&);						// Disable
	Item&	operator= (const Item& item);	// Disable

	void	InitNotifiers ();
	void	SendResizeEvent (short hGrow, short vGrow);
	void	SendMoveEvent (short hDisp, short vDisp);

	virtual short	NotifyDragDropEvent (DragDropEventArg& /*eventArg*/) override;
	virtual short	NotifyWheelEvent (const WheelEventArg& /*eventArg*/) override;
	virtual short	NotifyTrackEvent (const ItemTrackEventArg& /*eventArg*/) override;
	virtual short	NotifyFocusChangeEvent (const ItemFocusChangeEventArg& /*eventArg*/) override;
	virtual short	NotifyFilterCharEvent (const FilterCharEventArg& /*eventArg*/) override;

	virtual bool	NotifyContextMenuRequestEvent (ContextMenuEventArg& eventArg) override;
	virtual short	NotifyHelpRequestEvent (HelpEventArg& eventArg) override;
	virtual short	NotifyToolTipRequestEvent (HelpEventArg& eventArg) override;
	virtual short	NotifyClickEvent (const ItemClickEventArg& eventArg) override;
	virtual short	NotifyDoubleClickEvent (const ItemDoubleClickEventArg& eventArg) override;
	virtual short	NotifyChangeEvent (const ItemChangeEventArg& eventArg) override;
	virtual short	NotifyUserDefinedEvent (const UserDefinedEventArg& eventArg) override;

	class ResizeValues
	{
	public:
		short hGrow = 0;
		short vGrow = 0;
		short hMove = 0;
		short vMove = 0;

		virtual ~ResizeValues ();

		void	Clear ();
	};

 	ResizeValues	resizeValues;

	void			FlushResize ();

protected:
	virtual short	ProcessChangeRequestEvent (const DG::EventArg& msgData);
	virtual short	ProcessChangeEvent (const DG::EventArg& msgData);
	virtual short	ProcessCharEnterEvent (const DG::EventArg& msgData);
	virtual short	ProcessClickEvent (const DG::EventArg& msgData);
	virtual short	ProcessMouseDownEvent (const DG::EventArg& msgData);
	virtual short	ProcessMouseUpEvent (const DG::EventArg& msgData);
	virtual short	ProcessContextMenuEvent (DG::EventArg& msgData);
	virtual short	ProcessDoubleClickEvent (const DG::EventArg& msgData);
	virtual short	ProcessDragDropEvent (DG::EventArg& msgData);
	virtual short	ProcessFocusEvent (const DG::EventArg& msgData);
	virtual short	ProcessItemHelpEvent (DG::EventArg& msgData);
	virtual short	ProcessMouseMoveEvent (const DG::EventArg& msgData);
	virtual short	ProcessMouseEnterEvent (const DG::EventArg& msgData);
	virtual short	ProcessMouseLeaveEvent (const DG::EventArg& msgData);
	virtual short	ProcessTrackEvent (const DG::EventArg& msgData);
	virtual short	ProcessUpdateEvent (DG::EventArg& msgData);
	virtual short	ProcessWheelTrackEvent (const DG::EventArg& msgData);
	virtual short	ProcessResolutionFactorChangeEvent (const DG::EventArg& msgData);
	virtual short	ProcessHoverEvent (const DG::EventArg& msgData);
	virtual short	ProcessPressedEvent (const DG::EventArg& msgData);
	virtual short	ProcessUpdateOverlayEvent (const DG::EventArg& msgData);

	Item ();
	Item (const Panel& panel, short item);

	void	Init (const Panel& panel, short item);

public:
	~Item ();

	const std::function<void (const Panel&, ResizeEventArg&)> HVGrow;
	const std::function<void (const Panel&, ResizeEventArg&)> HGrow;
	const std::function<void (const Panel&, ResizeEventArg&)> VGrow;
	const std::function<void (const Panel&, ResizeEventArg&)> HVMove;
	const std::function<void (const Panel&, ResizeEventArg&)> VMove;
	const std::function<void (const Panel&, ResizeEventArg&)> HMove;
	const std::function<void (const Panel&, ResizeEventArg&)> HGrow_VMove;
	const std::function<void (const Panel&, ResizeEventArg&)> VGrow_HMove;

	EventNotifier<Item, ContextMenuEventArg, bool, false> onContextMenuRequested;
	EventNotifier<Item, HelpEventArg, short> onHelpRequested;
	EventNotifier<Item, HelpEventArg, short> onToolTipRequested;
	EventNotifier<Item, const ItemClickEventArg, short> onClicked;
	EventNotifier<Item, const ItemDoubleClickEventArg, short> onDoubleClicked;
	EventNotifier<Item, const ItemChangeEventArg, short> onChanged;
	EventNotifier<Item, const UserDefinedEventArg, short> onUserDefinedEvent;

	EventNotifier<Item, const ResizeEventArg> onResized;
	EventNotifier<Item, const MoveEventArg> onMoved;
	EventNotifier<Item, const VisibilityChangeEventArg> onVisibilityChanged;

	bool	operator== (const Item& rightOp) const;
	bool	operator!= (const Item& rightOp) const;

	void	Attach (ItemObserver& observer);
	void	Detach (ItemObserver& observer);

	void	Show (void);
	void	Hide (void);
	void	SetVisibility (bool show);
	bool	IsVisible (void) const;
	void	Flash (void);

	void	Enable (void);
	void	Disable (void);
	void	SetStatus (bool enable);
	bool	IsEnabled (void) const;

	void	Move (short hDisp, short vDisp);
	void	Resize (short hGrow, short vGrow);
	void	MoveAndResize (short hDisp, short vDisp, short hGrow, short vGrow);

	void	SetPosition (const Point& pt);
	void	SetPosition (short hPos, short vPos);
	void	SetRect (const Rect& rect);
	void	SetSize (short width, short height);
	void	SetWidth (short width);
	void	SetHeight (short height);

	Point	GetPosition (void) const;
	Rect	GetRect (void) const;
	short	GetWidth (void) const;
	short	GetHeight (void) const;

	virtual Point	GetContentSize (void) const;

	NativeRect	GetNativeRectInScreenSpace (void) const;

	void	Invalidate (void) const;
	void	Redraw (void) const;

	void	ResetModified (void);
	bool	IsModified (void) const;

	void			SetHelp (short helpIndex);
	GS::UniString	GetTooltipString (void) const;
	GS::UniString	GetAnchorString (void) const;

	void			SetDescription (const GS::UniString& description);
	GS::UniString	GetDescription () const;

	void	InvokeDragDrop (void);

	double	GetResolutionFactor (void) const;

	virtual void SetupAdditionalResource (GS::Ref<DGItemResourceData> creationData);

	virtual NewDisplay::NativeImage CaptureToNativeImage () const;

	virtual EventTarget* GetDefaultEventTarget () const override;

	virtual GSErrCode Store (GS::ObjectState& os) const;
};

}	// namespace DG

#endif
