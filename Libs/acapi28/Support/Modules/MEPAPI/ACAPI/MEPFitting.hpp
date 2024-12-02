#ifndef GS_ACAPI_MEP_FITTING_HPP
#define GS_ACAPI_MEP_FITTING_HPP

#include "MEPAPIExport.hpp"

#include "MEPModifiableElementBase.hpp"
#include "MEPFittingDefault.hpp"


namespace ACAPI::MEP {

namespace v1 {


/**
 * @brief A fitting is used in distribution systems to connect straight sections of pipes and ducts, adapting to different sizes or shapes.
 * @since Archicad 27
 * @ingroup MEP
 */
class MEPAPI_EXPORT Fitting final : public ModifiableElementBase {
	Fitting (const UniqueID&);

public:
	class Modifier;
	~Fitting ();

	/**
	 * @brief Returns a Fitting.
	 * @param uniqueId The UniqueID of the requested Fitting.
	 * @return If the uniqueId belongs to a Fitting, returns the object associated to it, otherwise Error.
	 */
	static Result<Fitting> Get (const UniqueID& uniqueId);

	/**
	 * @brief Picks up the Default from the Fitting.
	 * @return Returns a FittingDefault with the parameters of the object it was called for.
	 */
	FittingDefault PickUpDefault () const;

	/** @return Returns the domain of the Fitting. */
	Domain GetDomain () const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT Fitting::Modifier : public ModifiableElementBase::Modifier {
	Fitting& parent;

	Modifier (Fitting&);
	virtual ~Modifier ();

public:
	friend Fitting;

	/**
	 * @brief Injects the Default settings into the Fitting.
	 * @param fittingDefault The Default what will be injected. One should pay attention to the parameter, it has to belong to the same domain than the object it is called for.
	 * @return Returns an error if the injection fails for some reason, otherwise nothing.
	 */
	Result<void> Inject (const FittingDefault& fittingDefault);
};


template <typename ModifierFunc>
Result<void> Fitting::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::Fitting;

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_FITTING_HPP */