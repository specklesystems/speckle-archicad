#if !defined (SIMPLEPOLYGON2DDATA_H)
#define SIMPLEPOLYGON2DDATA_H

#include "GeometricDefinitions.h"
#include "CoordTypedef.hpp"

class Box2DData;


namespace Geometry {

	GEOMETRY_DLL_EXPORT void	Cut_ToBox (Int32* nCoords, Point2D** cah, const Box2DData* bounds);
}

#endif
