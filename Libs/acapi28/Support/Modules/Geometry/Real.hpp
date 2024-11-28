#if !defined (REAL_HPP)
#define REAL_HPP

#pragma once

#include	<cmath>
#include	"RealNumber.h"


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
		return std::fabs (r1 - r2) <= EPS;
	}

	template<>
	inline bool IsNotNear (const double& r1, const double& r2)
	{
		return std::fabs (r1 - r2) > EPS;
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
		return std::fabs (r) <= EPS;
	}

	template<>
	inline bool IsNotNearZero (const double& r)
	{
		return std::fabs (r) > EPS;
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
		return std::fabs (r1 - r2) <= givenEps;
	}

	template<>
	inline bool IsNotNear (const double& r1, const double& r2, double givenEps)
	{
		return std::fabs (r1 - r2) > givenEps;
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
		return std::fabs (r) <= givenEps;
	}

	template<>
	inline bool IsNotNearZero (const double& r, double givenEps)
	{
		return std::fabs (r) > givenEps;
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
		return std::floor ((r + EPS/2) / EPS);;
	}

	template<>
	inline double Discretize (double r, double givenEps)
	{
		return std::floor ((r + givenEps/2) / givenEps);
	}

	template<>
	inline double	Abs (const double& r)
	{
		return std::fabs (r);
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
		return std::sqrt (r);
	}

	template<>
	inline float	Sqrt (const float& r)
	{
		return std::sqrt (r);
	}


	template<>
	inline double GetEps<double> (void)
	{
		return EPS;
	}


} // namespace Geometry

#endif
