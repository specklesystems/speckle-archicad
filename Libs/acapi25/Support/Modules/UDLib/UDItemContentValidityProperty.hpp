#ifndef UDITEMCONTENTVALIDITYPROPERTY
#define UDITEMCONTENTVALIDITYPROPERTY
#pragma once

#include "UDDefinitions.hpp"
#include "FloatingMenu.hpp"

namespace UD
{

class UD_DLL_EXPORT ItemContentValidityProperty :	public DG::PanelObserver,
													public DG::NormalTabObserver,
													public DG::CompoundItemObserver
{
private:
	DG::Dialog&						dialog;
	DG::TabPage*					currTabPage;

	FloatingWindow::FloatingMenu	floatingMenu;
	bool							floatingMenuNeeded;
	bool							inPanelMoving;
	bool							tabPageIsInactive;
	bool							tabPageIsHidden;

protected:
	ItemContentValidityProperty (DG::Dialog& dialog, DG::TabPage* currTabPage);
	virtual ~ItemContentValidityProperty ();

	virtual bool ShouldShowFloatingMenu () const = 0;
	virtual const DG::Item& GetDGItem () const = 0;

	//DG::PanelObserver
	virtual void	PanelOpened (const DG::PanelOpenEvent& ev) override;
	virtual void	PanelIdle (const DG::PanelIdleEvent& ev) override;
	virtual void	PanelResizeEntered (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelResizeExited (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelMoveEntered (const DG::PanelMoveEvent& ev) override;
	virtual void	PanelMoveExited (const DG::PanelMoveEvent& ev) override;
	virtual	void	PanelBackgroundPostPaint (const DG::PanelBackgroundPaintEvent& ev) override;

	//DG::ItemObserver
	virtual void	ItemFocusGained (const DG::ItemFocusEvent& ev) override;

	//DG::NormalTabObserver
	virtual void	NormalTabClicked (const DG::NormalTabClickEvent& ev, bool* denyChange) override;

	void InitFloatingMenu (const GS::UniString& alreadyExistsAlertText);
	void UpdateFloatingMenu ();
	void HandleItemContentChanged ();

private:
	void HideFloatingMenu ();
	void RefreshFloatingMenu (bool onlyIfHidden = true);
};

}
#endif
