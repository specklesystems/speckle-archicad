// contact person : KiP

#ifndef COORDINATE_SYSTEM_3D_HPP
#define COORDINATE_SYSTEM_3D_HPP

#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "Matrix34.hpp"
#include "UnitVector3D.hpp"

// from GSRoot
#include "ChecksumUpdater.hpp"

// =====================================================================================================================

namespace Geometry {

class CoordinateSystem3D;
class GeneralCoordinateSystem3D;
class OrthonormalizedCoordinateSystem3D;
class Transformation3D;
class OrthogonalTransformation3D;

class GEOMETRY_DLL_EXPORT CoordinateSystem3D
{
public:
	class GEOMETRY_DLL_EXPORT CreationFailed : public GeometryException 
	{
	public:
		virtual ~CreationFailed ();
	};

	virtual ~CoordinateSystem3D ();

	Point3D		LocalToGlobal (const Point3D& localCoord) const;
	Point3D		GlobalToLocal (const Point3D& globalCoord) const;
	Vector3D	LocalToGlobal_V (const Vector3D& localVector) const;
	Vector3D	GlobalToLocal_V (const Vector3D& globalVector) const;

	bool											IsOrthonormalized () const;
	GS::Optional<OrthonormalizedCoordinateSystem3D> ToOrthonotmalized () const;
	GeneralCoordinateSystem3D						ToGeneral () const;

	void		WriteCoreContentForChecksum (GS::ChecksumUpdater& updater) const;
protected:
	CoordinateSystem3D (const Point3D& origo, const Vector3D& xAxis, const Vector3D& yAxis, const Vector3D& zAxis);

	Point3D		GetOrigoPrivate () const;	
	Vector3D	GetXAxisPrivate () const;
	Vector3D	GetYAxisPrivate () const;
	Vector3D	GetZAxisPrivate () const;

private:
	Point3D origo;
	Vector3D xAxis;
	Vector3D yAxis;
	Vector3D zAxis;

	Matrix34 localToGlobalTrafo;
	Matrix34 globalToLocalTrafo;
};


class GEOMETRY_DLL_EXPORT GeneralCoordinateSystem3D : public CoordinateSystem3D
{
public:
	GeneralCoordinateSystem3D (const Point3D& origo, const Vector3D& xAxis, const Vector3D& yAxis, const Vector3D& zAxis);
	virtual ~GeneralCoordinateSystem3D ();

	Point3D		GetOrigo () const;	
	Vector3D	GetXAxis () const;
	Vector3D	GetYAxis () const;
	Vector3D	GetZAxis () const;

	Transformation3D GetLocalToGlobalTrafo () const;
	Transformation3D GetGlobalToLocalTrafo () const;

	GS::Optional<GeneralCoordinateSystem3D> Transform (const Transformation3D& trafo) const;
};


class GEOMETRY_DLL_EXPORT OrthonormalizedCoordinateSystem3D : public CoordinateSystem3D
{
public:
	using CoordinateSystem3D::LocalToGlobal;
	using CoordinateSystem3D::GlobalToLocal;

	static OrthonormalizedCoordinateSystem3D CreateGlobal ();
	static OrthonormalizedCoordinateSystem3D Create (const Point3D& origo, const Vector3D& zAxisDir, const Vector3D& xAxisCandidate, bool mirrored = false);
	static OrthonormalizedCoordinateSystem3D Create (const Point3D& origo, const UnitVector_3D& xAxis, const UnitVector_3D& yAxis, const UnitVector_3D& zAxis);

	virtual ~OrthonormalizedCoordinateSystem3D ();

	Point3D			GetOrigo () const;
	UnitVector_3D	GetXAxis () const;
	UnitVector_3D	GetYAxis () const;
	UnitVector_3D	GetZAxis () const;

	UnitVector_3D	LocalToGlobal (const UnitVector_3D& localVector) const;
	UnitVector_3D	GlobalToLocal (const UnitVector_3D& globalVector) const;

	OrthogonalTransformation3D GetLocalToGlobalTrafo () const;
	OrthogonalTransformation3D GetGlobalToLocalTrafo () const;

	OrthonormalizedCoordinateSystem3D Transform (const OrthogonalTransformation3D& trafo) const;

private:
	OrthonormalizedCoordinateSystem3D (const Point3D& origo, const UnitVector_3D& xAxis, const UnitVector_3D& yAxis, const UnitVector_3D& zAxis);
};

}
#endif
