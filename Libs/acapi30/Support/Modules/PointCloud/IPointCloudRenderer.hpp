// *****************************************************************************
// File:			IPointCloudRenderer.hpp
//
// Description:		Pointcloud renderer object interface
//					Conditionally threadsafe (no per instance threadsafety)
//
// Project:			GRAPHISOFT PointCloud
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef		IPOINTCLOUDRENDERER_HPP
#define		IPOINTCLOUDRENDERER_HPP

// --- Includes ----------------------------------------------------------------

#include "PointCloudRenderingEffects.hpp"


// --- Predeclaratinos ---------------------------------------------------------

class	IPointCloud;
class	IPointCloudClip;
class	IPointCloudRendererDDI;


// --- IPointCloudRenderer -----------------------------------------------------

class	POINTCLOUD_DLL_EXPORT	IPointCloudRenderer
{
public:
	struct	Plane
	{
		double		a;
		double		b;
		double		c;
		double		d;
	};

protected:
	virtual	void					InvokeDrawFromCallback (void* renderData) = 0;

public:

	virtual	~IPointCloudRenderer ();

	// --- Factory functions
	
	static	IPointCloudRenderer*	Create ();

	// --- Setting rendering properties
	
	virtual	void					SetViewProjectionMatrices (const float (&viewMatrix)[4*4], const float (&projMatrix)[4*4]) = 0;
	virtual	void					SetWorldMatrix (const float (&worldMatrix)[4*4]) = 0;
	virtual	void					SetClipPlanes (const GS::Array<Plane>& clipPlanes) = 0;
	virtual	void					SetPointSize (float size, float resolutionFactor) = 0;
	virtual void					SetRenderingEffect (PC::IRenderingEffect* effect) = 0;
	virtual	void					SetConstantColor (float r, float g, float b, float a) = 0;
	virtual	void					SetColorBlendFactor (float factor) = 0;
	virtual void					SetStencilReference (GS::UInt32 value) = 0;

	// --- Rendering methods
	
	virtual	void					Draw (IPointCloud* pointCloud, IPointCloudRendererDDI* pDDIImpl) = 0;
	virtual	void					Draw (IPointCloudClip* pcClip, IPointCloudRendererDDI* pDDIImpl) = 0;

	virtual	void					DrawBoundBox (IPointCloud* pointCloud, IPointCloudRendererDDI* pDDIImpl) = 0;
	virtual	void					DrawBoundBox (IPointCloudClip* pcClip, IPointCloudRendererDDI* pDDIImpl) = 0;
};


#endif	// IPOINTCLOUDRENDERER_HPP