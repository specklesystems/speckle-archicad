#ifndef		POINTCLOUDBOX_HPP
#define		POINTCLOUDBOX_HPP

#include "PointCloudDefinitions.hpp"

namespace	PC	{

struct	POINTCLOUD_DLL_EXPORT	Box
{
	float	xMin;
	float	yMin;
	float	xMax;
	float	yMax;
	float	zMin;
	float	zMax;

	Box ();

	bool operator== (const Box& rightOp) const;
	bool operator!= (const Box& rightOp) const;

	void	GS_FORCE_INLINE	UnionPoint (float x, float y, float z, bool firstPoint)
	{
		if (firstPoint) {
			xMax = xMin = x;
			yMax = yMin = y;
			zMax = zMin = z;
		} else {
			if (xMax < x) {
				xMax = x;
			} else if (xMin > x) {
				xMin = x;
			}
			if (yMax < y) {
				yMax = y;
			} else if (yMin > y) {
				yMin = y;
			}
			if (zMax < z) {
				zMax = z;
			} else if (zMin > z) {
				zMin = z;
			}
		}
	}

	//void	GS_FORCE_INLINE	UnionPoint (const IPointCloud::Point& point, bool firstPoint);
};

}

#endif