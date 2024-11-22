#ifndef RADIO_ITEMS_CHANGE_OBSERVER_HPP
#define RADIO_ITEMS_CHANGE_OBSERVER_HPP

// from GSRoot
#include "Owner.hpp"
#include "Optional.hpp"

// from DG
#include "DGRadioItem.hpp"

// from UD
#include "UDDefinitions.hpp"

namespace UD {
	class EnumValueApplier;
}

namespace UD {

class UD_DLL_EXPORT RadioItemsChangeObserver : public DG::RadioItemObserver
{
public:
	RadioItemsChangeObserver (GS::Owner<EnumValueApplier> valueApplierInit, GS::Array<GS::Ref<DG::RadioItem>>& observedItems);

	virtual ~RadioItemsChangeObserver ();

	void SetObservedRadioItems (GS::Array<GS::Ref<DG::RadioItem>>& newRadioItems);

private:
	virtual void RadioItemChanged (const DG::RadioItemChangeEvent& ev) override final;

	GS::Optional<UInt32> FindRadioItemIndex (DG::RadioItem& otherItem) const;

	GS::Owner<EnumValueApplier> valueApplier;

	GS::Array<GS::Ref<DG::RadioItem>>& referredItems;
};

}

#endif