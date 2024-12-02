// *****************************************************************************
// Length. Has operators and comparisions with epsilon.
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// [SG compatible]
// *****************************************************************************

#ifndef GS_GEOMETRY_LENGTH_HPP
#define GS_GEOMETRY_LENGTH_HPP

#include "Real.hpp"

// from GSRoot
#include "GSDebug.hpp"

// from Standard Library
#include <cmath>


namespace Geometry {


class Length {
private:

	double mValue = 0.0;

public:

	Length () = default;
	explicit constexpr Length (double value);

	bool					IsNear			(Length other, double eps = Eps) const;
	constexpr bool			IsGreaterOrNear	(Length other, double eps = Eps) const;
	constexpr bool			IsLessOrNear	(Length other, double eps = Eps) const;
	constexpr bool			IsGreater		(Length other, double eps = Eps) const;
	constexpr bool			IsLess			(Length other, double eps = Eps) const;

	constexpr bool			IsNearZero		(double eps = Eps) const;
	constexpr bool			IsPositive		(double eps = Eps) const;

	constexpr operator		double () const;
	constexpr double		GetValue () const;

	constexpr void			operator+=		(Length other);
	constexpr void			operator-=		(Length other);
	constexpr void			operator*=		(Length other);
	constexpr void			operator/=		(Length other);

	static constexpr double	GetEps ();

// External operators

	friend constexpr Length	operator+ (Length l1, Length l2)	{ return Length { l1.mValue + l2.mValue }; }
	friend constexpr Length	operator* (Length l1, Length l2)	{ return Length { l1.mValue * l2.mValue }; }
	friend constexpr Length	operator- (Length l1, Length l2)	{ return Length { l1.mValue - l2.mValue }; }
	friend constexpr Length	operator/ (Length l1, Length l2)	{ return Length { l1.mValue / l2.mValue }; }

	friend constexpr double	operator+ (Length l, double v)		{ return l.mValue + v; }
	friend constexpr double operator* (Length l, double v)		{ return l.mValue * v; }
	friend constexpr double operator- (Length l, double v)		{ return l.mValue - v; }
	friend constexpr double operator/ (Length l, double v)		{ return l.mValue / v; }

	friend constexpr double	operator+ (double v, Length l)		{ return v + l.mValue; }
	friend constexpr double operator* (double v, Length l)		{ return v * l.mValue; }
	friend constexpr double operator- (double v, Length l)		{ return v - l.mValue; }
	friend constexpr double operator/ (double v, Length l)		{ return v / l.mValue; }
};


/* ================================================================================================================== */


constexpr Length::Length (double value)
	: mValue { value }
{
	// !!! error, we should throw an exception later
	if (value + Eps < 0.0) {
		DBBREAK_STR ("Length is initialized with negative number!");
	}
}


inline bool	Length::IsNear (Length other, double eps) const
{
	return std::fabs (mValue - other.mValue) <= eps;
}


constexpr bool	Length::IsGreaterOrNear (Length other, double eps) const
{
	return other.mValue - mValue <= eps;
}


constexpr bool	Length::IsLessOrNear (Length other, double eps) const
{
	return mValue - other.mValue <= eps;
}


constexpr bool	Length::IsGreater (Length other, double eps) const
{
	return mValue - other.mValue > eps;
}


constexpr bool	Length::IsLess (Length other, double eps) const
{
	return other.mValue - mValue > eps;
}


constexpr bool	Length::IsNearZero (double eps) const
{
	return mValue <= eps;
}


constexpr bool	Length::IsPositive (double eps) const
{
	return mValue > eps;
}


constexpr	Length::operator double () const
{
	return mValue;
}


constexpr double	Length::GetValue () const
{
	return mValue;
}


constexpr void	Length::operator+= (Length other)
{
	mValue += other.mValue;
}


constexpr void	Length::operator-= (Length other)
{
	mValue -= other.mValue;
}


constexpr void	Length::operator*= (Length other)
{
	mValue *= other.mValue;
}


constexpr void	Length::operator/= (Length other)
{
	mValue /= other.mValue;
}


constexpr double	Length::GetEps ()
{
	return Eps;
}


/* ================================================================================================================== */


constexpr Length	Min (Length l1, Length l2)
{
	return l1.GetValue () < l2.GetValue () ? l1 : l2;
}


constexpr Length	Max (Length l1, Length l2)
{
	return l1.GetValue () > l2.GetValue () ? l1 : l2;
}


} // namespace Geometry


#endif /* GS_GEOMETRY_LENGTH_HPP */
