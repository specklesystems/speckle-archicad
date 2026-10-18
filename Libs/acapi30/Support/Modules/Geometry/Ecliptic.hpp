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

// from Geometry
#include "GeometricDefinitions.h"


struct GSTimeRecord;


namespace Geometry {


struct SunAngles
{
	double sunZ = 0.0;	/*deg*/
	double sunXY = 0.0;	/*deg*/
};


struct SunRiseAndSetTimes
{
	short sunRiseHr = 0;
	short sunRiseMin = 0;
	short sunRiseSec = 0;
	short sunSetHr = 0;
	short sunSetMin = 0;
	short sunSetSec = 0;
};


struct SunData
{
	SunAngles			sunAngles;
	SunRiseAndSetTimes	sunRiseAndSetTimes;
};



GEOMETRY_DLL_EXPORT
SunAngles	CalcSunAngles (	short	year,				/*-2000 .. 6000*/
							short	month,				/*1 .. 12*/
							short	day,				/*1 .. 31*/
							short	hour,				/*0 .. 24*/
							short	minute,				/*0 .. 59*/
							short	second,				/*0 .. <60*/
							bool	sumTime,
							short	timeZoneInMinutes,
							double	longitude,			/*negative west of Greenwich, -180.0 .. 180.0*/
							double	latitude,			/*negative south of equator, -90.0 .. 90.0*/
							double	elevation,			/*meter*/
							double	north);

GEOMETRY_DLL_EXPORT
SunData		CalcSunData (short	year,				/*-2000 .. 6000*/
						 short	month,				/*1 .. 12*/
						 short	day,				/*1 .. 31*/
						 short	hour,				/*0 .. 24*/
						 short	minute,				/*0 .. 59*/
						 short	second,				/*0 .. <60*/
						 bool	sumTime,
						 short	timeZoneInMinutes,
						 double	longitude,			/*negative west of Greenwich, -180.0 .. 180.0*/
						 double	latitude,			/*negative south of equator, -90.0 .. 90.0*/
						 double	elevation,			/*meter*/
						 double	north);

GEOMETRY_DLL_EXPORT
void	InvCalcSunAngles (	double			sunAzimuth,
							double			sunAltitude,
							GSTimeRecord&	gmt,
							double&			latitude,
							double&			longitude);


}	// namespace Geometry


#endif // ECPILTIC_HPP
