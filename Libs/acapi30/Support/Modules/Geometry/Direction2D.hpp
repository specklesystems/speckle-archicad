// *****************************************************************************
//
// Direction2D. An absolute direction. Always normalized to [0, 2PI).
// While Angle is normalized to [0, 2PI].
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// [SG compatible]
// *****************************************************************************

#if !defined (DIRECTION2D_HPP)
#define DIRECTION2D_HPP

#pragma once

#include	<math.h>

#include	"Real.hpp"
#include	"Deflection2D.hpp"
#include	"SignedAngle.hpp"
#include	"Vector2D.hpp"
#include	"Point2D.hpp"
#include	"UnitVector2D.hpp"

namespace Geometry {
class Direction2D {
private:
	double x = 0.0;
	double y = 0.0;

public:
	GEOMETRY_DLL_EXPORT static const Direction2D Undefined;

	Direction2D () = default;
	explicit Direction2D (double angle, AngleUnit unit = Radian);
	explicit Direction2D (const Angle& angle);
	explicit Direction2D (const Vector2D& vector);
	explicit Direction2D (const Point2D& fromPt, const Point2D& toPt);
	Direction2D (double x, double y);

	friend	bool	IsNear	(const Direction2D& d1, const Direction2D& d2);
	friend	bool	IsNear	(const Direction2D& d1, const Direction2D& d2, double eps);

	bool			IsUndefined (void) const;
	void			Invert (void);

	Direction2D	operator+	(const Deflection2D& other) const;
	Direction2D	operator-	(const Deflection2D& other) const;
	Direction2D	operator*	(double ratio) const;
	Direction2D	operator/	(double ratio) const;

	friend	Deflection2D	GetDeflectionFromTo	(const UnitVector_2D& d1, const UnitVector_2D& d2);
	bool					PointsToSimilarDirection (const Direction2D& other) const;

	Direction2D& operator+=	(const Deflection2D& other);
	Direction2D& operator-=	(const Deflection2D& other);
	Direction2D& operator/=	(double ratio);

	double		GetX (void) const;
	double		GetY (void) const;
	Vector2D	GetVector (void) const;

	void	Set (const Vector2D& vector);
	void	Set (double x, double y);

	void	SnapToPiQuarters (void);
	Angle	GetPositionAngle (void) const;
	double	GetValue (AngleUnit unit = Radian) const;
	double	GetValue (double eps, AngleUnit unit = Radian) const;
};


// inline  bool operator== (const Direction2D& dir1, const Direction2D& dir2); -- forbidden


inline Direction2D::Direction2D (double angle, AngleUnit unit)
	:x (), y ()
{
	Angle a = Angle (angle, unit);
	x = Cos (a);
	y = Sin (a);
}

inline Direction2D::Direction2D (const Angle& angle)
	:x (), y ()
{
	x = Cos (angle);
	y = Sin (angle);
}

inline Direction2D::Direction2D (double xInitial, double yInitial)
	:x (), y ()
{
	Set (xInitial, yInitial);
}

inline Direction2D::Direction2D (const Vector2D& vector)
	:x (), y ()
{
	Set (vector);
}

inline Direction2D::Direction2D (const Point2D& fromPt, const Point2D& toPt)
	:x (), y ()
{
	Set (toPt.x - fromPt.x, toPt.y - fromPt.y);
}

inline bool IsNear (const Direction2D& d1, const Direction2D& d2)
{
	return IsNearZero (Sqrt ((d1.x - d2.x) * (d1.x - d2.x) + (d1.y - d2.y) * (d1.y - d2.y)));
}

inline bool IsNear (const Direction2D& d1, const Direction2D& d2, double eps)
{
	return IsNearZero (Sqrt ((d1.x - d2.x) * (d1.x - d2.x) + (d1.y - d2.y) * (d1.y - d2.y)), eps);
}

inline bool Direction2D::IsUndefined (void) const
{
	return IsNearZero (x) && IsNearZero (y);
}

inline void Direction2D::Invert (void)
{
	x = -x;
	y = -y;
}

inline Direction2D Direction2D::operator+ (const Deflection2D& other) const
{
	return Direction2D (ArcTan (y, x) + other.GetValue ());
}

inline Direction2D Direction2D::operator- (const Deflection2D& other) const
{
	return Direction2D (ArcTan (y, x) - other.GetValue ());
}

//inline Angle operator- (const Direction2D& d1, const Direction2D& d2)
//{
//	return ArcTan (d1.y, d1.x) - ArcTan (d2.y, d2.x);
//}

inline Deflection2D GetDeflectionFromTo (const UnitVector_2D& dirFromUV, const UnitVector_2D& dirToUV)
{
	double	asinx, acosy;
	Vector2D dirFrom = dirFromUV;
	Vector2D dirTo = dirToUV;

	double y = dirFrom.x * dirTo.x + dirFrom.y * dirTo.y;	// MulsVectors
	double x = dirFrom.x * dirTo.y - dirFrom.y * dirTo.x;	// MulvVectors
	asinx = ArcSin (x);
	acosy = ArcCos (y);
	if (asinx < 0.0 || asinx > PI)
		acosy = -acosy;

	return Deflection2D (acosy);
}


inline bool Direction2D::PointsToSimilarDirection (const Direction2D& other) const
{
	double scalar = x * other.x + y * other.y;	// MulsVectors
	return IsPositive (scalar);
}


inline Direction2D Direction2D::operator* (double ratio) const
{
	return Direction2D (ArcTan (y, x) * ratio);
}

inline Direction2D Direction2D::operator/ (double ratio) const
{
	return Direction2D (ArcTan (y, x) / ratio);
}


inline Direction2D& Direction2D::operator+= (const Deflection2D& other)
{
	Angle angle (ArcTan (y, x));
	angle += Angle (other.GetValue ());
	x = Cos (angle);
	y = Sin (angle);
	return *this;
}

inline Direction2D& Direction2D::operator-= (const Deflection2D& other)
{
	Angle angle (ArcTan (y, x));
	angle -= Angle (other.GetValue ());
	x = Cos (angle);
	y = Sin (angle);
	return *this;
}


inline Direction2D& Direction2D::operator/= (double ratio)
{
	Angle angle (ArcTan (y, x));
	angle /= ratio;
	x = Cos (angle);
	y = Sin (angle);
	return *this;
}


inline void Direction2D::Set (double xInitial, double yInitial)
{
	double len = Sqrt (xInitial * xInitial + yInitial * yInitial);
	if (IsNear (len, 0.0)) {
		x = 0.0;
		y = 0.0;
	} else {
		x = xInitial / len;
		y = yInitial / len;
	}
}

inline void Direction2D::Set (const Vector2D& vector)
{
	Set (vector.x, vector.y);
}


inline double Direction2D::GetX (void) const
{
	return x;
}

inline double Direction2D::GetY (void) const
{
	return y;
}

inline Vector2D Direction2D::GetVector (void) const
{
	return { x, y };
}

inline void Direction2D::SnapToPiQuarters (void)
{
	// If they are zero then swap to zero
	if (IsNearZero (x) && IsNearZero (y)) {
		x = 0.0;
		y = 0.0;
	} else {
		Angle angle (ArcTan (y, x));
		angle.SnapToPiQuarters ();
		x = Cos (angle);
		y = Sin (angle);
	}
	return;
}

inline Angle Direction2D::GetPositionAngle (void) const
{
	return Angle { ArcTan (y, x) };
}

inline double Direction2D::GetValue (AngleUnit unit) const
{
	// if x, y is zero, any direction is applicable. We choose the 0.0.
	if (IsNearZero (x) && IsNearZero (y)) {
		return 0.0;
	}
	Angle angle (ArcTan (y, x));
	if (IsNear (angle, Angle (2.0 * PI))) {
		return 0.0;
	}
	return angle.GetValue (unit);
}

inline double Direction2D::GetValue (double eps, AngleUnit unit) const
{
	// if x, y is zero, any direction is applicable. We choose the 0.0.
	if (IsNearZero (x, eps) && IsNearZero (y, eps)) {
		return 0.0;
	}
	Angle angle (ArcTan (y, x));
	if (IsNear (angle, Angle (2.0 * PI), eps)) {
		return 0.0;
	}
	return angle.GetValue (unit);
}

}
#endif
