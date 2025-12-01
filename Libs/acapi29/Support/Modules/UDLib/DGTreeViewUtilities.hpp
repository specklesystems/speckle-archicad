#ifndef GS_COMMONUI_DGTREEVIEWUTILITIES_HPP
#define GS_COMMONUI_DGTREEVIEWUTILITIES_HPP


#include "UDDefinitions.hpp"
#include "DGUtility.hpp"
#include "FunctionRef.hpp"
#include "DGTreeView.hpp"

namespace UD {

UD_DLL_EXPORT UInt32	GetTreeViewItemLevel (const DG::TreeView& treeView, const Int32 item);
UD_DLL_EXPORT short		GetTreeViewRequiredWidth (const DG::TreeView& treeView);
UD_DLL_EXPORT short		GetTreeViewRequiredHeight (const DG::TreeView& treeView);
UD_DLL_EXPORT DG::Rect	GetTreeViewBoundRect (const DG::TreeView& treeView);

namespace Imp {

// TODO C++20: Refactor this to std::generator<Int32> EnumerateTree (const DG::TreeView& treeView, Int32 root = DG::TreeView::RootItem)

UD_DLL_EXPORT DG::VisitorUtility::ApplyContinuation		EnumerateAllTreeViewItemsBreadthFirst (const DG::TreeView& treeView, Int32 parentItem, GS::FunctionRef<DG::VisitorUtility::ApplyContinuation (Int32 tvItem)> processor);
UD_DLL_EXPORT DG::VisitorUtility::ApplyContinuation		EnumerateAllTreeViewItemsDepthFirst (const DG::TreeView& treeView, Int32 parentItem, GS::FunctionRef<DG::VisitorUtility::ApplyContinuation (Int32 tvItem)> processor);

} // namespace Imp


template <class Callable>
DG::VisitorUtility::ApplyContinuation	EnumerateAllTreeViewItemsDepthFirst (const DG::TreeView& treeView, Int32 parentItem, Callable&& processor)
{
	return UD::Imp::EnumerateAllTreeViewItemsDepthFirst (treeView, parentItem, [&] (Int32 tvItem) {
		return DG::VisitorUtility::ApplyOnElement (processor, tvItem);
	});
}


template <class Callable>
DG::VisitorUtility::ApplyContinuation	EnumerateAllTreeViewItemsDepthFirst (const DG::TreeView& treeView, Callable&& processor)
{
	return EnumerateAllTreeViewItemsDepthFirst (treeView, DG::TreeView::RootItem, std::forward<Callable> (processor));
}


template <class Callable>
DG::VisitorUtility::ApplyContinuation	EnumerateAllTreeViewItemsBreadthFirst (const DG::TreeView& treeView, Int32 parentItem, Callable&& processor)
{
	return Imp::EnumerateAllTreeViewItemsBreadthFirst (treeView, parentItem, [&] (Int32 tvItem) {
		return DG::VisitorUtility::ApplyOnElement (processor, tvItem);
	});
}


template <class Callable>
DG::VisitorUtility::ApplyContinuation	EnumerateAllTreeViewItemsBreadthFirst (const DG::TreeView& treeView, Callable&& processor)
{
	return EnumerateAllTreeViewItemsBreadthFirst (treeView, DG::TreeView::RootItem, std::forward<Callable> (processor));
}


template <class Callable>
DG::VisitorUtility::ApplyContinuation	EnumerateListedTreeViewItemsBreadthFirst (const DG::TreeView& treeView, Callable&& processor)
{
	return EnumerateAllTreeViewItemsBreadthFirst (treeView, [&] (Int32 tvItem) {
		if (treeView.IsItemListed (tvItem)) {
			return DG::VisitorUtility::ApplyOnElement (processor, tvItem);
		}
		return DG::VisitorUtility::Continue;
	});
}


UD_DLL_EXPORT void	ExpandAllTreeViewItems (DG::TreeView& treeView);
UD_DLL_EXPORT void	CollapseAllTreeViewItems (DG::TreeView& treeView);

UD_DLL_EXPORT void	ExpandSelectedTreeViewItemsRecursively (DG::TreeView& treeView);
UD_DLL_EXPORT void	CollapseSelectedTreeViewItemsRecursively (DG::TreeView& treeView);

UD_DLL_EXPORT bool	HasExpandableSelectedTreeViewItemRecursively (const DG::TreeView& treeView);
UD_DLL_EXPORT bool	HasCollapsableSelectedTreeViewItemRecursively (const DG::TreeView& treeView);

} // namespace UD

#endif
