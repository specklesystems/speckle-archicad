#ifndef GS_ACAPI_MEP_PIPE_TRANSITION_PREFERENCE_TABLE_CONTAINER_HPP
#define GS_ACAPI_MEP_PIPE_TRANSITION_PREFERENCE_TABLE_CONTAINER_HPP

#include "MEPAPIExport.hpp"
#include "MEPPreferenceTableContainerBase.hpp"


namespace ACAPI::MEP {

/** @brief The PipeTransitionPreferenceTableContainer can contain several PipeTransitionPreferenceTables.
	@ingroup MEP
	@since Archicad 29
	@ingroup MEP
	@details The container is already initialized (but may be empty) and you can access it by calling GetPipeTransitionPreferenceTableContainer.
	@par Example code snippet from Test / New MEP
		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
*/
class MEPAPI_EXPORT PipeTransitionPreferenceTableContainer final : public PreferenceTableContainerBase {

	PipeTransitionPreferenceTableContainer (const API_Token&);
	static Result<PipeTransitionPreferenceTableContainer> Get (const API_Token&);

public:
	class Modifier;
	friend Result<PipeTransitionPreferenceTableContainer> GetPipeTransitionPreferenceTableContainer ();
};


/** @ingroup MEP
	@return If able, returns the PipeTransitionPreferenceTableContainer from the project.
*/
inline Result<PipeTransitionPreferenceTableContainer> GetPipeTransitionPreferenceTableContainer ()
{
	return PipeTransitionPreferenceTableContainer::Get (ACAPI_GetToken ());
}


} // ACAPI::MEP


#endif // GS_ACAPI_MEP_PIPE_TRANSITION_PREFERENCE_TABLE_CONTAINER_HPP