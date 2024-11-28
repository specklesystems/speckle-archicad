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
	Real	x;
	Real	y;

public:
	GEOMETRY_DLL_EXPORT static const Direction2D Undefined;

	inline	Direction2D (void);
	inline	Direction2D (const Direction2D& source);
	inline	explicit Direction2D (double angle, AngleUnit unit = Radian);
	inline	explicit Direction2D (const Real& angle, AngleUnit unit = Radian);
	inline	explicit Direction2D (const Angle& angle);
	inline	explicit Direction2D (const Vector2D& vector);
	inline	explicit Direction2D (const Point2D& fromPt, const Point2D& toPt);
	inline	Direction2D (const Real& x, const Real& y);
	inline	~Direction2D ();

	friend	bool	IsNear	(const Direction2D& d1, const Direction2D& d2);
	friend	bool	IsNear	(const Direction2D& d1, const Direction2D& d2, double eps);

	inline	bool			IsUndefined (void) const;
	inline	void			Invert (void);

	inline	Direction2D	operator+	(const Deflection2D& other) const;
	inline	Direction2D	operator-	(const Deflection2D& other) const;
	inline	Direction2D	operator*	(const Real& ratio) const;
	inline	Direction2D	operator/	(const Real& ratio) const;

	friend  inline	Deflection2D	GetDeflectionFromTo	(const UnitVector_2D& d1, const UnitVector_2D& d2);
	inline	bool	PointsToSimilarDirection (const Direction2D& other) const;

	inline	Direction2D& operator=	(const Direction2D& source);
	inline	Direction2D& operator+=	(const Deflection2D& other);
	inline	Direction2D& operator-=	(const Deflection2D& other);
	inline	Direction2D& operator/=	(const Real& ratio);

	friend	Real	Sin		(const Direction2D& a);
	friend	Real	Cos		(const Direction2D& a);
	friend	Real	Tan		(const Direction2D& a);

	inline	double	GetX (void) const;
	inline	double	GetY (void) const;
	inline	Vector2D	GetVector (void) const;

	inline	void	Set (const Vector2D& vector);
	inline	void	Set (const Real& x, const Real& y);

	inline	void	SnapToPiQuarters (void);
	inline	Angle	GetPositionAngle (void) const;
	inline	double	GetValue (AngleUnit unit = Radian) const;
	inline	double	GetValue (double eps, AngleUnit unit = Radian) const;
};


// inline  bool operator== (const Direction2D& dir1, const Direction2D& dir2); -- forbidden


Direction2D::Direction2D (void)
	:x (), y ()
{
}

Direction2D::Direction2D (const Direction2D& source)
	:x (source.x), y (source.y)
{
}

Direction2D::Direction2D (double angle, AngleUnit unit)
	:x (), y ()
{
	Angle a = Angle (Real (angle), unit);
	x = Cos (a);
	y = Sin (a);
}

Direction2D::Direction2D (const Real& angle, AngleUnit unit)
	:x (), y ()
{
	Angle a = Angle (angle, unit);
	x = Cos (a);
	y = Sin (a);
}

Direction2D::Direction2D (const Angle& angle)
	:x (), y ()
{
	x = Cos (angle);
	y = Sin (angle);
}

Direction2D::Direction2D (const Real& xInitial, const Real& yInitial)
	:x (), y ()
{
	Set (xInitial, yInitial);
}

Direction2D::Direction2D (const Vector2D& vector)
	:x (), y ()
{
	Set (vector);
}

Direction2D::Direction2D (const Point2D& fromPt, const Point2D& toPt)
	:x (), y ()
{
	Set (Real (toPt.x - fromPt.x), Real (toPt.y - fromPt.y));
}

Direction2D::~Direction2D ()
{
	// empty
}

inline bool IsNear (const Direction2D& d1, const Direction2D& d2)
{
	return IsNearZero (Sqrt ((d1.x - d2.x) * (d1.x - d2.x) + (d1.y - d2.y) * (d1.y - d2.y)));
}

inline bool IsNear (const Direction2D& d1, const Direction2D& d2, double eps)
{
	return IsNearZero (Sqrt ((d1.x - d2.x) * (d1.x - d2.x) + (d1.y - d2.y) * (d1.y - d2.y)), eps);
}

bool Direction2D::IsUndefined (void) const
{
	return IsNearZero (x) && IsNearZero (y);
}

void Direction2D::Invert (void)
{
	x = -x;
	y = -y;
}

Direction2D Direction2D::operator+ (const Deflection2D& other) const
{
	return Direction2D (ArcTan (y, x).GetValue () + other.GetValue ());
}

Direction2D Direction2D::operator- (const Deflection2D& other) const
{
	return Direction2D (ArcTan (y, x).GetValue () - other.GetValue ());
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
	asinx = ArcSin (Real (x)).GetValue ();
	acosy = ArcCos (Real (y)).GetValue ();
	if (asinx < 0.0 || asinx > PI)
		acosy = -acosy;

	return Deflection2D (acosy);
}


inline bool Direction2D::PointsToSimilarDirection (const Direction2D& other) const
{
	Real scalar = x * other.x + y * other.y;	// MulsVectors
	return IsPositive (scalar);
}


Direction2D Direction2D::operator* (const Real& ratio) const
{
	return Direction2D (ArcTan (y, x) * ratio);
}

Direction2D Direction2D::operator/ (const Real& ratio) const
{
	return Direction2D (ArcTan (y, x) / ratio);
}


Direction2D& Direction2D::operator= (const Direction2D& source)
{
	if (this != &source) {
		this->x = source.x;
		this->y = source.y;
	}
	return *this;
}

Direction2D& Direction2D::operator+= (const Deflection2D& other)
{
	Angle angle (ArcTan (y, x));
	angle += Angle (other.GetValue ());
	x = Cos (angle);
	y = Sin (angle);
	return *this;
}

Direction2D& Direction2D::operator-= (const Deflection2D& other)
{
	Angle angle (ArcTan (y, x));
	angle -= Angle (other.GetValue ());
	x = Cos (angle);
	y = Sin (angle);
	return *this;
}


Direction2D& Direction2D::operator/= (const Real& ratio)
{
	Angle angle (ArcTan (y, x));
	angle /= ratio;
	x = Cos (angle);
	y = Sin (angle);
	return *this;
}


void Direction2D::Set (const Real& xInitial, const Real& yInitial)
{
	Real len = Sqrt (xInitial * xInitial + yInitial * yInitial);
	if (IsNear (len, Real::Zero)) {
		x = Real::Zero;
		y = Real::Zero;
	} else {
		x = xInitial / len;
		y = yInitial / len;
	}
}

void Direction2D::Set (const Vector2D& vector)
{
	Set (Real (vector.x), Real (vector.y));
}


double Direction2D::GetX (void) const
{
	return x.GetValue ();
}

double Direction2D::GetY (void) const
{
	return y.GetValue ();
}

Vector2D Direction2D::GetVector (void) const
{
	Vector2D vector;
	vector.x = x.GetValue ();
	vector.y = y.GetValue ();

	return vector;
}

void Direction2D::SnapToPiQuarters (void)
{
	// If they are zero then swap to zero
	if (IsNearZero (x) && IsNearZero (y)) {
		x = Real (0.0);
		y = Real (0.0);
	} else {
		Angle angle (ArcTan (y, x));
		angle.SnapToPiQuarters ();
		x = Cos (angle);
		y = Sin (angle);
	}
	return;
}

Angle Direction2D::GetPositionAngle (void) const
{
	return ArcTan (y, x);
}

double Direction2D::GetValue (AngleUnit unit) const
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

double Direction2D::GetValue (double eps, AngleUnit unit) const
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
