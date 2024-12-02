#ifndef GS_ACAPI_MEP_ROUTING_SEGMENT_UI_MANAGER_HPP
#define GS_ACAPI_MEP_ROUTING_SEGMENT_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class IRoutingSegmentUIManagerImpl; }

namespace v1 {

class RoutingSegmentDefault;


/**
 * @brief The RoutingSegmentUIManager contains UI-related services for a RoutingSegment.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT RoutingSegmentUIManager final : public ACAPI::Object {
	RoutingSegmentUIManager (std::shared_ptr<Impl::IRoutingSegmentUIManagerImpl>);
	static Result<RoutingSegmentUIManager> Create (const API_Token&);

public:
	friend Result<RoutingSegmentUIManager> CreateRoutingSegmentUIManager ();

	/**
	 * @brief Creates a RoutingSegmentDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the RoutingSegment in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an RoutingSegmentDefault, otherwise returns the RoutingSegmentDefault created from it.
	 */
	Result<RoutingSegmentDefault> CreateRoutingSegmentDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param routingSegmentDefault The default to be set
	 * @return Returns error if the RoutingSegmentDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>			ApplyRoutingSegmentDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const RoutingSegmentDefault& routingSegmentDefault);
};


/**
 * @brief Creates a RoutingSegmentUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for RoutingSegment, otherwise Error.
 */
inline Result<RoutingSegmentUIManager> CreateRoutingSegmentUIManager ()
{
	return RoutingSegmentUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::RoutingSegmentUIManager;
using v1::CreateRoutingSegmentUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_ROUTING_SEGMENT_UI_MANAGER_HPP*/