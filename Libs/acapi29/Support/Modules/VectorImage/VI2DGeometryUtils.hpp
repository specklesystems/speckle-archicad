#ifndef	VI2DGEOMETRY_UTILS_HPP
#define	VI2DGEOMETRY_UTILS_HPP

#pragma once

// from VectorImage
#include "VectorImageExport.h"

class Box2DData;

class VI2DGeometryInterface;

class VI_DLL_CLASS_EXPORT VI2DGeometryUtils 
{
public:
	static Box2DData GetBounds (const VI2DGeometryInterface& geometry);
	static bool		 AreVertexIdsUnique (const VI2DGeometryInterface& geometry);
};

#endif
