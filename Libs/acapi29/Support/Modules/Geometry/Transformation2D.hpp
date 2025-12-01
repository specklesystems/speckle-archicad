#ifndef TRANSFORMATION_2D_HPP
#define TRANSFORMATION_2D_HPP

#pragma once 

#include "Matrix2.hpp"
#include "CoordTypedef.hpp"
#include "UnitVector2DClassDeclaration.hpp"

namespace Geometry {

class OrthogonalTransformation2D;
class GeneralCoordinateSystem2D;
class Line2D;

class GEOMETRY_DLL_EXPORT Transformation2D {
private:
	Matrix22 matrix;
	Vector2D offset;

public:
	static const Transformation2D Identity;

	Transformation2D (void);
	Transformation2D (const OrthogonalTransformation2D& other);

	bool IsSingular () const;
	bool IsIdentity () const;
	bool IsTranslationOnly () const;
	bool HasMirror () const;
	bool HasScaling () const;
	bool HasTranslation () const;

	Matrix22 GetMatrix () const;
	Vector2D GetOffset () const;
	GS::Optional<Transformation2D> GetInverse () const;

	void SetMatrix (const Matrix22& newMatrix);
	void SetOffset (const Vector2D& newOffset);

	static Transformation2D CreateIdentity ();
	static Transformation2D CreateTranslation (const Vector2D& offset);
	static Transformation2D CreateOrigoRotation (double angle);
	static Transformation2D CreateRotation (const Point2D& origo, double angle);
	static Transformation2D CreateMirrorX ();
	static Transformation2D CreateMirrorY ();
	static Transformation2D CreateMirror (const Line2D& mirrorAxis);
	static Transformation2D CreateScaling (double xScale, double yScale);
	static Transformation2D CreateGlobalToLocal (const GeneralCoordinateSystem2D& cs);
	static Transformation2D CreateLocalToGlobal (const GeneralCoordinateSystem2D& cs);

	// other * this 
	// Example: transform.AppendTranslation().AppendRotation()
	// On Apply this will first translate the point then rotate it

	Transformation2D& AppendTranslation (const Vector2D& offset);
	Transformation2D& AppendOrigoRotation (double angle);
	Transformation2D& AppendRotation (const Point2D& origo, double angle);
	Transformation2D& AppendScaling (double xScale, double yScale);
	Transformation2D& AppendMirrorX ();
	Transformation2D& AppendMirrorY ();
	Transformation2D& AppendMirror (const Line2D & mirrorAxis);
	Transformation2D& Append (const Transformation2D& other);

	// this * other
	// Example: transform.PrependTranslation().PrependRotation()
	// On Apply this will first rotate the point then translate it

	Transformation2D& PrependTranslation (const Vector2D& offset);
	Transformation2D& PrependOrigoRotation (double angle);
	Transformation2D& PrependRotation (const Point2D& origo, double angle);
	Transformation2D& PrependScaling (double xScale, double yScale);
	Transformation2D& PrependMirrorX ();
	Transformation2D& PrependMirrorY ();
	Transformation2D& PrependMirror (const Line2D & mirrorAxis);
	Transformation2D& Prepend (const Transformation2D& other);

	Transformation2D operator* (const Transformation2D& rhs) const;

	Point2D			Apply (const Point2D& p) const;
	Vector2D		Apply (const Vector2D& p) const;
};

}

#endif