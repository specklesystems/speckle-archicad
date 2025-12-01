#ifndef UDITEMCONTENTVALIDITYPROPERTY
#define UDITEMCONTENTVALIDITYPROPERTY
#pragma once

#include "DGTabControl.hpp"
#include "DGApplicationObserver.hpp"
#include "FloatingMenu.hpp"
#include "UDDefinitions.hpp"
#include <optional>

namespace UD {

class UD_DLL_EXPORT RectBasedContentValidityProperty :	public DG::ApplicationObserver,
													public DG::PanelObserver,
													public DG::NormalTabObserver,
													public DG::CompoundItemObserver
{
public:
	enum class Position {
		Right,
		Bottom,
	};
private:
	DG::Dialog&						dialog;
	DG::TabPage*					currTabPage;
	Position						position;

	FloatingWindow::FloatingMenu	floatingMenu;
	bool							floatingMenuNeeded;
	bool							inPanelMoving;
	bool							tabPageIsInactive;
	bool							tabPageIsHidden;

	short							modalStateLevel = 0;

protected:
	RectBasedContentValidityProperty (DG::Dialog& dialog, DG::TabPage* currTabPage, Position position);
	virtual ~RectBasedContentValidityProperty ();

	virtual bool			ShouldShowFloatingMenu () const = 0;
	virtual bool			IsItemVisibleAndEnabled () const = 0;
	virtual DG::NativeRect	GetItemNativeRectInScreenSpace (double sf) const = 0;

	//DG::ApplicationObserver
	virtual void	ModalStateBegin (void) override;
	virtual void	ModalStateEnd (void) override;

	//DG::PanelObserver
	virtual void	PanelOpened (const DG::PanelOpenEvent& ev) override;
	virtual void	PanelIdle (const DG::PanelIdleEvent& ev) override;
	virtual void	PanelResizeEntered (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelResizeExited (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelMoveEntered (const DG::PanelMoveEvent& ev) override;
	virtual void	PanelMoved (const DG::PanelMoveEvent& ev) override;
	virtual void	PanelMoveExited (const DG::PanelMoveEvent& ev) override;
	virtual	void	PanelBackgroundPostPaint (const DG::PanelBackgroundPaintEvent& ev) override;
	virtual void	PanelActivated (const DG::PanelActivateEvent& ev) override;
	virtual void	PanelWheelTrackEntered (const DG::PanelWheelEvent& ev, bool* processed) override;
	virtual void	PanelWheelTrackExited (const DG::PanelWheelEvent& ev, bool* processed) override;

	//DG::ItemObserver
	virtual void	ItemFocusGained (const DG::ItemFocusEvent& ev) override;

	//DG::NormalTabObserver
	virtual void	NormalTabClicked (const DG::NormalTabClickEvent& ev, bool* denyChange) override;

	void InitFloatingMenu (const GS::UniString& text);
	void InitFloatingMenu (const GS::Array<GS::UniString>& textLines);
	void UpdateFloatingMenu ();
	void HandleItemContentChanged ();

	void UpdateFloatingMenuText (const GS::UniString& floatingMenuText);

public:
	bool IsFloatingMenuVisible ();
	std::optional<GS::UniString>	GetDisplayedAlertMessage () const;
	void RefreshFloatingMenu (bool onlyIfHidden = true);

private:
	void HideFloatingMenu ();
};


class UD_DLL_EXPORT ItemContentValidityProperty : public RectBasedContentValidityProperty {
protected:

	using RectBasedContentValidityProperty::Position;
	using RectBasedContentValidityProperty::RectBasedContentValidityProperty;

	virtual const DG::Item&	GetDGItem () const = 0;

	virtual bool			IsItemVisibleAndEnabled () const override final;
	virtual DG::NativeRect	GetItemNativeRectInScreenSpace (double sf) const override final;

};


} // namespace UD


#endif
