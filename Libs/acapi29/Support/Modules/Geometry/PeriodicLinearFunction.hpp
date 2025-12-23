// Contact person : NN

#ifndef PERIODIC_LINEAR_FUNCTION_HPP
#define PERIODIC_LINEAR_FUNCTION_HPP

// from GSRoot
#include "Array.hpp"
#include "Pair.hpp"

// from Geometry
#include "GeometricDefinitions.h"

namespace Geometry {

//=================================================================
//
//	PeriodicLinearFunction
//
//	Implements a 1th order periodic spline.
//
//=================================================================

class GEOMETRY_DLL_EXPORT PeriodicLinearFunction
{
private:
	GS::Array<GS::Pair<double, double>> controlPoints;
	double								periodLength;

public:
	PeriodicLinearFunction (double periodLength);
	PeriodicLinearFunction ();

	void						AddNewTriangularFunction	(double startPoint, double topPoint, double endPoint, double topValue);
	double						GetValue					(double position) const;
	void						AddOtherFunction			(const PeriodicLinearFunction& other);
	double						GetPeriodLength				() const;
	GS::Array<double>			GetControlPoints			() const;

private:
	bool	IsNormalized					(double position) const;
	double	NormalizePosition				(double position) const;
	UInt32	ControlPointIndexBeforePosition (double normalizedPosition) const;
	UInt32	ControlPointIndexAfterPosition	(double normalizedPosition) const; 
	double	GetValueByTwoControlPoints		(UInt32 firstControlPoint, UInt32 secondControlPoint, double normalizedPosition) const;
	double	GetValueByTwoValues				(double x1, double functionValueInX1, double x2, double functionValueInX2, double normalizedPosition) const;
	void	InsertPoint						(double normalizedPosition);
	void	ModifyControlPoints				(double startPoint, double topPoint, double endPoint, double topValue);
	void	ModifyControlPointsInternal		(double x1, double functionValueInX1, double x2, double functionValueInX2);
	UInt32	GetControlPointIndexBeforeIndex (UInt32 index) const;
	UInt32	GetControlPointIndexAfterIndex	(UInt32 index) const;
};
	
} // namespace Geometry

#endif