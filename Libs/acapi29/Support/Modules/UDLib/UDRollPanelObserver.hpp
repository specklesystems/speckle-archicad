// *********************************************************************************************************************
// File:			UDRollPanelObserver.hpp
//
// Description:		RollDown and RollLeft panel observer
//
// Project:			GRAPHISOFT User Dialog Module (UDLib)
//
// Namespace:		UD
//
// Contact person:	VM
// *********************************************************************************************************************

#ifndef	UDROLLPANELOBSERVER_HPP
#define	UDROLLPANELOBSERVER_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

#include "UDDefinitions.hpp"
#include "UDRollDownInterfaces.hpp"


// === RollPanelObserver interface =====================================================================================

namespace UD {

class UD_DLL_EXPORT RollPanelObserver
{
public:
	virtual							~RollPanelObserver ();

	virtual void					BeginPanelExpanding (const IRollPanel* panel);
	virtual void					EndPanelExpanding (const IRollPanel* panel);

	virtual void					BeginPanelCollapsing (const IRollPanel* panel);
	virtual void					EndPanelCollapsing (const IRollPanel* panel);
};

}
#endif
