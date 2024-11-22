#ifndef GS_ACAPI_MEP_BEND_DEFAULT_HPP
#define GS_ACAPI_MEP_BEND_DEFAULT_HPP

#include "MEPAPIExport.hpp"
#include "MEPElementDefault.hpp"
#include "MEPTypes.hpp"

// from ACAPI
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"

#include <optional>


namespace ACAPI::MEP {

namespace Impl { class IBendDefaultImpl; }

inline namespace v1 {

class Bend;


/** @brief The BendDefault contains the necessary non-geometric data for modifying a Bend.
	@ingroup MEP
	@since Archicad 27
	@ingroup MEP
	@par Example code snippet from Test / New MEP
		Take a look at @ref RoutingElementDefault "RoutingElementDefault" and @ref RoutingNodeDefault "RoutingNodeDefault"
*/
class MEPAPI_EXPORT BendDefault final : public ElementDefault {
protected:
	BendDefault (std::shared_ptr<Impl::IBendDefaultImpl>);
	static Result<BendDefault> Create (const API_Token&, Domain);

	friend class RoutingNode;
	friend class RoutingNodeDefault;
	friend class Bend;

public:
	class Modifier;
	friend Result<BendDefault>	CreateBendDefault (Domain);

	/** @brief The radius of the Bend is calculated with the help of this value.
		@return Returns the factor of the BendDefault.
	*/
	double		GetFactorRadius () const;

	/** @brief Executes the given modifier scope in a NotUndoable command.
		@param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
		@return Returns an error if the process of modification fails for some reason, otherwise nothing.
	*/
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};


class MEPAPI_EXPORT BendDefault::Modifier : public ElementDefault::Modifier {
	BendDefault& parent;
	Modifier (BendDefault&);
	virtual ~Modifier ();

public:
	friend BendDefault;

	/** @brief Sets the factor of the radius of the BendDefault.
		@param factor The value to be set. Needs to be between 0.6 and 3.0.
		@return Returns an error if the parameter is not in range, otherwise nothing.
	*/
	Result<void>	SetFactorRadius (double factor);
};


/** @brief Creates a BendDefault
	@ingroup MEP
	@param domain The Domain of the requested BendDefault.
	@return If able, returns a copy of Archicad's current Default of the Bend from the Routing tool for the domain defined by the parameter, otherwise Error.
*/
inline Result<BendDefault> CreateBendDefault (Domain domain)
{
	return BendDefault::Create (ACAPI_GetToken (), domain);
}


template<class ModifierFunc>
Result<void> BendDefault::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}


} // v1

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_BEND_DEFAULT_HPP*/
