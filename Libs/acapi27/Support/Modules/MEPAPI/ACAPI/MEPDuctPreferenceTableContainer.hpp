#ifndef GS_ACAPI_MEP_DUCT_PREFERENCE_TABLE_CONTAINER_HPP
#define GS_ACAPI_MEP_DUCT_PREFERENCE_TABLE_CONTAINER_HPP

#include "MEPAPIExport.hpp"
#include "MEPPreferenceTableContainerBase.hpp"


namespace ACAPI::MEP {

inline namespace v1 {

/** @brief The DuctPreferenceTableContainer can contain several PreferenceTableBase associated with ventilation.
	@ingroup MEP
	@since Archicad 27
	@ingroup MEP
	@details The container is already initialized (but may be empty) and you can access it by calling GetDuctPreferenceContainer.
	@par Example code snippet from Test / New MEP
		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
*/
class MEPAPI_EXPORT DuctPreferenceTableContainer final : public PreferenceTableContainerBase {
	DuctPreferenceTableContainer (const API_Token&);
	static Result<DuctPreferenceTableContainer> Get (const API_Token&);

public:
	class Modifier;
	friend Result<DuctPreferenceTableContainer> GetDuctPreferenceTableContainer ();
};


/**	@ingroup MEP
	@return If able, returns the DuctPreferenceTableContainer from the project.
*/
inline Result<DuctPreferenceTableContainer> GetDuctPreferenceTableContainer ()
{
	return DuctPreferenceTableContainer::Get (ACAPI_GetToken ());
}


} // v1

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_DUCT_PREFERENCE_TABLE_CONTAINER_HPP