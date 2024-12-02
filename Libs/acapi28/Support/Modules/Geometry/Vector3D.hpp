// *********************************************************************************************************************
// Description:		Point3D, Vector3D template based definitions
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	FGY
//
// *********************************************************************************************************************

#if !defined (GS_VECTOR3D_HPP)
#define GS_VECTOR3D_HPP

#include "Length.hpp"
#include "Point2D.hpp"
#include "Real.hpp"
#include "Vector2D.hpp"

// from GSRoot
#include "Channel.hpp"
#include "GSDebug.hpp"
#include "XMLChannel.hpp"

// from Standard Library
#include <cstddef>


struct Vector3dData { // use for unions
	double x;
	double y;
	double z;
};

namespace Geometry {

template<typename Coordinate>
class Vector3 {
public:
	Coordinate	x;
	Coordinate	y;
	Coordinate	z;

public:
	constexpr	Vector3 ();

	template<typename Number2>
	constexpr Vector3 (const Vector3<Number2>& src) : x(src.x), y(src.y), z(src.z) {}
	constexpr	Vector3 (const Coordinate& x, const Coordinate& y, const Coordinate& z);
	inline	Vector3 (const Vector2<Coordinate>, const Coordinate& z);
		 // Strictly temporary while there is no distinct Point3d class
	template<typename Type2> Vector3 (const Type2& src, const Coordinate& z) : x(src.x), y(src.y) ,z(z) {}
	inline	Vector3 (const Vector3dData& src);
	inline	operator Vector3dData () const;

	template<typename Number2> Vector3& operator= (const Vector3<Number2>& src) { x = src.x; y = src.y; z = src.z; return *this; }

	inline	void GetCoords (Coordinate* x, Coordinate* y, Coordinate* z) const;
	inline	void Set (Coordinate x, Coordinate y, Coordinate z);

	inline	Length		GetLength (void) const;
	inline	Coordinate	GetLengthSqr (void) const;
	inline	double		CalcAngleToReference (const Vector3 <Coordinate> & refVector) const;		//returns angle from 0 to PI; the smallest possible angle between reference and the vector
	inline	bool		IsUnitVector (double givenEps) const;
	inline	bool		IsNullVector (double givenEps) const;
	inline	Vector3		GetUnitVector (void) const;
	inline	void		NormalizeVector (void);

	inline	Vector3		operator- () const;
	inline	Vector3		operator+ (const Vector3&) const;
	inline	Vector3		operator- (const Vector3&) const;

	inline	Coordinate	operator* (const Vector3&) const;			// dot product (skalar szorzas)
	inline	Vector3		operator^ (const Vector3&) const;			// cross product (vektorialis szorzas), !! has low precedence !!

	inline	Vector3		operator* (const Coordinate&) const;
	inline	Vector3		operator/ (const Coordinate&) const;

	inline	const Vector3&	operator+= (const Vector3&);
	inline	const Vector3&	operator-= (const Vector3&);
	inline	const Vector3&	operator*= (const Coordinate&);
	inline	const Vector3&	operator/= (const Coordinate&);

	inline	bool	IsNear (const Vector3&, double = SmallEps) const;
	inline	bool	operator== (const Vector3&) const;
	inline	bool	operator!= (const Vector3&) const;

	GSErrCode Read	(GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	GSErrCode ReadXML	(GS::XMLIChannel& ic, const char* tagName = nullptr);
	GSErrCode WriteXML (GS::XMLOChannel& oc, const char* tagName = nullptr) const;

	GS_FORCE_INLINE Coordinate& operator [] (UInt32 i)
	{
		DBASSERT (i < 3);
#if (defined (_MSC_VER) || defined (_LIBCPP_VERSION)) && !(defined(lint) || defined(_lint))
		static_assert (offsetof (Vector3<Coordinate>, y) - offsetof (Vector3<Coordinate>, x) == sizeof (Coordinate) && offsetof (Vector3<Coordinate>, z) - offsetof (Vector3<Coordinate>, x) == 2 * sizeof (Coordinate), "offset");
#endif
		return (&x)[i];
	}

	GS_FORCE_INLINE const Coordinate& operator [] (UInt32 i) const
	{
		DBASSERT (i < 3);
#if (defined (_MSC_VER) || defined (_LIBCPP_VERSION)) && !(defined(lint) || defined(_lint))
		static_assert (offsetof (Vector3<Coordinate>, y) - offsetof (Vector3<Coordinate>, x) == sizeof (Coordinate) && offsetof (Vector3<Coordinate>, z) - offsetof (Vector3<Coordinate>, x) == 2 * sizeof (Coordinate), "offset");
#endif
		return (&x)[i];
	}

};
template<typename Coordinate>
Vector3<Coordinate> operator* (const Coordinate&, const Vector3<Coordinate>&);

typedef Vector3<double>		Coord3D, Vector3D, Vector3d, COORD3, Point3D;  // Use Point3D, Vector3D for new code!
typedef Vector3<float>		F_Coord3D;


template<typename Coordinate>
bool	IsNearZero (const Vector3<Coordinate>& r);

template<typename Coordinate>
bool	IsNearZero (const Vector3<Coordinate>& v, double givenEps);


template<typename Coordinate>
constexpr Vector3<Coordinate>::Vector3 ()
: x(), y(), z()
{}


template<typename Coordinate>
constexpr Vector3<Coordinate>::Vector3 (const Coordinate& x, const Coordinate& y, const Coordinate& z)
: x(x), y(y), z(z)
{}


template<typename Coordinate>
Vector3<Coordinate>::Vector3 (const Vector2<Coordinate> v, const Coordinate& z)
: x(v.x), y(v.y), z(z)
{}

template<typename Coordinate>
Vector3<Coordinate>::Vector3 (const Vector3dData& src)
	: x(src.x), y(src.y), z(src.z)
	{}


template<typename Coordinate>
Vector3<Coordinate>::operator Vector3dData () const
{
	Vector3dData v;
	v.x = x;
	v.y = y;
	v.z = z;

	return v;
}


template<typename Coordinate>
void Vector3<Coordinate>::GetCoords (Coordinate* x, Coordinate* y, Coordinate* z) const
{
	DBASSERT (x != nullptr && y != nullptr && z != nullptr);
	*x = this->x;
	*y = this->y;
	*z = this->z;
}


template<typename Coordinate>
void Vector3<Coordinate>::Set (Coordinate x, Coordinate y, Coordinate z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


template<typename Coordinate>
Coordinate Vector3<Coordinate>::GetLengthSqr (void) const
{
	return x * x + y * y + z * z;
}

inline void RotXY (const double rt_diag, const double rt_offDiag, double &x, double &y, double &/*z*/)
{
	const double norm = sqrt (rt_diag * rt_diag + rt_offDiag * rt_offDiag);
	if (norm > 1E-10) {
		double resx =	( rt_diag * x		+ rt_offDiag * y)	/ norm;
		y =				(-rt_offDiag * x	+ rt_diag * y)		/ norm;
		x = resx;
	}
}

inline void RotYZ (const double rt_diag, const double rt_offDiag, double &/*x*/, double &y, double &z)
{
	const double norm = sqrt (rt_diag * rt_diag + rt_offDiag * rt_offDiag);
	if (norm > 1E-10) {
		double resy =	( rt_diag * y		+ rt_offDiag * z)	/ norm;
		z =				(-rt_offDiag * y	+ rt_diag * z)		/ norm;
		y = resy;
	}
}

template<typename Coordinate>
double Vector3<Coordinate>::CalcAngleToReference (const Vector3 <Coordinate> & refVector) const //returns angle from 0 to PI; the smallest possible angle between reference and the vector
{
#define  PI_over_2 (atan2 (1.0, 0.0))
	//Alg:
	//1. refVector = Rot_yz (refVector) so that no more Z component, do same Rot on this vector as well
	//2. refVector = Rot_xy (refVector) so that no more Y component, do same Rot on this vector as well
	//3. this = Rot_yz (this) so that there is no more Z component and only positive Y(!), refVector needs not to be rotated, it has only X component!
	double rx = refVector.x;
	double ry = refVector.y;
	double rz = refVector.z;

	double tx = x;
	double ty = y;
	double tz = z;
	//1
	RotYZ (ry, rz,   tx, ty, tz);
	RotYZ (ry, rz,   rx, ry, rz);

	//2
	RotXY (rx, ry,   tx, ty, tz);
	RotXY (rx, ry,   rx, ry, rz);

	DBASSERT ( fabs (ry) < EPS);
	DBASSERT ( fabs (rz) < EPS);

	//3
	RotYZ (ty, tz,   tx, ty, tz);
	DBASSERT ( fabs (tz) < EPS);
	ty = fabs (ty);					//additional 180 rotation!

	double a = atan2 (ty, tx);
	if (a < 0.0) {
		DBBREAK_STR ("Unexpected: a should have already been positiv");
		a += 4.0 * PI_over_2;
	}

	return a;

#undef PI_over_2
}


template<typename Coordinate>
Length Vector3<Coordinate>::GetLength (void) const
{
	return Length (Sqrt (x * x + y * y + z * z));
}


template<typename Coordinate>
bool Vector3<Coordinate>::IsUnitVector (double givenEps) const
{
	return (GetLength ().IsNear (Length (1.0), givenEps));
}


template<typename Coordinate>
bool Vector3<Coordinate>::IsNullVector (double givenEps) const
{
	return (GetLength ().IsNear (Length (0.0), givenEps));
}


template<typename Coordinate>
Vector3<Coordinate> Vector3<Coordinate>::GetUnitVector (void) const
{
	Length		l;

	l = this->GetLength ();
	if (l.IsPositive (SmallEps)) {
		return Vector3 <Coordinate> (x / l, y / l, z / l);
	} else {
		DBTRACE ("ERROR -> UnitVector divided by zero!");
		return Vector3 <Coordinate> (1.0, 0.0, 0.0);
	}
}

template<typename Coordinate>
void Vector3<Coordinate>::NormalizeVector (void)
{
	Length		l;

	l = this->GetLength ();
	if (l.IsPositive (SmallEps)) {
		Set (x / l, y / l, z / l);
	} else {
		DBTRACE ("ERROR -> NormVector divided by zero!");
		Set (1.0, 0.0, 0.0);
	}
}

template<typename Coordinate>
Vector3<Coordinate> Vector3<Coordinate>::operator- () const
{
	return Vector3 (-x, -y, -z);
}

template<typename Coordinate>
Vector3<Coordinate> Vector3<Coordinate>::operator+ (const Vector3& c) const
{
	return Vector3 (x + c.x, y + c.y, z + c.z);
}

template<typename Coordinate>
Vector3<Coordinate> Vector3<Coordinate>::operator- (const Vector3& c) const
{
	return Vector3 (x - c.x, y - c.y, z - c.z);
}

template<typename Coordinate>
Coordinate Vector3<Coordinate>::operator* (const Vector3& c) const		// dot product (skalar szorzas)
{
	return x * c.x + y * c.y + z * c.z;
}

template<typename Coordinate>
Vector3<Coordinate> Vector3<Coordinate>::operator^ (const Vector3& c) const	// cross product (vektorialis szorzas), !! has low precedence !!
{
	return Vector3 (y * c.z - z * c.y, z * c.x - x * c.z, x * c.y - y * c.x);
}

template<typename Coordinate>
Vector3<Coordinate> Vector3<Coordinate>::operator* (const Coordinate& k) const
{
	return Vector3 (x * k, y * k, z * k);
}

template<typename Coordinate>
Vector3<Coordinate> Vector3<Coordinate>::operator/ (const Coordinate& k) const
{
	return Vector3 { x / k, y / k, z / k };
}


template<typename Coordinate>
const Vector3<Coordinate>& Vector3<Coordinate>::operator+= (const Vector3& c)
{
	x += c.x;
	y += c.y;
	z += c.z;

	return *this;
}

template<typename Coordinate>
const Vector3<Coordinate>& Vector3<Coordinate>::operator-= (const Vector3& c)
{
	x -= c.x;
	y -= c.y;
	z -= c.z;

	return *this;
}

template<typename Coordinate>
const Vector3<Coordinate>& Vector3<Coordinate>::operator*= (const Coordinate& k)
{
	x *= k;
	y *= k;
	z *= k;

	return *this;
}

template<typename Coordinate>
const Vector3<Coordinate>& Vector3<Coordinate>::operator/= (const Coordinate& k)
{
	x /= k;
	y /= k;
	z /= k;

	return *this;
}

template<typename Coordinate>
bool Geometry::Vector3<Coordinate>::IsNear (const Vector3& c, double eps /*= SmallEps*/) const
{
	return (*this - c).GetLengthSqr () < eps * eps;
}

template<typename Coordinate>
bool Vector3<Coordinate>::operator== (const Vector3& c) const
{
	return x == c.x && y == c.y && z == c.z;
}

template<typename Coordinate>
bool Vector3<Coordinate>::operator!= (const Vector3& c) const
{
	return x != c.x || y != c.y || z != c.z;
}

template<typename Coordinate>
inline Vector3<Coordinate> operator* (const Coordinate& k, const Vector3<Coordinate>& c)
{
	return Vector3<Coordinate> (k * c.x, k * c.y, k * c.z);
}

template<typename Coordinate>
void Set (Vector3<Coordinate>& vect3d, const Coordinate& x, const Coordinate& y, const Coordinate& z)
{
	vect3d.x = x;
	vect3d.y = y;
	vect3d.z = z;
}

template<typename Coordinate>
inline bool	IsNearZero (const Vector3<Coordinate>& v)
{
	return IsNearZero (v, GetEps<Coordinate> ());
}

template<typename Coordinate>
inline bool	IsNearZero (const Vector3<Coordinate>& v, double givenEps)
{
	bool isNearZero = false;
	Coordinate distx = v.x;
	if (IsNearZero (distx, givenEps)) {
		Coordinate disty = v.y;
		if (IsNearZero (disty, givenEps)) {
			Coordinate distz = v.z;
			if (IsNearZero (distz, givenEps)) {
				Coordinate cubicDist = distx * distx + disty * disty + distz * distz;
				Coordinate cubicEps = givenEps * givenEps;
				if (IsNearZero (cubicDist, cubicEps)) {
					isNearZero = true;
				}
			}
		}
	}
	return isNearZero;
}

template<typename Coordinate>
GSErrCode Vector3<Coordinate>::Read (GS::IChannel& ic)
{
	return ic.Read (x, y, z);
}

template<typename Coordinate>
GSErrCode Vector3<Coordinate>::Write (GS::OChannel& oc) const
{
	return oc.Write (x, y, z);
}


template<typename Coordinate>
GSErrCode Store (GS::ObjectState& os, const Vector3<Coordinate>& v)
{
	Coordinate x = Coordinate ();
	Coordinate y = Coordinate ();
	Coordinate z = Coordinate ();

	v.GetCoords (&x, &y, &z);

	os.Add ("x", x);
	os.Add ("y", y);
	os.Add ("z", z);

	return NoError;
}

template<typename Coordinate>
GSErrCode Restore (const GS::ObjectState& os, Vector3<Coordinate>& v)
{
	Coordinate x = Coordinate ();
	Coordinate y = Coordinate ();
	Coordinate z = Coordinate ();

	if (!os.Get ("x", x) || !os.Get ("y", y) || !os.Get ("z", z))
		return Error;

	v.Set (x, y, z);

	return NoError;
}

template<typename Coordinate>
GSErrCode  Vector3<Coordinate>::ReadXML	(GS::XMLIChannel& ic, const char* tagName)
{
	GSErrCode errCode = NoError;
	GS::XMLITag tag (ic, tagName == nullptr ? "Vertex3D" : tagName);
	{
		if (errCode == NoError)
			errCode = ic.ReadXML ("X", x);
		if (errCode == NoError)
			errCode = ic.ReadXML ("Y", y);
		if (errCode == NoError)
			errCode = ic.ReadXML ("Z", z);
	}

	return errCode;
}



template<typename Coordinate>
GSErrCode  Vector3<Coordinate>::WriteXML (GS::XMLOChannel& oc, const char* tagName) const
{
	GSErrCode errCode = NoError;
	GS::XMLTag tag (oc, tagName == nullptr ? "Vertex3D" : tagName);
	{
		if (errCode == NoError)
			errCode = oc.WriteXML ("X", x);
		if (errCode == NoError)
			errCode = oc.WriteXML ("Y", y);
		if (errCode == NoError)
			errCode = oc.WriteXML ("Z", z);
	}

	return errCode;
}

//Checker functions

inline bool CheckCoord3D (const Point3D& coord, const double maxXY, const double maxZ)
{
	return GS::CheckDouble (coord.x, maxXY) && GS::CheckDouble (coord.y, maxXY) && GS::CheckDouble (coord.z, maxZ);
}

}	// namespace Geometry

using Geometry::Coord3D;
using Geometry::Point3D;
using Geometry::Vector3D;
using Geometry::Vector3d;
using Geometry::COORD3;
using Geometry::F_Coord3D;


#endif
