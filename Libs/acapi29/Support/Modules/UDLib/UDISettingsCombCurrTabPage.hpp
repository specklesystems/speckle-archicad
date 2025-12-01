#ifndef UDISETTINGSCOMBCURRTABPAGE_HPP
#define UDISETTINGSCOMBCURRTABPAGE_HPP

#pragma once

#include	<memory>
#include	"UDDefinitions.hpp"
#include	"UDRollDownInterfaces.hpp"
#include	"DGTabPage.hpp"

namespace UD {

class SettingsCombControl;

class UD_DLL_EXPORT ISettingsCombCurrTabPage : public DG::TabPage
{
protected:
	std::weak_ptr<SettingsCombControl>	settingsCombControl;
	UD::IRollPanel::GrowType			growType;
	DG::Icon							rollControlIcon;

public:
	ISettingsCombCurrTabPage (const DG::TabControl&					tabControl,
							 GSResModule							resModule,
							 short									resId,
							 GSResModule							dialIconResModule,
							 std::shared_ptr<SettingsCombControl>	settingsCombControl,
							 UD::IRollPanel::GrowType				growType = UD::IRollPanel::HVGrow,
							 short									rollControlIconId = DG::Icon::NoIcon);

	ISettingsCombCurrTabPage (const DG::TabControl&					tabControl,
							 short									width,
							 short									height,
							 std::shared_ptr<SettingsCombControl>	settingsCombControl);

	virtual ~ISettingsCombCurrTabPage ();

	virtual GS::UniString			GetTitle () const			{ return GS::UniString (); };
	inline UD::IRollPanel::GrowType	GetGrowType () const		{ return growType; };
	inline DG::Icon					GetRollControlIcon () const	{ return rollControlIcon; };

	virtual void	ApplySelectionChangeAndRefresh (const GS::Array<GS::Ref<GS::Object>>& combs) = 0;

	virtual void	Refresh () = 0;
};

} //namespace UD

#endif
