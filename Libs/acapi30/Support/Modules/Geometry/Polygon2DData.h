// *****************************************************************************
// C style struct for containing packed polygon data.
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// [SG compatible]
// *****************************************************************************
#if defined GDL_DLL_COMPILE || \
	defined VBELEMENTS_DLL_COMPILE || \
	defined VBTO3DCONVERTER_DLL_COMPILE || \
	defined EDITINGINTERACTIONS_DLL_COMPILE || \
	defined VBELEMEDITINGINTERACTIONS_DLL_COMPILE || \
	defined VB_ELEM_OPERATIONS_DLL_COMPILE || \
	defined AC_OPERATIONS_DLL_COMPILE || \
	defined AC_UTILITIES_DLL_COMPILE || \
	defined AC_LOGIC_DLL_COMPILE || \
	defined Archicad || \
	defined IFC_DLL_COMPILE

#error	Cant Use Polygon2DData in this module!

#endif

#if !defined (POLYGON2DDATA_H)
#define POLYGON2DDATA_H

#pragma once

#include "GeometricDefinitions.h"
#include "HashSet.hpp"
#include "RealNumber.h"
#include "HalfPlane2DData.h"
#include "Box2DData.h"
#include "Polygon2DOperations.h"
#include "PolyArcRec.h"
#include "GenArc2DData.h"

struct TRANMAT;
struct PolyArcRec;

namespace GS {
	template<class T> class VAArray;
}


namespace Geometry {

#define P2DD_CWORIENTATION 1

// All indices run from 1 to N
// The orientation always should be positive/counter-clockwise (right-hand coord system)
// The first vertex of a contour must be repeated in the last vertex of the contour
// The minimal distance between two neighboring vertex is MinPolygon2DDataVertexDistance

const double MinPolygon2DDataVertexDistance	= Eps;

struct Polygon2DData {
	struct {
		UInt32	isBoundBoxValid			: 1;// Set if you modify the polygon and not refresh the boundbox
		UInt32	isOrientationCorrect	: 1;// Set if you modify the polygon and not check the orientation
		UInt32	isSameDirEdgeLegal		: 1;// Set if two suceeding edge with same direction (two edge in one line) is legal
		UInt32	force64BitPrecision		: 1;
	}				status;
	Box2DData		boundBox;			// Boundbox of the whole polygon
	USize			nVertices;			// Total number of all vertices in all contours (equals to num of edges)
	Point2D**			vertices;			// Handle containing the vertices

	GSHandle		vertexInfos;		// Handle containing the attached vertex informations (eg. vertID)
	GSSize			sizeOfVertexInfo;	// The size of ONE vertexInfo struct
	GSHandle		defaultVertexInfo;	// Default vertex info filling the new vertices with

	GSHandle		inhEdgeInfos;		// Handle containing the attached edge informations inherited by all descendant (eg. height)
	GSSize			sizeOfInhEdgeInfo;	// The size of ONE inhEdgeInfo struct
	GSHandle		defaultInhEdgeInfo;	// Default vertex info filling the new edges with (NOT FROM SPLITTING!)

	GSHandle		uniqEdgeInfos;		// Handle containing the attached edge informations inherited by ONLY the FIRST descendant
	GSSize			sizeOfUniqEdgeInfo;	// The size of ONE uniqEdgeInfo struct
	GSHandle		defaultUniqEdgeInfo;// Default vertex info filling the new edges with (FROM SPLITTING TOO!)

	USize			nArcs;				// Total number of curved edges
	PolyArcRec**	arcs;				// the view angle of arcs (sign: + means CCW, - means CW) and the connecting vertices

	USize			nContours;			// The number of contours: the first is the main (outer), the others are the holes
	UIndex**		contourEnds;		// The index of the vertex in vertexPts which is the last in the given contour

	GSHandle		contourInfos;		// Handle containing the attached contour informations (inherited)
	GSSize			sizeOfContourInfo;	// The size of ONE contourInfo struct
	GSHandle		defaultContourInfo;	// Default contour info filling the new contours with

	GSHandle		inhPolygonInfo;			// Handle containing the attached polygon informations (inherited)
	GSSize			sizeOfInhPolygonInfo;	// The size of ONE inhPolygonInfo struct

	GSHandle		uniqPolygonInfo;		// Handle containing the attached polygon informations inherited by ONLY the FIRST descendant
	GSSize			sizeOfUniqPolygonInfo;	// The size of ONE sizeOfUniqPolygonInfo struct
	GSHandle		defaultUniqPolygonInfo;	// Default uniq info; descendants polygons will get this except the first
};

GEOMETRY_DLL_EXPORT
GSErr	InitPolygon2DData (Polygon2DData* poly,
						 GSSize sizeOfVertexInfo = 0,
						 GSPtr	defaultVertexInfo = nullptr,
						 GSSize sizeOfInhEdgeInfo = 0,
						 GSPtr	defaultInhEdgeInfo = nullptr,
						 GSSize	sizeOfUniqEdgeInfo = 0,
						 GSPtr	defaultUniqEdgeInfo = nullptr,
						 GSSize	sizeOfContourInfo = 0,
						 GSPtr	defaultContourInfo = nullptr,
						 GSSize	sizeOfInhPolygonInfo = 0,
						 GSSize sizeOfUniqPolygonInfo = 0,
						 GSPtr	defaultUniqPolygonInfo = nullptr);

GEOMETRY_DLL_EXPORT GSErr	InitPolygon2DDataFromTemplate (
								Polygon2DData*			destination,
								const Polygon2DData&	source);

GEOMETRY_DLL_EXPORT GSErr InitPolygon2DData (Polygon2DData* destPoly, const Box2DData& box);
GEOMETRY_DLL_EXPORT GSErr InitPolygon2DData (Polygon2DData* destPoly, const GS::Array<Point2D>& coords);

GEOMETRY_DLL_EXPORT GSErr	FreePolygon2DData (Polygon2DData*	poly);
GEOMETRY_DLL_EXPORT GSErr	CopyPolygon2DData (Polygon2DData*	destination, const Polygon2DData& source);
GEOMETRY_DLL_EXPORT GSErr	CheckPolygon2DDataIntegrity (const Geometry::Polygon2DData& poly);
GEOMETRY_DLL_EXPORT GSErr	CheckPolygon2DDataIntegrityDebug (const Geometry::Polygon2DData& poly);
GEOMETRY_DLL_EXPORT void	DumpPolygon2DData (const Polygon2DData& poly);
GEOMETRY_DLL_EXPORT void	DumpGDLPolygon2DData (const void* poly2DDataPtr);
GEOMETRY_DLL_EXPORT void	PrintPolygon2DData (GS::OChannel& oc, const Polygon2DData& poly);
GEOMETRY_DLL_EXPORT	GSErrCode	ReadPolygon2DDataXML (GS::XMLIChannel& ic, Polygon2DData& poly);
GEOMETRY_DLL_EXPORT	GSErrCode	WritePolygon2DDataXML (GS::XMLOChannel& oc, const Polygon2DData& poly);

inline GSErr ValidatePolygon2DData (Polygon2DData*	poly, UIndex* vertIdx = nullptr, UIndex* edgeIdx = nullptr, UShort* reportMask = nullptr);

GEOMETRY_DLL_EXPORT double	GetPolygon2DDataArea (const Polygon2DData& polygon2DData, bool isPolyLine = false);
GEOMETRY_DLL_EXPORT GSErr	GetPolygon2DDataBoundBox  (const Polygon2DData& poly, Box2DData* boundBox);

GEOMETRY_DLL_EXPORT double	GetPolygon2DDataPerimeter (const Polygon2DData& polygon2DData, UIndex iContour);

GEOMETRY_DLL_EXPORT GSErr	IsPolygon2DDataRegular (const Polygon2DData& poly, bool* isPolyRegular);

GEOMETRY_DLL_EXPORT GSErr	RegularizePolygon2DData   (
								const Polygon2DData& 		poly,
								GS::VAArray<Polygon2DData>*	resultPolys,
								GS::AbortInterfaceBase*		breaker = nullptr,
								bool						resolveSelfInters = true,
								PGRegulHoleHandling 		holeHandling = KeepMainContour);

GEOMETRY_DLL_EXPORT GSErr	RemovePolygon2DDataHoles  (const Polygon2DData& poly, Polygon2DData* unholedPoly);
GEOMETRY_DLL_EXPORT GSErr	OffsetPolygon2DData  (const Polygon2DData& poly, Vector2D	offset, Polygon2DData* offsetedPoly);

GEOMETRY_DLL_EXPORT GSErr	ResizePolygon2DDataContour(const Polygon2DData& poly, Int32 contourIdx, double offset, GS::VAArray<Polygon2DData>* resultPolys);

GEOMETRY_DLL_EXPORT GSErr	GetMaxPolygon2DDataVertexFillet (const Polygon2DData& poly, Int32 vertIdx, double* maxFilletRadius);

GEOMETRY_DLL_EXPORT GSErr	OffsetPolygon2DDataEdge   (const Polygon2DData& poly, Int32 edgeIdx, double offset, GS::VAArray<Polygon2DData>* resultPolys);
GEOMETRY_DLL_EXPORT GSErr	DeletePolygon2DDataVertexLow (Polygon2DData*	polygon2DData,
														  Int32				vertIndex);

GEOMETRY_DLL_EXPORT GSErr	GetPolygon2DDataPoint2DPosition 	  (const Polygon2DData& poly,  const Point2D& point, Boundary boundaries, RelativePosition* position, DetailedRelativePosition* detailed = nullptr);
GEOMETRY_DLL_EXPORT GSErr	GetPolygon2DDataBox2DPosition   	  (const Polygon2DData& poly,  const Box2DData& box, Boundary boundaries, RelativePosition* position, DetailedRelativePosition* detailed = nullptr);
GEOMETRY_DLL_EXPORT GSErr	GetPolygon2DDataPosition        	  (const Polygon2DData& poly1, const Polygon2DData& poly2, Boundary boundaries, RelativePosition* position, DetailedRelativePosition* detailed = nullptr);

GEOMETRY_DLL_EXPORT GSErr	UnifyPolygon2DData     (const Polygon2DData& poly1, const Polygon2DData& poly2, GS::VAArray<Polygon2DData>* resultPolys);
GEOMETRY_DLL_EXPORT GSErr	UnifyPolygon2DData     (GS::VAArray<Polygon2DData>* polys, PolyHoleHandling holeHandling = ReturnHoles, GS::AbortInterfaceBase* breaker = nullptr);
GEOMETRY_DLL_EXPORT GSErr	IntersectPolygon2DData (const Polygon2DData& poly1, const Polygon2DData& poly2,
													GS::VAArray<Polygon2DData>* resultPolys, Boundary boundaries = Boundary_Closed, RelativePosition* relativePosition = nullptr, DetailedRelativePosition* relativeDetailedPosition = nullptr,
													double epsilon = Eps);
GEOMETRY_DLL_EXPORT GSErr	SubstractPolygon2DData (const Polygon2DData& poly1, const Polygon2DData& poly2, GS::VAArray<Polygon2DData>* resultPolys, bool* changed = nullptr);

GEOMETRY_DLL_EXPORT GSErr	OrientPolygon2DData (Polygon2DData* poly, UIndex* vertIdx = nullptr, UIndex* edgeIdx = nullptr, UShort* reportMask = nullptr); // do NOT call it, it is a private fuction.

GEOMETRY_DLL_EXPORT void	ClipPolygon2D (Box2DData								*clip,		/* -> line params. 			*/
										   const Geometry::Polygon2DData*			poly,		/* -> polygon				*/
										   GS::VAArray<Geometry::Polygon2DData>*	respoly, 	/* <- result polygons		*/
										   Int32 									*wrcode);	/* <- warning error code   	*/

GEOMETRY_DLL_EXPORT bool	Polygon2DDataToPolyline (
								const Geometry::Polygon2DData& polygon2DData,
								Int32			inSubPoly,
								bool			makeBegZeroCoord,
								bool			useSeparator,
								const ArcDivParams& arcDivParams,
								Point2D**			poly_hCo,
								UIndex**		poly_subPolyEnds,
								USize*			poly_nCo,					/* mi13 */
								Int32**			later_edgeInd,
								Int32*			later_nEdge);

GEOMETRY_DLL_EXPORT GSErr	SegmentUpPolygon2DData (
								Polygon2DData*		polygon2DData,
								const ArcDivParams& arcDivParams);

GEOMETRY_DLL_EXPORT GSErr	SegmentUpPolygon2DData (
								const Polygon2DData&	polygon2DData,
								const ArcDivParams&		arcDivParams,
								Polygon2DData*			resultPolygon2DData);

GEOMETRY_DLL_EXPORT GSErr	AddPolygon2DDataHole (Polygon2DData* dest, const Polygon2DData& src, Int32 contour);

GEOMETRY_DLL_EXPORT	Geometry::PGPositionExt	SegmentInPolygon2DData (const Polygon2DData& polygon2DData, Sector segment, bool complement = false, GS::Array<Sector>* resSectors = nullptr);

GEOMETRY_DLL_EXPORT	bool	IntersectLineWithPolygon (const Polygon2DData& poly, const Point2D& c, const Vector2D& dir, GS::Array<Sector>* result);

GEOMETRY_DLL_EXPORT	Int32	ComparePolygon2DData (const Polygon2DData& ref, const Polygon2DData& poly, GS::HashSet<UIndex> *polyChanges = nullptr);

inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Geometry::Polygon2DData& poly)	{ return Geometry::ReadPolygon2DDataXML (ic, poly); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Geometry::Polygon2DData& poly)	{ return Geometry::WritePolygon2DDataXML (oc, poly); }
} // closing Geometry namespace


inline GSErr Geometry::ValidatePolygon2DData (Geometry::Polygon2DData*	poly, UIndex* vertIdx, UIndex* edgeIdx, UShort* reportMask)
{
	// using reportMask (example for orientation, bit0):
	// bit0 = 0 as input: if the orientation was incorrect during validation, bit0 = 1 as output
	// bit0 = 1 as input: just checking, returns NoError if the orientation was incorrect, otherwise bit0 = 0 as output

	GSErr	err = NoError;

	if (!poly->status.isBoundBoxValid) {
		err = Geometry::GetPolygon2DDataBoundBox (*poly, &poly->boundBox);
		if (err == NoError) {
			poly->status.isBoundBoxValid = true;	//lint !e915 (Implicit conversion (assignment) bool to unsigned int)
		}
	}

	if (err == NoError && !poly->status.isOrientationCorrect) {
		err = Geometry::OrientPolygon2DData (poly, vertIdx, edgeIdx, reportMask);
		if (err == NoError) {
			poly->status.isOrientationCorrect = true;	//lint !e915 (Implicit conversion (assignment) bool to unsigned int)
		}
	}

	return err;
}

#endif
