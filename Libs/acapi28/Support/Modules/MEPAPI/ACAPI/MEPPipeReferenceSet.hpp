#ifndef GS_ACAPI_MEP_PIPE_REFERENCE_SET_HPP
#define GS_ACAPI_MEP_PIPE_REFERENCE_SET_HPP

#include "MEPAPIExport.hpp"
#include "MEPReferenceSetBase.hpp"


namespace ACAPI::MEP {

namespace v1 {

/**
 * @brief The PipeReferenceSet contains referenceIds that are used in PipeSegmentPreferenceTable and PipeElbowPreferenceTable.
 * @since Archicad 28
 * @ingroup MEP
 * @details The container is already initialized and you can access it by calling GetPipeReferenceSet.
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref ReferenceSetBase
 */
class MEPAPI_EXPORT PipeReferenceSet final : public ReferenceSetBase {
	PipeReferenceSet (const API_Token&);
	static Result<PipeReferenceSet> Get (const API_Token&);

public:
	class Modifier;
	friend Result<PipeReferenceSet> GetPipeReferenceSet ();
};


/**
 * @ingroup MEP
 * @return If able, returns the PipeReferenceSet from the project.
 */
inline Result<PipeReferenceSet> GetPipeReferenceSet ()
{
	return PipeReferenceSet::Get (ACAPI_GetToken ());
}


} // v1

using v1::PipeReferenceSet;
using v1::GetPipeReferenceSet;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_PIPE_REFERENCE_SET_HPP