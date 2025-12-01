// *****************************************************************************
// File:			DGListView.hpp
//
// Description:		ListView classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGLISTVIEW_HPP
#define DGLISTVIEW_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "UniString.hpp"

#include "Color.hpp"

#include "DGItemProperty.hpp"

#include "DGItemEventArgs.hpp"
#include "DGEventNotifier.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class ListView;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- ListViewDropSourceEvent -------------------------------------------------

class DG_DLL_EXPORT ListViewDragSourceEvent: public ItemDragSourceEvent
{
friend class ListViewObserver;				// To access protected constructor
friend class ListViewDragSourceObserver;	// To access protected constructor

protected:
	explicit ListViewDragSourceEvent (const ItemDragSourceEvent& ev);

public:
	~ListViewDragSourceEvent ();

	ListView*	GetSource (void) const;
};


// --- ListViewDragSourceObserver ----------------------------------------------

class DG_DLL_EXPORT ListViewDragSourceObserver
{
protected:
	ListViewDragSourceObserver ();

public:
	virtual ~ListViewDragSourceObserver ();

	virtual void	ListViewDragStarting (const ListViewDragSourceEvent& ev, bool* canStart);
	virtual void	ListViewDragStarted (const ListViewDragSourceEvent& ev, UShort* effect);
	virtual void	ListViewDragStarted (const ListViewDragSourceEvent& ev, UShort* effect, bool* rightDragMenu);
	virtual void	ListViewDragEnded (const ListViewDragSourceEvent& ev, DragDrop::Effect effect);
	virtual void	ListViewDragSetDelayedData (const ListViewDragSourceEvent& ev);
};


// --- ListViewDragTargetEvent -------------------------------------------------

class DG_DLL_EXPORT ListViewDropTargetEvent: public ItemDropTargetEvent
{
friend class ListViewObserver;				// To access protected constructor
friend class ListViewDropTargetObserver;	// To access protected constructor

private:
	short	insertPos;

protected:
	explicit ListViewDropTargetEvent (const ItemDropTargetEvent& ev);

public:
	~ListViewDropTargetEvent ();

	short		GetInsertPosition (void) const;
	ListView*	GetSource (void) const;
};


// --- ListViewDropTargetObserver ----------------------------------------------

class DG_DLL_EXPORT ListViewDropTargetObserver
{
protected:
	ListViewDropTargetObserver ();

public:
	virtual ~ListViewDropTargetObserver ();

	virtual void	ListViewDragEntered (const ListViewDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour);
	virtual void	ListViewDragEntered (const ListViewDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour,
										 bool* rightDragMenu);
	virtual void	ListViewDragMoved (const ListViewDropTargetEvent& ev, DragDrop::Effect* effect,
									   DragDrop::Feedback* denyFeedback);
	virtual void	ListViewDragLeft (const ListViewDropTargetEvent& ev, DragDrop::Effect* effect);
	virtual void	ListViewDropped (const ListViewDropTargetEvent& ev, DragDrop::Effect* effect);
};


// --- ListViewSelectionEvent --------------------------------------------------

class DG_DLL_EXPORT ListViewSelectionEvent: public ItemChangeEvent
{
friend class ListViewObserver;				// To access protected constructor

protected:
	explicit ListViewSelectionEvent (const ItemChangeEvent& ev);

public:
	~ListViewSelectionEvent ();

	ListView*	GetSource (void) const;
};


// --- ListViewContextMenuEvent ------------------------------------------------

class DG_DLL_EXPORT ListViewContextMenuEvent: public ItemContextMenuEvent
{
friend class ListViewObserver;				// To access protected constructor

protected:
	explicit ListViewContextMenuEvent (const ItemContextMenuEvent& ev);

public:
	~ListViewContextMenuEvent ();

	ListView*	GetSource (void) const;
	short		GetItem   (void) const;
};


// --- ListViewMouseDownEvent ------------------------------------------------

class DG_DLL_EXPORT ListViewMouseDownEvent: public ItemMouseDownEvent
{
friend class ListViewObserver;				// To access protected constructor

protected:
	explicit ListViewMouseDownEvent (const ItemMouseDownEvent& ev);

public:
	~ListViewMouseDownEvent ();

	ListView*	GetSource (void) const;

	short	GetListItem (void) const;
	bool	IsHovered (void) const;
};


// --- ListViewDoubleClickEvent ------------------------------------------------

class DG_DLL_EXPORT ListViewDoubleClickEvent: public ItemDoubleClickEvent
{
friend class ListViewObserver;				// To access protected constructor

private:
	short	listItem;

protected:
	explicit ListViewDoubleClickEvent (const ItemDoubleClickEvent& ev);

public:
	~ListViewDoubleClickEvent ();

	ListView*	GetSource (void) const;

	short	GetListItem (void) const;
};


// --- ListViewMouseMoveEvent -------------------------------------------------------------------------------------------

class DG_DLL_EXPORT ListViewMouseMoveEvent: public ItemMouseMoveEvent
{
	friend class ListViewObserver;				// To access protected constructor

private:
	short	listItem;

protected:
	explicit ListViewMouseMoveEvent (const ItemMouseMoveEvent& ev);

public:
	~ListViewMouseMoveEvent ();

	ListView*	GetSource (void) const;

	short	GetListItem (void) const;
};


// --- ListViewUpdateEvent -----------------------------------------------------

class DG_DLL_EXPORT ListViewUpdateEvent: public ItemUpdateEvent
{
friend class ListViewObserver;				// To access protected constructor

private:
	ListViewUpdateEventArg*	updateData;

protected:
	explicit ListViewUpdateEvent (const ItemUpdateEvent& ev);

public:
	~ListViewUpdateEvent ();

	ListView*	GetSource (void) const;

	short	GetListItem (void) const;

	void*	GetDrawContext (void) const;

	short	GetWidth (void) const;
	short	GetHeight (void) const;
};


// --- ListViewHoverEvent ------------------------------------------------------

class DG_DLL_EXPORT ListViewHoverEvent : public ItemHoverEvent
{
friend class ListViewObserver;				// To access protected constructor

private:
	short	listItem;

protected:
	ListViewHoverEvent (const ItemHoverEvent& ev);

public:
	~ListViewHoverEvent();

	ListView*	GetSource (void) const;
	short	GetListItem (void) const;
};


// --- ListViewPressedEvent ----------------------------------------------------

class DG_DLL_EXPORT ListViewPressedEvent : public ItemPressedEvent
{
	friend class ListViewObserver;				// To access protected constructor

private:
	short	listItem;

protected:
	ListViewPressedEvent (const ItemPressedEvent& ev);

public:
	ListViewPressedEvent (const ListViewMouseDownEvent& ev);

	ListViewPressedEvent (Item* source, const DG::EventArg& msgData);

	~ListViewPressedEvent ();

	ListView*	GetSource (void) const;
	short	GetListItem (void) const;
};


// --- ListViewObserver --------------------------------------------------------

class DG_DLL_EXPORT ListViewObserver: public ItemObserver,
									  public ListViewDragSourceObserver,
									  public ListViewDropTargetObserver
{
protected:
	virtual	short	SpecChangeRequested (const ItemMouseDownEvent& ev) override;
	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual short	SpecMouseDown (const ItemMouseDownEvent& ev, bool* processed) override;
	virtual short	SpecContextMenuRequested (const ItemContextMenuEvent& ev) override;
	virtual	short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;
	virtual short	SpecMouseMoved (const ItemMouseMoveEvent& ev) override;
	virtual	short	SpecUpdate (const ItemUpdateEvent& ev) override;

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
	virtual short	SpecPressed (const ItemPressedEvent& ev) override;
	virtual	short	SpecOverlayUpdate (const ItemUpdateEvent& ev) override;

	virtual bool	ListViewSelectionChangeRequested (const ListViewMouseDownEvent& ev);
	virtual void	ListViewSelectionChanged (const ListViewSelectionEvent& ev);
	virtual void	ListViewContextMenuRequested (const ListViewContextMenuEvent& ev, bool* processed);
	virtual void	ListViewMouseDown (const ListViewMouseDownEvent& ev, bool* processed);
	virtual void	ListViewDoubleClicked (const ListViewDoubleClickEvent& ev);
	virtual void	ListViewMouseMoved (const ListViewMouseMoveEvent& ev);
	virtual void	ListViewItemUpdate (const ListViewUpdateEvent& ev, Rect* imageRect);
	virtual void	ListViewHoverStarted (const ListViewHoverEvent& ev);
	virtual void	ListViewHoverEnded (const ListViewHoverEvent& ev);
	virtual void	ListViewPressed (const ListViewPressedEvent& ev);
	virtual void	ListViewOverlayUpdate (const ListViewUpdateEvent& ev, Rect* imageRect);

public:
	ListViewObserver ();
   ~ListViewObserver ();
};


// --- ListView ----------------------------------------------------------------

class DG_DLL_EXPORT ListView: public Item,
							  public ItemFontProperty,
							  public FocusableProperty,
							  public ListViewNotifyHandler,
							  public ItemDragDropNotifier<ListView>,
							  public ItemWheelNotifier<ListView>,
							  public ItemFocusNotifier<ListView>
{
public:
	enum ViewMode {
		BottomText		= DG_LVVM_BOTTOMTEXT,
		RightText		= DG_LVVM_RIGHTTEXT,
		SingleColumn	= DG_LVVM_SINGLECOLUMN
	};

	enum ScrollType {
		Normal			= 0,
		HideScrollBar	= DG_LVST_HIDESCROLLBAR,
		ForceScrollBar	= DG_LVST_FORCESCROLLBAR
	};

	enum FrameType {
		NoFrame			= 0,
		Frame			= DG_LVFT_FRAME
	};

	enum ItemType {
		AllItems		= DG_ALL_ITEMS,
		TopItem			= DG_LIST_TOP,
		BottomItem		= DG_LIST_BOTTOM
	};

	enum ImageType {
		NoImage			= DG_LVIT_NOIMAGE,
		Icon			= DG_LVIT_ICON,
		Picture			= DG_LVIT_PICTURE,
		DIBitmap		= DG_LVIT_DIBITMAP,
		IconId			= DG_LVIT_ICONID,
		PictureId		= DG_LVIT_PICTUREID,
		ImageIndex		= DG_LVIT_IMAGEINDEX,
		OwnerDraw		= DG_LVIT_OWNERDRAW,
		ImageRef		= DG_LVIT_ICONIMAGEREF
	};

	enum Background {
		BGNormal		= DG_LVBG_NORMAL,
		BGButtonFace	= DG_LVBG_BUTTONFACE
	};

	enum SelectionStyle {
		SSNormal		= DG_LVSS_NORMAL,
		SSPush			= DG_LVSS_PUSH
	};

	enum HelpStyle {
		HSNormal		= DG_LVHS_NORMAL,
		HSForItem		= DG_LVHS_FORITEM
	};

private:
	void 	InitNotifiers ();

	virtual bool	NotifyItemMouseDownEvent (const ListViewItemMouseEventArg& eventArg) override;
	virtual bool	NotifySelectionChangeRequestEvent (const ListViewItemMouseEventArg& eventArg) override;

	virtual void	NotifyItemUpdateEvent (ListViewUpdateEventArg& /*eventArg*/) override;
	virtual void	NotifyItemOverlayUpdateEvent (const ListViewUpdateEventArg& /*eventArg*/) override;

	virtual short	NotifyItemMouseMoveEvent (const ListViewItemMouseMoveEventArg& eventArg) override;
	virtual short	NotifyItemDoubleClickEvent (const ListViewItemDoubleClickEventArg& eventArg) override;

	virtual short	NotifyItemHoverStartEvent (const ListViewItemHoverEventArg& eventArg) override;
	virtual short	NotifyItemHoverEndEvent (const ListViewItemHoverEventArg& eventArg) override;

	virtual short	NotifyItemPressEvent (const ListViewItemPressEventArg& eventArg) override;

protected:
	ListView ();
	ListView (const Panel& panel, short item);

public:
	~ListView ();

	EventNotifier<ListView, const ListViewItemMouseEventArg, bool, false> onMouseDown;
	EventNotifier<ListView, const ListViewItemMouseEventArg, bool, false> onSelectionChangeRequested;

	EventNotifier<ListView, ListViewUpdateEventArg> onItemUpdate;
	EventNotifier<ListView, const ListViewUpdateEventArg> onItemOverlayUpdated;

	EventNotifier<ListView, const ListViewItemMouseMoveEventArg, short> onMouseMove;
	EventNotifier<ListView, const ListViewItemDoubleClickEventArg, short> onItemDoubleClicked;

	EventNotifier<ListView, const ListViewItemHoverEventArg, short> onHoverStarted;
	EventNotifier<ListView, const ListViewItemHoverEventArg, short> onHoverEnded;

	EventNotifier<ListView, const ListViewItemPressEventArg, short> onItemPressed;

	void	Attach (ListViewObserver& observer);
	void	Detach (ListViewObserver& observer);

	void	AppendItem (void);
	void	InsertItem (short listItem);
	void	DeleteItem (short listItem);
	short	GetItemCount (void) const;

	void		SetItemText (short listItem, const GS::UniString& text);
	GS::UniString	GetItemText (short listItem) const;

	void			SetItemDescription (short listItem, const GS::UniString& description);
	GS::UniString	GetItemDescription (short listItem) const;

	ImageType	GetItemImageType (short listItem) const;

	void		SetItemIcon (short listItem, const DG::Icon& icon);
	DG::Icon	GetItemIcon (short listItem) const;

	void		SetItemPicture (short listItem, const DG::Picture& picture);
	DG::Picture	GetItemPicture (short listItem) const;

	void		SetItemImage (short listItem, ImageType imageType, const DG::Image& image);
	DG::Image	GetItemImage (short listItem) const;

	void		SetItemImageIndex (short listItem, short imageIndex);
	short		GetItemImageIndex (short listItem) const;

	void		SetItemImageOwnerDrawFlag (short listItem, bool flag = true);
	bool		IsItemImageOwnerDrawn (short listItem) const;

	void		SetItemFontStyle (short listItem, Font::Style style);
	Font::Style	GetItemFontStyle (short listItem) const;

	void	SetItemColor (short listItem, const Gfx::Color& color);
	bool	GetItemColor (short listItem, Gfx::Color* color) const;

	void		SetBackground (Background background);
	Background	GetBackground (void) const;

	void			SetSelectionStyle (SelectionStyle selectionStyle);
	SelectionStyle	GetSelectionStyle (void) const;

	void			SetHelpStyle (HelpStyle helpStyle);
	HelpStyle		GetHelpStyle (void);

	short	GetClientWidth (void) const;
	short	GetClientHeight (void) const;

	short	GetRowHeight (void) const;

	bool	HasVerticalScrollBar (void) const;
	bool	IsVerticalScrollBarVisible (void) const;

	void		SetItemValue (short listItem, DGUserData value);
	DGUserData	GetItemValue (short listItem) const;

	void					SetItemObjectData (short listItem, GS::Ref<GS::Object> object);
	GS::Ref<GS::Object>		GetItemObjectData (short listItem) const;

	void	EnableItem (short listItem);
	void	DisableItem (short listItem);
	void	SetItemStatus (short listItem, bool enable);
	bool	IsItemEnabled (short listItem) const;

	bool	IsItemVisible (short listItem) const;

	void				SelectItem (short listItem);
	void				SelectItems (const GS::Array<short>& listItems);
	void				DeselectItem (short listItem);
	short				GetSelectedCount (void) const;
	short				GetSelectedItem (short listItem = TopItem) const;
	short				GetSelectedItems (short* items, short maxCount) const;
	GS::Array<short>	GetSelectedItems (void) const;

	void	EnableMouseMoveEvent (void);
	void	EnableHoverEvent (void);
	void	EnablePressedEvent (void);

	void	ClearHover ();

	void	SetHoverInWaitMillisecs (Int32 hoverInWaitMillisecs);

	void	SetScrollPosition (short scrollPosition);
	short	GetScrollPosition (void) const;
	void	ScrollUp (void);
	void	ScrollDown (void);

	short	GetItemFromPosition (const Point& pos) const;

	void		SetViewMode (ViewMode viewMode);
	ViewMode	GetViewMode (void) const;

	void	SetItemSize (short itemWidth, short itemHeight);
	void	SetItemWidth (short itemWidth);
	void	SetItemHeight (short itemHeight);

	void	GetItemSize (short* itemWidth, short* itemHeight) const;
	short	GetItemWidth (void) const;
	short	GetItemHeight (void) const;
	bool	GetItemRect (short listItem, Rect* rect) const;

	void	SetImageSize (short imageWidth, short imageHeight);
	void	SetImageWidth (short imageWidth);
	void	SetImageHeight (short imageHeight);

	void	GetImageSize (short* imageWidth, short* imageHeight) const;
	short	GetImageWidth (void) const;
	short	GetImageHeight (void) const;

	ImageType	GetImageType (void) const;

	void		SetIcon (const DG::Icon& icon, short nImages, short nRows);
	DG::Icon	GetIcon (void) const;

	void		SetPicture (const DG::Picture& picture, short nImages, short nRows);
	DG::Picture	GetPicture (void) const;

	void		SetImage (ImageType imageType, const void* imageData, short nImages, short nRows);
	const void*	GetImage (void) const;

	void	SetImageGap (short imageGap);
	short	GetImageGap () const;

	void	SetTextTruncateWidth (short textTruncateWidth);
	short	GetTextTruncateWidth () const;

	void	GetImageLayout (short* nImages, short* nRows) const;
	short	GetSubImageCount (void) const;
	short	GetSubImageRowCount (void) const;

	void	EnableDraw (void);
	void	DisableDraw (void);

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- SingleSelListView -------------------------------------------------------

class DG_DLL_EXPORT SingleSelListView: public ListView
{
public:
	SingleSelListView (const Panel& panel, short item);
	SingleSelListView (const Panel& panel, const Rect& rect, ViewMode mode = BottomText, ScrollType scrollType = Normal, FrameType frameType = NoFrame);
   ~SingleSelListView ();
};


// --- MultiSelListView --------------------------------------------------------

class DG_DLL_EXPORT MultiSelListView: public ListView
{
public:
	MultiSelListView (const Panel& panel, short item);
	MultiSelListView (const Panel& panel, const Rect& rect, ViewMode mode = BottomText, ScrollType scrollType = Normal, FrameType frameType = NoFrame);
   ~MultiSelListView ();
};

}	// namespace DG

#endif
