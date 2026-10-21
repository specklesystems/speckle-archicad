#ifndef GS_TRACKING_ENUMSELECTORTRACKERITEM_HPP
#define GS_TRACKING_ENUMSELECTORTRACKERITEM_HPP

#include "EnumSelectorTrackerItemBase.hpp"
#include <utility>

namespace Tracking
{

template <typename IPropertyType>
class EnumSelectorTrackerItem : public EnumSelectorTrackerItemBase
{
public:
	using PropertyValue = decltype(std::declval<IPropertyType> ().GetValue ());
	~EnumSelectorTrackerItem ();
private:
	IPropertyType* iProperty = nullptr;
	struct ItemConfig : public EnumSelectorTrackerItemBase::ItemConfigBase
	{
		PropertyValue propertyValue;
	};
	GS::Array<ItemConfig> itemConfigs;

public:
	void SetProperty (IPropertyType& propertyType);
	void AddEnumValue (const DG::Icon& icon, const GS::UniString& text, const PropertyValue value);
	virtual void UserControlChanged (const DG::UserControlChangeEvent& ev) override;
protected:
	virtual void Synchronize () const override;
	virtual void ValueChanged (const PropertyValue&) const {};

	virtual const ItemConfig* GetItemConfigForCurrentValue () const override;
	virtual bool ConfigMatchesCurrentValue (const ItemConfigBase&) const override;
	virtual UIndex GetItemConfigCount () const override;
	virtual const ItemConfig& GetItemConfig (UIndex) const override;
};

template<typename IPropertyType>
EnumSelectorTrackerItem<IPropertyType>::~EnumSelectorTrackerItem ()
{
}

template<typename IPropertyType>
void EnumSelectorTrackerItem<IPropertyType>::SetProperty (IPropertyType& propertyType)
{
	iProperty = &propertyType;
}


template<typename IPropertyType>
void EnumSelectorTrackerItem<IPropertyType>::AddEnumValue (const DG::Icon& icon, const GS::UniString& text, const PropertyValue value)
{
	itemConfigs.PushNew (ItemConfigBase { icon, text }, value);
}


template<typename IPropertyType>
void	EnumSelectorTrackerItem<IPropertyType>::UserControlChanged (const DG::UserControlChangeEvent& ev)
{
	if (ev.GetSource () == popupControlOwner.Get ()) {
		const ItemConfig& itemConfig = itemConfigs[popupControlOwner->GetSelectedItem () - 1];
		const PropertyValue& propertyValue = itemConfig.propertyValue;
		iProperty->SetValue (propertyValue, GetParentHint (*parent));

		UpdateControlsWithItemConfig (itemConfig);

		Synchronize ();
		ValueChanged (propertyValue);
	}
}


template<typename IPropertyType>
void EnumSelectorTrackerItem<IPropertyType>::Synchronize () const
{
	if (iProperty != nullptr && popupControlOwner != nullptr) {
		const PropertyValue currentValue = iProperty->GetValue ();
		for (UIndex index = 0; index < itemConfigs.GetSize (); ++index) {
			if (itemConfigs[index].propertyValue == currentValue) {
				popupControlOwner->SelectItem (index + 1);
			}
		}
	}
}


template<typename IPropertyType>
const typename EnumSelectorTrackerItem<IPropertyType>::ItemConfig* EnumSelectorTrackerItem<IPropertyType>::GetItemConfigForCurrentValue () const
{
	const PropertyValue& propertyValue = iProperty->GetValue ();
	for (const ItemConfig& config : itemConfigs) {
		if (config.propertyValue == propertyValue) {
			return &config;
		}
	}
	return nullptr;
}

template<typename IPropertyType>
bool EnumSelectorTrackerItem<IPropertyType>::ConfigMatchesCurrentValue (const ItemConfigBase& configBase) const
{
	DBASSERT (iProperty != nullptr);
	const ItemConfig& config = static_cast<const ItemConfig&>(configBase);
	return config.propertyValue == iProperty->GetValue ();
}

template<typename IPropertyType>
UIndex EnumSelectorTrackerItem<IPropertyType>::GetItemConfigCount () const
{
	return itemConfigs.GetSize ();
}

template<typename IPropertyType>
const typename EnumSelectorTrackerItem<IPropertyType>::ItemConfig& EnumSelectorTrackerItem<IPropertyType>::GetItemConfig (const UIndex index) const
{
	return itemConfigs[index];
}


}

#endif // GS_TRACKING_ENUMSELECTORTRACKERITEM_HPP