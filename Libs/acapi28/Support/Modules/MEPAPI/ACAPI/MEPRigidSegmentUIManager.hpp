#ifndef GS_ACAPI_MEP_RIGID_SEGMENT_UI_MANAGER_HPP
#define GS_ACAPI_MEP_RIGID_SEGMENT_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class IRigidSegmentUIManagerImpl; }

namespace v1 {

class RigidSegmentDefault;


/**
 * @brief The RigidSegmentUIManager contains UI-related services for a RigidSegment.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT RigidSegmentUIManager final : public ACAPI::Object {
	RigidSegmentUIManager (std::shared_ptr<Impl::IRigidSegmentUIManagerImpl>);
	static Result<RigidSegmentUIManager> Create (const API_Token&);

public:
	friend Result<RigidSegmentUIManager> CreateRigidSegmentUIManager ();

	/**
	 * @brief Creates a RigidSegmentDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the RigidSegment in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an RigidSegmentDefault, otherwise returns the RigidSegmentDefault created from it.
	 */
	Result<RigidSegmentDefault> CreateRigidSegmentDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param rigidSegmentDefault The default to be set
	 * @return Returns error if the RigidSegmentDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>		ApplyRigidSegmentDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const RigidSegmentDefault& rigidSegmentDefault);
};


/**
 * @brief Creates a RigidSegmentUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for RigidSegment, otherwise Error.
 */
inline Result<RigidSegmentUIManager> CreateRigidSegmentUIManager ()
{
	return RigidSegmentUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::RigidSegmentUIManager;
using v1::CreateRigidSegmentUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_RIGID_SEGMENT_UI_MANAGER_HPP*/