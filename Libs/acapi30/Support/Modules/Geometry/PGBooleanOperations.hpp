// *****************************************************************************
// Polygon Boolean Operations
//
// Module: Geometry
// Contact person: HK
//
// *****************************************************************************

#ifndef PGBOOLEANOPERATIONS_H
#define PGBOOLEANOPERATIONS_H

#include "Polygon2DOperations.h"

namespace Geometry {

enum FillingMethod { Alternative, WindingRulePos, WindingRule };
typedef bool (*BoolFunctionType) (bool, bool);

class GEOMETRY_DLL_EXPORT PGBooleanOperations
{
	void* pgBooleanObject;

public:
	PGBooleanOperations (GS::AbortInterfaceBase* breaker);
	~PGBooleanOperations ();

	PGRelPolyPosExt	DoBoolean (const PGPOLYEXT *poly1,
							   const PGPOLYEXT *poly2,
							   FillingMethod f1,
							   FillingMethod f2,
							   BoolFunctionType boolFunction,
							   bool* isPolyRegular = nullptr,
							   PolyHoleHandling holeHandling = ReturnHoles);					// can throw

	void			GetResultPolygons (PGRESPOLYEXT* newPolygons);			// can throw
	void			PrintBooleanReport (const char* opName, PGRelPolyPosExt status, GS::OChannel& outChannel);
};

GEOMETRY_DLL_EXPORT
void PolyUnion (const PGPOLYEXT&		 poly1,
				const PGPOLYEXT&		 poly2,
				PGRESPOLYEXT*			 newPolygons,
				PGRelPolyPosExt*		 status,
				GS::AbortInterfaceBase*  breaker   = nullptr);	// can throw

GEOMETRY_DLL_EXPORT
void PolyIntersection (const PGPOLYEXT&		  	poly1,
					   const PGPOLYEXT&		 	poly2,
					   PGRESPOLYEXT*			newPolygons,
					   PGRelPolyPosExt*		  	status,
					   GS::AbortInterfaceBase*  breaker   = nullptr);	// can throw

GEOMETRY_DLL_EXPORT
void PolyDifference (const PGPOLYEXT&			poly1,
					 const PGPOLYEXT&			poly2,
					 PGRESPOLYEXT*				newPolygons,
					 PGRelPolyPosExt*			status,
					 GS::AbortInterfaceBase*  	breaker   = nullptr);	// can throw

GEOMETRY_DLL_EXPORT
void PolyRegularize (const PGPOLYEXT&			poly,
					 PGRESPOLYEXT*				newPolygons,
					 PGRegulHoleHandling		regul,
					 GS::AbortInterfaceBase* 	breaker   = nullptr,
					 PGRelPolyPosExt*			status	= nullptr,
					 PolyRegularizationMode   	mode = PolyRegularizationMode_Default);	// can throw

GEOMETRY_DLL_EXPORT
void PolyPosition (const PGPOLYEXT&		  	poly1,
				   const PGPOLYEXT&		  	poly2,
				   PGRelPolyPosExt*		  	status,
				   GS::AbortInterfaceBase*  breaker   = nullptr);	// can throw

GEOMETRY_DLL_EXPORT
bool IsPolyRegular (const PGPOLYEXT&		 poly,
					GS::AbortInterfaceBase*  breaker   = nullptr);	// can throw


namespace ResultSegmentPos {
	enum Et { Empty = 0x00, Inside = 0x01, Outside = 0x02, OnEdge = 0x04,
					InsideOrOn = Inside | OnEdge, OutsideOrOn = Outside | OnEdge, NotOnEdge = Inside | Outside };
}

GEOMETRY_DLL_EXPORT
PGPositionExt		SectorInPoly (const PGPOLYEXT &poly,
								  FillingMethod fMeth,
								  const Sector &sector,
								  ResultSegmentPos::Et pos,
								  PGRESSECTOREXT *newSectors,
								  GS::AbortInterfaceBase* breaker = nullptr);			// can throw

struct CircleArc
{
	Point2D	begC, endC;
	Point2D	origo;
};

GEOMETRY_DLL_EXPORT GSErrCode	ReadXML (GS::XMLIChannel& ic, CircleArc& arc);
GEOMETRY_DLL_EXPORT GSErrCode	WriteXML (GS::XMLOChannel& oc, const CircleArc& arc);

GEOMETRY_DLL_EXPORT
PGPositionExt		ArcInPoly (const PGPOLYEXT &poly,
							   FillingMethod fMeth,
							   const CircleArc &arc,
							   ResultSegmentPos::Et pos,
							   GS::Array<CircleArc> *newArcs,
							   GS::AbortInterfaceBase* breaker = nullptr);			// can throw



class GEOMETRY_DLL_EXPORT ResultSegments {
public:
	virtual void Segment (const Segment2D& segment, UInt32 origIndex) = 0;
	virtual void Arc (const CircleArc& arc, UInt32 origIndex) = 0;
	virtual ~ResultSegments ();
};

GEOMETRY_DLL_EXPORT
PGPositionExt		SegmentsInPoly (const PGPOLYEXT &poly,
								    FillingMethod fMeth,
								    const GS::Array<Segment2D>& segments,
								    const GS::Array<CircleArc>& arcs,
								    ResultSegmentPos::Et pos,
									ResultSegments* result,
								    GS::AbortInterfaceBase* breaker = nullptr);			// can throw
}

#endif
