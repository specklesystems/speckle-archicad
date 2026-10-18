// *********************************************************************************************************************
// Description:		Forward declarations for using PointCloudView
//
// Module:			PointCloudManager
// Namespace:		PointCloud
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#if !defined (POINTCLOUDVIEWFWD_HPP)
#define POINTCLOUDVIEWFWD_HPP

#pragma once

// from GSRoot
#include "SharedPtr.hpp"

namespace PointCloud {

	class PointCloudView;
	typedef GS::ConstSharedPtr<PointCloudView>	ConstViewPtr;

}	// namespace PointCloud

#endif // POINTCLOUDVIEWFWD_HPP
