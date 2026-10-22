#pragma once
#ifndef LINE_UTILS_2D_HPP_
#define LINE_UTILS_2D_HPP_

#include "Intersection2D.hpp"
#include "AngleData.h"

namespace Geometry {
namespace LineUtils2DHelper {

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
namespace LineUtils2D {

	struct EmptyMerge {};

	//  Shorter segment

	GEOMETRY_DLL_EXPORT const Segment2D&	GetShorterSegment (const Segment2D& segment1, const Segment2D& segment2);

	//  Contains

	GEOMETRY_DLL_EXPORT bool				ContainsEntirely (const Segment2D& container, const Segment2D& target, const DistanceTolerance& tol = {});
	GEOMETRY_DLL_EXPORT bool				ContainsEntirely (const Ray2D& container, const Segment2D& target, const DistanceTolerance& tol = {});

	GEOMETRY_DLL_EXPORT bool				ContainsAnyPart (const Segment2D& container, const Segment2D& target, const DistanceTolerance& tol = {});
	GEOMETRY_DLL_EXPORT bool				ContainsAnyPart (const Ray2D& container, const Segment2D& target, const DistanceTolerance& tol = {});

	//  Point on segment as an interpolation parameter

	GEOMETRY_DLL_EXPORT double				ProjectionAsInterpolationParameter (const Segment2D& segment, const Point2D& point);

	//  Determine orientation compared to X & Y axis

	template<typename T>
	bool IsHorizontal (const T& target, const AngleTolerance& tol = AngleTolerance { RadEps }) {

		static_assert(LineUtils2DHelper::HasGetDirection<T>::value,
					  "Target needs to implement GetDirection ()");

		return target.GetDirection ().IsParallelWith (UnitVector_2D::XAxis, tol);
	}


	template<typename T>
	bool IsVertical (const T& target, const AngleTolerance& tol = AngleTolerance { RadEps }) {

		static_assert(LineUtils2DHelper::HasGetDirection<T>::value,
					  "Target needs to implement GetDirection ()");

		return target.GetDirection ().IsParallelWith (UnitVector_2D::YAxis, tol);
	}

	//  Cut // #KMark_note: to be refined

	template<typename T>
	GS::Optional<GS::Pair<Ray2D, Ray2D>> Cut (const Line2D& target, const T& cutter, const Tolerance& tol = Tolerance {}) {
		static_assert(LineUtils2DHelper::is_one_of<T, Line2D, Ray2D, Segment2D>::value, "Can only cut line with the types listed.");
		
		auto intersection = Intersect (target, cutter, tol);
		GS::Optional<GS::Pair<Ray2D, Ray2D>> result;

		if (intersection.template Is<Point2D> ()) {
			result = GS::Pair<Ray2D, Ray2D> 
			{
				Ray2D (intersection.template Get<Point2D> (),  target.GetDirection ()),
				Ray2D (intersection.template Get<Point2D> (), -target.GetDirection ())
			};
		}

		return result;
	}

	template<typename T>
	GS::Optional<GS::Pair<Ray2D, Segment2D>> Cut (const Ray2D& target, const T& cutter, const Tolerance& tol = Tolerance {}) {
		static_assert(LineUtils2DHelper::is_one_of<T, Line2D, Ray2D, Segment2D>::value, "Can only cut ray with the types listed.");
		
		auto intersection = Intersect (target, cutter, tol);
		GS::Optional<GS::Pair<Ray2D, Segment2D>> result;

		if (intersection.template Is<Point2D> ()) {
			Point2D intersection_point = intersection.template Get<Point2D> ();

			result = GS::Pair<Ray2D, Segment2D> 
			{
				Ray2D     (intersection_point, target.GetDirection ()),
				Segment2D (intersection_point, target.BasePoint ())
			};
		}

		return result;
	}

	template<typename T>
	GS::Optional<GS::Pair<Segment2D, Segment2D>> Cut (const Segment2D& target, const T& cutter, const Tolerance& tol = Tolerance {}) {
		static_assert(LineUtils2DHelper::is_one_of<T, Line2D, Ray2D, Segment2D>::value, "Can only cut segment with the types listed.");
		
		auto intersection = Intersect (target, cutter, tol);
		GS::Optional<GS::Pair<Segment2D, Segment2D>> result;

		if (intersection.template Is<Point2D> ()) {
			Point2D intersection_point = intersection.template Get<Point2D> ();

			result = GS::Pair<Segment2D, Segment2D> 
			{
				std::move (Segment2D (intersection_point, -target.GetDirection ().Get (), (target.BegPoint () - intersection_point).GetLength ().GetValue ())),
				std::move (Segment2D (intersection_point, target.GetDirection ().Get (), (target.EndPoint () - intersection_point).GetLength ().GetValue ()))
			};
		}

		return result;
	}

	// Separate // #KMark_note: to be refined

	GEOMETRY_DLL_EXPORT bool Separate (const Segment2D& target, const Segment2D& cutter, Segment2D& intersection, GS::Array<Segment2D>& results, const Tolerance& tol = Tolerance {});

	//  Merge // #KMark_note: to be refined

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyMerge, Ray2D, Line2D> Merge (const Ray2D& ray1, const Ray2D& ray2, const Tolerance& tol = Tolerance {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyMerge, Ray2D>         Merge (const Ray2D& ray, const Segment2D& segment, const Tolerance& tol = Tolerance {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyMerge, Segment2D>     Merge (const Segment2D& segment1, const Segment2D& segment2, const Tolerance& tol = Tolerance {});

	//  Segment from boundaries

	GEOMETRY_DLL_EXPORT Segment2D  CreateSegmentFromSegmentExtremes (const Segment2D&, const Segment2D&);

}
}

#endif //LINE_UTILS_2D_HPP_
