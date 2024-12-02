#ifndef GS_COMMONUI_DGTREEVIEWUTILITIES_HPP
#define GS_COMMONUI_DGTREEVIEWUTILITIES_HPP


#include "UDDefinitions.hpp"
#include "Tag.hpp"


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
															  const std::function<void (Int32 tvItem)>&		processor,
															  GS::Tag <void>);

	UD_DLL_EXPORT bool EnumerateAllTreeViewItemsBreadthFirst (const DG::TreeView&							treeView,
															  const std::function<bool (Int32 tvItem)>&		processor,
															  GS::Tag <bool>);

	template <class Callable>
	auto EnumerateAllTreeViewItemsBreadthFirst (const DG::TreeView&	treeView,
												const Callable&		processor);

	UD_DLL_EXPORT void EnumerateAllTreeViewItemsDepthFirst (const DG::TreeView&							treeView,
															const std::function<void (Int32 tvItem)>&	processor,
															GS::Tag <void>);

	UD_DLL_EXPORT bool EnumerateAllTreeViewItemsDepthFirst (const DG::TreeView&							treeView,
															const std::function<bool (Int32 tvItem)>&	processor,
															GS::Tag <bool>);

	template <class Callable>
	auto EnumerateAllTreeViewItemsDepthFirst (const DG::TreeView&	treeView,
											  const Callable&		processor);

	UD_DLL_EXPORT void EnumerateListedTreeViewItemsBreadthFirst (const DG::TreeView&						treeView,
																 const std::function<void (Int32 tvItem)>&	processor);
	

	template <class Callable>
	auto	EnumerateAllTreeViewItemsBreadthFirst (const DG::TreeView& treeView, const Callable& processor)
	{
		return EnumerateAllTreeViewItemsBreadthFirst (treeView, processor, GS::Tag<GS::ResultType<Callable>> ());
	}


	template <class Callable>
	auto	EnumerateAllTreeViewItemsDepthFirst (const DG::TreeView& treeView, const Callable& processor)
	{
		return EnumerateAllTreeViewItemsDepthFirst (treeView, processor, GS::Tag<GS::ResultType<Callable>> ());
	}

	UD_DLL_EXPORT void ExpandAllTreeViewItems (DG::TreeView& treeView);
	UD_DLL_EXPORT void CollapseAllTreeViewItems (DG::TreeView& treeView);

}

#endif
