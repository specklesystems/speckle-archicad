#ifndef RADIO_ITEMS_HANDLER_HPP
#define RADIO_ITEMS_HANDLER_HPP

// from GSRoot
#include "Owner.hpp"
#include "OnHeap.hpp"
#include "Ref.hpp"
#include "Array.hpp"

// from UD
#include "UDDefinitions.hpp"
#include "DisplayerRefresherOwner.hpp"
#include "DGRadioItem.hpp"


namespace DG {
	class Panel;
}

namespace UD {
	class EnumDisplayer;
	class EnumValueApplier;
	class RadioItemsChangeObserver;
}

namespace UD {

class UD_DLL_EXPORT RadioItemCreator
{
public:
	virtual ~RadioItemCreator ();

	virtual GS::Ref<DG::RadioItem> CreateRadioItem (const DG::Panel& panel, short itemId) const = 0;
};

class UD_DLL_EXPORT RadioItemsHandler
{
public:
	RadioItemsHandler (const DG::Panel& panel,
					   GS::Array<short> items,
					   const RadioItemCreator& radioItemCreator,
					   GS::Owner<DisplayerRefresher<EnumDisplayer>> displayerRefresherInit,
					   GS::Owner<EnumValueApplier> valueApplierInit,
					   const std::function<void (EnumDisplayer& enumDisplayer)> initializer);

	virtual ~RadioItemsHandler ();

	void MoveAll (short horizontalDelta, short verticalDelta);

private:
	GS::Array<GS::Ref<DG::RadioItem>>		radioItems;
	GS::OnHeap<RadioItemsChangeObserver>	editValueChangeObserver;
	DisplayerRefresherOwner<EnumDisplayer>	displayerRefresherOwner;
};

UD_DLL_EXPORT const RadioItemCreator& GetIconPushRadioCreator ();

}


#endif