#ifndef GS_ACAPI_MEP_EQUIPMENT_DEFAULT_HPP
#define GS_ACAPI_MEP_EQUIPMENT_DEFAULT_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"
#include "MEPElementDefault.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IEquipmentDefaultImpl; }

namespace v1 {


/**
 * @brief The EquipmentDefault contains the necessary non-geometric data for creating an Equipment element.
 * @ingroup MEP
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Placement @snippet PlaceElements.cpp Equipment-Placement-Example
 */
class MEPAPI_EXPORT EquipmentDefault final : public ElementDefault {
	EquipmentDefault (std::shared_ptr<Impl::IEquipmentDefaultImpl>);
	static Result<EquipmentDefault> Create (const API_Token&);

protected:
	friend class ACAPI::Impl::ObjectCreator;

public:
	friend Result<EquipmentDefault> CreateEquipmentDefault ();

	/**
	 * @brief Places an Equipment element based on this Default.
	 *
	 * @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	 * 			When someone would like to group the placement of several RoutingElements and/or MEP elements together, it is recommended to create a single Command Scope.
	 * 			Doing this prevents the opening and closing of a Command Scope for every single created RoutingElement and/or MEP element, therefore the performance should be improved.
	 *
	 * @param coordinate The coordinate where the Equipment will be placed.
	 * @param orientation The orientation of the Equipment, which is based on a direction vector and a rotation vector.
	 * @param requiredId The guid to be set for the Equipment - optional parameter
	 * @return If executed with success, returns the newly placed Equipment's uniqueId, otherwise Error.
	 */
	Result<UniqueID> Place (const API_Coord3D& coordinate, const Orientation& orientation, const std::optional<API_Guid>& requiredId = std::nullopt) const;
};


/**
 * @brief Creates an EquipmentDefault.
 * @ingroup MEP
 * @return If able, returns a copy of Archicad's current Default of the Equipment tool, otherwise Error.
 */
inline Result<EquipmentDefault> CreateEquipmentDefault ()
{
	return EquipmentDefault::Create (ACAPI_GetToken ());
}


} // v1

using v1::EquipmentDefault;
using v1::CreateEquipmentDefault;

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_EQUIPMENT_DEFAULT_HPP */