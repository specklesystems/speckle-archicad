#ifndef GS_ACAPI_MEP_FITTING_UI_MANAGER_HPP
#define GS_ACAPI_MEP_FITTING_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class IFittingUIManagerImpl; }

namespace v1 {

class FittingDefault;


/**
 * @brief The FittingUIManager contains UI-related services for a Fitting.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT FittingUIManager final : public ACAPI::Object {
	FittingUIManager (std::shared_ptr<Impl::IFittingUIManagerImpl>);
	static Result<FittingUIManager> Create (const API_Token&);

public:
	friend Result<FittingUIManager> CreateFittingUIManager ();

	/**
	 * @brief Creates a FittingDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the Fitting in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an FittingDefault, otherwise returns the FittingDefault created from it.
	 */
	Result<FittingDefault> CreateFittingDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param fittingDefault The default to be set
	 * @return Returns error if the FittingDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>	ApplyFittingDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const FittingDefault& fittingDefault);
};


/**
 * @brief Creates a FittingUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for Fitting, otherwise Error.
 */
inline Result<FittingUIManager> CreateFittingUIManager ()
{
	return FittingUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::FittingUIManager;
using v1::CreateFittingUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_FITTING_UI_MANAGER_HPP*/