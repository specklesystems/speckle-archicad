#ifndef UDIMPROVEDLISTBOX_HPP
#define UDIMPROVEDLISTBOX_HPP

#pragma once

#include <memory>

#include "Ref.hpp"

#include "DGDialog.hpp"
#include "DGListBox.hpp"

#include "UDDefinitions.hpp"
#include "UDItemInfoTag.hpp"


namespace DG {
	class TabPage;
}


namespace UD {

class ImprovedListBoxObserver;

template <class ListBoxType>
class ImprovedListBox :	public ListBoxType,
						public ItemInfoTag::DisablerGuardInterfaceConnector {
	friend class ImprovedListBoxObserver;

public:
	ImprovedListBox (const DG::Panel& panel, short item, GS::Ref<ItemInfoTag::SettingsProvider> infoTagSettingsProvider = new ItemInfoTag::SettingsProvider (ItemInfoTag::RegistryBasedSettingsOptions ()));
	virtual ~ImprovedListBox ();

	void SetSettingsProvider (GS::Ref<ItemInfoTag::SettingsProvider> settingsProvider);
	ItemInfoTag::InfoTagContentCreator::MenuItemRowArray CreateMenuItemRowArray (short listItem) const;

private:
	std::shared_ptr<ItemInfoTag::ItemDecorator> decorator;

};

#ifndef UD_DLL_COMPILE
extern template class UD_DLL_EXPORT ImprovedListBox<DG::SingleSelListBox>;
extern template class UD_DLL_EXPORT ImprovedListBox<DG::MultiSelListBox>;
extern template class UD_DLL_EXPORT ImprovedListBox<DG::ListBox>;
#endif

typedef ImprovedListBox<DG::SingleSelListBox>	ImprovedSingleSelListBox;
typedef ImprovedListBox<DG::MultiSelListBox>	ImprovedMultiSelListBox;
typedef ImprovedListBox<DG::ListBox>			ImprovedSingleOrMultiSelListBox;


class UD_DLL_EXPORT ImprovedListBoxObserver : public DG::ListBoxObserver {
public:
	virtual void	CreateMenuItemRowArray (short listItem, const DG::ListBox& source, ItemInfoTag::InfoTagContentCreator::MenuItemRowArray& out) const;
};

}

#endif //UDIMPROVEDLISTBOX_HPP