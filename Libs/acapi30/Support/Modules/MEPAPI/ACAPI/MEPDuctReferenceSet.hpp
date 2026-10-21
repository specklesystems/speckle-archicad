#ifndef GS_ACAPI_MEP_DUCT_REFERENCE_SET_HPP
#define GS_ACAPI_MEP_DUCT_REFERENCE_SET_HPP

#include "MEPAPIExport.hpp"
#include "MEPReferenceSetBase.hpp"


namespace ACAPI::MEP {

/**
 * @brief The DuctReferenceSet contains referenceIds that are used in DuctCircularSegmentPreferenceTable and DuctElbowPreferenceTable.
 * @since Archicad 28
 * @ingroup MEP
 * @details The container is already initialized and you can access it by calling GetDuctReferenceSet.
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref ReferenceSetBase
 */
class MEPAPI_EXPORT DuctReferenceSet final : public ReferenceSetBase {
	DuctReferenceSet (const API_Token&);
	static Result<DuctReferenceSet> Get (const API_Token&);

public:
	class Modifier;
	friend Result<DuctReferenceSet> GetDuctReferenceSet ();
};


/**
 * @ingroup MEP
 * @return If able, returns the DuctReferenceSet from the project.
 */
inline Result<DuctReferenceSet> GetDuctReferenceSet ()
{
	return DuctReferenceSet::Get (ACAPI_GetToken ());
}


} // ACAPI::MEP


#endif // GS_ACAPI_MEP_DUCT_REFERENCE_SET_HPP