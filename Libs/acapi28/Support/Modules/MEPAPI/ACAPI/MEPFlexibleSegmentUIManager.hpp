#ifndef GS_ACAPI_MEP_FLEXIBLE_SEGMENT_UI_MANAGER_HPP
#define GS_ACAPI_MEP_FLEXIBLE_SEGMENT_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class IFlexibleSegmentUIManagerImpl; }

namespace v1 {

class FlexibleSegmentDefault;


/**
 * @brief The FlexibleSegmentUIManager contains UI-related services for a FlexibleSegment.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT FlexibleSegmentUIManager final : public ACAPI::Object {
	FlexibleSegmentUIManager (std::shared_ptr<Impl::IFlexibleSegmentUIManagerImpl>);
	static Result<FlexibleSegmentUIManager> Create (const API_Token&);

public:
	friend Result<FlexibleSegmentUIManager> CreateFlexibleSegmentUIManager ();

	/**
	 * @brief Creates a FlexibleSegmentDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the FlexibleSegment in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an FlexibleSegmentDefault, otherwise returns the FlexibleSegmentDefault created from it.
	 */
	Result<FlexibleSegmentDefault> CreateFlexibleSegmentDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param flexibleSegmentDefault The default to be set
	 * @return Returns error if the FlexibleSegmentDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>			ApplyFlexibleSegmentDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const FlexibleSegmentDefault& flexibleSegmentDefault);
};


/**
 * @brief Creates a FlexibleSegmentUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for FlexibleSegment, otherwise Error.
 */
inline Result<FlexibleSegmentUIManager> CreateFlexibleSegmentUIManager ()
{
	return FlexibleSegmentUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::FlexibleSegmentUIManager;
using v1::CreateFlexibleSegmentUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_FLEXIBLE_SEGMENT_UI_MANAGER_HPP*/