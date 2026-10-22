// *********************************************************************************************************************
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ
//
// SG compatible
//
// *********************************************************************************************************************

#if !defined DISCRETES_HPP
#define DISCRETES_HPP

#pragma once

#include "Algorithms.hpp"
#include "RealNumber.h"	// Eps
#include "DoubleClassification.hpp"


namespace PointIndex
{

template <int I>
class Point
{
public:
	double values[I];

public:
	explicit Point ()
	{
		for (UIndex i = 0; i < I; ++i) {
			values[i] = 0.0;
		}
	}

	Point (double val)
	{
		for (UIndex i = 0; i < I; ++i) {
			values[i] = val;
		}
	}

	template <typename... Ts>
	explicit Point (Ts... vals) {
		static_assert (sizeof...(Ts) == I, "PointIndex::Point::Point - wrong number of arguments given");
		StoreValues (0, vals...);
	}

private:
	void StoreValues (UIndex /*i*/) {
		// do nothing, end of recursion
	}

	template <typename T, typename... Ts>
	void StoreValues (UIndex i, const T& val, Ts... vals) {
		values[i] = val;
		StoreValues (i + 1, vals...);
	}
};


using Point2 = Point<2>;
using Point3 = Point<3>;


template <int value>
struct Pow3 {
	enum { Result = 3 * Pow3<value - 1>::Result };
};

template <>
struct Pow3<1> {
	enum { Result = 3 };
};


template <int I>
class Discretes
{
private:
	Int64 values[I];

private:
	Discretes Modulo (UInt32 u) const
	{
		Discretes retVal = *this;
		for (UIndex i = 0; i < I; ++i) {
			retVal.values[i] += Int32 ((u % 3) - 1);
			u /= 3;
		}

		return retVal;
	}

	Int64 Discrete (double d, double eps)
	{
		static const Int64 discretizedInvalidDoublesSpecialValue = MaxInt16 + 1;	// Note: just a number that wont appear too often
		if (!GS::CheckDouble (d, BiggestDouble - eps)) {
			return discretizedInvalidDoublesSpecialValue;
		}
		return static_cast<Int64> ((d + eps / 2) / eps);
	}

public:
	Discretes ()
	{
		for (UIndex i = 0; i < I; ++i) {
			values[i] = 0;
		}
	}

	Discretes (const Point<I>& point, double eps = Eps)
	{
		for (UIndex i = 0; i < I; ++i) {
			values[i] = Discrete (point.values[i], eps);
		}
	}

	bool IsNeighbour (const Discretes<I>& other) const
	{
		for (UIndex i = 0; i < I; ++i) {
			if (GS::Abs (values[i] - other.values[i]) > 1) {
				return false;
			}
		}

		return true;
	}

	template <class EnumeratorType>
	void EnumerateNeighbours (EnumeratorType& enumerator) const
	{
		for (UIndex i = 0; i < Pow3<I>::Result; ++i) {
			enumerator (Modulo (i));
		}
	}

	GS::ULong GenerateHashValue () const
	{
		static UInt32 HashPrime = 65599;	// prime for the hash value computation

		GS::ULong hash = 0;
		for (UIndex i = 0; i < I; ++i) {
			hash = hash * HashPrime + (GS::ULong)values[i];
		}

		return hash;
	}

	bool operator== (const Discretes<I>& other) const
	{
		for (UIndex i = 0; i < I; ++i) {
			if (values[i] != other.values[i]) {
				return false;
			}
		}

		return true;
	}
};


}

#endif
