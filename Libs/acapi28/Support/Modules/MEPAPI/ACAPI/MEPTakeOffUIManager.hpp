#ifndef GS_ACAPI_MEP_TAKE_OFF_UI_MANAGER_HPP
#define GS_ACAPI_MEP_TAKE_OFF_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class ITakeOffUIManagerImpl; }

namespace v1 {

class TakeOffDefault;


/**
 * @brief The TakeOffUIManager contains UI-related services for an TakeOff.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT TakeOffUIManager final : public ACAPI::Object {
	TakeOffUIManager (std::shared_ptr<Impl::ITakeOffUIManagerImpl>);
	static Result<TakeOffUIManager> Create (const API_Token&);

public:
	friend Result<TakeOffUIManager> CreateTakeOffUIManager ();

	/**
	 * @brief Creates a TakeOffDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the TakeOff in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an TakeOffDefault, otherwise returns the TakeOffDefault created from it.
	 */
	Result<TakeOffDefault> CreateTakeOffDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param TakeOffDefault The default to be set
	 * @return Returns error if the TakeOffDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>	 ApplyTakeOffDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const TakeOffDefault& TakeOffDefault);
};


/**
 * @brief Creates a TakeOffUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for TakeOff, otherwise Error.
 */
inline Result<TakeOffUIManager> CreateTakeOffUIManager ()
{
	return TakeOffUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::TakeOffUIManager;
using v1::CreateTakeOffUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_TAKE_OFF_UI_MANAGER_HPP*/