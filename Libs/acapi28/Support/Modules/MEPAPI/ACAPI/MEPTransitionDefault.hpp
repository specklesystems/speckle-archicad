#ifndef GS_ACAPI_MEP_TRANSITION_DEFAULT_HPP
#define GS_ACAPI_MEP_TRANSITION_DEFAULT_HPP

#include "MEPAPIExport.hpp"
#include "MEPEnums.hpp"
#include "MEPTypes.hpp"
#include "MEPUniqueID.hpp"
#include "MEPElementDefault.hpp"

// from ACAPI
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class ITransitionDefaultImpl; }

namespace v1 {

class Transition;


/**
 * @brief The TransitionDefault contains the necessary non-geometric data for creating and modifying a Transition.
 * @ingroup MEP
 * @since Archicad 27
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref RoutingElementDefault "RoutingElementDefault" and @ref RoutingNodeDefault "RoutingNodeDefault"
 */
class MEPAPI_EXPORT TransitionDefault : public ElementDefault {
protected:
	/**
	 * @brief Constructs a TransitionDefault with the given implementation.
	 * @param impl The given implementation.
	 */
	TransitionDefault (std::shared_ptr<Impl::ITransitionDefaultImpl> impl);

	/**
	 * @brief Creates a TransitionDefault with the given token and domain.
	 * @param token The given token.
	 * @param domain The given domain.
	 * @return The result of the creation with the created TransitionDefault.
	 */
	static Result<TransitionDefault>	Create (const API_Token& token, Domain domain);
	
	friend class ACAPI::Impl::ObjectCreator;

public:
	class Modifier;
	friend Result<TransitionDefault>	CreateTransitionDefault (Domain);

	/** @return Returns the angle of the TransitionDefault in degrees. */
	double								GetAngle () const;

	/** @return Returns the offset of the TransitionDefault in the Y direction. */
	double								GetOffsetY () const;

	/** @return Returns the offset of the TransitionDefault in the Z direction. */
	double								GetOffsetZ () const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};


class MEPAPI_EXPORT TransitionDefault::Modifier : public ElementDefault::Modifier {
	TransitionDefault& parent;
	Modifier (TransitionDefault&);
	virtual ~Modifier ();

public:
	friend TransitionDefault;

	/**
	 * @brief Sets the length of TransitionDefault.
	 * @param length The value to be set. Needs to be between [1, 89] degrees.
	 * @return Returns an error if the parameter is not in range, otherwise nothing.
	 */
	Result<void> SetAngle (double length);
};


/**
 * @brief Creates a TransitionDefault
 * @ingroup MEP
 * @param domain The Domain of the requested TransitionDefault.
 * @return If able, returns a copy of Archicad's current Default of the Transition from the RoutingElement tool for the domain defined by the parameter, otherwise Error.
 */
inline Result<TransitionDefault> CreateTransitionDefault (Domain domain)
{
	return TransitionDefault::Create (ACAPI_GetToken (), domain);
}


template<class ModifierFunc>
Result<void> TransitionDefault::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}

} // v1

using v1::TransitionDefault;
using v1::CreateTransitionDefault;

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_ROUTING_NODE_DEFAULT_HPP