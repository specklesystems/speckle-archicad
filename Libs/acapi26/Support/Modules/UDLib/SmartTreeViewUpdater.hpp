#ifndef GS_UD_SMART_TREE_VIEW_UPDATER_HPP
#define GS_UD_SMART_TREE_VIEW_UPDATER_HPP

#pragma once

#include "UDDefinitions.hpp"
#include "DGTreeView.hpp"
#include "LDTreeDiff.hpp"
#include "TreeViewAccessor.hpp"
#include "BiHashTable.hpp"

namespace UD {

class UD_DLL_EXPORT TreeViewDecorator {
public:
	virtual	void	Decorate (DG::TreeView& treeView, Int32 tvItem, const ListDiff::TreeDiffable& item) = 0;
	virtual ~TreeViewDecorator ();
};


class UD_DLL_EXPORT SmartTreeViewUpdater {
	class IndexMap;

public:
	using ItemType = std::shared_ptr<const ListDiff::TreeDiffable>;
	class UD_DLL_EXPORT UpdateResult {
		friend SmartTreeViewUpdater;

		GS::Array<GS::Guid>		selectedChain;
		GS::HashSet<GS::Guid>	wasExpanded;
		DG::TreeView*			treeView;
		const IndexMap*			indexMap;
		const TreeViewAccessor*	accessor;

		UpdateResult (DG::TreeView* treeView, const IndexMap* indexMap, const TreeViewAccessor* accessor);

		void	StoreExpandeds (const GS::Array<Int32>& tvItems, DG::TreeView* treeView);
		void	StoreSelectedChain ();

	public:
		UpdateResult (UpdateResult&&) = default;

		enum class SelectionRestoreResult {
			RestoredForOldItem,
			RestoredForAParent,
			Failed
		};
		SelectionRestoreResult	RestoreSelection ();

		void	RestoreExpandeds ();
	};
private:

	GS::Array<ItemType>					rootItems;
	UD::TreeViewAccessor				accessor;
	TreeViewDecorator*					decorator;
	DG::TreeView*						treeView;
	Owner<IndexMap>						indexMap;
	GS::HashTable<GS::Guid, ItemType>	itemsById;

	void	InsertSubTree (Int32 rootTvItem, const GS::Array<ItemType>& newItems);

	void	UpdateSubTree (Int32 rootTvItem,
						   const GS::Array<ItemType>& oldItems,
						   const GS::Array<ItemType>& newItems,
						   const ListDiff::TreeResult& result,
						   UpdateResult& updateResult);

	void	UpdateItemsById (const GS::Array<ItemType>& newArray);
	void	UpdateItemObjects ();

public:
	SmartTreeViewUpdater (DG::TreeView* treeView, TreeViewDecorator* decorator);

	UpdateResult					SetRootItems (GS::Array<ItemType>&& newItems);
	const GS::Array<ItemType>&		GetRootItems () const;
	void							UpdateItem (const GS::Guid& id);
	void							SetSelected (const GS::Guid& id) const;
	GS::Guid						GetTreeViewItemId (Int32 tvItem) const;
	bool							HasTreeViewItem (const GS::Guid& id) const;
	ItemType						GetTreeViewItem (Int32 tvItem) const;
	ItemType						GetTreeViewItem (const GS::Guid& id) const;
	Int32							GetTreeViewItemId (const GS::Guid& id) const;
	GS::Array<GS::Guid>				GetSelectedItemIds () const;
	GS::Array<ItemType>				GetSelectedItems () const;

	virtual ~SmartTreeViewUpdater ();
};

} // namespace UD

#endif
