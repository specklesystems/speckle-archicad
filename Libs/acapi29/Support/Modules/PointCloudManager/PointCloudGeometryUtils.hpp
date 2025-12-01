// *********************************************************************************************************************
// Description:		Utility functions for interoperability with the Geometry module.
//
// Module:			PointCloudManager
// Namespace:		PointCloud
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#ifndef POINTCLOUDGEOMETRYUTILS_HPP
#define POINTCLOUDGEOMETRYUTILS_HPP

// --- Includes	--------------------------------------------------------------------------------------------------------

// from PointCloud
#include "PCMatrix.hpp"
#include "PointCloudBox.hpp"

// from PointCloudManager
#include "PointCloudManagerDefinitions.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

struct TRANMAT;

namespace Geometry {
	template<USize RowCount, USize ColumnCount, class ElementType>
	class Matrix;
}

// --- Function declarations -------------------------------------------------------------------------------------------

namespace PointCloud {
	POINTCLOUDMANAGER_DLL_EXPORT 
	PC::Matrix	ToPointCloudTransformation (const TRANMAT& geometryTransformation);
	
	POINTCLOUDMANAGER_DLL_EXPORT
	PC::Matrix	ToPointCloudTransformation (const Geometry::Matrix<4, 4, double>& geometryTransformation);

	POINTCLOUDMANAGER_DLL_EXPORT
	PC::Box		TransformBoundingBox (const PC::Box& box, const PC::Matrix& trafo);
} // namespace PointCloud

#endif // POINTCLOUDGEOMETRYUTILS_HPP