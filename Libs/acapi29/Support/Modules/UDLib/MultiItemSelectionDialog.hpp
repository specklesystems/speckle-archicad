#ifndef MULTIITEMSELECTIONDIALOG_HPP
#define MULTIITEMSELECTIONDIALOG_HPP


#include "UDDefinitions.hpp"
#include "ItemSelectionDialog.hpp"


namespace UD {
	class BaseItemSelectionDataObserver;
}


namespace UD {


class UD_DLL_EXPORT MultiItemSelectionDialog :	public ItemSelectionDialogBase
{
public:

	MultiItemSelectionDialog (const DG::Item&			parentItem,
							  BaseItemSelectionData&	itemSelectionDialogData);
	MultiItemSelectionDialog (const DG::NativeRect&		parentRect,
							  BaseItemSelectionData&	itemSelectionDialogData);

	virtual ~MultiItemSelectionDialog ();

private:
	enum {
		DialogResourceId = 2101
	};
};


} // namespace UD


#endif // ITEMSELECTIONDIALOG_HPP
