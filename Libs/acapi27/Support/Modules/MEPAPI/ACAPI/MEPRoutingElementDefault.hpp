#ifndef GS_ACAPI_MEP_ROUTING_ELEMENT_DEFAULT_HPP
#define GS_ACAPI_MEP_ROUTING_ELEMENT_DEFAULT_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"
#include "MEPEnums.hpp"
#include "MEPRoutingElement.hpp"

// ARCHICADAPI
#include "ACAPI/ElementDefault.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"

#include <optional>


namespace ACAPI::MEP {

namespace Impl { class IRoutingElementDefaultImpl; }

inline namespace v1 {


class RoutingElement;
class RoutingSegmentDefault;
class RoutingNodeDefault;


/** @brief The RoutingElementDefault contains the necessary non-geometric data for creating a Routing element.
	@ingroup MEP
	@since Archicad 27
	@ingroup MEP
	@par Example code snippet from Test / New MEP
		Pickup and Getters @snippet QueryElementsAndDefaults.cpp RoutingElementDefault-Pickup-and-Getters-Example
		Assemble placement data @snippet PlaceElements.cpp RoutingElement-PlacementData-Example
		Placement @snippet PlaceElements.cpp RoutingElement-Placement-Example
*/
class MEPAPI_EXPORT RoutingElementDefault : public ACAPI::ElementDefault {
protected:
	RoutingElementDefault (std::shared_ptr<Impl::IRoutingElementDefaultImpl>);
	static Result<RoutingElementDefault> Create (const API_Token&, Domain);

public:
	class Modifier;
	friend Result<RoutingElementDefault> CreateRoutingElementDefault (Domain);
	friend class RoutingElement;

	/** @return Returns the RoutingSegmentDefault of the RoutingElementDefault.*/
	RoutingSegmentDefault GetRoutingSegmentDefault () const;

	/** @return Returns the RoutingNodeDefault of the RoutingElementDefault.*/
	RoutingNodeDefault GetRoutingNodeDefault () const;

	/** @brief Retrieves the domain of the RoutingElementDefault. */
	Domain GetDomain () const;

	/** @brief Returns the MEPSystem attribute of the RoutingElementDefault. */
	API_AttributeIndex GetMEPSystem () const;

	/** @brief Places a Routing element based on the Default.
		
		@details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
		When someone would like to group the placement of several routes and/or MEP elements together, it is recommended to create a single Command Scope.
		Doing this prevents the opening and closing of a Command Scope for every single created route and/or MEP element, therefore the performance should be improved.
	 
		@param nodeCoordinates List of coordinates for the corner points of RoutingElement.
		@param crossSectionData List of data for the cross sections of the RoutingSegments.
		@param requiredId The guid to be set for the RoutingElement - optional parameter
		@return If executed with success, returns the newly placed RoutingElement's uniqueId, otherwise Error.
	*/
	Result<UniqueID> Place (const std::vector<API_Coord3D>& nodeCoordinates, const std::vector<RoutingSegmentCrossSectionData>& crossSectionData, const std::optional<API_Guid>& requiredId = std::nullopt) const;

	/** @brief Executes the given modifier scope in a NotUndoable command.
		@param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
		@return Returns an error if the process of modification fails for some reason, otherwise nothing.
	*/
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};


class MEPAPI_EXPORT RoutingElementDefault::Modifier : public ACAPI::ModifierBase {
	RoutingElementDefault& parent;
	Modifier (RoutingElementDefault&);
	virtual ~Modifier ();

public:
	friend RoutingElementDefault;

	/** @brief Sets the RoutingSegmentDefault of RoutingElement.
		@param routingSegmentDefault The default to be set.
	*/
	void		SetRoutingSegmentDefault (const RoutingSegmentDefault& routingSegmentDefault);

	/** @brief Sets the RoutingNodeDefault of RoutingElement.
		@param routingNodeDefault The default to be set.
	*/
	void		SetRoutingNodeDefault (const RoutingNodeDefault& routingNodeDefault);

	/** @brief Sets the MEPSystem attribute of RoutingElement.
		@param attributeIndex The MEPSystem AttributeIndex to be set.
	*/
	Result<void>	SetMEPSystem (const API_AttributeIndex& attributeIndex);
};


/** @brief Creates a RoutingElementDefault
	@ingroup MEP
	@param domain The Domain of the requested RoutingElementDefault.
	@return If able, returns a copy of Archicad's current Default of the Routing tool for the domain defined by the parameter, otherwise Error.
*/
inline Result<RoutingElementDefault> CreateRoutingElementDefault (Domain domain)
{
	return RoutingElementDefault::Create (ACAPI_GetToken (), domain);
}


template<class ModifierFunc>
Result<void> RoutingElementDefault::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}


} // v1

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_ROUTING_ELEMENT_DEFAULT_HPP*/