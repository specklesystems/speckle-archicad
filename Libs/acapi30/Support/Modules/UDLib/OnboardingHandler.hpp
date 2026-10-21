#ifndef GS_UD_ONBOARDING_HANDLER_HPP
#define GS_UD_ONBOARDING_HANDLER_HPP

#include "UDDefinitions.hpp"

// from DG
#include "DGImage.hpp"
#include "DGPanel.hpp"
#include "DGUserItem.hpp"
#include "DGRect.hpp"
#include "DGButton.hpp"

// from GSRoot
#include "UniString.hpp"

// from StandardLibrary
#include <functional>


namespace UD {

class UD_DLL_EXPORT OnboardingHandler : public DG::PanelObserver,
										public DG::UserItemObserver,
										public DG::ButtonItemObserver,
										public DG::EventTarget
{
public:
	OnboardingHandler (DG::Panel& parentPanel, 
					   DG::Item& overlayedItem, 
					   GSResID userItemResId,
					   std::function<GS::Optional<DG::Icon> ()> getIconCallback,
					   std::function<bool ()> showOnboardingOverlayCallback,
					   std::function<void ()> onboardingOverlayButtonClickedCallback);

	virtual ~OnboardingHandler () = default;

	void Refresh ();

	void SetTopText (const GS::UniString& text);
	void SetBottomText (const GS::UniString& text);
	void SetButtonStatus (bool status);
	void SetButtonClickable (bool status);

private:
	virtual void PanelResized (const DG::PanelResizeEvent& ev) override;
	virtual void PanelResizeExited (const DG::PanelResizeEvent& ev) override;
	virtual void UserItemUpdate (const DG::UserItemUpdateEvent& ev) override;
	virtual void UserItemMouseDown (const DG::UserItemMouseDownEvent& ev, bool* processed) override;

	void RedrawUserItem (const DG::UserItemUpdateEvent& ev);
	void Show ();
	void Hide ();

private:
	DG::UserItem	onboarding;
	DG::Item&		overlayedItem;
	DG::Rect		clickArea;
	bool			buttonStatus;
	bool			buttonClickable;

	GS::UniString topText;
	GS::UniString bottomText;

	const std::function<const GS::Optional<DG::Icon> ()> getIcon;
	const std::function<bool ()>						 showOnboardingOverlay;
	const std::function<void ()>						 onboardingOverlayButtonClicked;
};

}

#endif
