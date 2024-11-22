#ifndef	UDRESIZEABLESPLITBUTTON_HPP
#define	UDRESIZEABLESPLITBUTTON_HPP

#pragma once

#include "UDDefinitions.hpp"
#include "DGUserControl.hpp"
#include "UCPopup.hpp"

#ifdef WINDOWS
#define USENATIVESPLIT
#endif

namespace UD {

class UD_DLL_EXPORT ResizeableSplitButton
{
public:

	enum RightButtonType {
		PopupMenuType,
		IconButtonType
	};

	ResizeableSplitButton (const DG::Panel& panel, short item, const RightButtonType& type, const bool isCustom);

#ifdef USENATIVESPLIT
	void Attach (DG::SplitButtonObserver& observer);
	void Detach (DG::SplitButtonObserver& observer);
	void Attach (DG::CustomSplitButtonObserver& observer);
	void Detach (DG::CustomSplitButtonObserver& observer);
#else
	void Attach (DG::ButtonItemObserver& observer);
	void Detach (DG::ButtonItemObserver& observer);
#endif

	void			Show				();
	void			Hide				();
	void			SetIcon				(const DG::Icon& icon);
	bool			LeftPartSent		(const DG::ButtonClickEvent& ev);
	bool			RightPartSent		(const DG::UserControlChangeEvent& ev);
	bool			RightPartSent		(const DG::ButtonClickEvent& ev);
	UIndex			GetSelectedItem		() const;
	GS::UniString	GetSelectedItemText	() const;
	void			Move				(short hDisp, short vDisp);
	void			SetStatus			(bool enable);
	void			AppendItem			(const GS::UniString& itemText, const DG::Icon& itemIcon = DG::Icon ());
	void			AppendSeparator		();
	void			DeleteAllItems		();
	USize			GetItemCount		();
	void			SetItemIcon			(short popupItem, const DG::Icon& itemIcon);

#ifdef USENATIVESPLIT
	GS::Ref<DG::SplitButtonBase>	splitButton;
#else
	GS::Ref<DG::IconButton>			splitButton;
	GS::Ref<DG::Item>				splitButton2;
#endif

	GS::Array<DG::Item*>	items;
};

}	// namespace UD

#endif
