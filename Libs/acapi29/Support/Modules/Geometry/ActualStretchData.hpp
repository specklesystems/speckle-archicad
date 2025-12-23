#ifndef GEOM_PPE_ACTUALSTRETCHDATA_HPP
#define GEOM_PPE_ACTUALSTRETCHDATA_HPP
#pragma once

#include "GeometricDefinitions.h"
#include "StretchZoneLimits.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT ActualStretchData
{
public:
	StretchZoneLimits originalLimits; 
	StretchZoneLimits finalLimits;
};


#endif //GEOM_PPE_ACTUALSTRETCHDATA_HPP

