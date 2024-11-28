#ifndef GS_ACAPI_MEP_ROUTING_ELEMENT_UI_MANAGER_HPP
#define GS_ACAPI_MEP_ROUTING_ELEMENT_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class IRoutingElementUIManagerImpl; }

namespace v1 {

class RoutingElementDefault;

/**
 * @brief The RoutingElementUIManager contains UI-related services for a Routing element.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT RoutingElementUIManager final : public ACAPI::Object {
	RoutingElementUIManager (std::shared_ptr<Impl::IRoutingElementUIManagerImpl> impl);
	static Result<RoutingElementUIManager> Create (const API_Token& token);

public:
	friend Result<RoutingElementUIManager> CreateRoutingElementUIManager ();

	/**
	 * @brief Creates a RoutingElementDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the RoutingElement in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an RoutingElementDefault, otherwise returns the RoutingElementDefault created from it.
	 */
	Result<RoutingElementDefault> CreateRoutingElementDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param routingElementDefault The default to be set
	 * @return Returns error if the RoutingElementDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>	ApplyRoutingElementDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const RoutingElementDefault& routingElementDefault);
};


/**
 * @brief Creates a RoutingElementUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for RoutingElement, otherwise Error.
 */
inline Result<RoutingElementUIManager> CreateRoutingElementUIManager ()
{
	return RoutingElementUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::RoutingElementUIManager;
using v1::CreateRoutingElementUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_ROUTING_ELEMENT_UI_MANAGER_HPP*/