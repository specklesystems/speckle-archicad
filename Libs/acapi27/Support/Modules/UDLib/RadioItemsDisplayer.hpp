#ifndef RADIO_ITEMS_DISPLAYER_HPP
#define RADIO_ITEMS_DISPLAYER_HPP

// from GSRoot
#include "Ref.hpp"

// from UD
#include "EnumDisplayer.hpp"

namespace DG {
	class RadioItem;
}

namespace UD { 

class UD_DLL_EXPORT RadioItemsDisplayer : public EnumDisplayer
{
public:
	RadioItemsDisplayer (GS::Array<GS::Ref<DG::RadioItem>>& radioItemsInit);

	virtual ~RadioItemsDisplayer ();

	virtual void SetEnumItem (UInt32 index) override final;
	virtual void DisableEnumItem (UInt32 index) override final;
	virtual void EnableEnumItem (UInt32 index) override final;
	virtual void SetFullDisable () override final;
	virtual void ReleaseFullDisable () override final;

private:
	GS::Array<GS::Ref<DG::RadioItem>>& radioItems;
	GS::Array<bool> itemEnabledFlags;
	bool forceDisableItems;
};

}

#endif