#ifndef _PARAMETRIC_LINE_3D_HPP_
#define _PARAMETRIC_LINE_3D_HPP_
#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "Line3D.hpp"

// =====================================================================================================================

namespace Geometry {

class GEOMETRY_DLL_EXPORT ParametricLine3D : public Line3D
{
public:
	ParametricLine3D (const Coord3D& linePointAtZeroParameter, const UnitVector_3D& direction);
	virtual ~ParametricLine3D ();

	class GEOMETRY_DLL_EXPORT DistanceParameter
	{
	public:
		DistanceParameter (double value) : value (value) {}
		double Get () const { return value; }

	private:
		double value;
	};

	Coord3D							GetPointAt (const DistanceParameter& parameter) const;
	GS::Optional<DistanceParameter>	GetParameterOf (const Coord3D& linePoint) const;

private:
	ParametricLine3D () = delete;

	Coord3D m_basePoint;
};

}
#endif
