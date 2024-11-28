#ifndef GS_ACAPI_MEP_ROUTING_ELEMENT_HPP
#define GS_ACAPI_MEP_ROUTING_ELEMENT_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"
#include "MEPEnums.hpp"

// ACAPI
#include "ACAPI/ElementBase.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"


namespace ACAPI::MEP {

namespace v1 {


class RoutingElementDefault;
class RoutingSegmentDefault;
class RoutingNodeDefault;


/**
 * @brief The RoutingElement can contain Routing Segments and Routing Nodes.
 * @details RoutingElement is on the highest level of the hierarchy.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Getters @snippet QueryElementsAndDefaults.cpp RoutingElement-Getters-Example
 * 		@snippet QueryElementsAndDefaults.cpp RoutingElement-Getters-Example2
 * 		Modification @snippet ModifyElements.cpp RoutingElement-Modification-Example
 * 		Connection of two RoutingElements @snippet PlaceElements.cpp RoutingElement-Connect-Example
 * 		Placement and Connection wrapped together @snippet PlaceElements.cpp RoutingElement-PlaceAndConnectWrapped-Example
 * 		Connection of RoutingElement with element @snippet PlaceElements.cpp RoutingElement-PlaceAndConnectRoutingElementToElement-Example
 */
class MEPAPI_EXPORT RoutingElement : public ACAPI::ElementBase {
private:
	RoutingElement (const UniqueID&);

public:
	~RoutingElement ();

	class Modifier;

	/**
	 * @brief Returns a Routing Element.
	 * @param uniqueId The UniqueID of the requested Routing Element.
	 * @return If the uniqueId belongs to a RoutingElement, returns the object associated to it, otherwise Error.
	 */
	static Result<RoutingElement>	Get (const UniqueID& uniqueId);
	
	/** @return Returns the UniqueIDs of the Routing Segments contained by the RoutingElement. */
	std::vector<UniqueID>			GetRoutingSegmentIds () const;

	/** @return Returns the UniqueIDs of the Routing Nodes contained by the RoutingElement. */
	std::vector<UniqueID>			GetRoutingNodeIds () const;

	/** @return Returns the list of 3D coordinates which form the polyline of the RoutingElement. */
	std::vector<API_Coord3D>		GetPolyLine () const;

	/** @return Returns the relative offset level from the lowest node of the RoutingElement to the level of Home Story. */
	double							GetOffsetFromHomeStory () const;

	/** @return Returns the domain of the RoutingElement. */
	Domain							GetDomain () const;

	/** @return Returns the AttributeIndex of the MEPSystem attribute to which it belongs. */
	API_AttributeIndex				GetMEPSystem () const;

	/** @return Returns the UniqueID of the Branch PreferenceTable of a Duct or Pipe Routing Element, in case of Cable Carrier returns Error. */
	Result<UniqueID>				GetBranchPreferenceTableId () const;

	/**
	 * @brief Picks up and returns the Default of the RoutingElement.
	 * @return Returns a BendDefault with the parameters of the object it was called for.
	 */
	RoutingElementDefault			PickUpDefault () const;

	/**
	 * @details On Archicad's user interface, in the editing mode of a RoutingElement, its RoutingSegments can be customized separately.
	 * 			This function provides the opportunity for querying the uncustomized RoutingSegment settings from the RoutingElement.
	 * @return Returns the parameters of the uncustomized RoutingSegments.
	 */
	RoutingSegmentDefault			GetRoutingSegmentDefaultParameters () const;

	/**
	 * @details On Archicad's user interface, in the editing mode of a RoutingElement, its RoutingNodes can be customized separately.
	 * 			This function provides the opportunity for querying the uncustomized RoutingNode settings from the RoutingElement.
	 * @return Returns the parameters of the uncustomized RoutingNodes.
	 */
	RoutingNodeDefault				GetRoutingNodeDefaultParameters () const;

	/**
	 * @return Returns the id of the Port which is at least logically connected to the RoutingElement's first RoutingSegment's first Port, otherwise std::nullopt. This does not necessarily mean
	 * that the RoutingSegment's first Port is in a physical connection with it. For that, please call @ref PortBase::IsPhysicallyConnected "PortBase::IsPhysicallyConnceted".
	 */
	std::optional<UniqueID>			GetLogicallyConnectedPortIdAtRouteBegin ();

	/**
	 * @return Returns the id of the Port which is at least logically connected to the RoutingElement's last RoutingSegment's last Port, otherwise std::nullopt. This does not necessarily mean
	 * that the RoutingSegment's last Port is in a physical connection with it. For that, please call @ref PortBase::IsPhysicallyConnected "PortBase::IsPhysicallyConnceted".
	 */
	std::optional<UniqueID>			GetLogicallyConnectedPortIdAtRouteEnd ();

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT RoutingElement::Modifier : public ACAPI::ModifierBase {
	RoutingElement& parent;

	Modifier (RoutingElement&);

protected:
	/**
	 * @brief Finalizes the modifications.
	 */
	void FinalizeModification () override;

public:
	virtual ~Modifier ();
	friend RoutingElement;

	/**
	 * @brief Injects the given Default settings to the RoutingElement.
	 * @param routingElementDefault The Default which will be injected. One should pay attention to the parameter, it has to belong to the same domain than the object it is called for.
	 * @return Returns an error if the injection fails for some reason, otherwise nothing.
	 */
	Result<void> Inject (const RoutingElementDefault& routingElementDefault);

	/**
	 * @brief Sets the MEPSystem attribute of the RoutingElement.
	 * @param index The AttributeIndex of the MEPSystem attribute.
	 */
	void SetMEPSystem (const API_AttributeIndex& index);

	/** 
	 * @brief Sets the Branch PreferenceTable of the RoutingElement.
	 * @param uniqueId The UniqueID of the PreferenceTable.
	 * @return Returns an error if the parameter does not identify a Branch PreferenceTable, otherwise nothing.
	*/
	Result<void> SetBranchPreferenceTableId (const UniqueID& uniqueId);

	/**
	 * @brief Sets the parameters of the uncustomized RoutingSegments.
	 * @details On Archicad's user interface, in the editing mode of a RoutingElement, its RoutingSegments can be customized separately.
	 * 			This function provides the opportunity for setting the uncustomized RoutingSegment parameters in the RoutingElement.
	 * @param routingSegmentDefault The Default to be set. One should pay attention to the parameter, it has to belong to the same domain than the object it is called for.
	 * @return Returns an error in case of domain mismatch or if the set operation fails for some internal reason, otherwise nothing.
	 */
	Result<void> SetRoutingSegmentDefaultParameters (const RoutingSegmentDefault& routingSegmentDefault);

	/**
	 * @brief Sets the parameters of the uncustomized RoutingNodes.
	 * @details On Archicad's user interface, in the editing mode of a RoutingElement, its RoutingNodes can be customized separately.
	 * 			This function provides the opportunity for setting the uncustomized RoutingNode parameters in the RoutingElement.
	 * @param routingNodeDefault The Default to be set. One should pay attention to the parameter, it has to belong to the same domain than the object it is called for.
	 * @return Returns an error in case of domain mismatch or if the set operation fails for some internal reason, otherwise nothing.
	 */
	Result<void> SetRoutingNodeDefaultParameters (const RoutingNodeDefault& routingNodeDefault);

	/**
	 * @brief Connects logically this RoutingElement with the parameter MEPElement or RoutingElement, if they can be connected.
	 * @details In case of RoutingElements, the two of them have to match in domain, MEPSystem and they need to have an intersection point which will serve as a connection.
	 * 			Depending on geometry this could mean the merge of two RoutingElements (when one is a continuation of the other), or insertion of a Branch element (when three RoutingElements meet,
	 * 			or one is connected into another's RoutingSegment). Either the beginning or the end node of the RoutingElement given as a parameter must intersect the RoutingElement from which Connect was called.
	 * 			In case of other MEPElements, their connecting ports have to match in domain, MEPSystem and have to be positioned and oriented correctly.
	 * 			The direction vector of the ports have to point in opposite directions.
	 *			The above mentioned requirements are enough to form a logical connection, however for a physical Port-Port connection to be created, please look for further guidance at @ref PortBase::IsPhysicallyConnectable "PortBase::IsPhysicallyConnectable".
	 * @param uniqueId The UniqueID of the MEPElement or RoutingElement which will be connected to this RoutingElement.
	 * @return Returns an error in case of domain, MEPSystem mismatch or if they can not be connected geometrically, otherwise RouteConnectionResult will contain as deletedRoutingElementId the RoutingElement given as parameter,
	 * 		   or the id of the newly created RoutingElement, splitted from the original RoutingElement.
	 */
	Result<RouteConnectionResult> ConnectLogically (const UniqueID& uniqueId);
};


template <typename ModifierFunc>
Result<void> RoutingElement::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::RoutingElement;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_ROUTING_ELEMENT_HPP*/