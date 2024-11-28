#ifndef GS_ACAPI_MEP_BRANCH_HPP
#define GS_ACAPI_MEP_BRANCH_HPP

#include "MEPAPIExport.hpp"

#include "MEPModifiableElementBase.hpp"
#include "MEPBranchDefault.hpp"

#include <optional>


namespace ACAPI::MEP {

namespace v1 {


/**
 * @brief A branch is a specific type of fitting that acts as an outlet from a large pipe to a smaller pipe or one of equal size.
 * @since Archicad 27
 * @ingroup MEP
 * @details This type of element can be placed at intersections
 * @par Example code snippets from Test / New MEP
 * 		Getters @snippet QueryElementsAndDefaults.cpp Branch-Getters-Example
 * 		Modification @snippet ModifyElements.cpp Branch-Modification-Example
 */
class MEPAPI_EXPORT Branch final : public ModifiableElementBase {
	Branch (const UniqueID&);
public:
	class Modifier;
	~Branch ();

	/**
	 * @brief Returns a Branch.
	 * @param uniqueId The UniqueID of the requested Branch.
	 * @return If the uniqueId belongs to a Branch, returns the object associated to it, otherwise Error.
	 */
	static Result<Branch> Get (const UniqueID& uniqueId);

	/**
	 * @brief Picks up the Default from the Branch.
	 * @return Returns a BranchDefault with the parameters of the object it was called for.
	 */
	BranchDefault PickUpDefault () const;

	/** @return Returns the insulation thickness if the Branch has insulation, otherwise std::nullopt. Branches of cable carrier domain cannot have insulation. */
	std::optional<double> GetInsulationThickness () const;

	/** @return Returns the length of the main axis of the Branch. */
	double GetLength () const;

	/** @return Returns the length of the branch of the Branch. */
	double GetBranchLength () const;

	/** @return Returns the angle of the branch of the element in degrees. */
	double GetBranchAngle () const;

	/** @return Returns the offset of the branch of the Branch. */
	double GetBranchOffset () const;

	/** @return Returns the domain of the Branch. */
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


class MEPAPI_EXPORT Branch::Modifier : public ModifiableElementBase::Modifier {
	Branch& parent;

	Modifier (Branch&);
	virtual ~Modifier ();

public:
	friend Branch;

	/**
	 * @brief Injects the Default settings into the Branch.
	 * @param branchDefault The Default what will be injected.
	 * @return Returns an error if the injection fails for some reason, otherwise nothing.
	 */
	Result<void> Inject (const BranchDefault& branchDefault);
	
	/**
	 * @brief Sets the insulation thickness of the Branch.
	 * @param thickness The value to be set. It should be a positive number.
	 * @return Returns an error if the Branch is of cable carrier domain, otherwise nothing.
	 */
	Result<void> SetInsulationThickness (double thickness);

	/** @brief Removes the insulation from the Branch. */
	void		 RemoveInsulation ();
};


template <typename ModifierFunc>
Result<void> Branch::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::Branch;

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_BRANCH_HPP