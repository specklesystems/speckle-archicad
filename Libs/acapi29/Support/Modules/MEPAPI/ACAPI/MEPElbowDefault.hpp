#ifndef GS_ACAPI_MEP_ELBOW_DEFAULT_HPP
#define GS_ACAPI_MEP_ELBOW_DEFAULT_HPP

#include "MEPAPIExport.hpp"
#include "MEPElementDefault.hpp"
#include "MEPTypes.hpp"

// from ACAPI
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"

#include <optional>


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IElbowDefaultImpl; }

class Elbow;


/**
 * @brief The ElbowDefault contains the necessary non-geometric data for modifying an Elbow.
 * @ingroup MEP
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref RoutingElementDefault "RoutingElementDefault" and @ref RoutingNodeDefault "RoutingNodeDefault"
 */
class MEPAPI_EXPORT ElbowDefault final : public ElementDefault {
protected:
	/**
	 * @brief Constructs an ElbowDefault with the given ElbowDefault implementation.
	 * @param impl The given ElbowDefault implementation.
	 */
	ElbowDefault (std::shared_ptr<Impl::IElbowDefaultImpl> impl);
	
	/**
	 * @brief Creates an ElbowDefault with the given token and domain.
	 * @param token The given token.
	 * @param domain The given domain.
	 * @return The result of the creation with the created ElbowDefault.
	 */
	static Result<ElbowDefault> Create (const API_Token& token, Domain domain);

	friend class ACAPI::Impl::ObjectCreator;

public:
	class Modifier;
	friend Result<ElbowDefault>	CreateElbowDefault (Domain);

	/**
	 * @brief The radius of the Elbow is calculated with the help of this value in the case of Duct and Cable Carrier.
	 * @return Returns the factor of the ElbowDefault in the case of Duct and Cable Carrier, otherwise Error.
	 */
	Result<double>		GetFactorRadius () const;

	/** @return Returns the UniqueID of the PreferenceTable of a PipeElbowDefault or a DuctElbowDefault, in case of CableCarrierElbowDefault returns Error. */
	Result<UniqueID>	GetPreferenceTable () const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};


/**
 * @brief Modifier of the ElbowDefault.
 * @ingroup MEP
 */
class MEPAPI_EXPORT ElbowDefault::Modifier : public ElementDefault::Modifier {
	ElbowDefault& parent;
	Modifier (ElbowDefault&);
	virtual ~Modifier ();

	friend ElbowDefault;
public:

	/**
	 * @brief Sets the factor of the radius of the ElbowDefault in the case of Duct and Cable Carrier.
	 * @param factor The value to be set. Needs to be larger than 0.6.
	 * @return Returns an error in case of PipeElbow or if the factor parameter is too small, otherwise nothing.
	 */
	Result<void>	SetFactorRadius (double factor);


	/**
	 * @brief Sets the PreferenceTable of the ElbowDefault in the case of Duct and Pipe. This PreferenceTable will be transferred into the Elbows when a route is placed or modified.
	 * @param tableId The UniqueID referring to the PreferenceTable to be set.
	 * @return Returns an error in the case of Cable Carrier Elbow or if the referred ElbowTable can not be found, otherwise nothing.
	 */
	Result<void>	SetPreferenceTable (const UniqueID& tableId);
};


/**
 * @brief Creates an ElbowDefault
 * @ingroup MEP
 * @param domain The Domain of the requested ElbowDefault.
 * @return If able, returns a copy of Archicad's current Default of the Elbow from the RoutingElement tool for the domain defined by the parameter, otherwise Error.
 */
inline Result<ElbowDefault> CreateElbowDefault (Domain domain)
{
	return ElbowDefault::Create (ACAPI_GetToken (), domain);
}


template<class ModifierFunc>
Result<void> ElbowDefault::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}


} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_ELBOW_DEFAULT_HPP*/
