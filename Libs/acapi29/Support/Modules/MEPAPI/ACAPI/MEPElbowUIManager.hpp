#ifndef GS_ACAPI_MEP_ELBOW_UI_MANAGER_HPP
#define GS_ACAPI_MEP_ELBOW_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class IElbowUIManagerImpl; }

class ElbowDefault;


/**
 * @brief The ElbowUIManager contains UI-related services for an Elbow.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElbowUIManager final : public ACAPI::Object {
	ElbowUIManager (std::shared_ptr<Impl::IElbowUIManagerImpl>);
	static Result<ElbowUIManager> Create (const API_Token&);

public:
	friend Result<ElbowUIManager> CreateElbowUIManager ();

	/**
	 * @brief Creates an ElbowDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the Elbow in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an ElbowDefault, otherwise returns the ElbowDefault created from it.
	 */
	Result<ElbowDefault>	CreateElbowDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param elbowDefault The default to be set
	 * @return Returns error if the ElbowDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>	ApplyElbowDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const ElbowDefault& elbowDefault);
};


/**
 * @brief Creates an ElbowUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for Elbow, otherwise Error.
 */
inline Result<ElbowUIManager> CreateElbowUIManager ()
{
	return ElbowUIManager::Create (ACAPI_GetToken ());
}


} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_ELBOW_UI_MANAGER_HPP*/