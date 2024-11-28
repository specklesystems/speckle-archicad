#if !defined CONVEX_HULL2D_CREATOR
#define CONVEX_HULL2D_CREATOR

#include "Point2DData.h"
#include "Point3DData.h"
#include "Box2DData.h"
#include "PagedArray.hpp"

class GEOMETRY_DLL_EXPORT ConvexHull2DCreator {
	public:
		ConvexHull2DCreator();

		void AddPoint		(double x, double y);
		void AddPoint		(double x, double y, double z); //the 3rd coord won't be used by the algorithm
		void AddPoint		(const Point2D& c);
		void AddPoint		(const Point3D& c);
		void ClearPoints	(void);

		GS::PagedArray<Point3D> CalcConvexHull ();

	private:
		Box2DData box;
		GS::PagedArray<Point3D> originalPoints;

		class Point;
		class AngleComparator;
};

#endif
