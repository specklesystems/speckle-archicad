#ifndef GS_ACAPI_MEP_ROUTING_NODE_HPP
#define GS_ACAPI_MEP_ROUTING_NODE_HPP

#include "MEPAPIExport.hpp"
#include "MEPEnums.hpp"
#include "MEPUniqueID.hpp"

// ACAPI
#include "ACAPI/ElementBase.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"

#include <optional>


namespace ACAPI::MEP {

namespace v1 {


class RoutingNodeDefault;
class BendDefault;
class TransitionDefault;


/**
 * @brief The RoutingNode can contain Bend and Transition elements.
 * @details This type of element is placed in the corner points of RoutingElement.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Getters @snippet QueryElementsAndDefaults.cpp RoutingNode-Getters-Example
 * 		Modification @snippet ModifyElements.cpp RoutingNode-Modification-Example
 */
class MEPAPI_EXPORT RoutingNode final : public ACAPI::ElementBase {
private:
	RoutingNode (const UniqueID&);

public:
	~RoutingNode ();

	class Modifier;

	/**
	 * @brief Returns a RoutingNode.
	 * @param uniqueId The UniqueID of the requested RoutingNode.
	 * @return If the uniqueId belongs to a RoutingNode, returns the object associated to it, otherwise Error.
	 */
	static Result<RoutingNode> Get (const UniqueID& uniqueId);

	/** @return Returns the position of the RoutingNode.*/
	API_Coord3D				GetPosition () const;

	/** @return Returns the UniqueID of the incoming segment if it has any.*/
	std::optional<UniqueID>	GetIncomingSegmentId () const;

	/** @return Returns the UniqueID of the outgoing segment if it has any.*/
	std::optional<UniqueID>	GetOutgoingSegmentId () const;

	/** @return Returns the UniqueIDs of the contained Bends.*/
	std::vector<UniqueID>	GetBendIds () const;

	/** @return Returns the UniqueIDs of the contained Transitions.*/
	std::vector<UniqueID>	GetTransitionIds () const;

	/** @return Returns the rule of the Bend-Transition placement order of the RoutingNode. */
	PreferredTransitionPlacement GetPreferredTransitionPlacement () const;

	/** @return Returns the UniqueID of the RoutingElement that it belongs to. */
	UniqueID				GetRoutingElementId () const;

	/** @return Returns the domain of the RoutingNode. */
	Domain					GetDomain () const;

	/**
	 * @brief Picks up and returns the Default of the RoutingNode.
	 * @return Returns a RoutingNodeDefault with the parameters of the object it was called for.
	 */
	RoutingNodeDefault		PickUpDefault () const;

	/** @return Returns the default parameters of the uncustomized Transitions.*/
	TransitionDefault		GetTransitionDefaultParameters () const;

	/** @return Returns the default parameters of the uncustomized Bends.*/
	BendDefault				GetBendDefaultParameters () const;

	/**
	 * @brief Executes the given modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT RoutingNode::Modifier : public ACAPI::ModifierBase {
	RoutingNode& parent;
	Modifier (RoutingNode&);
	virtual ~Modifier ();

protected:
	/**
	 * @brief Finalizes the modifications.
	 */
	void FinalizeModification () override;

public:
	friend RoutingNode;

	/**
	 * @brief Sets a new position of the Routing Node.
	 * @param newPosition The new position of the Routing Node.
	 */
	void	SetPosition (const API_Coord3D& newPosition);


	/**
	 * @brief Sets the rule of the Bend-Transition placement order of the Routing Node.
	 * @param preferredTransitionPlacement The rule to be set.
	 */
	void	SetPreferredTransitionPlacement (PreferredTransitionPlacement preferredTransitionPlacement);

	/**
	 * @brief Injects the given Default settings to the RoutingNode.
	 * @param routingNodeDefault The Default which will be injected.
	 * @return Returns an error if the injection fails for some reason, otherwise nothing.
	 */
	Result<void>	Inject (const RoutingNodeDefault& routingNodeDefault);

	/**
	 * @brief Sets the parameters of the Transitions.
	 * @param transitionDefault The Default to be set. One should pay attention to the parameter, it has to belong to the same domain than the object it is called for.
	 * @return Returns an error in case of domain mismatch or if the set operation fails for some internal reason, otherwise nothing.
	 */
	Result<void>	SetTransitionDefaultParameters (const TransitionDefault& transitionDefault);

	/**
	 * @brief Sets the parameters of the Bends.
	 * @param bendDefault The Default to be set. One should pay attention to the parameter, it has to belong to the same domain than the object it is called for.
	 * @return Returns an error in case of domain mismatch or if the set operation fails for some internal reason, otherwise nothing.
	 */
	Result<void>	SetBendDefaultParameters (const BendDefault& bendDefault);
};


template <typename ModifierFunc>
Result<void> RoutingNode::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::RoutingNode;

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_ROUTING_NODE_HPP