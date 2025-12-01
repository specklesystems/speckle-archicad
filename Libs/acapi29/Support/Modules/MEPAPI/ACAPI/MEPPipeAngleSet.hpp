#ifndef GS_ACAPI_MEP_PIPE_ANGLE_SET_HPP
#define GS_ACAPI_MEP_PIPE_ANGLE_SET_HPP

#include "MEPAPIExport.hpp"
#include "MEPAngleSetBase.hpp"


namespace ACAPI::MEP {

/**
 * @brief The PipeAngleSet contains angles that are used in PipeElbowPreferenceTable and PipeBranchPreferenceTable.
 * @since Archicad 29
 * @ingroup MEP
 * @details The container is already initialized and you can access it by calling GetPipeAngleSet.
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref AngleSetBase
 */
class MEPAPI_EXPORT PipeAngleSet final : public AngleSetBase {
	PipeAngleSet (const API_Token&);
	static Result<PipeAngleSet> Get (const API_Token&);

public:
	class Modifier;
	friend Result<PipeAngleSet> GetPipeAngleSet ();
};


/**
 * @ingroup MEP
 * @return If able, returns the PipeAngleSet from the project.
 */
inline Result<PipeAngleSet> GetPipeAngleSet ()
{
	return PipeAngleSet::Get (ACAPI_GetToken ());
}


} // ACAPI::MEP


#endif // GS_ACAPI_MEP_PIPE_ANGLE_SET_HPP