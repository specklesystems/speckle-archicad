#ifndef GS_ACAPI_MEP_PIPE_ELBOW_PREFERENCE_TABLE_CONTAINER_HPP
#define GS_ACAPI_MEP_PIPE_ELBOW_PREFERENCE_TABLE_CONTAINER_HPP

#include "MEPAPIExport.hpp"
#include "MEPPreferenceTableContainerBase.hpp"


namespace ACAPI::MEP {

namespace v1 {

/**
 * @brief The PipeElbowPreferenceTableContainer can contain several PipeElbowPreferenceTables.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 * @details The container is already initialized (but may be empty) and you can access it by calling GetPipeElbowPreferenceTableContainer.
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
 */
class MEPAPI_EXPORT PipeElbowPreferenceTableContainer final : public PreferenceTableContainerBase {

	PipeElbowPreferenceTableContainer (const API_Token&);
	static Result<PipeElbowPreferenceTableContainer> Get (const API_Token&);

public:
	class Modifier;
	friend Result<PipeElbowPreferenceTableContainer> GetPipeElbowPreferenceTableContainer ();
};


/**
 * @ingroup MEP
 * @return If able, returns the PipeElbowPreferenceTableContainer from the project.
 */
inline Result<PipeElbowPreferenceTableContainer> GetPipeElbowPreferenceTableContainer ()
{
	return PipeElbowPreferenceTableContainer::Get (ACAPI_GetToken ());
}


} // v1

using v1::PipeElbowPreferenceTableContainer;
using v1::GetPipeElbowPreferenceTableContainer;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_PIPE_PREFERENCE_TABLE_CONTAINER_HPP