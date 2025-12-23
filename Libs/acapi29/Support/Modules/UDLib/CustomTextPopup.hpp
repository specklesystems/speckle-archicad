#ifndef CUSTOMTEXTPOPUP_HPP
#define CUSTOMTEXTPOPUP_HPP


#include "DGDialog.hpp"
#include "UDDefinitions.hpp"
#include "UDLinkText.hpp"

namespace UD {

class UD_DLL_EXPORT CustomTextPopup: public DG::ModalDialog,
									 public UD::LinkTextObserver,
									 public DG::PanelObserver
{
public:
	enum WrappingMode {
		WrapContentToMaxWidth = 0,
		WrapContentToScreenSize = 1
	};

	CustomTextPopup (const DG::Item& inParentItem);
	CustomTextPopup (const DG::NativeRect& inParentRect);
	virtual ~CustomTextPopup ();

	void			SetContent			(const GS::UniString& title, const GS::UniString& text, const GS::UniString& linkText, const GS::UniString& linkURL);
	void			SetText				(const GS::UniString& newText);
	void			SetTargetUrl		(const GS::UniString& newText, const GS::UniString& newLink);
	void			SetTargetHelpAnchor (const GS::UniString& newText, const GS::UniString& newHelpAnchor);
	void			SetMaxWidth			(short newMaxWidth);
	void			SetAdditionalWidth	(short newAdditionalWidth);

private:
	enum class LinkType {
		None,
		Url,
		HelpAnchor
	};

	DG::LeftText	titleItem;
	DG::LeftText	contentItem;
	UD::LinkText	linkItem;

	DG::NativeRect	parentRect;
	short			maxWidth;
	short			additionalWidth;
	LinkType		linkType;
	bool			isInitialized;

	enum {
		PopupDialogResourceId	= 1100,
		TitleItemId				= 1,
		ContentItemId			= 2,
		LinkItemId				= 3
	};

	virtual	void	PanelOpened (const DG::PanelOpenEvent& ev) override;
	virtual	void	PanelIdle (const DG::PanelIdleEvent& ev) override;
	virtual void	LinkTextActivated (const UD::LinkTextActivationEvent& ev) override;

	void			FitToText ();
};

} // namespace UD


#endif // CUSTOMTEXTPOPUP_HPP
