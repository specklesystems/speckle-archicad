#ifndef GS_ACAPI_ELEMENT_OPENING_HPP
#define GS_ACAPI_ELEMENT_OPENING_HPP


#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/ElementBase.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"


namespace ACAPI::Element {

namespace Impl { class OpeningImpl; }

class OpeningFloorPlanParameters;
class ModifiableOpeningFloorPlanParameters;
class OpeningExtrusionParameters;
class ModifiableOpeningExtrusionParameters;
class OpeningGeometry;
class ModifiableOpeningGeometry;

/**
 * @details It is a representation of Opening element.
 * @since Archicad 29
 * @ingroup Element
 */
class ARCHICADAPI_EXPORT Opening final : public ACAPI::ElementBase {
protected:
	/**
	 * @brief Constructs an Opening with an opening implementation.
	 * @param impl The opening implementation.
	 */
	Opening (std::shared_ptr<Impl::OpeningImpl> impl);

public:
	class Modifier;

	~Opening ();

	/** @return Checks if the element still exists.	*/
	bool Exists () const;

	/** @return Returns the floorplan parameters of the opening. */
	OpeningFloorPlanParameters	GetFloorPlanParameters () const;

	/** @return Returns the extrusion parameters of the opening. */
	OpeningExtrusionParameters	GetExtrusionParameters () const;

	/** @return Returns the extrusion geometry of the opening. */
	OpeningGeometry				GetOpeningGeometry () const;

	/**
	 * @brief Returns an Opening.
	 * @param uniqueId The UniqueID of the requested Opening.
	 * @return If the uniqueId belongs to an Opening, returns the object associated to it, otherwise Error.
	 */
	static Result<Opening>	Get (const UniqueID& uniqueId);

	/** @return Returns the ID of the opening's parent element if it has any, otherwise Error. */
	Result<UniqueID>		GetParentElement () const;

	/** @return Returns the IDs of elements cut by the Opening. Parent element's ID will be included in the list as well. */
	std::vector<UniqueID>	GetCutElements () const;

	/**
	* @brief Returns all Openings connected to the specified element.
	* @param uniqueId The ID of the element whose connected openings you wish to query.
	* @param token The token used by the implementation.
	* @return Return the IDs of Openings that cut the element specified in the uniqueId, or returns error:
	* 			- if the ID points to a non-existing element;
	*			- if element's type specified by the ID can't be cut by Opening.
	*/
	static Result<std::vector<UniqueID>>	GetConnectedOpenings (const UniqueID& uniqueId, const API_Token& token);

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


/**
 * @details It represents a modifiable Opening element.
 * @since Archicad 29
 * @ingroup Element
 */
class ARCHICADAPI_EXPORT Opening::Modifier final : public ACAPI::ModifierBase
{
	Opening& parent;
protected:
	friend class Opening;
	/**
	 * @brief Constructs a Modifier with the given Opening parent.
	 * @param parent The parent Opening.
	 */
	Modifier (Opening& parent);

public:
	~Modifier ();

	/**
	 * @brief Gives access to OpeningFloorPlanParameters for modification
	 * @return Returns ModifiableOpeningFloorPlanParameters 
	 */
	ModifiableOpeningFloorPlanParameters GetFloorPlanParameters ();

	/**
	* @brief Gives access to OpeningExtrusionParameters for modification
	* @return Returns ModifiableOpeningExtrusionParameters
	*/
	ModifiableOpeningExtrusionParameters GetExtrusionParameters ();

	/**
	* @brief Gives access to OpeningGeometry for modification
	* @return Returns ModifiableOpeningGeometry
	*/
	ModifiableOpeningGeometry			GetOpeningGeometry ();

	/**
	* @brief Changes the Opening's parent element.
	* @param newParentElementId The ID of the element Opening will use as it's new parent element.
	* @return Returns nothing if the operation was successful, or returns error:
	*			- if the ID points to a non-existing element;
	*			- if element's type specified by the ID can't be cut by Opening.
	*/
	Result<void>			ChangeParentElement (const UniqueID& newParentElementId);

	/**
	* @brief Cuts an element by this opening.
	* @param elementToCutId The ID of the element that will be cut by this opening.
	* @return Returns nothing if the operation was successful, or returns error:
	*			- if the ID points to a non-existing element;
	*			- if element's type specified by the ID can't be cut by Opening.
	*/
	Result<void>			AddCutElement (const UniqueID& elementToCutId);

	/**
	* @brief The opening will no longer cut this element. Opening will be deleted it the specified element is the opening's parent element!
	* @param elementToRemoveConnectionId The ID of the element that will no longer be cut by this opening.
	* @return Returns nothing if the operation was successful, or returns error:
	*			- if the ID points to a non-existing element;
	*			- if element's type specified by the ID can't be cut by Opening.
	*/
	Result<void>			RemoveCutElement (const UniqueID& elementToRemoveConnectionId);
};


template <typename ModifierFunc>
Result<void> Opening::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}

} // ACAPI::Element


#endif /*GS_ACAPI_ELEMENT_OPENING_HPP*/