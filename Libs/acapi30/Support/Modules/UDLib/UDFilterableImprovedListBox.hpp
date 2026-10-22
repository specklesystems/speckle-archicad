#include "UDFilterableListBox.hpp"
#include "UDImprovedListBox.hpp"

namespace UD {


class UD_DLL_EXPORT FilterableImprovedSingleSelListBox : public FilterableListBoxHandler {

	UD::ImprovedSingleSelListBox mListBox;

public:

	FilterableImprovedSingleSelListBox (const DG::Panel& panel,
										short item,
										GS::Ref<ItemInfoTag::SettingsProvider> infoTagSettingsProvider
										= new ItemInfoTag::SettingsProvider (ItemInfoTag::RegistryBasedSettingsOptions ()));

	virtual ~FilterableImprovedSingleSelListBox ();
};


class UD_DLL_EXPORT FilterableImprovedMultiSelListBox : public FilterableListBoxHandler {

	UD::ImprovedMultiSelListBox mListBox;

public:

	FilterableImprovedMultiSelListBox (const DG::Panel& panel,
									   short item,
									   GS::Ref<ItemInfoTag::SettingsProvider> infoTagSettingsProvider
									   = new ItemInfoTag::SettingsProvider (ItemInfoTag::RegistryBasedSettingsOptions ()));

	virtual ~FilterableImprovedMultiSelListBox ();
};


}	//namespace UD