// Contact person: KiP

#ifndef HELIX3D_HPP
#define HELIX3D_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "Vector3D.hpp"
#include "Plane.hpp"
#include "Box3DData.h"


namespace Geometry 
{

class GenArc;
class HelixPlaneIntersectionCalculator;

class GEOMETRY_DLL_EXPORT Helix3D
{
public:
	enum ParamType 
	{
		AngleParam,
		LengthParam
	};

	static Helix3D		Create (const Plane& localCoordFrame, double radius, double pitchPerTurn, double begAngleParam, double endAngleParam, bool isInfinite);
	static Helix3D		CreateOneTwistPerpendicularHelix (const Point3D& begC, const Point3D& endC, double angle);

	const Plane&		GetLocalCoordFrame		() const;
	double				GetRadius				() const;
	double				GetBegParam				(ParamType paramType = AngleParam) const;
	double				GetEndParam				(ParamType paramType = AngleParam) const;
	double				GetPitch				() const;
	double				GetPitchPerTurn			() const;
	Vector3D			GetAxisDir				() const;
	Point3D				GetBegC					() const;
	Point3D				GetEndC					() const;
	Box3D				GetBounds				() const;
	bool				IsInfinite				() const;
	bool				Reflected				() const;
	
	bool				IsValidAngleParam		(double angleParam) const;
	double				ToLengthParam			(double angleParam) const;
	double				ToAngleParam			(double lengthParam) const;

	bool				IsPointOf				(const Point3D& point, bool extendToInfinite = false) const;
	Point3D				GetPoint				(double param, ParamType paramType = AngleParam) const;	
 	double				GetParam				(const Point3D& point, ParamType paramType = AngleParam) const;	
	Point3D				GetClosestPoint			(const Point3D& point) const;
	double				GetDistance				(const Point3D& point) const;
	Vector3D			GetTangential			(double param, ParamType paramType = AngleParam) const;	
	GS::Array<Point3D>	SegmentUp				(double tolerance) const;
	GenArc				ProjectAlongMainAxis	() const;										// the result GenArc is in LocalCoordFrame!

	// Modification
	void				ExtendToInfinite		();

	// Serialization
	GSErrCode			Read					(GS::IChannel& ic);
	GSErrCode			Write					(GS::OChannel& oc) const;

private:
	Plane		localCoordFrame;
	double		radius;
	double		pitch;
	double		begAngleParam;
	double		endAngleParam;
	bool		isInfinite;
	bool		reflected;

	double CalcX (double angleParam) const;
	double CalcY (double angleParam) const;
	double CalcZ (double angleParam) const;
	Point3D CalcLocalPoint (double angleParam) const;
	double CalcAngleParamFromLocalZ (double localZ) const;

	double CalcDX (double angleParam) const;
	double CalcDY (double angleParam) const;
	double CalcDZ (double angleParam) const;

	Helix3D ();	// disabled, use constructor functions

	friend HelixPlaneIntersectionCalculator;
};

GEOMETRY_DLL_EXPORT
GS::Array<Point3D>	CalcHelixLineIntersections (const Helix3D& helix, const Point3D& linePoint, const Vector3D& lineDir);

GEOMETRY_DLL_EXPORT
GS::Array<Point3D>	CalcHelixRayIntersections (const Helix3D& helix, const Point3D& rayStartPoint, const Vector3D& rayDir);

GEOMETRY_DLL_EXPORT
GS::Array<Point3D>	CalcHelixSectorIntersections (const Helix3D& helix, const Sector3D& sector);

GEOMETRY_DLL_EXPORT
GS::Array<Point3D>	CalcHelixPlaneIntersections (const Helix3D& helix, const PlaneEq& plane);

}

#endif
