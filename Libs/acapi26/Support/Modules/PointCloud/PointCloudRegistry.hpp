// *****************************************************************************
// File:			PointCloudRegistry.hpp
//
// Description:		Point cloud registry manager (threadsafe)
//
// Project:			GRAPHISOFT PointCloud
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	POINTCLOUDREGISTRY
#define POINTCLOUDREGISTRY

// --- Includes ----------------------------------------------------------------

#include "PointCloudDefinitions.hpp"

// --- PointCloudRegistry ------------------------------------------------------

class	POINTCLOUD_DLL_EXPORT	PointCloudRegistry
{
public:	
	static	float		GetDefaultPointSize ();
	static	float		GetMaxPointSize ();
	static	bool		IsAsynchronousTreeBuildEnabled ();
	static	bool		IsMultiThreadedRenderingEnabled ();
	static	bool		IsFileMappingEnabled ();
	static	UInt32		GetMaxVideoMemWorkingSet ();
	static	UInt32		GetPointNumRenderingThreshold ();
};

#endif	// POINTCLOUDREGISTRY