#ifndef GEOM_PPE_STRETCHZONELIMITS_HPP
#define GEOM_PPE_STRETCHZONELIMITS_HPP
#pragma once

#include "GeometricDefinitions.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT StretchZoneLimits
{
public:
	StretchZoneLimits ();
	double horLowLimit, horHighLimit;
	double vertLowLimit, vertHighLimit;

	bool IsValidHorizontalLimits () const;
	bool IsValidVerticalLimits () const;

	double GetHorizontalSize () const;
	double GetVerticalSize () const;
};


#endif //GEOM_PPE_STRETCHZONELIMITS_HPP

