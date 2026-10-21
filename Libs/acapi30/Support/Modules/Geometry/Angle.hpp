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

#include "GSDebug.hpp"	// DBBREAK_STR

#include "Real.hpp"
#include "SignedAngle.hpp"

#include "AngleData.h"

// from Standard Library
#include <cmath>


namespace Geometry {

inline bool IsBetweenAng (const double b, const  double a1, const  double a2) { //do angles a1, b, a2 in this order give positive direction? we allow b=a1 or b=a2 (but not a1=a2)
	return (IsLess(a2, a1) && IsLessOrNear(a1, b)) || (IsLessOrNear(a1, b) && IsLessOrNear(b, a2)) || (IsLessOrNear(b, a2) && IsLess(a2, a1));
}
inline bool IsStrictlyBetweenAng (const double b, const  double a1, const double a2) { //do angles a1, b, a2 in this order give positive direction?
	return (IsLess(a2, a1) && IsLess(a1, b)) || (IsLess(a1, b) && IsLess(b, a2)) || (IsLess(b, a2) && IsLess(a2, a1));
}

class Angle {

	private:
		mutable	SignedAngle	value { 0.0 };							// The value of the angle, the key variable
		void		Normalize (void) const;
		void		Normalize (double eps) const;
		explicit	Angle (const SignedAngle& angBase);

	public:

		Angle () = default;
		explicit Angle (double angle, double givenEps, AngleUnit unit = Radian);
		explicit Angle (double angle, AngleUnit unit = Radian);

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

				Angle	operator-	(void) const;

		friend	Angle	operator+	(const Angle& a1, const Angle& a2);
		friend	Angle	operator-	(const Angle& a1, const Angle& a2);
		friend	double	operator/	(const Angle& a1, const Angle& a2);

				Angle	operator*	(double ratio) const;
				Angle	operator/	(double ratio) const;

				Angle& operator+=	(const Angle& other);
				Angle& operator-=	(const Angle& other);
				Angle& operator/=	(double ratio);

		friend	double	Sin		(const Angle& a);
		friend	double	Cos		(const Angle& a);
//		friend	Real	Tan		(const Angle& a);

		void	SnapToPiQuarters (void);
		void	SnapToPiQuarters (double givenEps);

		operator double () const;

		double	GetValue (AngleUnit unit = Radian) const;
		double	GetValue (double eps, AngleUnit unit = Radian) const;

		static double	GetEps (void);
	};


inline double	Sin (const Angle& angle)
{
	return std::sin (angle.value.GetValue ());
}


inline double	Cos (const Angle& angle)
{
	return std::cos (angle.value.GetValue ());
}


inline Angle::Angle (const SignedAngle& angBase)
	:value (angBase)
{
	// no negativity checking!!!
	Normalize ();
}

inline Angle::Angle (double angle, double givenEps, AngleUnit unit)
	:value (angle, givenEps, unit)
{
//	DBERROR_STR (value.IsLess (SignedAngle (0.0)), "Angle is negative!");
}

inline Angle::Angle (double angle, AngleUnit unit)
	:value (angle, unit)
{
//	DBERROR_STR (value.IsLess (SignedAngle (0.0)), "Angle is negative!");
}

inline bool IsNear (const Angle& a1, const Angle& a2)
{
	return IsNear (a1.value, a2.value);
}

inline bool IsGreaterOrNear (const Angle& a1, const Angle& a2)
{
	return IsGreaterOrNear (a1.value, a2.value);
}

inline bool IsLessOrNear (const Angle& a1, const Angle& a2)
{
	return IsLessOrNear (a1.value, a2.value);
}

inline bool IsGreater (const Angle& a1, const Angle& a2)
{
	return IsGreater (a1.value, a2.value);
}

inline bool IsLess (const Angle& a1, const Angle& a2)
{
	return IsLess (a1.value, a2.value);
}


inline bool IsNear (const Angle& a1, const Angle& a2, double eps)
{
	return IsNear (a1.value, a2.value, eps);
}

inline bool IsGreaterOrNear (const Angle& a1, const Angle& a2, double eps)
{
	return IsGreaterOrNear (a1.value, a2.value, eps);
}

inline bool IsLessOrNear (const Angle& a1, const Angle& a2, double eps)
{
	return IsLessOrNear (a1.value, a2.value, eps);
}

inline bool IsGreater (const Angle& a1, const Angle& a2, double eps)
{
	return IsGreater (a1.value, a2.value, eps);
}

inline bool IsLess (const Angle& a1, const Angle& a2, double eps)
{
	return IsLess (a1.value, a2.value, eps);
}

inline Angle Angle::operator- (void) const

{
	return Angle (-value);
}

inline Angle operator+ (const Angle& a1, const Angle& a2)
{
	return Angle (a1.value + a2.value);
}

inline Angle operator- (const Angle& a1, const Angle& a2)
{
	return Angle (a1.value - a2.value);
}

inline Angle Angle::operator* (double ratio) const
{
	return Angle (value * ratio);
}

inline double operator/ (const Angle& a1, const Angle& a2)
{
	return a1.value / a2.value;
}

inline Angle Angle::operator/ (double ratio) const
{
	return Angle (value / ratio);
}

inline Angle& Angle::operator+= (const Angle& other)
{
	value += other.value;
	Normalize ();
	return *this;
}

inline Angle& Angle::operator-= (const Angle& other)
{
	value -= other.value;
	Normalize ();
	return *this;
}


inline Angle& Angle::operator/= (double ratio)
{
	value /= ratio;
	Normalize ();
	return *this;
}

/* normalize: 0 <= retval <= 2*PI; snap to k*PI/2 (k=0,1,2,3,4) with eps) */

inline void Angle::Normalize (void) const
{
	/* normalize */
	if (IsLess (value, SignedAngle (0.0))) {
		value += SignedAngle (2.0 * PI);
	}
}


inline void Angle::Normalize (double eps) const
{
	if (IsLess (value, SignedAngle (0.0), eps)) {
		value += SignedAngle (2.0 * PI);
	}
}

inline void Angle::SnapToPiQuarters (void)
{
	value.SnapToPiQuarters ();
}

inline void Angle::SnapToPiQuarters (double givenEps)
{
	value.SnapToPiQuarters (givenEps);
}

inline	Angle::operator double () const
{
	Normalize ();
	return value.GetValue (Radian);
}

inline double Angle::GetValue (AngleUnit unit) const
{
	Normalize ();
	return value.GetValue (unit);
}

inline double Angle::GetValue (double eps, AngleUnit unit) const
{
	Normalize (eps);
	return value.GetValue (unit);
}

inline double Angle::GetEps (void)
{
	return SignedAngle::GetEps ();
}


} // namespace Geometry

#endif
