// *****************************************************************************
// File:			DGCommandLayout.hpp
//
// Description:		Command layout helper class
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BLA
//
// SG compatible
// *****************************************************************************

#ifndef DGCOMMANDLAYOUT_HPP
#define DGCOMMANDLAYOUT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Object.hpp"
#include "UniString.hpp"

#include "DG.h"
#include "DGCommandDescriptor.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace DG {

class MenuBar;
class Menu;
class ContextMenu;
class ToolBar;
class CommandDescriptor;

// --- Class declarations ------------------------------------------------------

// --- CommandLayout -----------------------------------------------------------

class DG_DLL_EXPORT CommandLayout		:	public GS::Object
{
	DECLARE_CLASS_INFO

private:
	GS::Array<Menu*>				menus;
	GS::Array<ContextMenu*>			contextMenus;
	GS::Array<MenuBar*>				menuBars;
	GS::Array<ToolBar*>				toolBars;

						CommandLayout	(const CommandLayout& source);	// disable copy
		CommandLayout&	operator=		(const CommandLayout& source);

public:

						CommandLayout	();
						CommandLayout	(GS::Array<DG::MenuBar*>& menuBars,
										 GS::Array<DG::Menu*>& menus,
										 GS::Array<DG::ContextMenu*>& contextMenus,
										 GS::Array<DG::ToolBar*>& toolBars);
					   ~CommandLayout	();

	void				DeleteContent	(void);

	// copy
	void				DeepCopy		(const CommandLayout& source);
	void				DeepCopyBinary	(const CommandLayout& source);

	// accessors
	inline GS::Array<DG::MenuBar*>&		GetMenuBars			(void);
	inline GS::Array<DG::Menu*>&		GetMenus			(void);
	inline GS::Array<DG::ContextMenu*>&	GetContextMenus		(void);
	inline GS::Array<DG::ToolBar*>&		GetToolBars			(void);

	inline const GS::Array<DG::MenuBar*>&		GetMenuBars			(void) const;
	inline const GS::Array<DG::Menu*>&			GetMenus			(void) const;
	inline const GS::Array<DG::ContextMenu*>&	GetContextMenus		(void) const;
	inline const GS::Array<DG::ToolBar*>&		GetToolBars			(void) const;

	DG::MenuBar*	GetMenuBar	(GS::Guid guid) const;

	// serialization
	GSErrCode				XMLWrite	(xercesc::DOMElement* parent, int level) const;
	GSErrCode				XMLRead		(const xercesc::DOMElement* parent);
	GSErrCode				XMLReadVersion1	(const xercesc::DOMElement* parent);
	GSErrCode				XMLReadVersion2	(const xercesc::DOMElement* parent);

	virtual	GSErrCode		Read			(GS::IChannel& ic) override;
	virtual	GSErrCode		ReadVersion1	(GS::IChannel& ic);
	virtual	GSErrCode		ReadVersion2	(GS::IChannel& ic);
	virtual	GSErrCode		Write			(GS::OChannel& oc) const override;

	// utilities
	void				SortToolBarsArray ();
};


inline GS::Array<DG::MenuBar*>&	CommandLayout::GetMenuBars (void)
{
	return menuBars;
}


inline GS::Array<DG::Menu*>&	CommandLayout::GetMenus (void)
{
	return menus;
}


inline GS::Array<DG::ContextMenu*>&	CommandLayout::GetContextMenus (void)
{
	return contextMenus;
}


inline GS::Array<DG::ToolBar*>&	CommandLayout::GetToolBars (void)
{
	return toolBars;
}


inline const GS::Array<DG::MenuBar*>&	CommandLayout::GetMenuBars (void) const
{
	return menuBars;
}


inline const GS::Array<DG::Menu*>&	CommandLayout::GetMenus (void) const
{
	return menus;
}


inline const GS::Array<DG::ContextMenu*>&	CommandLayout::GetContextMenus (void) const
{
	return contextMenus;
}


inline const GS::Array<DG::ToolBar*>&	CommandLayout::GetToolBars (void) const
{
	return toolBars;
}

}	// namespace DG

#endif
