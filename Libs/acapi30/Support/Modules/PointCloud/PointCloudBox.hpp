#ifndef		POINTCLOUDBOX_HPP
#define		POINTCLOUDBOX_HPP

#include "PointCloudDefinitions.hpp"

namespace PC {

struct POINTCLOUD_DLL_EXPORT Box
{
	float xMin = 0.0f;
	float yMin = 0.0f;
	float xMax = 0.0f;
	float yMax = 0.0f;
	float zMin = 0.0f;
	float zMax = 0.0f;

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