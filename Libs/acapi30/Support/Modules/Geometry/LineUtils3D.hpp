#pragma once
#ifndef LINE_UTILS_3D_HPP_
#define LINE_UTILS_3D_HPP_

#include "Intersection3D.hpp"
#include "AngleData.h"

namespace Geometry {
namespace LineUtils3DHelper {

template <typename...>
struct is_one_of {
	static constexpr bool value = false;
};

template <typename F, typename S, typename... T>
struct is_one_of<F, S, T...> {
	static constexpr bool value =
		GS::IsSame<F, S> || is_one_of<F, T...>::value;
};

template <typename T>
class HasGetDirection {
	template <typename C> static void test (decltype (std::declval<C> ().GetDirection ())*);
	template <typename C> static char test (...);
public:
	static constexpr bool value = std::is_void<decltype(test<T> (0))>::value;
};

}
}

namespace Geometry {
namespace LineUtils3D {

	struct EmptyMerge {};

	//  Shorter segment

	GEOMETRY_DLL_EXPORT const Segment3D&	GetShorterSegment (const Segment3D& segment1, const Segment3D& segment2);

	//  Contains

	GEOMETRY_DLL_EXPORT bool				ContainsEntirely (const Segment3D& container, const Segment3D& target, const DistanceTolerance& tol = {});
	GEOMETRY_DLL_EXPORT bool				ContainsEntirely (const Ray3D& container, const Segment3D& target, const DistanceTolerance& tol = {});

	GEOMETRY_DLL_EXPORT bool				ContainsAnyPart (const Segment3D& container, const Segment3D& target, const DistanceTolerance& tol = {});
	GEOMETRY_DLL_EXPORT bool				ContainsAnyPart (const Ray3D& container, const Segment3D& target, const DistanceTolerance& tol = {});

	//  Point on segment as an interpolation parameter

	GEOMETRY_DLL_EXPORT double				ProjectionAsInterpolationParameter (const Segment3D& segment, const Point3D& point);

	//  Determine orientation compared to X & Y axis

	template<typename T>
	bool IsHorizontal (const T& target, const AngleTolerance& tol = AngleTolerance { RadEps }) {

		static_assert(LineUtils3DHelper::HasGetDirection<T>::value,
					  "Target needs to implement GetDirection ()");

		return target.GetDirection ().IsParallelWith (UnitVector_3D::XAxis, tol);
	}


	template<typename T>
	bool IsVertical (const T& target, const AngleTolerance& tol = AngleTolerance { RadEps }) {

		static_assert(LineUtils3DHelper::HasGetDirection<T>::value,
					  "Target needs to implement GetDirection ()");

		return target.GetDirection ().IsParallelWith (UnitVector_3D::YAxis, tol);
	}

	//  Cut // #KMark_note: to be refined

	template<typename T>
	GS::Optional<GS::Pair<Ray3D, Ray3D>> Cut (const Line3D& target, const T& cutter, const Tolerance& tol = Tolerance {}) {
		static_assert(LineUtils3DHelper::is_one_of<T, Line3D, Ray3D, Segment3D>::value, "Can only cut line with the types listed.");
		
		auto intersection = Intersect (target, cutter, tol);
		GS::Optional<GS::Pair<Ray3D, Ray3D>> result;

		if (intersection.template Is<Point3D> ()) {
			result = GS::Pair<Ray3D, Ray3D> 
			{
				Ray3D (intersection.template Get<Point3D> (),  target.GetDirection ()),
				Ray3D (intersection.template Get<Point3D> (), -target.GetDirection ())
			};
		}

		return result;
	}

	template<typename T>
	GS::Optional<GS::Pair<Ray3D, Segment3D>> Cut (const Ray3D& target, const T& cutter, const Tolerance& tol = Tolerance {}) {
		static_assert(LineUtils3DHelper::is_one_of<T, Line3D, Ray3D, Segment3D>::value, "Can only cut ray with the types listed.");
		
		auto intersection = Intersect (target, cutter, tol);
		GS::Optional<GS::Pair<Ray3D, Segment3D>> result;

		if (intersection.template Is<Point3D> ()) {
			Point3D intersection_point = intersection.template Get<Point3D> ();

			result = GS::Pair<Ray3D, Segment3D> 
			{
				Ray3D     (intersection_point, target.GetDirection ()),
				Segment3D (intersection_point, target.BasePoint ())
			};
		}

		return result;
	}

	template<typename T>
	GS::Optional<GS::Pair<Segment3D, Segment3D>> Cut (const Segment3D& target, const T& cutter, const Tolerance& tol = Tolerance {}) {
		static_assert(LineUtils3DHelper::is_one_of<T, Line3D, Ray3D, Segment3D>::value, "Can only cut segment with the types listed.");
		
		auto intersection = Intersect (target, cutter, tol);
		GS::Optional<GS::Pair<Segment3D, Segment3D>> result;

		if (intersection.template Is<Point3D> ()) {
			Point3D intersection_point = intersection.template Get<Point3D> ();

			result = GS::Pair<Segment3D, Segment3D> 
			{
				std::move (Segment3D (intersection_point, -target.GetDirection ().Get (), (target.BegPoint () - intersection_point).GetLength ().GetValue ())),
				std::move (Segment3D (intersection_point, target.GetDirection ().Get (), (target.EndPoint () - intersection_point).GetLength ().GetValue ()))
			};
		}

		return result;
	}

	// Separate // #KMark_note: to be refined

	GEOMETRY_DLL_EXPORT bool Separate (const Segment3D& target, const Segment3D& cutter, Segment3D& intersection, GS::Array<Segment3D>& results, const Tolerance& tol = Tolerance {});

	//  Merge // #KMark_note: to be refined

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyMerge, Ray3D, Line3D> Merge (const Ray3D& ray1, const Ray3D& ray2, const Tolerance& tol = Tolerance {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyMerge, Ray3D>         Merge (const Ray3D& ray, const Segment3D& segment, const Tolerance& tol = Tolerance {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyMerge, Segment3D>     Merge (const Segment3D& segment1, const Segment3D& segment2, const Tolerance& tol = Tolerance {});

	//  Segment from boundaries

	GEOMETRY_DLL_EXPORT Segment3D  CreateSegmentFromSegmentExtremes (const Segment3D&, const Segment3D&); // #KMark_note this is broken

}
}

#endif //LINE_UTILS_3D_HPP_
