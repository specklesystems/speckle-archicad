#ifndef GS_ACAPI_ELEMENT_OPENINGDEFAULT_HPP
#define GS_ACAPI_ELEMENT_OPENINGDEFAULT_HPP


#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/ElementDefault.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/UniqueID.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::Element {

namespace Impl { class OpeningDefaultImpl; }


class OpeningFloorPlanParameters;
class ModifiableOpeningFloorPlanParameters;
class OpeningExtrusionParameters;
class ModifiableOpeningExtrusionParameters;

/**
 * @brief The ElementDefault contains the necessary non-geometric data for creating a MEP element.
 * @ingroup Element
 * @since Archicad 29
 */
class ARCHICADAPI_EXPORT OpeningDefault final : public ACAPI::ElementDefault {
protected:
	/**
	 * @brief Constructs an OpeningDefault with the given element default implementation.
	 * @param impl The OpeningDefault implementation.
	 */
	OpeningDefault (std::shared_ptr<Impl::OpeningDefaultImpl> impl);

	/**
	 * @brief Creates an OpeningDefault with the given token.
	 * @param token The given token.
	 * @return The result of the creation with the created OpeningDefault.
	 */
	static Result<OpeningDefault>	Create (const API_Token& token);

	friend class ACAPI::Impl::ObjectCreator;
	friend Result<OpeningDefault>	CreateOpeningDefault ();
	friend ARCHICADAPI_EXPORT Result<OpeningDefault> CreateOpeningDefault (const ACAPI::ElementDefault& defaultElem);

public:

	/**
	* @brief Puts an opening in an element at a given point.
	* @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	* @details If the input point is not on the parent element's surface, the opening will be placed on the closest point on the surface, projected perpendicularly.
	* @param parentElemId The parent element's unique ID.
	* @param inputPoint The point where the opening will be placed.
	* @return If executed with success, returns the newly placed opening's unique ID, otherwise Error.
	*/
	Result<UniqueID>			Place (const UniqueID& parentElemId, const API_Coord3D& inputPoint) const;


	/**
	* @brief Puts an opening in an element at a given point.
	* @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	* @details If the input point is not on the parent element's surface, the opening will be placed on the closest point on the surface, projected perpendicularly.
	* @details The created opening will be custom, and use the polygon given as parameter even if the default was set to rectangular or circular.
	* @param parentElemId The parent element's unique ID.
	* @param inputPoint The point where the opening will be placed.
	* @param polygon The shape of the opening.
	* @return If executed with success, returns the newly placed opening's unique ID, otherwise Error.
	*/
	Result<UniqueID>			PlacePolygonal (const UniqueID& parentElemId, const API_Coord3D& inputPoint, const Geometry::Polygon2D& polygon) const;

	class Modifier;

	/** @return Returns the floorplan parameters of the opening. */
	OpeningFloorPlanParameters	GetFloorPlanParameters () const;

	/** @return Returns the extrusion geometry of the opening. */
	OpeningExtrusionParameters	GetExtrusionParameters () const;

	/**
	 * @brief Executes the given modifier scope in a NotUndoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);
};


/**
 * @details It represents a modifiable OpeningDefault
 * @since Archicad 29
 * @ingroup Element
 */
class ARCHICADAPI_EXPORT OpeningDefault::Modifier final : public ACAPI::ModifierBase
{
protected:
	friend class OpeningDefault;
	/**
	 * @brief Constructs a Modifier with the given parent OpeningDefault.
	 * @param parent The parent  OpeningDefault.
	 */
	Modifier (OpeningDefault& parent);
public:
	virtual ~Modifier ();

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

private:
	OpeningDefault&		parent;
};


template<class ModifierFunc>
Result<void> OpeningDefault::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}


/**
 * @brief Creates an OpeningDefault
 * @ingroup Element
 * @since Archicad 29
 * @return If able, returns a copy of Archicad's current Opening of the Opening tool, otherwise Error.
 */
inline Result<OpeningDefault> CreateOpeningDefault ()
{
	return OpeningDefault::Create (ACAPI_GetToken ());
}


/**
 * @brief Creates an OpeningDefault from the given base element default.
 * @param defaultElem The base element default which will be converted to an OpeningDefault.
 * @ingroup Element
 * @since Archicad 29
 * @return If the given base element default refers to an Opening, returns a copy of the OpeningDefault, otherwise Error.
 */
ARCHICADAPI_EXPORT Result<OpeningDefault> CreateOpeningDefault (const ACAPI::ElementDefault& defaultElem);

} // ACAPI::Element


#endif /*GS_ACAPI_ELEMENT_OPENINGDEFAULT_HPP*/