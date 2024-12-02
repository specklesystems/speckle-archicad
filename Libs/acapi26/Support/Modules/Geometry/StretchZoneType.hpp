#ifndef GEOM_PPE_STRETCHZONETYPE_HPP
#define GEOM_PPE_STRETCHZONETYPE_HPP

#pragma once

#include "GeometricDefinitions.h"
#include <string>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class GEOMETRY_DLL_EXPORT StretchZoneType
{
	Compressible = 1, 
	Incompressible = 2, 
	Undefined = 0
};

GEOMETRY_DLL_EXPORT void Convert (const std::string& s, StretchZoneType& t);
GEOMETRY_DLL_EXPORT void Convert (const StretchZoneType& t, std::string& s);


#endif
