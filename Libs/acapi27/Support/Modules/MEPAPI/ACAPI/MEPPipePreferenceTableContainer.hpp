#ifndef GS_ACAPI_MEP_PIPE_PREFERENCE_TABLE_CONTAINER_HPP
#define GS_ACAPI_MEP_PIPE_PREFERENCE_TABLE_CONTAINER_HPP

#include "MEPAPIExport.hpp"
#include "MEPPreferenceTableContainerBase.hpp"


namespace ACAPI::MEP {

inline namespace v1 {

/** @brief The PipePreferenceTableContainer can contain several PreferenceTableBase associated with piping.
	@ingroup MEP
	@since Archicad 27
	@ingroup MEP
	@details The container is already initialized (but may be empty) and you can access it by calling GetPipePreferenceContainer.
	@par Example code snippet from Test / New MEP
		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
*/
class MEPAPI_EXPORT PipePreferenceTableContainer final : public PreferenceTableContainerBase {
	PipePreferenceTableContainer (const API_Token&);
	static Result<PipePreferenceTableContainer> Get (const API_Token&);

public:
	class Modifier;
	friend Result<PipePreferenceTableContainer> GetPipePreferenceTableContainer ();
};


/** @ingroup MEP
	@return If able, returns the PipePreferenceTableContainer from the project.
*/
inline Result<PipePreferenceTableContainer> GetPipePreferenceTableContainer ()
{
	return PipePreferenceTableContainer::Get (ACAPI_GetToken ());
}


} // v1

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_PIPE_PREFERENCE_TABLE_CONTAINER_HPP