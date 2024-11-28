// *********************************************************************************************************************
// File:			PointCloudLib.hpp
//
// Description:		Main include of the Point Cloud Library
//
// Project:			GRAPHISOFT Point Cloud
//
// Namespace:
//
// Contact person:	DG
//
// SG compatible
// *********************************************************************************************************************

#ifndef	POINTCLOUDLIB_HPP
#define	POINTCLOUDLIB_HPP

#include	"PointCloudDefinitions.hpp"
#include	"Location.hpp"

// --- Module export defines -------------------------------------------------------------------------------------------

bool	POINTCLOUD_DLL_EXPORT CCALL		PointCloudLibInit ();
void	POINTCLOUD_DLL_EXPORT CCALL		PointCloudLibExit ();
void	POINTCLOUD_DLL_EXPORT CCALL		PointCloudLibSetTemporaryFolder (const IO::Location* tempFolder = nullptr);


#endif	// POINTCLOUDLIB_HPP