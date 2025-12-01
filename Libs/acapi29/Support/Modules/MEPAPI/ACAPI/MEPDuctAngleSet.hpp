#ifndef GS_ACAPI_MEP_DUCT_ANGLE_SET_HPP
#define GS_ACAPI_MEP_DUCT_ANGLE_SET_HPP

#include "MEPAPIExport.hpp"
#include "MEPAngleSetBase.hpp"


namespace ACAPI::MEP {

/**
 * @brief The DuctAngleSet contains angles that are used in DuctElbowPreferenceTable and DuctBranchPreferenceTable.
 * @since Archicad 29
 * @ingroup MEP
 * @details The container is already initialized and you can access it by calling GetDuctAngleSet.
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref AngleSetBase
 */
class MEPAPI_EXPORT DuctAngleSet final : public AngleSetBase {
	DuctAngleSet (const API_Token&);
	static Result<DuctAngleSet> Get (const API_Token&);

public:
	class Modifier;
	friend Result<DuctAngleSet> GetDuctAngleSet ();
};


/**
 * @ingroup MEP
 * @return If able, returns the DuctAngleSet from the project.
 */
inline Result<DuctAngleSet> GetDuctAngleSet ()
{
	return DuctAngleSet::Get (ACAPI_GetToken ());
}


} // ACAPI::MEP


#endif // GS_ACAPI_MEP_DUCT_ANGLE_SET_HPP