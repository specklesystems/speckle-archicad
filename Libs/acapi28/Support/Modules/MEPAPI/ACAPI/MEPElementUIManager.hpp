#ifndef GS_ACAPI_MEP_ELEMENT_UI_MANAGER_HPP
#define GS_ACAPI_MEP_ELEMENT_UI_MANAGER_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"

#include "ACAPI/Result.hpp"


namespace TBUI { class IAPIToolUIData; }

namespace ACAPI::MEP {

namespace Impl { class IElementUIManagerImpl; }

namespace v1 {

class ElementDefault;


/**
 * @brief The ElementUIManager contains UI-related services for an Element.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElementUIManager final : public ACAPI::Object {
	ElementUIManager (std::shared_ptr<Impl::IElementUIManagerImpl>);
	static Result<ElementUIManager> Create (const API_Token&);

public:
	friend Result<ElementUIManager> CreateElementUIManager ();

	/**
	 * @brief Creates a ElementDefault from a toolUIData
	 * @param toolUIData The data which contains the temporary state of the Element in the scope of a Settings Dialog.
	 * @return Returns error if the given Default from the IAPIToolUIData is not an ElementDefault, otherwise returns the ElementDefault created from it.
	 */
	Result<ElementDefault> CreateElementDefaultFromToolUIData (const TBUI::IAPIToolUIData& toolUIData);

	/**
	 * @brief Changes the default elem in the given toolUIData
	 * @param toolUIData The data in which the default elem will be changed
	 * @param elementDefault The default to be set
	 * @return Returns error if the ElementDefault is not the same type as the Default in IAPIToolUIData, or if they mismatch in their MEP Domain, otherwise nothing.
	 */
	Result<void>	ApplyElementDefaultToToolUIData (TBUI::IAPIToolUIData& toolUIData, const ElementDefault& elementDefault);
};


/**
 * @brief Creates a ElementUIManager
 * @ingroup MEP
 * @return If able, creates a new manager for Element, otherwise Error.
 */
inline Result<ElementUIManager> CreateElementUIManager ()
{
	return ElementUIManager::Create (ACAPI_GetToken ());
}


} // v1

using v1::ElementUIManager;
using v1::CreateElementUIManager;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_ELEMENT_UI_MANAGER_HPP*/