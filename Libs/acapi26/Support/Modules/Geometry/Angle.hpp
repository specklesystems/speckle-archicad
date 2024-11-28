// *****************************************************************************
// Angle. Always normalized to [0, 2PI].
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// [SG compatible]
// *****************************************************************************

#if !defined (ANGLE_HPP)
#define ANGLE_HPP

#pragma once

#include	"GSDebug.hpp"	// DBBREAK_STR

#include	"Real.hpp"
#include	"SignedAngle.hpp"

#include	"AngleData.h"


namespace Geometry {

inline bool IsBetweenAng (const double b, const  double a1, const  double a2) { //do angles a1, b, a2 in this order give positive direction? we allow b=a1 or b=a2 (but not a1=a2)
	return (IsLess(a2, a1) && IsLessOrNear(a1, b)) || (IsLessOrNear(a1, b) && IsLessOrNear(b, a2)) || (IsLessOrNear(b, a2) && IsLess(a2, a1));
}
inline bool IsStrictlyBetweenAng (const double b, const  double a1, const double a2) { //do angles a1, b, a2 in this order give positive direction?
	return (IsLess(a2, a1) && IsLess(a1, b)) || (IsLess(a1, b) && IsLess(b, a2)) || (IsLess(b, a2) && IsLess(a2, a1));
}

class Angle {

	private:
		mutable	SignedAngle	value;						// The value of the angle, the key variable
		inline void	Normalize (void) const;
		inline void	Normalize (double eps) const;
		inline	explicit Angle (const SignedAngle& angBase);
		inline	explicit Angle (double angle, AngleUnit unit);		// disabled, calls unexpected ctor without warning

	public:

		inline	Angle (void);
		inline	Angle (const Angle& source);
		inline	explicit Angle (double angle, double givenEps = SignedAngle::GetEps (), AngleUnit unit = Radian);
		inline	explicit Angle (const Real& angle, AngleUnit unit = Radian);
		inline	~Angle ();

		friend	bool	IsNear			(const Angle& a1, const Angle& a2);
		friend	bool	IsGreaterOrNear	(const Angle& a1, const Angle& a2);
		friend	bool	IsLessOrNear	(const Angle& a1, const Angle& a2);
		friend	bool	IsGreater		(const Angle& a1, const Angle& a2);
		friend	bool	IsLess			(const Angle& a1, const Angle& a2);

		friend	bool	IsNear			(const Angle& a1, const Angle& a2, double eps);
		friend	bool	IsGreaterOrNear	(const Angle& a1, const Angle& a2, double eps);
		friend	bool	IsLessOrNear	(const Angle& a1, const Angle& a2, double eps);
		friend	bool	IsGreater		(const Angle& a1, const Angle& a2, double eps);
		friend	bool	IsLess			(const Angle& a1, const Angle& a2, double eps);

		inline	Angle	operator-	(void) const;

		friend	inline Angle	operator+	(const Angle& a1, const Angle& a2);
		friend	inline Angle	operator-	(const Angle& a1, const Angle& a2);
		friend	inline Real		operator/	(const Angle& a1, const Angle& a2);

		inline	Angle	operator*	(const Real& ratio) const;
		inline	Angle	operator/	(const Real& ratio) const;

		inline	Angle& operator=	(const Angle& source);
		inline	Angle& operator+=	(const Angle& other);
		inline	Angle& operator-=	(const Angle& other);
		inline	Angle& operator/=	(const Real& ratio);

		friend	inline Real	Sin		(const Angle& a);
		friend	inline Real	Cos		(const Angle& a);
//		friend	inline Real	Tan		(const Angle& a);

		friend	inline Angle	ArcSin	(const Real& x);
		friend	inline Angle	ArcCos	(const Real& x);
		friend	inline Angle	ArcTan	(const Real& y, const Real& x);

		inline	void	SnapToPiQuarters (void);
		inline	void	SnapToPiQuarters (double givenEps);
		inline	operator double () const;
		inline	double	GetValue (AngleUnit unit = Radian) const;
		inline	double	GetValue (double eps, AngleUnit unit = Radian) const;
		inline	static double	GetEps (void);
	};

	inline Real Sin (const Angle& angle)
	{
		return Real (sin (angle.value.GetValue ()));
	}

	inline Real Cos (const Angle& angle)
	{
		return Real (cos (angle.value.GetValue ()));
	}

	inline Angle	ArcSin (const Real& x)
	{
		if (x.GetValue () > 1.0)		/* It could be sligly greater due to rounding error. */
			return Angle (PI / 2.0);
		if (x.GetValue () < -1.0)
			return Angle (-PI / 2.0);
		return Angle (asin (x.GetValue ()));
	}


	inline Angle	ArcCos (const Real& x)
	{
		if (x.GetValue () > 1.0)		/* It could be sligly greater due to rounding error. */
			return Angle (0.0);
		if (x.GetValue () < -1.0)
			return Angle (PI);
		return Angle (acos (x.GetValue ()));
	}


	inline Angle ArcTan	(const Real& y, const Real& x)
	{
		if (IsNearZero (x) && IsNearZero (y)) {
			DBBREAK_STR ("x and y is zero in the ArcTan function!!!");
		}
		Angle angle;
		angle.value = SignedAngle (atan2 (y.GetValue (), x.GetValue ()));
		return Angle (angle);
	}
}


inline Geometry::Angle::Angle (void)
	:value (0.0)
{
}

inline Geometry::Angle::Angle (const Angle& source)
	:value (source.value)
{
	// no negativity checking!!!
	Normalize ();
}

inline Geometry::Angle::Angle (const SignedAngle& angBase)
	:value (angBase)
{
	// no negativity checking!!!
	Normalize ();
}

inline Geometry::Angle::Angle (double angle, double givenEps, AngleUnit unit)
	:value (angle, givenEps, unit)
{
//	DBERROR_STR (value.IsLess (SignedAngle (0.0)), "Angle is negative!");
}

inline Geometry::Angle::Angle (const Real& angle, AngleUnit unit)
	:value (angle, unit)
{
//	DBERROR_STR (value.IsLess (SignedAngle (0.0)), "Angle is negative!");
}

inline Geometry::Angle::~Angle ()
{
	// empty
}

inline bool Geometry::IsNear (const Geometry::Angle& a1, const Angle& a2)
{
	return IsNear (a1.value, a2.value);
}

inline bool Geometry::IsGreaterOrNear (const Geometry::Angle& a1, const Geometry::Angle& a2)
{
	return IsGreaterOrNear (a1.value, a2.value);
}

inline bool Geometry::IsLessOrNear (const Geometry::Angle& a1, const Angle& a2)
{
	return IsLessOrNear (a1.value, a2.value);
}

inline bool Geometry::IsGreater (const Geometry::Angle& a1, const Angle& a2)
{
	return IsGreater (a1.value, a2.value);
}

inline bool Geometry::IsLess (const Geometry::Angle& a1, const Angle& a2)
{
	return IsLess (a1.value, a2.value);
}



inline bool Geometry::IsNear (const Geometry::Angle& a1, const Angle& a2, double eps)
{
	return IsNear (a1.value, a2.value, eps);
}

inline bool Geometry::IsGreaterOrNear (const Geometry::Angle& a1, const Angle& a2, double eps)
{
	return IsGreaterOrNear (a1.value, a2.value, eps);
}

inline bool Geometry::IsLessOrNear (const Geometry::Angle& a1, const Angle& a2, double eps)
{
	return IsLessOrNear (a1.value, a2.value, eps);
}

inline bool Geometry::IsGreater (const Geometry::Angle& a1, const Angle& a2, double eps)
{
	return IsGreater (a1.value, a2.value, eps);
}

inline bool Geometry::IsLess (const Geometry::Angle& a1, const Angle& a2, double eps)
{
	return IsLess (a1.value, a2.value, eps);
}

inline Geometry::Angle Geometry::Angle::operator- (void) const

{
	return Angle (-value);
}

inline Geometry::Angle Geometry::operator+ (const Geometry::Angle& a1, const Geometry::Angle& a2)
{
	return Angle (a1.value + a2.value);
}

inline Geometry::Angle Geometry::operator- (const Geometry::Angle& a1, const Geometry::Angle& a2)
{
	return Angle (a1.value - a2.value);
}

inline Geometry::Angle Geometry::Angle::operator* (const Geometry::Real& ratio) const
{
	return Angle (value * ratio);
}

inline Geometry::Real Geometry::operator/ (const Geometry::Angle& a1, const Geometry::Angle& a2)
{
	return Real (a1.value / a2.value);
}

inline Geometry::Angle Geometry::Angle::operator/ (const Geometry::Real& ratio) const
{
	return Angle (value / ratio);
}


inline Geometry::Angle& Geometry::Angle::operator= (const Geometry::Angle& source)
{
	if (this != &source) {
		this->value = source.value;
	}
	return *this;
}

inline Geometry::Angle& Geometry::Angle::operator+= (const Geometry::Angle& other)
{
	value += other.value;
	Normalize ();
	return *this;
}

inline Geometry::Angle& Geometry::Angle::operator-= (const Geometry::Angle& other)
{
	value -= other.value;
	Normalize ();
	return *this;
}


inline Geometry::Angle& Geometry::Angle::operator/= (const Geometry::Real& ratio)
{
	value /= ratio;
	Normalize ();
	return *this;
}

/* normalize: 0 <= retval <= 2*PI; snap to k*PI/2 (k=0,1,2,3,4) with eps) */

inline void Geometry::Angle::Normalize (void) const
{
	/* normalize */
	if (IsLess (value, SignedAngle (0.0))) {
		value += SignedAngle (2.0 * PI);
	}
}


inline void Geometry::Angle::Normalize (double eps) const
{
	if (IsLess (value, SignedAngle (0.0), eps)) {
		value += SignedAngle (2.0 * PI);
	}
}

inline void Geometry::Angle::SnapToPiQuarters (void)
{
	value.SnapToPiQuarters ();
}

inline void Geometry::Angle::SnapToPiQuarters (double givenEps)
{
	value.SnapToPiQuarters (givenEps);
}

inline	Geometry::Angle::operator double () const
{
	Normalize ();
	return value.GetValue (Radian);
}

inline double Geometry::Angle::GetValue (Geometry::AngleUnit unit) const
{
	Normalize ();
	return value.GetValue (unit);
}

inline double Geometry::Angle::GetValue (double eps, Geometry::AngleUnit unit) const
{
	Normalize (eps);
	return value.GetValue (unit);
}

inline double Geometry::Angle::GetEps (void)
{
	return SignedAngle::GetEps ();
}

#endif
