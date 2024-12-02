#ifndef GS_ACAPI_MEP_TRANSITION_UI_MANAGER_HPP
#define GS_ACAPI_MEP_TRANSITION_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class ITransitionUIManagerImpl; }

namespace v1 {

class TransitionDefault;


/**
 * @brief The TransitionUIManager contains UI-related services for a Transition.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT TransitionUIManager final : public ACAPI::Object {
	TransitionUIManager (std::shared_ptr<Impl::ITransitionUIManagerImpl>);
	static Result<TransitionUIManager> Create (const API_Token&);

public:
	friend Result<TransitionUIManager> CreateTransitionUIManager ();

	/**
	 * @brief Creates a TransitionDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the Transition in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an TransitionDefault, otherwise returns the TransitionDefault created from it.
	 */
	Result<TransitionDefault> CreateTransitionDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param transitionDefault The default to be set
	 * @return Returns error if the TransitionDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>		ApplyTransitionDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const TransitionDefault& transitionDefault);
};


/**
 * @brief Creates a TransitionUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for Transitions, otherwise Error.
 */
inline Result<TransitionUIManager> CreateTransitionUIManager ()
{
	return TransitionUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::TransitionUIManager;
using v1::CreateTransitionUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_TRANSITION_UI_MANAGER_HPP*/