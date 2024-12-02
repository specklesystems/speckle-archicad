#ifndef GS_ACAPI_MEP_BANCH_UI_MANAGER_HPP
#define GS_ACAPI_MEP_BANCH_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class IBranchUIManagerImpl; }

namespace v1 {

class BranchDefault;


/**
 * @brief The BranchUIManager contains UI-related services for a Branch.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT BranchUIManager final : public ACAPI::Object {
	BranchUIManager (std::shared_ptr<Impl::IBranchUIManagerImpl>);
	static Result<BranchUIManager> Create (const API_Token&);

public:
	friend Result<BranchUIManager> CreateBranchUIManager ();

	/**
	 * @brief Creates a BranchDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the Branch in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an BranchDefault, otherwise returns the BranchDefault created from it.
	 */
	Result<BranchDefault> CreateBranchDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);
	
	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param branchDefault The default to be set
	 * @return Returns error if the BranchDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>	ApplyBranchDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const BranchDefault& branchDefault);
};


/**
 * @brief Creates a BranchUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for Branch, otherwise Error.
 */
inline Result<BranchUIManager> CreateBranchUIManager ()
{
	return BranchUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::BranchUIManager;
using v1::CreateBranchUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_BANCH_UI_MANAGER_HPP*/