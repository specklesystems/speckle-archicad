// *********************************************************************************************************************
// API definitions - basic structures
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_BASE_H)
#define	APIDEFS_BASE_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"GSTime.hpp"
#include	"Array.hpp"
#include	"HashTable.hpp"


// --- Compiler settings -----------------------------------------------------------------------------------------------


// --- Constant definitions	--------------------------------------------------------------------------------------------

#define API_NameLen					32
#define API_LongNameLen				128
#define API_UniLongNameLen			256
#define	API_InfoLen					16
#define API_AttrNameLen				256

#define	API_DBCodeLen	 			32
#define	API_DBNameLen				128

#define	API_DefPenWeigth			-1.0

#define	API_UAddParStrLen			256
#define	API_UAddParDescLen			256
#define	API_UAddParNumDescLen		256


// --- Type definitions	------------------------------------------------------------------------------------------------

typedef UInt64						API_GridElemID;


/**
 * @brief Pixel data
 * @struct API_Point
 * @ingroup GeoLocation
 * @remarks An integer type representation of an @ref API_Coord. Expressed in the local coordinates of the window, based on pixels from the top/left corner.
 * 			Refer to the @ref ACAPI_View_CoordToPoint and @ref ACAPI_View_CoordToPoint conversion functions for further details.
 */
struct API_Point {

/**
 * @brief vertical coordinate
 * @var v
 */
	short							v;

/**
 * @brief horizontal coordinate
 * @var h
 */
	short							h;

};
/**
 * @brief A pair of Cartesian (real) coordinates.
 * @ingroup GeoLocation
 * @struct API_Coord
 * @remarks It is a real coordinate. Always expressed in meters, if no other instructions are given in the corresponding documentation.
 * 			For the integer type representation refer to the @ref API_Point structure, or to the @ref ACAPI_View_CoordToPoint and @ref ACAPI_View_CoordToPoint functions for the conversion algorithms.
 */
struct API_Coord {
/**
 * @brief Horizontal coordinate.
 * @var x
 */
	double							x;

/**
 * @brief Vertical coordinate.
 * @var y
 */
	double							y;
};

/**
 * @brief A two dimensional vector.
 * @remarks It is a real coordinate. Always expressed in meters, if no other instructions are given in the corresponding documentation. See also @ref API_Coord.
 */
using API_Vector = API_Coord;

/**
 * @brief Real (Cartesian) 3D coordinates of a three-dimensional space.
 * @ingroup GeoLocation
 * @struct API_Coord3D
 * @remarks It is a real 3D coordinate. Always expressed in meters, if no other instruction is given in the corresponding documentation.
 */
struct API_Coord3D {
/**
 * @brief The x factor.
 * @var x
 */
	double							x;

/**
 * @brief The y factor.
 * @var y
 */
	double							y;

/**
 * @brief The z factor.
 * @var z
 */
	double							z;
};


/**
 * @brief A 3D vector.
 * @remarks It is a real 3D coordinate. Always expressed in meters, if no other instruction is given in the corresponding documentation.. See also @ref API_Coord3D.
 */
using API_Vector3D = API_Coord3D;

/**
 * @brief The local coordinate system of a texture at a given surface point.
 * @struct API_UVCoord
 * @ingroup  ModelAccess
 */
struct API_UVCoord {

/**
 * @brief The u coordinate.
 * @var u
 */
	double							u;

/**
 * @brief The v coordinate.
 * @var v
 */
	double							v;

};


/**
 * @brief Describes the geometry of a 2D line.
 * @struct API_Sector
 * @ingroup Element
 */
struct API_Sector {

/**
 * @brief Start point.
 * @var c1
 */
	API_Coord						c1;

/**
 * @brief End point.
 * @var c2
 */
	API_Coord						c2;

};


/**
 * @brief Rectangular region of the model.
 * @struct API_Box
 * @ingroup View
 * @remarks It is a rectangle in model coordinates. Always expressed in meters, if no other instructions in the corresponding documentation.
 * 			For the integer type representation refer to the @ref API_Rect structure or to the @ref ACAPI_View_CoordToPoint and @ref ACAPI_View_CoordToPoint functions for the conversion algorithms.
 */
struct API_Box {
/**
 * @brief Minimum value of the x coordinate of the box.
 * @var xMin
 */
	double							xMin;

/**
 * @brief Minimum value of the y coordinate of the box.
 * @var yMin
 */
	double							yMin;

/**
 * @brief Maximum value of the x coordinate of the box.
 * @var xMax
 */
	double							xMax;

/**
 * @brief Maximum value of the y coordinate of the box.
 * @var yMax
 */
	double							yMax;

};


/**
 * @brief Rectangular region of the model with Z extent.
 * @struct API_Box3D
 * @ingroup Element
 * @remarks It is a rectangle in model coordinates, with vertical information. Always expressed in meters, if no other instructions in the corresponding documentation.
 */
struct API_Box3D {
/**
 * @brief Minimum value of the x coordinate of the box.
 * @var xMin
 */
	double							xMin;

/**
 * @brief Minimum value of the y coordinate of the box.
 * @var yMin
 */
	double							yMin;

/**
 * @brief Minimum value of the z coordinate of the box.
 * @var zMin
 */
	double							zMin;

/**
 * @brief Maximum value of the x coordinate of the box.
 * @var xMax
 */
	double							xMax;

/**
 * @brief Maximum value of the y coordinate of the box.
 * @var yMax
 */
	double							yMax;

/**
 * @brief Maximum value of the z coordinate of the box.
 * @var zMax
 */
	double							zMax;

};


/**
 * @brief RGB color reference
 * @struct API_RGBColor
 * @ingroup Dialog
 * @remarks Each component expressed in [0.0... 1.0] interval. The {0.0, 0.0, 0.0} components represents the black, {1.0, 1.0, 1.0} the white color.
 */
struct API_RGBColor {

/**
 * @brief red component
 * @var f_red
 */
	double							f_red;

/**
 * @brief green component
 * @var f_green
 */
	double							f_green;

/**
 * @brief blue component
 * @var f_blue
 */
	double							f_blue;

};

/**
 * @brief RGB color reference with transparency.
 * @struct API_RGBAColor
 * @ingroup View
 * @remarks Each component expressed in [0.0... 1.0] interval. The {0.0, 0.0, 0.0} components represents the black, {1.0, 1.0, 1.0} the white color.
 */
struct API_RGBAColor {

/**
 * @brief red component
 * @var f_red
 */
	double							f_red;

/**
 * @brief green component
 * @var f_green
 */
	double							f_green;

/**
 * @brief blue component
 * @var f_blue
 */
	double							f_blue;

/**
 * @brief transparency
 * @var f_alpha
 */
	double							f_alpha;

};

/**
 * @brief Rectangle in pixel coordinates.
 * @struct API_Rect
 * @ingroup View
 * @remarks An integer type representation of an @ref API_Box. Expressed in the local coordinates of the window, based on pixels from the top/left corner.
 * 			Refer to the @ref ACAPI_View_CoordToPoint and @ref ACAPI_View_CoordToPoint conversion functions for further details.
 */
struct API_Rect {

/**
 * @brief top pixel (vertical) of the rectangle
 * @var top
 */
	short							top;

/**
 * @brief left pixel (horizontal) of the rectangle
 * @var left
 */
	short							left;

/**
 * @brief bottom pixel (vertical) of the rectangle
 * @var bottom
 */
	short							bottom;

/**
 * @brief right pixel (horizontal) of the rectangle
 * @var right
 */
	short							right;

};


/**
 * @brief Polygonal or rectangular region of the model.
 * @struct API_Region
 * @ingroup Database
 * @remarks It is a closed polygon expressed in model coordinates. Special representation can be a (rotated) rectangle. In the case of polygonal representation the data structure follows the rules specified in @ref API_Polygon.
 */
struct API_Region {

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief number of coordinates (in case of polygonal representation)
 * @var nCoords
 */
	Int32							nCoords;

/**
 * @brief the coordinate handle (in case of polygonal representation)
 * @var coords
 */
	API_Coord						**coords;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

/**
 * @brief the rectangle (in case rectangular representation)
 * @var box
 */
	API_Box							box;

/**
 * @brief the rotation angle (in case rectangular representation)
 * @var boxRotAngle
 */
	double							boxRotAngle;

};


//	A common 3x4 transformation matrix, where
//		x' = tmx[0] * x + tmx[1] * y + tmx[2]  * z + tmx[3]
//		y' = tmx[4] * x + tmx[5] * y + tmx[6]  * z + tmx[7]
//		z' = tmx[8] * x + tmx[9] * y + tmx[10] * z + tmx[11]

/**
 * @brief A 3*4 transformation matrix
 * @struct API_Tranmat
 * @ingroup View
 * @remarks This structure represents a standard 3*4 transformation matrix for linear transformations.
 * 			The transformed coordinates are calculated using the below formula:
 * 			x' = tmx[0] * x + tmx[1] * y + tmx[2] * z + tmx[3] y' = tmx[4] * x + tmx[5] * y + tmx[6] * z + tmx[7] z' = tmx[8] * x + tmx[9] * y + tmx[10] * z + tmx[11]
 */
struct API_Tranmat {
//! @cond Doxygen_Suppress
	double							tmx[12];
//! @endcond
};


/**
 * @brief Representation of an arc segment of a two dimensional polygon.
 * @struct API_PolyArc
 * @ingroup UserInput
 * @remarks Refer to the @ref API_Polygon structure for more details.
 */
struct API_PolyArc {

/**
 * @brief Node index of one end point of the arc
 * @var begIndex
 */
	Int32							begIndex;

/**
 * @brief Node index of the other end point of the arc
 * @var endIndex
 */
	Int32							endIndex;

/**
 * @brief Angle of the arc; it is positive, if the arc is on the right-hand side of the straight segment.
 * @var arcAngle
 */
	double							arcAngle;

};

/**
 * @brief Representation of a two dimensional polygon.
 * @struct API_Polygon
 * @ingroup Dialog
 * @remarks This structure holds the size of the corresponding geometry only, i.e. the number of nodes, number of subpolygons and number of arc segments in the polygon shape. The geometry data is always passed through an @ref API_ElementMemo structure.
 * 			What are the components:
 * 			- 2D coordinates; represented by an @ref API_Coord array.
 * 			- subpolygons; represented by an index (Int32) array to the coordinates. Each index points to the last coordinate of a contour.
 * 			- arc segments; represented by an @ref API_PolyArc array.
 * 			Let's see an example, with the list of rules.
 * @image html polygon.png "API Polygon"
 * 		  Coordinates:
 * 		  - poly-&gt;nCoords = BMGetHandleSize ((GSHandle) memo->coords) / sizeof (API_Coord) - 1;
 * 		  - the first coordinate of the array is not used; must be initialized to (0.0, 0.0) for polygons, and to (-1.0, 0.0) for polylines,
 * 		  - coordinates are duplicated for the end-nodes for each subcontour (see c 1 and c 7 )
 * 		  Contour ends:
 * 		  - poly-&gt;nSubPolys = BMGetHandleSize ((GSHandle) memo->pends) / sizeof (Int32) - 1;
 * 		  - the pends array contains indices to the coordinate array, indicating the vertices which close the subcontours
 * 		  - the first element is always 0
 * 		  Arc segments:
 * 		  - poly-&gt;nArcs = BMGetHandleSize ((GSHandle) memo->parcs) / sizeof (API_PolyArc);
 * 		  - the parcs array is allocated only if there are any arc segments in the polygon,
 * 		  - each record refers to two coordinate indices ( begIndex, endIndex) between which the polygon edge is an arc,
 * 		  - each record gives the signed arc angle. The angle is positive, if the arc is on the right-hand side of the (begPoint, endPoint) segment,
 * 		  - the angle is given in radians (degrees are shown on the picture only for better readability)
 * 		  Vertex IDs:
 * 		  - the number of coordinates and the number of vertexIDs are equal; each coordinate has a vertexID. That's why the @ref API_Polygon structure does not contain an nVertexID field,
 * 		  - vertexIDs can be called as node unique IDs (that's why c 1 and c 6 have the same vertex ID),
 * 		  - the maximal vertexID value is stored in the 0. cell,
 * 		  - there isn't any correspondence between the coordinate indices and the assigned vertexIDs; however they are often the same. (See that c 6 has the ID 1.),
 * 		  - upon editing the polygon shape the maximal vertexID can be not be decremented, and the nodes must keep the vertexID values
 * 		  - vertex IDs are useful in dimensioning and editing
 * 		  Editing the shape of a polygon covers many difficulties which must be handled. They are:
 * 		  - vertex IDs must be maintained,
 * 		  - arc references must be updated; partially,
 * 		  - contour-end references must be updated; partially.
 * 		  Use the provided functions to change the shape of a polygon. These functions are:
 * 		  - @ref ACAPI_Polygon_InsertPolyNode
 * 		  - @ref ACAPI_Polygon_DeletePolyNode
 * 		  - @ref ACAPI_Polygon_InsertSubPoly
 * 		  - @ref ACAPI_Polygon_DeleteSubPoly
 * @par Example
 * 		@snippet API_Examples.cpp API_Polygon-Example-Snippet
 */
struct API_Polygon {

/**
 * @brief Number of elements in the coordinate array. The begin points of contours are duplicated.
 * @var nCoords
 */
	Int32							nCoords;

/**
 * @brief Number of closed subpolygons including the main polygon. For polylines, this is always 1.
 * @var nSubPolys
 */
	Int32							nSubPolys;

/**
 * @brief Number of arched segments in the polygon/polyline.
 * @var nArcs
 */
	Int32							nArcs;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	GS::IntPtr						filler_1;

};


/**
 * @brief The direction of a grid mesh.
 * @enum API_GridMeshDirection
 * @remarks Defines the possible GridMesh directions
 */
typedef enum {
	API_GridMeshLeft		= 0,
	API_GridMeshRight		= 1,
	API_GridMeshLowerRight	= 2,
	API_GridMeshLower		= 3,
	API_GridMeshLowerLeft	= 4,
	API_GridMeshUpperRight	= 5,
	API_GridMeshUpper		= 6,
	API_GridMeshUpperLeft	= 7,
	API_GridMeshDirNum		= 8

} API_GridMeshDirection;

/**
 * @brief General header for Grid Mesh type.
 * @struct API_GridMeshHead
 * @ingroup Element
 * @remarks None
 */
struct API_GridMeshHead {

/**
 * @brief Validity flag
 * @var valid
 */
	bool							valid;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[7];

/**
 * @brief The identifier of the mesh-element.
 * @var elemID
 */
	API_GridElemID					elemID;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	UInt32							filler_2[2];

};

/**
 * @brief Describes a Grid Mesh vertex.
 * @struct API_GridMeshVertex
 * @ingroup Element
 * @remarks For more information see @ref API_GridMesh.
 */
struct API_GridMeshVertex {

/**
 * @brief General header for Grid Mesh.
 * @var head
 */
	API_GridMeshHead				head;

/**
 * @brief 2D coordinate of the vertex in the Grid Mesh's local coordinate system.
 * @var surfaceParam
 */
	API_Coord						surfaceParam;

/**
 * @brief 3D coordinate of the vertex in the global coordinate system (relative to the owner story's height).
 * @var coord
 */
	API_Coord3D						coord;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	UInt32							filler_1[2];

};

/**
 * @brief Describes a Grid Mesh edge.
 * @struct API_GridMeshEdge
 * @ingroup Element
 * @remarks For more information see @ref API_GridMesh.
 */
struct API_GridMeshEdge {

/**
 * @brief General header for Grid Mesh.
 * @var head
 */
	API_GridMeshHead				head;

/**
 * @brief The identifier of the begin vertex.
 * @var begID
 */
	API_GridElemID					begID;

/**
 * @brief The identifier of the end vertex.
 * @var endID
 */
	API_GridElemID					endID;

/**
 * @brief Attached custom data.
 * @var userData
 */
	UInt32							userData;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	UInt32							filler_1[3];

};

/**
 * @brief Contains extended information of a @ref API_GridMeshEdge.
 * @struct API_GridEdgeInfo
 * @ingroup Element
 * @remarks The main axis is vertical. For more information see @ref API_GridMesh.
 */
struct API_GridEdgeInfo {

/**
 * @brief The identifier of the edge, the info belongs to
 * @var id
 */
	API_GridElemID					id;

/**
 * @brief Whether it belongs to the main axis or not.
 * @var mainAxis
 */
	bool							mainAxis;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[7];

};

/**
 * @brief Describes a grid line of the mesh.
 * @struct API_GridMeshLine
 * @ingroup Element
 */
struct API_GridMeshLine {

/**
 * @brief Identifies the mesh element.
 * @var head
 */
	API_GridMeshHead				head;

/**
 * @brief The identifier of begpoint vertices.
 * @var begID
 */
	API_GridElemID					begID;

/**
 * @brief The identifier of endpoint vertices.
 * @var endID
 */
	API_GridElemID					endID;

/**
 * @brief Custom value assigned to this mesh line.
 * @var userData
 */
	UInt32							userData;

/**
 * @brief If false then secondary direction.
 * @var mainDir
 */
	bool							mainDir;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	UInt32							filler_2[3];

};

/**
 * @brief A 3D mesh polygon with four edge indices
 * @struct API_GridMeshPolygon
 * @ingroup Element
 * @remarks For more information see @ref API_GridMesh.
 */
struct API_GridMeshPolygon {

/**
 * @brief General Grid Mesh header.
 * @var head
 */
	API_GridMeshHead				head;

/**
 * @brief The identifiers of the neighbour polygons in all the 8 (=API_GridMeshDirNum) directions).
 * @var neighbourIDs
 */
	GS::Array<API_GridElemID>		neighbourIDs[API_GridMeshDirNum];

/**
 * @brief Edge indices of the grid mesh polygon.
 * @var edges
 */
	API_GridEdgeInfo				edges[4];

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[2];

};

/**
 * @brief Describes a Curtain Wall segment geometry.
 * @struct API_GridMesh
 * @ingroup Element
 * @remarks Figure @image html GridMesh.png width=33%
 */
struct API_GridMesh {

/**
 * @brief For internal use.
 * @var useIDs
 */
	bool							useIDs;

/**
 * @brief Reserved for further use.
 * @var filler_1
 */

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[7];

/**
 * @brief The identifier of the left lower grid mesh polygon.
 * @var lowerLeftPolyID
 */
	API_GridElemID					lowerLeftPolyID;

/**
 * @brief The identifier of the right lower grid mesh polygon
 * @var lowerRightPolyID
 */
	API_GridElemID					lowerRightPolyID;


/**
 * @brief Array of Grid Lines belong to the main axis (vertical).
 * @var meshLinesMainAxis
 */
	GS::Array<API_GridMeshLine>		meshLinesMainAxis;

/**
 * @brief Array of Grid Lines belong to the secondary axis (horizontal).
 * @var meshLinesSecondaryAxis
 */
	GS::Array<API_GridMeshLine>		meshLinesSecondaryAxis;


/**
 * @brief Table of grid mesh vertices with identifier keys.
 * @var meshVertices
 */
	GS::HashTable<API_GridElemID, API_GridMeshVertex>	meshVertices;

/**
 * @brief Table of grid mesh polygons with identifier keys.
 * @var meshPolygons
 */
	GS::HashTable<API_GridElemID, API_GridMeshPolygon>	meshPolygons;

/**
 * @brief Table of Grid Edges belong to the main axis (vertical).
 * @var meshEdgesMainAxis
 */
	GS::HashTable<API_GridElemID, API_GridMeshEdge>		meshEdgesMainAxis;

/**
 * @brief Table of Grid Edges belong to the secondary axis (horizontal).
 * @var meshEdgesSecondaryAxis
 */
	GS::HashTable<API_GridElemID, API_GridMeshEdge>		meshEdgesSecondaryAxis;


/**
 * @brief the identifiers for the Lower left, lower right, upper right and upper left vertices of the grid mesh.
 * @var cornerPointIDs
 */
	API_GridElemID					cornerPointIDs[4];

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	UInt32							filler_2[2];

};

/**
 * @brief Describes an interval with handling possible periodicity.
 * @ingroup Element
 * @struct API_Interval
 * @remarks None
 */
struct API_Interval {

/**
 * @brief Lower bound of the interval.
 * @var lower
 */
	double							lower;

/**
 * @brief Upper bound of the interval.
 * @var upper
 */
	double							upper;

/**
 * @brief Interval Length if it is circular.
 * @var periodicity
 */
	double							periodicity;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	double							filler_1;

};

/**
 * @brief Desribes a 3D plane.
 * @struct API_Plane3D
 * @ingroup Dialog
 */
struct API_Plane3D {

/**
 * @brief Base point of the plane.
 * @var basePoint
 */
	API_Coord3D						basePoint;

/**
 * @brief The X axis.
 * @var axisX
 */
	API_Vector3D					axisX;

/**
 * @brief The Y axis.
 * @var axisY
 */
	API_Vector3D					axisY;

/**
 * @brief The Z axis.
 * @var axisZ
 */
	API_Vector3D					axisZ;

};

/**
 * @brief Renovation status of the (primitive) element.
 * @enum API_RenovationStatusType
 * @ingroup Dialog
 */
typedef enum {
	API_UndefinedStatus		= -1,
	API_DefaultStatus		= 0,								// special value; input only
	API_ExistingStatus		= 1,
	API_NewStatus			= 2,
	API_DemolishedStatus	= 3

} API_RenovationStatusType;


// ---------------------------------------------------------------------------------------------------------------------

#endif
