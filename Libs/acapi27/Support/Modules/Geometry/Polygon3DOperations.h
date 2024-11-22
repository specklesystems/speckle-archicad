// *****************************************************************************
// 3D POLYGON OPERATIONS
// Combination of the struct and the callback functions
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************

#if !defined (POLYGON3DOPERATIONS_H)
#define POLYGON3DOPERATIONS_H

#pragma once

#include "GeometricDefinitions.h"
#include "Point2DData.h"
#include "Box2DData.h"
#include "HalfPlane2DData.h"
#include "Polygon2DOperations.h"
#include "Plane3DData.h"

namespace Geometry {

struct PG3DEDGEEXT {
	PGEDGEEXT	d2;						/*  32 */	/* default 2D data					*/
	double		zz;						/*   8 */	/* z coordinate						*/
};				    		/* 40 */

struct PG3DPOLYEXT;

typedef	PG3DEDGEEXT	(*GetPG3DEdgeProcExt)	(const PG3DPOLYEXT* polygon, Int32 ind);
//typedef	GSErr		(*SetPG3DEdgeProcExt)	(PG3DPOLYEXT* polygon, const PG3DEDGEEXT* pgedge);

struct PG3DPOLYEXT {
	PGPOLYEXT	d2;						/*  48 */	/* default 2D data					*/
	double		zmin, zmax; 			/*  16 */ 	/* z extent							*/
	double		plana, planb,
				planc, pland;			/*  32 */	/* plane coefficients				*/
	GetPG3DEdgeProcExt	getEdge;	// gets the i-th segment (vertex and edge (straight or arced) starting from it) of the polygon
};							/* 96 */

enum PGPoly3DPosition {
	InfrontPlane_3DPosition		=	1,
	BehindPlane_3DPosition		=	2,
	OnPlane_3DPosition			=	3,
	SplitPlane_3DPosition		=	4
};

GEOMETRY_DLL_EXPORT short	PG3DPolyPositionExt (
					PG3DPOLYEXT*	poly,
					const PlaneEq&	plane);

GEOMETRY_DLL_EXPORT GSErr	PG3DSplitPolyExt (
					PG3DPOLYEXT*	poly,
					const PlaneEq&	plane,
					PG3DPOLYEXT*	pFront,
					GS::PagedArray<Geometry::PG3DEDGEEXT>*			frontEdges,
					PG3DPOLYEXT*	pBack,
					GS::PagedArray<Geometry::PG3DEDGEEXT>*			backEdges,
					short*			splitRes);


// with Exceptions


GEOMETRY_DLL_EXPORT Geometry::PGPoly3DPosition	PGX3DPolyPositionExt (
					PG3DPOLYEXT*	poly,
					const PlaneEq&	plane);

GEOMETRY_DLL_EXPORT void	                	PGX3DSplitPolyExt (
					PG3DPOLYEXT*	poly,
					const PlaneEq&	plane,
					PG3DPOLYEXT*	pFront,
					GS::PagedArray<Geometry::PG3DEDGEEXT>*			frontEdges,
					PG3DPOLYEXT*	pBack,
					GS::PagedArray<Geometry::PG3DEDGEEXT>*			backEdges,
					short*			splitRes);

GEOMETRY_DLL_EXPORT GSErrCode	ReadXMLPG3DEDGEEXT (GS::XMLIChannel& ic, PG3DEDGEEXT& p);
GEOMETRY_DLL_EXPORT GSErrCode	WriteXMLPG3DEDGEEXT (GS::XMLOChannel& oc, const PG3DEDGEEXT& p);
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Geometry::PG3DEDGEEXT& p)	{ return Geometry::ReadXMLPG3DEDGEEXT (ic, p); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Geometry::PG3DEDGEEXT& p)	{ return Geometry::WriteXMLPG3DEDGEEXT (oc, p); }

}


#endif
