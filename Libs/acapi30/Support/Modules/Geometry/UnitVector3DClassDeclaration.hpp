#ifndef _UNITVECTOR_3D_CLASS_DECLARATION_HPP
#define _UNITVECTOR_3D_CLASS_DECLARATION_HPP
#pragma once

#include "Vector3D.hpp"
#include "UnitVectorCreationError.hpp"
#include "Tolerance.hpp"


namespace Geometry {

template <class CoordinateType>
class CustomUnitVector3D
{
public:
	static const CustomUnitVector3D<CoordinateType> XAxis;
	static const CustomUnitVector3D<CoordinateType> YAxis;
	static const CustomUnitVector3D<CoordinateType> ZAxis;

	static CustomUnitVector3D Create (CoordinateType x, CoordinateType y, CoordinateType z, const DistanceTolerance& tol = DistanceTolerance (SmallEps));
	static CustomUnitVector3D Create (const Vector3<CoordinateType>& v, const DistanceTolerance& tol = DistanceTolerance (SmallEps));

	inline Vector3<CoordinateType> ToVector3D () const;
	inline operator Vector3<CoordinateType> () const;

	bool IsParallelWith		(const CustomUnitVector3D& other, const AngleTolerance& tol = AngleTolerance::Default) const;
	bool IsEqualWith		(const CustomUnitVector3D& other, const AngleTolerance& tol = AngleTolerance::Default) const;
	bool IsPerpendicularTo	(const CustomUnitVector3D& other, const AngleTolerance& tol = AngleTolerance::Default) const;

	static bool AreParallel			(const CustomUnitVector3D& u1, const CustomUnitVector3D& u2, const AngleTolerance& tol = AngleTolerance::Default);
	static bool AreEqual			(const CustomUnitVector3D& u1, const CustomUnitVector3D& u2, const AngleTolerance& tol = AngleTolerance::Default);
	static bool ArePerpendicular	(const CustomUnitVector3D& u1, const CustomUnitVector3D& u2, const AngleTolerance& tol = AngleTolerance::Default);

	CustomUnitVector3D operator- () const;

	GSErrCode Read (GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	GSErrCode ReadXML (GS::XMLIChannel& ic, const char* tagName = nullptr);
	GSErrCode WriteXML (GS::XMLOChannel& oc, const char* tagName = nullptr) const;

private:
	template<class T> 
	friend GS::Optional<CustomUnitVector3D<T>> ConvertToUnitVector (const Vector3<T>&, const DistanceTolerance&);
		
	CustomUnitVector3D () = delete;
	CustomUnitVector3D (CoordinateType x, CoordinateType y, CoordinateType z);

	template<class T>
	using ValidCoordinateType = EnableIf<GS::IsSame<T, float> || GS::IsSame<T, double>, T>;

	ValidCoordinateType<CoordinateType> x, y, z;
};


template<class CoordinateType>	GS::Optional<CustomUnitVector3D<CoordinateType>> ConvertToUnitVector (const Vector3<CoordinateType>& v, const DistanceTolerance& tol = DistanceTolerance { SmallEps });
template<class CoordinateType>	CustomUnitVector3D<CoordinateType> ConvertToUnitVector (const Vector3<CoordinateType>& v, const CustomUnitVector3D<CoordinateType>& resultIfInputIsNull);	// to keep the functionality of CustomUnitVector3D function

template<class CoordinateType> Vector3<CoordinateType>	operator* (double d, const CustomUnitVector3D<CoordinateType>& u);
template<class CoordinateType> Vector3<CoordinateType>	operator* (const CustomUnitVector3D<CoordinateType>& u, double d);
template<class CoordinateType> Vector3<CoordinateType>	operator+ (const CustomUnitVector3D<CoordinateType>& u1, const CustomUnitVector3D<CoordinateType>& u2); 
template<class CoordinateType> Vector3<CoordinateType>	operator- (const CustomUnitVector3D<CoordinateType>& u1, const CustomUnitVector3D<CoordinateType>& u2); 
template<class CoordinateType> CoordinateType			operator* (const CustomUnitVector3D<CoordinateType>& u1, const CustomUnitVector3D<CoordinateType>& u2);
template<class CoordinateType> Vector3<CoordinateType>	operator^ (const CustomUnitVector3D<CoordinateType>& u1, const CustomUnitVector3D<CoordinateType>& u2); 


typedef CustomUnitVector3D<double> UnitVector_3D;
typedef CustomUnitVector3D<float> F_UnitVector_3D;

}

using Geometry::UnitVector_3D;

#endif

