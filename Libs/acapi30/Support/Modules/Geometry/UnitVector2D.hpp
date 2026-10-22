#ifndef _UNITVECTOR_2D_HPP
#define _UNITVECTOR_2D_HPP
#pragma once

#include "UnitVector2DClassDeclaration.hpp"


namespace Geometry {

template<class CoordinateType>
CustomUnitVector2D<CoordinateType> CustomUnitVector2D<CoordinateType>::Create (CoordinateType x, CoordinateType y, const DistanceTolerance& nullVectorLengthLimit /*= SmallEps*/)
{
	return Create (Vector2<CoordinateType> (x, y), nullVectorLengthLimit);
}

template<class CoordinateType>
CustomUnitVector2D<CoordinateType> CustomUnitVector2D<CoordinateType>::Create (const Vector2<CoordinateType>& v, const DistanceTolerance& nullVectorLengthLimit /*= SmallEps*/)
{
	const GS::Optional<CustomUnitVector2D<CoordinateType>> u = ConvertToUnitVector<CoordinateType> (v, nullVectorLengthLimit);
	if (u.HasValue ()) {
		return u.Get ();
	} else {
		throw UnitVectorCreationError ();
	}
}

template<class CoordinateType>
Vector2<CoordinateType> CustomUnitVector2D<CoordinateType>::ToVector2D () const
{
	return Vector2<CoordinateType> (x, y);
}

template<class CoordinateType>
CustomUnitVector2D<CoordinateType>::operator Vector2<CoordinateType> () const
{
	return ToVector2D ();
}

template<class CoordinateType>
bool CustomUnitVector2D<CoordinateType>::IsParallelWith (const CustomUnitVector2D& other, const AngleTolerance& tol) const
{
	return fabs (x * other.y - y * other.x) < tol;
}

template<class CoordinateType>
bool CustomUnitVector2D<CoordinateType>::IsEqualWith (const CustomUnitVector2D& other, const AngleTolerance& tol) const
{
	return IsParallelWith (other, tol) && ((*this) * other > 0.0);
}

template<class CoordinateType>
bool CustomUnitVector2D<CoordinateType>::IsPerpendicularTo (const CustomUnitVector2D& other, const AngleTolerance& tol) const
{
	return fabs ((*this) * other) < tol;
}

template<class CoordinateType>
bool CustomUnitVector2D<CoordinateType>::AreParallel (const CustomUnitVector2D& u1, const CustomUnitVector2D& u2, const AngleTolerance& tol)
{
	return u1.IsParallelWith (u2, tol);
}

template<class CoordinateType>
bool CustomUnitVector2D<CoordinateType>::AreEqual (const CustomUnitVector2D& u1, const CustomUnitVector2D& u2, const AngleTolerance& tol)
{
	return u1.IsEqualWith (u2, tol);
}

template<class CoordinateType>
bool CustomUnitVector2D<CoordinateType>::ArePerpendicular (const CustomUnitVector2D& u1, const CustomUnitVector2D& u2, const AngleTolerance& tol)
{
	return u1.IsPerpendicularTo (u2, tol);
}

template<class CoordinateType>
CustomUnitVector2D<CoordinateType> CustomUnitVector2D<CoordinateType>::operator- () const
{
	return CustomUnitVector2D<CoordinateType> (-x, -y);
}

template<class CoordinateType>
GSErrCode CustomUnitVector2D<CoordinateType>::Read (GS::IChannel& ic)
{
	return ic.Read (x, y);
}

template<class CoordinateType>
GSErrCode CustomUnitVector2D<CoordinateType>::Write (GS::OChannel& oc) const
{
	return oc.Write (x, y);
}

template<class CoordinateType>
GSErrCode CustomUnitVector2D<CoordinateType>::ReadXML (GS::XMLIChannel& ic, const char* tagName /*= nullptr*/)
{
	GS::XMLITag tag (ic, tagName == nullptr ? "UnitVector2D" : tagName);
	GSErrCode err = ic.ReadXML ("X", x);
	if DBERROR (err != NoError) return err;
	err = ic.ReadXML ("Y", y);
	if DBERROR (err != NoError) return err;
	return NoError;
}

template<class CoordinateType>
GSErrCode CustomUnitVector2D<CoordinateType>::WriteXML (GS::XMLOChannel& oc, const char* tagName /*= nullptr*/) const
{
	GS::XMLTag tag (oc, tagName == nullptr ? "UnitVector2D" : tagName);
	GSErrCode err = oc.WriteXML ("X", x);
	if DBERROR (err != NoError) return err;
	err = oc.WriteXML ("Y", y);
	if DBERROR (err != NoError) return err;
	return NoError;
}

template<class CoordinateType>
CustomUnitVector2D<CoordinateType>::CustomUnitVector2D (CoordinateType x, CoordinateType y) :
	x (x),
	y (y)
{

}

template<class CoordinateType>
GS::Optional<CustomUnitVector2D<CoordinateType>> ConvertToUnitVector (const Vector2<CoordinateType>& v, const DistanceTolerance& nullVectorLengthLimit /*= SmallEps*/)
{
	const double length = v.GetLength ();
	if (IsNearZero (length, nullVectorLengthLimit)) {
		return GS::NoValue;
	}
	return CustomUnitVector2D<CoordinateType> (static_cast<CoordinateType> (v.x / length), static_cast<CoordinateType> (v.y / length));
}

template<class CoordinateType> 
CustomUnitVector2D<CoordinateType> ConvertToUnitVector (const Vector2<CoordinateType>& v, const CustomUnitVector2D<CoordinateType>& resultIfInputIsNull)
{
	const GS::Optional<CustomUnitVector2D<CoordinateType>> u = ConvertToUnitVector (v);
	if (u.HasValue ()) {
		return u.Get ();
	} else {
		return resultIfInputIsNull;
	}
}

template<class CoordinateType> 
Vector2<CoordinateType>	operator* (double d, const CustomUnitVector2D<CoordinateType>& u)
{
	return static_cast<CoordinateType> (d) * u.ToVector2D ();
}

template<class CoordinateType> 
Vector2<CoordinateType>	operator* (const CustomUnitVector2D<CoordinateType>& u, double d)
{
	return d * u;
}

template<class CoordinateType> 
Vector2<CoordinateType>	operator+ (const CustomUnitVector2D<CoordinateType>& u1, const CustomUnitVector2D<CoordinateType>& u2)
{
	return u1.ToVector2D () + u2.ToVector2D ();
}

template<class CoordinateType> 
Vector2<CoordinateType>	operator- (const CustomUnitVector2D<CoordinateType>& u1, const CustomUnitVector2D<CoordinateType>& u2)
{
	return u1.ToVector2D () - u2.ToVector2D ();
}

template<class CoordinateType> 
CoordinateType operator* (const CustomUnitVector2D<CoordinateType>& u1, const CustomUnitVector2D<CoordinateType>& u2)
{
	return u1.ToVector2D () * u2.ToVector2D ();
}

template<class CoordinateType> 
CoordinateType operator^ (const CustomUnitVector2D<CoordinateType>& u1, const CustomUnitVector2D<CoordinateType>& u2)
{
	return u1.ToVector2D () ^ u2.ToVector2D ();
}

template <class CoordinateType> const CustomUnitVector2D<CoordinateType> CustomUnitVector2D<CoordinateType>::XAxis = CustomUnitVector2D<CoordinateType>::Create (1, 0);
template <class CoordinateType> const CustomUnitVector2D<CoordinateType> CustomUnitVector2D<CoordinateType>::YAxis = CustomUnitVector2D<CoordinateType>::Create (0, 1);

}

#endif

