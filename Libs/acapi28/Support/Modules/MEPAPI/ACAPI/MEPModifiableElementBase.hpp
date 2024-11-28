#ifndef GS_ACAPI_MEP_MODIFIABLE_ELEMENTBASE_HPP
#define GS_ACAPI_MEP_MODIFIABLE_ELEMENTBASE_HPP

#include "MEPAPIExport.hpp"
#include "MEPTypes.hpp"
#include "MEPEnums.hpp"
#include "MEPElementBase.hpp"

#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"

#include <vector>


namespace ACAPI::MEP {

namespace Impl { class IElementBaseImpl; }

namespace v1 {


/**
 * @brief The ModifiableElementBase contains the available modifying actions for ElementBase.
 * @details It is a collection of actions regarding common MEP attributes that can be handled through this parent entity.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippets from Test / New MEP
 * 		Modification @snippet ModifyElements.cpp ModifiableElement-Modification-Example
 */
class MEPAPI_EXPORT ModifiableElementBase : public ElementBase {

protected:
	/**
	 * @brief Constructs a ModifiableElementBase with the IElementBaseImpl.
	 * @param impl The element base implementation.
	 */
	ModifiableElementBase (std::shared_ptr<Impl::IElementBaseImpl> impl);
	~ModifiableElementBase ();

public:
	class Modifier;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT ModifiableElementBase::Modifier : public ACAPI::ModifierBase {
	ModifiableElementBase& parent;

protected:
	/**
	 * @brief Constructs a Modifier with the parent ModifiableElementBase.
	 * @param parent The parent ModifiableELementBase.
	 */
	Modifier (ModifiableElementBase& parent);
	
	/**
	 * @brief Finalizes the modifications.
	 */
	void FinalizeModification () override;

public:
	~Modifier ();

	friend ModifiableElementBase;

	/**
	 * @brief Sets the anchor point of the ModifiableElement.
	 * @param anchorPoint The value to be set.
	 */
	void	SetAnchorPoint (const API_Coord3D& anchorPoint);

	/**
	 * @brief Sets the orientation of the ModifiableElement.
	 * @param orientation The value to be set, which contains a vector of direction and rotation.
	 */
	void	SetOrientation (const MEP::Orientation& orientation);

	/**
	 * @brief Sets the referenced library part of the ModifiableElement.
	 * @param libraryPartId The main GUID of the library part.
	 */
	void	SetObjectId (const API_Guid& libraryPartId);
};


template <typename ModifierFunc>
Result<void> ModifiableElementBase::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::ModifiableElementBase;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_MODIFIABLE_ELEMENTBASE_HPP*/