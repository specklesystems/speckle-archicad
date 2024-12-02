#ifndef GS_ACAPI_MEP_PIPE_SEGMENT_PREFERENCE_TABLE_CONTAINER_HPP
#define GS_ACAPI_MEP_PIPE_SEGMENT_PREFERENCE_TABLE_CONTAINER_HPP

#include "MEPAPIExport.hpp"
#include "MEPPreferenceTableContainerBase.hpp"


namespace ACAPI::MEP {

namespace v1 {

/**
 * @brief The PipeSegmentPreferenceTableContainer can contain several PreferenceTableBase associated with piping.
 * @ingroup MEP
 * @since Archicad 27
 * @ingroup MEP
 * @details The container is already initialized (but may be empty) and you can access it by calling GetPipeSegmentPreferenceContainer.
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
 */
class MEPAPI_EXPORT PipeSegmentPreferenceTableContainer final : public PreferenceTableContainerBase {
	PipeSegmentPreferenceTableContainer (const API_Token&);
	static Result<PipeSegmentPreferenceTableContainer> Get (const API_Token&);

public:
	class Modifier;
	friend Result<PipeSegmentPreferenceTableContainer> GetPipeSegmentPreferenceTableContainer ();
};


/**
 * @ingroup MEP
 * @return If able, returns the PipePreferenceTableContainer from the project.
 */
inline Result<PipeSegmentPreferenceTableContainer> GetPipeSegmentPreferenceTableContainer ()
{
	return PipeSegmentPreferenceTableContainer::Get (ACAPI_GetToken ());
}


} // v1

using v1::PipeSegmentPreferenceTableContainer;
using v1::GetPipeSegmentPreferenceTableContainer;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_PIPE_SEGMENT_PREFERENCE_TABLE_CONTAINER_HPP