// *****************************************************************************
// 2D POLYGON OPERATIONS
// Combination of the struct and the callback functions
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************

#if !defined (POLYGON2DOPERATIONS_H)
#define POLYGON2DOPERATIONS_H

#pragma once

// from GSRoot
#include "BMX.hpp"
#include "SessionUnId.hpp"
#include "GSAbort.hpp"

#include "GeometricDefinitions.h"
#include "Point2DData.h"

#include "Box2DData.h"
#include "HalfPlane2DData.h"
#include "Plane3DData.h"

namespace Geometry {

enum PolyHoleHandling { ReturnHoles, WithoutHoles };

enum PolyRegularizationMode {
	PolyRegularizationMode_Default,
	PolyRegularizationMode_Alternative
};

// General

enum PGError {
	PGSelfintersect  = ErrorCodeBase + 1
};

GEOMETRY_DLL_EXPORT void	PGSetDebugFlagsExt (unsigned char flags);
unsigned char PGGetDebugFlagsExt (void);

// CallbackPolygon data-structures

struct PGEDGESTATUSEXT {
	bool	isArc			: 1; 		/* edge is an arc							*/
	bool	isArcRevoriented: 1; 		/* if edge is an arc then reverse oriented	*/
	bool	isBegHole		: 1; 		/* starting edge of a hole					*/
	bool	isEndContour	: 1; 		/* last edge of the contoure or a hole		*/
	bool	isEndPolygon	: 1; 		/* last edge of the whole polygon			*/
	bool	isInvisible		: 1; 		/* invisible edge							*/
	bool	isSplitLine		: 1; 		/* edge from a splitline					*/
};

const PGEDGESTATUSEXT	NormalEdgeStatus = {false, false, false, false, false, false, false};

const double InvLen_NotInited	= -1.0;
const double InvLen_ZeroEdge	= -2.0;

struct PGEDGEEXT {
	PGEDGESTATUSEXT status;			/*   4 */	/* status							*/
	Int32	filler2;				/*	 4 */	/* must be zero						*/
	double	invlen;					/*   8 */	/* edge length	  1.0/(dx*dx+dy*dy)	*/
	Point2D	begPt;					/*  16 */	/* edge start point					*/

	Point2D	center;					/*  16 */	/* center x,y						*/
	double	radius;					/*   8 */	/* radius							*/
	double	fi1;					/*   8 */	/* start point angle				*/
	double  fi2;					/*   8 */	/* end point angle					*/

	GSPtr	vertexData;				/*   4 */	/* pointer of attached vertex data	*/
	UInt32	generatedVertexId;		/*	 4 */	/* algorithm specific vertex id in returned polygon */
	GSPtr	inhEdgeData;			/*   4 */	/* pointer of attached edge data	*/
	GSPtr	uniqEdgeData;			/*   4 */	/* pointer of attached once edge data*/
	GSPtr	contourData;			/*   4 */	/* pointer of attached once edge data*/
};						/* 92 */

struct PGPOLYEXT;

typedef	PGEDGEEXT	(*GetPGEdgeProcExt)	(const PGPOLYEXT* polygon, Int32 ind);	//
typedef	GSErr		(*NewPGEdgeProcExt)	(PGPOLYEXT* polygon, const PGEDGEEXT* pgedge);

struct PGPOLYSTATUSEXT {
	UInt32	isRevoriented		: 1;	/* poly is revoriented						*/
	UInt32	isSameDirEdgeLegal	: 1;	/* true, if two suceeding edge with same direction (two edge in one line) is legal */
	UInt32	hasZeroArea			: 1;	/* true, if polygon has zero area. */
	UInt32	force64BitPrecision : 1;
};

const PGPOLYSTATUSEXT	NormalPolyStatus = { false, false, false, false}; //lint !e915 (Implicit conversion (return) int to bool)

struct PGPOLYEXT {
	PGPOLYSTATUSEXT		status;		// status info
	Int32				nContours;	// the number of contours of the whole polygon
	Int32				nEdges;		// the number of edges of the whole polygon
	Int32				nArcs;		// the number of arcs of the whole polygon
	Box2DData			boundBox;	// the bound box of the polygon
	double				epsilon;	// epsilon for length and real comparisions
	double				angleEpsilon; // epsilon for angle comparisions
	double				minVertexDist;// the minimal vertex distance (shorter edges will be omitted)

	GSSize				sizeOfData;	// the size of the above data
	bool				isNewData;	// if false we use the Polygon2D objects
	GSPtr				data;		// the polygon data, if the functions are nullptr, it must be Polygon2DData* or Polygon2D* depending on the isNewData flag, otherwise anything

	GSPtr				defaultVertexData;		/* pointer of default vertex data	*/
	GSPtr				defaultInhEdgeData;		/* pointer of default edge data		*/
	GSPtr				defaultUniqEdgeData;	/* pointer of default once edge data*/
	GSPtr				defaultContourData;		/* pointer of default contour data	*/
	GSPtr				inhPolygonData;			/* pointer of polygon data			*/

	GetPGEdgeProcExt	getEdge;	// gets the i-th segment (vertex and edge (straight or arced) starting from it) of the polygon
	NewPGEdgeProcExt	newEdge;	// gives the i-th segment (vertex and edge (straight or arced) starting from it) of the polygon

	GS::SessionUnId	unid;		// if unid != 0 && &PGPOLYEXT is the same and unid is the same, PG could use the internal cache (but not sure)

	PGPOLYEXT () :
		status (NormalPolyStatus),
		nContours (0),
		nEdges (0),
		nArcs (0),
		epsilon (0.0),
		angleEpsilon (0.0),
		minVertexDist (0.0),
		sizeOfData (0),
		isNewData (false),
		data (nullptr),
		defaultVertexData (nullptr),
		defaultInhEdgeData (nullptr),
		defaultUniqEdgeData (nullptr),
		defaultContourData (nullptr),
		inhPolygonData (nullptr),
		getEdge (nullptr),
		newEdge (nullptr),
		unid (GS::NullSessionUnId)
   {
   }
};

struct PGRESPOLYEXT;

typedef	GSErr		(*NewPGPolyProcExt)	(PGRESPOLYEXT* polygons, const PGPOLYEXT* newPoly, PGPOLYEXT** storedPoly); /* the *storedPoly must be valid till the next call */

struct PGRESPOLYEXT {
	GSPtr					polygonsData;	// the polygons array, if the newPolygon is nullptr, it must be GS::VAArray<Polygon2DData>* or GS::VAArray<Polygon2D>* depending on the isNewData flag
	bool					isNewData;		// if false we use the Polygon2D objects
	NewPGPolyProcExt		newPolygon;		// creates a new polygon

	PGRESPOLYEXT ():
		polygonsData (nullptr),
		isNewData (false),
		newPolygon (nullptr)
	{

	}
};

// Whole polygon operations

GEOMETRY_DLL_EXPORT double				PGPolyAreaExt (
					const PGPOLYEXT*	polygon,
					double*				thole);

GEOMETRY_DLL_EXPORT GSErr				PGPolyRemoveHolesExt (
					const PGPOLYEXT*	polygon,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT GSErr					PGPolyMakeRegularExt (
					const PGPOLYEXT*		originalPolygon,
					PGRESPOLYEXT*			newPolygons,
					GS::AbortInterfaceBase*	breaker = nullptr);

enum PGRegulHoleHandling {
	KeepInvalidHoles,
	ThrowInvalidHoles,
	KeepMainContour				// NA #17810  2002.11.29
};

enum PGRelPolyPosExt {
	UnknownStatus			= -1,
	PolysOverlap			= 0,
	Poly1CoversPoly2		= 1,
	Poly2CoversPoly1		= 2,
	PolysEqual				= 3,
	PolysDisjunct			= 4,
	PolysDisjunct_Node		= 5,
	PolysDisjunct_Edge		= 6,
	Poly1HasZeroArea		= 7,
	Poly2HasZeroArea		= 8
};


GEOMETRY_DLL_EXPORT GSErr				PGIsPolyRegularExt (
					const PGPOLYEXT*	originalPolygon,
					bool*				isPolyRegular);


GEOMETRY_DLL_EXPORT GSErr						PGPolyMakeRegular2Ext (
					const PGPOLYEXT*			originalPolygon,
					PGRESPOLYEXT*				newPolygons,
					bool						resolveSelfInters,
					GS::AbortInterfaceBase*		breaker = nullptr,
					PGRegulHoleHandling			holeHandling = KeepMainContour,
					PGRelPolyPosExt*			status = nullptr,
					PolyRegularizationMode		mode = PolyRegularizationMode_Default);

// Contour operations

GEOMETRY_DLL_EXPORT GSErr				PGPolyResizeContourExt (
					const PGPOLYEXT*	originalPolygon,
					UIndex				contourIdx,
					double				offset,
					PGRESPOLYEXT*		newPolygons);

// Vertex operations

GEOMETRY_DLL_EXPORT GSErr				PGPolyMoveVertexExt (
					const PGPOLYEXT*	polygon,
					UIndex				movedVertexIdx,
					const Point2D&		newVertexPosition,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT GSErr				PGPolyGetMaxVertexFilletExt (
					const PGPOLYEXT*	poly,
					UIndex				filletedVertexIdx,
					double*				maxFilletRadius);

GEOMETRY_DLL_EXPORT GSErr				PGPolyFilletVertexExt (
					const PGPOLYEXT*	polygon,
					UIndex				filletedVertexIdx,
					double				filletRadius,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT GSErr				PGPolyFilletContourExt (
					const PGPOLYEXT*	polygon,
					UIndex				filletedContourIdx,
					double				filletRadius,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT GSErr				PGPolyChamferVertexExt (
					const PGPOLYEXT*	polygon,
					UIndex				chamferedVertexIdx,
					double				chamferRadius,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT GSErr				PGPolyChamferContourExt (
					const PGPOLYEXT*	polygon,
					UIndex				chamferedContourIdx,
					double				chamferRadius,
					PGRESPOLYEXT*		newPolygons);


// Edge operations

GEOMETRY_DLL_EXPORT GSErr				PGPolyInsertVertexExt (
					const PGPOLYEXT*	polygon,
					UIndex				breakedEdgeIdx,
					const Point2D&		newVertexPosition,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT GSErr				PGPolySetEdgeAngleExt (
					const PGPOLYEXT*	polygon,
					UIndex				edgeIdx,
					double				viewAngle,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT GSErr				PGPolyOffsetEdgeExt (
					const PGPOLYEXT*	polygon,
					UIndex				edgeIdx,
					double				offset,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT GSErr				PGPolyOffsetEdgeFixAreaExt (
					const PGPOLYEXT*	polygon,
					UIndex				edgeIdx,
					UIndex				vertIdx,
					double				offset,
					double				area,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT GSErr				PGPolyDeleteEdgeExt (
					const PGPOLYEXT*	polygon,
					UIndex				edgeIdx,
					bool*				deleteAble,
					PGRESPOLYEXT*		newPolygons);

// Polygon - Point operations

enum PGPositionExt {
	PGInsidePoly		= 0,
	PGOutsidePoly		= 1,
	PGOnPolyEdge		= 2
};

GEOMETRY_DLL_EXPORT PGPositionExt			 PGCoordInPolyExt (
					const PGPOLYEXT*	polygon,
					const Point2D*		p,
					bool				mainContOnly);

GEOMETRY_DLL_EXPORT PGPositionExt			 PGPoint2DPosition (
					const PGPOLYEXT*	polygon,
					const Point2D*		p,
					bool				mainContOnly);


// CallbackSector data-structures

struct PGRESSECTOREXT;

typedef	GSErr		(*NewSectorProcExt)	(PGRESSECTOREXT* sectors, const Sector& newSector);

struct PGRESSECTOREXT {
	GSPtr					sectorsData;	// the sectors array, if the newSector is nullptr, it must be GS::VAArray<Sector>*
	NewSectorProcExt		newSector;		// creates a new sector
};
// Polygon - Sector operations

GEOMETRY_DLL_EXPORT PGPositionExt			 PGSegmentInPolyExt (
					const PGPOLYEXT*		polygon,
					Point2D*					bp,
					Point2D*					ep,
					bool					complement,
					PGRESSECTOREXT*			newSectors,
					GS::AbortInterfaceBase*	breaker = nullptr);

// Polygon - polygon operations


GEOMETRY_DLL_EXPORT GSErr				PGPolyPositionExt (
					const PGPOLYEXT*			polygon1,
					const PGPOLYEXT*			polygon2,
					PGRelPolyPosExt*			status,
					GS::AbortInterfaceBase*		breaker = nullptr);

GEOMETRY_DLL_EXPORT GSErr				PGPolyUnionExt (
					const PGPOLYEXT*	polygon1,
					const PGPOLYEXT*	polygon2,
					PGRESPOLYEXT*		newPolygons,
					PGRelPolyPosExt*	status);

GEOMETRY_DLL_EXPORT GSErr				PGPolyIntersectionExt (
					const PGPOLYEXT*	polygon1,
					const PGPOLYEXT*	polygon2,
					PGRESPOLYEXT*		newPolygons,
					PGRelPolyPosExt*	status);

GEOMETRY_DLL_EXPORT GSErr				PGPolyDifferenceExt (
					const PGPOLYEXT*		polygon1,
					const PGPOLYEXT*		polygon2,
					PGRESPOLYEXT*			newPolygons,
					PGRelPolyPosExt*		status,
					GS::AbortInterfaceBase*	breaker = nullptr);

GEOMETRY_DLL_EXPORT GSErr				PGPolyCreateCommonEdgeSectionsExt (
					const PGPOLYEXT*	polygon1,
					const PGPOLYEXT*	polygon2,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT GSErr				PGPolygonClipping (
				 const GS::Array<const PGPOLYEXT*>&		polys,			/*-> input polygons from highest to lowest priority */
				 PGRESPOLYEXT*							newPolygons, 	/* <- result polygons		*/
				 GS::AbortInterfaceBase*				breaker = nullptr);

GEOMETRY_DLL_EXPORT bool				PGPolyCut (
				HalfPlane2DData			*cutline,		/* -> line params.			*/
				const PGPOLYEXT*	polygon,		/* -> polygon				*/
				PGRESPOLYEXT*		newPolygons, 	/* <- result polygons		*/
				Int32 				*wrcode);		/* <- warning error code   	*/


GEOMETRY_DLL_EXPORT bool				PGPolyStrip (
				HalfPlane2DData		*cutline1,		/* -> line params.			*/
				HalfPlane2DData		*cutline2,		/* -> line params.			*/
				const PGPOLYEXT*	polygon,		/* -> polygon				*/
				PGRESPOLYEXT*		newPolygons, 	/* <- result polygons		*/
				Int32 				*wrcode);		/* <- warning error code   	*/


GEOMETRY_DLL_EXPORT bool				PGPolyClip (
				 Box2DData*			clip,			/* -> line params.			*/
				 const PGPOLYEXT*	polygon,		/* -> polygon				*/
				 PGRESPOLYEXT*		newPolygons, 	/* <- result polygons		*/
				 Int32*				wrcode);		/* <- warning error code   	*/


}

#endif
