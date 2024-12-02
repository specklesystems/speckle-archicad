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

#include	<math.h>

#include	"GeometricDefinitions.h"
#include	"AngleData.h"
#include	"RealNumber.h"
#include	"Real.hpp"


namespace Geometry {
	enum AngleUnit {Radian, Degree};

	class GEOMETRY_DLL_EXPORT SignedAngle {

	private:
		static const double	RadianToDegree;			// exchange factor between radian and degree
		static const double	DegreeToRadian;			// exchange factor between degree and radian

		static	double	eps;						// The epsilon used by angBase type
		inline	static void		SetEps (double eps);

		mutable	double	value;						// The value of the angBase, the key variable
		inline	void	Normalize (void) const;
		inline	void	Normalize (double givenEps) const;

	public:

		inline	SignedAngle (void);
		inline	SignedAngle (const SignedAngle& source);
		inline	explicit SignedAngle (double angBase, double givenEps = SignedAngle::eps, AngleUnit unit = Radian);
		inline	explicit SignedAngle (const Real& angBase, AngleUnit unit = Radian);
		inline	~SignedAngle ();

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

		inline	SignedAngle	operator-	(void) const;

		friend	SignedAngle	operator+	(const SignedAngle& ab1, const SignedAngle& ab2);
		friend	SignedAngle	operator-	(const SignedAngle& ab1, const SignedAngle& ab2);
		friend	Real		operator/	(const SignedAngle& ab1, const SignedAngle& ab2);

		inline	SignedAngle	operator*	(const Real& ratio) const;
		inline	SignedAngle	operator/	(const Real& ratio) const;

		inline	SignedAngle& operator=	(const SignedAngle& source);
		inline	SignedAngle& operator+=	(const SignedAngle& other);
		inline	SignedAngle& operator-=	(const SignedAngle& other);
		inline	SignedAngle& operator/=	(const Real& ratio);

		void	SnapToPiQuarters (void);
		void	SnapToPiQuarters (double givenEps);

		inline	double	GetValue (AngleUnit unit = Radian) const;
		inline	static double	GetEps (void);
	};
}


inline Geometry::SignedAngle::SignedAngle (void)
	:value (0.0)
{
}

inline Geometry::SignedAngle::SignedAngle (const SignedAngle& source)
	:value (source.value)
{
	Normalize ();
}

inline Geometry::SignedAngle::SignedAngle (double angBase, double givenEps, AngleUnit unit)
	:value (0.0)
{
	if (unit == Radian) {
		value = angBase;
	} else {
		value = angBase * DegreeToRadian;
	}
	Normalize (givenEps);
}

inline Geometry::SignedAngle::SignedAngle (const Real& angBase, AngleUnit unit)
	:value (0.0)
{
	if (unit == Radian) {
		value = angBase.GetValue ();
	} else {
		value = angBase.GetValue () * DegreeToRadian;
	}
	Normalize ();
}

inline Geometry::SignedAngle::~SignedAngle ()
{
	// empty
}

inline bool Geometry::IsNear (const SignedAngle& ab1, const SignedAngle& ab2)
{
	if (fabs (ab1.value - ab2.value) <= ab1.eps) {
		return true;
	} else {
		return false;
	}
}

inline bool Geometry::IsGreaterOrNear (const SignedAngle& ab1, const SignedAngle& ab2)
{
	if (ab2.value - ab1.value <= ab1.eps) {
		return true;
	} else {
		return false;
	}
}

inline bool Geometry::IsLessOrNear (const SignedAngle& ab1, const SignedAngle& ab2)
{
	if (ab1.value - ab2.value <= ab1.eps) {
		return true;
	} else {
		return false;
	}
}

inline bool Geometry::IsGreater (const SignedAngle& ab1, const SignedAngle& ab2)
{
	if (ab1.value - ab2.value > ab1.eps) {
		return true;
	} else {
		return false;
	}
}

inline bool Geometry::IsLess (const SignedAngle& ab1, const SignedAngle& ab2)
{
	if (ab2.value - ab1.value > ab1.eps) {
		return true;
	} else {
		return false;
	}
}


GEOMETRY_DLL_EXPORT bool IsBetween(const Geometry::SignedAngle& begAng, const Geometry::SignedAngle& endAng, const Geometry::SignedAngle& toTest);



inline bool Geometry::IsNear (const SignedAngle& ab1, const SignedAngle& ab2, double givenEps)
{
	if (fabs (ab1.GetValue () - ab2.GetValue ()) <= givenEps) {
		return true;
	} else {
		return false;
	}
}

inline bool Geometry::IsGreaterOrNear (const SignedAngle& ab1, const SignedAngle& ab2, double givenEps)
{
	if (ab2.GetValue () - ab1.GetValue () <= givenEps) {
		return true;
	} else {
		return false;
	}
}

inline bool Geometry::IsLessOrNear (const SignedAngle& ab1, const SignedAngle& ab2, double givenEps)
{
	if (ab1.GetValue () - ab2.GetValue () <= givenEps) {
		return true;
	} else {
		return false;
	}
}

inline bool Geometry::IsGreater (const SignedAngle& ab1, const SignedAngle& ab2, double givenEps)
{
	if (ab1.GetValue () - ab2.GetValue () > givenEps) {
		return true;
	} else {
		return false;
	}
}

inline bool Geometry::IsLess (const SignedAngle& ab1, const SignedAngle& ab2, double givenEps)
{
	if (ab2.GetValue () - ab1.GetValue () > givenEps) {
		return true;
	} else {
		return false;
	}
}

inline Geometry::SignedAngle Geometry::SignedAngle::operator- (void) const

{
	return SignedAngle (-value);
}

inline Geometry::SignedAngle Geometry::operator+ (const Geometry::SignedAngle& ab1, const Geometry::SignedAngle& ab2)
{
	return SignedAngle (ab1.value + ab2.value);
}

inline Geometry::SignedAngle Geometry::operator- (const Geometry::SignedAngle& ab1, const Geometry::SignedAngle& ab2)
{
	return SignedAngle (ab1.value - ab2.value);
}

inline Geometry::SignedAngle Geometry::SignedAngle::operator* (const Real& ratio) const
{
	return SignedAngle (value * ratio.GetValue ());
}

inline Geometry::Real Geometry::operator/ (const Geometry::SignedAngle& ab1, const Geometry::SignedAngle& ab2)
{
	return Real (ab1.value / ab2.value);
}

inline Geometry::SignedAngle Geometry::SignedAngle::operator/ (const Geometry::Real& ratio) const
{
	return SignedAngle (value / ratio.GetValue ());
}


inline Geometry::SignedAngle& Geometry::SignedAngle::operator= (const Geometry::SignedAngle& source)
{
	if (this != &source) {
		this->value = source.value;
	}
	return *this;
}

inline Geometry::SignedAngle& Geometry::SignedAngle::operator+= (const Geometry::SignedAngle& other)
{
	value += other.value;
	Normalize ();
	return *this;
}

inline Geometry::SignedAngle& Geometry::SignedAngle::operator-= (const Geometry::SignedAngle& other)
{
	value -= other.value;
	Normalize ();
	return *this;
}

inline Geometry::SignedAngle& Geometry::SignedAngle::operator/= (const Real& ratio)
{
	value /= ratio.GetValue ();
	Normalize ();
	return *this;
}

inline double Geometry::SignedAngle::GetValue (AngleUnit unit) const
{
	if (unit == Radian) {
		return value;
	} else {
		return value * RadianToDegree;
	}
}

inline void Geometry::SignedAngle::SetEps (double newEps)
{
	eps = newEps;
}

inline double Geometry::SignedAngle::GetEps (void)
{
	return eps;
}

/* normalize: -2*PI <= retval <= 2*PI */
inline void Geometry::SignedAngle::Normalize (void) const
{
	/* normalize */
	if (fabs (value) > 2.0 * PI + eps) {
		value = fmod (value, 2.0 * PI);
	}
}

/* normalize: -2*PI <= retval <= 2*PI */
inline void Geometry::SignedAngle::Normalize (double givenEps) const
{
	/* normalize */
	if (fabs (value) > 2.0 * PI + givenEps) {
		value = fmod (value, 2.0 * PI);
	}
}

#endif
