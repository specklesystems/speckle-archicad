#ifndef GS_COMMONUI_DGITEMUTILITIES_HPP
#define GS_COMMONUI_DGITEMUTILITIES_HPP


#include "UDDefinitions.hpp"


namespace DG {
	class Item;
	class Dialog;
	class Rect;
}

namespace UD {

UD_DLL_EXPORT	short		GetItemWidth (short dialId, short item);
UD_DLL_EXPORT	short		GetItemHeight (short dialId, short item);

}
//namespace UD {
//	UD_DLL_EXPORT DG::Dialog*	GetItemParentDialog (const DG::Item& item);
//	UD_DLL_EXPORT DG::Rect		GetItemAbsoluteRect (const DG::Item& item);
//}

#endif
