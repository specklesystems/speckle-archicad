#ifndef GS_ACAPI_MEP_TERMINAL_DEFAULT_HPP
#define GS_ACAPI_MEP_TERMINAL_DEFAULT_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"
#include "MEPElementDefault.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class ITerminalDefaultImpl; }

namespace v1 {


/**
 * @brief The TerminalDefault contains the necessary non-geometric data for creating a Terminal element.
 * @ingroup MEP
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Placement @snippet PlaceElements.cpp Terminal-Placement-Example
 */
class MEPAPI_EXPORT TerminalDefault final : public ElementDefault {
	TerminalDefault (std::shared_ptr<Impl::ITerminalDefaultImpl>);
	static Result<TerminalDefault> Create (const API_Token&, Domain);

protected:
	friend class ACAPI::Impl::ObjectCreator;

public:
	friend Result<TerminalDefault> CreateTerminalDefault (Domain);

	/**
	 * @brief Places a Terminal element based on this Default.
	 *
	 * @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	 * 			When someone would like to group the placement of several RoutingElements and/or MEP elements together, it is recommended to create a single Command Scope.
	 * 			Doing this prevents the opening and closing of a Command Scope for every single created RoutingElement and/or MEP element, therefore the performance should be improved.
	 *
	 * @param coordinate The coordinate where the Terminal will be placed.
	 * @param orientation The orientation of the Terminal, which is based on a direction vector and a rotation vector.
	 * @param requiredId The guid to be set for the Terminal - optional parameter
	 * @return If executed with success, returns the newly placed Terminal's uniqueId, otherwise Error.
	 */
	Result<UniqueID> Place (const API_Coord3D& coordinate, const Orientation& orientation, const std::optional<API_Guid>& requiredId = std::nullopt) const;

	/**
	 * @brief Places a Terminal element based on this Default and connects it with the provided Port or RoutingNode, if it is possible.
	 *
	 * @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	 * 			When someone would like to group the placement of several RoutingElements and/or MEP elements together, it is recommended to create a single Command Scope.
	 * 			Doing this prevents the opening and closing of a Command Scope for every single created RoutingElement and/or MEP element, therefore the performance should be improved.
	 *
	 * @param portOrNodeId The id of a Port or RoutingNode, which provides the placed Terminal's position and orientation.
	 * @param requiredId The guid to be set for the Terminal - optional parameter
	 * @return If executed with success, returns the newly placed Terminal's uniqueId, otherwise Error.
	 */
	Result<UniqueID> Place (const UniqueID& portOrNodeId, const std::optional<API_Guid>& requiredId = std::nullopt) const;
};


/**
 * @brief Creates a TerminalDefault
 * @ingroup MEP
 * @param domain The Domain of the requested TerminalDefault. It can be ventilation or piping.
 * @return If able, returns a copy of Archicad's current Default of the Terminal tool for the domain defined by the parameter, otherwise Error (for ex. if domain is cable carrier).
 */
inline Result<TerminalDefault> CreateTerminalDefault (Domain domain)
{
	return TerminalDefault::Create (ACAPI_GetToken (), domain);
}


} // v1

using v1::TerminalDefault;
using v1::CreateTerminalDefault;

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_TERMINAL_DEFAULT_HPP */