#ifndef POLY2DTEMPRESETPOLYIDGUARD_HPP
#define POLY2DTEMPRESETPOLYIDGUARD_HPP
#pragma once

#include "Poly2DTypes.hpp"
#include "Array.hpp"
#include "GeometricDefinitions.h"


namespace Geometry {
class GEOMETRY_DLL_EXPORT Poly2DTempResetPolyIDGuard
{
public:
	Poly2DTempResetPolyIDGuard (IrregularPolygon2D& onePoly);
	Poly2DTempResetPolyIDGuard (MultiIrregularPolygon2D& multiPoly);
	virtual ~Poly2DTempResetPolyIDGuard ();

private:
	class GuardDataForPoly;
	GS::Array <GuardDataForPoly*>	data;
};
}

#endif

