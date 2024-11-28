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
typedef GSIndex						API_AttributeIndex;

// =============================================================================
// Geometry
//
// =============================================================================

typedef struct {
	short							v;
	short							h;
} API_Point;

typedef struct {
	double							x;
	double							y;
} API_Coord, API_Vector;


typedef struct {
	double							x;
	double							y;
	double							z;
} API_Coord3D, API_Vector3D;


typedef struct {
	double							u;
	double							v;
} API_UVCoord;


typedef struct {
	API_Coord						c1;
	API_Coord						c2;
} API_Sector;


typedef struct {
	double							xMin;
	double							yMin;
	double							xMax;
	double							yMax;
} API_Box;


typedef struct {
	double							xMin;
	double							yMin;
	double							zMin;
	double							xMax;
	double							yMax;
	double							zMax;
} API_Box3D;


typedef struct {
	double							f_red;						// 0.0 -> 1.0
	double							f_green;
	double							f_blue;
} API_RGBColor;

typedef struct {
	double							f_red;						// 0.0 -> 1.0
	double							f_green;
	double							f_blue;
	double							f_alpha;
} API_RGBAColor;

typedef struct {
	short							top;
	short							left;
	short							bottom;
	short							right;
} API_Rect;


typedef struct {
	Int32							filler_1;
	Int32							nCoords;
	API_Coord						**coords;
	Int32							filler_2;
	API_Box							box;
	double							boxRotAngle;
} API_Region;


//	A common 3x4 transformation matrix, where
//		x' = tmx[0] * x + tmx[1] * y + tmx[2]  * z + tmx[3]
//		y' = tmx[4] * x + tmx[5] * y + tmx[6]  * z + tmx[7]
//		z' = tmx[8] * x + tmx[9] * y + tmx[10] * z + tmx[11]

typedef struct {
	double							tmx[12];
} API_Tranmat;


typedef struct {
	Int32							begIndex;					// arc between begIndex, endIndex in poly
	Int32							endIndex;
	double							arcAngle;					// maybe +/-
} API_PolyArc;

typedef struct {
	Int32							nCoords; 					// number of vertices
	Int32							nSubPolys;					// number of closed sub polygons including the first one
	Int32							nArcs;						// number of curves in the polygon
	GS::IntPtr						filler_1;
} API_Polygon;


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

typedef struct {
	bool							valid;
	bool							filler_1[7];
	API_GridElemID					elemID;
	UInt32							filler_2[2];
} API_GridMeshHead;

typedef struct {
	API_GridMeshHead				head;
	API_Coord						surfaceParam;
	API_Coord3D						coord;
	UInt32							filler_1[2];
} API_GridMeshVertex;

typedef struct {
	API_GridMeshHead				head;
	API_GridElemID					begID;						// ID of begpoint vertices
	API_GridElemID					endID;						// ID of endpoint vertices
	UInt32							userData;
	UInt32							filler_1[3];
} API_GridMeshEdge;

typedef struct {
	API_GridElemID					id;
	bool							mainAxis;
	bool							filler_1[7];
} API_GridEdgeInfo;

typedef struct {
	API_GridMeshHead				head;
	API_GridElemID					begID;						// ID of begpoint vertices
	API_GridElemID					endID;						// ID of endpoint vertices
	UInt32							userData;
	bool							mainDir;					// if false then secondary direction
	bool							filler_1;
	UInt32							filler_2[3];
} API_GridMeshLine;

typedef struct {
	API_GridMeshHead				head;
	GS::Array<API_GridElemID>		neighbourIDs[API_GridMeshDirNum];
	API_GridEdgeInfo				edges[4];
	Int32							filler_1[2];
} API_GridMeshPolygon;

typedef struct {
	bool							useIDs;
	bool							filler_1[7];
	API_GridElemID					lowerLeftPolyID;
	API_GridElemID					lowerRightPolyID;

	GS::Array<API_GridMeshLine>		meshLinesMainAxis;			// lines in main axis
	GS::Array<API_GridMeshLine>		meshLinesSecondaryAxis;		// lines in secondary axis

	GS::HashTable<API_GridElemID, API_GridMeshVertex>	meshVertices;	// 3D points
	GS::HashTable<API_GridElemID, API_GridMeshPolygon>	meshPolygons;	// polygons
	GS::HashTable<API_GridElemID, API_GridMeshEdge>		meshEdgesMainAxis;
	GS::HashTable<API_GridElemID, API_GridMeshEdge>		meshEdgesSecondaryAxis;

	API_GridElemID					cornerPointIDs[4];			// lower left, lower right, upper right and upper left points
	UInt32							filler_2[2];
} API_GridMesh;

typedef struct {
	double							lower;						// lower bound
	double							upper;						// upper bound of the interval
	double							periodicity;				// interval Length if it is circular
	double							filler_1;
} API_Interval;

typedef struct {
	API_Coord3D						basePoint;					// base point of the plane
	API_Vector3D					axisX;
	API_Vector3D					axisY;
	API_Vector3D					axisZ;
} API_Plane3D;

typedef enum {
	API_UndefinedStatus		= -1,
	API_DefaultStatus		= 0,								// special value; input only
	API_ExistingStatus		= 1,
	API_NewStatus			= 2,
	API_DemolishedStatus	= 3
} API_RenovationStatusType;


// ---------------------------------------------------------------------------------------------------------------------

#endif
