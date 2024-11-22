/****************************************************************************/
/* 			Constants for geometric calculations.							*/
/* 			Geometry, platform-independent									*/
/*																			*/
/* 			Namespaces:        Contact person:								*/
/*     			Geometry          RJ, FGY									*/
/*																			*/
/****************************************************************************/

#if !defined (REALNUMBER_H)
#define	REALNUMBER_H

#pragma once

#include "Definitions.hpp"
#include "GeometricDefinitions.h"

#include <limits>

/****************************************************************************/
/*																			*/
/*								Geometric Primitives						*/
/*																			*/
/****************************************************************************/

/* -------------------------- Mathematical constants ---------------------- */
constexpr double INF = std::numeric_limits<double>::infinity ();

static constexpr double	BIGEPS			= 1E-01;
static constexpr double	BigEps2			= 1E-02;
static constexpr double	MEDEPS			= 1E-03;
static constexpr double	BigEps3			= 1E-03;
static constexpr double	EPS				= 1E-05;	/* 0.00001 Machinery zero for general purp.	*/
static constexpr double	Eps				= 1E-05;
static constexpr double	MiddleEps6		= 1E-06;
static constexpr double	SmallEps9		= 1E-09;
static constexpr double	SMALLEPS		= 1E-10;
static constexpr double	SmallEps		= 1E-12;

static constexpr double	Big1e9			= 1.00E9;
static constexpr double	Big1Dot1e9		= 1.10E9;
static constexpr double	Big1e25			= 1.00E25;
static constexpr double	BiggestDouble	= 1.00E35;

#if !defined(MIN)
template<class Type>
inline Type MIN (Type x, Type y) { return x < y ? x : y; }
#endif

#if !defined(MAX)
template<class Type>
inline Type MAX (Type x, Type y) { return x > y ? x : y; }
#endif

inline double sqr (double x) { return x * x; }


GEOMETRY_DLL_EXPORT Int32	RoundToLong (double	x);

GEOMETRY_DLL_EXPORT short	RoundToShort (double x);

GEOMETRY_DLL_EXPORT short	RoundToShortLimited (double x, short limit);

GEOMETRY_DLL_EXPORT Int32	TruncToLong (double	x);

GEOMETRY_DLL_EXPORT short	LongToShort (Int32	xLong, short limit);

GEOMETRY_DLL_EXPORT short	SoftRoundToShortLimited (double x, short limit);


namespace Geometry {

GEOMETRY_DLL_EXPORT Int32	Round (double x);

}


#endif
