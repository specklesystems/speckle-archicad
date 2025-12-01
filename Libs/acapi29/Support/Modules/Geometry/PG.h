// *****************************************************************************
// 2D/3D POLYGON OPERATIONS
// See also:
//		Marx/Engels/Lenins:		Az elet nagy kerdesei	 (Officina 1967)
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************

/*vv2*/

#ifndef PG_H
#define PG_H

#pragma once

#include "GeometricDefinitions.h"

#include "Box2DData.h"
#include "Polygon2DOperations.h"

struct	DESC;

/*************************************************************************************
**																					**
** 									Type definitions								**
**																					**
*************************************************************************************/

/*
**	The following structures own the minimum information to describe a 2D polygon.
**	Additional data can be assigned extending the data records.
*/

struct PGPOLY {
	Geometry::PGPOLYSTATUSEXT	status;			/*   2 */	/* status							*/
	UShort		userStatus;
	short		par1;					/*	 2 */	/* free to use						*/
	Int32		par2;					/*   4 */	/* free to use						*/
	Int32		fedge, ledge;			/*   8 */	/* first, last edge					*/
	Box2DData	boundBox;				/*  32 */	/* extent box in 2D					*/
};				    				/* 48 */

typedef struct {
	Geometry::PGEDGESTATUSEXT	status;			/*   2 */	/* status							*/
	unsigned short	userStatus;
	short	par1;					/*	 2 */	/* ???								*/
	Int32	par2;					/*	 4 */	/* free to use						*/
	Point2D	begPt;					/*  16 */	/* edge start point					*/
	double	invlen;					/*   8 */	/* edge length	  1.0/(dx*dx+dy*dy)	*/
} PGEDGE;				    		/* 32 */

typedef struct {
	Geometry::PGEDGESTATUSEXT	status;			/*   2 */	/* status							*/
	short	par1;					/*	 2 */	/* free to use						*/
	Int32	par2;					/*   4 */	/* free to use						*/
	double	ox,oy;					/*  16 */	/* origo x,y						*/
	double	radius;					/*   8 */	/* radius							*/
	double	fi1,fi2;				/*  16 */	/* start / end point angle			*/
} PGARC;							/* 48 */	/* csm100 */

/*
**	The following structures own the minimum information to describe a 3D polygon.
**	Additional data can be assigned extending the data records.
*/

typedef struct {
	PGPOLY	d2;						/*  48 */	/* default 2D data					*/
	double	zmin, zmax; 			/*  16 */ 	/* z extent							*/
	double	plana, planb,
			planc, pland;			/*  32 */	/* plane coefficients				*/
} PG3DPOLY;							/* 96 */

typedef struct {
	PGEDGE	d2;						/*  32 */	/* default 2D data					*/
	double	zz;						/*   8 */	/* z coordinate						*/
} PG3DEDGE;				    		/* 40 */



typedef	PGEDGE*		GetPGEdgeProc (void* userData, Int32 ind);
typedef	PGARC*		GetPGArcProc (Int32 ind);
typedef	PG3DEDGE*	GetPG3DEdgeProc (void* userData, Int32 ind);

typedef	GSErr		NewPGEdgeProc (PGEDGE *pgedge, PGARC *pgarc, Int32 *ind);
typedef	GSErr		NewPG3DEdgeProc (void* userData, PG3DEDGE *pgedge, Int32 *ind);

typedef GSErr		NewPGArcProc (PGARC *pgarc,Int32 *ind);				/* csm100	*/

typedef	GSErr		NewPGPolyProc (PGPOLY *pgpoly);
typedef	GSErr		NewPG3DPolyProc (PG3DPOLY *pgpoly);

typedef	GSErr		NewPGSegmentProc (const Point2D *bp, const Point2D *ep);


/*************************************************************************************
**																					**
** 										Constants									**
**																					**
*************************************************************************************/

/* Algorithmic constants							*/
/*--------------------------------------------------*/
#define	PGEDGE_WORKLIMIT	200			/* Limit for effective operations			*/

/* Status bits										*/
/* (bits 4-7 are reserved for internal use)			*/
/*--------------------------------------------------*/
#define	POLY_NORMAL			0
#define	POLY_REVORIENT		0x0001		/* clockwise polygon orientation			*/

#define	EDGE_NORMAL			0
#define	EDGE_BEGHOLE		0x0001 		/* starting edge of a hole					*/
#define	EDGE_ENDCONT		0x0002		/* last edge of the contoure or a hole		*/
#define	EDGE_INVIS			0x0004		/* invisible edge							*/
#define	EDGE_SPLITLINE		0x0008		/* edge from a splitline					*/
#define	EDGE_ARC			0x0010		/* edge is an arc							*/
#define EDGE_ENDPOLY		0x0020		/* last edge of the whole polygon			*/

#define	ARC_NORMAL			0x0000		/* 									csm100	*/
#define	ARC_REVORIENT		0x1000		/* clockwise arc orientation		csm100	*/

/* Special values for 'invlen'						*/
/*--------------------------------------------------*/
#define	INVLEN_NOTINITED	-1.0
#define	INVLEN_ZEROEDGE		-2.0


/* Special return values (error codes)				*/
/*--------------------------------------------------*/
#define	PGERR_ALGORITHM		1
#define	PGERR_ZEROPOLY1		2
#define	PGERR_ZEROPOLY2		3
#define	PGERR_SELFINTERSECT	4

enum PGSameDirEdgeHandling {PGRemoveSameDirEdges, PGPreserveSameDirEdges};

/*************************************************************************************
**																					**
** 									Function prototypes								**
**																					**
*************************************************************************************/


/* 2D operations									*/
/*--------------------------------------------------*/

GEOMETRY_DLL_EXPORT void	PGInitCtrlGlobals (double	theEps,
											   double	zeroEdge,
											   double	sensEps,
											   double	sensEdge);

GEOMETRY_DLL_EXPORT double	PGGetMainEps (void);
GEOMETRY_DLL_EXPORT double	PGGetSensEps (void);

GEOMETRY_DLL_EXPORT bool	PGUsePrevPoly2Hereafter (void);
GEOMETRY_DLL_EXPORT void	PGStopUsingPrevPoly2 (void);

GEOMETRY_DLL_EXPORT GSErr	PGInitPoly2DOperations (PGSameDirEdgeHandling edgeHandling = PGRemoveSameDirEdges);

GEOMETRY_DLL_EXPORT GSErr	PGPolyMakeRegular (
					PGPOLY *poly, GetPGEdgeProc *getEdge, void* userData,
					NewPGEdgeProc *newEdge, NewPGPolyProc *newPoly);

GEOMETRY_DLL_EXPORT GSErr	PGPolyMakeRegular2 (
					PGPOLY *poly, GetPGEdgeProc *getEdge, void* userData, GetPGArcProc *getArc,
					NewPGEdgeProc *newEdge, NewPGPolyProc *newPoly, bool resolveSelfInters);

enum PGPolyStatus {
	UnknownStatus			= -1,
	PolysOverlap			= 0,
	Poly1CoversPoly2		= 1,
	Poly2CoversPoly1		= 2,
	PolysEqual				= 3,
	PolysDisjunct			= 4,
	PolysDisjunct_Node		= 5,
	PolysDisjunct_Edge		= 6
};

GEOMETRY_DLL_EXPORT GSErr	PGPolyPosition (
					PGPOLY *poly1, GetPGEdgeProc *getEdge1, void* userData1, GetPGArcProc *getArc1,
					PGPOLY *poly2, GetPGEdgeProc *getEdge2, void* userData2, GetPGArcProc *getArc2,
					short *status);

GEOMETRY_DLL_EXPORT GSErr	PGPolyUnion (
					PGPOLY *poly1, GetPGEdgeProc *getEdge1, void* userData1, GetPGArcProc *getArc1,
					PGPOLY *poly2, GetPGEdgeProc *getEdge2, void* userData2, GetPGArcProc *getArc2,
					NewPGEdgeProc *newEdge, NewPGPolyProc *newPoly,
					short *status);

GEOMETRY_DLL_EXPORT GSErr	PGPolyIntersection (
					PGPOLY *poly1, GetPGEdgeProc *getEdge1, void* userData1, GetPGArcProc *getArc1,
					PGPOLY *poly2, GetPGEdgeProc *getEdge2, void* userData2, GetPGArcProc *getArc2,
					NewPGEdgeProc *newEdge, NewPGPolyProc *newPoly,
					short *status);

GEOMETRY_DLL_EXPORT GSErr	PGPolyDifference (
					PGPOLY *poly1, GetPGEdgeProc *getEdge1, void* userData1, GetPGArcProc *getArc1,
					PGPOLY *poly2, GetPGEdgeProc *getEdge2, void* userData2, GetPGArcProc *getArc2,
					NewPGEdgeProc *newEdge, NewPGPolyProc *newPoly,
					short *status);

GEOMETRY_DLL_EXPORT void	PGClosePoly2DOperations (void);


enum PGPosition {
	PGInsidePoly		= 0,
	PGOutsidePoly		= 1,
	PGOnPolyEdge		= 2
};

GEOMETRY_DLL_EXPORT short	PGCoordInPoly (const PGPOLY *poly, GetPGEdgeProc *getEdge, void* userData,
										   const Point2D *p, bool mainContOnly);

GEOMETRY_DLL_EXPORT short	PGSegmentInPoly (
					PGPOLY *poly, GetPGEdgeProc *getEdge, void* userData, Point2D *bp, Point2D *ep, bool complement,
					NewPGSegmentProc *newSegment);

GEOMETRY_DLL_EXPORT double	PGPolyArea (PGPOLY *poly, GetPGEdgeProc *getEdge, void* userData, double *thole);

GEOMETRY_DLL_EXPORT GSErrCode	ReadXMLPG3DPOLY (GS::XMLIChannel& ic, PG3DPOLY& p);
GEOMETRY_DLL_EXPORT GSErrCode	WriteXMLPG3DPOLY (GS::XMLOChannel& oc, const PG3DPOLY& p);

inline GSErrCode	ReadXML (GS::XMLIChannel& ic, PG3DPOLY& p)	{ return ReadXMLPG3DPOLY (ic, p); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const PG3DPOLY& p)	{ return WriteXMLPG3DPOLY (oc, p); }

/* 3D operations									*/
/*--------------------------------------------------*/

#define	InfrontPlane		1
#define	BehindPlane			2
#define	OnPlane				3
#define SplitPlane			4

GEOMETRY_DLL_EXPORT short	PG3DPolyPosit (
					PG3DPOLY *poly, GetPG3DEdgeProc *getEdge, void* userData,
					double plana, double planb, double planc, double pland);

GEOMETRY_DLL_EXPORT GSErr	PG3DSplitPoly (PG3DPOLY *poly, GetPG3DEdgeProc *get3DEdge, void* userData,
										   double plana, double planb, double planc, double pland,
										   PG3DPOLY *pFront, DESC *frontEdges,
										   PG3DPOLY *pBack, DESC *backEdges,
										   short *splitRes);

GEOMETRY_DLL_EXPORT void	PGSetDebugFlags (unsigned char	flags);

#endif
