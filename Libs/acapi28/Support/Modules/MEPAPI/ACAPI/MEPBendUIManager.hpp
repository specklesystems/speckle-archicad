#ifndef GS_ACAPI_MEP_BEND_UI_MANAGER_HPP
#define GS_ACAPI_MEP_BEND_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class IBendUIManagerImpl; }

namespace v1 {

class BendDefault;


/**
 * @brief The BendUIManager contains UI-related services for a Bend.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT BendUIManager final : public ACAPI::Object {
	BendUIManager (std::shared_ptr<Impl::IBendUIManagerImpl>);
	static Result<BendUIManager> Create (const API_Token&);

public:
	friend Result<BendUIManager> CreateBendUIManager ();

	/**
	 * @brief Creates a BendDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the Bend in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an BendDefault, otherwise returns the BendDefault created from it.
	 */
	Result<BendDefault>	CreateBendDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param bendDefault The default to be set
	 * @return Returns error if the BendDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>	ApplyBendDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const BendDefault& bendDefault);
};


/**
 * @brief Creates a BendUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for Bend, otherwise Error.
 */
inline Result<BendUIManager> CreateBendUIManager ()
{
	return BendUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::BendUIManager;
using v1::CreateBendUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_BEND_UI_MANAGER_HPP*/