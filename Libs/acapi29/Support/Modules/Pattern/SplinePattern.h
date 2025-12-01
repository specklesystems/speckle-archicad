/****************************************************************/
/*																*/
/*		Rajzolas alrutinjai:									*/
/*			-vonal, kor, ...									*/
/*																*/
/****************************************************************/

#ifndef HIGHGRAPHICS_H
#define HIGHGRAPHICS_H

#pragma once


#include	"PatternExport.h"


PATTERN_DLL_EXPORT
Coord	Cubic (const double t, const double* const px);

PATTERN_DLL_EXPORT
void	CollectSySpline (
						const bool      				isSplineClosed,
						const double					t0,
						const double					t1,
						const Int32                   	nCo,
						const Coord* const   			coords,
						const Geometry::DirType* const	dirs,
						Int32* const                  	nSplineSegments,
						Coord** const                	splineSegments,
						Int32** const                 	splineIndices,
						const double                 	tolerance,
						bool							toApi,
						bool							calcBox,
						Box2DData*						bounds,
						const Box2DData*				filterBox = nullptr);

// hot05.06.09: This function calculates t0 and t1 to cover the whole spline
// and then passes it on to CollectSySpline
PATTERN_DLL_EXPORT
void	CollectSySpline_NoFilter (
						const bool      				isSplineClosed,
						const Int32                   	nCo,
						const Coord* const   			coords,
						const Geometry::DirType* const	dirs,
						Int32* const                  	nSplineSegments,
						Coord** const                	splineSegments,
						Int32** const                 	splineIndices,
						const double                 	tolerance,
						bool							toApi,
						bool							calcBox,
						Box2DData*						bounds);

PATTERN_DLL_EXPORT
void	CollectSplineForInput (
							   const Int32                  n,
							   const double* const * const	x0,
							   const double* const * const	y0,
							   const double* const * const	x1,
							   const double* const * const	y1,
							   const double* const * const	x2,
							   const double* const * const	y2,
							   const double* const * const	x3,
							   const double* const * const	y3,
							   double						maxSplineDifference,
							   Int32* const                 nSplineSegments,
							   Coord** const				splineSegments,
							   bool							toApi,
							   bool							calcBox,
							   Box2DData*					bounds);

#endif
