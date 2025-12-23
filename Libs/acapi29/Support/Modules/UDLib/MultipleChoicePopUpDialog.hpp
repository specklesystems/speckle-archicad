#ifndef	GS_COMMONUI_MULTIPLECHOICEPOPUPDIALOG_HPP
#define	GS_COMMONUI_MULTIPLECHOICEPOPUPDIALOG_HPP


#include "UDDefinitions.hpp"
#include "DGDialog.hpp"
#include "MultipleChoiceListBox.hpp"


namespace UD {


class UD_DLL_EXPORT MultipleChoicePopUpDialog : public DG::ModalDialog,
												public DG::PanelObserver
{
private:
	enum {
		DialogResourceId = 2105
	};

	enum {
		NoScrollListBoxId	= 1,
		VScrollListBoxId	= 2
	};

	MultipleChoiceListBox	noScrollMultipleChoiceListBox;
	MultipleChoiceListBox	vScrollMultipleChoiceListBox;
	const DG::Item*			parentItem;
	const short				parentDialogId;
	const short				parentItemId;

	virtual void	PanelOpened (const DG::PanelOpenEvent& ev) override;
	virtual void	PanelResized (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelResizeExited (const DG::PanelResizeEvent& ev) override;

public:
	MultipleChoicePopUpDialog  (MultipleChoiceData&	multipleChoiceData, const DG::Item& parentItem);
	MultipleChoicePopUpDialog  (MultipleChoiceData&	multipleChoiceData, short parentDialogId, short parentItemId);
};


} // namespace UD


#endif
