// *********************************************************************************************************************
// API definitions - managing 3D models
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_3D_H)
#define	APIDEFS_3D_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Base.h"
#include "APIdefs_Elements.h"
#include "APIdefs_Attributes.h"


// --- Compiler settings -----------------------------------------------------------------------------------------------


// --- Type definitions	------------------------------------------------------------------------------------------------

// =============================================================================
// 3D component types and common header
//
// =============================================================================

/**
 * @brief This is the enumeration of the applicable types of 3D components.
 * @enum API_3DTypeID
 * @ingroup  ModelAccess
 * @remarks These component types are usable in the typeID field of @ref API_3D_Head structure.
 */
typedef enum {													// 3D component types
	API_Zombie3DID					= 0,

	API_BodyID,

	API_PgonID,
	API_PedgID,
	API_EdgeID,
	API_VertID,
	API_VectID,

	API_UmatID,
	API_LghtID
} API_3DTypeID;


/**
 * @brief Common header for the 3D components.
 * @struct API_3D_Head
 * @ingroup  ModelAccess
 * @remarks This structure specify the type and the database index of a 3D component.
 * 			You can get a 3D component by the @ref ACAPI_ModelAccess_GetComponent function. Give the type and index information in the appropriate fields of the header of an @ref API_Component3D structure, and you will get its other parameters.
 * @par Example
 * 		@snippet API_Examples.cpp API_3D_Head-Example-Snippet
 */
struct API_3D_Head {

/**
 * @brief Identifies the type of the component.
 * @var typeID
 */
	API_3DTypeID					typeID;

/**
 * @brief The @c index field gives the current database index of the given component. Note that this number is not constant for a particular element through the whole life of the project element index.
 * @var index
 */
	Int32							index;

/**
 * @brief Gives the internal element index plus one for a body; output only parameter for @ref API_BodyType. It can be used to get the (u,v) texture coordinates with @ref ACAPI_ModelAccess_GetTextureCoord.
 * @var elemIndex
 */
	Int32							elemIndex;

/**
 * @brief Gives the internal body index plus one for a body; output only parameter for @ref API_BodyType. It can be used to get the (u,v) texture coordinates with @ref ACAPI_ModelAccess_GetTextureCoord.
 * @var bodyIndex
 */
	Int32							bodyIndex;

};



// =============================================================================
// 3D Body
//
// =============================================================================

#define APIBody_MulRtxt				0x0100						// more textures are referenced by its materials
#define APIBody_MulColor			0x0200						// more colors referenced by its edges
#define APIBody_MulMater			0x0400						// more materials referenced by its polygons
#define APIBody_Closed				0x0001						// its geometry is closed
#define APIBody_Curved				0x0002						// it has smooth polygons

/**
 * @brief Representation of a 3D body.
 * @struct API_BodyType
 * @ingroup  ModelAccess
 * @remarks The 3D representation of a particular element is based on the @ref API_BodyType structure.
 * 			One element may hold one or more bodies to describe the 3D geometry.
 * 			Generally, a body is built up from several vertices, edges, polygons, and normal vectors.
 * 			This data structure gives you the number of internal components, some status bits, surface properties, and a global transformation matrix.
 * 			You also get a reference to the parent element through an @ref API_Elem_Head structure.
 * 			You can get a body component just after you call @ref ACAPI_ModelAccess_GetComponent with the appropriate body component.
 * 			Then you can obtain edges, pgons, vertices etc. of that body.
 * 			Use indices from 1 to `nPgon`, `nPedg`, `nEdge`, `nVert`, or `nVect` in the parameter of @ref ACAPI_ModelAccess_GetComponent function to get a subcomponent.
 * 			The status field specifies some properties of the body. You can use the bitwise-OR operator (|) to combine any of the following constants:
 * 			- @c APIBody_MulRtxt : more textures are referenced by its materials.
 * 			- @c APIBody_MulColor : more than one colors referenced by its edges.
 * 			- @c APIBody_MulMater : more than one materials referenced by its polygons.
 * 			- @c APIBody_Closed : its geometry is closed.
 * 			- @c APIBody_Curved : it has smooth polygons.
 */
struct API_BodyType {

/**
 * @brief Header information of this component. This specifies the type and database index.
 * @var head
 */
	API_3D_Head						head;

/**
 * @brief The floorplan element the body has been converted from.
 * @var parent
 */
	API_Elem_Head					parent;


/**
 * @brief The properties of the body.
 * @var status
 */
	Int32							status;

/**
 * @brief Refers to the default color of the body edges.
 * @var color
 */
	short							color;
	short							filler_0[3];

/**
 * @brief Refers to the default material of the body polygons.
 * @var iumat
 */
	Int32							iumat;

/**
 * @brief Minimum of the bounding box in X direction.
 * @var xmin
 */
	float							xmin;

/**
 * @brief Minimum of the bounding box in Y direction.
 * @var ymin
 */
	float							ymin;

/**
 * @brief Minimum of the bounding box in Z direction.
 * @var zmin
 */
	float							zmin;

/**
 * @brief Maximum of the bounding box in X direction.
 * @var xmax
 */
	float							xmax;

/**
 * @brief Maximum of the bounding box in Y direction.
 * @var ymax
 */
	float							ymax;

/**
 * @brief Maximum of the bounding box in Z direction.
 * @var zmax
 */
	float							zmax;


/**
 * @brief Number of polygons in the body.
 * @var nPgon
 */
	Int32							nPgon;

/**
 * @brief Number of edge references in the body.
 * @var nPedg
 */
	Int32							nPedg;

/**
 * @brief Number of edges in the body.
 * @var nEdge
 */
	Int32							nEdge;

/**
 * @brief Number of vertices in the body.
 * @var nVert
 */
	Int32							nVert;

/**
 * @brief Number of normal vectors in the body.
 * @var nVect
 */
	Int32							nVect;
	Int32							filler_1;


/**
 * @brief The base transformation matrix.
 * @var tranmat
 */
	API_Tranmat						tranmat;					// the base transformation matrix

};


// =============================================================================
// 3D Polygon
//
// =============================================================================

#define APIPgon_Invis				0x0001						// invisible polygon
#define APIPgon_Curved				0x0002						// polygon of a curved surface
#define APIPgon_Concav				0x0010						// concave polygon
#define APIPgon_PHole				0x0020						// polygon with holes
#define APIPgon_HolesCnv			0x0040						// hole(s) are convex
#define APIPgon_Complex				0x0030						// the polygon is concave or with holes

/**
 * @brief Representation of a 3D Polygon.
 * @struct API_PgonType
 * @ingroup  ModelAccess
 * @remarks Accessing polygons must be base on bodies. First you should get a body by @ref ACAPI_ModelAccess_GetComponent and just after is obtainable its polygons. A polygon component consist of directed edges.
 * 			You can get those using `fpedg`, `lpedg` index range. These indices refer to @ref API_PedgType components, which can be
 * 			use to retrieve the edges of the given polygon. It may occure that `fpedg >lpedg`, that means the polygon has no
 * 			edge references. Note that negative pedg value in @ref API_PedgType means opposite direction. The `ivect` is an index
 * 			to an @ref API_VectType component. This is the normal vector of this polygon. If `ivect` is negative, the direction of
 * 			the normal vector is the opposite of the stored one. The `status` field specifies some properties of the polygon.
 * 			You can use the bitwise-OR operator (|) to combine any of the following constants:
 * 			- @c APIPgon_Invis : invisible polygon,
 * 			- @c APIPgon_Curved : polygon of a curved surface,
 * 			- @c APIPgon_Concav : concave polygon,
 * 			- @c APIPgon_PHole : polygon with holes,
 * 			- @c APIPgon_HolesCnv : hole(s) are convex,
 * 			- @c APIPgon_Complex : the polygon is concave or with holes.
 */
typedef	struct {

/**
 * @brief Header information of this component. This specifies the type and database index.
 * @var head
 */
	API_3D_Head						head;


/**
 * @brief Information about the properties of polygon.
 * @var status
 */
	Int32							status;

/**
 * @brief Refers to the material of the polygon.
 * @var iumat
 */
	Int32							iumat;

/**
 * @brief Internal use.
 * @var irtxt
 */
	Int32							irtxt;

/**
 * @brief Refers to the polygon's normal vector (negative: use opposite direction). It is an index of a vector you can get by @ref ACAPI_ModelAccess_GetComponent.
 * @var ivect
 */
	Int32							ivect;

/**
 * @brief Index of the first polygon contour edge.
 * @var fpedg
 */
	Int32							fpedg;

/**
 * @brief Index of the last polygon contour edge.
 * @var lpedg
 */
	Int32							lpedg;

} API_PgonType;


// =============================================================================
// 3D Edge reference
//
// =============================================================================

/**
 * @brief Representation of a 3D edge reference.
 * @struct API_PedgType
 * @ingroup  ModelAccess
 * @remarks The edges in the 3D model are stored in a list. The value of `pedg` field is an index to the items
 * 			of that list. If you go through the edge reference list from `fpedg` to `lpedg`, you can obtain the edges of a
 * 			polygon. (The `fpedg` and `lpedg` are available in the @ref API_PgonType record, after you got a polygon of a body by
 * 			calling @ref ACAPI_ModelAccess_GetComponent function.) The `pedg` field is an index of an @ref API_EdgeType structure which
 * 			represents an edge. The orientation of the edge list is counterclockwise (mathematical positive), if you are
 * 			looking at it from the outside of the body. The orientation of the holes is opposite to that of the parent
 * 			polygon. If `pedg` is negative, it means the referred edge direction is reversed. If `pedg` is zero, it means a
 * 			contour end; a hole follows.
 */
struct API_PedgType {

/**
 * @brief Header information of this component. This specifies the type and database index.
 * @var head
 */
	API_3D_Head						head;


/**
 * @brief Edge reference. Negative value means opposite direction. Zero value starts a new hole.
 * @var pedg
 */
	Int32							pedg;
	Int32							filler_1;

};


// =============================================================================
// 3D Edge
//
// =============================================================================

#define APIEdge_Invis				0x0001						// invisible edge
#define APIEdge_Curved				0x0002						// edge of a curved surface

/**
 * @brief Representation of a 3D edge.
 * @struct API_EdgeType
 * @ingroup  ModelAccess
 * @remarks Polygons are lists of edges with orientation, including the indices of the edges. One edge may belong to 0
 * 			to 2 polygons. Its indices are included in `pgon1`, `pgon2`. In the case of a side or single line, the missing
 * 			polygon is signed with a -1 index. An edge has two endpoints, indexed by `vert1`, and `vert2`. Note that in the
 * 			case of closed bodies, the polygon's orientation is correct if the edge has different prefixes in the edge list
 * 			of the two polygons. Accessing edges are based on a body. First, you must get a body by @ref ACAPI_ModelAccess_GetComponent,
 * 			and then its components are obtainable.
 */
struct API_EdgeType {

/**
 * @brief Header information of this component. This specifies the type and database index.
 * @var head
 */
	API_3D_Head						head;


/**
 * @brief Information about the edge properties.
 * @var status
 */
	Int32							status;
	short							filler_1;

/**
 * @brief Refers to the color of the edge.
 * @var color
 */
	short							color;

/**
 * @brief Vertex index of one edge endpoint.
 * @var vert1
 */
	Int32							vert1;

/**
 * @brief Vertex index of the other edge endpoint.
 * @var vert2
 */
	Int32							vert2;

/**
 * @brief Index of one of the neighbouring polygons.
 * @var pgon1
 */
	Int32							pgon1;

/**
 * @brief Index of the other neighbouring polygon.
 * @var pgon2
 */
	Int32							pgon2;

};


// =============================================================================
// 3D Vertex
//
// =============================================================================

/**
 * @brief Representation of a 3D vertex.
 * @struct API_VertType
 * @ingroup  ModelAccess
 * @remarks A node in the x-y-z space, defined by its 3 coordinates.
 * 			The vertices are the endpoints of the edges. In the @ref API_EdgeType structure the vert1, vert2 fields refers to an @ref API_VertType component by index. With these indices can be used to retrieve the given vertices from the database.
 * 			Accessing vertices are based on a body. First you must get a body by @ref ACAPI_ModelAccess_GetComponent and just after is obtainable its components.
 */
struct API_VertType {

/**
 * @brief Header information of this component. This specifies the type and database index.
 * @var head
 */
	API_3D_Head						head;


/**
 * @brief The x coordinate of the point in the model space.
 * @var x
 */
	double							x;

/**
 * @brief The y coordinate of the point in the model space.
 * @var y
 */
	double							y;

/**
 * @brief The z coordinate of the point in the model space.
 * @var z
 */
	double							z;

};


// =============================================================================
// 3D Vector
//
// =============================================================================

/**
 * @brief Representation of a 3D normal vector.
 * @struct API_VectType
 * @ingroup  ModelAccess
 * @remarks This structure is used to describe a normal vector of a polygon. If you get a polygon of a body,
 * 			you will get an index (`ivect` field of @ref API_PgonType structure) to an @ref API_VectType structure.
 * 			Use this index in the `head.index` field to get the normal vector of that polygon.
 * 			Note: In the case of closed bodies, they point from the inside to the outside of the body. Normal vectors
 * 			of an open body must point to the same side of the body.
 */
struct API_VectType {

/**
 * @brief Header information of this component. This specifies the type and database index.
 * @var head
 */
	API_3D_Head						head;


/**
 * @brief The x coordinate of the point in the model space.
 * @var x
 */
	double							x;

/**
 * @brief The y coordinate of the point in the model space.
 * @var y
 */
	double							y;

/**
 * @brief The z coordinate of the point in the model space.
 * @var z
 */
	double							z;

};


// =============================================================================
// 3D Light
//
// =============================================================================

/**
 * @brief Possible types of a 3D light source.
 * @enum API_LghtSouID
 * @ingroup  ModelAccess
 * @remarks These identifiers are usable in @ref API_LghtType type field.
 */
typedef enum {
	APILght_DistantID,
	APILght_DirectionID,
	APILght_SpotID,
	APILght_PointID,
	APILght_SunID,
	APILght_EyeID

} API_LghtSouID;

#define APILight_CastShadow			0x0001

/**
 * @brief Representation of a 3D light source.
 * @struct API_LghtType
 * @ingroup  ModelAccess
 * @remarks A light source radiates `lightRGB` colored light from the local origin (`posx`, `posy`, `posz`)
 * 			along the direction vector ( `dirx`, `diry`, `dirz`). The light is projected parallel to the
 * 			direction vector from a point or circle source. (See figure below!) It has its maximum intensity within the
 * 			alpha-angle frustum of a cone and falls to zero at the beta-angle frustum of a cone. This falloff is
 * 			controlled by the `afall` parameter. (Zero gives the light a sharp edge, higher values mean that the
 * 			transition is smoother.) The effect of the light is limited along the axis by the `dist1` and `dist2`
 * 			clipping values. The `dfall` parameter controls the decrease in intensity depending on the distance. (Zero
 * 			value means a constant intensity, bigger values are used for stronger falloff.) The type of light source can be
 * 			one of the `@ref API_LghtSouID` members. The status must be `APILight_CastShadow` if you want Archicad to calculate
 * 			shadow casting from this light source, or else set it zero.
 * @image html LightSource.png "Light source" width=50%
 */
struct API_LghtType {

/**
 * @brief Header information of this component. This specifies the type (@c API_LghtID) and database index.
 * @var head
 */
	API_3D_Head						head;


/**
 * @brief The type of the light
 * @var type
 */
	API_LghtSouID					type;

/**
 * @brief The light casts shadow or not.
 * @var status
 */
	Int32							status;
	Int32							filler_1[2];

/**
 * @brief The color of the light source.
 * @var lightRGB
 */
	API_RGBColor					lightRGB;

/**
 * @brief X coordinate of the local origin of the light.
 * @var posx
 */
	double							posx;

/**
 * @brief Y coordinate of the local origin of the light.
 * @var posy
 */
	double							posy;

/**
 * @brief Z coordinate of the local origin of the light.
 * @var posz
 */
	double							posz;

/**
 * @brief X component of the direction vector of the light.
 * @var dirx
 */
	double							dirx;

/**
 * @brief Y component of the direction vector of the light.
 * @var diry
 */
	double							diry;

/**
 * @brief Z component of the direction vector of the light.
 * @var dirz
 */
	double							dirz;

/**
 * @brief The radius of the light source.
 * @var radius
 */
	double							radius;

/**
 * @brief The cosine of the angle of the cone within the light has its maximum intensity.
 * @var cosa
 */
	double							cosa;

/**
 * @brief The cosine of the angle of the cone within the intensity falls to zero.
 * @var cosb
 */
	double							cosb;

/**
 * @brief The falloff control of the light (decrease of intensity depending on the cone angle).
 * @var afall
 */
	double							afall;

/**
 * @brief The clipping values along the X axis (with @c dist2).
 * @var dist1
 */
	double							dist1;

/**
 * @brief The clipping values along the X axis (with @c dist1).
 * @var dist2
 */
	double							dist2;

/**
 * @brief Controls the fall-of of intensity depending on the distance.
 * @var dfall
 */
	double							dfall;

};


// =============================================================================
// 3D Material
//
// =============================================================================

/**
 * @brief Representation of a 3D material.
 * @struct API_UmatType
 * @ingroup  ModelAccess
 * @remarks This structure contains the properties of a material. These properties are described in @ref API_MaterialType structure.
 * 			Basically there are two source of materials. First is the globally stored, the second is when they are come from an object's GDL script. In case of GDL materials the index in the header is 0. In case of global material the value of the header is than 0. In both cases the parameters of the material can be obtained from the mater field of this structure.
 * 			The following 3D components can refer to material: @ref API_PgonType, @ref API_BodyType.
 */
struct API_UmatType {

/**
 * @brief Header information of this component. This specifies the type and database index.
 * @var head
 */
	API_3D_Head						head;


/**
 * @brief The definition of the material.
 * 		  the @c head.index is @c 0 in case of GDL materials; and @c n in case of global material reference
 * @var mater
 */
	API_MaterialType				mater;

};


// =============================================================================
// General component
//
// =============================================================================

/**
 * @brief General representation of a 3D component.
 * @union API_Component3D
 * @ingroup  ModelAccess
 * @remarks This structure is used to work with 3D components of the actual database. The definition of a 3D component is described in this structure, which is in fact a union of all component types.
 * 			Before you try to understand how the 3D model corresponds to the API structures, please read carefully the Primitive Elements chapter in the GDL Reference Manual.
 * 			The 3D geometry itself is described by the @ref API_PgonType, @ref API_PedgType, @ref API_EdgeType, @ref API_VertType and @ref API_VectType structures.
 * 			Negative index referring to an edge or a normal vector indicates that the component should be interpreted reversed. In this case require the component using the absolute value of the index, but consider the edge directing from the second vertex to the first one, or when retrieving a normal vector, invert its coordinates.
 * 			The 3D representation also owns a common pool of the surface materials. The polygon instances of the geometry description refer to these materials by indices. One surface definition is described by the @ref API_UmatType structure. Surface materials may come from two sources. The list of materials contains all the global material attributes which are referenced by any polygon of the 3D geometry. Materials may be defined in GDL scripts also.
 * 			Elements placed with the light tool on the floorplan may contain light emissions, defined via GDL scripts. All of the light sources present in the 3D geometry are described with the @ref API_LghtType structure.
 */
union API_Component3D {

/**
 * @brief The common header which specify the type and database index of the given component.
 * @var header
 */
	API_3D_Head						header;


/**
 * @brief Parameters of a body type component.
 * @var body
 */
	API_BodyType					body;


/**
 * @brief Parameters of a polygon type component.
 * @var pgon
 */
	API_PgonType					pgon;

/**
 * @brief Edge reference. Negative value means opposite direction, zero index identifies a new hole in a polygon
 * @var pedg
 */
	API_PedgType					pedg;

/**
 * @brief Parameters of an edge type component.
 * @var edge
 */
	API_EdgeType					edge;

/**
 * @brief Parameters of a vertex.
 * @var vert
 */
	API_VertType					vert;

/**
 * @brief Parameters of a vector type component.
 * @var vect
 */
	API_VectType					vect;


/**
 * @brief Parameters of a light type component.
 * @var lght
 */
	API_LghtType					lght;

/**
 * @brief Parameters of a surface material.
 * @var umat
 */
	API_UmatType					umat;

};


// =============================================================================
// API_PolygonExt
//
// =============================================================================

/** @brief Representation of a 2D polygon and the 3D transformation plane
	@struct API_PolygonExt
	@ingroup Dialog
	@remarks Refer to the @ref API_Polygon, @ref API_ElementMemo and @ref API_Plane3D structures for more details.
*/

struct API_PolygonExt {

/**	@brief Representation of the two dimensional polygon.
	@var polygon
*/
	API_Polygon						polygon;

/**	@brief Contains the geometry data of the polygon.
	@var polygonData
*/
	API_ElementMemo					polygonData;

/**	@brief Plane which transforms the points of the polygon into 3D coordinates. 
	@var plane
*/
	API_Plane3D						plane;
};


typedef GS::HashTable<GS::Pair<API_Guid, API_Guid>, GS::Array<API_PolygonExt>> API_ElementConnectionTable;


// ---------------------------------------------------------------------------------------------------------------------

#endif
