// *********************************************************************************************************************
// File:			UDLinkItemHandler.hpp
//
// Description:		LinkItemHandler classes
//
// Project:			GRAPHISOFT User Dialog Module (UDLib)
//
// Namespace:		UD
//
// Contact person:	UE
//
// SG compatible
// *********************************************************************************************************************

#ifndef UDLINKITEMHANDLER_HPP
#define UDLINKITEMHANDLER_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "AppearanceManager/DGColorCatalog.hpp"
#include "DGStaticItem.hpp"
#include "UDDefinitions.hpp"

namespace DG {
	class AppearanceManager;
	class AppearanceChangedEventArg;
}

// --- Class declarations ----------------------------------------------------------------------------------------------

namespace UD {

// --- LinkItemHandler class -------------------------------------------------------------------------------------------

class UD_DLL_EXPORT LinkItemHandler : public DG::StaticTextObserver,
									  public DG::EventTarget
{
private:
	DG::ColorId	textColorId = DG::ColorId::LinkColor;
	DG::StaticText&	staticText;

public:
	explicit LinkItemHandler (DG::StaticText& staticText);
	virtual ~LinkItemHandler ();

	virtual void	StaticTextMouseMoved (const DG::StaticTextMouseMoveEvent& ev, bool* noDefaultCursor) override;
	virtual void	StaticTextClicked (const DG::StaticTextClickEvent& ev) override;

private:
	void			SetCursor ();
	void			AppearanceChangedHandler(const DG::AppearanceManager& /*manager*/, const DG::AppearanceChangedEventArg& /*arg*/);
	void 			UpdateTextColor ();
};

}	// namespace UD

#endif
