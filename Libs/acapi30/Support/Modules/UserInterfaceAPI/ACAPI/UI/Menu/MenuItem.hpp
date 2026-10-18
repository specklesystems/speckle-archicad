#ifndef GS_ACAPIUIMENU_MENUITEM_HPP
#define GS_ACAPIUIMENU_MENUITEM_HPP

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

#include "UserInterfaceAPIExport.hpp"

#include <vector>

struct API_MenuItemRef;

namespace ACAPI::UI::Menu {

namespace Impl { class MenuItemImpl; }

/**
 * @brief MenuItem is a representation of one of this add-on's menu items.
 * @ingroup MenuItem
 * @par Example code snippets from DG_Test / Dump information about this menucommand
 *		@snippet DG_Test.cpp MenuItem-Example
 * @since Archicad 29
 */
class USERINTERFACEAPI_DLL_EXPORT MenuItem : public ACAPI::Object {
friend class MenuManager;

public:
	/**
	 * @brief The raw text of the menu item. Raw text contains & to indicate accelerator keys, and double && to indicate a single &.
	 * @returns Menu item text.
	 */
	GS::UniString	GetRawText () const;

	/**
	 * @brief The display text of the menu item. Display text contains only single &.
	 * @returns Menu item text.
	 */
	GS::UniString	GetDisplayText () const;

	/**
	 * @brief Changes the text of the menu item. Raw text must be used, display text is derived from the raw text. Accelerator keys may be indicated with a preceeding ampersand.
	 * @param rawText Menu item text to set.
	 */
	void			SetRawText (const GS::UniString& rawText);

	/**
	 * @brief Changes the text of the menu item. Display text must be used, and this is converted into raw text. There are no accelerator keys.
	 * @param displayText Menu item text to set.
	 */
	void			SetDisplayText (const GS::UniString& displayText);

	/**
	 * @brief The text of the menu item, which appears in the Work Environment Dialog.
	 * @returns The text that appears as the name of the menu item in the menu customization part of the work environment dialog.
	 */
	GS::UniString	GetWorkEnvironmentText () const;

	/**
	 * @brief Changes the text of the menu item, which will appear in the Work Environment Dialog.
	 * @param text The text that will appear as the name of the menu item in the menu customization part of the work environment dialog.
	 * @par Example code snippets from DG_Test / Change the WE text of the Dump Info menucommand
	 *		@snippet DG_Test.cpp MenuItem-SetWorkEnvironmentText-Example
	 */
	void			SetWorkEnvironmentText (const GS::UniString& text);

	/**
	 * @brief The flags of the menu item command.
	 * @return The flags of the menu item command.
	 */
	GSFlags			GetFlags () const;

	/**
	 * @brief Changes the flags of the menu item command.
	 * @param flags The desired flags of the menu item command.
	 */
	void			SetFlags (const GSFlags flags);

	/**
	 * @brief The shortcuts of the menu item command.
	 * @return The shortcuts of the menu item command.
	 */
	std::vector<GS::UniString> GetShortcuts () const;

private:
	explicit MenuItem (std::shared_ptr<Impl::MenuItemImpl> impl);
};

} //namespace ACAPI::UI::Menu

#endif //GS_ACAPIUIMENU_MENUITEM_HPP
