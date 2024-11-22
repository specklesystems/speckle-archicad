#ifndef GS_ACAPI_MEP_ACCESSORY_DEFAULT_HPP
#define GS_ACAPI_MEP_ACCESSORY_DEFAULT_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"
#include "MEPElementDefault.hpp"


namespace ACAPI::MEP {

namespace Impl { class IAccessoryDefaultImpl; }

inline namespace v1 {


/** @brief The AccessoryDefault contains the necessary non-geometric data for creating an Accessory element.
	@since Archicad 27
	@ingroup MEP
	@par Example code snippet from Test / New MEP
		Placement @snippet PlaceElements.cpp Accessory-Placement-Example
*/
class MEPAPI_EXPORT AccessoryDefault final : public ElementDefault {
	AccessoryDefault (std::shared_ptr<Impl::IAccessoryDefaultImpl>);
	static Result<AccessoryDefault> Create (const API_Token&, Domain);

public:
	friend class Accessory;
	friend Result<AccessoryDefault> CreateAccessoryDefault (Domain);

	/** @brief Places an Accessory element based on this Default.
	 
		@details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
		When someone would like to group the placement of several routes and/or MEP elements together, it is recommended to create a single Command Scope.
		Doing this prevents the opening and closing of a Command Scope for every single created route and/or MEP element, therefore the performance should be improved.
	
		@param coordinate The coordinate where the Accessory will be placed.
		@param orientation The orientation of the Accessory, which is based on a direction vector and a rotation vector.
		@param requiredId The guid to be set for the Accessory - optional parameter
		@return If executed with success, returns the newly placed Accessory's uniqueId, otherwise Error.
	*/
	Result<UniqueID> Place (const API_Coord3D& coordinate, const Orientation& orientation, const std::optional<API_Guid>& requiredId = std::nullopt) const;
};


/** @brief Creates an AccessoryDefault
	@ingroup MEP
	@param domain The Domain of the requested AccessoryDefault. It can be ventilation or piping.
	@return If able, returns a copy of Archicad's current Default of the Accessory tool for the domain defined by the parameter, otherwise Error (for ex. if domain is cable carrier).
*/
inline Result<AccessoryDefault> CreateAccessoryDefault (Domain domain)
{
	return AccessoryDefault::Create (ACAPI_GetToken (), domain);
}


} // v1

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_ACCESSORY_DEFAULT_HPP */