#ifndef ORTHOGONALTRANSFORMATION_3D_HPP
#define ORTHOGONALTRANSFORMATION_3D_HPP

#pragma once

#include "Matrix3.hpp"
#include "UnitVector3D.hpp"

namespace Geometry {

class OrthonormalizedCoordinateSystem3D;
class Line3D;
class Plane3D;

class GEOMETRY_DLL_EXPORT OrthogonalTransformation3D {

private:
	Matrix33 matrix;
	Vector3D offset;

public:

	static const OrthogonalTransformation3D Identity;
	OrthogonalTransformation3D (void);

	bool IsIdentity () const;
	bool IsTranslationOnly () const;
	bool HasMirror () const;
	bool HasTranslation ()const;

	Matrix33 GetMatrix () const;
	Vector3D GetOffset () const;
	OrthogonalTransformation3D GetInverse () const;

	void SetOffset (const Vector3D& newOffset);

	static OrthogonalTransformation3D CreateIdentity ();
	static OrthogonalTransformation3D CreateTranslation (const Vector3D& offset);
	static OrthogonalTransformation3D CreateRotationX (double angle);
	static OrthogonalTransformation3D CreateRotationY (double angle);
	static OrthogonalTransformation3D CreateRotationZ (double angle);
	static OrthogonalTransformation3D CreateRotation (const Line3D& axis, double angle);
	static OrthogonalTransformation3D CreateMirrorXY ();
	static OrthogonalTransformation3D CreateMirrorYZ ();
	static OrthogonalTransformation3D CreateMirrorZX ();
	static OrthogonalTransformation3D CreateMirror (const Plane3D& mirrorPlane);
	static OrthogonalTransformation3D CreateGlobalToLocal (const OrthonormalizedCoordinateSystem3D& cs);
	static OrthogonalTransformation3D CreateLocalToGlobal (const OrthonormalizedCoordinateSystem3D& cs);

	// other * this 
	// Example: transform.AppendTranslation().AppendRotation()
	// On Apply this will first translate the point then rotate it

	OrthogonalTransformation3D& AppendTranslation (const Vector3D& offset);
	OrthogonalTransformation3D& AppendRotationX (double angle);
	OrthogonalTransformation3D& AppendRotationY (double angle);
	OrthogonalTransformation3D& AppendRotationZ (double angle);
	OrthogonalTransformation3D& AppendRotation (const Line3D& axis, double angle);
	OrthogonalTransformation3D& AppendMirrorXY ();
	OrthogonalTransformation3D& AppendMirrorYZ ();
	OrthogonalTransformation3D& AppendMirrorZX ();
	OrthogonalTransformation3D& AppendMirror (const Plane3D& mirrorPlane);
	OrthogonalTransformation3D& Append (const OrthogonalTransformation3D& other);

	// this * other
	// Example: transform.PrependTranslation().PrependRotation()
	// On Apply this will first rotate the point then translate it

	OrthogonalTransformation3D& PrependTranslation (const Vector3D& offset);
	OrthogonalTransformation3D& PrependRotationX (double angle);
	OrthogonalTransformation3D& PrependRotationY (double angle);
	OrthogonalTransformation3D& PrependRotationZ (double angle);
	OrthogonalTransformation3D& PrependRotation (const Line3D& axis, double angle);
	OrthogonalTransformation3D& PrependMirrorXY ();
	OrthogonalTransformation3D& PrependMirrorYZ ();
	OrthogonalTransformation3D& PrependMirrorZX ();
	OrthogonalTransformation3D& PrependMirror (const Plane3D& mirrorPlane);
	OrthogonalTransformation3D& Prepend (const OrthogonalTransformation3D& other);

	OrthogonalTransformation3D operator*(const OrthogonalTransformation3D& rhs) const;

	Point3D  Apply (const Point3D& p) const;
	Vector3D Apply_V (const Vector3D& v) const;
	UnitVector_3D Apply_V (const UnitVector_3D& uv) const;
};

}

#endif