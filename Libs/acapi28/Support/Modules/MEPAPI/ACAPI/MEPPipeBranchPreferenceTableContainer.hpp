#ifndef GS_ACAPI_MEP_PIPE_BRANCH_PREFERENCE_TABLE_CONTAINER_HPP
#define GS_ACAPI_MEP_PIPE_BRANCH_PREFERENCE_TABLE_CONTAINER_HPP

#include "MEPAPIExport.hpp"
#include "MEPPreferenceTableContainerBase.hpp"


namespace ACAPI::MEP {

namespace v1 {

/** @brief The PipeBranchPreferenceTableContainer can contain several PipeBranchPreferenceTables.
	@ingroup MEP
	@since Archicad 28
	@ingroup MEP
	@details The container is already initialized (but may be empty) and you can access it by calling GetPipeBranchPreferenceTableContainer.
	@par Example code snippet from Test / New MEP
		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
*/
class MEPAPI_EXPORT PipeBranchPreferenceTableContainer final : public PreferenceTableContainerBase {

	PipeBranchPreferenceTableContainer (const API_Token&);
	static Result<PipeBranchPreferenceTableContainer> Get (const API_Token&);

public:
	class Modifier;
	friend Result<PipeBranchPreferenceTableContainer> GetPipeBranchPreferenceTableContainer ();
};


/** @ingroup MEP
	@return If able, returns the PipeBranchPreferenceTableContainer from the project.
*/
inline Result<PipeBranchPreferenceTableContainer> GetPipeBranchPreferenceTableContainer ()
{
	return PipeBranchPreferenceTableContainer::Get (ACAPI_GetToken ());
}


} // v1

using v1::PipeBranchPreferenceTableContainer;
using v1::GetPipeBranchPreferenceTableContainer;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_PIPE_BRANCH_PREFERENCE_TABLE_CONTAINER_HPP