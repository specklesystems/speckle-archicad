// *****************************************************************************
// Spline and its operations.
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************

#if !defined (SPLINE_H)
#define SPLINE_H

#pragma once

#include "GeometricDefinitions.h"
#include "CoordTypedef.hpp"
#include "Vector2D.hpp"


CmpResult CmpDoubles (const void	*p1,
					  const void	*p2);


struct Sector;
class Box2DData;


namespace Geometry {

struct DirType;

class GenArc;
class Circle2D;
class BezierDetails;


/*							CALCULATIONS ON SPLINES						*/

GEOMETRY_DLL_EXPORT void	CubicToBezier (
						Point2D 	*pco0, 				/* sm007 */
						Point2D 	*pco1,
						Point2D 	*pco2,
						Point2D 	*pco3,
						const double  *x0,
						const double  *y0,
						const double  *x1,
						const double  *y1,
						const double  *x2,
						const double  *y2,
						const double  *x3,
						const double  *y3);

GEOMETRY_DLL_EXPORT void	BezierToCubic (
						const Point2D 	*pco0, 				/* sm007 */
						const Point2D 	*pco1,
						const Point2D 	*pco2,
						const Point2D 	*pco3,
						double  *x0,
						double  *y0,
						double  *x1,
						double  *y1,
						double  *x2,
						double  *y2,
						double  *x3,
						double  *y3);

GEOMETRY_DLL_EXPORT void	CalcSplineCoeffs ( bool opened,
						bool cyclic,
						Int32 	n,
						double  **x0,
						double  **y0,
						double  **x1,
						double  **y1,
						double  **x2,
						double  **y2,
						double  **x3,
						double  **y3,
						double  xtf,
						double  ytf,
						double  xtl,
						double  ytl);

GEOMETRY_DLL_EXPORT void	GetBezierDirCoords (const Point2D&	pCo,
												const DirType&	pDir,
												Point2D&		cPrev,
												Point2D&		cNext);

GEOMETRY_DLL_EXPORT void	SetBezierDirType (const Point2D&	pCo,
											  DirType&			pDir,
											  const Point2D&	cPrev,
											  const Point2D&	cNext);

GEOMETRY_DLL_EXPORT bool	CalcSpline (const Point2D* const	coords, /* sm009 */
										DirType* const			dirs,
										const Int32				nCo,
										const bool				closed);

GEOMETRY_DLL_EXPORT double		SplineLen (
									Int32			nCo,
									const Point2D*	coords, /* sm175 */
									const DirType*	dirs,
									double			a,
									double			b);

GEOMETRY_DLL_EXPORT double		SplineLen (
									const BezierDetails&	bezDet,
									double 					a,
									double 					b);

GEOMETRY_DLL_EXPORT double		Spline_ax (
									Int32			nCo,
									const Point2D*	coords, /* sm175 */
									const DirType*	dirs,
									double 			a,
									double			givenLen,
									bool			closed);

GEOMETRY_DLL_EXPORT double		Spline_ax (
									const BezierDetails&	bezDet,
									double 					a,
									double					givenLen,
									bool					closed);


GEOMETRY_DLL_EXPORT double		GetSplineParam (
									double			x0,
									double			y0,
									double			x1,
									double			y1,
									double			x2,
									double			y2,
									double			x3,
									double			y3,
									const Point2D&	cc);

GEOMETRY_DLL_EXPORT double	GetSplineSegmCloseCoord (Int32						segment,
													 Int32						nCoords,
													 const Point2D				*coords,
													 const Geometry::DirType	*dirs,
													 const Point2D				*co,
													 Point2D	  				*prCo);

GEOMETRY_DLL_EXPORT double		GetSplineCloseCoord (
									Int32			nCoords,
									const Point2D*	coords,
									const DirType*	dirs,
									bool			closed,
									const Point2D*	co,
									Point2D*		prCo);

GEOMETRY_DLL_EXPORT double		GetSplineCloseCoord (
									const BezierDetails&	bezDet,
									const Point2D&			co,
									Point2D&				prCo);

GEOMETRY_DLL_EXPORT double		GetSplineMaxDist (
									const Point2D*	coords, /*hot00.02.22 - dev. for Tillberg */
									const DirType*	dirs,
									Int32			segment,
									Point2D**		cc,
									Int32			nCoords);

GEOMETRY_DLL_EXPORT void		BezierPoints (
									const Point2D*	pCoords,
									const DirType*	pDirs,
									Int32			ibeg,
									Int32			iend,	/* sm012 */
									Point2D*		bezp);	// array of 4 Coords required!

GEOMETRY_DLL_EXPORT void		BezierPoints4 (
									const Point2D*	coords, /* sm007 */
									const DirType*	dirs,
									Int32			ibeg,
									Int32			iend, /* sm012 */
									Point2D*		p0,
									Point2D*		p1,
									Point2D*		p2,
									Point2D*		p3);

GEOMETRY_DLL_EXPORT void		BezierPoints4 (
									const BezierDetails&	bezDet,
									Int32					ibeg,
									Point2D*				p0,
									Point2D*				p1,
									Point2D*				p2,
									Point2D*				p3);

GEOMETRY_DLL_EXPORT Point2D		GetSplineVal (
									Int32			nCoords,
									const Point2D*	pCoords,
									const DirType*	pDirs,
									double 			t);

GEOMETRY_DLL_EXPORT Point2D		GetSplineVal (
									const BezierDetails&	bezDet,
									double 					t);

GEOMETRY_DLL_EXPORT Vector2D	GetSplineTan (
									Int32			nCo,
									const Point2D*	coords,
									const DirType*	dirs,
									double 			t,
									bool			forw,
									bool			norm);

GEOMETRY_DLL_EXPORT Vector2D	GetSplineTan (
									const BezierDetails&	bezDet,
									double 					t,
									bool					forw,
									bool					norm);

GEOMETRY_DLL_EXPORT void		SegmentToBox (
									Box2DData*	boundbox, /* sm009 */
									double		x0,
									double		y0,
									double		x1,
									double		y1,
									double		x2,
									double		y2,
									double		x3,
									double		y3,
									double		a,
									double		b); /* sm012 */

GEOMETRY_DLL_EXPORT Box2DData	SplineToBox (const BezierDetails& bezier);

GEOMETRY_DLL_EXPORT void		GetSplineDMinDMax (
									const double* const    p,
									const double		   a,
									const double		   b,
									const Point2D&		   fa,
									const Point2D&		   fb,
									double*				   dmin,
									double*				   dmax);

GEOMETRY_DLL_EXPORT bool		SameSplines (
									const BezierDetails& bezDet1,
									const BezierDetails& bezDet2);

GEOMETRY_DLL_EXPORT void	XSplineLine (
								Int32					nCo,
								const Point2D			*coords,
								const Geometry::DirType	*dirs,
								bool					closed,
								Int32					segment, /* sm122 */
								const Sector			*s,
								GS::Array<double>&		hSect);

GEOMETRY_DLL_EXPORT void	XSplineLine (
								const BezierDetails&	bezDet,
								Int32					segment, /* sm122 */
								const Sector&			s,
								GS::Array<double>&		hSect);

GEOMETRY_DLL_EXPORT void	XSplineSector (
								Int32						nCo,
								const Point2D*				coords,
								const Geometry::DirType*	dirs,
								bool						closed,
								const Sector*				s,
								GS::Array<double>&			hSect);

GEOMETRY_DLL_EXPORT void	XSplineSector (
								const BezierDetails&	bezDet,
								const Sector&			s,
								GS::Array<double>&		hSect);

GEOMETRY_DLL_EXPORT void	XSplineCircle (
								Int32					nCo,
								const Point2D			*coords,
								const Geometry::DirType	*dirs,
								bool					closed,
								Int32					segment,		/* sm122 */
								const Circle2D			*c,
								bool					elliptic,		/* ellipszis */ /* sm121 */
								double					angle,			/* tengely szoge */
								double					ratio,			/* == a/b */
								GS::Array<double>&		hSect);

GEOMETRY_DLL_EXPORT void	XSplineCircle (
								const BezierDetails&	bezDet,
								Int32					segment,		/* sm122 */
								const Circle2D			*c,
								bool					elliptic,		/* ellipszis */ /* sm121 */
								double					angle,			/* tengely szoge */
								double					ratio,			/* == a/b */
								GS::Array<double>&		hSect);

GEOMETRY_DLL_EXPORT void	XSplineGenArc (
								Int32					nCo,
								const Point2D*			coords,
								const DirType*			dirs,
								bool					closed,
								const GenArc*			arcT,
								GS::Array<double>&		hSect);

GEOMETRY_DLL_EXPORT void	XSplineGenArc (
								const BezierDetails&	bezDet,
								const GenArc&			arcT,
								GS::Array<double>&		hSect);

GEOMETRY_DLL_EXPORT void	XSplineSpline (
								 Int32 				nCo1,
								 const Point2D		*coords1,
								 const DirType		*dirs1,
								 bool				closed1,
								 Int32 				nCo2,
								 const Point2D		*coords2,
								 const DirType		*dirs2,
								 bool				closed2,
								 GS::Array<double>&	hSect1,
								 GS::Array<double>*	hSect2,
								 Int32				limitedToSegment_1 = 0,
								 Int32				limitedToSegment_2 = 0);

GEOMETRY_DLL_EXPORT void	XSplineSpline (
								 const BezierDetails&	bezDet1,
								 const BezierDetails&	bezDet2,
								 GS::Array<double>&		hSect1,
								 GS::Array<double>*		hSect2);

GEOMETRY_DLL_EXPORT void	SplineSegNormTangPoints (
								Int32 				nCo,
								const Point2D		*coords,
								const DirType		*dirs,
								Int32				segment,
								const Point2D		*baseC,
								GS::Array<double>&	hSect,
								double				xPixelSize, /* calcInWin->p_X */
								bool				isNormal);

GEOMETRY_DLL_EXPORT void	SplineSegNormTangPoints (
								const BezierDetails&	bezDet,
								Int32					segment,
								const Point2D			*baseC,
								GS::Array<double>&		hSect,
								double					xPixelSize, /* calcInWin->p_X */
								bool					isNormal);

GEOMETRY_DLL_EXPORT void	SplineSegNormTangPoints (
								const BezierDetails&	bezDet,
								const Point2D			*cursor,
								const Point2D			*baseC,
								GS::Array<double>&		hSect,
								double					xPixelSize, /* calcInWin->p_X */
								bool					isNormal);

GEOMETRY_DLL_EXPORT void	DivSplinePart (
							  Int32 					nCo,
							  const Point2D				*coords,
							  const Geometry::DirType	*dirs,
							  bool						closed,
							  bool						forw,
							  const Point2D&			startCo,
							  double					partLength,
							  GS::Array<double>&		hSect);

GEOMETRY_DLL_EXPORT void	DivSplineDiff (
							  Int32						nCo,
							  const Point2D				*coords,
							  const Geometry::DirType	*dirs,
							  bool						closed,
							  bool						forw,
							  double					diff,
							  GS::Array<double>&		hSect);

GEOMETRY_DLL_EXPORT bool	TangentCircle (
							   Int32					nCo,
							   const Point2D			*coords,
							   const Geometry::DirType	*dirs,
							   double					t1,
							   double					t2,
							   const Point2D&			f1,
							   const Point2D&			f2,
							   double					arcDiff,
							   Point2D					*origo,
							   bool 					*exist);

GEOMETRY_DLL_EXPORT void	DivSplineDiff_Arc (
								  Int32 					nCo,
								  const Point2D				*coords,
								  const Geometry::DirType	*dirs,
								  bool						closed,
								  bool						forw,
								  double					diff,
								  GS::Array<double>&		hSect);

GEOMETRY_DLL_EXPORT void	IVDir (GS::PlatformSign inplatform, DirType *pDir);
GEOMETRY_DLL_EXPORT void	IVDir (GS::PlatformSign inplatform, GS::PlatformSign toplatform, DirType *pDir);


GEOMETRY_DLL_EXPORT Int32	ACSpline2NUBS (
								Int32 				nCo,
								const Point2D		*coords,
								const DirType		*dirs,
								bool				closed,
								double				**knots,
								Point2D				**cpts);

GEOMETRY_DLL_EXPORT Int32	NUBS2ACSpline (
								Int32				m,
								Int32				nLev,
								double				**knots,
								Point2D				**cpts,
								Point2D				**coords,
								Geometry::DirType	**dirs,
								Int32				**endIndices);

GEOMETRY_DLL_EXPORT GSErrCode	ReadXMLDirType (GS::XMLIChannel& ic, Geometry::DirType& dt);
GEOMETRY_DLL_EXPORT GSErrCode	WriteXMLDirType (GS::XMLOChannel& oc, const Geometry::DirType& dt);
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Geometry::DirType& dt)	{ return Geometry::ReadXMLDirType (ic, dt); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Geometry::DirType& dt)	{ return Geometry::WriteXMLDirType (oc, dt); }


}	// namespace Geometry


#endif
