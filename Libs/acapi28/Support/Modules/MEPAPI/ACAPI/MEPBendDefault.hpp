#ifndef GS_ACAPI_MEP_BEND_DEFAULT_HPP
#define GS_ACAPI_MEP_BEND_DEFAULT_HPP

#include "MEPAPIExport.hpp"
#include "MEPElementDefault.hpp"
#include "MEPTypes.hpp"

// from ACAPI
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"

#include <optional>


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IBendDefaultImpl; }

namespace v1 {

class Bend;


/**
 * @brief The BendDefault contains the necessary non-geometric data for modifying a Bend.
 * @ingroup MEP
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref RoutingElementDefault "RoutingElementDefault" and @ref RoutingNodeDefault "RoutingNodeDefault"
 */
class MEPAPI_EXPORT BendDefault final : public ElementDefault {
protected:
	/**
	 * @brief Constructs a BendDefault with the given bend default implementation.
	 * @param impl The given bend default implementation.
	 */
	BendDefault (std::shared_ptr<Impl::IBendDefaultImpl> impl);
	
	/**
	 * @brief Creates a BendDefault with the given token and domain.
	 * @param token The given token.
	 * @param domain The given domain.
	 * @return The result of the creation with the created BendDefault.
	 */
	static Result<BendDefault> Create (const API_Token& token, Domain domain);

	friend class ACAPI::Impl::ObjectCreator;

public:
	class Modifier;
	friend Result<BendDefault>	CreateBendDefault (Domain);

	/**
	 * @brief The radius of the Bend is calculated with the help of this value in the case of Duct and Cable Carrier.
	 * @return Returns the factor of the BendDefault in the case of Duct and Cable Carrier, otherwise Error.
	 */
	Result<double>		GetFactorRadius () const;

	/** @return Returns the UniqueID of the PreferenceTable of a PipeBendDefault or a circular DuctBendDefault, in case of rectangular DuctBendDefault and CableCarrierBendDefault returns Error. */
	Result<UniqueID>	GetPreferenceTable () const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
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

	/**
	 * @brief Sets the factor of the radius of the BendDefault in the case of Duct and Cable Carrier.
	 * @param factor The value to be set. Needs to be larger than 0.6.
	 * @return Returns an error in case of Pipe Bend or if the factor parameter is too small, otherwise nothing.
	 */
	Result<void>	SetFactorRadius (double factor);


	/**
	 * @brief Sets the PreferenceTable of the BendDefault in the case of Pipe. This PreferenceTable will be transferred into the Bends when a route is placed or modified.
	 * @param tableId The UniqueID referring to the PreferenceTable to be set.
	 * @return Returns an error in the case of rectangular Duct Bend and Cable Carrier Bend or if the referred ElbowTable can not be found, otherwise nothing.
	 */
	Result<void>	SetPreferenceTable (const UniqueID& tableId);
};


/**
 * @brief Creates a BendDefault
 * @ingroup MEP
 * @param domain The Domain of the requested BendDefault.
 * @return If able, returns a copy of Archicad's current Default of the Bend from the RoutingElement tool for the domain defined by the parameter, otherwise Error.
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

using v1::BendDefault;
using v1::CreateBendDefault;

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_BEND_DEFAULT_HPP*/
