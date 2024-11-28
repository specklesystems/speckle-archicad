#ifndef GS_ACAPI_MEP_ROUTING_NODE_UI_MANAGER_HPP
#define GS_ACAPI_MEP_ROUTING_NODE_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class IRoutingNodeUIManagerImpl; }

namespace v1 {

class RoutingNodeDefault;


/**
 * @brief The RoutingNodeUIManager contains UI-related services for a RoutingNode.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT RoutingNodeUIManager final : public ACAPI::Object {
	RoutingNodeUIManager (std::shared_ptr<Impl::IRoutingNodeUIManagerImpl>);
	static Result<RoutingNodeUIManager> Create (const API_Token&);

public:
	friend Result<RoutingNodeUIManager> CreateRoutingNodeUIManager ();

	/**
	 * @brief Creates a RoutingNodeDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the RoutingNode in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an RoutingNodeDefault, otherwise returns the RoutingNodeDefault created from it.
	 */
	Result<RoutingNodeDefault>	CreateRoutingNodeDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param routingNodeDefault The default to be set
	 * @return Returns error if the RoutingNodeDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>		ApplyRoutingNodeDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const RoutingNodeDefault& routingNodeDefault);
};


/**
 * @brief Creates a RoutingNodeUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for RoutingNode, otherwise Error.
 */
inline Result<RoutingNodeUIManager> CreateRoutingNodeUIManager ()
{
	return RoutingNodeUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::RoutingNodeUIManager;
using v1::CreateRoutingNodeUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_ROUTING_NODE_UI_MANAGER_HPP*/