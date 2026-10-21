// ******************************************************************************
// File:			LowLevelContext.hpp
//
// Description:		Main interface for common low level GPU interface
//
// Contact person:	DG
//
// SG compatible
// ******************************************************************************

#ifndef	LOWLEVELCONTEXT_HPP
#define	LOWLEVELCONTEXT_HPP

// --- Includes ----------------------------------------------------------------

#include "GraphixDefinitions.hpp"
#include "LowLevelObjects.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace NewDisplay {

class	NativeContextBase;

}

namespace	Graphix	{

class	ResourceFactory;

}

namespace	Graphix	{


// --- LowLevelContext ---------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	LowLevelContext
{
public:
	enum	PrimitiveTopology
	{
		PointList	=	0,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip,

		NumOfPrimitiveTopologies,
		TopologyUndefined
	};

public:
	virtual		~LowLevelContext ();

	virtual		ResourceFactory*		GetFactory () const = 0;
	virtual		ContextID				GetContextId () const = 0;

	virtual		void		PushState () = 0;		// To be removed; only for OpenGL
	virtual		void		PopState () = 0;

	virtual		UInt32		GetMaxElementVertices () const = 0;

	virtual		void		GetViewportCorretionMatrix (float (&matrix)[4*4]) const = 0;
	virtual		Viewport	GetViewPort () const = 0;
	virtual		void		SetViewPort (const Viewport* viewPort) = 0;
	virtual		double		GetResolutionFactor () const = 0;

	virtual		void		SetDepthStencilState (const DepthStencilState* pState, UInt8 stencilRef) = 0;
	virtual		void		SetDepthStencil (const DepthStencil* pDesc, UInt8 stencilRef) = 0;
	virtual		void		SetBlendState (const BlendState* pState) = 0;
	virtual		void		SetBlend (const Blend* pDesc) = 0;
	virtual		void		SetRasterizerState (const RasterizerState* pState) = 0;
	virtual		void		SetRasterizer (const Rasterizer* pDesc) = 0;
	
	virtual		void		SetProgram (const Program* pProgram) = 0;
	virtual		void		SetVertexBuffers (UInt32 startSlot, UInt32 numBuffers, VertexBuffer* const * vBuffers, const UInt32* strides) = 0;
	virtual		void		SetIndexBuffer (IndexBuffer* indexBuffer) = 0;

	virtual		void		Clear (float r, float g, float b, float a, float z, UInt8 stencil, bool clearColor, bool clearDepth, bool clearStencil) = 0;

	virtual		void		Draw (PrimitiveTopology topology, UInt32 vertexCount, UInt32 startVertexIndex) = 0;
	virtual		void		DrawInstanced (PrimitiveTopology topology, UInt32 vertexCountPerInstance, UInt32 instanceCount, UInt32 startVertexIndex, UInt32 startInstanceLocation) = 0;
	virtual		void		DrawIndexed (PrimitiveTopology topology, UInt32 minVertex, UInt32 numOfVertices, UInt32 indexCount, UInt32 startIndexLocation/*, Int32 baseVertexLocation*/) = 0;
	virtual		void		DrawIndexedInstanced (PrimitiveTopology topology, UInt32 indexCountPerInstance, UInt32 instanceCount,
												UInt32 startIndexLocation, UInt32 baseVertexLocation, UInt32 startInstanceLocation) = 0;

};


// --- Functions ---------------------------------------------------------------

GRAPHIX_DLL_EXPORT	LowLevelContext*		CreateOpenGLLowLevelContext (double resolutionFactor);

} // namespace Graphix

#endif	// LOWLEVELCONTEXT_HPP