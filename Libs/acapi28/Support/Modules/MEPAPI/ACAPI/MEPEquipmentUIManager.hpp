#ifndef GS_ACAPI_MEP_EQUIPMENT_UI_MANAGER_HPP
#define GS_ACAPI_MEP_EQUIPMENT_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class IEquipmentUIManagerImpl; }

namespace v1 {

class EquipmentDefault;


/**
 * @brief The EquipmentUIManager contains UI-related services for an Equipment .
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT EquipmentUIManager final : public ACAPI::Object {
	EquipmentUIManager (std::shared_ptr<Impl::IEquipmentUIManagerImpl>);
	static Result<EquipmentUIManager> Create (const API_Token&);

public:
	friend Result<EquipmentUIManager> CreateEquipmentUIManager ();

	/**
	 * @brief Creates a EquipmentDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the Equipment  in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an EquipmentDefault, otherwise returns the EquipmentDefault created from it.
	 */
	Result<EquipmentDefault> CreateEquipmentDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param equipmentDefault The default to be set
	 * @return Returns error if the EquipmentDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>	 ApplyEquipmentDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const EquipmentDefault& equipmentDefault);
};


/**
 * @brief Creates a EquipmentUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for Equipment, otherwise Error.
 */
inline Result<EquipmentUIManager> CreateEquipmentUIManager ()
{
	return EquipmentUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::EquipmentUIManager;
using v1::CreateEquipmentUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_EQUIPMENT_UI_MANAGER_HPP*/