#ifndef GS_ACAPIUIMENU_MENUMANAGER_HPP
#define GS_ACAPIUIMENU_MENUMANAGER_HPP

// from ARCHICADAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "APIdefs_Callback.h"
#include "UserInterfaceAPIExport.hpp"


struct API_MenuItemRef;

namespace ACAPI::UI::Menu {

namespace Impl { class MenuItemImpl; }

class MenuItem;

/**
 * @brief A class that contains menu item related functions.
 * @since Archicad 29
 * @ingroup MenuItem
 */
class USERINTERFACEAPI_DLL_EXPORT MenuManager : public ACAPI::Object {
	friend MenuManager CreateMenuManager ();

public:

	/**
	* @brief Get an existing menu item.
	* @returns The referred menu item object.
	* @param menuItemRef The reference to an add-on menu item.
	* @remarks This function is used to get the menu item which belongs to the caller API tool add-on.
	*/
	Result<MenuItem> GetMenuItem (const API_MenuItemRef& menuItemRef) const;

	/**
	* @brief Create a new menu.
	* @returns Result of the creation
	* @param menuStrResID The resource ID of the menu resource, which should be in the resource fork of the add-on.
	* @param promptStrResID The resource ID of the prompt string resource, which should be in the resource fork of the add-on. These strings appear in the status bar.
	* @param menuPosCode Defines the server application's menu to insert the command into.
	* @param menuFlags Flags describing whether you would like to see any separator item in the menu before or after the registered menu item.
	*			Its possible values are: MenuFlag_Default, MenuFlag_SeparatorBefore, and MenuFlag_SeparatorAfter.
	*/
	Result<void> RegisterMenu (short menuStrResID, short promptStrResID, APIMenuCodeID menuPosCode, GSFlags menuFlags) const;

	/**
	* @brief Installs a callback procedure for handling the add-on's menu commands.
	* @returns Result of the callback procedure installation.
	* @param menuStrResID An identifier of the menu to install the callback procedure for. This should be the same what you used in the RegisterMenu function.
	* @param handlerProc The callback function to handle the menu commands.
	*/
	Result<void> InstallMenuHandler (short menuStrResID, APIMenuCommandProc* handlerProc) const;

private:
	explicit MenuManager (const API_Token& token);
	static MenuManager Create (const API_Token& token);
};


/**
 * @brief A function to create menu manager instance, that lets you query and manipulate menu related data.
 * @ingroup MenuItem
 * @returns The menu manager instance.
 */
inline MenuManager CreateMenuManager ()
{
	return MenuManager::Create (ACAPI_GetToken ());
}

} //namespace ACAPI::UI::Menu

#endif //GS_ACAPIUIMENU_MENUMANAGER_HPP
