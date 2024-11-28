#ifndef GS_ACAPI_MEP_ROUTING_NODE_DEFAULT_HPP
#define GS_ACAPI_MEP_ROUTING_NODE_DEFAULT_HPP

#include "MEPAPIExport.hpp"
#include "MEPEnums.hpp"
#include "MEPUniqueID.hpp"
#include "MEPTypes.hpp"
#include "MEPRoutingNode.hpp"

// from ACAPI
#include "ACAPI/ElementDefault.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IRoutingNodeDefaultImpl; }

namespace v1 {

class BendDefault;
class TransitionDefault;

/**
 * @brief The RoutingNodeDefault contains the necessary non-geometric data for creating and modifying a Routing Node.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref RoutingElementDefault "RoutingElementDefault"
 * 		RoutingNodeDefault Modification @snippet ModifyElements.cpp RoutingNodeDefault-Modification-Example
 */
class MEPAPI_EXPORT RoutingNodeDefault : public ACAPI::ElementDefault {
protected:

	friend class ACAPI::Impl::ObjectCreator;

	/**
	 * @brief Constructs a RoutingNodeDefault with the given implementation.
	 * @param impl The given implementation.
	 */
	RoutingNodeDefault (std::shared_ptr<Impl::IRoutingNodeDefaultImpl> impl);

	/**
	 * @brief Creates a RoutingNodeDefault with the given token and domain.
	 * @param token The given token.
	 * @param domain The given domain.
	 * @return The result of the creation with the created RoutingNodeDefault.
	 */
	static Result<RoutingNodeDefault> Create (const API_Token& token, Domain domain);

public:
	class Modifier;
	friend Result<RoutingNodeDefault> CreateRoutingNodeDefault (Domain);

	/** @return Returns the BendDefault of the RoutingNodeDefault.*/
	BendDefault						GetBendDefault () const;

	/** @return Returns the TransitionDefault of the RoutingNodeDefault.*/
	TransitionDefault				GetTransitionDefault () const;

	/** @return Returns the domain of the default. */
	Domain							GetDomain () const;

	/** @return Returns the rule of the Bend-Transition placement order of the RoutingNodeDefault. */
	PreferredTransitionPlacement	GetPreferredTransitionPlacement () const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};


class MEPAPI_EXPORT RoutingNodeDefault::Modifier : public ACAPI::ModifierBase {
	RoutingNodeDefault& parent;
	Modifier (RoutingNodeDefault&);
	virtual ~Modifier ();

public:
	friend RoutingNodeDefault;

	/**
	 * @brief Sets the BendDefault to the RoutingNodeDefault.
	 * @param bendDefault The value to be set.
	 */
	void SetBendDefault (const BendDefault& bendDefault) const;

	/**
	 * @brief Sets the TransitionDefault to the RoutingNodeDefault.
	 * @param transitionDefault The value to be set.
	 */
	void SetTransitionDefault (const TransitionDefault& transitionDefault) const;

	/**
	 * @brief Sets the rule of the Bend-Transition placement order of the RoutingNodeDefault.
	 * @param preferredTransitionPlacement The rule to be set.
	 */
	void SetPreferredTransitionPlacement (PreferredTransitionPlacement preferredTransitionPlacement);
};


/**
 * @brief Creates a RoutingNodeDefault
 * @ingroup MEP
 * @param domain The Domain of the requested RoutingNodeDefault.
 * @return If able, returns a copy of Archicad's current Default of the RoutingNode from the RoutingElement tool for the domain defined by the parameter, otherwise Error.
 */
inline Result<RoutingNodeDefault> CreateRoutingNodeDefault (Domain domain)
{
	return RoutingNodeDefault::Create (ACAPI_GetToken (), domain);
}


template<class ModifierFunc>
Result<void> RoutingNodeDefault::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}


} // v1

using v1::RoutingNodeDefault;
using v1::CreateRoutingNodeDefault;

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_ROUTING_NODE_DEFAULT_HPP