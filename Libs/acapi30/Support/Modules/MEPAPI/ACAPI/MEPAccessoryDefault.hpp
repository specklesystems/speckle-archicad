#ifndef GS_ACAPI_MEP_ACCESSORY_DEFAULT_HPP
#define GS_ACAPI_MEP_ACCESSORY_DEFAULT_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"
#include "MEPElementDefault.hpp"

namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IAccessoryDefaultImpl; }

/**
 * @brief The AccessoryDefault contains the necessary non-geometric data for creating an Accessory element.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Placement @snippet PlaceElements.cpp Accessory-Placement-Example
 */
class MEPAPI_EXPORT AccessoryDefault final : public ElementDefault {
	AccessoryDefault (std::shared_ptr<Impl::IAccessoryDefaultImpl>);
	static Result<AccessoryDefault> Create (const API_Token&, Domain);
protected:
	friend class ACAPI::Impl::ObjectCreator;

public:
	friend Result<AccessoryDefault> CreateAccessoryDefault (Domain);
	friend MEPAPI_EXPORT Result<AccessoryDefault> CreateAccessoryDefault (const ACAPI::ElementDefault&);

	/**
	 * @brief Places an Accessory element based on this Default.
	 *
	 * @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	 * 			When someone would like to group the placement of several RoutingElements and/or MEP elements together, it is recommended to create a single Command Scope.
	 * 			Doing this prevents the opening and closing of a Command Scope for every single created RoutingElement and/or MEP element, therefore the performance should be improved.
	 *
	 * @param coordinate The coordinate where the Accessory will be placed.
	 * @param orientation The orientation of the Accessory, which is based on a direction vector and a rotation vector.
	 * @param requiredId The guid to be set for the Accessory - optional parameter
	 * @return If executed with success, returns the newly placed Accessory's uniqueId, otherwise Error.
	 */
	Result<UniqueID> Place (const API_Coord3D& coordinate, const Orientation& orientation, const std::optional<API_Guid>& requiredId = std::nullopt) const;

	/**
	 * @brief Places an Accessory element based on this Default and connects it with the provided Port or RoutingNode, if it is possible.
	 *
	 * @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	 * 			When someone would like to group the placement of several RoutingElements and/or MEP elements together, it is recommended to create a single Command Scope.
	 * 			Doing this prevents the opening and closing of a Command Scope for every single created RoutingElement and/or MEP element, therefore the performance should be improved.
	 *
	 * @param portOrNodeId The id of a Port or RoutingNode, which provides the placed Accessory's position and orientation.
	 * @param requiredId The guid to be set for the Accessory - optional parameter
	 * @return If executed with success, returns the newly placed Terminal's uniqueId, otherwise Error.
	 */
	Result<UniqueID> Place (const UniqueID& portOrNodeId, const std::optional<API_Guid>& requiredId = std::nullopt) const;
};


/**
 * @brief Creates an AccessoryDefault
 * @ingroup MEP
 * @param domain The Domain of the requested AccessoryDefault. It can be ventilation or piping.
 * @return If able, returns a copy of Archicad's current Default of the Accessory tool for the domain defined by the parameter, otherwise Error (for ex. if domain is cable carrier).
 */
inline Result<AccessoryDefault> CreateAccessoryDefault (Domain domain)
{
	return AccessoryDefault::Create (ACAPI_GetToken (), domain);
}


/**
 * @brief Creates an AccessoryDefault from the given base element default.
 * @param defaultElem The base element default which will be converted to an AccessoryDefault.
 * @ingroup MEP
 * @since Archicad 29
 * @return If the given base element default refers to an Accessory, returns a copy of the AccessoryDefault, otherwise Error.
 */
MEPAPI_EXPORT Result<AccessoryDefault> CreateAccessoryDefault (const ACAPI::ElementDefault& defaultElem);


} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_ACCESSORY_DEFAULT_HPP */