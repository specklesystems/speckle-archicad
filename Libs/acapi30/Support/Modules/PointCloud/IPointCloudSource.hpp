// *****************************************************************************
// File:			IPointCloudSource.hpp
//
// Description:		Pointcloud source object interface
//
// Project:			GRAPHISOFT PointCloud
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef		IPOINTCLOUDSOURCE_HPP
#define		IPOINTCLOUDSOURCE_HPP

// --- Includes ----------------------------------------------------------------

#include	"IPointCloud.hpp"

// --- IPointCloudSource -------------------------------------------------------

class	POINTCLOUD_DLL_EXPORT	IPointCloudSource
{
public:

	struct	Point
	{
		double	x, y, z;
		UInt32	argbColor;
	};

public:
	IPointCloudSource ()
	{
	}
	
	virtual ~IPointCloudSource ();

	virtual	UInt32		GetNumberOfPoints () const = 0;
	virtual	bool		GetPoints (Point* pts, UInt32 pointStartIndex, UInt32 pointEndIndex) = 0;
};


#endif	// IPOINTCLOUDSOURCE_HPP