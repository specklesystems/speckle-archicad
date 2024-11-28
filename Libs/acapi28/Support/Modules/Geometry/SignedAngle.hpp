// *****************************************************************************
// SignedAngle. Always normalized to [-2PI, 2PI].
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// [SG compatible]
// *****************************************************************************

#if !defined (ANGLEBASE_HPP)
#define ANGLEBASE_HPP

#pragma once

#include <math.h>

#include "GeometricDefinitions.h"
#include "AngleData.h"
#include "RealNumber.h"
#include "Real.hpp"


namespace Geometry {


enum AngleUnit { Radian, Degree };


class GEOMETRY_DLL_EXPORT SignedAngle {
private:
	static const double	RadianToDegree;			// exchange factor between radian and degree
	static const double	DegreeToRadian;			// exchange factor between degree and radian

	static	double	eps;						// The epsilon used by angBase type
	static	void	SetEps (double eps);

	mutable	double	value = 0.0;				// The value of the angBase, the key variable
	void	Normalize (void) const;
	void	Normalize (double givenEps) const;

public:

	SignedAngle () = default;
	explicit SignedAngle (double angBase, double givenEps, AngleUnit unit = Radian);
	explicit SignedAngle (double angBase, AngleUnit unit = Radian);

	friend	bool	IsNear			(const SignedAngle& ab1, const SignedAngle& ab2);
	friend	bool	IsGreaterOrNear	(const SignedAngle& ab1, const SignedAngle& ab2);
	friend	bool	IsLessOrNear	(const SignedAngle& ab1, const SignedAngle& ab2);
	friend	bool	IsGreater		(const SignedAngle& ab1, const SignedAngle& ab2);
	friend	bool	IsLess			(const SignedAngle& ab1, const SignedAngle& ab2);

	friend	bool	IsNear			(const SignedAngle& ab1, const SignedAngle& ab2, double givenEps);
	friend	bool	IsGreaterOrNear	(const SignedAngle& ab1, const SignedAngle& ab2, double givenEps);
	friend	bool	IsLessOrNear	(const SignedAngle& ab1, const SignedAngle& ab2, double givenEps);
	friend	bool	IsGreater		(const SignedAngle& ab1, const SignedAngle& ab2, double givenEps);
	friend	bool	IsLess			(const SignedAngle& ab1, const SignedAngle& ab2, double givenEps);

			SignedAngle	operator-	(void) const;

	friend	SignedAngle	operator+	(const SignedAngle& ab1, const SignedAngle& ab2);
	friend	SignedAngle	operator-	(const SignedAngle& ab1, const SignedAngle& ab2);
	friend	double		operator/	(const SignedAngle& ab1, const SignedAngle& ab2);

			SignedAngle	operator*	(double ratio) const;
			SignedAngle	operator/	(double ratio) const;

			SignedAngle& operator+=	(const SignedAngle& other);
			SignedAngle& operator-=	(const SignedAngle& other);
			SignedAngle& operator/=	(double ratio);

	void	SnapToPiQuarters (void);
	void	SnapToPiQuarters (double givenEps);

	double			GetValue (AngleUnit unit = Radian) const;
	static double	GetEps (void);
};


inline SignedAngle::SignedAngle (double angBase, double givenEps, AngleUnit unit)
	:value (0.0)
{
	if (unit == Radian) {
		value = angBase;
	} else {
		value = angBase * DegreeToRadian;
	}
	Normalize (givenEps);
}

inline SignedAngle::SignedAngle (double angBase, AngleUnit unit)
	:value (0.0)
{
	if (unit == Radian) {
		value = angBase;
	} else {
		value = angBase * DegreeToRadian;
	}
	Normalize ();
}

inline bool IsNear (const SignedAngle& ab1, const SignedAngle& ab2)
{
	if (fabs (ab1.value - ab2.value) <= ab1.eps) {
		return true;
	} else {
		return false;
	}
}

inline bool IsGreaterOrNear (const SignedAngle& ab1, const SignedAngle& ab2)
{
	if (ab2.value - ab1.value <= ab1.eps) {
		return true;
	} else {
		return false;
	}
}

inline bool IsLessOrNear (const SignedAngle& ab1, const SignedAngle& ab2)
{
	if (ab1.value - ab2.value <= ab1.eps) {
		return true;
	} else {
		return false;
	}
}

inline bool IsGreater (const SignedAngle& ab1, const SignedAngle& ab2)
{
	if (ab1.value - ab2.value > ab1.eps) {
		return true;
	} else {
		return false;
	}
}

inline bool IsLess (const SignedAngle& ab1, const SignedAngle& ab2)
{
	if (ab2.value - ab1.value > ab1.eps) {
		return true;
	} else {
		return false;
	}
}


GEOMETRY_DLL_EXPORT bool IsBetween(const SignedAngle& begAng, const SignedAngle& endAng, const SignedAngle& toTest);



inline bool IsNear (const SignedAngle& ab1, const SignedAngle& ab2, double givenEps)
{
	if (fabs (ab1.GetValue () - ab2.GetValue ()) <= givenEps) {
		return true;
	} else {
		return false;
	}
}

inline bool IsGreaterOrNear (const SignedAngle& ab1, const SignedAngle& ab2, double givenEps)
{
	if (ab2.GetValue () - ab1.GetValue () <= givenEps) {
		return true;
	} else {
		return false;
	}
}

inline bool IsLessOrNear (const SignedAngle& ab1, const SignedAngle& ab2, double givenEps)
{
	if (ab1.GetValue () - ab2.GetValue () <= givenEps) {
		return true;
	} else {
		return false;
	}
}

inline bool IsGreater (const SignedAngle& ab1, const SignedAngle& ab2, double givenEps)
{
	if (ab1.GetValue () - ab2.GetValue () > givenEps) {
		return true;
	} else {
		return false;
	}
}

inline bool IsLess (const SignedAngle& ab1, const SignedAngle& ab2, double givenEps)
{
	if (ab2.GetValue () - ab1.GetValue () > givenEps) {
		return true;
	} else {
		return false;
	}
}

inline SignedAngle SignedAngle::operator- (void) const
{
	return SignedAngle (-value);
}

inline SignedAngle operator+ (const SignedAngle& ab1, const SignedAngle& ab2)
{
	return SignedAngle (ab1.value + ab2.value);
}

inline SignedAngle operator- (const SignedAngle& ab1, const SignedAngle& ab2)
{
	return SignedAngle (ab1.value - ab2.value);
}

inline SignedAngle SignedAngle::operator* (double ratio) const
{
	return SignedAngle (value * ratio);
}

inline double operator/ (const SignedAngle& ab1, const SignedAngle& ab2)
{
	return ab1.value / ab2.value;
}

inline SignedAngle SignedAngle::operator/ (double ratio) const
{
	return SignedAngle (value / ratio);
}

inline SignedAngle& SignedAngle::operator+= (const SignedAngle& other)
{
	value += other.value;
	Normalize ();
	return *this;
}

inline SignedAngle& SignedAngle::operator-= (const SignedAngle& other)
{
	value -= other.value;
	Normalize ();
	return *this;
}

inline SignedAngle& SignedAngle::operator/= (double ratio)
{
	value /= ratio;
	Normalize ();
	return *this;
}

inline double SignedAngle::GetValue (AngleUnit unit) const
{
	if (unit == Radian) {
		return value;
	} else {
		return value * RadianToDegree;
	}
}

inline void SignedAngle::SetEps (double newEps)
{
	eps = newEps;
}

inline double SignedAngle::GetEps (void)
{
	return eps;
}

/* normalize: -2*PI <= retval <= 2*PI */
inline void SignedAngle::Normalize (void) const
{
	/* normalize */
	if (fabs (value) > 2.0 * PI + eps) {
		value = fmod (value, 2.0 * PI);
	}
}

/* normalize: -2*PI <= retval <= 2*PI */
inline void SignedAngle::Normalize (double givenEps) const
{
	/* normalize */
	if (fabs (value) > 2.0 * PI + givenEps) {
		value = fmod (value, 2.0 * PI);
	}
}


} // namespace Geometry


#endif
