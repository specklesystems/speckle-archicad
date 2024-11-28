#ifndef GS_UD_IFILTERABLELISTBOX_HPP
#define GS_UD_IFILTERABLELISTBOX_HPP
#pragma once

#include "UDIFilterableItem.hpp"
#include "DGListBox.hpp"

namespace UD {

class UD_DLL_EXPORT IFilterableListBox : public IFilterableItem {
public:
	static constexpr short NoItem = -1;

public:
	virtual ~IFilterableListBox ();

// === DG ListBox interface ===========================================================================================
	virtual void	Attach (DG::ListBoxObserver& observer) = 0;
	virtual void	Detach (DG::ListBoxObserver& observer) = 0;

	virtual Int32	AppendItem (void) = 0;
	virtual Int32	InsertItem (Int32 listItem) = 0;
	virtual void	DeleteItem (Int32 listItem) = 0;
	virtual Int32	GetItemCount (void) const = 0;

	virtual Int32	InsertSeparator (Int32 listItem) = 0;
	virtual bool	IsSeparator (Int32 listItem) const = 0;

	virtual bool	HasHeader (void) const = 0;
	virtual short	GetHeaderHeight (void) const = 0;

	virtual void	SetHeaderSynchronState (bool isSynchron) = 0;
	virtual bool	IsHeaderInSynchronState (void) const = 0;

	virtual void	SetHeaderPushableButtons (bool hasPushableButtons) = 0;
	virtual bool	HasHeaderPushableButtons (void) const = 0;

	virtual void	SetHeaderDragableButtons (bool hasDragableButtons) = 0;
	virtual bool	HasHeaderDragableButtons (void) const = 0;

	virtual void	SetHeaderItemCount (short itemCount) = 0;
	virtual short	GetHeaderItemCount (void) const = 0;

	virtual void			SetHeaderItemText (short headerItem, const GS::UniString& text) = 0;
	virtual GS::UniString	GetHeaderItemText (short headerItem) const = 0;

	virtual void		SetHeaderItemIcon (short headerItem, const DG::Icon& icon) = 0;
	virtual DG::Icon	GetHeaderItemIcon (short headerItem) const = 0;

	virtual void		SetHeaderItemFont (short headerItem, DG::Font::Size size, DG::Font::Style style) = 0;
	virtual DG::Font::Size	GetHeaderItemFontSize (short headerItem) const = 0;
	virtual DG::Font::Style	GetHeaderItemFontStyle (short headerItem) const = 0;

	virtual void			SetHeaderItemStyle (short headerItem, DG::ListBox::Justification just, DG::ListBox::Truncation trunc) = 0;
	virtual DG::ListBox::Justification	GetHeaderItemJustification (short headerItem) const = 0;
	virtual DG::ListBox::Truncation		GetHeaderItemTruncation (short headerItem) const = 0;

	virtual void	SetHeaderItemSizeableFlag (short headerItem, bool isSizeable) = 0;
	virtual bool	IsHeaderItemSizeable (short headerItem) const = 0;

	virtual void	SetHeaderItemSize (short headerItem, short size) = 0;
	virtual short	GetHeaderItemSize (short headerItem) const = 0;

	virtual void	SetHeaderItemMinSize (short headerItem, short minSize) = 0;
	virtual short	GetHeaderItemMinSize (short headerItem) const = 0;

	virtual void		SetHeaderItemArrowType (short headerItem, DG::ListBox::ArrowType arrowType) = 0;
	virtual DG::ListBox::ArrowType	GetHeaderItemArrowType (short headerItem) const = 0;

	virtual void		SetHeaderButtonIcon (const DG::Icon& icon) = 0;
	virtual DG::Icon	GetHeaderButtonIcon (void) const = 0;

	virtual void	EnableHeaderButton (void) = 0;
	virtual void	DisableHeaderButton (void) = 0;
	virtual bool	IsHeaderButtonEnabled (void) const = 0;

	virtual bool	SetTabFieldCount (short nTabFields) = 0;
	virtual short	GetTabFieldCount (void) const = 0;

	virtual void	SetTabFieldProperties (short tabIndex, short begPos, short endPos, DG::ListBox::Justification just, DG::ListBox::Truncation trunc,
								   bool hasSeparator = false, bool status = true) = 0;
	
	virtual void	SetTabFieldBeginEndPosition (short tabIndex, short begPos, short endPos) = 0;
	virtual short	GetTabFieldBeginPosition (short tabIndex) const = 0;
	virtual short	GetTabFieldEndPosition (short tabIndex) const = 0;
	virtual short	GetTabFieldWidth (short tabIndex) const = 0;

	virtual void	SetTabFieldJustification (short tabIndex, DG::ListBox::Justification just) = 0;
	virtual DG::ListBox::Justification	GetTabFieldJustification (short tabIndex) const = 0;

	virtual void	SetTabFieldTruncation (short tabIndex, DG::ListBox::Truncation trunc) = 0;
	virtual DG::ListBox::Truncation	GetTabFieldTruncation (short tabIndex) const = 0;

	virtual void	SetTabFieldSeparator (short tabIndex, bool hasSeparator) = 0;
	virtual bool	HasTabFieldSeparator (short tabIndex) const = 0;

	virtual void	SetTabFieldStatus (short tabIndex, bool status) = 0;
	virtual bool	IsTabFieldEnabled (short tabIndex) const = 0;

	virtual void	SetTabFieldOwnerDrawFlag (short tabIndex, bool ownerDraw) = 0;
	virtual bool	GetTabFieldOwnerDrawFlag (short tabIndex) const = 0;

	virtual void	SetTabFieldToSearch (short tabIndex) = 0;
	virtual short	GetTabFieldToSearch (void) const = 0;

	virtual void	SetOnTabItem (short tabIndex, const DG::Item& item) = 0;
	virtual void	RemoveOnTabItem (short tabIndex) = 0;
	virtual DG::Item* GetOnTabItem (short tabIndex) const = 0;

	virtual void		SetTabItemText (Int32 listItem, short tabIndex, const GS::UniString& text) = 0;
	virtual GS::UniString GetTabItemText (Int32 listItem, short tabIndex) const = 0;

	virtual void		SetTabItemIcon (Int32 listItem, short tabIndex, const DG::Icon& icon) = 0;
	virtual DG::Icon	GetTabItemIcon (Int32 listItem, short tabIndex) const = 0;

	virtual void		SetTabItemFontStyle (Int32 listItem, short tabIndex, DG::Font::Style style) = 0;
	virtual DG::Font::Style	GetTabItemFontStyle (Int32 listItem, short tabIndex) const = 0;

	virtual void	SetTabItemColor (Int32 listItem, short tabIndex, const Gfx::Color& color) = 0;
	virtual bool	GetTabItemColor (Int32 listItem, short tabIndex, Gfx::Color* color) const = 0;

	virtual void	SetTabItemBackgroundColor (Int32 listItem, short tabIndex, const Gfx::Color& color) = 0;
	virtual bool	GetTabItemBackgroundColor (Int32 listItem, short tabIndex, Gfx::Color* color) const = 0;

	virtual void			SetTabItemDescription (Int32 listItem, short tabIndex, const GS::UniString& description) = 0;
	virtual GS::UniString	GetTabItemDescription (Int32 listItem, short tabIndex) const = 0;

	virtual void		SetItemFontStyle (Int32 listItem, DG::Font::Style style) = 0;
	virtual DG::Font::Style	GetItemFontStyle (Int32 listItem) const = 0;

	virtual void	SetItemColor (Int32 listItem, const Gfx::Color& color) = 0;
	virtual void	ResetItemColor (Int32 listItem) = 0;
	virtual bool	GetItemColor (Int32 listItem, Gfx::Color* color) const = 0;

	virtual void	SetItemBackgroundColor (Int32 listItem, const Gfx::Color& color) = 0;
	virtual void	ResetItemBackgroundColor (Int32 listItem) = 0;
	virtual bool	GetItemBackgroundColor (Int32 listItem, Gfx::Color* color) const = 0;

	virtual void	SetItemValue (Int32 listItem, DGUserData value) = 0;
	virtual DGUserData	GetItemValue (Int32 listItem) const = 0;

	virtual void					SetItemObjectData (Int32 listItem, GS::Ref<GS::Object> object) = 0;
	virtual GS::Ref<GS::Object>		GetItemObjectData (Int32 listItem) const = 0;

	virtual void		SetItemStatus (Int32 listItem, DG::ListBox::ItemStatus status) = 0;
	virtual DG::ListBox::ItemStatus	GetItemStatus (Int32 listItem) const = 0;

	virtual void	EnableItem (Int32 listItem) = 0;
	virtual void	GrayItem (Int32 listItem) = 0;
	virtual void	DisableItem (Int32 listItem) = 0;

	virtual bool	IsItemEnabled (Int32 listItem) const = 0;
	virtual bool	IsItemGrayed (Int32 listItem) const = 0;
	virtual bool	IsItemDisabled (Int32 listItem) const = 0;
	virtual bool	IsItemVisible (Int32 listItem) const = 0;

	virtual void	SetItemOwnerDrawFlag (Int32 listItem, bool isOwnerDrawn) = 0;
	virtual bool	GetItemOwnerDrawFlag (Int32 listItem) const = 0;

	virtual void	SetItemHeight (short itemHeight) = 0;
	virtual short	GetItemHeight (void) const = 0;
	virtual short	GetItemWidth (void) const = 0;
	virtual bool	GetItemRect (Int32 listItem, DG::Rect* rect) const = 0;
	virtual void	SetNoPartialItem (void) = 0;

	virtual void	EnableSeparatorLines (bool hasSeparatorLines) = 0;
	virtual bool	HasSeparatorLines (void) const = 0;
	virtual void				SetSeparatorLineColor (const Gfx::Color& color) = 0;
	virtual const Gfx::Color	GetSeparatorLineColor (void) const = 0;

	virtual void	SelectItem (Int32 listItem) = 0;
	virtual void	SelectItems (const GS::Array<Int32>& listItems) = 0;
	virtual void	DeselectItem (Int32 listItem) = 0;
	virtual Int32	GetSelectedCount (void) const = 0;
	virtual Int32	GetSelectedItem (Int32 listItem = DG::ListBox::TopItem) const = 0;
	virtual GS::Array<Int32>	GetSelectedItems (void) const = 0;

	virtual void	EnableDraw (void) = 0;
	virtual void	DisableDraw (void) = 0;
	virtual void	RedrawItem (Int32 listItem) = 0;
	virtual void	RedrawTabItem (Int32 listItem, short tabIndex) = 0;

	virtual void	EnableMouseMoveEvent (void) = 0;
	virtual void	EnableHoverEvent (void) = 0;


	virtual void	SetScrollPosition (short scrollPosition) = 0;
	virtual short	GetScrollPosition (void) const = 0;
	virtual void	ScrollUp (void) = 0;
	virtual void	ScrollDown (void) = 0;
	virtual void	SetHScrollPosition (short scrollPosition) = 0;
	virtual short	GetHScrollPosition (void) const = 0;

	virtual Int32	GetItemFromPosition (const DG::Point& pos) const = 0;

	virtual void			SetHelpStyle (DG::ListBox::HelpStyle helpStyle) = 0;
	virtual DG::ListBox::HelpStyle		GetHelpStyle (void) = 0;

	virtual GSErrCode Store (GS::ObjectState& os) const = 0;

// === IFilterableListBox interface ===================================================================================
public:

	virtual DG::ListBox& GetNotConstListBox () = 0;
	virtual const DG::ListBox& GetConstListBox () const = 0;

	virtual bool	IsOwnListBox (const void* listboxPtr) const = 0;

	virtual bool	IsValidListItem (Int32 index) const = 0;

	using	ConstEnumerateFunction = std::function<void (Int32)>;
	virtual void	EnumerateItems (Int32 fromIndex, const ConstEnumerateFunction& enumerateFn) const = 0;

	virtual void	AddFilteredTabIndex (short tabIndex) = 0;

	virtual void	AddExcludeIndex (Int32 itemIdx) = 0;

	virtual short				GetFilteredItemCount (void) const = 0;
	virtual GS::Array<Int32>	GetFilteredItemIds (void) const = 0;
};

}

#endif //GS_UD_IFILTERABLELISTBOX_HPP
