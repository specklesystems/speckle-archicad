// *****************************************************************************
//
// Deflection2D. A relative direction. It has an value and an orientation.
// Always normalized to [-2PI, 2PI].
// While Angle is normalized to [0, 2PI].
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// [SG compatible]
// *****************************************************************************

#if !defined (DEFLECTION2D_HPP)
#define DEFLECTION2D_HPP

#pragma once

#include	<math.h>

#include	"Real.hpp"
#include	"SignedAngle.hpp"
#include	"Angle.hpp"

namespace Geometry {

class Direction2D;


class Deflection2D {

private:
	SignedAngle	value;	// It is the deflection value. The sign shows the orientation. +: CW, -: CCW.
	inline	explicit Deflection2D (const SignedAngle& value);

public:

	enum Orientation {ZeroOrientation, Clockwise, CounterClockwise};

	GEOMETRY_DLL_EXPORT static const Deflection2D Zero;

	inline	Deflection2D (void);
	inline	explicit Deflection2D (double deflection, AngleUnit unit = Radian);
	inline	explicit Deflection2D (Angle value, Orientation orientation);

	inline	Deflection2D	operator-	(void) const;

	friend	Deflection2D	operator+	(const Deflection2D& d1, const Deflection2D& d2);
	friend	Deflection2D	operator-	(const Deflection2D& d1, const Deflection2D& d2);

	inline	Deflection2D	operator*	(double ratio) const;
	inline	Deflection2D	operator/	(double ratio) const;

	inline	Deflection2D& operator+=	(const Deflection2D& other);
	inline	Deflection2D& operator-=	(const Deflection2D& other);
	inline	Deflection2D& operator/=	(double ratio);

	inline	Angle		GetAngle (void) const;
	inline	SignedAngle	GetSignedAngle (void) const;
	inline	Orientation	GetOrientation (void) const;
	inline	double		GetValue (AngleUnit unit = Radian) const;


	friend	bool	IsNear <Deflection2D>			(const Deflection2D& r1, const Deflection2D& r2, double givenEps);
	friend	bool	IsNotNear <Deflection2D>		(const Deflection2D& r1, const Deflection2D& r2, double givenEps);

	friend	bool	IsNearZero <Deflection2D>		(const Deflection2D& r, double givenEps);
	friend	bool	IsNotNearZero <Deflection2D>	(const Deflection2D& r, double givenEps);
	friend	bool	IsNegative <Deflection2D>		(const Deflection2D& r, double givenEps);
	friend	bool	IsNotNegative <Deflection2D>	(const Deflection2D& r, double givenEps);
	friend	bool	IsPositive <Deflection2D>		(const Deflection2D& r, double givenEps);
	friend	bool	IsNotPositive <Deflection2D>	(const Deflection2D& r, double givenEps);

};

Deflection2D::Deflection2D (void)
	:value (0.0)
{
}

Deflection2D::Deflection2D (double deflection, AngleUnit unit)
	:value (deflection, unit)
{
}

Deflection2D::Deflection2D (Angle angle, Deflection2D::Orientation orientation)
	:value (SignedAngle (angle.GetValue ()))
{
	if (orientation == CounterClockwise) {
		value = -value;
	}
}

Deflection2D::Deflection2D (const SignedAngle& angBase)
	:value (angBase)
{
}

Deflection2D Deflection2D::operator- (void) const

{
	return Deflection2D (-value);
}

inline Deflection2D operator+ (const Deflection2D& d1, const Deflection2D& d2)
{
	return Deflection2D (d1.value + SignedAngle (d2.value));
}

inline Deflection2D operator- (const Deflection2D& d1, const Deflection2D& d2)
{
	return Deflection2D (d1.value - SignedAngle (d2.value));
}

Deflection2D Deflection2D::operator* (double ratio) const
{
	return Deflection2D (value * ratio);
}

Deflection2D Deflection2D::operator/ (double ratio) const
{
	return Deflection2D (value / ratio);
}


Deflection2D& Deflection2D::operator+= (const Deflection2D& other)
{
	value += other.value;
	return *this;
}

Deflection2D& Deflection2D::operator-= (const Deflection2D& other)
{
	value -= other.value;
	return *this;
}


Deflection2D& Deflection2D::operator/= (double ratio)
{
	value /= ratio;
	return *this;
}

Angle Deflection2D::GetAngle (void) const
{
	double val = value.GetValue ();
	if (val < 0.0) { // the comparision with 0.0 is needed here
		val += 2.0 * PI;
		//!!! ha val tobbszor korbe van csavarodva, akkor gond lesz!
	}
	return Angle (val);
}

SignedAngle Deflection2D::GetSignedAngle (void) const
{
	return value;
}

Deflection2D::Orientation Deflection2D::GetOrientation (void) const
{
	if (IsNear (value, SignedAngle (0.0))) {
		return Deflection2D::ZeroOrientation;
	} else if (IsLess (value, SignedAngle (0.0))) {
		return Deflection2D::CounterClockwise;
	} else {
		return Deflection2D::Clockwise;
	}
}

double Deflection2D::GetValue (AngleUnit unit) const
{
	return value.GetValue (unit);
}

template<>
inline bool IsNear (const Deflection2D& r1, const Deflection2D& r2, double givenEps)
{
	bool isFirstAtPI = IsNear (Abs (r1.value), SignedAngle (PI), givenEps);
	bool isSecondAtPI = IsNear (Abs (r2.value), SignedAngle (PI), givenEps);

	bool isValueNear = IsNear (r1.value, r2.value, givenEps);

	return isValueNear || (isFirstAtPI && isSecondAtPI);
}


template<>
inline bool IsNotNear (const Deflection2D& r1, const Deflection2D& r2, double givenEps)
{
	return !IsNear (r1, r2, givenEps);
}


template<>
inline bool IsNearZero (const Deflection2D& r, double givenEps)
{
	return IsNearZero (r.value.GetValue (), givenEps);
}


template<>
inline bool IsNotNearZero (const Deflection2D& r, double givenEps)
{
	return IsNotNearZero (r.value.GetValue (), givenEps);
}


template<>
inline bool IsNegative (const Deflection2D& r, double givenEps)
{
	return IsNegative (r.value.GetValue (), givenEps);
}


template<>
inline bool IsNotNegative (const Deflection2D& r, double givenEps)
{
	return IsNotNegative (r.value.GetValue (), givenEps);
}


template<>
inline bool IsPositive (const Deflection2D& r, double givenEps)
{
	return IsPositive (r.value.GetValue (), givenEps);
}


template<>
inline bool IsNotPositive (const Deflection2D& r, double givenEps)
{
	return IsNotPositive (r.value.GetValue (), givenEps);
}


} // namespace Geometry

#endif
