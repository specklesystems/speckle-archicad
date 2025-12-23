#ifndef UDSETTINGSCOMBHEADERTABPAGE_HPP
#define UDSETTINGSCOMBHEADERTABPAGE_HPP

#pragma once

#include	<memory>
#include	"UDDefinitions.hpp"
#include	"DGUtility.hpp"
#include	"Ref.hpp"
#include	"UDImprovedTextEdit.hpp"

namespace UD {

class SettingsCombControl;

class UD_DLL_EXPORT SettingsCombHeaderTabPage :	public DG::TabPage,
												public DG::PanelObserver,
												public DG::CompoundItemObserver,
												public DG::TextEditBaseObserver
{
private:
	enum HeaderElements {
		nameStaticTextId	= 1,
		editableEditTextId	= 2,
		nameEditTextId		= 3
	};

	enum {
		TabPageUIResId = 5002
	};

	class TheTextEdit : public UD::ImprovedTextEdit {
	public:
		TheTextEdit (DG::Dialog& dialog, short item, DG::TabPage& tabPage, std::shared_ptr<SettingsCombControl> settingsCombControl);

		virtual bool	GoodName ()			const override;
		virtual bool	UniqueGoodName ()	const override;

		void	StartTimer ();
		void	DeleteTimer ();
		void	PrintTimer () const;
		bool	HasTimer () const;
		double	GetTimerValue () const;

	private:
		std::shared_ptr<SettingsCombControl>	settingsCombControl;

		GS::Ref<GSTimer>			timerRef;
	};


	GS::Array<GS::Ref<GS::Object>>	selSetsCombRefArr;
	std::weak_ptr<SettingsCombControl>			settingsCombControl;

	DG::LeftText					nameStaticText;
	DG::RightText					editableEditText;
	TheTextEdit						nameEditText;

public:
	SettingsCombHeaderTabPage (const DG::TabControl& tabControl, std::shared_ptr<SettingsCombControl> settingsCombControl);

	virtual void	PanelClosed (const DG::PanelCloseEvent& ev) override;

	virtual void	PanelResized (const DG::PanelResizeEvent& ev) override;

	virtual void	PanelIdle (const DG::PanelIdleEvent& ev) override;

	virtual void	PanelContextHelpRequested (const DG::PanelHelpEvent& ev, GS::UniString* contextHelpAnchor) override;

	virtual void	ItemFocusLost (const DG::ItemFocusEvent& ev) override;

	virtual void	TextEditChanged (const DG::TextEditChangeEvent& ev) override;

			void	ApplySelectionChangeAndRefresh (const GS::Array<GS::Ref<GS::Object>>& combs);

			void	Refresh ();

private:
	void TryToApplyTextChange ();
};

} //namespace UD

#endif
