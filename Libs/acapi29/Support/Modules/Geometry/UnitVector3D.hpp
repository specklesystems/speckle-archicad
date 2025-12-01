#ifndef _UNITVECTOR_3D_HPP
#define _UNITVECTOR_3D_HPP
#pragma once

#include "UnitVector3DClassDeclaration.hpp"


namespace Geometry {

template<class CoordinateType>
CustomUnitVector3D<CoordinateType> CustomUnitVector3D<CoordinateType>::Create (CoordinateType x, CoordinateType y, CoordinateType z, const DistanceTolerance& nullVectorLengthLimit)
{
	return Create (Vector3<CoordinateType> (x, y, z), nullVectorLengthLimit);
}

template<class CoordinateType>
CustomUnitVector3D<CoordinateType> CustomUnitVector3D<CoordinateType>::Create (const Vector3<CoordinateType>& v, const DistanceTolerance& nullVectorLengthLimit)
{
	const GS::Optional<CustomUnitVector3D<CoordinateType>> u = ConvertToUnitVector<CoordinateType> (v, nullVectorLengthLimit);
	if (u.HasValue ()) {
		return u.Get ();
	} else {
		throw UnitVectorCreationError ();
	}
}

template<class CoordinateType>
Vector3<CoordinateType> CustomUnitVector3D<CoordinateType>::ToVector3D () const
{
	return Vector3<CoordinateType> (x, y, z);
}

template<class CoordinateType>
CustomUnitVector3D<CoordinateType>::operator Vector3<CoordinateType> () const
{
	return ToVector3D ();
}

template <class CoordinateType>
bool CustomUnitVector3D<CoordinateType>::IsParallelWith (const CustomUnitVector3D& other, const AngleTolerance& eps) const
{
	return ((*this) ^ other).GetLengthSqr () < eps * eps;
}

template<class CoordinateType>
bool CustomUnitVector3D<CoordinateType>::IsEqualWith (const CustomUnitVector3D& other, const AngleTolerance& eps) const
{
	return IsParallelWith (other, eps) && ((*this) * other > 0.0);
}

template<class CoordinateType>
bool CustomUnitVector3D<CoordinateType>::IsPerpendicularTo (const CustomUnitVector3D& other, const AngleTolerance& eps) const
{
	return fabs ((*this) * other) < eps;
}

template<class CoordinateType>
bool CustomUnitVector3D<CoordinateType>::AreParallel (const CustomUnitVector3D& u1, const CustomUnitVector3D& u2, const AngleTolerance& eps)
{
	return u1.IsParallelWith (u2, eps);
}

template<class CoordinateType>
bool CustomUnitVector3D<CoordinateType>::AreEqual (const CustomUnitVector3D& u1, const CustomUnitVector3D& u2, const AngleTolerance& eps)
{
	return u1.IsEqualWith (u2, eps);
}

template<class CoordinateType>
bool CustomUnitVector3D<CoordinateType>::ArePerpendicular (const CustomUnitVector3D& u1, const CustomUnitVector3D& u2, const AngleTolerance& eps)
{
	return u1.IsPerpendicularTo (u2, eps);
}

template<class CoordinateType>
CustomUnitVector3D<CoordinateType> CustomUnitVector3D<CoordinateType>::operator- () const
{
	return CustomUnitVector3D<CoordinateType> (-x, -y, -z);
}

template <class CoordinateType>
CustomUnitVector3D<CoordinateType>::CustomUnitVector3D (CoordinateType x, CoordinateType y, CoordinateType z) :
	x (x),
	y (y),
	z (z)
{

}

template<class CoordinateType> 
Vector3<CoordinateType> operator* (double d, const CustomUnitVector3D<CoordinateType>& u)
{
	return static_cast<CoordinateType> (d) * u.ToVector3D ();
}

template<class CoordinateType> 
Vector3<CoordinateType> operator* (const CustomUnitVector3D<CoordinateType>& u, double d)
{
	return d * u;
}

template<class CoordinateType> 
Vector3<CoordinateType> operator+ (const CustomUnitVector3D<CoordinateType>& u1, const CustomUnitVector3D<CoordinateType>& u2) 
{
	return u1.ToVector3D () + u2.ToVector3D ();
}

template<class CoordinateType> 
Vector3<CoordinateType> operator- (const CustomUnitVector3D<CoordinateType>& u1, const CustomUnitVector3D<CoordinateType>& u2) 
{
	return u1.ToVector3D () - u2.ToVector3D ();
}

template<class CoordinateType> 
CoordinateType operator* (const CustomUnitVector3D<CoordinateType>& u1, const CustomUnitVector3D<CoordinateType>& u2)
{
	return u1.ToVector3D () * u2.ToVector3D ();
}

template<class CoordinateType> 
Vector3<CoordinateType> operator^ (const CustomUnitVector3D<CoordinateType>& u1, const CustomUnitVector3D<CoordinateType>& u2) 
{
	return u1.ToVector3D () ^ u2.ToVector3D ();
}

template<class CoordinateType>
GS::Optional<CustomUnitVector3D<CoordinateType>> ConvertToUnitVector (const Vector3<CoordinateType>& v, const DistanceTolerance& nullVectorLengthLimit /*= SmallEps*/)
{
	const double length = v.GetLength ();
	if (IsNearZero (length, nullVectorLengthLimit)) {
		return GS::NoValue;
	}
	return CustomUnitVector3D<CoordinateType> (static_cast<CoordinateType> (v.x / length), static_cast<CoordinateType> (v.y / length), static_cast<CoordinateType> (v.z / length));
}

template<class CoordinateType>
CustomUnitVector3D<CoordinateType> ConvertToUnitVector (const Vector3<CoordinateType>& v, const CustomUnitVector3D<CoordinateType>& resultIfInputIsNull)	// to keep the functionality of CustomUnitVector3D function
{
	const GS::Optional<CustomUnitVector3D<CoordinateType>> u = ConvertToUnitVector (v);
	if (u.HasValue ()) {
		return u.Get ();
	} else {
		return resultIfInputIsNull;
	}
}

template<class CoordinateType>
GSErrCode CustomUnitVector3D<CoordinateType>::Read (GS::IChannel& ic)
{
	ERRCHK (ic.Read (x));
	ERRCHK (ic.Read (y));
	ERRCHK (ic.Read (z));
	return NoError;
}

template<class CoordinateType>
GSErrCode CustomUnitVector3D<CoordinateType>::Write (GS::OChannel& oc) const
{
	ERRCHK (oc.Write (x));
	ERRCHK (oc.Write (y));
	ERRCHK (oc.Write (z));
	return NoError;
}

template<class CoordinateType>
GSErrCode CustomUnitVector3D<CoordinateType>::ReadXML (GS::XMLIChannel& ic, const char* tagName /*= nullptr*/)
{
	GS::XMLITag tag (ic, tagName == nullptr ? "UnitVector3D" : tagName);
	ERRCHK (ic.ReadXML ("X", x));
	ERRCHK (ic.ReadXML ("Y", y));
	ERRCHK (ic.ReadXML ("Z", z));
	return NoError;
}

template<class CoordinateType>
GSErrCode CustomUnitVector3D<CoordinateType>::WriteXML (GS::XMLOChannel& oc, const char* tagName /*= nullptr*/) const
{
	GS::XMLTag tag (oc, tagName == nullptr ? "UnitVector3D" : tagName);
	ERRCHK (oc.WriteXML ("X", x));
	ERRCHK (oc.WriteXML ("Y", y));
	ERRCHK (oc.WriteXML ("Z", z));
	return NoError;
}

template <class CoordinateType> const CustomUnitVector3D<CoordinateType> CustomUnitVector3D<CoordinateType>::XAxis = CustomUnitVector3D<CoordinateType>::Create (1, 0, 0);
template <class CoordinateType> const CustomUnitVector3D<CoordinateType> CustomUnitVector3D<CoordinateType>::YAxis = CustomUnitVector3D<CoordinateType>::Create (0, 1, 0);
template <class CoordinateType> const CustomUnitVector3D<CoordinateType> CustomUnitVector3D<CoordinateType>::ZAxis = CustomUnitVector3D<CoordinateType>::Create (0, 0, 1);

}

#endif

