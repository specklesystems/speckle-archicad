// *****************************************************************************
// File:			IPointCloudRendererDDI.hpp
//
// Description:		DDI interface for pointcloud renderer
//
// Project:			GRAPHISOFT PointCloud
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	IPOINTCLOUDRENDERERDDI_HPP
#define	IPOINTCLOUDRENDERERDDI_HPP

// --- Includes ----------------------------------------------------------------

#include "PointCloudDefinitions.hpp"
#include "IPointCloudRenderer.hpp"
#include "PointCloudRenderingEffects.hpp"


// --- Constant definitions ----------------------------------------------------

#define	MAX_CLIPPLANES		10
#define	QUEUE_TERMINATOR	0xFFFFFFFF

// --- Predeclarations ---------------------------------------------------------

namespace	Graphix
{
	// LowLevel DDI
	class	LowLevelContext;

	// FrLevel DDI
	class	IRenderingContext;
	class	IResourceFactory;
	class	IGraphicsPipeline;
	class	IRenderPass;

	struct   Viewport;
}

// --- IPointCloudRendererDDI --------------------------------------------------

class	POINTCLOUD_DLL_EXPORT	IPointCloudRendererDDI
{
public:
	struct	Vertex
	{
		float	x,y,z;
		UInt32	color;
	};


	struct	Display
	{
		UInt32	xRes;
		UInt32	yRes;
	};


	struct PointBatchData
	{
		void*			pointCloudId;
		UInt32			vertexRangeStart;
		UInt32			vertexRangeEnd;
		UInt32			indexNum;
		const UInt32*	indexData;
		bool			indexed;
	};


	struct Interval
	{
		UInt32			vertexRangeStart;
		UInt32			vertexRangeEnd;
	};

	struct QueueData
	{
		volatile	UInt32			queueLockBegin;
		volatile	UInt32			queueLockEnd;
		UInt32						queueLength;
		Interval*					queue;
		volatile	bool			renderingCancelled;
	};

public:
	virtual	~IPointCloudRendererDDI ();

	// --- Factory functions for built-in implementations
	
	static	IPointCloudRendererDDI*		CreateLowLevelPointCloudRendererDDI (Graphix::LowLevelContext* lowLevelContext);
	static	IPointCloudRendererDDI*		CreateFrLevelPointCloudRendererDDI (Graphix::IResourceFactory* pFactory, Graphix::IGraphicsPipeline* pPipeLine,
																			Graphix::IRenderingContext* pContext, float resolutionFactor, int universeId);

	// --- Methods for executing

	virtual	bool						InvokeRendererFromCallback (IPointCloudRenderer* pCallback, void* renderData) = 0;

	// --- Methods for querying rendering environment and capabilities

	virtual	Display						GetDisplay () = 0;
	virtual	UInt32						GetMaxSizeOfPointBatch () const = 0;
	virtual	UInt32						GetMaxSizeOfIndexedPointBatch () const = 0;
	virtual	bool						IsMultiThreadedQueuedRenderingSupported () const = 0;
	virtual bool						IsRenderingEffectSupported (PC::IRenderingEffect* effect) const = 0;

	// --- Methods for setting rendering properties

	virtual	void						SetMatrices (float (&worldMatrix)[4*4], float (&viewMatrix)[4*4], float (&projMatrix)[4*4], float (&invViewMatrix)[4*4]) = 0;
	virtual	void						SetClipPlanes (const GS::Array<IPointCloudRenderer::Plane>& clipPlanes) = 0;
	virtual	void						SetPointSize (float size) = 0;
	virtual void						SetRenderingEffect (PC::IRenderingEffect* effect) = 0;
	virtual	void						SetConstantColor (float r, float g, float b, float a) = 0;	// Colorblending applies after rendering effect
	virtual	void						SetColorBlendFactor (float factor) = 0;
	virtual void						SetViewport (const Graphix::Viewport& viewport) = 0;
	virtual void						SetRenderPass (Graphix::IRenderPass* renderpass) = 0;

	// --- Methods for rendering

	virtual	bool						BeginDrawSession (void* pointCloudId, void* pcIndexingId, UInt32 numOfPoints, UInt32 stencilRef, void* points) = 0;
	virtual	void						DrawPointRange (const PointBatchData& data) = 0;
	virtual	void						DrawPointRangeIndexed (const PointBatchData& data) = 0;
	virtual void						DrawTriangles (const Vertex* triangles, UInt32 numOfTriangles) = 0;
	virtual	void						EnterRenderingLoop (QueueData& queueData) = 0;
	virtual	void						EndDrawSession (void* pointCloudId, void* pcIndexingId) = 0;
};


#endif	// IPOINTCLOUDRENDERERDDI_HPP