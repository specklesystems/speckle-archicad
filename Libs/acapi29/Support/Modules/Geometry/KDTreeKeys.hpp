// *********************************************************************************************************************
// Description:		KDTreeKeys.hpp
//
// Module:			Modeler
// Contact person:	PP
//
// *********************************************************************************************************************

#ifndef KDTREEKEYS_HPP
#define KDTREEKEYS_HPP


#pragma once
#include "GeometricDefinitions.h"
#include "Box3DData.h"


namespace Geometry {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, short D>
	class KDTreeKeyTemplate {
	public:
		static const short DimCnt = D;
		typedef T DimType;

	protected:
		DimType data [DimCnt];

	public:
		GS_FORCE_INLINE	KDTreeKeyTemplate () {
			for (UIndex i = 0; i < DimCnt; ++i)
				data[i] = DimType ();
		}

		GS_FORCE_INLINE	DimType	GetDimVal (UInt32 dimIdx) const	
		{ 
			DBASSERT (dimIdx < DimCnt);
			return data [dimIdx];
		}

		GS_FORCE_INLINE	void	SetDimVal (UInt32 dimIdx, const DimType& val)
		{ 
			DBASSERT (dimIdx < DimCnt);
			data [dimIdx] = val;
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class GEOMETRY_DLL_EXPORT Box3DKey : public KDTreeKeyTemplate<double, 6> {
	public:
					Box3DKey () : KDTreeKeyTemplate<double, 6>::KDTreeKeyTemplate () {}
		explicit	Box3DKey (const F_Box3D& box); 
		explicit	Box3DKey (const Box3D& box); 
		explicit	Box3DKey (const Point3D& p, const double bxHalfSize); 
		explicit	Box3DKey (const Point3D& lowCorner, const Point3D& highCorner); 
		explicit	Box3DKey (const double xMin, const double xMax, const double yMin, const double yMax, const double zMin, const double zMax);
	};


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class GEOMETRY_DLL_EXPORT Box2DKey : public KDTreeKeyTemplate<double, 4> {
	public:
					Box2DKey () : KDTreeKeyTemplate<double, 4>::KDTreeKeyTemplate () {}
		explicit	Box2DKey (const Geometry::Vector2 <double>& lowCorner, const Geometry::Vector2 <double>& highCorner, const double addMargin = 0.0); 
		explicit	Box2DKey (double xMin, double xMax, double yMin, double yMax); 
		explicit	Box2DKey (const Box2DData& box); 
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class GEOMETRY_DLL_EXPORT Vector3DKey : public KDTreeKeyTemplate<double, 3> {
	public:
					Vector3DKey () : KDTreeKeyTemplate<double, 3>::KDTreeKeyTemplate () {}
		explicit	Vector3DKey (const Vector3D& v); 
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class GEOMETRY_DLL_EXPORT PlaneEqKey : public KDTreeKeyTemplate<double, 4> {
	public:
					PlaneEqKey () : KDTreeKeyTemplate<double, 4>::KDTreeKeyTemplate () {}
		explicit	PlaneEqKey (double a, double b, double c, double d); 
	};

} //Geometry

#endif //KDTREEKEYS_HPP