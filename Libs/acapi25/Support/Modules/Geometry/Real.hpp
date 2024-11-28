#if !defined (REAL_HPP)
#define REAL_HPP

#pragma once

#include	<math.h>

#if !defined (REALNUMBER_H)
#include	"RealNumber.h"
#endif

namespace Geometry {

// =============================================================================
//
// General comparision functions (allowing number type-templated algorihms
//
//	(no general implementation, only specializations)
// =============================================================================

	template <class NumberType>	bool	IsNear			(const NumberType& r1, const NumberType& r2);
	template <class NumberType>	bool	IsNotNear		(const NumberType& r1, const NumberType& r2);
	template <class NumberType>	bool	IsGreaterOrNear	(const NumberType& r1, const NumberType& r2);
	template <class NumberType>	bool	IsLessOrNear	(const NumberType& r1, const NumberType& r2);
	template <class NumberType>	bool	IsGreater		(const NumberType& r1, const NumberType& r2);
	template <class NumberType>	bool	IsLess			(const NumberType& r1, const NumberType& r2);

	template <class NumberType>	bool	IsNearZero		(const NumberType& r);
	template <class NumberType>	bool	IsNotNearZero	(const NumberType& r);
	template <class NumberType>	bool	IsNegative		(const NumberType& r);
	template <class NumberType>	bool	IsNotNegative	(const NumberType& r);
	template <class NumberType>	bool	IsPositive		(const NumberType& r);
	template <class NumberType>	bool	IsNotPositive	(const NumberType& r);

	template <class NumberType>	bool	IsNear			(const NumberType& r1, const NumberType& r2, double givenEps);
	template <class NumberType>	bool	IsNotNear		(const NumberType& r1, const NumberType& r2, double givenEps);
	template <class NumberType>	bool	IsGreaterOrNear	(const NumberType& r1, const NumberType& r2, double givenEps);
	template <class NumberType>	bool	IsLessOrNear	(const NumberType& r1, const NumberType& r2, double givenEps);
	template <class NumberType>	bool	IsGreater		(const NumberType& r1, const NumberType& r2, double givenEps);
	template <class NumberType>	bool	IsLess			(const NumberType& r1, const NumberType& r2, double givenEps);

	template <class NumberType>	bool	IsNearZero		(const NumberType& r, double givenEps);
	template <class NumberType>	bool	IsNotNearZero	(const NumberType& r, double givenEps);
	template <class NumberType>	bool	IsNegative		(const NumberType& r, double givenEps);
	template <class NumberType>	bool	IsNotNegative	(const NumberType& r, double givenEps);
	template <class NumberType>	bool	IsPositive		(const NumberType& r, double givenEps);
	template <class NumberType>	bool	IsNotPositive	(const NumberType& r, double givenEps);

	template <class NumberType>	NumberType	Discretize	(NumberType r);
	template <class NumberType>	NumberType	Discretize	(NumberType r, double givenEps);

	template <class NumberType>	NumberType	Abs  		(const NumberType& param); // absolute value
	template <class NumberType>	NumberType	Sgn  		(const NumberType& param);	// signum value
	template <class NumberType>	NumberType	Sqrt 		(const NumberType& param);	// square root value
	template <class NumberType>	double		GetEps		(void);


// =============================================================================
//
// General comparision functions specialized for doubles
//
// =============================================================================

	template<>
	inline bool IsNear (const double& r1, const double& r2)
	{
		return fabs (r1 - r2) <= EPS;
	}

	template<>
	inline bool IsNotNear (const double& r1, const double& r2)
	{
		return fabs (r1 - r2) > EPS;
	}

	template<>
	inline bool IsGreaterOrNear (const double& r1, const double& r2)
	{
		return r2 - r1 <= EPS;
	}

	template<>
	inline bool IsLessOrNear (const double& r1, const double& r2)
	{
		return r1 - r2 <= EPS;
	}

	template<>
	inline bool IsGreater (const double& r1, const double& r2)
	{
		return r1 - r2 > EPS;
	}

	template<>
	inline bool IsLess (const double& r1, const double& r2)
	{
		return r2 - r1 > EPS;
	}

	template<>
	inline bool IsNearZero (const double& r)
	{
		return fabs (r) <= EPS;
	}

	template<>
	inline bool IsNotNearZero (const double& r)
	{
		return fabs (r) > EPS;
	}

	template<>
	inline bool IsNegative (const double& r)
	{
		return r < -EPS;
	}

	template<>
	inline bool IsNotNegative (const double& r)
	{
		return r >= -EPS;
	}

	template<>
	inline bool IsPositive (const double& r)
	{
		return r > EPS;
	}

	template<>
	inline bool IsNotPositive (const double& r)
	{
		return r <= EPS;
	}


	template<>
	inline bool IsNear (const double& r1, const double& r2, double givenEps)
	{
		return fabs (r1 - r2) <= givenEps;
	}

	template<>
	inline bool IsNotNear (const double& r1, const double& r2, double givenEps)
	{
		return fabs (r1 - r2) > givenEps;
	}

	template<>
	inline bool IsGreaterOrNear (const double& r1, const double& r2, double givenEps)
	{
		return r2 - r1 <= givenEps;
	}

	template<>
	inline bool IsLessOrNear (const double& r1, const double& r2, double givenEps)
	{
		return r1 - r2 <= givenEps;
	}

	template<>
	inline bool IsGreater (const double& r1, const double& r2, double givenEps)
	{
		return r1 - r2 > givenEps;
	}

	template<>
	inline bool IsLess (const double& r1, const double& r2, double givenEps)
	{
		return r2 - r1 > givenEps;
	}

	template<>
	inline bool IsNearZero (const double& r, double givenEps)
	{
		return fabs (r) <= givenEps;
	}

	template<>
	inline bool IsNotNearZero (const double& r, double givenEps)
	{
		return fabs (r) > givenEps;
	}

	template<>
	inline bool IsNegative (const double& r1, double givenEps)
	{
		return r1 < -givenEps;
	}

	template<>
	inline bool IsNotNegative (const double& r1, double givenEps)
	{
		return r1 >= -givenEps;
	}

	template<>
	inline bool IsPositive (const double& r1, double givenEps)
	{
		return r1 > givenEps;
	}

	template<>
	inline bool IsNotPositive (const double& r1, double givenEps)
	{
		return r1 <= givenEps;
	}

	template<>
	inline double Discretize (double r)
	{
		return floor((r + EPS/2) / EPS);;
	}

	template<>
	inline double Discretize (double r, double givenEps)
	{
		return floor((r + givenEps/2) / givenEps);
	}

	template<>
	inline double	Abs (const double& r)
	{
		return fabs (r);
	}

	template<>
	inline double	Sgn (const double& r)
	{
		if (IsNearZero (r)) {
			return 0.0;
		} else if (r < 0.0) {
			return -1.0;
		} else {
			return 1.0;
		}
	}

	template<>
	inline double	Sqrt (const double& r)
	{
		return sqrt (r);
	}

	template<>
	inline float	Sqrt (const float& r)
	{
		return sqrt (r);
	}


	template<>
	inline double GetEps<double> (void)
	{
		return EPS;
	}


// =============================================================================
//
// Real number class
//
// =============================================================================


class GEOMETRY_DLL_EXPORT Real {

private:
	double	value;

	static	double	eps;
	inline	static void		SetEps (double eps);

public:

	static const Real Zero;

	inline	Real (void);
	inline	Real (const Real& source);
	inline	explicit Real (double real);
	inline	~Real ();

	friend	bool	IsNear <Real>			(const Real& r1, const Real& r2);
	friend	bool	IsNotNear <Real>		(const Real& r1, const Real& r2);
	friend	bool	IsGreaterOrNear <Real>	(const Real& r1, const Real& r2);
	friend	bool	IsLessOrNear <Real>		(const Real& r1, const Real& r2);
	friend	bool	IsGreater <Real>		(const Real& r1, const Real& r2);
	friend	bool	IsLess <Real>			(const Real& r1, const Real& r2);

	friend	bool	IsNearZero <Real>		(const Real& r);
	friend	bool	IsNotNearZero <Real>	(const Real& r);
	friend	bool	IsNegative <Real>		(const Real& r);
	friend	bool	IsNotNegative <Real>	(const Real& r);
	friend	bool	IsPositive <Real>		(const Real& r);
	friend	bool	IsNotPositive <Real>	(const Real& r);

	friend	bool	IsNear <Real>			(const Real& r1, const Real& r2, double givenEps);
	friend	bool	IsNotNear <Real>		(const Real& r1, const Real& r2, double givenEps);
	friend	bool	IsGreaterOrNear <Real>	(const Real& r1, const Real& r2, double givenEps);
	friend	bool	IsLessOrNear <Real>		(const Real& r1, const Real& r2, double givenEps);
	friend	bool	IsGreater <Real>		(const Real& r1, const Real& r2, double givenEps);
	friend	bool	IsLess <Real>			(const Real& r1, const Real& r2, double givenEps);

	friend	bool	IsNearZero <Real>		(const Real& r, double givenEps);
	friend	bool	IsNotNearZero <Real>	(const Real& r, double givenEps);
	friend	bool	IsNegative <Real>		(const Real& r, double givenEps);
	friend	bool	IsNotNegative <Real>	(const Real& r, double givenEps);
	friend	bool	IsPositive <Real>		(const Real& r, double givenEps);
	friend	bool	IsNotPositive <Real>	(const Real& r, double givenEps);

	inline	Real	operator-	(void) const;
	friend 	Real	operator+	(const Real& r1, const Real& r2);
	friend	Real	operator-	(const Real& r1, const Real& r2);
	friend	Real	operator*	(const Real& r1, const Real& r2);
	friend	Real	operator/	(const Real& r1, const Real& r2);

	inline	Real& operator=		(const Real& source);
	inline	Real& operator+=	(const Real& other);
	inline	Real& operator-=	(const Real& other);
	inline	Real& operator*=	(const Real& other);
	inline	Real& operator/=	(const Real& other);

	friend	Real	Abs <Real> (const Real& r);
	friend	Real	Sgn <Real> (const Real& r);
	friend	Real	Sqrt <Real> (const Real& r);
	friend	Real	Min (const Real& r1, const Real& r2);
	friend	Real	Max (const Real& r1, const Real& r2);

	inline	operator double () const;
	inline	double	GetValue (void) const;

	friend	double GetEps <Real> (void);
};


Real::Real (void)
	:value (0.0)
{
}

Real::Real (const Real& source)
	:value (source.value)
{
}

Real::Real (double real)
	:value (real)
{
}

Real::~Real ()
{
	// empty
}

Real Real::operator- (void) const

{
	return Real (-value);
}

Real& Real::operator= (const Real& source)
{
	if (this != &source) {
		this->value = source.value;
	}
	return *this;
}

Real& Real::operator+= (const Real& other)
{
	value += other.value;
	return *this;
}

Real& Real::operator-= (const Real& other)
{
	value -= other.value;
	return *this;
}

Real& Real::operator*= (const Real& other)
{
	value *= other.value;
	return *this;
}

Real& Real::operator/= (const Real& other)
{
	value /= other.value;
	return *this;
}

// =============================================================================
//
// General comparision functions specialized for Reals
//
// =============================================================================

// The eps could be accessed with "Real::" instead of "real."
// In the future it is imaginable that all Reals have an own eps.
// This notation express this possible direction.

template<>
inline bool IsNear (const Real& r1, const Real& r2)
{
	return fabs (r1.value - r2.value) <= r1.eps;
}

template<>
inline bool IsNotNear (const Real& r1, const Real& r2)
{
	return fabs (r1.value - r2.value) > r1.eps;
}

template<>
inline bool IsGreaterOrNear (const Real& r1, const Real& r2)
{
	return r2.value - r1.value <= r1.eps;
}

template<>
inline bool IsLessOrNear (const Real& r1, const Real& r2)
{
	return r1.value - r2.value <= r1.eps;
}

template<>
inline bool IsGreater (const Real& r1, const Real& r2)
{
	return r1.value - r2.value > r1.eps;
}

template<>
inline bool IsLess (const Real& r1, const Real& r2)
{
	return r2.value - r1.value > r1.eps;
}

template<>
inline bool IsNearZero (const Real& r)
{
	return fabs (r.value) <= r.eps;
}

template<>
inline bool IsNotNearZero (const Real& r)
{
	return fabs (r.value) > r.eps;
}

template<>
inline bool IsNegative (const Real& r)
{
	return r.value < -r.eps;
}

template<>
inline bool IsNotNegative (const Real& r)
{
	return r.value >= -r.eps;
}

template<>
inline bool IsPositive (const Real& r)
{
	return r.value > r.eps;
}

template<>
inline bool IsNotPositive (const Real& r)
{
	return r.value <= r.eps;
}

template<>
inline bool IsNear (const Real& r1, const Real& r2, double givenEps)
{
	return fabs (r1.value - r2.value) <= givenEps;
}

template<>
inline bool IsNotNear (const Real& r1, const Real& r2, double givenEps)
{
	return fabs (r1.value - r2.value) > givenEps;
}

template<>
inline bool IsGreaterOrNear (const Real& r1, const Real& r2, double givenEps)
{
	return r2.value - r1.value <= givenEps;
}

template<>
inline bool IsLessOrNear (const Real& r1, const Real& r2, double givenEps)
{
	return r1.value - r2.value <= givenEps;
}

template<>
inline bool IsGreater (const Real& r1, const Real& r2, double givenEps)
{
	return r1.value - r2.value > givenEps;
}

template<>
inline bool IsLess (const Real& r1, const Real& r2, double givenEps)
{
	return r2.value - r1.value > givenEps;
}

template<>
inline bool IsNearZero (const Real& r, double givenEps)
{
	return fabs (r.value) <= givenEps;
}

template<>
inline bool IsNotNearZero (const Real& r, double givenEps)
{
	return fabs (r.value) > givenEps;
}

template<>
inline bool IsNegative (const Real& r1, double givenEps)
{
	return r1.value < -givenEps;
}

template<>
inline bool IsNotNegative (const Real& r1, double givenEps)
{
	return r1.value >= -givenEps;
}

template<>
inline bool IsPositive (const Real& r1, double givenEps)
{
	return r1.value > givenEps;
}

template<>
inline bool IsNotPositive (const Real& r1, double givenEps)
{
	return r1.value <= givenEps;
}

inline Real operator+ (const Real& r1, const Real& r2)
{
	return Real (r1.value + r2.value);
}

inline Real operator- (const Real& r1, const Real& r2)
{
	return Real (r1.value - r2.value);
}

inline Real operator* (const Real& r1, const Real& r2)
{
	return Real (r1.value * r2.value);
}

inline Real operator/ (const Real& r1, const Real& r2)
{
	return Real (r1.value / r2.value);
}

inline Real::operator double () const
{
	return value;
}

inline double Real::GetValue () const
{
	return value;
}

inline void Real::SetEps (double newEps)
{
	eps = newEps;
}

template<>
inline double GetEps<Real> (void)
{
	return Real::eps;
}


template<>
inline Real	Abs<Real> (const Real& r)
{
	return Real (fabs (r.value));
}

template<>
inline Real	Sgn<Real> (const Real& r)
{
	return Real (Sgn (r.value));
}

template<>
inline Real	Sqrt<Real> (const Real& r)
{
	return Real (sqrt (r.value));
}

inline Real Min (const Real& r1, const Real& r2)
{
	return Real (r1.value < r2.value ? r1.value : r2.value);
}

inline Real Max (const Real& r1, const Real& r2)
{
	return Real (r1.value > r2.value ? r1.value : r2.value);
}

} // namespace Geometry

#endif
