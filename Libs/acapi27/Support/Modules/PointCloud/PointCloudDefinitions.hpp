// *********************************************************************************************************************
// File:			PointCloudDefinitions.hpp
//
// Description:		Common defintions of the PointCloud Module
//
// Project:			GRAPHISOFT PointCloud
//
// Namespace:
//
// Contact person:	DG
//
// SG compatible
// *********************************************************************************************************************

#ifndef	POINTCLOUDDEFINITIONS_HPP
#define	POINTCLOUDDEFINITIONS_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"
#include "Array.hpp"

// --- Module export defines -------------------------------------------------------------------------------------------

#if defined (POINTCLOUD_DLL_COMPILE)
	#define POINTCLOUD_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define POINTCLOUD_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif	// POINTCLOUDDEFINITIONS_HPP
