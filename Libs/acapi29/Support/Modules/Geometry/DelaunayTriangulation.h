// *****************************************************************************
// Delaunay triangulation. PROTOTYPES FOR TD... ROUTINES
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************

#ifndef DELAUNAY_TRIANGULATION_H
#define DELAUNAY_TRIANGULATION_H

#pragma once

#include "GeometricDefinitions.h"
#include "Polygon2DOperations.h"

#define	TDUNDEF				-1				/* undef index 		*/

#define	TDINVALID			0x0001			/*	0b0000000000000001	##	*/
#define	TDINVISIBIT			0x0002			/*	0b0000000000000010	##	*/
#define	TDFORCEDBIT			0x0004			/*	0b0000000000000100	##	*/
#define	TDCONTOURBIT		0x0008			/*	0b0000000000001000	##	*/

#define	TD_ISINVALID(s)		(((s)->status & TDINVALID) 		!= 0)
#define	TD_ISINVIS(s)		(((s)->status & TDINVISIBIT) 	!= 0)
#define	TD_ISFORCED(s)		(((s)->status & TDFORCEDBIT) 	!= 0)
#define	TD_ISCONTOUR(s)		(((s)->status & TDCONTOURBIT) 	!= 0)


namespace GS
{
	class ProcessControl;
}


namespace Geometry {

struct TDVer {
	enum {
		PolyVertex,
		MeshLevelVertex
	} type;
	Int32 index;
};

struct TDTri {
	TDVer v1;
	TDVer v2;
	TDVer v3;
};

typedef	struct {			/* 24 bytes */
	short	status;			/* status */
	short	filler1;		/* filler */
	Int32 	left;			/* left triangle */
	Int32 	right;			/* right triangle */
	Int32 	org;			/* origin */
	Int32 	dest;			/* destination */
	Int32	inputOrig;		/* origo in input mesh level */
	Int32	inputDest;		/* destination in input mesh level	*/
} TDOEDGE;

typedef	struct {			/* 16 bytes */
	short	filler1;		/* filler */
	short	status;			/* status */
	Int32 	edges[3];		/* edges of the triangle */
} TDOTRIANGLES;

typedef	struct {						/* 8 bytes					*/
	Int32			edges[3];			/* edges of the triangle	*/
	short			status;				/* status					*/
	short			filler;				/* filler					*/
} TDTRIANGLE;

typedef	struct tdedge {					/* 16 bytes								*/
	Int32			num;				/* index in the corresponding quad edge */
	Int32			tri;				/* left triangle						*/
	Int32			coorInd;			/* non-topological information			*/
	Int32			next;				/* newt ccw edge						*/
} TDEDGE;

typedef	struct {						/* 80 bytes (4 * 16 + 16)						*/
	TDEDGE			e[4];				/* edges, it must be remained the first field	*/
	Int32			inputOrig;			/* origo in input mesh level					*/
	Int32			inputDest;			/* destination in input mesh level				*/
	short			status;				/* status										*/
	short			filler1;			/* filler										*/
	Int32			filler2;			/* destination in input mesh level				*/
} QUADEDGE;

typedef	struct {						/* 24 bytes							*/
	Int32			orig;				/* origin index						*/
	Int32			dest;				/* dest index						*/
	bool			contour;			/* contour ?						*/
	bool			filler1;			/* filler							*/
	short			filler2;			/* filler							*/
	Int32			inputOrig;			/* origo in input mesh level		*/
	Int32			inputDest;			/* destination in input mesh level	*/
	Int32			filler3;			/* filler							*/
} TDFORCEDEDGE;

typedef	struct {						/* 12 bytes							*/
	short			status;				/* status							*/
	short			pos;				/* position modifier				*/
	Int32			sector;				/* sector no.						*/
	Int32			next;				/* next pt. in sector.				*/
} TDPOINTINFO;

typedef	struct   {						/* 184 bytes */
	const double	*polyx;				/* TDInit parameter							*/
	const double	*polyy;				/* TDInit parameter							*/
	const double	*polyz;				/* TDInit parameter							*/
	const short		*mask;				/* TDInit parameter							*/
	Int32			ncoord;				/* TDInit parameter							*/
	Int32			numMeshLevelPts;	/* TDInit parameter							*/
	Int32			numSubLineEnds;		/* TDInit parameter							*/
	Int32			filler1;			/* filler									*/
	const Int32		*subLineEnds;		/* TDInit parameter							*/
	const double	*meshLevelx;		/* TDInit parameter							*/
	const double	*meshLevely;		/* TDInit parameter							*/
	const double	*meshLevelz;		/* TDInit parameter							*/
	Int32			startingEdge;		/* internal variable for algorithmical use	*/
	Int32			numCPoints;			/* contour points							*/
	Point3D			*points;			/* points									*/
	unsigned short	*contour;			/* ID of the contour for each point			*/
	Int32			*pointId;			/* ID of the point							*/
	bool			*positiveContour;	/* true for a ccw contour					*/
	TDPOINTINFO		*pointInfo;			/* info										*/
	QUADEDGE		*qedges;			/* edges									*/
	TDTRIANGLE		*triangles;			/* triangles								*/
	TDFORCEDEDGE	**forcedEdges;		/* forced edge								*/
	Int32			numForcedEdges;		/* num of forced lines						*/
	Int32			allocForcedEdges;	/* num of forced lines allocated						*/
	Int32			numPoints;			/* num of points							*/
	Int32			firstFreeQedge;		/* first free quad edge						*/
	Int32			allocQedges;		/* max. #(edges) = 3*numPts-6				*/
	Int32			firstFreeTriangle;	/* first free triangle						*/
	Int32			allocTriangles;		/* max. #(triangles) = 2*numPts-5			*/
	Int32			filler2;			/* filler									*/
	Geometry::PGEDGEEXT *pgEdges;			/* PGPoly edges (PGCoordInPoly)				*/
	short			errNo;				/* error number								*/
	short			filler3;			/* filler									*/
	Geometry::PGPOLYEXT	polyExt;
	double			minx;				/* encl. box								*/
	double			maxx;				/* encl. box								*/
	double			miny;				/* encl. box								*/
	double			maxy;				/* encl. box								*/
	Int32			*sectors;			/* sectors									*/
	Int32			filler4;
} SUBDIVISION;

class GEOMETRY_DLL_EXPORT DelaunayTriangulation {
private:
	SUBDIVISION	subDiv;


	inline Int32		TDRot (Int32 	e);
	inline Int32		TDinvRot (Int32 	e);
	inline Int32		TDSym (Int32 	e);
	inline TDEDGE*		TDSymPtr (Int32	e);
	inline Int32		TDOnext (Int32 	e);
	inline Int32		TDOprev (Int32 	e);
	//inline long		TDDnext (long	e);
	inline Int32		TDDprev (Int32	e);
	inline Int32		TDLnext (Int32 	e);
	inline Int32		TDLprev (Int32 	e);
	//inline long		TDRnext (long 	e);
	//inline long		TDRprev (long 	e);
	inline Int32		TDOrgIndex (Int32 	e);
	inline Int32		TDDestIndex (Int32 	e);
	inline void		TDOrgDestIndex (Int32	e,
										Int32	*org,
										Int32	*dest);
	inline Point2D		TDDest2D (Int32 	e);
	inline Point2D		TDOrg2D (Int32 	e);
	inline void		TDSplice (Int32	a,
								  Int32	b);
	inline void		TDAllocQedges (Int32	n);
	inline void		TDFreeQedges (void);
	inline void		TDFreeQedge (Int32	qedge);
	inline Int32		TDAllocQedge (void);
	inline Int32		TDMakeEdge (void);
	inline void		TDDeleteEdge (Int32	e);
	inline void		TDTriangleInit (Int32	tri);
	inline Int32		TDAllocTriangle (void);
	inline void		TDFreeTriangle (Int32	tri);
	inline Int32		TDMakeTriangle (void);
	inline void		TDDeleteTriangle (Int32	tri);
	inline void		TDAllocTriangles (Int32	n);
	inline void		TDFreeTriangles (void);
	inline void		TDSetTriangle (Int32		tri,
									   Int32		e0,
									   Int32		e1,
									   Int32		e2);
	inline Int32		TDInTriangle (Int32		tri,
									  Point2D		*xx);

	inline void		TDQuadEdgeInit (Int32 	qedge);
	inline void		TDEndPoints (Int32		e,
									 Int32		org,
									 Int32		dest);
	inline Int32		TDConnect (Int32		a,
								   Int32		b);
	inline void		TDSwap (Int32	e);
	inline double		TDTriArea (Point2D	*a,
								   Point2D	*b,
								   Point2D	*c);
	inline bool		TDInCircle (Point2D	*a,
									Point2D	*b,
									Point2D	*c,
									Point2D	*d);
	inline bool		TDccw (Point2D	a,
							   Point2D	b,
							   Point2D	c);
	inline bool		TDRightOf (const Point2D&	x,
								   Int32		e);
	inline bool		TDOnEdge (Point2D		*x,
								  Int32		e);
	inline bool		TDOnSector (Point2D	*x,
									Sector	*s);
	inline void		TDSubdivisionSetup (Int32		a,
											Int32		b,
											Int32		c);
	inline Int32		TDLocate (Int32	x);
	inline void		TDInsertSite (Int32	x);
	inline void		TDAllocPoints (void);
	inline void		TDAllocLevelPoints (void);
	inline void		TDAllocContourPoints (void);
	inline bool		TDAllocForcedEdges (void);
	inline Int32		TDInSector (Int32 sector, Int32 what, Int32 max);
	inline void		TDDeleteEquPts (void);
	inline void		TDDeleteEquPt (Int32 		deleted,
									   Int32			substitute);
	inline void		TDUnchain (Int32 		deleted,
								   Int32			substitute);
	inline void		TDBreakEdges (void);
	inline void		TDBreakOnForcedEdges (Int32	x);
	inline void		TDBreakIntoTwo (Int32	forcedEdge,
										Int32	x);
	inline void		TDFreePoints (void);
	inline void		TDFreeForcedEdges (void);
	inline void		TDCalcBox (void);
	inline void		TDInitPointSectors (Int32 p);
	inline void		TDSetPointNext (Int32 p, Int32 next);
	inline Int32		TDGetPointNext (Int32 p);
	inline void		TDRemovePoint (Int32 prev, Int32 p);
	inline void		TDAddPointSector (Int32 p, Int32 s, short pos);
	inline void		TDCalcSectors (void);
	inline void		TDLast3Points (void);
	inline void		TDOPoints (double				**pointsx,
								   double				**pointsy,
								   double				**pointsz,
								   Geometry::TDOEDGE	*edges,
								   Int32					numEdges,
								   Int32					*numPts,
								   bool					compress);
	inline Point3D		TDTriangleNormal (Int32	tri);
	inline void		TDFilterEdges (void);
	inline void		TDStandAlonePoints (GS::ProcessControl& processControl);
	inline void		TDInsertStaPt (Int32		lonelyID,
									   bool	startIcl,
									   bool	endIcl);
	inline Int32		TDFindEquContourPoint (Point2D	*pt);
	inline Int32		TDFindEquContourEdge (Point2D		*org,
											  Point2D		*dest);
	inline Int32		TDFindNextContourPoint (Int32	p);
	inline Int32		TDFindPrevContourPoint (Int32	p);

	inline bool		TDIsStandAlone (GS::ProcessControl& processControl, Int32	index);

	inline void		TDForceEdges (	GS::ProcessControl&		processControl, 
									Int32					orig,
									Int32					dest,
									bool					contour,
									Int32					inputOrig,
									Int32					inputDest);
	inline void		TDForce (GS::ProcessControl& processControl);
	inline void		TDAllocPgEdges (void);
	inline void		TDFreePgEdges (void);
	inline short		TDCoordInPoly (Point2D	*xc);
	inline Int32		TDPolyPt (Point2D	*xc);
	//inline bool		TDPolyOnEdge (Point2D	*xc);
	inline void		TDDeleteOutEdges (void);
	inline void		TDDeleteOutTriangles (void);
	inline Geometry::TDOEDGE*	TDOCompressEdges (GS::ProcessControl&		processControl, 
												  Geometry::TDOEDGE			*edges,
												  Int32						*numEdges,
												  Geometry::TDOTRIANGLES	*triangles,
												  Int32						numTriangles);
	inline Point3D*		TDGetPointPtr (Int32	index);
	inline TDEDGE*		TDGetEdgePtr (Int32	index);
	inline QUADEDGE*	TDQedgeOfEdgeIndex (Int32	e);
	inline QUADEDGE*	TDGetQedgePtr (Int32	index);
	inline TDTRIANGLE*	TDGetTrianglePtr (Int32	tri);
	inline void		TDSetErr (short	errNo);
	inline bool		TDIsErr (void);
	inline bool		TDCheck	(GS::ProcessControl& processControl);
	inline bool		TDCheckContourEdge (Int32	org,
											Int32	dest);
	inline Geometry::TDOEDGE*		TDOEdges (void);
	inline Geometry::TDOTRIANGLES*	TDOTriangles (void);

	//void TDDumpTriangles ();
	#if defined( DEBUVERS_VT )
	void TDDumpTrianglesVRML ( float r = 1, float g = 1 , float b = 1,			// polygon color
										float er = 1, float eg = 0 , float eb = 0, bool write_edges = false );	// edge color
	inline bool		TDCheckTriangles	(void);	 // checks self-intersection of triangles
	#endif

	void	TDExit (void);

	bool	TDTriangulate (	GS::ProcessControl&		processControl,
							TDOEDGE					**edges,
							Int32					*numEdges,
							TDOTRIANGLES			**triangles,
							Int32					*numTriangles,
							bool					compress);

public:
	DelaunayTriangulation (
				const double	*polyx,					/* polygon x coords (see GetPolyNodes) */
				const double	*polyy,					/* polygon y coords (see GetPolyNodes) */
				const double	*polyz,					/* polygon z coords (see GetPolyNodes) */
				const short		*mask,					/* polygon masks (see GetPolyNodes) */
				Int32			ncoord,					/* num of polygon coords (see GetPolyNodes) */
				const double	*meshLevelx,			/* mesh level x coords */
				const double	*meshLevely,			/* mesh level y coords */
				const double	*meshLevelz,			/* mesh level z coords */
				Int32			numMeshLevelPts,		/* num of mesh level points */
				const Int32		*subLineEnds,			/* ptr to mesh level subline ends */
				Int32			numSubLineEnds);		/* number of mesh level subline ends */

	~DelaunayTriangulation ();

	bool	TDTriangulate (	GS::ProcessControl&		processControl,
							double					**pointsx,
							double					**pointsy,
							double					**pointsz,
							Int32					*numPts,
							TDOEDGE					**edges,
							Int32					*numEdges,
							TDOTRIANGLES			**triangles,
							Int32					*numTriangles,
							bool					compress);

	bool	TDTriangulate (GS::Array<TDTri>& tris);

};

GEOMETRY_DLL_EXPORT short	TDGetHeightAtPoint (
								const double*		pointsx,
								const double*		pointsy,
								const double*		pointsz,
								Int32				numPts,
								const TDOEDGE*		edges,
								Int32				numEdges,
								const TDOTRIANGLES*	triangles,
								Int32				numTriangles,
								const Point2d&		ptLoc,
								double*				height);

GEOMETRY_DLL_EXPORT bool	TDGetPointsAtLine  (
								const double*		pointsx,
								const double*		pointsy,
								const double*		pointsz,
								Int32				numPts,
								const TDOEDGE*		edges,
								Int32				numEdges,
								const TDOTRIANGLES*	triangles,
								Int32				numTriangles,
								const Point2d&		ptArcBeg,
								const Point2d&		ptArcEnd,
								double				angArc,
								bool				onlyForced,
								double				**linex,
								double				**liney,
								double				**linez,
								double				**lineAngle,
								Int32				*numLines);
}//namespace
#endif
