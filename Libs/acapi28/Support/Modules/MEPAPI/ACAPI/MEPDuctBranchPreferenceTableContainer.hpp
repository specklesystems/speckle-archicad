#ifndef GS_ACAPI_MEP_DUCT_BRANCH_PREFERENCE_TABLE_CONTAINER_HPP
#define GS_ACAPI_MEP_DUCT_BRANCH_PREFERENCE_TABLE_CONTAINER_HPP

#include "MEPAPIExport.hpp"
#include "MEPPreferenceTableContainerBase.hpp"


namespace ACAPI::MEP {

namespace v1 {

/** @brief The DuctBranchPreferenceTableContainer can contain several DuctBranchPreferenceTables.
	@ingroup MEP
	@since Archicad 28
	@ingroup MEP
	@details The container is already initialized (but may be empty) and you can access it by calling GetDuctBranchPreferenceTableContainer.
	@par Example code snippet from Test / New MEP
		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
*/
class MEPAPI_EXPORT DuctBranchPreferenceTableContainer final : public PreferenceTableContainerBase {

	DuctBranchPreferenceTableContainer (const API_Token&);
	static Result<DuctBranchPreferenceTableContainer> Get (const API_Token&);

public:
	class Modifier;
	friend Result<DuctBranchPreferenceTableContainer> GetDuctBranchPreferenceTableContainer ();
};


/** @ingroup MEP
	@return If able, returns the DuctBranchPreferenceTableContainer from the project.
*/
inline Result<DuctBranchPreferenceTableContainer> GetDuctBranchPreferenceTableContainer ()
{
	return DuctBranchPreferenceTableContainer::Get (ACAPI_GetToken ());
}


} // v1

using v1::DuctBranchPreferenceTableContainer;
using v1::GetDuctBranchPreferenceTableContainer;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_DUCT_BRANCH_PREFERENCE_TABLE_CONTAINER_HPP