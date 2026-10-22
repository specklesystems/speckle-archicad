#ifndef GS_ACAPI_ELEMENT_OPENING_EXTRUSIONPARAMETERS_HPP
#define GS_ACAPI_ELEMENT_OPENING_EXTRUSIONPARAMETERS_HPP


// ARCHICADAPI
#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

#include <optional>


namespace ACAPI::Element {


/**
* @brief Type of The opening polygon
* @since Archicad 29
* @ingroup Element
*/
enum class ShapeType {
	Rectangular,	/**< The base polygon of the opening is rectangular. Suitable for most door and window openings. */
	Circular,		/**< The base polygon of the opening is circular. Commonly used for round windows or other circular openings. */
	Polygonal		/**< The base polygon of the opening is polygonal, allowing for custom shapes beyond simple rectangles and circles. */
};


/**
* @brief Orientation of the opening in host element
* @since Archicad 29
* @ingroup Element
*/
enum class Constraint {
	ForcedVertical,		/**< The opening is oriented vertically, regardless of the host element's orientation. */
	ForcedHorizontal,	/**< The opening is oriented horizontally, regardless of the host element's orientation. */
	Aligned,			/**< The opening's orientation aligns with the host element's orientation. */
	Free				/**< The opening's orientation is not constrained and can be freely defined. Not usable for OpeningDefault */
};


/**
* @brief Type of the extrusion body
* @ingroup Element
* @since Archicad 29
*/
enum class LimitType {
	Infinite,			/**< The extrusion extends infinitely in both directions. */
	Finite,				/**< The extrusion has a defined length, starting and ending within the host element. */
	HalfInfinite		/**< The extrusion starts within the host element and extends infinitely in one direction. */
};


/**
* @brief Relation between the width and height value
* @ingroup Element
* @since Archicad 29
*/
enum class LinkedStatus {
	Linked,				/**< The width and height of the opening are linked, changing one will change the other. */
	NotLinked			/**< The width and height of the opening are independent, changing one does not affect the other. */
};


namespace Impl { class OpeningExtrusionParametersBase; }

class Opening;
class OpeningDefault;


/**
* @details It represents the parameters of the extrusion body of an Opening element or an OpeningDefault element.
* @since Archicad 29
* @ingroup Element
*/
class ARCHICADAPI_EXPORT OpeningExtrusionParameters : public ACAPI::Object {
protected:
	friend class Opening;
	friend class OpeningDefault;
	/**
	* @brief Constructs an OpeningExtrusionParameters with an OpeningExtrusionParameters implementation.
	* @param impl The OpeningExtrusionParameters implementation.
	*/
	OpeningExtrusionParameters (std::shared_ptr<Impl::OpeningExtrusionParametersBase> impl);

public:
	//! @cond Doxygen_Suppress
	OpeningExtrusionParameters (const OpeningExtrusionParameters&) = delete;
	OpeningExtrusionParameters (OpeningExtrusionParameters&&) = delete;
	~OpeningExtrusionParameters ();

	OpeningExtrusionParameters& operator= (const OpeningExtrusionParameters&) = delete;
	OpeningExtrusionParameters& operator= (OpeningExtrusionParameters&&) = delete;
	//! @endcond

	/** @return Returns the type of the base polygon */
	ShapeType								GetShapeType () const;

	/** @return Returns the width of the opening, or std::nullopt if the polygon type is not Rectangular or Circular. */
	std::optional<double>					GetWidth () const;

	/** @return Returns the height of the opening, or std::nullopt if the polygon type is not Rectangular or Circular. */
	std::optional<double>					GetHeight () const;

	/** @return Returns if the width and height value are related. */
	std::optional<LinkedStatus>				GetLinkedStatus () const;

	/** @return Returns the orientation of extrusion body in the host element. */
	Constraint								GetConstraint () const;

	/** @return Returns the anchor point of the opening. */
	API_AnchorID							GetAnchor () const;

	/** @return Returns the altitude of the anchor point of the opening or std::nullopt if Constrain is not ForcedHorizontal and not Aligned. */
	std::optional<double>					GetAnchorAltitude () const;

	/** @return Returns the limit type of the extrusion body. */
	LimitType								GetLimitType () const;

	/** @return Returns the extrusion offset from the reference plane if the extrusion body is not Infinite. */
	std::optional<double>					GetExtrusionStartOffset () const;

	/** @return Returns the length of the extrusion body if it is limited on both sides */
	std::optional<double>					GetFiniteBodyLength () const;

	/** @return Returns whether the Surface attribute of the end surface of the extrusion body is overridden. */
	bool									IsEndSurfaceAttributeOverridden () const;

	/** @return Returns the overridden AttributeIndex of the Surface attribute of the end Surface. */
	API_AttributeIndex						GetOverriddenEndSurfaceAttributeIndex () const;

	/** @return Returns whether the Surface attribute of the extrusion surface is overridden. */
	bool									IsExtrusionSurfaceAttributeOverridden () const;

	/** @return Returns the overridden AttributeIndex of the Surface attribute of the Extrusion Surface. */
	API_AttributeIndex						GetOverriddenExtrusionSurfaceAttributeIndex () const;

	/** @return Returns whether the overridden end surface and extrusion surface attributes are linked together. */
	bool									AreOverriddenSurfaceAttributesLinked () const;
};


/**
* @details It represents the modifiable extrusion parameters of an Opening element or an OpeningDefault element.
* @since Archicad 29
* @ingroup Element
*/
class ARCHICADAPI_EXPORT ModifiableOpeningExtrusionParameters final : public OpeningExtrusionParameters {
protected:
	friend class Opening;
	friend class OpeningDefault;

	/**
	* @brief Constructs a ModifiableOpeningExtrusionParameters with an ExtrusionParameters implementation.
	* @param impl The ExtrusionParameters implementation.
	*/
	ModifiableOpeningExtrusionParameters (std::shared_ptr<Impl::OpeningExtrusionParametersBase> impl);

public:
	//! @cond Doxygen_Suppress
	ModifiableOpeningExtrusionParameters (const ModifiableOpeningExtrusionParameters&) = delete;
	ModifiableOpeningExtrusionParameters (ModifiableOpeningExtrusionParameters&&) = delete;
	~ModifiableOpeningExtrusionParameters ();

	ModifiableOpeningExtrusionParameters& operator= (const ModifiableOpeningExtrusionParameters&) = delete;
	ModifiableOpeningExtrusionParameters& operator= (ModifiableOpeningExtrusionParameters&&) = delete;
	//! @endcond

	/**
	* @brief Sets the the polygon type of the opening.
	* @param polygonType The type of the opening polygon.
	*/
	void			SetShapeType (const ShapeType polygonType);

	/**
	* @brief Sets the width of the opening.
	* @param width The width of the opening.
	* @return Returns an error if the polygon type is not Rectangular or Circular, nothing otherwise.
	*/
	Result<void>	SetWidth (double width);
			
	/**
	* @brief Sets the height of the opening.
	* @param height The height of the opening.
	* @return Returns an error if the polygon type is not Rectangular or Circular, nothing otherwise.
	*/
	Result<void>	SetHeight (double height);

	/**
	* @brief Sets the linked status of the width and height value.
	* @param linkedStatus The width and height values are linked or not linked.
	* @return Returns error if failed to set linked status, nothing otherwise.
	*/
	Result<void>	SetLinkedStatus (const LinkedStatus linkedStatus);

	/**
	* @brief Sets the constraint of orientation of the extrusion body in the host element.
	* @param constraint The orientation of the extrusion body.
	* @return Returns error if failed to set constraint, nothing otherwise.
	*/
	Result<void>	SetConstraint (const Constraint constraint);

	/**
	* @brief Sets the anchor point tpye of the opening.
	* @param anchor The anchor point of the opening.
	*/
	void			SetAnchor (const API_AnchorID anchor);

	/**
	* @brief Sets the altitude of the anchor point of the opening.
	* @param anchorAltitude The altitude of the anchor point of the opening.
	* @return Returns error if failed to set anchor altitude, nothing otherwise.
	*/
	Result<void>	SetAnchorAltitude (double anchorAltitude);

	/**
	* @brief Sets the limitation type of the extrusion body.
	* @param limitType The type of the extrusion body.
	*/
	void			SetLimitType (const LimitType limitType);

	/**
	* @brief Sets the offset from the reference plane of the extrusion body.
	* @param extrusionStartOffset The offset from the reference plane of the extrusion body.
	* @return Returns error if failed to set extrusion start offset, nothing otherwise.
	*/
	Result<void>	SetExtrusionStartOffset (double extrusionStartOffset);

	/**
	* @brief Sets the length of the extrusion body if it is finite.
	* @param finiteBodyLength The length of the extrusion body.
	* @return Returns error if failed to set finite body length, nothing otherwise.
	*/
	Result<void>	SetFiniteBodyLength (double finiteBodyLength);

	/**
	* @brief Sets the overridden status of the Surface attribute of the End Surface.
	* @param isOverride Whether the Surface attribute of the End Surface is overridden.
	*/
	void			SetEndSurfaceAttributeOverridden (bool isOverride);

	/**
	* @brief Sets the overridden AttributeIndex of the Surface attribute of the End Surface.
	* @param attributeIndex The overridden AttributeIndex of the Surface attribute of the End Surface.
	*/
	void			SetOverriddenEndSurfaceAttributeIndex (const API_AttributeIndex& attributeIndex);
	
	/**
	 * @brief Sets the overridden status of the Surface attribute of the Extrusion Surface.
	 * @param isOverride Whether the Surface attribute of the Extrusion Surface is overridden.
	 */
	void			SetExtrusionSurfaceAttributeOverridden (bool isOverride);

	/**
	* @brief Sets the overridden AttributeIndex of the Surface attribute of the Extrusion Surface.
	* @param attributeIndex The overridden AttributeIndex of the Surface attribute of the Extrusion Surface.
	*/
	void			SetOverriddenExtrusionSurfaceAttributeIndex (const API_AttributeIndex& attributeIndex);

	/**
	* @brief Sets the linked status of the overridden end-surface and extrusion surface attributes.
	* @param linked Whether the overridden end-surface and extrusion surface attributes are linked together.
	*/
	void			SetOverriddenSurfaceAttributesLinked (bool linked);
};

} // ACAPI::Element


#endif