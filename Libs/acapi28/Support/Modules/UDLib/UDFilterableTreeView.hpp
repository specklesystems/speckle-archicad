#ifndef GS_UD_FILTERABLETREEVIEW_HPP
#define GS_UD_FILTERABLETREEVIEW_HPP
#pragma once

#include "BiHashTable.hpp"
#include "Optional.hpp"

#include "Location.hpp"

#include "UDIFilterableTreeView.hpp"
#include "UDArrayBasedTree.hpp"
#include "UDFilterableTreeViewItemData.hpp"

namespace UD {

template<class TreeViewType>
class FilterableTreeView : public IFilterableTreeView {
private:
	TreeViewType								treeView;
	ArrayBasedTree<FilterableTreeViewItemData>	arrayBasedTree;
	GS::BiHashTable<Int32, Int32>				arrayBasedTreeToDGTreeViewBiHashTable;

public:
	FilterableTreeView (const DG::Panel& panel, short treeViewId);
	FilterableTreeView (const DG::Panel& panel, const DG::Rect& treeViewRect);

	virtual void	DoRefreshFiltering () override;

	virtual DG::Panel* GetPanel (void) const override;

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

	virtual void	Attach (DG::TreeViewObserver& observer) override;
	virtual void	Detach (DG::TreeViewObserver& observer) override;

	virtual Int32	AppendItem (Int32 parentItem) override;
	virtual Int32	InsertItem (Int32 parentItem, Int32 targetTvPosition) override;
	virtual void	DeleteItem (Int32 tvItem) override;
	virtual Int32	GetItemCount (void)	const override;

	virtual Int32	GetItem (Int32 tvItem, DG::TreeView::GetItemFlag flag) const override;
	virtual Int32	GetTopMostParent (Int32 tvItem) const override;
	virtual bool	HasAncestor (Int32 tvItem, Int32 ancestorItem) const override;
	virtual Int32	GetLastVisibleChild (Int32 tvItem) const override;

	virtual void			SetItemText (Int32 tvItem, const GS::UniString& text) override;
	virtual GS::UniString	GetItemText (Int32 tvItem) const override;

	virtual void		SetItemNormalIcon (Int32 tvItem, const DG::Icon& icon) override;
	virtual DG::Icon	GetItemNormalIcon (Int32 tvItem) const override;

	virtual void		SetItemStateIcon (Int32 tvItem, const DG::Icon& icon) override;
	virtual DG::Icon	GetItemStateIcon (Int32 tvItem) const override;

	virtual void		SetItemOverlayIcon (Int32 tvItem, const DG::Icon& icon) override;
	virtual DG::Icon	GetItemOverlayIcon (Int32 tvItem) const override;

	virtual void	SetNormalIconSize (short width, short height) override;
	virtual void	SetNormalIconWidth (short width) override;
	virtual void	SetNormalIconHeight (short height) override;

	virtual short	GetNormalIconWidth () const override;
	virtual short	GetNormalIconHeight () const override;

	virtual void	SetStateIconSize (short width, short height) override;
	virtual void	SetStateIconWidth (short width) override;
	virtual void	SetStateIconHeight (short height) override;

	virtual void	SetItemFontStyle (Int32 tvItem, DG::Font::Style style) override;
	virtual DG::Font::Style	GetItemFontStyle (Int32 tvItem) const override;

	virtual void	SetItemColor (Int32 tvItem, const Gfx::Color& color) override;
	virtual void	ResetItemColor (Int32 tvItem) override;
	virtual bool	GetItemColor (Int32 tvItem, Gfx::Color* color) const override;

	virtual void	SetItemValue (Int32 tvItem, DGUserData value) override;
	virtual DGUserData	GetItemValue (Int32 tvItem) const override;

	virtual void					SetItemObjectData (Int32 tvItem, GS::Ref<GS::Object> object) override;
	virtual GS::Ref<GS::Object>		GetItemObjectData (Int32 tvItem) const override;

	virtual void		SetItemStatus (Int32 tvItem, DG::TreeView::ItemStatus status) override;
	virtual DG::TreeView::ItemStatus	GetItemStatus (Int32 tvItem) const override;

	virtual bool		GetItemRect (Int32 tvItem, DG::Rect* rect) const override;

	virtual void				EnableItem (Int32 tvItem) override;
	virtual void				DisableItem (Int32 tvItem) override;

	virtual void				ExpandItem (Int32 tvItem) override;
	virtual void				CollapseItem (Int32 tvItem) override;
	virtual bool				IsItemExpanded (Int32 tvItem) const override;
	virtual	void		 		BeginItemEdit (Int32 tvItem) override;

	virtual void				SelectItem (Int32 tvItem) override;
	virtual void				DeselectItem (Int32 tvItem) override;
	virtual Int32				GetSelectedCount (void) const override;
	virtual Int32				GetSelectedItem (Int32 tvItem = DG::TreeView::RootItem) const override;
	virtual Int32				GetSelectedItems (Int32* selItems, Int32 maxCount) const override;
	virtual GS::Array<Int32>	GetSelectedItems (void) const override;

	virtual void		DisableDraw () override;
	virtual void		EnableDraw () override;
	virtual void		RedrawItem (Int32 tvItem) override;

	virtual void		SetHelpStyle (DG::TreeView::HelpStyle helpStyle) override;
	virtual DG::TreeView::HelpStyle	GetHelpStyle (void) override;

	virtual void	SetScrollPosition (Int32 scrollPosition) override;
	virtual Int32	GetScrollPosition (void) const override;

	virtual Int32	GetItemFromPosition (const DG::Point& pos) const override;

	virtual GSErrCode	Store (GS::ObjectState& os) const override;

	virtual DG::TreeView& GetNotConstTreeView () override;
	virtual const DG::TreeView& GetConstTreeView () const override;

	virtual Int32	GetItemIndexFromDGItemIndex (Int32 tvItem) const override;

	virtual bool	IsOwnTree (const void* treePtr) const override;

	using	ConstEnumerateFunction = std::function<void (Int32)>;
	
	void	EnumerateItems (Int32 fromIndex, const ConstEnumerateFunction& enumerateFn) const;

	IO::Location	DumpToFile (const GS::Optional<GS::UniString>& fileNameString = GS::NoValue) const;
	USize			LoadFromFile (const IO::Location& filePath);

private:
	enum class ExpandParent {
		True,
		False
	};

	using AllowedArrayBasedTreeItemCache = GS::HashSet<Int32>;

	void AddToDGTreeViewWithAncestors (const ArrayBasedTree<FilterableTreeViewItemData>::Node& treeItem);

	void InsertToDGTreeView (const ArrayBasedTree<FilterableTreeViewItemData>::Node&	treeItem,
							 ExpandParent												expandParent);

	void AddAllChildren (const ArrayBasedTree<FilterableTreeViewItemData>::Node&	treeItem,
						 ExpandParent												expandParent,
						 AllowedArrayBasedTreeItemCache*							cache = nullptr);

	Int32 GetDGTreeViewPositionToInsert (const ArrayBasedTree<FilterableTreeViewItemData>::Node& treeItem) const;

	void ExpandDGTreeViewItemAndParentsUntilRoot (Int32 itemIndex);

	void AdjustItemInDGTreeViewToFilter (const ArrayBasedTree<FilterableTreeViewItemData>::Node&		treeItem,
										 AllowedArrayBasedTreeItemCache*								cache = nullptr);

	void StoreExpandednessBeforeFilteringWhenFilteringJustTurnedOn ();

	void RestoreExpandednessAfterFilteringTurnedOff ();

	void ExpandSelectedItemsAfterFiltering (const GS::Array<Int32>& selectedItems);

	void AdjustScrollPositionAfterFiltering (const GS::Array<Int32>& selectedItems);

	void HandleExpandednessSelectionScrollpositionAfterFiltering ();

	void DeleteFromDGTreeView (const ArrayBasedTree<FilterableTreeViewItemData>::Node& treeItemToDelete,
							   AllowedArrayBasedTreeItemCache*							cache = nullptr);

	bool AllowBecauseItselfOrParent (const ArrayBasedTree<FilterableTreeViewItemData>::Node& treeItem,
									 AllowedArrayBasedTreeItemCache* cache = nullptr,
									 const GS::Optional<std::reference_wrapper<const ArrayBasedTree<FilterableTreeViewItemData>::Node>>& itemToSkip = GS::NoValue) const;

	bool AllowBecauseChildren (const ArrayBasedTree<FilterableTreeViewItemData>::Node& treeItem,
							   AllowedArrayBasedTreeItemCache* cache = nullptr,
							   const GS::Optional<std::reference_wrapper<const ArrayBasedTree<FilterableTreeViewItemData>::Node>>& itemToSkip = GS::NoValue) const;

	bool AllowBecauseItselfParentOrChildren (const ArrayBasedTree<FilterableTreeViewItemData>::Node& treeItem,
											 AllowedArrayBasedTreeItemCache* cache = nullptr,
											 const GS::Optional<std::reference_wrapper<const ArrayBasedTree<FilterableTreeViewItemData>::Node>>& itemToSkip = GS::NoValue) const;

	bool EnsureItemIndexIsOfArrayBasedTree (Int32& itemIndex) const;

	bool EnsureItemIndexIsOfDGTree (Int32& itemIndex) const;

	bool IsGetItemFlagNeedsDGTreeView (const DG::TreeView::GetItemFlag itemFlag) const;

	UD::ArrayBasedTreeBase::GetItemFlag ConvertToArrayBasedTreeBaseGetItemFlag (const DG::TreeView::GetItemFlag itemFlag) const;

};


#ifndef UD_DLL_COMPILE

extern template class UD_DLL_EXPORT FilterableTreeView<DG::SingleSelTreeView>;
extern template class UD_DLL_EXPORT FilterableTreeView<DG::MultiSelTreeView>;

#endif

using FilterableSingleSelTreeView = FilterableTreeView<DG::SingleSelTreeView>;
using FilterableMultiSelTreeView = FilterableTreeView<DG::MultiSelTreeView>;

}

#endif  //GS_UD_FILTERABLETREEVIEW_HPP
