// *****************************************************************************
// File:			APIToolUIPanel.hpp
//
// Namespace:		TBUI
//
// SG compatible
// *****************************************************************************

#ifndef APITOOLUIPANEL_HPP
#define APITOOLUIPANEL_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "VBElemDialogsExport.hpp"

#include "GSRoot.hpp"

#include "DGModule.hpp"
#include "IAPIToolUIData.hpp"

namespace TBUI {

// -----------------------------------------------------------------------------
// Class:		APIToolUIPanel
//
// Description:	Wrapper class
// -----------------------------------------------------------------------------

class VBELEMDIALOGS_DLL_EXPORT APIToolUIPanel
{
protected:
		Int32				refCon;
		DG::TabPage*		tabPage;
public:
						 APIToolUIPanel (Int32 refConParam);
		virtual			~APIToolUIPanel ();

		virtual		bool					CreatePage (const DG::TabControl& tabControl, IAPIToolUIData* data, DG::TabPage** tabPage) = 0;
		virtual		void					DestroyPage (void) = 0;

		Int32								GetRefCon (void) const { return refCon; };
		virtual		const DG::TabPage*		GetTabPage (void) const { return tabPage; };
};

}	// namespace TBUI

#endif
