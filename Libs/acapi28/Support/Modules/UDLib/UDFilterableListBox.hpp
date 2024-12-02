#ifndef GS_UD_FILTERABLELISTBOX_HPP
#define GS_UD_FILTERABLELISTBOX_HPP
#pragma once

#include "BiHashTable.hpp"
#include "Optional.hpp"

#include "Location.hpp"

#include "UDIFilterableListBox.hpp"
#include "UDArrayBasedTree.hpp"
#include "UDFilterableListBoxItemData.hpp"


namespace UD {


class UD_DLL_EXPORT FilterableListBoxHandler : public IFilterableListBox,
											   public DG::ListBoxObserver {
private:

	DG::ListBox&								listBox;
	ArrayBasedTree<FilterableListBoxItemData>	arrayBasedTree;
	GS::BiHashTable<Int32, Int32>				arrayBasedTreeToDGListBoxBiHashTable;
	GS::HashSet<short>							filteredTabIndices;
	GS::HashSet<Int32>							excludeSet;

public:
	FilterableListBoxHandler (DG::ListBox& listBox);

	virtual void	DoRefreshFiltering () override;

	virtual DG::Panel* GetPanel (void) const override;

	// DG::ListBoxObserver

	virtual void	ListBoxHeaderItemDragged (const DG::ListBoxHeaderItemDragEvent& ev) override;

	// IFilterableListBox

	virtual void	Show (void) override;
	virtual void	Hide (void) override;
	virtual void	SetVisibility (bool show) override;
	virtual bool	IsVisible (void) const override;

	virtual void	Enable (void) override;
	virtual void	Disable (void) override;
	virtual void	SetStatus (bool enable) override;
	virtual bool	IsEnabled (void) const override;

	virtual void	Move (short hDisp, short vDisp) override;
	virtual void	Resize (short hGrow, short vGrow) override;
	virtual void	MoveAndResize (short hDisp, short vDisp, short hGrow, short vGrow) override;

	virtual void	SetPosition (const DG::Point& pt) override;
	virtual void	SetPosition (short hPos, short vPos) override;
	virtual void	SetRect (const DG::Rect& rect) override;
	virtual void	SetSize (short width, short height) override;
	virtual void	SetWidth (short width) override;
	virtual void	SetHeight (short height) override;

	virtual DG::Point	GetPosition (void) const override;
	virtual DG::Rect	GetRect (void) const override;
	virtual short	GetWidth (void) const override;
	virtual short	GetHeight (void) const override;

	virtual DG::NativeRect	GetNativeRectInScreenSpace (void) const override;

	virtual void	Invalidate (void) const override;
	virtual void	Redraw (void) const override;

	virtual DG::EventNotifier<DG::Item, const DG::VisibilityChangeEventArg>& AccessOnVisibilityChangedEventNotifier () override;

	virtual void		 SetFontSize (DG::Font::Size size) override;
	virtual DG::Font::Size	 GetFontSize (void) const override;

	virtual void		 SetFontStyle (DG::Font::Style style) override;
	virtual DG::Font::Style	 GetFontStyle (void) const override;

	virtual void	SetFocus (void) override;
	virtual bool	IsFocused (void) const override;

	virtual void	Attach (DG::ListBoxObserver& observer) override;
	virtual void	Detach (DG::ListBoxObserver& observer) override;

	virtual Int32	AppendItem (void) override;
	virtual Int32	InsertItem (Int32 listItem) override;
	virtual void	DeleteItem (Int32 listItem) override;
	virtual Int32	GetItemCount (void) const override;

	virtual Int32	InsertSeparator (Int32 listItem) override;
	virtual bool	IsSeparator (Int32 listItem) const override;

	virtual bool	HasHeader (void) const override;
	virtual short	GetHeaderHeight (void) const override;

	virtual void	SetHeaderSynchronState (bool isSynchron) override;
	virtual bool	IsHeaderInSynchronState (void) const override;

	virtual void	SetHeaderPushableButtons (bool hasPushableButtons) override;
	virtual bool	HasHeaderPushableButtons (void) const override;

	virtual void	SetHeaderDragableButtons (bool hasDragableButtons) override;
	virtual bool	HasHeaderDragableButtons (void) const override;

	virtual void	SetHeaderItemCount (short itemCount) override;
	virtual short	GetHeaderItemCount (void) const override;

	virtual void			SetHeaderItemText (short headerItem, const GS::UniString& text) override;
	virtual GS::UniString	GetHeaderItemText (short headerItem) const override;

	virtual void		SetHeaderItemIcon (short headerItem, const DG::Icon& icon) override;
	virtual DG::Icon	GetHeaderItemIcon (short headerItem) const override;

	virtual void		SetHeaderItemFont (short headerItem, DG::Font::Size size, DG::Font::Style style) override;
	virtual DG::Font::Size	GetHeaderItemFontSize (short headerItem) const override;
	virtual DG::Font::Style	GetHeaderItemFontStyle (short headerItem) const override;

	virtual void			SetHeaderItemStyle (short headerItem, DG::ListBox::Justification just, DG::ListBox::Truncation trunc) override;
	virtual DG::ListBox::Justification	GetHeaderItemJustification (short headerItem) const override;
	virtual DG::ListBox::Truncation		GetHeaderItemTruncation (short headerItem) const override;

	virtual void	SetHeaderItemSizeableFlag (short headerItem, bool isSizeable) override;
	virtual bool	IsHeaderItemSizeable (short headerItem) const override;

	virtual void	SetHeaderItemSize (short headerItem, short size) override;
	virtual short	GetHeaderItemSize (short headerItem) const override;

	virtual void	SetHeaderItemMinSize (short headerItem, short minSize) override;
	virtual short	GetHeaderItemMinSize (short headerItem) const override;

	virtual void		SetHeaderItemArrowType (short headerItem, DG::ListBox::ArrowType arrowType) override;
	virtual DG::ListBox::ArrowType	GetHeaderItemArrowType (short headerItem) const override;

	virtual void		SetHeaderButtonIcon (const DG::Icon& icon) override;
	virtual DG::Icon	GetHeaderButtonIcon (void) const override;

	virtual void		EnableHeaderButton (void) override;
	virtual void		DisableHeaderButton (void) override;
	virtual bool		IsHeaderButtonEnabled (void) const override;

	virtual bool	SetTabFieldCount (short nTabFields) override;
	virtual short	GetTabFieldCount (void) const override;

	virtual void	SetTabFieldProperties (short tabIndex, short begPos, short endPos, DG::ListBox::Justification just, DG::ListBox::Truncation trunc,
										   bool hasSeparator = false, bool status = true) override;

	virtual void	SetTabFieldBeginEndPosition (short tabIndex, short begPos, short endPos) override;
	virtual short	GetTabFieldBeginPosition (short tabIndex) const override;
	virtual short	GetTabFieldEndPosition (short tabIndex) const override;
	virtual short	GetTabFieldWidth (short tabIndex) const override;

	virtual void	SetTabFieldJustification (short tabIndex, DG::ListBox::Justification just) override;
	virtual DG::ListBox::Justification	GetTabFieldJustification (short tabIndex) const override;

	virtual void	SetTabFieldTruncation (short tabIndex, DG::ListBox::Truncation trunc) override;
	virtual DG::ListBox::Truncation		GetTabFieldTruncation (short tabIndex) const override;

	virtual void	SetTabFieldSeparator (short tabIndex, bool hasSeparator) override;
	virtual bool	HasTabFieldSeparator (short tabIndex) const override;

	virtual void	SetTabFieldStatus (short tabIndex, bool status) override;
	virtual bool	IsTabFieldEnabled (short tabIndex) const override;

	virtual void	SetTabFieldOwnerDrawFlag (short tabIndex, bool ownerDraw) override;
	virtual bool	GetTabFieldOwnerDrawFlag (short tabIndex) const override;

	virtual void	SetTabFieldToSearch (short tabIndex) override;
	virtual short	GetTabFieldToSearch (void) const override;

	virtual void	SetOnTabItem (short tabIndex, const DG::Item& item) override;
	virtual void	RemoveOnTabItem (short tabIndex) override;
	virtual DG::Item* GetOnTabItem (short tabIndex) const override;

	virtual void		SetTabItemText (Int32 listItem, short tabIndex, const GS::UniString& text) override;
	virtual GS::UniString GetTabItemText (Int32 listItem, short tabIndex) const override;

	virtual void		SetTabItemIcon (Int32 listItem, short tabIndex, const DG::Icon& icon) override;
	virtual DG::Icon	GetTabItemIcon (Int32 listItem, short tabIndex) const override;

	virtual void		SetTabItemFontStyle (Int32 listItem, short tabIndex, DG::Font::Style style) override;
	virtual DG::Font::Style	GetTabItemFontStyle (Int32 listItem, short tabIndex) const override;

	virtual void	SetTabItemColor (Int32 listItem, short tabIndex, const Gfx::Color& color) override;
	virtual bool	GetTabItemColor (Int32 listItem, short tabIndex, Gfx::Color* color) const override;

	virtual void	SetTabItemBackgroundColor (Int32 listItem, short tabIndex, const Gfx::Color& color) override;
	virtual bool	GetTabItemBackgroundColor (Int32 listItem, short tabIndex, Gfx::Color* color) const override;

	virtual void			SetTabItemDescription (Int32 listItem, short tabIndex, const GS::UniString& description) override;
	virtual GS::UniString	GetTabItemDescription (Int32 listItem, short tabIndex) const override;

	virtual void		SetItemFontStyle (Int32 listItem, DG::Font::Style style) override;
	virtual DG::Font::Style	GetItemFontStyle (Int32 listItem) const override;

	virtual void	SetItemColor (Int32 listItem, const Gfx::Color& color) override;
	virtual void	ResetItemColor (Int32 listItem) override;
	virtual bool	GetItemColor (Int32 listItem, Gfx::Color* color) const override;

	virtual void	SetItemBackgroundColor (Int32 listItem, const Gfx::Color& color) override;
	virtual void	ResetItemBackgroundColor (Int32 listItem) override;
	virtual bool	GetItemBackgroundColor (Int32 listItem, Gfx::Color* color) const override;

	virtual void	SetItemValue (Int32 listItem, DGUserData value) override;
	virtual DGUserData	GetItemValue (Int32 listItem) const override;

	virtual void					SetItemObjectData (Int32 listItem, GS::Ref<GS::Object> object) override;
	virtual GS::Ref<GS::Object>		GetItemObjectData (Int32 listItem) const override;

	virtual void		SetItemStatus (Int32 listItem, DG::ListBox::ItemStatus status) override;
	virtual DG::ListBox::ItemStatus	GetItemStatus (Int32 listItem) const override;

	virtual void	EnableItem (Int32 listItem) override;
	virtual void	GrayItem (Int32 listItem) override;
	virtual void	DisableItem (Int32 listItem) override;

	virtual bool	IsItemEnabled (Int32 listItem) const override;
	virtual bool	IsItemGrayed (Int32 listItem) const override;
	virtual bool	IsItemDisabled (Int32 listItem) const override;
	virtual bool	IsItemVisible (Int32 listItem) const override;

	virtual void	SetItemOwnerDrawFlag (Int32 listItem, bool isOwnerDrawn) override;
	virtual bool	GetItemOwnerDrawFlag (Int32 listItem) const override;

	virtual void	SetItemHeight (short itemHeight) override;
	virtual short	GetItemHeight (void) const override;
	virtual short	GetItemWidth (void) const override;
	virtual bool	GetItemRect (Int32 listItem, DG::Rect* rect) const override;
	virtual void	SetNoPartialItem (void) override;

	virtual void	EnableSeparatorLines (bool hasSeparatorLines) override;
	virtual bool	HasSeparatorLines (void) const override;
	virtual void				SetSeparatorLineColor (const Gfx::Color& color) override;
	virtual const Gfx::Color	GetSeparatorLineColor (void) const override;

	virtual void	SelectItem (Int32 listItem) override;
	virtual void	SelectItems (const GS::Array<Int32>& listItems) override;
	virtual void	DeselectItem (Int32 listItem) override;
	virtual Int32	GetSelectedCount (void) const override;
	virtual Int32	GetSelectedItem (Int32 listItem = DG::ListBox::TopItem) const override;
	virtual GS::Array<Int32>	GetSelectedItems (void) const override;

	virtual void	EnableDraw (void) override;
	virtual void	DisableDraw (void) override;
	virtual void	RedrawItem (Int32 listItem) override;
	virtual void	RedrawTabItem (Int32 listItem, short tabIndex) override;

	virtual void	EnableMouseMoveEvent (void) override;
	virtual void	EnableHoverEvent (void) override;


	virtual void	SetScrollPosition (short scrollPosition) override;
	virtual short	GetScrollPosition (void) const override;
	virtual void	ScrollUp (void) override;
	virtual void	ScrollDown (void) override;
	virtual void	SetHScrollPosition (short scrollPosition) override;
	virtual short	GetHScrollPosition (void) const override;

	virtual Int32	GetItemFromPosition (const DG::Point& pos) const override;

	virtual void			SetHelpStyle (DG::ListBox::HelpStyle helpStyle) override;
	virtual DG::ListBox::HelpStyle		GetHelpStyle (void) override;

	virtual GSErrCode Store (GS::ObjectState& os) const override;

public:

	virtual DG::ListBox& GetNotConstListBox () override;
	virtual const DG::ListBox& GetConstListBox () const override;

	virtual bool	IsOwnListBox (const void* listboxPtr) const override;

	virtual bool	IsValidListItem (Int32 index) const override;

	virtual void	EnumerateItems (Int32 fromIndex, const ConstEnumerateFunction& enumerateFn) const override;

	virtual void	AddFilteredTabIndex (short tabIndex) override;

	virtual void	AddExcludeIndex (Int32 itemIdx) override;

	virtual short				GetFilteredItemCount (void) const override;
	virtual GS::Array<Int32>	GetFilteredItemIds (void) const override;

private:

	short GetDGListBoxPositionToInsert (const ArrayBasedTree<FilterableListBoxItemData>::Node& treeItem) const;

	void InsertToDGListBox (const ArrayBasedTree<FilterableListBoxItemData>::Node& treeItem);

	void DeleteFromDGListBox (const ArrayBasedTree<FilterableListBoxItemData>::Node& treeItemToDelete);

	bool EnsureItemIndexIsOfArrayBasedTree (Int32& itemIndex) const;

	bool AllowByFilter (const ArrayBasedTree<FilterableListBoxItemData>::Node& treeItem) const;

	bool EnsureItemIndexIsOfDGListBox (Int32& itemIndex) const;

	void AdjustItemInDGListBoxToFilter (const ArrayBasedTree<FilterableListBoxItemData>::Node& treeItem);

	GS::HashSet<Int32> CollectDuplicateSeparatorsIndices (const DG::ListBox& listBox);

	void HandleSelectionScrollpositionAfterFiltering ();
};


// =====================================================================================================================


class UD_DLL_EXPORT FilterableSingleSelListBox : public FilterableListBoxHandler {

	DG::SingleSelListBox mListBox;

public:
	
	FilterableSingleSelListBox (const DG::Panel& panel, short item);
	FilterableSingleSelListBox (const DG::Panel& panel,
							    const DG::Rect& rect,
								DG::ListBox::ScrollType scroll = DG::ListBox::VScroll,
								DG::ListBox::PartialItemType part = DG::ListBox::PartialItems,
								DG::ListBox::HeaderFlag headerFlag = DG::ListBox::NoHeader,
								short headerSize = 0,
								DG::ListBox::FrameType frameType = DG::ListBox::NoFrame);

	virtual ~FilterableSingleSelListBox ();

};


class UD_DLL_EXPORT FilterableMultiSelListBox : public FilterableListBoxHandler {

	DG::MultiSelListBox mListBox;

public:

	FilterableMultiSelListBox (const DG::Panel& panel, short listBoxId);
	FilterableMultiSelListBox (const DG::Panel& panel,
							   const DG::Rect& rect,
							   DG::ListBox::ScrollType scroll = DG::ListBox::VScroll,
							   DG::ListBox::PartialItemType part = DG::ListBox::PartialItems,
							   DG::ListBox::HeaderFlag headerFlag = DG::ListBox::NoHeader,
							   short headerSize = 0,
							   DG::ListBox::FrameType frameType = DG::ListBox::NoFrame);

	virtual ~FilterableMultiSelListBox ();
};
}

#endif  //GS_UD_FILTERABLELISTBOX_HPP

