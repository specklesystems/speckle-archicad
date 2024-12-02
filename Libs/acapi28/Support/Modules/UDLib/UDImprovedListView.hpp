#ifndef UDIMPROVEDLISTVIEW_HPP
#define UDIMPROVEDLISTVIEW_HPP

#pragma once

#include <memory>

#include "Ref.hpp"

#include "DGDialog.hpp"
#include "UDDefinitions.hpp"
#include "UDItemInfoTag.hpp"

namespace UD {

class UD_DLL_EXPORT	LayoutableProperty {
public:
	virtual ~LayoutableProperty ();

	virtual void			SetItemMinWidth (short itemMinWidth) = 0;
	virtual void			UpdateItemWidthAfterResize (short dh) = 0;
};

class ImprovedListViewObserver;

template <class ListViewType>
class ImprovedListView :	public ListViewType,
							public LayoutableProperty,
							public ItemInfoTag::DisablerGuardInterfaceConnector
{
	friend class ImprovedListViewObserver;

public:
	ImprovedListView (const DG::Panel& panel, short item,
					  GS::Ref<ItemInfoTag::SettingsProvider> infoTagSettingsProvider = new ItemInfoTag::SettingsProvider (ItemInfoTag::RegistryBasedSettingsOptions ()));

	virtual void	SetItemMinWidth (short itemMinWidth) override;
	virtual void	UpdateItemWidthAfterResize (short dh) override;

	ItemInfoTag::InfoTagContentCreator::MenuItemRowArray CreateMenuItemRowArray (short listItem) const;

private:
	short		itemMinWidth;

	std::shared_ptr<ItemInfoTag::ItemDecorator> decorator;

	short CalcListBoxItemWidth (short dh) const;

};

#ifndef UD_DLL_COMPILE
extern template class UD_DLL_EXPORT ImprovedListView<DG::SingleSelListView>;
extern template class UD_DLL_EXPORT ImprovedListView<DG::MultiSelListView>;
extern template class UD_DLL_EXPORT ImprovedListView<DG::ListView>;
#endif

typedef ImprovedListView<DG::SingleSelListView>	ImprovedSingleSelListView;
typedef ImprovedListView<DG::MultiSelListView>	ImprovedMultiSelListView;
typedef ImprovedListView<DG::ListView>			ImprovedSingleOrMultiSelListView;


class UD_DLL_EXPORT ImprovedListViewObserver : public DG::ListViewObserver
{
public:
	virtual void	CreateMenuItemRowArray (short listItem, const DG::ListView& source, ItemInfoTag::InfoTagContentCreator::MenuItemRowArray& out) const;
};

}

#endif //UDIMPROVEDLISTVIEW_HPP
