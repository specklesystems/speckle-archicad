/****************************************************************************/
/*																			*/
/*				Cut Line/Arc/PolyLine/Spline and Hatch with a polygon		*/
/*																			*/
/****************************************************************************/
#if !defined (CUTELEMS_H)
#define CUTELEMS_H

#pragma once

#include "GeometricDefinitions.h"
#include "Point2DData.h"


struct PolyArcRec;
struct Sector;

namespace Geometry {

struct DirType;
struct Polygon2DData;
class BezierDetails;
class GenArc;

struct GEOMETRY_DLL_EXPORT CutParam
{
	double param;
	UIndex edgeIndex;		// in case of polyline: 1..nEdge, otherwise 0
	
	CutParam () :
		param (0.0),
		edgeIndex (0)
	{
	}


	explicit CutParam (double _param, UIndex _edgeIndex = 0) :
		param (_param),
		edgeIndex (_edgeIndex)
	{
	}


	bool	InternalPoint (double tLen, UIndex maxEdgeIndex = 0) const
	{
		if (edgeIndex == 0) {
			DBASSERT (maxEdgeIndex == 0);
			return 0.0 < param && param < tLen;
		} else {
			DBASSERT (1 <= edgeIndex && edgeIndex <= maxEdgeIndex);
			return ((edgeIndex != 1 && edgeIndex != maxEdgeIndex) ||
					(edgeIndex == 1 && 0.0 < param && param < 1.0) ||
					(edgeIndex == maxEdgeIndex && 0.0 < param && param < 1.0));
		}
	}

	bool	IsEdgeBeg (void) const
	{
		return (fabs (param) < Eps);
	}


	bool	IsEdgeEnd (void) const
	{
		return (fabs (param - 1.0) < Eps);
	}


	double	ToOldStyleCutParam (void) const
	{
		if (edgeIndex == 0)
			return param;
		else
			return param + static_cast<double> (edgeIndex - 1);
	}


	void	ConvertFromOldStyleParam (double cutParam)
	{
		// csak polyline-ra!
		edgeIndex	= static_cast<UIndex> (cutParam + 1 + Eps);
		param		= cutParam - (edgeIndex - 1);
	}


	bool	operator== (const CutParam& rightOp) const
	{
		return (edgeIndex == rightOp.edgeIndex && IsNear (param, rightOp.param));
	}


	bool	operator!= (const CutParam& rightOp) const
	{
		return !(*this == rightOp);
	}


	bool	operator> (const CutParam& rightOp) const
	{
		return (edgeIndex > rightOp.edgeIndex || (edgeIndex == rightOp.edgeIndex && IsGreater (param, rightOp.param)));
	}


	bool	operator< (const CutParam& rightOp) const
	{
		return (edgeIndex < rightOp.edgeIndex || (edgeIndex == rightOp.edgeIndex && IsLess (param, rightOp.param)));
	}
};

						
							
GEOMETRY_DLL_EXPORT CutParam	CalcElemParam  (
						short				typ,			// spline-ra nem hivjuk, mert ott tudjuk a parametert
						const Sector*		pSector,
						const GenArc*		pGenArc,
						Int32				nCoords,		// polyLine
						const Point2D*		pCoords,		// polyLine
						Int32				nArcs,			// polyLine
						const PolyArcRec*	pArcs,			// polyLine
						const Point2D*		c,
						Int32				inIndex,		// ???
						bool				pointOnCurve);	// set to true if you know that c is on curve, applies to polyline only


GEOMETRY_DLL_EXPORT void  GetElemCoord (
					const CutParam&		cutParam,
					short				typ,
					const Sector*		pSector,
					const GenArc*		pGenArc,
					Int32				nCoords,		// polyLine
					const Point2D*		pCoords,		// polyLine
					const DirType*		pDirs,			// spline
					Int32				nArcs,			// polyLine
					const PolyArcRec*	pArcs,			// polyLine
					Point2D*				c);



typedef void PieceFunc (
				short			typ,
				Sector*			pSector,
				GenArc*			pGenArc,
				Int32			nCoords,		// spline/polyLine/polygon
				Point2D*			pCoords,		// spline/polyLine/polygon
				DirType*		pDirs,			// spline
				UInt32*			pVertInds,		// polyLine/polygon
				Int32			nEnds,			// polygon
				Int32*			pEnds,			// polygon
				Int32			nArcs,			// polyLine/polygon
				PolyArcRec*		pArcs,			// polyLine/polygon
				//Polygon2DData*	pPoly,			// polygon (alternative form)
				const void*		userData);


GEOMETRY_DLL_EXPORT void	MakePiece (
										short				typ,
										const Sector*		pSector,
										const GenArc*		pGenArc,
										Int32				nCoords,		// spline/polyLine
										const Point2D*		pCoords,		// spline/polyLine
										const DirType*		pDirs,			// spline
										const UInt32*		pVertInds,		// polyLine
										Int32				nArcs,			// polyLine
										const PolyArcRec*	pArcs,			// polyLine
										const CutParam&		cutParam1,
										const CutParam&		cutParam2,
										PieceFunc*			StorePiece,		// call back for storing pieces
										const void*			userData);		// user data for call back func.

}

#endif
