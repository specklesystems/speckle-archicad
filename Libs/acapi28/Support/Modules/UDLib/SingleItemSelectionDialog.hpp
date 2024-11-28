#ifndef SINGLEITEMSELECTIONDIALOG_HPP
#define SINGLEITEMSELECTIONDIALOG_HPP

#include "UDDefinitions.hpp"
#include "ItemSelectionDialog.hpp"


namespace UD {
	class BaseItemSelectionDataObserver;
}


namespace UD {


class UD_DLL_EXPORT SingleItemSelectionDialog : public ItemSelectionDialogBase
{
public:
	SingleItemSelectionDialog (const DG::Item&			parentItem,
							   BaseItemSelectionData&	itemSelectionDialogData);

	SingleItemSelectionDialog (const DG::NativeRect& 	parentRect,
							   BaseItemSelectionData&	itemSelectionDialogData);

	virtual ~SingleItemSelectionDialog ();

private:
	enum {
		DialogResourceId = 2110
	};

	virtual DG::EventHandlerResultType KeyPressed (const DG::Key::Code& code, DG::Item** item) override;
};


class UD_DLL_EXPORT AutoClosingSingleItemSelectionDialog : public SingleItemSelectionDialog
{

public:
	AutoClosingSingleItemSelectionDialog (const DG::Item&			parent,
										  BaseItemSelectionData&	itemSelectionDialogData);

	AutoClosingSingleItemSelectionDialog (const DG::NativeRect& 	parentRect,
										  BaseItemSelectionData&	itemSelectionDialogData);

	virtual ~AutoClosingSingleItemSelectionDialog ();

private:
	virtual void	PanelOpened (const DG::PanelOpenEvent& ev) override;
	virtual void	TreeViewItemDoubleClicked (const DG::TreeViewDoubleClickEvent& ev, bool* processed) override;
	virtual void	ListBoxDoubleClicked (const DG::ListBoxDoubleClickEvent& ev) override;
	virtual void	ButtonClicked (const DG::ButtonClickEvent& ev) override;
};

} // namespace UD


#endif // ITEMSELECTIONDIALOG_HPP
