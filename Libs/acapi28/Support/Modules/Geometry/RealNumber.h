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

constexpr double	BIGEPS			= 1E-01;
constexpr double	BigEps2			= 1E-02;
constexpr double	MEDEPS			= 1E-03;
constexpr double	BigEps3			= 1E-03;
constexpr double	EPS				= 1E-05;	/* 0.00001 Machinery zero for general purp.	*/
constexpr double	Eps				= 1E-05;
constexpr double	MiddleEps6		= 1E-06;
constexpr double	SmallEps9		= 1E-09;
constexpr double	SMALLEPS		= 1E-10;
constexpr double	SmallEps		= 1E-12;

constexpr double	Big1e9			= 1.00E9;
constexpr double	Big1Dot1e9		= 1.10E9;
constexpr double	Big1e25			= 1.00E25;
constexpr double	BiggestDouble	= 1.00E35;

#if !defined(MIN)
template<class Type>
inline Type MIN (Type x, Type y) { return x < y ? x : y; }
#endif

#if !defined(MAX)
template<class Type>
inline Type MAX (Type x, Type y) { return x > y ? x : y; }
#endif

constexpr double sqr (double x) { return x * x; }


GEOMETRY_DLL_EXPORT Int32	RoundToLong (double	x);

GEOMETRY_DLL_EXPORT short	RoundToShort (double x);

GEOMETRY_DLL_EXPORT short	RoundToShortLimited (double x, short limit);

GEOMETRY_DLL_EXPORT Int32	TruncToLong (double	x);

GEOMETRY_DLL_EXPORT short	LongToShort (Int32	xLong, short limit);

GEOMETRY_DLL_EXPORT short	SoftRoundToShortLimited (double x, short limit);


#endif
