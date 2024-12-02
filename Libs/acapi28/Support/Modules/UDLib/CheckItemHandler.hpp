#ifndef CHECK_ITEM_HANDLER_HPP
#define CHECK_ITEM_HANDLER_HPP

#include "OnHeap.hpp"
#include "DisplayerRefresherOwner.hpp"
#include "SimplifiedDataControlTypes.hpp"
#include "CheckItemDisplayer.hpp"


namespace DG {
	class Panel;
	class CheckItem;
}

namespace UD {
	class BoolDisplayer;
	class CheckItemChangeObserver;
}

namespace UD {

class UD_DLL_EXPORT CheckItemHandler
{
public:
	CheckItemHandler (
		GS::Owner<DG::IconPushCheck> iconPushCheck,
		const IconPushCheckDisplayer::InitData& displayerInitData,
		GS::Owner<DisplayerRefresher<BoolDisplayer>> refresherInit,
		GS::Owner<BoolValueApplier> valueApplierInit,
		const std::function<void (BoolDisplayer&)> initializer
	);

	virtual ~CheckItemHandler ();

	void Move (short horizontalDelta, short verticalDelta);

private:
	GS::Owner<DG::CheckItem>				checkItem;
	GS::OnHeap<CheckItemChangeObserver>		editValueChangeObserver;
	DisplayerRefresherOwner<BoolDisplayer>	displayerRefresherOwner;
};

}


#endif