#ifndef UDIMPROVEDTREEVIEW_HPP
#define UDIMPROVEDTREEVIEW_HPP

#pragma once

#include <memory>

#include "Ref.hpp"

#include "DGDialog.hpp"
#include "UDDefinitions.hpp"
#include "UDItemInfoTag.hpp"


namespace DG {
	class TabPage;
}


namespace UD {

class ImprovedTreeViewObserver;

template <class TreeViewType>
class ImprovedTreeView :	public TreeViewType,
							public ItemInfoTag::DisablerGuardInterfaceConnector {
	friend class ImprovedTreeViewObserver;

public:
	ImprovedTreeView (const DG::Panel& panel, short item, GS::Ref<ItemInfoTag::SettingsProvider> infoTagSettingsProvider = new ItemInfoTag::SettingsProvider (ItemInfoTag::RegistryBasedSettingsOptions ()));
	virtual ~ImprovedTreeView ();

	void SetSettingsProvider (GS::Ref<ItemInfoTag::SettingsProvider> settingsProvider);
	ItemInfoTag::InfoTagContentCreator::MenuItemRowArray CreateMenuItemRowArray (short subItem) const;

private:
	std::shared_ptr<ItemInfoTag::ItemDecorator> decorator;

};

#ifndef UD_DLL_COMPILE
extern template class UD_DLL_EXPORT ImprovedTreeView<DG::SingleSelTreeView>;
extern template class UD_DLL_EXPORT ImprovedTreeView<DG::MultiSelTreeView>;
extern template class UD_DLL_EXPORT ImprovedTreeView<DG::TreeView>;
#endif

typedef ImprovedTreeView<DG::SingleSelTreeView>	ImprovedSingleSelTreeView;
typedef ImprovedTreeView<DG::MultiSelTreeView>	ImprovedMultiSelTreeView;
typedef ImprovedTreeView<DG::TreeView>			ImprovedSingleOrMultiSelTreeView;


class UD_DLL_EXPORT ImprovedTreeViewObserver : public DG::TreeViewObserver {
public:
	virtual void	CreateMenuItemRowArray (short tvItem, const DG::TreeView& source, ItemInfoTag::InfoTagContentCreator::MenuItemRowArray& out) const;
};

}

#endif //UDIMPROVEDTREEVIEW_HPP
