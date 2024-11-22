#ifndef GS_ACAPI_MEP_CABLE_CARRIER_PREFERENCE_TABLE_CONTAINER_HPP
#define GS_ACAPI_MEP_CABLE_CARRIER_PREFERENCE_TABLE_CONTAINER_HPP

#include "MEPAPIExport.hpp"
#include "MEPPreferenceTableContainerBase.hpp"


namespace ACAPI::MEP {

inline namespace v1 {

/** @brief The CableCarrierPreferenceTableContainer can contain several PreferenceTableBase associated with cable carriers.
	@ingroup MEP
	@since Archicad 27
 	@ingroup MEP
	@details The container is already initialized (but may be empty) and you can access it by calling GetCableCarrierPreferenceContainer.
 	@par Example code snippet from Test / New MEP
 		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
*/
class MEPAPI_EXPORT CableCarrierPreferenceTableContainer final : public PreferenceTableContainerBase {
	CableCarrierPreferenceTableContainer (const API_Token&);
	static Result<CableCarrierPreferenceTableContainer> Get (const API_Token&);

public:
	class Modifier;
	friend Result<CableCarrierPreferenceTableContainer> GetCableCarrierPreferenceTableContainer ();
};


/** @ingroup MEP
	@return If able, returns the CableCarrierPreferenceTableContainer from the project.
*/
inline Result<CableCarrierPreferenceTableContainer> GetCableCarrierPreferenceTableContainer ()
{
	return CableCarrierPreferenceTableContainer::Get (ACAPI_GetToken ());
}


} // v1

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_CABLE_CARRIER_PREFERENCE_TABLE_CONTAINER_HPP