#ifndef GS_ACAPI_MEP_CABLE_CARRIER_SEGMENT_PREFERENCE_TABLE_CONTAINER_HPP
#define GS_ACAPI_MEP_CABLE_CARRIER_SEGMENT_PREFERENCE_TABLE_CONTAINER_HPP

#include "MEPAPIExport.hpp"
#include "MEPPreferenceTableContainerBase.hpp"


namespace ACAPI::MEP {

namespace v1 {

/**
 * @brief The CableCarrierSegmentPreferenceTableContainer can contain several PreferenceTableBase associated with cable carriers.
 * @ingroup MEP
 * @since Archicad 27
 * @ingroup MEP
 * @details The container is already initialized (but may be empty) and you can access it by calling GetCableCarrierSegmentPreferenceContainer.
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
 */
class MEPAPI_EXPORT CableCarrierSegmentPreferenceTableContainer final : public PreferenceTableContainerBase {
	CableCarrierSegmentPreferenceTableContainer (const API_Token&);
	static Result<CableCarrierSegmentPreferenceTableContainer> Get (const API_Token&);

public:
	class Modifier;
	friend Result<CableCarrierSegmentPreferenceTableContainer> GetCableCarrierSegmentPreferenceTableContainer ();
};


/**
 * @ingroup MEP
 * @return If able, returns the CableCarrierPreferenceTableContainer from the project.
 */
inline Result<CableCarrierSegmentPreferenceTableContainer> GetCableCarrierSegmentPreferenceTableContainer ()
{
	return CableCarrierSegmentPreferenceTableContainer::Get (ACAPI_GetToken ());
}


} // v1

using v1::CableCarrierSegmentPreferenceTableContainer;
using v1::GetCableCarrierSegmentPreferenceTableContainer;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_CABLE_CARRIER_SEGMENT_PREFERENCE_TABLE_CONTAINER_HPP