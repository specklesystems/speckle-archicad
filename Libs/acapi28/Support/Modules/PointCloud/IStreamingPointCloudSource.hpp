// *****************************************************************************
// File:			IStreamingPointCloudSource.hpp
//
// Description:		Streaming pointcloud source object interface
//
// Project:			GRAPHISOFT PointCloud
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef		ISTREAMINGPOINTCLOUDSOURCE_HPP
#define		ISTREAMINGPOINTCLOUDSOURCE_HPP

// --- Includes ----------------------------------------------------------------

#include	"IPointCloud.hpp"

// --- IStreamingPointCloudSource ----------------------------------------------

class	POINTCLOUD_DLL_EXPORT	IStreamingPointCloudSource
{
public:

	struct	Point
	{
		double	x, y, z;
		UInt32	argbColor;
	};

	// --- Streaming callback

	class	POINTCLOUD_DLL_EXPORT	Callback
	{
	public:
		virtual ~Callback ();

		virtual	bool	Append (const Point* points, UInt32 numberOfPoints) = 0;
	};

public:
	IStreamingPointCloudSource ()
	{
	}
	
	virtual ~IStreamingPointCloudSource ();

	virtual	UInt32		GetNumberOfPoints () const = 0;			// Return 0 if the exact number is unknown
	virtual	bool		DoStreaming (Callback& callback) = 0;
};


POINTCLOUD_DLL_EXPORT	IStreamingPointCloudSource*	CreateASCIIReader (UInt32 pcIndex);

#endif	// ISTREAMINGPOINTCLOUDSOURCE_HPP