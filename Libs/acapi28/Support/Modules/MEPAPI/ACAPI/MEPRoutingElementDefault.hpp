#ifndef GS_ACAPI_MEP_ROUTING_ELEMENT_DEFAULT_HPP
#define GS_ACAPI_MEP_ROUTING_ELEMENT_DEFAULT_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"
#include "MEPEnums.hpp"

// ARCHICADAPI
#include "ACAPI/ElementDefault.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"

#include <optional>
#include <map>


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IRoutingElementDefaultImpl; }

namespace v1 {

class RoutingSegmentDefault;
class RoutingNodeDefault;


/**
 * @brief The RoutingElementDefault contains the necessary non-geometric data for creating a Routing element.
 * @ingroup MEP
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Pickup and Getters @snippet QueryElementsAndDefaults.cpp RoutingElementDefault-Pickup-and-Getters-Example
 * 		Assemble placement data @snippet PlaceElements.cpp RoutingElement-PlacementData-Example
 * 		Placement @snippet PlaceElements.cpp RoutingElement-Placement-Example
 */
class MEPAPI_EXPORT RoutingElementDefault : public ACAPI::ElementDefault {
protected:

	friend class ACAPI::Impl::ObjectCreator;

	/**
	 * @brief Constructs a RoutingElementDefault with the given implementation.
	 * @param impl The given implementation.
	 */
	RoutingElementDefault (std::shared_ptr<Impl::IRoutingElementDefaultImpl> impl);

	/**
	 * @brief Creates a RoutingElementDefault with the given token and domain.
	 * @param token The given token.
	 * @param domain The given domain.
	 * @return The result with the created RoutingElementDefault.
	 */
	static Result<RoutingElementDefault>	Create (const API_Token& token, Domain domain);

public:
	class Modifier;
	friend Result<RoutingElementDefault>	CreateRoutingElementDefault (Domain);

	/** @return Returns the RoutingSegmentDefault of the RoutingElementDefault.*/
	RoutingSegmentDefault					GetRoutingSegmentDefault () const;

	/** @return Returns the RoutingNodeDefault of the RoutingElementDefault.*/
	RoutingNodeDefault						GetRoutingNodeDefault () const;

	/**
	 * @brief Retrieves the domain of the RoutingElementDefault.
	 * @return The domain of the RoutingElementDefault.
	 */
	Domain									GetDomain () const;

	/** @return Returns the MEPSystem attribute of the RoutingElementDefault. */
	API_AttributeIndex						GetMEPSystem () const;

	/** @return Returns the UniqueID of the Branch PreferenceTable of a Duct or Pipe RoutingElementDefault, in case of Cable Carrier returns Error. */
	Result<UniqueID>						GetBranchPreferenceTableId () const;

	/**
	 * @brief Places a Routing element based on the Default.
	 *
	 * @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	 * 			When someone would like to group the placement of several RoutingElements and/or MEP elements together, it is recommended to create a single Command Scope.
	 * 			Doing this prevents the opening and closing of a Command Scope for every single created RoutingElement and/or MEP element, therefore the performance should be improved.
	 *
	 * @param nodeCoordinates List of coordinates for the corner points of RoutingElement.
	 * @param rectangularCrossSectionData List of data for the rectangular cross sections of the RoutingSegments.
	 * @param circularCrossSectionData List of data for the circular cross sections of the RoutingSegments.
	 * @param requiredId The guid to be set for the RoutingElement - optional parameter
	 * @return If executed with success, returns the newly placed RoutingElement's uniqueId, otherwise Error.
	 */
	Result<UniqueID> Place (const std::vector<API_Coord3D>& nodeCoordinates, const std::map<UInt32, RoutingSegmentRectangularCrossSectionData>& rectangularCrossSectionData, const std::map<UInt32, RoutingSegmentCircularCrossSectionData>& circularCrossSectionData, const std::optional<API_Guid>& requiredId = std::nullopt) const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
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

	/**
	 * @brief Sets the RoutingSegmentDefault of RoutingElement.
	 * @param routingSegmentDefault The default to be set.
	 */
	void		SetRoutingSegmentDefault (const RoutingSegmentDefault& routingSegmentDefault);

	/**
	 * @brief Sets the RoutingNodeDefault of RoutingElement.
	 * @param routingNodeDefault The default to be set.
	 */
	void		SetRoutingNodeDefault (const RoutingNodeDefault& routingNodeDefault);

	/**
	 * @brief Sets the MEPSystem attribute of RoutingElement.
	 * @param attributeIndex The MEPSystem AttributeIndex to be set.
	 * @return The result of the setting.
	 */
	Result<void>	SetMEPSystem (const API_AttributeIndex& attributeIndex);

	/**
	 * @brief Sets the Branch PreferenceTable of the RoutingElementDefault.
	 * @param uniqueId The UniqueID of the Branch PreferenceTable.
	 * @return Returns an error if the parameter does not identify a Branch PreferenceTable, otherwise nothing.
	 */
	Result<void>	SetBranchPreferenceTableId (const UniqueID& uniqueId);
};


/**
 * @brief Creates a RoutingElementDefault
 * @ingroup MEP
 * @param domain The Domain of the requested RoutingElementDefault.
 * @return If able, returns a copy of Archicad's current Default of the RoutingElement tool for the domain defined by the parameter, otherwise Error.
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

using v1::RoutingElementDefault;
using v1::CreateRoutingElementDefault;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_ROUTING_ELEMENT_DEFAULT_HPP*/