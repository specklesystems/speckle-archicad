// *****************************************************************************
// Length. Has operators and comparisions with epsilon.
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// [SG compatible]
// *****************************************************************************

#if !defined (LENGTH_HPP)
#define LENGTH_HPP

#pragma once

#undef		Length /* !!! PlotMaker */

#include	<math.h>

#include	"Real.hpp"

namespace Geometry {
class Length {

private:
	double	value;			// The value of the length, the key variable
	GEOMETRY_DLL_EXPORT static	double	eps;	// The epsilon used by length type
	inline	static void		SetEps (double eps);

public:
	static const Length Zero;

	inline	Length (void);
	inline	Length (const Length& source);
	inline	explicit Length (double real);
	inline	explicit Length (const Real& real);
	inline	~Length ();

	inline	bool	IsNear			(const Length& other) const;
	inline	bool	IsGreaterOrNear	(const Length& other) const;
	inline	bool	IsLessOrNear	(const Length& other) const;
	inline	bool	IsGreater		(const Length& other) const;
	inline	bool	IsLess			(const Length& other) const;

	inline	bool	IsNearZero		(void) const;
	inline	bool	IsPositive		(void) const;

	inline	bool	IsNear			(const Length& other, double givenEps) const;
	inline	bool	IsGreaterOrNear	(const Length& other, double givenEps) const;
	inline	bool	IsLessOrNear	(const Length& other, double givenEps) const;
	inline	bool	IsGreater		(const Length& other, double givenEps) const;
	inline	bool	IsLess			(const Length& other, double givenEps) const;

	inline	bool	IsNearZero		(double givenEps) const;
	inline	bool	IsPositive		(double givenEps) const;

	friend	Length	operator+	(const Length& l1, const Length& l2);
	friend	Length	operator-	(const Length& l1, const Length& l2);
	friend	Real	operator/	(const Length& l1, const Length& l2);

	inline	Length	operator*	(const Real& ratio) const;
	inline	Length	operator/	(const Real& ratio) const;

	inline	Length& operator=	(const Length& source);
	inline	Length& operator+=	(const Length& other);
	inline	Length& operator-=	(const Length& other);
	inline	Length& operator/=	(const Real& ratio);

	friend	Length	Min (const Length& l1, const Length& l2);
	friend	Length	Max (const Length& l1, const Length& l2);

	inline	operator double () const;
	inline	double	GetValue (void) const;

	inline	static double	GetEps (void);
};

Length::Length (void)
	:value (0.0)
{
}

Length::Length (const Length& source)
	:value (source.value)
{
}

Length::Length (double real)
	:value (real)
{
	// !!! error, we should throw an exception later
	if (value + eps < 0.0) {
		DBBREAK_STR ("Length is initialized with negative number!");
	}
}

Length::Length (const Real& real)
	:value (real.GetValue ())
{
	// !!! error, we should throw an exception later
	if (value + eps < 0.0) {
		DBBREAK_STR ("Length is initialized with negative number!");
	}
}

Length::~Length ()
{
	// empty
}

bool Length::IsNear (const Length& other) const
{
	return fabs (this->value - other.GetValue ()) <= eps;
}

bool Length::IsGreaterOrNear (const Length& other) const
{
	return other.GetValue () - GetValue () <= eps;
}

bool Length::IsLessOrNear (const Length& other) const
{
	return GetValue () - other.GetValue () <= eps;
}

bool Length::IsGreater (const Length& other) const
{
	return GetValue () - other.GetValue () > eps;
}

bool Length::IsLess (const Length& other) const
{
	return other.GetValue () - GetValue () > eps;
}

bool Length::IsNearZero (void) const
{
	return fabs (this->value) <= eps;
}

bool Length::IsPositive (void) const
{
	return fabs (this->value) > eps;
}


bool Length::IsNear (const Length& other, double givenEps) const
{
	return fabs (GetValue () - other.GetValue ()) <= givenEps;
}

bool Length::IsGreaterOrNear (const Length& other, double givenEps) const
{
	return other.GetValue () - GetValue () <= givenEps;
}

bool Length::IsLessOrNear (const Length& other, double givenEps) const
{
	return GetValue () - other.GetValue () <= givenEps;
}

bool Length::IsGreater (const Length& other, double givenEps) const
{
	return GetValue () - other.GetValue () > givenEps;
}

bool Length::IsLess (const Length& other, double givenEps) const
{
	return other.GetValue () - GetValue () > givenEps;
}

bool Length::IsNearZero (double givenEps) const
{
	return fabs (GetValue ()) <= givenEps;
}

bool Length::IsPositive (double givenEps) const
{
	return fabs (GetValue ()) > givenEps;
}


inline Length operator+ (const Length& l1, const Length& l2)
{
	return Length (l1.value + l2.value);
}

inline Length operator- (const Length& l1, const Length& l2)
{
	return Length (l1.value - l2.value);
}

inline Real operator/ (const Length& l1, const Length& l2)
{
	return Real (l1.value / l2.value);
}

Length Length::operator/ (const Real& ratio) const
{
	return Length (value / ratio.GetValue ());
}

Length& Length::operator= (const Length& source)
{
	if (this != &source) {
		this->value = source.value;
	}
	return *this;
}

Length& Length::operator+= (const Length& other)
{
	value += other.value;
	return *this;
}

Length& Length::operator-= (const Length& other)
{
	value -= other.value;
	return *this;
}


Length& Length::operator/= (const Real& ratio)
{
	value /= ratio.GetValue ();
	return *this;
}

inline	Length::operator double () const
{
	return value;
}

double Length::GetValue () const
{
	return value;
}

void Length::SetEps (double newEps)
{
	eps = newEps;
}

double Length::GetEps (void)
{
	return eps;
}

inline Length Min (const Length& l1, const Length& l2)
{
	return Length (l1.value < l2.value ? l1.value : l2.value);
}

inline Length Max (const Length& l1, const Length& l2)
{
	return Length (l1.value > l2.value ? l1.value : l2.value);
}
}
#endif
