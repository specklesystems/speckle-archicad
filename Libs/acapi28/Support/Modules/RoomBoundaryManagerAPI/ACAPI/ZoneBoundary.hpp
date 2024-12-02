#ifndef GS_ACAPI_ZONEBOUNDARY_HPP
#define GS_ACAPI_ZONEBOUNDARY_HPP

#include "ZoneBoundaryQueryAPIExport.hpp"

// from ArchicadAPI
#include "ACAPI/Object.hpp"

// from ModelerAPI
#include "ModelMeshBody.hpp"
#include "Polygon.hpp"


namespace ACAPI::Impl { class ObjectCreator; }
namespace ACAPI::Impl { class ZoneBoundary; }


namespace ACAPI {
namespace v1 {


/**
 * @ingroup Element
 * @since Archicad 27
 * @brief Represents a boundary between a Zone and another element. A boundary is the intersection of the coplanar surfaces
 * 		  of the Zone body and the boundary element. The surface will be split into multiple boundaries if it is connected to
 * 		  multiple Zones, one boundary for each Zone. A boundary can be either internal or external. An internal boundary
 * 		  is between two Zones, otherwise it is external.
 */
class ZONEBOUNDARYQUERYAPI_EXPORT ZoneBoundary : public Object {

	ZoneBoundary (std::shared_ptr<Impl::ZoneBoundary>);
	friend class Impl::ObjectCreator;

public:

	/** @return Returns the unique identifier of the connected element. */
	API_Guid				GetElemId () const;

	/**
	 * @return Returns the unique identifer of the other Zone the element connects to if the boundary is internal.
	 * 		   Returns APINULLGuid if the boundary is external.
	 * 		   Please note that this boundary does not represent the boundary of the element with the other Zone.
	 */
	API_Guid				GetNeighbouringZoneId () const;

	/** @return Returns wheter the boundary is an external one. */
	bool					IsExternal () const;

	/** @return Returns the body in which the polygon of the boundary can be interpreted. */
	ModelerAPI::MeshBody	GetBody () const;

	/** @return Returns the polygon of the boundary. */
	ModelerAPI::Polygon		GetPolygon () const;

	/** @return Returns the area of the polygon of the boundary. */
	double					GetArea () const;
};


} // namespace v1

using namespace v1;

} // namespace ACAPI


#endif /* GS_ACAPI_ZONEBOUNDARY_HPP */
