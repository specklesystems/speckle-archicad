#ifndef GS_DG_DGCOMMANDLAYOUTCLEANER_HPP
#define GS_DG_DGCOMMANDLAYOUTCLEANER_HPP

#include "Array.hpp"
#include "DGDLLExport.h"
#include <functional>


namespace DG {
	class Menu;
	class MenuBar;
	class ToolBar;
	class CommandTreeItem;
	class CommandTreeItemList;
}


namespace DG {
	using CommandItemPredicate = std::function <bool (const CommandTreeItem&)>;

	DG_DLL_EXPORT void CCALL CleanCommands	(DG::CommandTreeItemList& list, const CommandItemPredicate& shouldRemoveCommand);
	DG_DLL_EXPORT void CCALL CleanMenuBars	(GS::Array<DG::MenuBar*>& menuBars, const CommandItemPredicate& shouldRemoveCommand);
	DG_DLL_EXPORT void CCALL CleanMenus		(GS::Array<DG::Menu*>& menus, const CommandItemPredicate& shouldRemoveCommand);
	DG_DLL_EXPORT void CCALL CleanToolBars	(GS::Array<DG::ToolBar*>& toolBars, const CommandItemPredicate& shouldRemoveCommand);
}


#endif