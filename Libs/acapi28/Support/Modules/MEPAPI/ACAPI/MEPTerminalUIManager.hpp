#ifndef GS_ACAPI_MEP_TERMINAL_UI_MANAGER_HPP
#define GS_ACAPI_MEP_TERMINAL_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class ITerminalUIManagerImpl; }

namespace v1 {

class TerminalDefault;


/**
 * @brief The TerminalUIManager contains UI-related services for a Terminal.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT TerminalUIManager final : public ACAPI::Object {
	TerminalUIManager (std::shared_ptr<Impl::ITerminalUIManagerImpl>);
	static Result<TerminalUIManager> Create (const API_Token&);

public:
	friend Result<TerminalUIManager> CreateTerminalUIManager ();

	/**
	 * @brief Creates a TerminalDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the Terminal in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an TerminalDefault, otherwise returns the TerminalDefault created from it.
	 */
	Result<TerminalDefault> CreateTerminalDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param terminalDefault The default to be set
	 * @return Returns error if the TerminalDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>	ApplyTerminalDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const TerminalDefault& terminalDefault);
};


/**
 * @brief Creates a TerminalUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for Terminal, otherwise Error.
 */
inline Result<TerminalUIManager> CreateTerminalUIManager ()
{
	return TerminalUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::TerminalUIManager;
using v1::CreateTerminalUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_TERMINAL_UI_MANAGER_HPP*/