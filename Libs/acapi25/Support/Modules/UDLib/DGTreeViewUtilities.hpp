#ifndef GS_COMMONUI_DGTREEVIEWUTILITIES_HPP
#define GS_COMMONUI_DGTREEVIEWUTILITIES_HPP


#include "UDDefinitions.hpp"


namespace DG {
	class Rect;
	class TreeView;
}


namespace UD {
	UD_DLL_EXPORT UInt32 GetTreeViewItemLevel (const DG::TreeView& treeView, const Int32 item);
	UD_DLL_EXPORT short GetTreeViewRequiredWidth (const DG::TreeView& treeView);
	UD_DLL_EXPORT short GetTreeViewRequiredHeight (const DG::TreeView& treeView);
	UD_DLL_EXPORT DG::Rect GetTreeViewBoundRect (const DG::TreeView& treeView);
	UD_DLL_EXPORT void EnumerateAllTreeViewItemsBreadthFirst (const DG::TreeView&							treeView,
																			   const std::function<void (Int32 tvItem)>&	processor);
	UD_DLL_EXPORT void EnumerateAllTreeViewItemsDepthFirst (const DG::TreeView&						treeView,
																			 const std::function<void (Int32 tvItem)>&	processor);
	UD_DLL_EXPORT void EnumerateListedTreeViewItemsBreadthFirst (const DG::TreeView&						treeView,
																				  const std::function<void (Int32 tvItem)>&	processor);
}


#endif