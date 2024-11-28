// *****************************************************************************
// File:			PointCloudUtils.hpp
//
// Description:		PointCloud utils
//					(non-threadsafe, can only be used in main thread)
//
// Project:			GRAPHISOFT PointCloud
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	POINTCLOUDUTILS_HPP
#define	POINTCLOUDUTILS_HPP

// --- Includes ----------------------------------------------------------------

#include "IPointCloudClip.hpp"
#include "PCMatrix.hpp"
#include "PCPlane.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace	NewDisplay	{

class	NativeContext;

}


namespace	PC	{

// --- Utils class -------------------------------------------------------------

class	POINTCLOUD_DLL_EXPORT	Utils
{
public:

	// --- Hit test functions --------------------------------------------------

	// Tests if there is at least one point of the pointcloud which is one the positive side on all planes
	static	bool	HitTest (IPointCloud* pointCloud, const GS::Array<PC::Plane>& planes, PC::Point* detectedPoint);

	static	bool	HitTest (IPointCloudClip* pointCloudClip, const GS::Array<PC::Plane>& planes, PC::Point* detectedPoint);
	
	// Tests if there is at least one point of the pointcloud in the rect ((left, top, right, bottom) given in projection space)
	// with the specified transformation matrices
	static	bool	HitTest	(IPointCloud* pointCloud, double left, double top, double right, double bottom,
							 const PC::Matrix* worldMatrix, const PC::Matrix* viewMatrix, const PC::Matrix* projMatrix,
							 PC::Point* detectedPoint);

	static	bool	HitTest	(IPointCloudClip* pointCloudClip, double left, double top, double right, double bottom,
							 const PC::Matrix* worldMatrix, const PC::Matrix* viewMatrix, const PC::Matrix* projMatrix,
							 PC::Point* detectedPoint);


	// --- Drawing functions ----------------------------------------------------
	
	// Draws a pointcloud into a NativeContext
	static	bool	Draw	(IPointCloud* pointCloud, NewDisplay::NativeContext& context,
							 const PC::Matrix* worldMatrix, const PC::Matrix* viewMatrix, const PC::Matrix* projMatrix,
							 Int32 viewPortLeft, Int32 viewPortTop, Int32 viewPortRight, Int32 viewPortBottom,
							 UInt32 clipRectLeft, UInt32 clipRectTop, UInt32 clipRectRight, UInt32 clipRectBottom,
							 float pointSize = 0.0f);

	static	bool	Draw	(IPointCloudClip* pointCloudClip, NewDisplay::NativeContext& context,
							 const PC::Matrix* worldMatrix, const PC::Matrix* viewMatrix, const PC::Matrix* projMatrix,
							 Int32 viewPortLeft, Int32 viewPortTop, Int32 viewPortRight, Int32 viewPortBottom,
							 UInt32 clipRectLeft, UInt32 clipRectTop, UInt32 clipRectRight, UInt32 clipRectBottom,
							 float pointSize = 0.0f);

	// --- Draws a pointcloud or pointcloud clip into a NativeContext using orthogonal projection
	//     Camera coordinate system is x = (1, 0, 0), y = (0, 1, 0), z = (0, 0, -1)
	//     Transformed boundbox is scaled into the viewportrect then the clipped against the cliprect

	static	bool	DrawOrtho (IPointCloud* pointCloud, const PC::Matrix& transformation, NewDisplay::NativeContext& context,
								Int32 viewPortLeft, Int32 viewPortTop, Int32 viewPortRight, Int32 viewPortBottom,
								UInt32 clipRectLeft, UInt32 clipRectTop, UInt32 clipRectRight, UInt32 clipRectBottom,
								float pointSize = 0.0f);

	static	bool	DrawOrtho (IPointCloudClip* pointCloudClip, const PC::Matrix& transformation, NewDisplay::NativeContext& context,
								Int32 viewPortLeft, Int32 viewPortTop, Int32 viewPortRight, Int32 viewPortBottom,
								UInt32 clipRectLeft, UInt32 clipRectTop, UInt32 clipRectRight, UInt32 clipRectBottom,
								float pointSize = 0.0f);
};

} // namespace PC


#endif	// POINTCLOUDUTILS_HPP