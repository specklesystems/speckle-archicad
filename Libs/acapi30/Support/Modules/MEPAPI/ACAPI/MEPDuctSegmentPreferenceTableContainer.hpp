#ifndef GS_ACAPI_MEP_DUCT_SEGMENT_PREFERENCE_TABLE_CONTAINER_HPP
#define GS_ACAPI_MEP_DUCT_SEGMENT_PREFERENCE_TABLE_CONTAINER_HPP

#include "MEPAPIExport.hpp"
#include "MEPPreferenceTableContainerBase.hpp"


namespace ACAPI::MEP {

/**
 * @brief The DuctSegmentPreferenceTableContainer can contain several PreferenceTableBase associated with ventilation.
 * @ingroup MEP
 * @since Archicad 27
 * @ingroup MEP
 * @details The container is already initialized (but may be empty) and you can access it by calling GetDuctSegmentPreferenceContainer.
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
 */
class MEPAPI_EXPORT DuctSegmentPreferenceTableContainer final : public PreferenceTableContainerBase {
	DuctSegmentPreferenceTableContainer (const API_Token&);
	static Result<DuctSegmentPreferenceTableContainer> Get (const API_Token&);

public:
	class Modifier;
	friend Result<DuctSegmentPreferenceTableContainer> GetDuctSegmentPreferenceTableContainer ();
};


/**
 * @ingroup MEP
 * @return If able, returns the DuctPreferenceTableContainer from the project.
 */
inline Result<DuctSegmentPreferenceTableContainer> GetDuctSegmentPreferenceTableContainer ()
{
	return DuctSegmentPreferenceTableContainer::Get (ACAPI_GetToken ());
}


} // ACAPI::MEP


#endif // GS_ACAPI_MEP_DUCT_SEGMENT_PREFERENCE_TABLE_CONTAINER_HPP