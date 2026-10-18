// *****************************************************************************
// File:			APIAttrUIPanel.hpp
//
// Namespace:		VBAD
//
// SG compatible
// *****************************************************************************

#ifndef APIATTRUIPANEL_HPP
#define APIATTRUIPANEL_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "VBElemDialogsExport.hpp"

#include "GSRoot.hpp"

#include "DGModule.hpp"
#include "IAPIAttrUIData.hpp"

namespace VBAD {

// -----------------------------------------------------------------------------
// Class:		APIAttrUIPanel
//
// Description:	Wrapper class
// -----------------------------------------------------------------------------

class VBELEMDIALOGS_DLL_EXPORT APIAttrUIPanel
{
protected:
		Int32				refCon;
		DG::TabPage*		tabPage;
public:
						 APIAttrUIPanel (Int32 refConParam);
		virtual			~APIAttrUIPanel ();

		virtual		bool					CreatePage (const DG::TabControl& tabControl, IAPIAttrUIData* data, DG::TabPage** tabPage) = 0;
		virtual		void					DestroyPage (void) = 0;

		Int32								GetRefCon (void) const { return refCon; };
		virtual		const DG::TabPage*		GetTabPage (void) const { return tabPage; };
};

}	// namespace VBAD

#endif
