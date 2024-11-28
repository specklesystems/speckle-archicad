#ifndef SETTINGSCOMBMAINDIALOG_HPP
#define SETTINGSCOMBMAINDIALOG_HPP

#pragma once

#include	<memory>
#include	"UDRollDownDialogs.hpp"


namespace UD {
	class SettingsCombHeaderTabPage;
	class SettingsCombListTabPage;
	class ISettingsCombCurrTabPage;
	class SettingsCombControl;
	class SettingsCombDialogState;
}

namespace UD {

class UD_DLL_EXPORT SettingsCombMainDialog : public UD::RollDownModalDialog {
public:
	class UD_DLL_EXPORT ISettingsCombDialogEnvironment : public DG::PanelObserver {
	public:
		virtual ~ISettingsCombDialogEnvironment ();

		virtual GS::UniString	GetDialogTitle () const = 0;

		virtual USize			GetTabPageCount () const { return 1; };

		virtual bool			IsHeaderPanelVisible () const { return true; };

		virtual GS::Array<UD::ISettingsCombCurrTabPage*> CreateSettingsCombCurrTabPage (const GS::Array<UD::IRollPanel*>& rollPanelArray, std::shared_ptr<UD::SettingsCombControl> settingsCombControl) = 0;

		virtual bool IsLeftPanelDeactivated () const { return false; };

		virtual bool IsLeftPanelEditable () const { return true; };

		virtual bool IsListBoxTypeMultiSel () const { return true; }; 

		//Based on GRC: MultiSelList 0 3 266 278 LargePlain PartialItems VScroll 21 HasHeader 18
		virtual DG::Rect GetRect () const { return DG::Rect (0, 3, 266, 278); };

		virtual DG::Font::Style GetFontStyle () const { return DG::Font::Plain; };

		virtual DG::Font::Size GetFontSize () const { 
#ifdef WINDOWS
			return DG::Font::Large;
#else
			return DG::Font::Small;
#endif 
		};

		virtual DG::ListBox::ScrollType GetScrollType () const { return DG::ListBox::VScroll; };

		virtual short GetItemSize () const { return 21; };

		virtual DG::ListBox::PartialItemType GetPartialItemType () const { return DG::ListBox::PartialItems; };

		virtual DG::ListBox::HeaderFlag GetHeaderFlag () const { return DG::ListBox::Header; };

		virtual short GetHeaderSize () const { return 18; };

		virtual DG::ListBox::FrameType GetFrameType () const { return DG::ListBox::NoFrame; };

		virtual GS::Array<short> GetSearchTabIndices () const { return {1}; }
	};

	class UD_DLL_EXPORT ICustomBottomPanelCreator {
	public:
		virtual ~ICustomBottomPanelCreator ();

		virtual void	CreateBottomPanel (UD::RollDownModalDialog& rollDownDialog) = 0;
	};
protected:
	GS::Array<GS::Ref<GS::Object>>&				setsCombRefArr;
	GS::Ref<ISettingsCombDialogEnvironment>		dialogEnvironment;
	std::shared_ptr<SettingsCombControl>		settingsCombControl;

public:
	SettingsCombMainDialog (GS::Ref<ISettingsCombDialogEnvironment>		dialogEnvironment,
							GS::Array<GS::Ref<GS::Object> >&			setsCombRefArr,
							std::shared_ptr<SettingsCombControl>		settingsCombControl,
							const SettingsCombDialogState*				dialogState,
							const GS::Guid&								guid = GS::NULLGuid);

	SettingsCombMainDialog (GS::Ref<ISettingsCombDialogEnvironment>		dialogEnvironment,
							GS::Array<GS::Ref<GS::Object> >&			setsCombRefArr,
							std::shared_ptr<SettingsCombControl>		settingsCombControl,
							const SettingsCombDialogState*				dialogState,
							GS::Ref <ICustomBottomPanelCreator>			customBottomPanelCreator,
							const GS::Guid&								guid = GS::NULLGuid);

	~SettingsCombMainDialog ();

	SettingsCombDialogState GetDialogState () const;

private:
	void InitCustomBottomPanel	(GS::Ref <ICustomBottomPanelCreator>	customBottomPanelCreator);

	void InitMainTabPages		(GS::Ref<ISettingsCombDialogEnvironment>	settingsCombDialogEnvironment,
								 const SettingsCombDialogState*				dialogState);
};


} //namespace UD

#endif
