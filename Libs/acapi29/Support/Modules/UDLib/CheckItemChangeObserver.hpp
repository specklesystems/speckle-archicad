#ifndef CHECK_ITEM_CHANGE_OBSERVER_HPP
#define CHECK_ITEM_CHANGE_OBSERVER_HPP

#include "Owner.hpp"
#include "DGCheckItem.hpp"
#include "UDDefinitions.hpp"
#include "SimplifiedDataControlTypes.hpp"


namespace UD {

class UD_DLL_EXPORT CheckItemChangeObserver : public DG::CheckItemObserver
{
public:
	CheckItemChangeObserver (GS::Owner<BoolValueApplier> valueApplierInit, DG::CheckItem& observedItem);

	virtual ~CheckItemChangeObserver ();

private:
	virtual void CheckItemChanged (const DG::CheckItemChangeEvent& ev) override final;

	GS::Owner<BoolValueApplier> valueApplier;
};

}

#endif