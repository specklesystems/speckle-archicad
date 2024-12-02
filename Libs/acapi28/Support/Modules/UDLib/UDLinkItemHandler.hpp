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

#include "DGStaticItem.hpp"
#include "UDDefinitions.hpp"


// --- Class declarations ----------------------------------------------------------------------------------------------

namespace UD {

// --- LinkItemHandler class -------------------------------------------------------------------------------------------

class UD_DLL_EXPORT LinkItemHandler : public DG::StaticTextObserver
{
private:
	DG::StaticText&	staticText;

public:
	static const Gfx::Color linkColor;
	static const Gfx::Color visitedLinkColor;

	LinkItemHandler (DG::StaticText& staticText);
	virtual ~LinkItemHandler ();

	virtual void	StaticTextMouseMoved (const DG::StaticTextMouseMoveEvent& ev, bool* noDefaultCursor) override;
	virtual void	StaticTextClicked (const DG::StaticTextClickEvent& ev) override;

	void			SetCursor (void);
};

}	// namespace UD

#endif
