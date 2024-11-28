#ifndef GS_ACAPI_MEP_FITTING_DEFAULT_HPP
#define GS_ACAPI_MEP_FITTING_DEFAULT_HPP

#include "MEPAPIExport.hpp"

#include "MEPElementDefault.hpp"
#include "MEPTypes.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IFittingDefaultImpl; }

namespace v1 {


/**
 * @brief The FittingDefault contains the necessary non-geometric data for creating a Fitting element.
 * @ingroup MEP
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Placement @snippet PlaceElements.cpp Fitting-Placement-Example
 */
class MEPAPI_EXPORT FittingDefault final : public ElementDefault {
	FittingDefault (std::shared_ptr<Impl::IFittingDefaultImpl>);
	static Result<FittingDefault> Create (const API_Token&, Domain);

protected:
	friend class ACAPI::Impl::ObjectCreator;

public:
	friend Result<FittingDefault> CreateFittingDefault (Domain);

	/**
	 * @brief Places a Fitting element based on this Default.
	 *
	 * @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	 * 			When someone would like to group the placement of several RoutingElements and/or MEP elements together, it is recommended to create a single Command Scope.
	 * 			Doing this prevents the opening and closing of a Command Scope for every single created RoutingElement and/or MEP element, therefore the performance should be improved.
	 *
	 * @param coordinate The coordinate where the Fitting will be placed.
	 * @param orientation The orientation of the Fitting, which is based on a direction vector and a rotation vector.
	 * @param requiredId The guid to be set for the Fitting - optional parameter
	 * @return If executed with success, returns the newly placed Fitting's uniqueId, otherwise Error.
	 */
	Result<UniqueID> Place (const API_Coord3D& coordinate, const Orientation& orientation, const std::optional<API_Guid>& requiredId = std::nullopt) const;

	/**
	 * @brief Places a Fitting element based on this Default and connects it with the provided Port or RoutingNode, if it is possible.
	 *
	 * @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	 * 			When someone would like to group the placement of several RoutingElements and/or MEP elements together, it is recommended to create a single Command Scope.
	 * 			Doing this prevents the opening and closing of a Command Scope for every single created RoutingElement and/or MEP element, therefore the performance should be improved.
	 *
	 * @param portOrNodeId The id of a Port or RoutingNode, which provides the placed Fitting's position and orientation.
	 * @param requiredId The guid to be set for the Fitting - optional parameter
	 * @return If executed with success, returns the newly placed Terminal's uniqueId, otherwise Error.
	 */
	Result<UniqueID> Place (const UniqueID& portOrNodeId, const std::optional<API_Guid>& requiredId = std::nullopt) const;
};


/**
 * @brief Creates an FittingDefault
 * @ingroup MEP
 * @param domain The Domain of the requested FittingDefault.
 * @return If able, returns a copy of Archicad's current Default of the Fitting tool for the domain defined by the parameter, otherwise Error.
 */
inline Result<FittingDefault> CreateFittingDefault (Domain domain)
{
	return FittingDefault::Create (ACAPI_GetToken (), domain);
}


} // v1

using v1::FittingDefault;
using v1::CreateFittingDefault;

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_FITTING_DEFAULT_HPP */