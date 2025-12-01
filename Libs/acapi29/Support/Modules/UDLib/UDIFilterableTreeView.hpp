#ifndef GS_UD_IFILTERABLETREEVIEW_HPP
#define GS_UD_IFILTERABLETREEVIEW_HPP
#pragma once

#include "UDIFilterableItem.hpp"
#include "DGTreeView.hpp"

namespace UD {

class UD_DLL_EXPORT IFilterableTreeView : public IFilterableItem {
public:
	virtual ~IFilterableTreeView ();

	virtual void	Attach (DG::TreeViewObserver& observer) = 0;
	virtual void	Detach (DG::TreeViewObserver& observer) = 0;

	virtual Int32	AppendItem (Int32 parentItem) = 0;
	virtual Int32	InsertItem (Int32 parentItem, Int32 targetTvPosion) = 0;
	virtual void	DeleteItem (Int32 tvItem) = 0;
	virtual Int32	GetItemCount (void)	const = 0;

	virtual Int32	GetItem (Int32 tvItem, DG::TreeView::GetItemFlag flag) const = 0;
	virtual Int32	GetTopMostParent (Int32 tvItem) const = 0;
	virtual bool	HasAncestor (Int32 tvItem, Int32 ancestorItem) const = 0;
	virtual Int32	GetLastVisibleChild (Int32 tvItem) const = 0;

	virtual void			SetItemText (Int32 tvItem, const GS::UniString& text) = 0;
	virtual GS::UniString	GetItemText (Int32 tvItem) const = 0;

	virtual void		SetItemNormalIcon (Int32 tvItem, const DG::Icon& icon) = 0;
	virtual DG::Icon	GetItemNormalIcon (Int32 tvItem) const = 0;

	virtual void		SetItemStateIcon (Int32 tvItem, const DG::Icon& icon) = 0;
	virtual DG::Icon	GetItemStateIcon (Int32 tvItem) const = 0;

	virtual void		SetItemOverlayIcon (Int32 tvItem, const DG::Icon& icon) = 0;
	virtual DG::Icon	GetItemOverlayIcon (Int32 tvItem) const = 0;

	virtual void	SetNormalIconSize (short width, short height) = 0;
	virtual void	SetNormalIconWidth (short width) = 0;
	virtual void	SetNormalIconHeight (short height) = 0;

	virtual short	GetNormalIconWidth () const = 0;
	virtual short	GetNormalIconHeight () const = 0;

	virtual void	SetStateIconSize (short width, short height) = 0;
	virtual void	SetStateIconWidth (short width) = 0;
	virtual void	SetStateIconHeight (short height) = 0;

	virtual void		SetItemFontStyle (Int32 tvItem, DG::Font::Style style) = 0;
	virtual DG::Font::Style	GetItemFontStyle (Int32 tvItem) const = 0;

	virtual void	SetItemColor (Int32 tvItem, const Gfx::Color& color) = 0;
	virtual void	ResetItemColor (Int32 tvItem) = 0;
	virtual bool	GetItemColor (Int32 tvItem, Gfx::Color* color) const = 0;

	virtual void	SetItemValue (Int32 tvItem, DGUserData value) = 0;
	virtual DGUserData	GetItemValue (Int32 tvItem) const = 0;

	virtual void					SetItemObjectData (Int32 tvItem, GS::Ref<GS::Object> object) = 0;
	virtual GS::Ref<GS::Object>		GetItemObjectData (Int32 tvItem) const = 0;

	virtual void		SetItemStatus (Int32 tvItem, DG::TreeView::ItemStatus status) = 0;
	virtual DG::TreeView::ItemStatus	GetItemStatus (Int32 tvItem) const = 0;

	virtual bool		GetItemRect (Int32 tvItem, DG::Rect* rect) const = 0;

	virtual void				EnableItem (Int32 tvItem) = 0;
	virtual void				DisableItem (Int32 tvItem) = 0;

	virtual void				ExpandItem (Int32 tvItem) = 0;
	virtual void				CollapseItem (Int32 tvItem) = 0;
	virtual bool				IsItemExpanded (Int32 tvItem) const = 0;
	virtual	void		 		BeginItemEdit (Int32 tvItem) = 0;


	virtual void				SelectItem (Int32 tvItem) = 0;
	virtual void				DeselectItem (Int32 tvItem) = 0;
	virtual Int32				GetSelectedCount (void) const = 0;
	virtual Int32				GetSelectedItem (Int32 tvItem = DG::TreeView::RootItem) const = 0;
	virtual Int32				GetSelectedItems (Int32* selItems, Int32 maxCount) const = 0;
	virtual GS::Array<Int32>	GetSelectedItems (void) const = 0;

	virtual void		DisableDraw () = 0;
	virtual void		EnableDraw () = 0;
	virtual void		RedrawItem (Int32 tvItem) = 0;

	virtual void		SetHelpStyle (DG::TreeView::HelpStyle helpStyle) = 0;
	virtual DG::TreeView::HelpStyle	GetHelpStyle (void) = 0;

	virtual void	SetScrollPosition (Int32 scrollPosition) = 0;
	virtual Int32	GetScrollPosition (void) const = 0;

	virtual Int32	GetItemFromPosition (const DG::Point& pos) const = 0;

	virtual GSErrCode	Store (GS::ObjectState& os) const = 0;

	virtual DG::TreeView& GetNotConstTreeView () = 0;
	virtual const DG::TreeView& GetConstTreeView () const = 0;

	virtual Int32	GetItemIndexFromDGItemIndex (Int32 tvItem) const = 0;

	virtual bool	IsOwnTree (const void* treePtr) const = 0;
};

}

#endif //GS_UD_IFILTERABLETREEVIEW_HPP
