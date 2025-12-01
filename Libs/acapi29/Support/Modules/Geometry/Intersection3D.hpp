#ifndef INTERSECTION3D_H_
#define INTERSECTION3D_H_

#include "Ray3D.hpp"
#include "Variant.hpp"
#include "Sector3DData.h"
#include "Plane3D.hpp"
#include "InfiniteCylinder.hpp"
#include "InfiniteCone.hpp"

namespace Geometry {

struct EmptyIntersection3D {};
struct PointPair3D { Point3D p1; Point3D p2; };

GEOMETRY_DLL_EXPORT auto	Intersect	(const Line3D&,		const Line3D&,				const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, Line3D>;
GEOMETRY_DLL_EXPORT auto	Intersect	(const Line3D&,		const Ray3D&,				const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, Ray3D>;
GEOMETRY_DLL_EXPORT auto	Intersect	(const Line3D&,		const Sector3D&,			const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, Sector3D>;
GEOMETRY_DLL_EXPORT auto	Intersect	(const Ray3D&,		const Ray3D&,				const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, Sector3D, Ray3D>;
GEOMETRY_DLL_EXPORT auto	Intersect	(const Ray3D& ,		const Sector3D&,			const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, Sector3D>;
GEOMETRY_DLL_EXPORT	auto	Intersect	(const Sector3D&,	const Sector3D&,			const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, Sector3D>;

GEOMETRY_DLL_EXPORT	auto	Intersect	(const Line3D&,		const Plane3D&,				const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, Line3D>;
GEOMETRY_DLL_EXPORT auto	Intersect	(const Ray3D&,		const Plane3D&,				const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, Ray3D>;
GEOMETRY_DLL_EXPORT auto	Intersect	(const Sector3D&,	const Plane3D&,				const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, Sector3D>;

GEOMETRY_DLL_EXPORT auto	Intersect	(const Line3D&,		const InfiniteCylinder&,	const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, PointPair3D, Line3D>;
GEOMETRY_DLL_EXPORT auto	Intersect	(const Ray3D&,		const InfiniteCylinder&,	const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, PointPair3D, Ray3D>;
GEOMETRY_DLL_EXPORT auto	Intersect	(const Sector3D&,	const InfiniteCylinder&,	const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, PointPair3D, Sector3D>;

GEOMETRY_DLL_EXPORT auto	Intersect	(const Line3D&,		const InfiniteCone&,		const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, PointPair3D, Ray3D>;
GEOMETRY_DLL_EXPORT auto	Intersect	(const Ray3D&,		const InfiniteCone&,		const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, PointPair3D, Sector3D, Ray3D>;
GEOMETRY_DLL_EXPORT auto	Intersect	(const Sector3D&,	const InfiniteCone&,		const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Point3D, PointPair3D, Sector3D>;

GEOMETRY_DLL_EXPORT auto	Intersect	(const Plane3D&,	const Plane3D&,				const Tolerance& = {})	-> GS::Variant<EmptyIntersection3D, Line3D, Plane3D>;


// ==== Intersection Convenience functions ====

GEOMETRY_DLL_EXPORT inline auto Intersect (const Ray3D& g1,				const Line3D& g2,		const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const Sector3D& g1,			const Line3D& g2,		const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const Sector3D& g1,			const Ray3D& g2,		const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT	inline auto Intersect (const Plane3D& g1,			const Line3D& g2,		const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const Plane3D& g1,			const Ray3D& g2,		const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const Plane3D& g1,			const Sector3D& g2,		const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const InfiniteCylinder& g1,	const Line3D& g2,		const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const InfiniteCylinder& g1,	const Ray3D& g2,		const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const InfiniteCylinder& g1,	const Sector3D& g2,		const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const InfiniteCone& g1,		const Line3D& g2,		const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const InfiniteCone& g1,		const Ray3D& g2,		const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }
GEOMETRY_DLL_EXPORT inline auto Intersect (const InfiniteCone& g1,		const Sector3D& g2,		const Tolerance& tol = {}) { return Intersect (g2, g1, tol); }


// ==== Optional intersection versions ====

template <typename IntersectionT, typename T1, typename T2>
GS::Optional<IntersectionT> IntersectIn (const T1& geom1, const T2& geom2, const Tolerance& tolerance = {})
{
	auto intersection = Intersect (geom1, geom2, tolerance);
	if (intersection.template Is<IntersectionT> ()) {
		return intersection.template Get<IntersectionT> ();
	} else {
		return GS::NoValue;
	}
}


template <typename T1, typename T2>
GS::Optional<Point3D> IntersectInPoint3D (const T1& geom1, const T2& geom2, const Tolerance& tolerance = {})
{
	return IntersectIn<Point3D, T1, T2> (geom1, geom2, tolerance);
}

template <typename T1, typename T2>
GS::Optional<Line3D> IntersectInLine3D (const T1& geom1, const T2& geom2, const Tolerance& tolerance = {})
{
	return IntersectIn<Line3D, T1, T2> (geom1, geom2, tolerance);
}

}


#endif
