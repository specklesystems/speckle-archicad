#ifndef UDIMPROVEDFLOATINGMENU_HPP
#define UDIMPROVEDFLOATINGMENU_HPP

#pragma once

#include "DGDialog.hpp"
#include "DGApplicationObserver.hpp"
#include "UDDefinitions.hpp"
#include "DGUserControl.hpp"
#include "FloatingMenu.hpp"

namespace UD {


class ImprovedFloatingMenuObserver;


class UD_DLL_EXPORT ImprovedFloatingMenu :	public FloatingWindow::FloatingMenu,
											public DG::ItemObserver,
											public DG::PanelObserver,
											public DG::ApplicationObserver,
											public GS::EventSource
{
public:
	enum Pos {
		IFM_Top,
		IFM_Left,
		IFM_Bottom,
		IFM_Right
	};

	using ItemRectGetterFunction = std::function<DG::NativeRect ()>;

private:
	ItemRectGetterFunction			m_itemRectGetterFunction;
	DG::Dialog&						m_dialog;
	Pos								m_pos;
	bool							m_isEnabled = false;
	bool							m_justOpened = true;
	bool							m_inPanelResizing = false;
    bool                            m_inPanelMoving = false;
	bool							m_wasShown = false;
	UInt32							m_relativeModalDialogLevel = 0;
    bool                            m_forcePlaceInFrontOfOnNextIdle = false;

public:
	ImprovedFloatingMenu (DG::Dialog& dialog,
						  const ItemRectGetterFunction& itemRectGetterFunction,
						  GS::Array<DG::Panel*> panelListToAttachToAllItems = {});
	virtual ~ImprovedFloatingMenu () override;

private:
	short	Init (Pos pos);

	enum class RefreshMethod {Normal, ForcedPlaceInFrontOf};

	void	RefreshInternal (RefreshMethod refreshMethod);
	void	UpdatePosition (const DG::NativeRect& itemRect);

public:
	void	Attach (ImprovedFloatingMenuObserver& observer);
	void	Detach (ImprovedFloatingMenuObserver& observer);

	void	SetTextAndInit (Pos pos, const GS::UniString& text, const GS::UniString* const titleText = nullptr);
	void	SetIconTextAndInit (Pos pos, const DG::Icon& icon, const GS::UniString& text);

	void	SetStatus (const bool enable);
	void	Enable (void);
	void	Disable (bool reset = false);
	bool	WasShown () const;

protected:
	//FloatingWindow::FloatingMenu
	virtual void	OnClick () override;

	//DG::Item
    virtual void    ItemTrackEntered (const DG::ItemTrackEvent& ev) override;
    virtual void	ItemTrackExited (const DG::ItemTrackEvent& ev) override;

	//DG::PanelObserver
	virtual void	PanelResizeEntered (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelResizeExited (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelMoveEntered (const DG::PanelMoveEvent& ev) override;
	virtual void	PanelMoved (const DG::PanelMoveEvent& ev) override;
	virtual void	PanelMoveExited (const DG::PanelMoveEvent& ev) override;
	virtual void	PanelClosed (const DG::PanelCloseEvent& ev) override;
	virtual void	PanelIdle (const DG::PanelIdleEvent& ev) override;
	virtual void	PanelTopStatusGained (const DG::PanelTopStatusEvent& ev) override;
	virtual void	PanelTopStatusLost (const DG::PanelTopStatusEvent& ev) override;
	virtual void	PanelActivated (const DG::PanelActivateEvent& ev) override;

	//DG::ApplicationObserver
	virtual	void	ApplicationActivated (void) override;
	virtual void	ModalStateBegin (void) override;
	virtual void	ModalStateEnd (void) override;

	//own
	void	Refresh ();

};


class UD_DLL_EXPORT ImprovedFloatingMenuObserver : public GS::EventObserver {
	friend class ImprovedFloatingMenu;

protected:
	virtual void	FloatingMenuClicked ();

};


}

#endif //UDIMPROVEDFLOATINGMENU_HPP
