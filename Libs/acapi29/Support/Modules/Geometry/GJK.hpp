/**
 * @file	GJK.hpp
 *
 * @brief	Specialized Gilbert-Johnson-Keerthi algorithm implementation for quick collision detection.
 *
 * @details	GJK's original intent was to determine the distance between two convex shapes, but with this
 * 			specialized implementation can also be used to return collision information. Relies heavily on a
 * 			concept called the Minkowski Sum or Difference.
 *
 * 			It is an algorithm that can only be used with convex shapes. It is an iterative method but converges
 * 			very fast, trying to determine collision by checking if the Minkowski Difference of the two convex
 * 			shapes encloses the zero point, meaning that they have at least one common point, i.e. collision occurs.
 *
 * @namespace	Geometry
 * @author		BLZ
 */

#ifndef GJK_HPP
#define GJK_HPP

#pragma once

#include "Vector2D.hpp"
#include "Vector3D.hpp"


namespace Geometry {

	/**
	 * The result of the collision detection.
	 * @ingroup Geometry
	 */
	template<typename VectorType>
	class GJKResult
	{
	public:
		/**
		 * Enumerates all possible results of the GJK algorithm.
		 */
		enum class CollisionType
		{
			UNDEFINED,
			COLLISION,
			NO_COLLISION,
			COLLISION_NOT_FOUND
		};

		/**
		 * Check if this class contains a collision.
		 * @return True if there was a collision.
		 */
		operator bool () const {
			return collision == CollisionType::COLLISION;
		}

		/**
		 * Check if this class contains a collision.
		 * @return True if there was a collision.
		 */
		bool IsCollided () const {
			return collision == CollisionType::COLLISION;
		}

		/**
		 * Check if any collision was found.
		 * @return True if any collision was not found.
		 */
		bool IsNotFound () const {
			return collision == CollisionType::COLLISION_NOT_FOUND;
		}

		/**
		 * Check if objects are closer than the @c dist parameter.
		 * @param dist The distance.
		 * @return True if the distance between objects is closer than the @c dist parameter.
		 */
		template<typename DistanceType>
		bool IsCloser (DistanceType dist) const {
			return IsCollided () || ( collision == CollisionType::NO_COLLISION && -support * direction < dist * direction.GetLength ());
		}

		/**
		 * Creates a @ref GJKResult object with collision result.
		 * @return A @ref GJKResult object.
		 */
		static GJKResult Collision ()
		{
			GJKResult res;
			res.collision = CollisionType::COLLISION;
			return res;
		}

		/**
		 * Creates a @ref GJKResult object with no collision result.
		 * @param support Support point.
		 * @param direction The direction vector.
		 * @return A @ref GJKResult object.
		 */
		static GJKResult NoCollision (const VectorType &support, const VectorType &direction)
		{
			GJKResult res;
			res.collision = CollisionType::NO_COLLISION;
			res.support = support;
			res.direction = direction;
			return res;
		}

		/**
		 * Creates a @ref GJKResult object with collision not found result.
		 * @param support Support point.
		 * @param direction The direction vector.
		 * @return A @ref GJKResult object.
		 */
		static GJKResult NotFound (const VectorType &support, const VectorType &direction)
		{
			GJKResult res;
			res.collision = CollisionType::COLLISION_NOT_FOUND;
			res.support = support;
			res.direction = direction;
			return res;
		}

	private:
		GJKResult () {}

		CollisionType collision = CollisionType::UNDEFINED;
		VectorType support;
		VectorType direction;
	};


	// *********************************************************************************************************************
	// *** Helper functions
	// *********************************************************************************************************************


	/**
	 * This is to compute the average center (roughly).
	 *
	 * It might be different from the Center of Gravity, especially for bodies with nonuniform density,
	 * but this is ok as the initial direction of simplex search in GJK.
	 * @ingroup Geometry
	 * @param vertices	The array of vertices.
	 *
	 * @return			The average center point.
	 */
	template<typename VectorType>
	VectorType GJKGetAveragePoint (const GS::Array<VectorType>& vertices);


	/**
	 * Get the furthest vertex point along a certain direction.
	 * @ingroup Geometry
	 * @param vertices	The array of vertices.
	 * @param d			The direction vector.
	 *
	 * @return			The furthest vertex point.
	 */
	template<typename VectorType>
	VectorType GJKGetFurthestPoint (const GS::Array<VectorType>& vertices, const VectorType& d);


	/**
	 * Minkowski sum support function for GJK.
	 * @ingroup Geometry
	 * @param vertices1	The array of vertices of the first shape.
	 * @param vertices2	The array of vertices of the second shape.
	 * @param d			The direction vector.
	 *
	 * @return			The Minkowski sum support point along the specified direction.
	 */
	template<typename VectorType>
	VectorType GJKGetSupport (const GS::Array<VectorType>& vertices1, const GS::Array<VectorType>& vertices2, const VectorType& d);


	// *********************************************************************************************************************
	// *** Simplex computing in 2D and 3D
	// *********************************************************************************************************************


	/**
	 * Zero-point check for the current simplex in the Minkowski space.
	 *
	 * Specific implementation for the 2D case.
	 * @ingroup Geometry
	 * @param simplex	The current simplex. The function updates it based on the zero-point direction.
	 * @param direction	The current direction. The function updates it based on the zero-point direction.
	 *
	 * @return			<c>true</c> if the zero point is included in the Minkowski sum, i.e. collision is detected, <c>false</c> otherwise.
	 */
	template<typename Coordinate>
	bool GJKDoSimplex (GS::Array<Vector2<Coordinate>>& simplex, Vector2<Coordinate>& direction);


	/**
	 * Zero-point check for the current simplex in the Minkowski space.
	 *
	 * Specific implementation for the 3D case.
	 * @ingroup Geometry
	 * @param simplex	The current simplex. The function updates it based on the zero-point direction.
	 * @param direction	The current direction. The function updates it based on the zero-point direction.
	 *
	 * @return			<c>true</c> if the zero point is included in the Minkowski sum, i.e. collision is detected, <c>false</c> otherwise.
	 */
	template<typename Coordinate>
	bool GJKDoSimplex (GS::Array<Vector3<Coordinate>>& simplex, Vector3<Coordinate>& direction);


	// *********************************************************************************************************************
	// *** GJK Algorithm implementations
	// *********************************************************************************************************************


	/**
	 * Generic implementation of the specialized GJK algorithm for collision detection.
	 * @ingroup Geometry
	 * @param supportFunction	The support function callback to get the Minkowski difference point for a specific direction.
	 * @param direction			The initial direction for algorithm startup.
	 *
	 * @return					<c>true</c> if the zero point is included in the Minkowski difference, i.e. collision is detected, <c>false</c> otherwise.
	 */
	template<typename SupportFunction, typename VectorType>
	GJKResult<VectorType> GJKCollisionDetection (SupportFunction supportFunction, VectorType direction);


	/**
	 * Specific implementation of the specialized GJK algorithm for two shapes defined by vertices.
	 * @ingroup Geometry
	 * @param vertices1	The array of vertices of the first shape.
	 * @param vertices2	The array of vertices of the second shape.
	 *
	 * @return			<c>true</c> if the zero point is included in the Minkowski difference, i.e. collision is detected, <c>false</c> otherwise.
	 */
	template<typename VectorType>
	GJKResult<VectorType> GJKCollisionDetection (const GS::Array<VectorType>& vertices1, const GS::Array<VectorType>& vertices2);


	// *********************************************************************************************************************
	// *** Template functions implementation
	// *********************************************************************************************************************


	template<typename VectorType>
	VectorType GJKGetAveragePoint (const GS::Array<VectorType>& vertices)
	{
		VectorType avg;

		for (auto& vertice : vertices)
			avg += vertice;

		avg /= vertices.GetSize ();

		return avg;
	}


	template<typename VectorType>
	VectorType GJKGetFurthestPoint (const GS::Array<VectorType>& vertices, const VectorType& d)
	{
		USize count = vertices.GetSize ();
		if (count == 0)
			return VectorType ();

		auto maxProduct = d * vertices[0];
		const VectorType *vMax = &vertices[0];

		for (USize i = 1; i < count; ++i) {
			auto product = d * vertices[i];
			if (product > maxProduct) {
				maxProduct = product;
				vMax = &vertices[i];
			}
		}

		return *vMax;
	}


	template<typename VectorType>
	VectorType GJKGetSupport (const GS::Array<VectorType>& vertices1, const GS::Array<VectorType>& vertices2, const VectorType& d)
	{
		// get furthest point of first body along an arbitrary direction
		VectorType v1 = GJKGetFurthestPoint (vertices1, d);

		// get furthest point of second body along the opposite direction
		VectorType v2 = GJKGetFurthestPoint (vertices2, -d);

		// subtract the two points to compute the Minkowski difference
		return v1 - v2;
	}


	template<typename Coordinate>
	bool GJKDoSimplex (GS::Array<Vector2<Coordinate>>& simplex, Vector2<Coordinate>& direction)
	{
		// Triple product expansion is used to calculate perpendicular normal vectors,
		// which kinda 'prefer' pointing towards the Origin in Minkowski space.
		auto tripleProduct = [](const Vector2<Coordinate>& a, const Vector2<Coordinate>& b, const Vector2<Coordinate>& c) -> Vector2<Coordinate> {
			Coordinate ac = a * c; // perform a.dot(c)
			Coordinate bc = b * c; // perform b.dot(c)

			// perform b * a.dot(c) - a * b.dot(c)
			Vector2<Coordinate> r {
				b.x * ac - a.x * bc,
				b.y * ac - a.y * bc,
			};

			return r;
		};

		// Handle the different number of simplex points.
		//
		// The simplex should always have at least two points, when the function is called.
		//
		// When the simplex has:
		//   - 2 points, i.e. a line, we should check in which direction to search for the next point.
		//   - 3 points, i.e. a triangle, it can enclose the origo (for 2D shapes the Minkowski space is also 2D),
		//     or if the origo is still outside, check which simplex point(s) must be eliminated, and in which
		//     direction to search for the next point.
		//
		// As for convention the following named vectors are used:
		//   - 'a': the last simplex point
		//   - 'b': the previous simplex point
		//   - 'c': the pre-previous simplex point (just in the 3 points case)
		//
		//   - 'ao': the direction from A towards the origin
		//   - 'ab': the direction from A to B
		//   - 'ac': the direction from A to C
		//
		// The implementation uses auto type specification instead of fully classified types just for convenience,
		// better code readability and also easier to compare to the 3D implementation.

		switch (simplex.GetSize ())
		{
			case 0:
			case 1:
				DBBREAK (); // simplex must have at least 2 points

			case 2: // simplex has 2 points (a line segment, not a triangle yet)
			{
				auto a = simplex[1];
				auto b = simplex[0];

				auto ao = -a; // from point A to Origin is just negative A
				auto ab = b - a; // from point A to B

				// the Origin is in the same direction as AB
				if (ab * ao > 0) {
					//simplex = { b, a }; // simplex remains as it is
					direction = tripleProduct (ab, ao, ab); // normal to AB towards Origin

				// the Origin is still further away
				} else {
					simplex = { a };
					direction = ao;
				}
			} break;

			case 3: // simplex has 3 points (a triangle)
			{
				auto a = simplex[2];
				auto b = simplex[1];
				auto c = simplex[0];

				auto ao = -a; // from point A to Origin is just negative A
				auto ab = b - a; // from point A to B
				auto ac = c - a; // from point A to C

				auto abperp = tripleProduct (ac, ab, ab); // perpendicular vector on the AB
				auto acperp = tripleProduct (ab, ac, ac); // perpendicular vector on the AC

				if (acperp * ao > 0) { // above the AC line
					simplex = { c, a };
					direction = acperp;
				} else if (abperp * ao > 0) { // above the AB line
					simplex = { b, a };
					direction = abperp;
				} else { // inside the triangle
					return true;
				}
			} break;

			default:
				DBBREAK (); // we should not get in here
		}

		return false;
	}


	template<typename Coordinate>
	bool GJKDoSimplex (GS::Array<Vector3<Coordinate>>& simplex, Vector3<Coordinate>& direction)
	{
		// Handle the different number of simplex points.
		//
		// The simplex should always have at least two points, when the function is called.
		//
		// When the simplex has:
		//   - 2 points, i.e. a line, check in which direction to search for the next point.
		//   - 3 points, i.e. a triangle, check in which direction to search for the next point.
		//   - 4 points, i.e. a tetraheadron, it can enclose the origo (for 3D shapes the Minkowski space is also 3D),
		//     or if the origo is still outside, check which simplex point(s) must be eliminated, and in which
		//     direction to search for the next point.
		//
		// As for convention the following named vectors are used:
		//   - 'a': the last simplex point
		//   - 'b': the previous simplex point
		//   - 'c': the pre-previous simplex point
		//   - 'd': the pre-pre-previous simplex point (just in the 4 points case)
		//
		//   - 'ao': the direction from A towards the origin
		//   - 'ab': the direction from A to B
		//   - 'ac': the direction from A to C
		//   - 'ad': the direction from A to D
		//
		//   - abc: the ABC triangle plane normal
		//   - acd: the ACD triangle plane normal
		//   - adb: the ADB triangle plane normal
		//
		// The implementation uses auto type specification instead of fully classified types just for convenience,
		// better code readability and also easier to compare to the 2D implementation.

		switch (simplex.GetSize ()) {
			case 0:
			case 1:
				DBBREAK (); // simplex must have at least 2 points

			case 2: // simplex has 2 points (a line segment, not a triangle yet)
			{
				auto a = simplex[1];
				auto b = simplex[0];

				auto ao = -a; // from point A to Origin is just negative A
				auto ab = b - a; // from point A to B

				// the Origin is in the same direction as AB
				if (ab * ao > 0) {
					//simplex = { b, a }; // simplex remains as it is
					direction = ab ^ ao ^ ab; // normal to AB towards Origin

				// the Origin is still further away
				} else {
					simplex = { a };
					direction = ao;
				}
			} break;

			case 3: // simplex has 3 points (a triangle)
			{
				auto a = simplex[2];
				auto b = simplex[1];
				auto c = simplex[0];

				auto ao = -a; // from point A to Origin is just negative A
				auto ab = b - a; // from point A to B
				auto ac = c - a; // from point A to C
				auto abc = ab ^ ac; // the triangle plane normal

				if ((abc ^ ac) * ao > 0) { // outside of the Triangle, above the AC line
					if (ac * ao > 0) { // over the AC line
						simplex = { c, a };
						direction = ac ^ ao ^ ac;
					} else {
						if (ab * ao > 0) { // over the AB line
							simplex = { b, a };
							direction = ab ^ ao ^ ab;
						} else { // the Origin is still further away
							simplex = { a };
							direction = ao;
						}
					}
				} else {
					if ((ab ^ abc) * ao > 0) { // outside of the Triangle, above the AC line
						if (ab * ao > 0) { // over the AB line
							simplex = { b, a };
							direction = ab ^ ao ^ ab;
						} else { // the Origin is still further away
							simplex = { a };
							direction = ao;
						}
					} else { // over the triangle
						if (abc * ao > 0) { // above the Triangle
							//simplex = { c, b, a }; // simplex remains as it is
							direction = abc;
						} else { // below the triangle
							simplex = { b, c, a };
							direction = -abc;
						}
					}
				}
			} break;

			case 4: // simplex has 4 points (a tetraheadron)
			{
				//                               [A]
				//                              ,|,
				//                            ,7``\'VA,
				//                          ,7`   |, `'VA,
				//                        ,7`     `\    `'VA,
				//                      ,7`        |,      `'VA,
				//                    ,7`          `\         `'VA,
				//                  ,7`             |,           `'VA,
				//                ,7`               `\       ,..ooOOTK` [B]
				//              ,7`                  |,.ooOOT''`    AV
				//            ,7`            ,..ooOOT`\`           /7
				//          ,7`      ,..ooOOT''`      |,          AV
				//         ,T,..ooOOT''`              `\         /7
				//    [C] `'TTs.,                      |,       AV
				//             `'TTs.,                 `\      /7
				//                  `'TTs.,             |,    AV
				//                       `'TTs.,        `\   /7
				//                            `'TTs.,    |, AV
				//                                 `'TTs.,\/7
				//                                      `'T`
				//                                        [D]

				auto a = simplex[3];
				auto b = simplex[2];
				auto c = simplex[1];
				auto d = simplex[0];

				auto ao = -a; // from point A to Origin is just negative A
				auto ab = b - a; // from point A to B
				auto ac = c - a; // from point A to C
				auto ad = d - a; // from point A to D

				auto abc = ab ^ ac; // the triangle plane normal
				auto acd = ac ^ ad; // the triangle plane normal
				auto adb = ad ^ ab; // the triangle plane normal

				bool above_abc = abc * ao > 0;
				bool above_acd = acd * ao > 0;
				bool above_adb = adb * ao > 0;

				auto above_planes = 0
					+ (above_abc ? 1 : 0)
					+ (above_acd ? 1 : 0)
					+ (above_adb ? 1 : 0)
					;

				switch (above_planes) {
					case 0: // inside of the tetraheadron
						return true;

					case 1: // above only one triangle
					{
						if (above_abc) {
							// do nothing
						} else if (above_acd) {
							// rotate ACD into ABC
							b = c;
							c = d;

							ab = ac;
							ac = ad;

							abc = acd;
						} else if (above_adb) {
							// rotate ADB into ABC
							c = b;
							b = d;

							ac = ab;
							ab = ad;

							abc = adb;
						} else {
							DBBREAK (); // we should not get in here
						}

						if ((abc ^ ac) * ao > 0) { // over the AC line
							simplex = { c, a };
							direction = ac ^ ao ^ ac;
						} else if ((ab ^ abc) * ao > 0) { // over the AB line
							simplex = { b, a };
							direction = ab ^ ao ^ ab;
						} else { // over the triangle
							simplex = { c, b, a };
							direction = abc;
						}
					} break;

					case 2: // above only two triangles
					{
						if (above_abc && above_acd) {
							// do nothing
						} else if (above_acd && above_adb) {
							// rotate ACD, ADB into ABC, ACD -> common edge AD into AC
							d = c;
							ac = ad;
						} else if (above_adb && above_abc) {
							// rotate ADB, ABC into ABC, ACD -> common edge AB into AC
							b = c;
							ab = ac;
						} else {
							DBBREAK (); // we should not get in here
						}

						bool over_abc = !((abc ^ ac) * ao > 0);
						bool over_acd = !((ac ^ acd) * ao > 0);

						if (over_abc) { // over one Triangle
							simplex = { c, b, a };
							direction = abc;
						} else if (over_acd) { // over the other Triangle
							simplex = { d, c, a };
							direction = acd;
						} else if (ac * ao > 0) { // over the AC lin
							simplex = { c, a };
							direction = ac ^ ao ^ ac;
						} else { // still further away
							simplex = { a };
							direction = ao;
						}
					} break;

					case 3: // above all three triangles
					{
						// it is just above the tetraheadron
						simplex = { a };
						direction = ao;
					} break;
				}
			} break;

			default:
				DBBREAK (); // we should not get in here
		}

		return false;
	}


	template<typename SupportFunction, typename VectorType>
	GJKResult<VectorType> GJKCollisionDetection (SupportFunction supportFunction, VectorType direction)
	{
		// if initial direction is zero, set it to any arbitrary axis
		if (direction.GetLengthSqr () <= 0)
			direction.x = 1;

		// get the first support point along the initial direction
		VectorType support = supportFunction (direction);

		// set the first support point as initial point of the new simplex
		GS::Array<VectorType> simplex { support };

		// search in the opposite direction
		direction = -support;

		// limit the number of cycles to avoid infinite cycles
		Int32 max_cycles = 20;

		while (--max_cycles > 0) {
			// get the next support point
			support = supportFunction (direction);

			// check if we reached past the origo
			if (support * direction < 0)
				return GJKResult<VectorType>::NoCollision (support, direction); // no collision

			// add the new support point to the simplex
			simplex.Push (support);

			// check if the current simplex contains the origin, and compute the new simplex and the new search direction if not
			if (GJKDoSimplex (simplex, direction))
				return GJKResult<VectorType>::Collision (); // collision
		}

		// cycles limit reached, returning with no collision found
		return GJKResult<VectorType>::NotFound (support, direction);
	}


	template<typename VectorType>
	GJKResult<VectorType> GJKCollisionDetection (const GS::Array<VectorType>& vertices1, const GS::Array<VectorType>& vertices2)
	{
		// get the center points to compute the initial direction
		VectorType position1 = GJKGetAveragePoint (vertices1); // not a real Center of Gravity but
		VectorType position2 = GJKGetAveragePoint (vertices2); // it's ok for GJK

		// initial direction from the center of 1st body to the center of 2nd body
		VectorType direction = position1 - position2;

		// if initial direction is zero, set it to any arbitrary axis
		if (direction.GetLengthSqr () <= 0)
			direction.x = 1;

		// run the generic GJK algorithm with the computed initial direction and specified support function lambda
		return GJKCollisionDetection ([&](const VectorType& d) { return GJKGetSupport (vertices1, vertices2, d); }, direction);
	}


}

#endif
