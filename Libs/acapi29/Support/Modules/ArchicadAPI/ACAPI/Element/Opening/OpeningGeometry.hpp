#ifndef GS_ACAPI_ELEMENT_OPENING_GEOMETRY_HPP
#define GS_ACAPI_ELEMENT_OPENING_GEOMETRY_HPP


// ARCHICADAPI
#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

// std
#include <optional>


namespace ACAPI::Element {

namespace Impl { class OpeningGeometryImpl; }

class Opening;


/**
 * @details It represents the shape and place of the opening.
 * @since Archicad 29
 * @ingroup Element
 */
class ARCHICADAPI_EXPORT OpeningGeometry : public ACAPI::Object {
protected:
	friend class Opening;

	/**
	 * @brief Constructs an OpeningGeometry with an OpeningGeometry implementation.
	 * @param impl The OpeningGeometry implementation.
	 */
	OpeningGeometry (std::shared_ptr<Impl::OpeningGeometryImpl> impl);

public:
	//! @cond Doxygen_Suppress
	OpeningGeometry (const OpeningGeometry&) = delete;
	OpeningGeometry (OpeningGeometry&&) = delete;
	~OpeningGeometry ();

	OpeningGeometry& operator= (const OpeningGeometry&) = delete;
	OpeningGeometry& operator= (OpeningGeometry&&) = delete;
	//! @endcond

	/** @return Returns the polygon describing the openings shape. Returns nullopt if the opening does not use custom shape.	*/
	std::optional<Geometry::Polygon2D>	GetPolygon () const;

	/** @return Returns the coordinates of the openings anchor point. This is the center of its local coordinate system.	*/
	API_Coord3D							GetAnchorPoint () const;

	/** @return Returns the base vector x of the openings local coordinate system.	*/
	API_Vector3D						GetVectorX () const;

	/** @return Returns the base vector y of the openings local coordinate system.	*/
	API_Vector3D						GetVectorY () const;

	/** @return Returns the direction of the opening.	*/
	API_Vector3D						GetExtrusionDirection () const;
};


/**
 * @details It represents the modifiable polygon and place of an Opening element.
 * @since Archicad 29
 * @ingroup Element
 */
class ARCHICADAPI_EXPORT ModifiableOpeningGeometry final : public OpeningGeometry
{
protected:
	friend class Opening;

	/**
	 * @brief Constructs a ModifiableOpeningGeometry with an OpeningGeometry implementation.
	 * @param impl The OpeningGeometry implementation.
	 */
	ModifiableOpeningGeometry (std::shared_ptr<Impl::OpeningGeometryImpl> impl);
public:
	//! @cond Doxygen_Suppress
	ModifiableOpeningGeometry (const ModifiableOpeningGeometry&) = delete;
	ModifiableOpeningGeometry (ModifiableOpeningGeometry&&) = delete;
	~ModifiableOpeningGeometry ();

	ModifiableOpeningGeometry& operator= (const ModifiableOpeningGeometry&) = delete;
	ModifiableOpeningGeometry& operator= (ModifiableOpeningGeometry&&) = delete;
	//! @endcond

	/**
	 * @brief Sets the shape of the opening.
	 * @param polygon The new custom polygon that will be set as the openings shape.
	 */
	void								SetPolygon (const Geometry::Polygon2D& polygon);

	/**
	 * @brief Moves and rotates the opening.
	 * @param transformation The matrix of the transformation. Must contain an ortogonal matrix with no scaling.
	 * @return Returns error in case of bad parameters.
	 */
	Result<void>						Transform (const API_Tranmat& transformation);
};

} // ACAPI::Element


#endif /*GS_ACAPI_ELEMENT_OPENING_GEOMETRY_HPP*/