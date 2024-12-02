// *****************************************************************************
// 2D Point. Wrapper class for Point functionality.
// The eps value is either global or per operation. No eps per instance.
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          FGY
//
// SG compatible
// *****************************************************************************
#if !defined (GS_POINT2D_HPP)
#define GS_POINT2D_HPP
#pragma once

#include <iterator>

// from GSRoot
#include "DoubleClassification.hpp"
#include "BaseAlgorithms.hpp"
#include "HashCommon.hpp"
#include "ObjectState.hpp"

// from Geometry
#include "CoordTypedef.hpp"
#include "Real.hpp"
#include "Length.hpp"
#include "Point2Predeclaration.hpp"
#include "Vector2D.hpp"

struct Point2dData { // use for unions
	double x;
	double y;
};

namespace Geometry {


template<typename Coordinate>
class Point2 {
public:
	Coordinate	x;
	Coordinate	y;

public:
	Point2 ();

	template<typename Point2LikeType> explicit Point2 (const Point2LikeType& src) : x(src.x), y(src.y) {}
	Point2 (const Coordinate& x, const Coordinate& y);
	explicit Point2 (const Point2dData& src);
	operator Point2dData () const;

	Coordinate GetX (void) const;
	Coordinate GetY (void) const;
	void GetCoords (Coordinate* x, Coordinate* y) const;
	void Set (Coordinate x, Coordinate y);

	Length GetDistFromOrigo (void) const;
	Coordinate GetDistFromOrigoSqr (void) const;

	Point2	operator+ (const Vector2<Coordinate>&) const;
	Point2	operator- (const Vector2<Coordinate>&) const;
	Vector2<Coordinate>	operator- (const Point2<Coordinate>&) const;

	Point2& operator+= (const Vector2<Coordinate>& other);
	Point2& operator-= (const Vector2<Coordinate>& other);

	bool	IsNear (const Point2& p) const;
	bool	IsNear (const Point2& p, double eps) const;
	bool	operator== (const Point2&) const;
	bool	operator!= (const Point2&) const;

	GSErrCode	Read	(GS::IChannel& ic);
	GSErrCode	Write	(GS::OChannel& oc) const;

	GSErrCode	Store	(GS::ObjectState& os) const;
	GSErrCode	Restore (const GS::ObjectState& os);

	GSErrCode ReadXML	(GS::XMLIChannel& ic, const char* attrName = nullptr);
	GSErrCode WriteXML	(GS::XMLOChannel& oc, const char* attrName = nullptr) const;

	GS_FORCE_INLINE Coordinate& operator [] (UInt32 i)
	{
		DBASSERT (i < 3);
#if ! (defined(lint) || defined(_lint))
		static_assert (offsetof (Point2<Coordinate>, y) - offsetof (Point2<Coordinate>, x) == sizeof (Coordinate), "offset");
#endif
		return (&x)[i];
	}

	GS_FORCE_INLINE const Coordinate& operator [] (UInt32 i) const
	{
		DBASSERT (i < 3);
#if ! (defined(lint) || defined(_lint))
		static_assert (offsetof (Point2<Coordinate>, y) - offsetof (Point2<Coordinate>, x) == sizeof (Coordinate), "offset");
#endif
		return (&x)[i];
	}

};

// *****************************************************************************
// ORIGO2: Special Point2 class for conversion between Point2 and Vector2
// *****************************************************************************
constexpr class Origo2 {} ORIGO2;

template<typename Coordinate>
Point2<Coordinate> operator+ (const Origo2&, const Vector2<Coordinate>& v) { return Point2<Coordinate> (v.x, v.y); }
template<typename Coordinate>
Point2<Coordinate> operator- (const Origo2&, const Vector2<Coordinate>& v) { return Point2<Coordinate> (-v.x, -v.y); }

template<typename Coordinate>
Vector2<Coordinate> operator- (const Point2<Coordinate>& p, const Origo2&) { return Vector2<Coordinate> (p.x, p.y); }

// *****************************************************************************
// Predefined types
// *****************************************************************************
typedef Point2<double>	Point2d;
typedef Point2<float>	Point2f;


template<typename Coordinate>
bool	IsNear			(const Point2<Coordinate>& p1, const Point2<Coordinate>& p2);

template<typename Coordinate>
bool	IsNearOrigo		(const Point2<Coordinate>& r);

template<typename Coordinate>
bool	IsNear			(const Point2<Coordinate>& p1, const Point2<Coordinate>& p2, double givenEps);

template<typename Coordinate>
bool	IsNearOrigo		(const Point2<Coordinate>& p, double givenEps);

template<typename Coordinate>
Point2<Coordinate>	MidPoint (const Point2<Coordinate>& p1, const Point2<Coordinate>& p2);

template<typename Coordinate>
Point2<Coordinate>	Discretize (const Point2<Coordinate>& p);

template<typename Coordinate>
Point2<Coordinate>	Discretize (const Point2<Coordinate>& p, double givenEps);


template <typename InputIterator>
typename std::iterator_traits<InputIterator>::value_type GetCenterPoint (InputIterator first, InputIterator last);

template<typename Coordinate>
Point2<Coordinate>	LinearCombination (Coordinate coeff1, const Point2<Coordinate>& p1, Coordinate coeff2, const Point2<Coordinate>& p2);

template<typename Coordinate>
GSErrCode Point2<Coordinate>::ReadXML	(GS::XMLIChannel& ic, const char* attrName /* = nullptr */)
{
	GSErrCode errCode = NoError;

	if (errCode == NoError)
		errCode = ic.ReadStartElement (attrName == nullptr ? "Vertex" : attrName);
	if (errCode == NoError)
		errCode = ic.ReadXML ("X", x);
	if (errCode == NoError)
		errCode = ic.ReadXML ("Y", y);
	if (errCode == NoError)
		errCode = ic.ReadEndElement (attrName == nullptr ? "Vertex" : attrName);

	return errCode;
}

template<typename Coordinate>
GSErrCode Point2<Coordinate>::WriteXML	(GS::XMLOChannel& oc, const char* attrName /* = nullptr */) const
{
	GSErrCode errCode = NoError;

	if (errCode == NoError)
		errCode = oc.WriteStartElement (attrName == nullptr ? "Vertex" : attrName);
	if (errCode == NoError)
		errCode = oc.WriteXML ("X", x);
	if (errCode == NoError)
		errCode = oc.WriteXML ("Y", y);
	if (errCode == NoError)
		errCode = oc.WriteEndElement ();

	return errCode;
}


template<typename Coordinate>
inline Point2<Coordinate>::Point2 (void)
: x (0.0), y (0.0)
{}


template<typename Coordinate>
inline Point2<Coordinate>::Point2 (const Coordinate& x, const Coordinate& y)
	: x (x), y (y)
{}


template<typename Coordinate>
inline Point2<Coordinate>::Point2 (const Point2dData& src)
: x(src.x), y(src.y)
{}


template<typename Coordinate>
inline Point2<Coordinate>::operator Point2dData () const
{
	Point2dData v;
	v.x = x;
	v.y = y;

	return v;
}


template<typename Coordinate>
inline Coordinate Point2<Coordinate>::GetX (void) const
{
	return x;
}


template<typename Coordinate>
inline Coordinate Point2<Coordinate>::GetY (void) const
{
	return y;
}


template<typename Coordinate>
inline void Point2<Coordinate>::GetCoords (Coordinate* x, Coordinate* y) const
{
	DBASSERT (x != nullptr && y != nullptr);
	*x = this->x;
	*y = this->y;
}


template<typename Coordinate>
inline void Point2<Coordinate>::Set (Coordinate x, Coordinate y)
{
	this->x = x;
	this->y = y;
}


template<typename Coordinate>
inline Coordinate Point2<Coordinate>::GetDistFromOrigoSqr (void) const
{
	return x * x + y * y;
}


template<typename Coordinate>
inline Length Point2<Coordinate>::GetDistFromOrigo (void) const
{
	return Length (Sqrt (x * x + y * y));
}


template<typename Coordinate>
inline Point2<Coordinate>& Point2<Coordinate>::operator+= (const Vector2<Coordinate>& other)
{
	x += other.x;
	y += other.y;

	return *this;
}


template<typename Coordinate>
inline Point2<Coordinate>& Point2<Coordinate>::operator-= (const Vector2<Coordinate>& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}


template<typename Coordinate>
bool Geometry::Point2<Coordinate>::IsNear(const Point2& p, double eps) const
{
	return Geometry::IsNear (*this, p, eps);
}


template<typename Coordinate>
bool Geometry::Point2<Coordinate>::IsNear(const Point2& p) const
{
	return Geometry::IsNear (*this, p, GetEps<Coordinate>());
}


template<typename Coordinate>
inline bool	Point2<Coordinate>::operator== (const Point2& p) const
{
	return x == p.x && y == p.y;
}


template<typename Coordinate>
inline bool	Point2<Coordinate>::operator!= (const Point2& p) const
{
	return x != p.x || y != p.y;
}


template<typename Coordinate>
inline Point2<Coordinate> Point2<Coordinate>::operator+ (const Vector2<Coordinate>& p2) const
{
	Point2<Coordinate> ret (x, y);
	ret +=p2;

	return ret;
}


template<typename Coordinate>
Vector2<Coordinate> Point2<Coordinate>::operator- (const Point2<Coordinate>& p2) const
{
	Vector2<Coordinate> ret (x - p2.x, y - p2.y);
	return ret;
}


template<typename Coordinate>
Point2<Coordinate> Point2<Coordinate>::operator- (const Vector2<Coordinate>& v2) const
{
	Point2<Coordinate> ret (x, y);
	ret -= v2;

	return ret;
}


template<typename Coordinate>
inline bool	IsNear (const Point2<Coordinate>& v1, const Point2<Coordinate>& v2)
{
	return IsNear (v1, v2, GetEps<Coordinate> ());
}


template<typename Coordinate>
inline bool	IsNearZero (const Point2<Coordinate>& v)
{
	return IsNearZero (v, GetEps<Coordinate> ());
}


template<typename Coordinate>
inline bool	IsNear (const Point2<Coordinate>& p1, const Point2<Coordinate>& p2, double givenEps)
{
	return IsNear (Vector2<Coordinate> (p1.x, p1.y), Vector2<Coordinate> (p2.x, p2.y), givenEps);
}


template<typename Coordinate>
inline bool	IsNearOrigo (const Point2<Coordinate>& v, double givenEps)
{
	return IsNearZero (Vector2<Coordinate> (v.x, v.y), givenEps);
}



template<typename Coordinate>
inline Point2<Coordinate>	MidPoint (const Point2<Coordinate>& p1, const Point2<Coordinate>& p2)
{
	return Point2<Coordinate> ((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
}


template<typename Coordinate>
inline Point2<Coordinate>	Discretize (const Point2<Coordinate>& p)
{
	return Point2<Coordinate> (Geometry::Discretize (p.x), Geometry::Discretize (p.y));
}


template<typename Coordinate>
inline Point2<Coordinate>	Discretize (const Point2<Coordinate>& p, double givenEps)
{
	return Point2<Coordinate> (Geometry::Discretize (p.x, givenEps), Geometry::Discretize (p.y, givenEps));
}


template <typename InputIterator>
typename std::iterator_traits<InputIterator>::value_type GetCenterPoint (InputIterator first, InputIterator last)
{
	typename std::iterator_traits<InputIterator>::value_type centerPt;
	ULong count = 0;
	for (; first != last; ++first) {
		centerPt.x += first->x;
		centerPt.y += first->y;
		++count;
	}
	if (count > 0) {
		centerPt.x = centerPt.x / count;
		centerPt.y = centerPt.y / count;
	}
	return centerPt;
}


template<typename Coordinate>
Point2<Coordinate>	LinearCombination (Coordinate coeff1, const Point2<Coordinate>& p1, Coordinate coeff2, const Point2<Coordinate>& p2)
{
//	DBASSERT (GS::Abs (coeff1 + coeff2 - 1.0) < EPS); - this would be a requirement only if it was convex combination
	return Point2<Coordinate> (coeff1 * p1.x + coeff2 * p2.x, coeff1 * p1.y + coeff2 * p2.y);
}


template<typename Coordinate>
GSErrCode Point2<Coordinate>::Read (GS::IChannel& ic)
{
	GSErrCode err = ic.Read (x);
	if (err == NoError)
		err = ic.Read (y);

	return err;
}


template<typename Coordinate>
GSErrCode Point2<Coordinate>::Write (GS::OChannel& oc) const
{
	GSErrCode err = oc.Write (x);
	if (err == NoError)
		err = oc.Write (y);

	return err;
}


template<typename Coordinate>
GSErrCode Point2<Coordinate>::Store (GS::ObjectState& os) const
{
	os.Add ("x", x);
	os.Add ("y", y);

	return NoError;
}


template<typename Coordinate>
GSErrCode  Point2<Coordinate>::Restore (const GS::ObjectState& os)
{
	Coordinate x = Coordinate ();
	Coordinate y = Coordinate ();

	if (!os.Get ("x", x) || !os.Get ("y", y))
		return Error;

	Set (x, y);

	return NoError;
}


}	// namespace Geometry

namespace Geometry {

	inline double MaxCoordValue (void) {

		return 8e8;		//	az egyenlito hosszanak 20-szorosa
	}

	inline double CorrigateDouble (const double d, const double maxValue, bool correctToUp = true)
	{
		bool nan = GS::IsDoubleClassNaN (d);
		DBASSERT (!nan);
		if (!GS::CheckDouble (d, maxValue)) {
			if ((!nan || correctToUp) && d >= 0) {
				return maxValue;
			}
			return - maxValue;
		}
		return d;
	}

	inline bool CheckCoord (const Point2D& coord, const double maxValue)
	{
		return	GS::CheckDouble (coord.x, maxValue) && GS::CheckDouble (coord.y, maxValue);
	}

	class GEOMETRY_DLL_EXPORT HashableCoord : public Point2D {
	public:
		HashableCoord ();
		HashableCoord (const Point2D& coord);
		virtual ~HashableCoord ();

		ULong GenerateHashValue () const;
	};

}

#endif
