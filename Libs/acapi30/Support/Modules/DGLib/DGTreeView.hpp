// *********************************************************************************************************************
// File:			DGTreeView.hpp
//
// Description:		TreeView classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
// *********************************************************************************************************************

#ifndef DGTREEVIEW_HPP
#define DGTREEVIEW_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "UniString.hpp"

#include "Color.hpp"

#include "DGItemProperty.hpp"

#include "DGEventNotifier.hpp"
#include "DGItemEventArgs.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace DG {
	class TreeView;
}


// --- Class declarations ----------------------------------------------------------------------------------------------

namespace DG {

// --- TreeViewDropSourceEvent -----------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewDragSourceEvent: public ItemDragSourceEvent
{
friend class TreeViewObserver;				// To access protected constructor
friend class TreeViewDragSourceObserver;	// To access protected constructor

protected:
	explicit TreeViewDragSourceEvent (const ItemDragSourceEvent& ev);

public:
	~TreeViewDragSourceEvent ();

	TreeView*	GetSource (void) const;
};


// --- TreeViewDragSourceObserver --------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewDragSourceObserver
{
protected:
	TreeViewDragSourceObserver ();

public:
	virtual ~TreeViewDragSourceObserver ();

	virtual void	TreeViewDragStarting (const TreeViewDragSourceEvent& ev, bool* canStart);
	virtual void	TreeViewDragStarted (const TreeViewDragSourceEvent& ev, UShort* effect);
	virtual void	TreeViewDragStarted (const TreeViewDragSourceEvent& ev, UShort* effect, bool* rightDragMenu);
	virtual void	TreeViewDragEnded (const TreeViewDragSourceEvent& ev, DragDrop::Effect effect);
	virtual void	TreeViewDragSetDelayedData (const TreeViewDragSourceEvent& ev);
};


// --- TreeViewDragTargetEvent -----------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewDropTargetEvent: public ItemDropTargetEvent
{
friend class TreeViewObserver;				// To access protected constructor
friend class TreeViewDropTargetObserver;	// To access protected constructor

private:
	Int32	insertPos;
	short	relativePos;

protected:
	explicit TreeViewDropTargetEvent (const ItemDropTargetEvent& ev);

public:
	~TreeViewDropTargetEvent ();

	TreeView*					GetSource (void) const;

	Int32						GetInsertPosition (void) const;
	DG::DragDrop::RelativePos	GetRelativePosition (void) const;
};


// --- TreeViewDropTargetObserver --------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewDropTargetObserver
{
protected:
	TreeViewDropTargetObserver ();

public:
	virtual ~TreeViewDropTargetObserver ();

	virtual void	TreeViewDragEntered (const TreeViewDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour);
	virtual void	TreeViewDragEntered (const TreeViewDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour,
										 bool* rightDragMenu);
	virtual void	TreeViewDragMoved (const TreeViewDropTargetEvent& ev, DragDrop::Effect* effect,
									   DragDrop::Feedback* denyFeedback);
	virtual void	TreeViewDragLeft (const TreeViewDropTargetEvent& ev, DragDrop::Effect* effect);
	virtual void	TreeViewDropped (const TreeViewDropTargetEvent& ev, DragDrop::Effect* effect);
};


// --- TreeViewSelectionEvent ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewSelectionEvent: public ItemChangeEvent
{
friend class TreeViewObserver;				// To access protected constructor

protected:
	explicit TreeViewSelectionEvent (const ItemChangeEvent& ev);

public:
	~TreeViewSelectionEvent ();

	TreeView*	GetSource (void) const;
};


// --- TreeViewClickEvent ----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewClickEvent: public ItemClickEvent
{
friend class TreeViewObserver;				// To access protected constructor

private:
	Int32	treeItem;

protected:
	explicit TreeViewClickEvent (const ItemClickEvent& ev);

public:
	~TreeViewClickEvent ();

	TreeView*	GetSource (void) const;

	Int32	GetTreeItem (void) const;
};


// --- TreeViewContextMenuEvent ----------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewContextMenuEvent: public ItemContextMenuEvent
{
friend class TreeViewObserver;				// To access protected constructor

protected:
	explicit TreeViewContextMenuEvent (const ItemContextMenuEvent& ev);

public:
	~TreeViewContextMenuEvent ();

	TreeView*	GetSource (void) const;
	Int32		GetItem   (void) const;
};


// --- TreeViewDoubleClickEvent ----------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewDoubleClickEvent: public ItemDoubleClickEvent
{
friend class TreeViewObserver;				// To access protected constructor

private:
	Int32	treeItem;

protected:
	explicit TreeViewDoubleClickEvent (const ItemDoubleClickEvent& ev);

public:
	~TreeViewDoubleClickEvent ();

	TreeView*	GetSource (void) const;

	Int32	GetTreeItem (void) const;
};


// --- TreeViewItemClickEvent ------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewItemClickEvent: public ItemEvent
{
friend class TreeView;				// To access protected constructor
friend class TreeViewObserver;
private:
	const DG::TreeViewItemClickEventArg*	treeViewItemClickData;

protected:
	explicit TreeViewItemClickEvent (TreeView* source, const DG::EventArg& msgData);

public:
	enum TreeItemPartId {
		StateIcon	= DG_TVPI_STATEICON,
		NormalIcon	= DG_TVPI_NORMALICON
	};

	~TreeViewItemClickEvent ();

	TreeView*	GetSource (void) const;

	Int32	GetTreeItem (void) const;
	short	GetPartId (void) const;
};


// --- TreeViewExpandEvent ---------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewExpandEvent: public ItemChangeEvent
{
friend class TreeViewObserver;				// To access protected constructor

private:
	Int32	treeItem;

protected:
	explicit TreeViewExpandEvent (const ItemChangeEvent& ev);

public:
	~TreeViewExpandEvent ();

	TreeView*	GetSource (void) const;

	Int32	GetTreeItem (void) const;
};


// --- TreeViewLabelEvent ----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewLabelEvent: public ItemChangeEvent
{
friend class TreeViewObserver;				// To access protected constructor

private:
	const DG::TreeViewChangeEventArg*	changeData;

protected:
	explicit TreeViewLabelEvent (const ItemChangeEvent& ev);

public:
	~TreeViewLabelEvent ();

	TreeView*	GetSource (void) const;

	Int32	GetTreeItem (void) const;

	GS::UniString	GetOldLabel (void) const;
	GS::UniString	GetNewLabel (void) const;
};


// --- TreeViewObserver ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeViewObserver: public ItemObserver,
									  public TreeViewDragSourceObserver,
									  public TreeViewDropTargetObserver
{
friend class TreeView;

public:
	enum EditResponse {
		SetNewLabel		= DG_TVCR_SETNEWTEXT,
		KeepOldLabel	= DG_TVCR_KEEPOLDTEXT,
		EditLabel		= DG_TVCR_EDITTEXT
	};

protected:

	virtual	short	SpecChanged (const ItemChangeEvent& ev) override;
	virtual	short	SpecClicked (const ItemClickEvent& ev) override;
	virtual short	SpecContextMenuRequested (const ItemContextMenuEvent& ev) override;
	virtual short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;

	virtual short	SpecDragStarting (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragStarted (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragEnded (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragSetDelayedData (const ItemDragSourceEvent& ev) override;
	virtual short	SpecDragEntered (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDragMoved (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDragLeft (const ItemDropTargetEvent& ev) override;
	virtual short	SpecDropped (const ItemDropTargetEvent& ev) override;

	virtual void	TreeViewSelectionChanged (const TreeViewSelectionEvent& ev);
	virtual void	TreeViewItemClicked (const TreeViewItemClickEvent& ev, bool* denySelectionChange);

	virtual void	TreeViewItemCollapsed (const TreeViewExpandEvent& ev);
	virtual void	TreeViewItemExpanded (const TreeViewExpandEvent& ev);

	virtual void	TreeViewContextMenuRequested (const TreeViewContextMenuEvent& ev, bool* processed);
	virtual void	TreeViewStateIconClicked (const TreeViewClickEvent& ev, bool* denySelectionChange);
	virtual void	TreeViewItemDoubleClicked (const TreeViewDoubleClickEvent& ev, bool* processed);

	virtual void	TreeViewLabelEditStarted (const TreeViewLabelEvent& ev, bool* denyEdit);
	virtual void	TreeViewLabelEditFinished (const TreeViewLabelEvent& ev, EditResponse* editResponse);

public:
	TreeViewObserver ();
   ~TreeViewObserver ();
};


// --- TreeView --------------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT TreeView: public Item,
							  public ItemFontProperty,
							  public FocusableProperty,
							  public TreeViewNotifyHandler,
							  public ItemDragDropNotifier<TreeView>,
							  public ItemWheelNotifier<TreeView>
{
public:
	enum LabelFlag {
		NoLabelEdit		= 0,
		LabelEdit		= DG_TVT_LABELEDIT
	};

	enum DragDropFlag {
		NoDragDrop		= 0,
		DragDrop		= DG_TVT_DRAGDROP
	};

	enum RootButtonFlag {
		NoRootButton	= 0,
		RootButton		= DG_TVT_ROOTBUTTON
	};

	enum FrameType {
		NoFrame			= 0,
		Frame			= DG_TVT_FRAME
	};

	enum ItemType {
		AllItems		= DG_ALL_ITEMS,
		NoItem			= DG_TVI_NONE,
		RootItem		= DG_TVI_ROOT,
		TopItem			= DG_TVI_TOP,
		BottomItem		= DG_TVI_BOTTOM
	};

	enum GetItemFlag {
		First			= DG_TVG_FIRST,
		Next			= DG_TVG_NEXT,
		Previous		= DG_TVG_PREVIOUS,
		Parent			= DG_TVG_PARENT,
		Child			= DG_TVG_CHILD,
		FirstListed		= DG_TVG_FIRSTLISTED,
		LastListed		= DG_TVG_LASTLISTED,
		NextListed		= DG_TVG_NEXTLISTED,
		PreviousListed	= DG_TVG_PREVLISTED
	};

	enum ItemStatus {
		Enabled			= DG_IS_ENABLE,
		Disabled		= DG_IS_DISABLE
	};

	enum ItemVisibility {
		NotListed			= DG_TVR_NOTLISTED,
		Listed				= DG_TVR_LISTED,
		PartiallyVisible	= DG_TVR_PARTIALLY_VISIBLE,
		FullyVisible		= DG_TVR_FULLY_VISIBLE
	};

	enum CheckIcons {
		NoIcon					= DG_NO_ICON,
		CheckedIcon				= DG_TVIC_CHECKED,
		UncheckedIcon			= DG_TVIC_UNCHECKED,
		MixedCheckedIcon		= DG_TVIC_MIXEDCHECKED,
		GrayCheckedIcon			= DG_TVIC_GRAYCHECKED,
		GrayUncheckedIcon		= DG_TVIC_GRAYUNCHECKED,
		GrayMixedCheckedIcon	= DG_TVIC_GRAYMIXEDCHECKED,
		FramelessCheckIcon		= DG_TVIC_FRAMELESSCHECK,
		FramelessGrayCheckIcon	= DG_TVIC_FRAMELESSGRAYCHECK
	};

	enum HelpStyle {
		HSNormal		= DG_TREEHS_NORMAL,
		HSForItem		= DG_TREEHS_FORITEM,
		HSUnderContent	= DG_TREEHS_UNDERCONTENT
	};

private:
	short	ProcessTreeViewItemClickEvent (const DG::EventArg& msgData);

	void	InitNotifiers ();

	virtual bool	NotifyChangeEvent (const TreeViewChangeEventArg& eventArg) override;
	virtual short	NotifyClickEvent (const TreeViewClickEventArg& eventArg) override;
	virtual short	NotifyDoubleClickEvent (const TreeViewDoubleClickEventArg& eventArg) override;
	virtual bool	NotifyItemClickEvent (const TreeViewItemClickEventArg& eventArg) override;

protected:
	TreeView ();
	TreeView (const Panel& panel, short item);

public:
	~TreeView ();

	DG::EventNotifier<TreeView, const TreeViewChangeEventArg, bool, true> onChanged;
	DG::EventNotifier<TreeView, const TreeViewClickEventArg, short> onClicked;
	DG::EventNotifier<TreeView, const TreeViewDoubleClickEventArg, short> onDoubleClicked;
	DG::EventNotifier<TreeView, const TreeViewItemClickEventArg, bool, false> onItemClicked;

	void	Attach (TreeViewObserver& observer);
	void	Detach (TreeViewObserver& observer);

	Int32	AppendItem (Int32 parentItem);
	Int32	InsertItem (Int32 parentItem, Int32 tvItem);
	void	DeleteItem (Int32 tvItem);
	Int32	GetItemCount (void)	const;

	Int32	GetItem (Int32 tvItem, GetItemFlag flag) const;
	Int32	GetTopMostParent (Int32 tvItem) const;
	bool	HasAncestor (Int32 tvItem, Int32 ancestorItem) const;
	Int32	GetLastVisibleChild (Int32 tvItem) const;

	void		SetItemText (Int32 tvItem, const GS::UniString& text);
	GS::UniString	GetItemText (Int32 tvItem) const;

	void		SetItemNormalIcon (Int32 tvItem, const DG::Icon& icon);
	DG::Icon	GetItemNormalIcon (Int32 tvItem) const;

	void		SetItemStateIcon (Int32 tvItem, const DG::Icon& icon);
	DG::Icon	GetItemStateIcon (Int32 tvItem) const;

	void		SetItemOverlayIcon (Int32 tvItem, const DG::Icon& icon);
	DG::Icon	GetItemOverlayIcon (Int32 tvItem) const;

	void	SetNormalIconSize (short width, short height);
	void	SetNormalIconWidth (short width);
	void	SetNormalIconHeight (short height);

	short	GetNormalIconWidth () const;
	short	GetNormalIconHeight () const;

	void	SetStateIconSize (short width, short height);
	void	SetStateIconWidth (short width);
	void	SetStateIconHeight (short height);

	short	GetStateIconWidth () const;
	short	GetStateIconHeight () const;

	void		SetItemFontStyle (Int32 tvItem, Font::Style style);
	Font::Style	GetItemFontStyle (Int32 tvItem) const;

	void	SetItemTextColor (Int32 tvItem, const Gfx::Color& color);
	void	ResetItemTextColor (Int32 tvItem);
	bool	GetItemTextColor (Int32 tvItem, Gfx::Color& color) const;

	void	SetItemBackgroundColor (Int32 tvItem, const Gfx::Color& color);
	void	ResetItemBackgroundColor (Int32 tvItem);
	bool	GetItemBackgroundColor (Int32 tvItem, Gfx::Color& color) const;

	void	SetItemValue (Int32 tvItem, DGUserData value);
	DGUserData	GetItemValue (Int32 tvItem) const;

	void					SetItemObjectData (Int32 tvItem, GS::Ref<GS::Object> object);
	GS::Ref<GS::Object>		GetItemObjectData (Int32 tvItem) const;

	void		SetItemStatus (Int32 tvItem, ItemStatus status);
	ItemStatus	GetItemStatus (Int32 tvItem) const;

	void	EnableItem (Int32 tvItem);
	void	DisableItem (Int32 tvItem);

	bool	IsItemEnabled (Int32 tvItem) const;
	bool	IsItemDisabled (Int32 tvItem) const;

	bool	IsItemListed (Int32 tvItem) const;
	bool	IsItemVisible (Int32 tvItem) const;
	bool	GetItemRect (Int32 tvItem, Rect* rect) const;

	void	ExpandItem (Int32 tvItem);
	void	CollapseItem (Int32 tvItem);
	bool	IsItemExpanded (Int32 tvItem) const;
	void	BeginItemEdit (Int32 tvItem);

	void				SelectItem (Int32 tvItem);
	void				DeselectItem (Int32 tvItem);
	Int32				GetSelectedCount (void) const;
	Int32				GetSelectedItem (Int32 tvItem = RootItem) const;
	Int32				GetSelectedItems (Int32* selItems, Int32 maxCount) const;
	GS::Array<Int32>	GetSelectedItems (void) const;

	void	EnableDraw (void);
	void	DisableDraw (void);
	void	RedrawItem (Int32 tvItem);

	void		SetHelpStyle (HelpStyle helpStyle);
	HelpStyle	GetHelpStyle (void);

	void	SetScrollPosition (Int32 scrollPosition);
	Int32	GetScrollPosition (void) const;

	Int32	GetItemFromPosition (const Point& pos) const;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;
};


// --- SingleSelTreeView -----------------------------------------------------------------------------------------------

class DG_DLL_EXPORT SingleSelTreeView: public TreeView
{
public:
	SingleSelTreeView (const Panel& panel, short item);
	SingleSelTreeView (const Panel& panel, const Rect& rect, short labelLength,
					   LabelFlag label = NoLabelEdit, DragDropFlag dragDrop = NoDragDrop,
					   RootButtonFlag root = RootButton, FrameType frameType = NoFrame);
   ~SingleSelTreeView ();
};


// --- MultiSelTreeView ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT MultiSelTreeView: public TreeView
{
public:
	MultiSelTreeView (const Panel& panel, short item);
	MultiSelTreeView (const Panel& panel, const Rect& rect, short labelLength,
					  LabelFlag label = NoLabelEdit, DragDropFlag dragDrop = NoDragDrop,
					  RootButtonFlag root = RootButton, FrameType frameType = NoFrame);
   ~MultiSelTreeView ();
};

}	// namespace DG

#endif
