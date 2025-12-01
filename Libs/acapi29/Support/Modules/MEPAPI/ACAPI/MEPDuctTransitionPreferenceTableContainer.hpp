#ifndef GS_ACAPI_MEP_DUCT_TRANSITION_PREFERENCE_TABLE_CONTAINER_HPP
#define GS_ACAPI_MEP_DUCT_TRANSITION_PREFERENCE_TABLE_CONTAINER_HPP

#include "MEPAPIExport.hpp"
#include "MEPPreferenceTableContainerBase.hpp"


namespace ACAPI::MEP {

/** @brief The DuctTransitionPreferenceTableContainer can contain several DuctTransitionPreferenceTables.
	@ingroup MEP
	@since Archicad 29
	@details The container is already initialized (but may be empty) and you can access it by calling GetDuctTransitionPreferenceTableContainer.
	@par Example code snippet from Test / New MEP
		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
*/
class MEPAPI_EXPORT DuctTransitionPreferenceTableContainer final : public PreferenceTableContainerBase {

	DuctTransitionPreferenceTableContainer (const API_Token&);
	static Result<DuctTransitionPreferenceTableContainer> Get (const API_Token&);

public:
	class Modifier;
	friend Result<DuctTransitionPreferenceTableContainer> GetDuctTransitionPreferenceTableContainer ();
};


/** @ingroup MEP
	@return If able, returns the DuctTransitionPreferenceTableContainer from the project.
*/
inline Result<DuctTransitionPreferenceTableContainer> GetDuctTransitionPreferenceTableContainer ()
{
	return DuctTransitionPreferenceTableContainer::Get (ACAPI_GetToken ());
}

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_DUCT_TRANSITION_PREFERENCE_TABLE_CONTAINER_HPP