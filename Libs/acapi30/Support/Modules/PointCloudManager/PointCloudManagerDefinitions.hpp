// *********************************************************************************************************************
// Description:		Common declarations and definitions related to PointCloudManager module
//					
// Module:			PointCloudManager
// Namespace:		PointCloud
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#if !defined (POINTCLOUDDEMANAGERFINITIONS_HPP)
#define POINTCLOUDDEMANAGERFINITIONS_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"
#include "SharedPtr.hpp"
#include "UniString.hpp"
#include "GSGuid.hpp"
#include "Pair.hpp"

// --- Module export defines -------------------------------------------------------------------------------------------

#if defined (POINTCLOUDMANAGER_DLL_COMPILE)
#define POINTCLOUDMANAGER_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
#define POINTCLOUDMANAGER_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif


// --- Type definitions ------------------------------------------------------------------------------------------------

namespace PC {
	typedef GS::Guid							ContentId;
	typedef	GS::UniString						PointSourceId;
	typedef	GS::Guid							ClipDataId;
	typedef GS::Pair<PointSourceId, ClipDataId> ClipId;
}

namespace PointCloud {
	class PointCloudCachable;
	class PointCloudClipCachable;
	class PointCloudClipDataCachable;

	typedef GS::ConstSharedPtr<PointCloudCachable>			ConstPointCloudPtr;
	typedef GS::ConstSharedPtr<PointCloudClipCachable>		ConstPointCloudClipPtr;
	typedef GS::ConstSharedPtr<PointCloudClipDataCachable>	ConstPointCloudClipDataPtr;
}

#endif // POINTCLOUDDEMANAGERFINITIONS_HPP