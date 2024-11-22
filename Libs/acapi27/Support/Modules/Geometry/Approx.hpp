
// *********************************************************************************************************************
// Description:		Approx.hpp
//
// Module:			Modeler
// Contact person:	BeA
//
// *********************************************************************************************************************

#pragma once

#ifndef APPROX_HPP
#define APPROX_HPP

#include "DoubleClassification.hpp"

#include <float.h>

namespace QXTools {

class Approx
{
private:
	double min, max;

	static_assert (sizeof (Int64) == sizeof (double), "chksize");


	static GS_FORCE_INLINE double MulMin (double v1, double v2)
	{
		double val = v1 * v2;
		if (val == 0) {
			if (v1 != 0 && v2 != 0) { // the result of v1 * v2 is not exactly 0 (underflow)
				val = -DBL_MIN;
				DBASSERT (val < 0);
			}
		} else {
			DecOneUlp (&val);
		}
		return val;
	}

	static GS_FORCE_INLINE double MulMax (double v1, double v2)
	{
		double val = v1 * v2;
		if (val == 0) {
			if (v1 != 0 && v2 != 0) { // the result of v1 * v2 is not exactly 0 (underflow)
				val = DBL_MIN;
				DBASSERT (val > 0);
			}
		} else {
			IncOneUlp (&val);
		}
		return val;
	}

	static GS_FORCE_INLINE double DivMin (double v1, double v2)
	{
		double val = v1 / v2;
		if (DBERROR (v2 == 0.0)) {
			return val;
		}

		if (val == 0) {
			if (v1 != 0) { // the result of v1 / v2 is not exactly 0 (underflow)
				val = -DBL_MIN;
				DBASSERT (val < 0);
			}
		} else {
			DecOneUlp (&val);
		}
		return val;
	}

	static GS_FORCE_INLINE double DivMax (double v1, double v2)
	{
		double val = v1 / v2;
		if (DBERROR (v2 == 0.0)) {
			return val;
		}
		if (val == 0) {
			if (v1 != 0) { // the result of v1 / v2 is not exactly 0 (underflow)
				val = DBL_MIN;
				DBASSERT (val > 0);
			}
		} else {
			IncOneUlp (&val);
		}
		return val;
	}

	static GS_FORCE_INLINE bool IsNumber (double* d)
	{
		GS::DoubleClass::Value dc = GS::ClassifyDouble (*d);
		return dc == GS::DoubleClass::Zero || dc == GS::DoubleClass::Normal || dc == GS::DoubleClass::Denormal;
	}

public:

	static GS_FORCE_INLINE void IncOneUlp (double* d)
	{
		// no NAN, underflow or overflow checks :
		// 0 conversions are assumed to be exact
		// addition and multiplication of integers can't cause underflow
		// overflows should be avoided on the caller's side

#ifdef CHECKED_VERSION
		double savedVal = *d;
#endif
		if (*d > 0) {
			++(*reinterpret_cast<Int64*> (d));
		} else if (*d < 0) {
			--(*reinterpret_cast<Int64*> (d));
		}
		DBASSERT (savedVal == 0 || savedVal < *d);
		DBASSERT (IsNumber (d));
	}

	static GS_FORCE_INLINE double IncOneUlp (double d)
	{
		IncOneUlp (&d);
		return d;
	}

	// With underflow handling
	static GS_FORCE_INLINE void IncOneUlp_Uf (double* d)
	{
		if (*d == 0) {
			*d = DBL_MIN;
			DBASSERT (*d > 0);
		} else {
			IncOneUlp (d);
		}
	}

	static GS_FORCE_INLINE double IncOneUlp_Uf (double d)
	{
		IncOneUlp_Uf (&d);
		return d;
	}

	static GS_FORCE_INLINE void DecOneUlp (double* d)
	{
#ifdef CHECKED_VERSION
		double savedVal = *d;
#endif
		if (*d > 0) {
			--(*reinterpret_cast<Int64*> (d));
		} else if (*d < 0) {
			++(*reinterpret_cast<Int64*> (d));
		}
		DBASSERT (savedVal == 0 || savedVal > *d);
		DBASSERT (IsNumber (d));
	}

	static GS_FORCE_INLINE double DecOneUlp (double d)
	{
		DecOneUlp (&d);
		return d;
	}

	static GS_FORCE_INLINE void DecOneUlp_Uf (double* d)
	{
		if (*d == 0) {
			*d = -DBL_MIN;
			DBASSERT (*d < 0);
		} else {
			DecOneUlp (d);
		}
	}

	static GS_FORCE_INLINE double DecOneUlp_Uf (double d)
	{
		DecOneUlp_Uf (&d);
		return d;
	}

	GS_FORCE_INLINE Approx () : min (0.0), max (0.0)
	{
	}

	GS_FORCE_INLINE Approx (double min, double max) : min (min), max (max)
	{
		DBASSERT (min <= max);
	}

	GS_FORCE_INLINE Approx (Int32 minInt, Int32 maxInt) : min (minInt), max (maxInt)
	{
		DBASSERT (static_cast<Int32> (min) == minInt);
		DBASSERT (static_cast<Int32> (max) == maxInt);

		DBASSERT (min <= max);
	}

	GS_FORCE_INLINE Approx (Int64 minInt, Int64 maxInt) : min (static_cast<double> (minInt)), max (static_cast<double> (maxInt))
	{
		DecOneUlp (&min);
		IncOneUlp (&max);

		DBASSERT (static_cast<Int64> (min) <= minInt);
		DBASSERT (static_cast<Int64> (max) >= maxInt);

		DBASSERT (min <= max);
	}

	GS_FORCE_INLINE Approx	operator + (const Approx& rhs) const
	{
		double newMin = min + rhs.min;
		DecOneUlp (&newMin);
		double newMax = max + rhs.max;
		IncOneUlp (&newMax);

		return Approx (newMin, newMax);
	}

	GS_FORCE_INLINE Approx&	operator += (const Approx& rhs)
	{
		min += rhs.min;
		DecOneUlp (&min);
		max += rhs.max;
		IncOneUlp (&max);

		DBASSERT (min <= max);

		return *this;
	}

	GS_FORCE_INLINE Approx	operator - () const
	{
		return Approx (-max, -min);
	}


	GS_FORCE_INLINE Approx	operator - (const Approx& rhs) const
	{
		double newMin = min - rhs.max;
		DecOneUlp (&newMin);
		double newMax = max - rhs.min;
		IncOneUlp (&newMax);

		return Approx (newMin, newMax);
	}

	GS_FORCE_INLINE Approx	operator -= (const Approx& rhs)
	{
		min -= rhs.max;
		DecOneUlp (&min);
		max -= rhs.min;
		IncOneUlp (&max);

		DBASSERT (min <= max);

		return *this;
	}

	GS_FORCE_INLINE Approx operator * (const Approx& rhs) const
	{
		double newMin, newMax;
		if (0 <= min) {
			if (0 <= rhs.min) {
				newMin = MulMin (min, rhs.min);
				newMax = MulMax (max, rhs.max);
			} else if (rhs.max <= 0) {
				newMin = MulMin (max, rhs.min);
				newMax = MulMax (min, rhs.max);
			} else {
				newMin = MulMin (max, rhs.min);
				newMax = MulMax (max, rhs.max);
			}
		} else if (max <= 0) {
			if (0 <= rhs.min) {
				newMin = MulMin (min, rhs.max);
				newMax = MulMax (max, rhs.min);
			} else if (rhs.max <= 0) {
				newMin = MulMin (max, rhs.max);
				newMax = MulMax (min, rhs.min);
			} else {
				newMin = MulMin (min, rhs.max);
				newMax = MulMax (min, rhs.min);
			}
		} else {
			if (0 <= rhs.min) {
				newMin = MulMin (min, rhs.max);
				newMax = MulMax (max, rhs.max);
			} else if (rhs.max <= 0) {
				newMin = MulMin (max, rhs.min);
				newMax = MulMax (min, rhs.min);
			} else {
				newMin = GS::Min (MulMin (min, rhs.max), MulMin (max, rhs.min));
				newMax = GS::Max (MulMax (min, rhs.min), MulMax (max, rhs.max));
			}
		}

		DBASSERT (newMin < GS::Min (GS::Min (min * rhs.min, min * rhs.max), GS::Min (max * rhs.min, max * rhs.max)) || newMin == 0);
		DBASSERT (newMax > GS::Max (GS::Max (min * rhs.min, min * rhs.max), GS::Max (max * rhs.min, max * rhs.max)) || newMax == 0);

		return Approx (newMin, newMax);
	}

	GS_FORCE_INLINE Approx& operator *= (const Approx& rhs)
	{
		Approx temp = this->operator * (rhs);
		min = temp.min;
		max = temp.max;

		return *this;
	}

	GS_FORCE_INLINE Approx operator / (const Approx& rhs) const
	{
		double newMin, newMax;
		if (0 <= min) {
			if (0 < rhs.min) {  //+/+
				newMin = DivMin (min, rhs.max);
				newMax = DivMax (max, rhs.min);
			} else if (rhs.max < 0) { //+/-
				newMin = DivMin (max, rhs.max);
				newMax = DivMax (min, rhs.min);
			} else {
				DBBREAK_STR ("Division with zero in Approx!");
				newMin = -DBL_MAX;
				newMax = DBL_MAX;
			}
		} else if (max <= 0) {
			if (0 < rhs.min) { //-/+
				newMin = DivMin (min, rhs.min);
				newMax = DivMax (max, rhs.max);
			} else if (rhs.max < 0) { //-/-
				newMin = DivMin (max, rhs.min);
				newMax = DivMax (min, rhs.max);
			} else {
				DBBREAK_STR ("Division with zero in Approx!");
				newMin = -DBL_MAX;
				newMax = DBL_MAX;
			}
		} else {
			if (0 < rhs.min) {
				newMin = DivMin (min, rhs.min);
				newMax = DivMax (max, rhs.min);
			} else if (rhs.max < 0) {
				newMin = DivMin (max, rhs.max);
				newMax = DivMax (min, rhs.max);
			} else {
				DBBREAK_STR ("Division with zero in Approx!");
				newMin = -DBL_MAX;
				newMax = DBL_MAX;
			}
		}

		DBASSERT (newMin < GS::Min (GS::Min (min / rhs.min, min / rhs.max), GS::Min (max / rhs.min, max / rhs.max)) || newMin == 0);
		DBASSERT (newMax > GS::Max (GS::Max (min / rhs.min, min / rhs.max), GS::Max (max / rhs.min, max / rhs.max)) || newMax == 0);

		return Approx (newMin, newMax);
	}

	GS_FORCE_INLINE Approx& operator /= (const Approx& rhs)
	{
		Approx temp = this->operator / (rhs);
		min = temp.min;
		max = temp.max;

		return *this;
	}

	GS_FORCE_INLINE bool CanBeNull () const
	{
		return min <= 0 && max >= 0;
	}

	GS_FORCE_INLINE bool CanBeEqual (const Approx& other) const
	{
		return min <= other.max && other.min <= max;
	}

	GS_FORCE_INLINE bool CanBeLess (const Approx& other) const
	{
		return min <= other.max;
	}

	GS_FORCE_INLINE bool MustBeSameSign (const Approx &val) const
	{
		return max < 0 && val.max < 0 || 0 < min && 0 < val.min;
	}

	GS_FORCE_INLINE bool MustBeLessThan (const Approx &val) const
	{
		return max < val.min;
	}

	GS_FORCE_INLINE bool MustBeLessThan (const double val) const
	{
		return max < val;
	}

	GS_FORCE_INLINE bool MustBeGreaterThan (const Approx &val) const
	{
		return min > val.max;
	}

	GS_FORCE_INLINE bool MustBeGreaterThan (const double val) const
	{
		return val < min;
	}

	GS_FORCE_INLINE bool MustBeLessEqualThan (const double val) const
	{
		return max <= val;
	}

	GS_FORCE_INLINE bool MustBeGreaterEqualThan (const double val) const
	{
		return val <= min;
	}

	enum Sign {
		Positive,
		Negative,
		Unknown
	};

	GS_FORCE_INLINE Sign Sgn () const
	{
		if (max < 0) {
			return Negative;
		} else if (min > 0) {
			return Positive;
		} else {
			return Unknown;
		}
	}

	GS_FORCE_INLINE double GetMin () const
	{
		return min;
	}

	GS_FORCE_INLINE double GetMax () const
	{
		return max;
	}

	GS_FORCE_INLINE double GetMedian () const
	{
		return 0.5 * (min + max);
	}

	GS_FORCE_INLINE Approx Abs () const
	{
		if (max <= 0) {
			return Approx (-max, -min);
		} else if (min >= 0) {
			return *this;
		} else {
			return Approx (0.0L, GS::Max (-min, max));
		}
	}

	GS_FORCE_INLINE double AbsMin () const
	{
		if (max <= 0) {
			return -max;
		} else if (min >= 0) {
			return min;
		} else {
			return 0.0;
		}
	}
};


GS_FORCE_INLINE bool Solve2X2 (Approx (&rhs_x)[2], Approx (&M)[2][2]) //Attention, M gets destroyed! Result is returned in rhs_x
{
	if (M[0][0].CanBeNull() || M[1][1].CanBeNull()) {
		if (M[1][0].CanBeNull() || M[0][1].CanBeNull()) {
			return false;
		}

		//swap rows
		GS::Swap (M[0][0], M[1][0]);
		GS::Swap (M[0][1], M[1][1]);
		GS::Swap (rhs_x[0], rhs_x[1]);
	}

	Approx mul = M[1][0];
	mul /= M[0][0];

	M[1][1] -= M[0][1] * mul;
	if (M[1][1].CanBeNull()) {
		return false;
	}

	rhs_x[1] -= rhs_x[0] * mul;

	//mul = M[0][1] / M[1][1];
	//M[0][1] -= M[1][1] * mul;
	rhs_x[0] -= rhs_x[1] * M[0][1] / M[1][1];

	rhs_x[0] /= M[0][0];
	rhs_x[1] /= M[1][1];

	return true;
}

GS_FORCE_INLINE bool Solve3X3 (Approx (&rhs_x)[3], Approx (&M)[3][3]) //Attention, M gets destroyed! Result is returned in rhs_x
{
	if (M[0][0].CanBeNull ()) {
		if (M[1][0].CanBeNull ()) {
			if (M[2][0].CanBeNull ()) {
				return false;
			}
			//swap row 0,2
			GS::Swap (M[0][0], M[2][0]);
			GS::Swap (M[0][1], M[2][1]);
			GS::Swap (M[0][2], M[2][2]);
			GS::Swap (rhs_x[0], rhs_x[2]);
		}
		else {
			//swap row 0,1:
			GS::Swap (M[0][0], M[1][0]);
			GS::Swap (M[0][1], M[1][1]);
			GS::Swap (M[0][2], M[1][2]);
			GS::Swap (rhs_x[0], rhs_x[1]);
		}
	}

	//eliminate under the diagonal, first column:
	Approx mul = M[1][0] / M[0][0];
	//M[1][0] = 0
	M[1][1] -= M[0][1] * mul;
	M[1][2] -= M[0][2] * mul;
	rhs_x[1] -= rhs_x[0] * mul;

	mul = M[2][0] / M[0][0];
	//M[2][0] = 0
	M[2][1] -= M[0][1] * mul;
	M[2][2] -= M[0][2] * mul;
	rhs_x[2] -= rhs_x[0] * mul;

	if (M[1][1].CanBeNull ()) {
		if (M[2][1].CanBeNull ()) {
			return false;
		}
		//swap rows 1, 2
		//GS::Swap (M[1][0], M[2][0]);
		GS::Swap (M[1][1], M[2][1]);
		GS::Swap (M[1][2], M[2][2]);
		GS::Swap (rhs_x[1], rhs_x[2]);
	}

	//eliminate under the diagonal second column:
	mul = M[2][1] / M[1][1];
	//M[2][1] = 0
	M[2][2] -= M[1][2] * mul;
	if (M[2][2].CanBeNull ()) {
		return false;
	}
	rhs_x[2] -= rhs_x[1] * mul;

	//back elimination (upper triangular!)
	rhs_x[2] /= M[2][2];
	rhs_x[1] -= rhs_x[2] * M[1][2];
	rhs_x[1] /= M[1][1];
	rhs_x[0] -= rhs_x[2] * M[0][2] + rhs_x[1] * M[0][1];
	rhs_x[0] /= M[0][0];

	return true;
}

class ApproxPoint
{
public:
	Approx x, y, z;

private:
	GS_FORCE_INLINE ApproxPoint (const Approx& x, const Approx& y, const Approx& z) : x (x), y (y), z (z) {}

public:
	GS_FORCE_INLINE ApproxPoint () : x (static_cast<Int32>(0), static_cast<Int32>(0)), y (static_cast<Int32>(0), static_cast<Int32>(0)), z (static_cast<Int32>(0), static_cast<Int32>(0))
	{
	}

	template <typename NodeType>
	GS_FORCE_INLINE ApproxPoint (const NodeType* node) : x (node->bb.xmin, node->bb.xmax), y (node->bb.ymin, node->bb.ymax), z (node->bb.zmin, node->bb.zmax)
	{
	}

	GS_FORCE_INLINE ApproxPoint operator + (const ApproxPoint& rhs) const
	{
		return ApproxPoint (x + rhs.x, y + rhs.y, z + rhs.z);
	}

	GS_FORCE_INLINE ApproxPoint operator - (const ApproxPoint& rhs) const
	{
		return ApproxPoint (x - rhs.x, y - rhs.y, z - rhs.z);
	}

	GS_FORCE_INLINE ApproxPoint operator- () const
	{
		return ApproxPoint (-x, -y, -z);
	}

	GS_FORCE_INLINE Approx operator * (const ApproxPoint& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	GS_FORCE_INLINE ApproxPoint operator ^ (const ApproxPoint& rhs) const
	{
		return ApproxPoint (y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
	}

	GS_FORCE_INLINE ApproxPoint& operator *= (const Approx& scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	GS_FORCE_INLINE ApproxPoint operator * (const Approx& scalar) const
	{
		return ApproxPoint (x * scalar, y * scalar, z * scalar);
	}

	GS_FORCE_INLINE bool CanBeNull () const
	{
		return x.CanBeNull () && y.CanBeNull () && z.CanBeNull ();
	}

	GS_FORCE_INLINE bool CanBeEqual (const ApproxPoint & p) const
	{
		return x.CanBeEqual (p.x) && y.CanBeEqual (p.y) && z.CanBeEqual (p.z);
	}

	GS_FORCE_INLINE Approx& operator [] (UInt32 i)
	{
		DBASSERT (i < 3);
#if ! (defined(lint) || defined(_lint))
		static_assert (offsetof (ApproxPoint, y) - offsetof (ApproxPoint, x) == sizeof (Approx) && offsetof (ApproxPoint, z) - offsetof (ApproxPoint, x) == 2 * sizeof (Approx), "offset");
#endif
		return (&x)[i];
	}

	GS_FORCE_INLINE const Approx& operator [] (UInt32 i) const
	{
		DBASSERT (i < 3);
#if ! (defined(lint) || defined(_lint))
		static_assert (offsetof (ApproxPoint, y) - offsetof (ApproxPoint, x) == sizeof (Approx) && offsetof (ApproxPoint, z) - offsetof (ApproxPoint, x) == 2 * sizeof (Approx), "offset");
#endif
		return (&x)[i];
	}
};

class ApproxPoint2D
{
public:
	Approx x, y;

	GS_FORCE_INLINE ApproxPoint2D (const Approx& x, const Approx& y) : x (x), y (y) {}

	GS_FORCE_INLINE ApproxPoint2D () : x (static_cast<Int32>(0), static_cast<Int32>(0)), y (static_cast<Int32>(0), static_cast<Int32>(0))
	{
	}

	template <typename NodeType>
	GS_FORCE_INLINE ApproxPoint2D (const NodeType* node, Int32 crd1, Int32 crd2)
	{
		switch (crd1) {
		case 0: x = Approx(node->bb.xmin, node->bb.xmax);
			break;
		case 1: x = Approx(node->bb.ymin, node->bb.ymax);
			break;
		case 2: x = Approx(node->bb.zmin, node->bb.zmax);
			break;
		}

		switch (crd2) {
		case 0: y = Approx(node->bb.xmin, node->bb.xmax);
			break;
		case 1: y = Approx(node->bb.ymin, node->bb.ymax);
			break;
		case 2: y = Approx(node->bb.zmin, node->bb.zmax);
			break;
		}
	}

	GS_FORCE_INLINE ApproxPoint2D (const ApproxPoint& point, Int32 crd)
	{
		switch (crd) {
		case 0:
			x = point.y;
			y = point.z;
			break;
		case 1:
			x = point.z;
			y = point.x;
			break;
		case 2:
			x = point.x;
			y = point.y;
			break;
#if defined (DEBUVERS)
		default:
			DBBREAK ();
			break;
#endif
		}
	}

	template <typename Node2DType>
	GS_FORCE_INLINE ApproxPoint2D (const Node2DType* node) :
		x (node->bb.xmin, node->bb.xmax), y (node->bb.ymin, node->bb.ymax)
	{
	}

	GS_FORCE_INLINE ApproxPoint2D operator + (const ApproxPoint2D& rhs) const
	{
		return ApproxPoint2D (x + rhs.x, y + rhs.y);
	}

	GS_FORCE_INLINE ApproxPoint2D operator - (const ApproxPoint2D& rhs) const
	{
		return ApproxPoint2D (x - rhs.x, y - rhs.y);
	}

	GS_FORCE_INLINE ApproxPoint2D operator- () const
	{
		return ApproxPoint2D (-x, -y);
	}

	GS_FORCE_INLINE Approx operator * (const ApproxPoint2D& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	GS_FORCE_INLINE Approx operator ^ (const ApproxPoint2D& rhs) const	//cross product result is in the third dimension!
	{
		return x * rhs.y - y * rhs.x;
	}

	GS_FORCE_INLINE ApproxPoint2D& operator *= (const Approx& scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	GS_FORCE_INLINE ApproxPoint2D operator * (const Approx& scalar) const
	{
		return ApproxPoint2D (x * scalar, y * scalar);
	}

	GS_FORCE_INLINE bool CanBeNull () const
	{
		return x.CanBeNull () && y.CanBeNull ();
	}

	GS_FORCE_INLINE bool CanBeEqual (const ApproxPoint2D & p) const
	{
		return x.CanBeEqual (p.x) && y.CanBeEqual (p.y);
	}

	GS_FORCE_INLINE Approx& operator [] (UInt32 i)
	{
		DBASSERT (i < 2);
#if ! (defined(lint) || defined(_lint))
		static_assert (offsetof (ApproxPoint2D, y) - offsetof (ApproxPoint2D, x) == sizeof (Approx), "offset");
#endif
		return (&x)[i];
	}

	GS_FORCE_INLINE const Approx& operator [] (UInt32 i) const
	{
		DBASSERT (i < 2);
#if ! (defined(lint) || defined(_lint))
		static_assert (offsetof (ApproxPoint2D, y) - offsetof (ApproxPoint2D, x) == sizeof (Approx), "offset");
#endif
		return (&x)[i];
	}
};

} // namespace QXTools

#endif
