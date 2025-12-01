// *********************************************************************************************************************
// File:			APIUnitUtilities.hpp
//
// Module:			ApiTools
// Namespace:		-
// Contact person:
//
// *********************************************************************************************************************


#ifndef APIUNITUTILITIES_HPP
#define APIUNITUTILITIES_HPP

#pragma once


#include "APIdefs_Environment.h"


inline bool		IsMetricAPIUnit (API_LengthTypeID lengthUnit)
{
	return lengthUnit == API_LengthTypeID::Meter		   ||
		   lengthUnit == API_LengthTypeID::Decimeter	   ||
		   lengthUnit == API_LengthTypeID::Centimeter	   ||
		   lengthUnit == API_LengthTypeID::Millimeter;
}


inline bool		IsMetricAPIUnit (API_AreaTypeID areaUnit)
{
	return areaUnit == API_AreaTypeID::SquareMeter		   ||
		   areaUnit == API_AreaTypeID::SquareCentimeter	   ||
		   areaUnit == API_AreaTypeID::SquareMillimeter;
}


inline bool		IsMetricAPIUnit (API_VolumeTypeID volumeUnit)
{
	return volumeUnit == API_VolumeTypeID::CubicMeter	   ||
		   volumeUnit == API_VolumeTypeID::Liter		   ||
		   volumeUnit == API_VolumeTypeID::CubicCentimeter ||
		   volumeUnit == API_VolumeTypeID::CubicMillimeter;
}


#endif
