#ifndef UDIMPROVEDFLOATINGMENU_HPP
#define UDIMPROVEDFLOATINGMENU_HPP

#pragma once

#include "DGDialog.hpp"
#include "DGApplicationObserver.hpp"
#include "UDDefinitions.hpp"
#include "FloatingMenu.hpp"

namespace UD
{

class UD_DLL_EXPORT ImprovedFloatingMenu :	public FloatingWindow::FloatingMenu,
											public DG::PanelObserver,
											public DG::ApplicationObserver
{
public:
	enum Pos {
		IFM_Top,
		IFM_Left,
		IFM_Bottom,
		IFM_Right
	};

private:
	const DG::Item&					m_attachedItem;
	DG::Dialog&						m_dialog;
	Pos								m_pos;
	bool							m_isEnabled;
	bool							m_justOpened;

	short	Init (Pos pos);

public:
	ImprovedFloatingMenu (DG::Dialog& dialog, const DG::Item& item);

	~ImprovedFloatingMenu ();

	void	SetTextAndInit (Pos pos, const GS::UniString& text, const GS::UniString* const titleText = nullptr);
	void	SetIconTextAndInit (Pos pos, const DG::Icon& icon, const GS::UniString& text);

	void	SetStatus (const bool enable);
	void	Enable (void);
	void	Disable (void);

protected:
	//DG::PanelObserver
	virtual void	PanelResizeEntered (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelResizeExited (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelMoveEntered (const DG::PanelMoveEvent& ev) override;
	virtual void	PanelMoveExited (const DG::PanelMoveEvent& ev) override;
	virtual void	PanelOpened (const DG::PanelOpenEvent& ev) override;
	virtual void	PanelClosed (const DG::PanelCloseEvent& ev) override;
	virtual void	PanelIdle (const DG::PanelIdleEvent& ev) override;

	//DG::ApplicationObserver
	virtual	void	ApplicationActivated (void) override;

	//own
	void	Refresh ();
};
}

#endif //UDIMPROVEDFLOATINGMENU_HPP
