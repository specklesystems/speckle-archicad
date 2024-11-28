// contact person : KiP

#ifndef COORDINATE_SYSTEM_2D_HPP
#define COORDINATE_SYSTEM_2D_HPP

#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "Matrix23.hpp"
#include "UnitVector2D.hpp"

// =====================================================================================================================

namespace Geometry {

class CoordinateSystem2D;
class GeneralCoordinateSystem2D;
class OrthogonalTransformation2D;
class Transformation2D;
class OrthonormalizedCoordinateSystem2D;


DECLARE_EXCEPTION_CLASS (CoordinateSystemCreationError, GeometryException, Error, GEOMETRY_DLL_EXPORT)


class GEOMETRY_DLL_EXPORT CoordinateSystem2D
{
public:
	virtual ~CoordinateSystem2D ();

	Point2D		GetOrigo () const;
	Vector2D	GetXAxis () const;
	Vector2D	GetYAxis () const;

	Point2D		LocalToGlobal (const Point2D& localCoord) const;
	Point2D		GlobalToLocal (const Point2D& globalCoord) const;
	Vector2D	LocalToGlobal (const Vector2D& localVector) const;
	Vector2D	GlobalToLocal (const Vector2D& globalVector) const;

protected:
	bool IsMirrored () const;

	CoordinateSystem2D (const Point2D& origo, const Vector2D& xAxis, const Vector2D& yAxis);

	Point2D		GetOrigoPrivate () const;
	Vector2D	GetXAxisPrivate () const;
	Vector2D	GetYAxisPrivate () const;

private:
	Point2D origo;
	Vector2D xAxis;
	Vector2D yAxis;
	Geometry::Matrix23 localToGlobal;
	Geometry::Matrix23 globalToLocal;

	void InitMatrices ();
};


class GEOMETRY_DLL_EXPORT GeneralCoordinateSystem2D : public CoordinateSystem2D
{
public:
	static GeneralCoordinateSystem2D Create (const Point2D& origo, const Vector& xAxis, const Vector& yAxis);
	virtual ~GeneralCoordinateSystem2D ();

	bool IsOrthonormalized () const;
	GS::Optional<OrthonormalizedCoordinateSystem2D> ToOrthonotmalized () const;

	Transformation2D GetLocalToGlobalTrafo () const;
	Transformation2D GetGlobalToLocalTrafo () const;

	GS::Optional<GeneralCoordinateSystem2D> Transform (const Transformation2D& trafo) const;

private:
	GeneralCoordinateSystem2D (const Point2D& origo, const Vector& xAxis, const Vector& yAxis);
};


class GEOMETRY_DLL_EXPORT OrthonormalizedCoordinateSystem2D : public CoordinateSystem2D
{
public:
	using CoordinateSystem2D::LocalToGlobal;
	using CoordinateSystem2D::GlobalToLocal;

	static OrthonormalizedCoordinateSystem2D CreateGlobal ();
	static OrthonormalizedCoordinateSystem2D Create (const Point2D& origo, double xAxisAngle, bool mirrored = false);
	static OrthonormalizedCoordinateSystem2D Create (const Point2D& origo, const Vector& xAxis, bool mirrored = false);
	virtual ~OrthonormalizedCoordinateSystem2D ();

	UnitVector_2D	GetXAxis () const;
	UnitVector_2D	GetYAxis () const;

	GeneralCoordinateSystem2D ToGeneral () const;

	UnitVector_2D	LocalToGlobal (const UnitVector_2D& localVector) const;
	UnitVector_2D	GlobalToLocal (const UnitVector_2D& globalVector) const;

	OrthogonalTransformation2D GetLocalToGlobalTrafo () const;
	OrthogonalTransformation2D GetGlobalToLocalTrafo () const;

	OrthonormalizedCoordinateSystem2D Transform (const OrthogonalTransformation2D& trafo) const;

private:
	OrthonormalizedCoordinateSystem2D (const Point2D& origo, const Vector& xAxis, const Vector& yAxis);
};

}
#endif
