// *********************************************************************************************************************
// Description:		Solar System-related functions
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (ECPILTIC_HPP)
#define ECPILTIC_HPP

#pragma once

// from Geometry
#include	"GeometricDefinitions.h" 

struct GSTimeRecord;

namespace Geometry {


struct	GEOMETRY_DLL_EXPORT		SunAngles
{
	double	sunZ;			/*deg*/
	double	sunXY;			/*deg*/

	SunAngles (void) : 
		sunZ (0.0),
		sunXY (0.0)
	{
	}
};


struct	GEOMETRY_DLL_EXPORT		SunRiseAndSetTimes
{
	short	sunRiseHr;
	short	sunRiseMin;
	short	sunRiseSec;
	short	sunSetHr;
	short	sunSetMin;
	short	sunSetSec;

	SunRiseAndSetTimes (void) :
		sunRiseHr (0),
		sunRiseMin (0),
		sunRiseSec (0),
		sunSetHr (0),
		sunSetMin (0),
		sunSetSec (0)
	{
	}
};


struct	GEOMETRY_DLL_EXPORT		SunData
{
	SunAngles			sunAngles;
	SunRiseAndSetTimes	sunRiseAndSetTimes;
};



GEOMETRY_DLL_EXPORT
SunAngles	CalcSunAngles (	const short		year,				/*-2000 .. 6000*/
							const short		month,				/*1 .. 12*/
							const short		day,				/*1 .. 31*/
							const short		hour,				/*0 .. 24*/
							const short		minute,				/*0 .. 59*/
							const short		second,				/*0 .. <60*/
							const bool		sumTime,
							const short		timeZoneInMinutes,	
							const double	longitude,			/*negative west of Greenwich, -180.0 .. 180.0*/
							const double	latitude,			/*negative south of equator, -90.0 .. 90.0*/
							const double	elevation,			/*meter*/
							const double	north);

GEOMETRY_DLL_EXPORT
SunData		CalcSunData (const short	year,				/*-2000 .. 6000*/
						 const short	month,				/*1 .. 12*/
						 const short	day,				/*1 .. 31*/
						 const short	hour,				/*0 .. 24*/
						 const short	minute,				/*0 .. 59*/
						 const short	second,				/*0 .. <60*/
						 const bool		sumTime,
						 const short	timeZoneInMinutes,
						 const double	longitude,			/*negative west of Greenwich, -180.0 .. 180.0*/
						 const double	latitude,			/*negative south of equator, -90.0 .. 90.0*/
						 const double	elevation,			/*meter*/
						 const double	north);

GEOMETRY_DLL_EXPORT
void	InvCalcSunAngles (	double			sunAzimuth,
							double			sunAltitude,
							GSTimeRecord&	gmt,
							double&			latitude,
							double&			longitude);


}	// namespace Geometry

#endif // ECPILTIC_HPP
