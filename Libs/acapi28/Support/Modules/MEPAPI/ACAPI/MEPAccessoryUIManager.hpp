#ifndef GS_ACAPI_MEP_ACCESSORY_UI_MANAGER_HPP
#define GS_ACAPI_MEP_ACCESSORY_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class IAccessoryUIManagerImpl; }

namespace v1 {

class AccessoryDefault;


/**
 * @brief The AccessoryUIManager contains UI-related services for an Accessory.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT AccessoryUIManager final : public ACAPI::Object {
	AccessoryUIManager (std::shared_ptr<Impl::IAccessoryUIManagerImpl>);
	static Result<AccessoryUIManager> Create (const API_Token&);

public:
	friend Result<AccessoryUIManager> CreateAccessoryUIManager ();

	/**
	 * @brief Creates a AccessoryDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the Accessory in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an AccessoryDefault, otherwise returns the AccessoryDefault created from it.
	 */
	Result<AccessoryDefault> CreateAccessoryDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param accessoryDefault The default to be set
	 * @return Returns error if the AccessoryDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>	 ApplyAccessoryDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const AccessoryDefault& accessoryDefault);
};


/**
 * @brief Creates a AccessoryUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for Accessory, otherwise Error.
 */
inline Result<AccessoryUIManager> CreateAccessoryUIManager ()
{
	return AccessoryUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::AccessoryUIManager;
using v1::CreateAccessoryUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_ACCESSORY_UI_MANAGER_HPP*/