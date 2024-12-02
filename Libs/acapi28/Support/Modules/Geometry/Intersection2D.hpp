#ifndef INTERSECTION2D_H_
#define INTERSECTION2D_H_

#include "Ray2D.hpp"
#include "Variant.hpp"
#include "Sector2DData.h"
#include "Circle2DData.h"

namespace Geometry {

struct EmptyIntersection2D {};
struct PointPair2D { Point2D p1; Point2D p2; };

//  Calculate Intersection

GEOMETRY_DLL_EXPORT	auto	Intersect	(const Line2D&,		const Line2D&,		const Tolerance& = {})	-> GS::Variant<EmptyIntersection2D, Point2D, Line2D>;
GEOMETRY_DLL_EXPORT	auto	Intersect	(const Line2D&,		const Ray2D&,		const Tolerance& = {})	-> GS::Variant<EmptyIntersection2D, Point2D, Ray2D>;
GEOMETRY_DLL_EXPORT	auto	Intersect	(const Line2D&,		const Segment2D&,	const Tolerance& = {})	-> GS::Variant<EmptyIntersection2D, Point2D, Segment2D>;
GEOMETRY_DLL_EXPORT	auto	Intersect	(const Ray2D&,		const Ray2D&,		const Tolerance& = {})	-> GS::Variant<EmptyIntersection2D, Point2D, Segment2D, Ray2D>;
GEOMETRY_DLL_EXPORT	auto	Intersect	(const Ray2D&,		const Segment2D&,	const Tolerance& = {})	-> GS::Variant<EmptyIntersection2D, Point2D, Segment2D>;
GEOMETRY_DLL_EXPORT	auto	Intersect	(const Segment2D&,	const Segment2D&,	const Tolerance& = {})	-> GS::Variant<EmptyIntersection2D, Point2D, Segment2D>;
GEOMETRY_DLL_EXPORT	auto	Intersect	(const Line2D&,		const Circle2D&,	const Tolerance& = {})	-> GS::Variant<EmptyIntersection2D, Point2D, PointPair2D>;


GEOMETRY_DLL_EXPORT inline auto Intersect (const Ray2D& g1,		const Line2D& g2,	const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const Segment2D& g1, const Line2D& g2,	const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const Segment2D& g1, const Ray2D& g2,	const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const Circle2D& g1,	const Line2D& g2,	const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }


template <typename T1, typename T2>
GS::Optional<Point2D> IntersectInPoint (const T1& geom1, const T2& geom2, const Tolerance& tol = {})
{
	auto intersection = Intersect (geom1, geom2, tol);
	if (intersection.template Is<Point2D> ()) {
		return intersection.template Get<Point2D> ();
	} else {
		return GS::NoValue;
	}
}

}


#endif
