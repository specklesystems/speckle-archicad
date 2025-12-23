// *********************************************************************************************************************
// File:			DGListBox.hpp
//
// Description:		ListBox classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *********************************************************************************************************************

#ifndef DGLISTBOX_HPP
#define DGLISTBOX_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "UniString.hpp"

#include "Color.hpp"

#include "DGDefs.h"
#include "DGItemProperty.hpp"

#include "DGItemEventArgs.hpp"
#include "DGEventNotifier.hpp"

// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace DG {
	class ListBox;
}


// --- Class declarations ----------------------------------------------------------------------------------------------

namespace DG {

// --- ListBoxDropSourceEvent ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxDragSourceEvent: public ItemDragSourceEvent
{
friend class ListBoxObserver;				// To access protected constructor
friend class ListBoxDragSourceObserver;		// To access protected constructor

protected:
	explicit ListBoxDragSourceEvent (const ItemDragSourceEvent& ev);

public:
	~ListBoxDragSourceEvent ();

	ListBox*	GetSource (void) const;
};


// --- ListBoxDragSourceObserver ---------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxDragSourceObserver
{
protected:
	ListBoxDragSourceObserver ();

public:
	virtual ~ListBoxDragSourceObserver ();

	virtual void	ListBoxDragStarting (const ListBoxDragSourceEvent& ev, bool* canStart);
	virtual void	ListBoxDragStarted (const ListBoxDragSourceEvent& ev, UShort* effect);
	virtual void	ListBoxDragStarted (const ListBoxDragSourceEvent& ev, UShort* effect, bool* rightDragMenu);
	virtual void	ListBoxDragEnded (const ListBoxDragSourceEvent& ev, DragDrop::Effect effect);
	virtual void	ListBoxDragSetDelayedData (const ListBoxDragSourceEvent& ev);
};


// --- ListBoxDragTargetEvent ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxDropTargetEvent: public ItemDropTargetEvent
{
friend class ListBoxObserver;				// To access protected constructor
friend class ListBoxDropTargetObserver;		// To access protected constructor

private:
	short	insertPos;
	short	relativePos;

protected:
	explicit ListBoxDropTargetEvent (const ItemDropTargetEvent& ev);

public:
	~ListBoxDropTargetEvent ();

	short					  GetInsertPosition (void) const;
	DG::DragDrop::RelativePos GetRelativePosition (void) const;
	ListBox*				  GetSource (void) const;
};


// --- ListBoxDropTargetObserver ---------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxDropTargetObserver
{
protected:
	ListBoxDropTargetObserver ();

public:
	virtual ~ListBoxDropTargetObserver ();

	virtual void	ListBoxDragEntered (const ListBoxDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour);
	virtual void	ListBoxDragEntered (const ListBoxDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour,
										bool* rightDragMenu);
	virtual void	ListBoxDragMoved (const ListBoxDropTargetEvent& ev, DragDrop::Effect* effect,
									  DragDrop::Feedback* denyFeedback);
	virtual void	ListBoxDragLeft (const ListBoxDropTargetEvent& ev, DragDrop::Effect* effect);
	virtual void	ListBoxDropped (const ListBoxDropTargetEvent& ev, DragDrop::Effect* effect);
};


// --- ListBoxEventProperty --------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxEventProperty
{
private:
	const DG::ListBoxItemMouseEventArg*	listMsgData;

protected:
	explicit ListBoxEventProperty (const DG::EventArg& msgData);

public:
	virtual ~ListBoxEventProperty ();

	short	GetListItem (void) const;
	short	GetTabFieldIndex (void) const;

	Point	GetMouseOffset (void) const;

	bool	IsCommandPressed (void) const;
	bool	IsOptionPressed (void) const;
	bool	IsShiftPressed (void) const;
};


// --- ListBoxSelectionEvent -------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxSelectionEvent: public ItemChangeEvent
{
friend class ListBoxObserver;				// To access protected constructor

protected:
	explicit ListBoxSelectionEvent (const ItemChangeEvent& ev);

public:
	~ListBoxSelectionEvent ();

	ListBox*	GetSource (void) const;
};


// --- ListBoxDragEvent ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxDragEvent: public ItemChangeEvent
{
friend class ListBoxObserver;				// To access protected constructor

private:
	short	previousIndex;
	short	newIndex;

protected:
	explicit ListBoxDragEvent (const ItemChangeEvent& ev);

public:
	~ListBoxDragEvent ();

	ListBox*	GetSource (void) const;

	short	GetPreviousIndex (void) const;
	short	GetNewIndex (void) const;
};


// --- ListBoxClickEvent -----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxClickEvent: public ItemClickEvent,
									   public ListBoxEventProperty
{
friend class ListBoxObserver;				// To access protected constructor

protected:
	explicit ListBoxClickEvent (const ItemClickEvent& ev);

public:
	~ListBoxClickEvent ();

	ListBox*	GetSource (void) const;
};


// --- ListBoxMouseDownEvent -------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxMouseDownEvent: public ItemMouseDownEvent,
										   public ListBoxEventProperty
{
	friend class ListBoxObserver;				// To access protected constructor

protected:
	explicit ListBoxMouseDownEvent (const ItemMouseDownEvent& ev);

public:
	~ListBoxMouseDownEvent ();

	ListBox*	GetSource (void) const;
};


// --- ListBoxContextMenuEvent -----------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxContextMenuEvent: public ItemContextMenuEvent
{
friend class ListBoxObserver;				// To access protected constructor

protected:
	explicit ListBoxContextMenuEvent (const ItemContextMenuEvent& ev);

public:
	~ListBoxContextMenuEvent ();

	ListBox*	GetSource (void) const;
	short		GetItem (void) const;
	short		GetHeaderItem (void) const;
	bool		IsInHeaderButton (void) const;
};


// --- ListBoxDoubleClickEvent -----------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxDoubleClickEvent: public ItemDoubleClickEvent,
											 public ListBoxEventProperty
{
friend class ListBoxObserver;				// To access protected constructor

protected:
	explicit ListBoxDoubleClickEvent (const ItemDoubleClickEvent& ev);

public:
	~ListBoxDoubleClickEvent ();

	ListBox*	GetSource (void) const;
};


// --- ListBoxMouseMoveEvent -------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxMouseMoveEvent: public ItemMouseMoveEvent,
										   public ListBoxEventProperty
{
friend class ListBoxObserver;				// To access protected constructor

protected:
	explicit ListBoxMouseMoveEvent (const ItemMouseMoveEvent& ev);

public:
	~ListBoxMouseMoveEvent ();

	ListBox*	GetSource (void) const;
};


// --- ListBoxItemUpdateEvent ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxItemUpdateEvent: public ItemUpdateEvent
{
friend class ListBoxObserver;				// To access protected constructor

private:
	const DG::ListBoxUpdateEventArg*	updateData;

protected:
	explicit ListBoxItemUpdateEvent (const ItemUpdateEvent& ev);

public:
	~ListBoxItemUpdateEvent ();

	ListBox*	GetSource (void) const;

	short	GetListItem (void) const;

	void*	GetDrawContext (void) const;

	short	GetWidth (void) const;
	short	GetHeight (void) const;

	bool	IsUpdatedListItemHighlighted (void) const;

	Gfx::Color	GetForeColor (void) const;
	Gfx::Color	GetBackColor (void) const;
};


// --- ListBoxTabItemUpdateEvent ---------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxTabItemUpdateEvent: public ItemUpdateEvent
{
friend class ListBoxObserver;				// To access protected constructor

private:
	const ListBoxUpdateEventArg*	updateData;

protected:
	explicit ListBoxTabItemUpdateEvent (const ItemUpdateEvent& ev);

public:
	~ListBoxTabItemUpdateEvent ();

	ListBox*	GetSource (void) const;

	short	GetListItem (void) const;
	short	GetTabFieldIndex (void) const;

	void*	GetDrawContext (void) const;

	short	GetWidth (void) const;
	short	GetHeight (void) const;

	bool	IsUpdatedListItemHighlighted (void) const;

	GS::UniString	GetTabItemText (void) const;

	Gfx::Color	GetForeColor (void) const;
	Gfx::Color	GetBackColor (void) const;
};


// --- ListBoxHoverEvent ------------------------------------------------------

class DG_DLL_EXPORT ListBoxHoverEvent : public ItemHoverEvent
{
	friend class ListBoxObserver;				// To access protected constructor

private:
	short	listItem;

protected:
	ListBoxHoverEvent (const ItemHoverEvent& ev);

public:
	~ListBoxHoverEvent();

	ListBox*	GetSource (void) const;
	short	GetListItem (void) const;
};


// --- ListBoxHeaderItemClickEvent -------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxHeaderItemClickEvent: public ItemEvent
{
friend class ListBox;				// To access protected constructor
friend class ListBoxObserver;
private:
	const ListBoxHeaderEventArg*	listHeaderMsgData;

protected:
	explicit ListBoxHeaderItemClickEvent (ListBox* source, const DG::EventArg& msgData);

public:
	~ListBoxHeaderItemClickEvent ();

	ListBox*	GetSource (void) const;

	short	GetHeaderItem (void) const;
};


// --- ListBoxHeaderItemDragEvent --------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxHeaderItemDragEvent: public ItemEvent
{
friend class ListBox;				// To access protected constructor
friend class ListBoxObserver;
private:
	const DG::ListBoxHeaderEventArg*	listHeaderMsgData;

protected:
	explicit ListBoxHeaderItemDragEvent (ListBox* source, const DG::EventArg& msgData);

public:
	~ListBoxHeaderItemDragEvent ();

	ListBox*	GetSource (void) const;

	short	GetOldPos (void) const;
	short	GetNewPos (void) const;
};


// --- ListBoxHeaderItemResizeEvent ------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxHeaderItemResizeEvent: public ItemEvent
{
friend class ListBox;				// To access protected constructor
friend class ListBoxObserver;
private:
	const DG::ListBoxHeaderEventArg*	listHeaderMsgData;

protected:
	explicit ListBoxHeaderItemResizeEvent (ListBox* source, const DG::EventArg& msgData);

public:
	~ListBoxHeaderItemResizeEvent ();

	ListBox*	GetSource (void) const;

	short	GetHeaderItem (void) const;
	short	GetChange (void) const;
};


// --- ListBoxHeaderButtonClickEvent -----------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxHeaderButtonClickEvent: public ItemEvent
{
friend class ListBox;				// To access protected constructor
friend class ListBoxObserver;
private:
	const DG::ListBoxHeaderEventArg*	listHeaderMsgData;

protected:
	explicit ListBoxHeaderButtonClickEvent (ListBox* source, const DG::EventArg& msgData);

public:
	~ListBoxHeaderButtonClickEvent ();

	ListBox*	GetSource (void) const;
};


// --- ListBoxObserver -------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBoxObserver: public ItemObserver,
									 public ListBoxDragSourceObserver,
									 public ListBoxDropTargetObserver
{
friend class ListBox;

protected:
	virtual short	SpecChangeRequested (const ItemMouseDownEvent& ev) override;
	virtual short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual short	SpecClicked (const ItemClickEvent& ev) override;
	virtual short	SpecMouseDown (const ItemMouseDownEvent& ev, bool* processed) override;
	virtual short	SpecContextMenuRequested (const ItemContextMenuEvent& ev) override;
	virtual short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;
	virtual short	SpecMouseMoved (const ItemMouseMoveEvent& ev) override;
	virtual short	SpecUpdate (const ItemUpdateEvent& ev) override;

	virtual short	SpecDragStarting (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragStarted (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragEnded (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragSetDelayedData (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragEntered (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDragMoved (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDragLeft (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDropped (const ItemDropTargetEvent& ev) override;
	virtual short	SpecHoverStarted (const ItemHoverEvent& ev) override;
	virtual short	SpecHoverEnded (const ItemHoverEvent& ev) override;
	virtual	short	SpecOverlayUpdate (const ItemUpdateEvent& ev) override;

	virtual bool	ListBoxSelectionChangeRequested (const ListBoxMouseDownEvent& ev);
	virtual void	ListBoxSelectionChanged (const ListBoxSelectionEvent& ev);
	virtual void	ListBoxItemDragged (const ListBoxDragEvent& ev);
	virtual void	ListBoxClicked (const ListBoxClickEvent& ev);
	virtual void	ListBoxMouseDown (const ListBoxMouseDownEvent& ev, bool* processed);
	virtual void	ListBoxContextMenuRequested (const ListBoxContextMenuEvent& ev, bool* processed);
	virtual void	ListBoxDoubleClicked (const ListBoxDoubleClickEvent& ev);
	virtual void	ListBoxMouseMoved (const ListBoxMouseMoveEvent& ev, short* inArea);
	virtual void	ListBoxItemUpdate (const ListBoxItemUpdateEvent& ev);
	virtual void	ListBoxTabFieldUpdate (const ListBoxTabItemUpdateEvent& ev);
	virtual void	ListBoxHoverStarted (const ListBoxHoverEvent& ev);
	virtual void	ListBoxHoverEnded (const ListBoxHoverEvent& ev);
	virtual void	ListBoxOverlayUpdate (const ListBoxItemUpdateEvent& ev, Rect* imageRect);

	virtual void	ListBoxHeaderItemClicked (const ListBoxHeaderItemClickEvent& ev);
	virtual void	ListBoxHeaderItemDragged (const ListBoxHeaderItemDragEvent& ev);
	virtual short	ListBoxHeaderItemResizeEntered (const ListBoxHeaderItemResizeEvent& ev);
	virtual short	ListBoxHeaderItemResized (const ListBoxHeaderItemResizeEvent& ev);
	virtual short	ListBoxHeaderItemResizeExited (const ListBoxHeaderItemResizeEvent& ev);
	virtual void	ListBoxHeaderButtonClicked (const ListBoxHeaderButtonClickEvent& ev);

public:
	ListBoxObserver ();
   ~ListBoxObserver ();
};


// --- ListBox ---------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListBox: public Item,
							 public ItemFontProperty,
							 public FocusableProperty,
							 public ListBoxNotifyHandler,
							 public ItemDragDropNotifier<ListBox>,
							 public ItemWheelNotifier<ListBox>,
							 public ItemFocusNotifier<ListBox>
{
public:
	enum ScrollType {
		NoScroll		= DG_LT_NOSCROLL,
		VScroll			= DG_LT_VSCROLL,
		HScroll			= DG_LT_HSCROLL,
		HVScroll		= DG_LT_HSCROLL | DG_LT_VSCROLL
	};

	enum PartialItemType {
		PartialItems	= 0,
		NoPartialItems	= DG_LT_NOPARTIALITEMS
	};

	enum HeaderFlag {
		NoHeader		= 0,
		Header			= DG_LT_HEADER
	};

	enum FrameType {
		NoFrame			= 0,
		Frame			= DG_LT_FRAME,
	};

	enum ItemType {
		AllItems		= DG_ALL_ITEMS,
		TopItem			= DG_LIST_TOP,
		BottomItem		= DG_LIST_BOTTOM
	};

	enum Justification {
		Left			= DG_IS_LEFT,
		Center			= DG_IS_CENTER,
		Right			= DG_IS_RIGHT,
		DefaultJust		= DG_IS_DEFAULT
	};

	enum Truncation {
		NoTruncate		= DG_IS_NOTRUNC,
		EndTruncate		= DG_IS_TRUNCEND,
		MiddleTruncate	= DG_IS_TRUNCMIDDLE,
		DefaultTrunc	= DG_IS_DEFAULT
	};

	enum ItemStatus {
		Enabled			= DG_IS_ENABLE,
		Grayed			= DG_IS_GRAY,
		Disabled		= DG_IS_DISABLE
	};

	enum SpecialIcons {
		NoIcon					= DG_NO_ICON,
		DragIcon				= DG_LIST_DRAGICON,
		CheckedIcon				= DG_LIST_CHECKEDICON,
		UncheckedIcon			= DG_LIST_UNCHECKEDICON,
		MixedCheckedIcon		= DG_LIST_MIXEDCHECKEDICON,
		GrayCheckedIcon			= DG_LIST_GRAYCHECKEDICON,
		GrayUncheckedIcon		= DG_LIST_GRAYUNCHECKEDICON,
		GrayMixedCheckedIcon	= DG_LIST_GRAYMIXEDCHECKEDICON,
		FramelessCheckIcon		= DG_LIST_FRAMELESSCHECKICON,
		FramelessGrayCheckIcon	= DG_LIST_FRAMELESSGRAYCHECKICON
	};

	enum SpecialArea {
		NoSpecArea		= DG_LIST_NOSPECAREA,
		DragArea		= DG_LIST_INDRAGAREA,
		UserArea		= DG_LIST_INUSERAREA
	};

	enum HelpStyle {
		HSNormal		= DG_LISTHS_NORMAL,
		HSForItem		= DG_LISTHS_FORITEM
	};

	enum ArrowType {
		NoArrow			= DG_LHA_NONE,
		Up				= DG_LHA_UP,
		Down			= DG_LHA_DOWN,
		DoubleUp		= DG_LHA_DOUBLEUP,
		DoubleDown		= DG_LHA_DOUBLEDOWN
	};


private:
	void	ProcessListBoxHeaderClickEvent (const DG::EventArg& msgData);
	void	ProcessListBoxHeaderDragEvent (const DG::EventArg& msgData);
	short	ProcessListBoxHeaderResizeEvent (const DG::EventArg& msgData);
	void	ProcessListBoxHeaderButtonClickEvent (const DG::EventArg& msgData);

	void 	InitNotifiers ();

	virtual void	NotifyItemClickEvent (const ListBoxItemMouseEventArg& eventArg) override;
	virtual void	NotifyItemDoubleClickEvent (const ListBoxItemMouseEventArg& eventArg) override;
	virtual short	NotifyItemMouseMoveEvent (const ListBoxItemMouseEventArg& eventArg) override;
	virtual bool	NotifyItemMouseDownEvent (const ListBoxItemMouseEventArg& eventArg) override;

	virtual void	NotifyHeaderItemClickEvent (const ListBoxHeaderEventArg& eventArg) override;
	virtual void	NotifyHeaderItemDragEvent (const ListBoxHeaderEventArg& eventArg) override;
	virtual short	NotifyHeaderItemResizeEnterEvent (const ListBoxHeaderEventArg& eventArg) override;
	virtual short	NotifyHeaderItemResizeEvent (const ListBoxHeaderEventArg& eventArg) override;
	virtual short	NotifyHeaderItemResizeExitEvent (const ListBoxHeaderEventArg& eventArg) override;
	virtual void	NotifyHeaderButtonClickEvent (const ListBoxHeaderEventArg& eventArg) override;

	virtual short	NotifyItemHoverStartEvent (const ListBoxItemHoverEventArg& eventArg) override;
	virtual short	NotifyItemHoverEndEvent (const ListBoxItemHoverEventArg& eventArg) override;

	virtual bool	NotifySelectionChangeRequestEvent (const ListBoxItemMouseEventArg& eventArg) override;
	virtual void	NotifySelectionChangeEvent (const ItemSelectionChangeEventArg& /*eventArg*/) override;

	virtual void	NotifyItemUpdateEvent (ListBoxUpdateEventArg& /*eventArg*/) override;
	virtual void	NotifyItemOverlayUpdateEvent (const ListBoxUpdateEventArg& /*eventArg*/) override;

protected:
	ListBox ();
	ListBox (const Panel& panel, short item);

public:
	~ListBox ();

	EventNotifier<ListBox, const ListBoxItemMouseEventArg> onMouseClick;
	EventNotifier<ListBox, const ListBoxItemMouseEventArg> onMouseDoubleClick;
	EventNotifier<ListBox, const ListBoxItemMouseEventArg, short> onMouseMove;
	EventNotifier<ListBox, const ListBoxItemMouseEventArg, bool, false> onMouseDown;

	EventNotifier<ListBox, const ListBoxHeaderEventArg> onHeaderItemClick;
	EventNotifier<ListBox, const ListBoxHeaderEventArg> onHeaderItemDrag;
	EventNotifier<ListBox, const ListBoxHeaderEventArg, short> onHeaderItemResizeEnter;
	EventNotifier<ListBox, const ListBoxHeaderEventArg, short> onHeaderItemResize;
	EventNotifier<ListBox, const ListBoxHeaderEventArg, short> onHeaderItemResizeExit;
	EventNotifier<ListBox, const ListBoxHeaderEventArg> onHeaderButtonClick;

	EventNotifier<ListBox, const ListBoxItemHoverEventArg, short> onHoverStarted;
	EventNotifier<ListBox, const ListBoxItemHoverEventArg, short> onHoverEnded;

	EventNotifier<ListBox, const ListBoxItemMouseEventArg, bool, false> onSelectionChangeRequested;
	EventNotifier<ListBox, const ItemSelectionChangeEventArg> onSelectionChanged;

	EventNotifier<ListBox, ListBoxUpdateEventArg> onItemUpdate;
	EventNotifier<ListBox, const ListBoxUpdateEventArg> onItemOverlayUpdated;

	void	Attach (ListBoxObserver& observer);
	void	Detach (ListBoxObserver& observer);

	bool	AppendItem (void);
	bool	InsertItem (short listItem);
	void	DeleteItem (short listItem);
	short	GetItemCount (void) const;

	bool	InsertSeparator (short listItem);
	bool	IsSeparator (short listItem) const;

	bool	HasHeader (void) const;
	short	GetHeaderHeight (void) const;

	void	SetHeaderSynchronState (bool isSynchron);
	bool	IsHeaderInSynchronState (void) const;

	void	SetHeaderPushableButtons (bool hasPushableButtons);
	bool	HasHeaderPushableButtons (void) const;

	void	SetHeaderDragableButtons (bool hasDragableButtons);
	bool	HasHeaderDragableButtons (void) const;

	void	SetHeaderItemCount (short itemCount);
	short	GetHeaderItemCount (void) const;

	void			SetHeaderItemText (short headerItem, const GS::UniString& text);
	GS::UniString	GetHeaderItemText (short headerItem) const;

	void		SetHeaderItemIcon (short headerItem, const DG::Icon& icon);
	DG::Icon	GetHeaderItemIcon (short headerItem) const;

	void		SetHeaderItemFont (short headerItem, Font::Size size, Font::Style style);
	Font::Size	GetHeaderItemFontSize (short headerItem) const;
	Font::Style	GetHeaderItemFontStyle (short headerItem) const;

	void			SetHeaderItemStyle (short headerItem, Justification just, Truncation trunc);
	Justification	GetHeaderItemJustification (short headerItem) const;
	Truncation		GetHeaderItemTruncation (short headerItem) const;

	void	SetHeaderItemSizeableFlag (short headerItem, bool isSizeable);
	bool	IsHeaderItemSizeable (short headerItem) const;

	void	SetHeaderItemSize (short headerItem, short size);
	short	GetHeaderItemSize (short headerItem) const;

	void	SetHeaderItemMinSize (short headerItem, short minSize);
	short	GetHeaderItemMinSize (short headerItem) const;

	void		SetHeaderItemArrowType (short headerItem, ArrowType arrowType);
	ArrowType	GetHeaderItemArrowType (short headerItem) const;

	void		SetHeaderButtonIcon (const DG::Icon& icon);
	DG::Icon	GetHeaderButtonIcon (void) const;

	void		EnableHeaderButton (void);
	void		DisableHeaderButton (void);
	bool		IsHeaderButtonEnabled (void) const;

	bool	SetTabFieldCount (short nTabFields);
	short	GetTabFieldCount (void) const;

	void	SetTabFieldProperties (short tabIndex, short begPos, short endPos, Justification just, Truncation trunc,
								   bool hasSeparator = false, bool status = true);
	void	SetTabFieldBeginEndPosition (short tabIndex, short begPos, short endPos);
	void	SetTabFieldJustification (short tabIndex, Justification just);
	void	SetTabFieldTruncation (short tabIndex, Truncation trunc);
	void	SetTabFieldSeparator (short tabIndex, bool hasSeparator);
	void	SetTabFieldStatus (short tabIndex, bool status);

	short			GetTabFieldBeginPosition (short tabIndex) const;
	short			GetTabFieldEndPosition (short tabIndex) const;
	short			GetTabFieldWidth (short tabIndex) const;
	Justification	GetTabFieldJustification (short tabIndex) const;
	Truncation		GetTabFieldTruncation (short tabIndex) const;
	bool			HasTabFieldSeparator (short tabIndex) const;
	bool			IsTabFieldEnabled (short tabIndex) const;

	void	SetTabFieldOwnerDrawFlag (short tabIndex, bool ownerDraw);
	bool	GetTabFieldOwnerDrawFlag (short tabIndex) const;

	void	SetTabFieldToSearch (short tabIndex);
	short	GetTabFieldToSearch (void) const;

	void		SetTabItemText (short listItem, short tabIndex, const GS::UniString& text);
	GS::UniString GetTabItemText (short listItem, short tabIndex) const;

	void		SetTabItemIcon (short listItem, short tabIndex, const DG::Icon& icon);
	DG::Icon	GetTabItemIcon (short listItem, short tabIndex) const;

	void		SetTabItemFontStyle (short listItem, short tabIndex, Font::Style style);
	Font::Style	GetTabItemFontStyle (short listItem, short tabIndex) const;

	void	SetTabItemColor (short listItem, short tabIndex, const Gfx::Color& color);
	void	SetTabItemBackgroundColor (short listItem, short tabIndex, const Gfx::Color& color);
	bool	GetTabItemColor (short listItem, short tabIndex, Gfx::Color* color) const;
	bool	GetTabItemBackgroundColor (short listItem, short tabIndex, Gfx::Color* color) const;

	void			SetTabItemDescription (short listItem, short tabIndex, const GS::UniString& description);
	GS::UniString	GetTabItemDescription (short listItem, short tabIndex) const;

	void	SetOnTabItem (short tabIndex, const Item& item);
	void	RemoveOnTabItem (short tabIndex);
	Item*	GetOnTabItem (short tabIndex) const;

	void		SetItemFontStyle (short listItem, Font::Style style);
	Font::Style	GetItemFontStyle (short listItem) const;

	void	SetItemColor (short listItem, const Gfx::Color& color);
	void	SetItemBackgroundColor (short listItem, const Gfx::Color& color);
	void	ResetItemColor (short listItem);
	void	ResetItemBackgroundColor (short listItem);
	bool	GetItemColor (short listItem, Gfx::Color* color) const;
	bool	GetItemBackgroundColor (short listItem, Gfx::Color* color) const;

	void	SetItemValue (short listItem, DGUserData value);
	DGUserData	GetItemValue (short listItem) const;

	void					SetItemObjectData (short listItem, GS::Ref<GS::Object> object);
	GS::Ref<GS::Object>		GetItemObjectData (short listItem) const;

	void		SetItemStatus (short listItem, ItemStatus status);
	ItemStatus	GetItemStatus (short listItem) const;

	void	EnableItem (short listItem);
	void	GrayItem (short listItem);
	void	DisableItem (short listItem);

	bool	IsItemEnabled (short listItem) const;
	bool	IsItemGrayed (short listItem) const;
	bool	IsItemDisabled (short listItem) const;
	bool	IsItemVisible (short listItem) const;

	void	SetItemOwnerDrawFlag (short listItem, bool isOwnerDrawn);
	bool	GetItemOwnerDrawFlag (short listItem) const;

	void	SetItemHeight (short itemHeight);
	short	GetItemHeight (void) const;
	short	GetItemWidth (void) const;
	bool	GetItemRect (short listItem, Rect* rect) const;
	void	SetNoPartialItem (void);

	void	EnableSeparatorLines (bool hasSeparatorLines);
	bool	HasSeparatorLines (void) const;
	void				SetSeparatorLineColor (const Gfx::Color& color);
	const Gfx::Color	GetSeparatorLineColor (void) const;

	void	SelectItem (short listItem);
	void	SelectItems (const GS::Array<short>& listItems);
	void	DeselectItem (short listItem);
	short	GetSelectedCount (void) const;
	short	GetSelectedItem (short listItem = TopItem) const;
	short	GetSelectedItems (short* selItems, short maxCount) const;
	GS::Array<short>	GetSelectedItems (void) const;

	void	EnableDraw (void);
	void	DisableDraw (void);
	void	RedrawItem (short listItem);
	void	RedrawTabItem (short listItem, short tabIndex);

	void	EnableMouseMoveEvent (void);
	void	EnableHoverEvent (void);


	void	SetScrollPosition (short scrollPosition);
	short	GetScrollPosition (void) const;
	void	ScrollUp (void);
	void	ScrollDown (void);
	void	SetHScrollPosition (short scrollPosition);
	short	GetHScrollPosition (void) const;

	short	GetItemFromPosition (const Point& pos) const;

	void			SetHelpStyle (HelpStyle helpStyle);
	HelpStyle		GetHelpStyle (void);

    virtual GSErrCode Store (GS::ObjectState& os) const override;
};


// --- SingleSelListBox ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT SingleSelListBox: public ListBox
{
public:
	SingleSelListBox (const Panel& panel, short item);
	SingleSelListBox (const Panel& panel, const Rect& rect, ScrollType scroll = VScroll,
					  PartialItemType part = PartialItems, HeaderFlag headerFlag = NoHeader,
					  short headerSize = 0, FrameType frameType = NoFrame);
   ~SingleSelListBox ();
};


// --- MultiSelListBox -------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT MultiSelListBox: public ListBox
{
public:
	MultiSelListBox (const Panel& panel, short item);
	MultiSelListBox (const Panel& panel, const Rect& rect, ScrollType scroll = VScroll,
					 PartialItemType part = PartialItems, HeaderFlag headerFlag = NoHeader,
					 short headerSize = 0, FrameType frameType = NoFrame);
   ~MultiSelListBox ();
};

}	// namespace DG

#endif
