#ifndef GS_ACAPI_MEP_DUCT_ELBOW_PREFERENCE_TABLE_CONTAINER_HPP
#define GS_ACAPI_MEP_DUCT_ELBOW_PREFERENCE_TABLE_CONTAINER_HPP

#include "MEPAPIExport.hpp"
#include "MEPPreferenceTableContainerBase.hpp"


namespace ACAPI::MEP {

namespace v1 {

/**
 * @brief The DuctElbowPreferenceTableContainer can contain several DuctElbowPreferenceTables.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 * @details The container is already initialized (but may be empty) and you can access it by calling GetDuctElbowPreferenceTableContainer.
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
 */
class MEPAPI_EXPORT DuctElbowPreferenceTableContainer final : public PreferenceTableContainerBase {

	DuctElbowPreferenceTableContainer (const API_Token&);
	static Result<DuctElbowPreferenceTableContainer> Get (const API_Token&);

public:
	class Modifier;
	friend Result<DuctElbowPreferenceTableContainer> GetDuctElbowPreferenceTableContainer ();
};


/**
 * @ingroup MEP
 * @return If able, returns the DuctElbowPreferenceTableContainer from the project.
 */
inline Result<DuctElbowPreferenceTableContainer> GetDuctElbowPreferenceTableContainer ()
{
	return DuctElbowPreferenceTableContainer::Get (ACAPI_GetToken ());
}


} // v1

using v1::DuctElbowPreferenceTableContainer;
using v1::GetDuctElbowPreferenceTableContainer;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_DUCT_PREFERENCE_TABLE_CONTAINER_HPP