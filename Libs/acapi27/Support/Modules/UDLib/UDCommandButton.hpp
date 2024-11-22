// *********************************************************************************************************************
// File:			UDCommandButton.hpp
//
// Description:		A DG control, that represents a DG::Command as a DG::IconPushCheck.
//					- Use "IconPushCheck" in the .grc file.
//					- If "NoIcon" is given in the .grc file, the control will use the DG::Command's icon.
//					- Clicking this control posts the DG::Command to the main message loop.
//					- The control's checked/unchecked state and enabled/disabled status cannot be set. It is refreshed
//					  automatically from the DG::Command's state and status.
//					- It can be converted to DG::Item with AsItem (), but do not get or set its enabled/disabled status
//					  through it. Instead query and modify the DG::Command's status directly.
//
// Namespace:		UD
// Module:			UDLib
// Contact person:
//
// *********************************************************************************************************************


#ifndef UDCOMMANDBUTTON_HPP
#define UDCOMMANDBUTTON_HPP

#pragma once


#include "DGCheckItem.hpp"
#include "DGCommandDescriptor.hpp"
#include "UDDefinitions.hpp"


namespace UD {


// === class CommandButton =============================================================================================

class UD_DLL_EXPORT CommandButton : private DG::IconPushCheck,
									private DG::CheckItemObserver,
									private DG::CommandDescriptorObserver
{
public:
	CommandButton (const DG::Panel& panel, short item, const DG::Command& command);
    virtual ~CommandButton ();

	using DG::IconPushCheck::Show;
	using DG::IconPushCheck::Hide;
	using DG::IconPushCheck::SetVisibility;
	using DG::IconPushCheck::IsVisible;
	using DG::IconPushCheck::Flash;
	using DG::IconPushCheck::Move;
	using DG::IconPushCheck::Resize;
	using DG::IconPushCheck::MoveAndResize;
	using DG::IconPushCheck::SetPosition;
	using DG::IconPushCheck::SetRect;
	using DG::IconPushCheck::SetSize;
	using DG::IconPushCheck::SetWidth;
	using DG::IconPushCheck::SetHeight;
	using DG::IconPushCheck::GetPosition;
	using DG::IconPushCheck::GetRect;
	using DG::IconPushCheck::GetWidth;
	using DG::IconPushCheck::GetHeight;
	using DG::IconPushCheck::GetNativeRectInScreenSpace;
	using DG::IconPushCheck::Invalidate;
	using DG::IconPushCheck::Redraw;
	using DG::IconPushCheck::GetResolutionFactor;

	DG::Item&						AsItem ();
	const DG::Item&					AsItem () const;

private:
	virtual void					ItemToolTipRequested (const DG::ItemHelpEvent& ev, GS::UniString* toolTipText) override;
	virtual void					CheckItemChanged (const DG::CheckItemChangeEvent& ev) override;

	virtual void					EnableChanged (const DG::CommandDescriptorEnableEvent& ev) override;
	virtual void					CheckChanged (const DG::CommandDescriptorCheckEvent& ev) override;
	virtual void					IconChanged (const DG::CommandDescriptorIconEvent& ev) override;

	DG::CommandDescriptor* const	mCommandDescriptor;
};


}	// namespace UD


#endif
