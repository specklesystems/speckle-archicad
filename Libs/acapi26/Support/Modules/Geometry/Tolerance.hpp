#ifndef GEOMETRY_TOLERANCE_H_
#define GEOMETRY_TOLERANCE_H_
#pragma once

#include "GeometricDefinitions.h"

namespace Geometry {

class GEOMETRY_DLL_EXPORT AngleTolerance 
{ 
public:
	static AngleTolerance Default;	// former RadEps

	AngleTolerance ();
	explicit AngleTolerance (double value);

	operator double () const;

private:
	double value;
};


class GEOMETRY_DLL_EXPORT DistanceTolerance 
{
public:
	static DistanceTolerance Default;	// former Eps or EPS

	DistanceTolerance ();
	explicit DistanceTolerance (double value);

	operator double () const;

private:
	double value;
};


class GEOMETRY_DLL_EXPORT Tolerance 
{
public:
	Tolerance () = default;
	Tolerance (const DistanceTolerance& distance, const AngleTolerance& angle);

	operator AngleTolerance () const;
	operator DistanceTolerance () const;

	AngleTolerance		GetForAngle () const;
	DistanceTolerance	GetForDistance () const;

private:
	AngleTolerance angle;
	DistanceTolerance distance;
};

}

#endif
