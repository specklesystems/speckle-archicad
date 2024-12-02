#ifndef GS_UD_TREEVIEW_ACCESSOR_HPP
#define GS_UD_TREEVIEW_ACCESSOR_HPP

#pragma once

#include "UDDefinitions.hpp"
#include "DGTreeView.hpp"

namespace UD {

class UD_DLL_EXPORT TreeViewAccessor {
	DG::TreeView* tree;
public:
	TreeViewAccessor (DG::TreeView* tree);
	Int32	GetFirstChildItem (Int32 itemId) const;
	bool	IsExistingItem (Int32 itemId) const;
	Int32	GetPreviousSiblingItem (Int32 itemId) const;
	Int32	GetNextSiblingItem (Int32 itemId) const;
	Int32	GetParentItem (Int32 itemId) const;
	GS::Array<Int32>	GetChildren (Int32 parent) const;
	GS::Array<Int32>	GetAllChildren (Int32 parent) const;
	GS::Array<Int32>	GetSiblings (Int32 aSibling) const;

	Int32	GetInsertItem (Int32 parent, UInt32 index);


	virtual ~TreeViewAccessor ();
};

} // namespace UD


#endif
