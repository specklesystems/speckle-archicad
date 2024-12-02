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


typedef struct {
	API_3DTypeID					typeID;						// type of the 3D component
	Int32							index;						// element index
	Int32							elemIndex;					// 3D element index; for bodies only; output only
	Int32							bodyIndex;					// 3D body index; for bodies only; output only
} API_3D_Head;



// =============================================================================
// 3D Body
//
// =============================================================================

#define APIBody_MulRtxt				0x0100						// more textures are referenced by its materials
#define APIBody_MulColor			0x0200						// more colors referenced by its edges
#define APIBody_MulMater			0x0400						// more materials referenced by its polygons
#define APIBody_Closed				0x0001						// its geometry is closed
#define APIBody_Curved				0x0002						// it has smooth polygons

typedef struct {
	API_3D_Head						head;
	API_Elem_Head					parent;						// floorplan element the body has been converted from

	Int32							status;						// the body properties
	short							color;						// refers to the default color of the body edges
	short							filler_0[3];
	API_AttributeIndex				iumat;						// refers to the default material of the body polygons
	float							xmin;						// the bounding box of the body geometry
	float							ymin;
	float							zmin;
	float							xmax;
	float							ymax;
	float							zmax;

	Int32							nPgon;						// number of polygons in the body
	Int32							nPedg;						// number of edge references in the body
	Int32							nEdge;						// number of edges in the body
	Int32							nVert;						// number of vertices in the body
	Int32							nVect;						// number of normal vectors in the body
	Int32							filler_1;

	API_Tranmat						tranmat;					// the base transformation matrix
} API_BodyType;


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

typedef	struct {
	API_3D_Head						head;

	Int32							status;						// information about the polygon properties
	API_AttributeIndex				iumat;						// refers to the polygon material
	Int32							irtxt;						// internal use
	Int32							ivect;						// refers to the polygon normal vector  (negative: use opposite direction)
	Int32							fpedg;						// range of indices referring to the polygon contour edges
	Int32							lpedg;
} API_PgonType;


// =============================================================================
// 3D Edge reference
//
// =============================================================================

typedef struct {
	API_3D_Head						head;

	Int32							pedg;						// Edge reference. Negative value means opposite direction. Zero index identifies a new hole
	Int32							filler_1;
} API_PedgType;


// =============================================================================
// 3D Edge
//
// =============================================================================

#define APIEdge_Invis				0x0001						// invisible edge
#define APIEdge_Curved				0x0002						// edge of a curved surface

typedef struct {
	API_3D_Head						head;

	Int32							status;						// information about the edge properties
	short							filler_1;
	short							color;						// refers to the edge color
	Int32							vert1;						// vertex indices of the edge endpoints
	Int32							vert2;
	Int32							pgon1;						// indices of the neighbouring polygons
	Int32							pgon2;						// indices of the neighbouring polygons
} API_EdgeType;


// =============================================================================
// 3D Vertex
//
// =============================================================================

typedef struct {
	API_3D_Head						head;

	double							x;							// the model coordinates
	double							y;
	double							z;
} API_VertType;


// =============================================================================
// 3D Vector
//
// =============================================================================

typedef struct {
	API_3D_Head						head;

	double							x;
	double							y;
	double							z;
} API_VectType;


// =============================================================================
// 3D Light
//
// =============================================================================

typedef enum {
	APILght_DistantID,
	APILght_DirectionID,
	APILght_SpotID,
	APILght_PointID,
	APILght_SunID,
	APILght_EyeID
} API_LghtSouID;

#define APILight_CastShadow			0x0001

typedef struct {
	API_3D_Head						head;

	API_LghtSouID					type;						// the type of the light
	Int32							status;
	Int32							filler_1[2];
	API_RGBColor					lightRGB;					// the light source color
	double							posx;						// the local origin of the light
	double							posy;
	double							posz;
	double							dirx;						// direction of the light
	double							diry;
	double							dirz;
	double							radius;						// the radius of the light source
	double							cosa;						// cosine of the angle of the cone within the light has its maximum intensity
	double							cosb;						// cosine of the angle of the cone within the intensity falls to zero
	double							afall;						// falloff control of the light (decrease of intensity depending on the cone angle)
	double							dist1;						// clipping values along the x axis
	double							dist2;
	double							dfall;						// controls the decrease of intensity depending on the distance
} API_LghtType;


// =============================================================================
// 3D Material
//
// =============================================================================

typedef struct {
	API_3D_Head						head;

	API_MaterialType				mater;						// API_Attr_Head::index - 0 in case of GDL materials; n - in case of global material reference
} API_UmatType;


// =============================================================================
// General component
//
// =============================================================================

typedef union {
	API_3D_Head						header;

	API_BodyType					body;

	API_PgonType					pgon;
	API_PedgType					pedg;
	API_EdgeType					edge;
	API_VertType					vert;
	API_VectType					vect;

	API_LghtType					lght;
	API_UmatType					umat;
} API_Component3D;


// ---------------------------------------------------------------------------------------------------------------------

#endif
