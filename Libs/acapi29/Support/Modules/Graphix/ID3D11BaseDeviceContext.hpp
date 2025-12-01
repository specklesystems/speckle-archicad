// *****************************************************************************
// File:			ID3D11BaseDeviceContext.hpp
//
// Description:		GRAPHISOFT D3D11 IBaseDeviceContext interface
//
// Contact person:	DG
//
// SG compatible
// ***************************************************************************** 

#ifndef	ID3D11BASEDEVICECONTEXT_HPP
#define	ID3D11BASEDEVICECONTEXT_HPP

// --- Includes ----------------------------------------------------------------

#include "ID3D11Core.hpp"

// --- ID3D11BaseDeviceContext -------------------------------------------------

class	GRAPHIX_DLL_EXPORT	ID3D11BaseDeviceContext
{
protected:
	ID3D11Core*		core;
	UInt32			contextId;

public:
	ID3D11BaseDeviceContext (ID3D11Core* core):
		core		(core),
		contextId	(INVALID_D3D11_ID)
		{
		}

	virtual	~ID3D11BaseDeviceContext ()
	{
	}


	ID3D11Core*					GetCore () const { return core; }

	UInt32						GetContextId () const { return contextId; }
	UInt32						GetDeviceIndex () const { return core->GetDeviceIndexFromContextId (contextId); }

	// --- Resource mapping functions --------------------------------------------------------

	virtual	bool				Map (ID3D11Resource* pResource, UInt32 subresource, D3D11_MAP mapType, UInt32 mapFlags, D3D11_MAPPED_SUBRESOURCE* pMappedResource, HRESULT* pHResult = nullptr) = 0;
	virtual	void				Unmap (ID3D11Resource* pResource, UInt32 subresource) = 0;

	// --- Render state management functions -------------------------------------------------

	virtual	void				SetAlphaBlending (ID3D11BlendState* pAlphaBlendState, UInt32 sampleCoverage) = 0;
	virtual	void				SetDepthStencil (ID3D11DepthStencilState* pDepthStencilState, UInt32 stencilRef) = 0;
	virtual	void				SetRasterizer (ID3D11RasterizerState* pRasterizerState) = 0;
	virtual	void				SetViewPort (const D3D11_VIEWPORT& desc) = 0;

	virtual	void				SetPixelShader (ID3D11PixelShader* pPixelShader) = 0;
	virtual	void				SetPixelShaderResources (UInt32 startSlot, UInt32 numViews, ID3D11ShaderResourceView *const *ppShaderResourceViews) = 0;
	virtual	void				SetPixelShaderConstantBuffers (UInt32 startSlot, UInt32 numBuffers, ID3D11Buffer* const* ppConstantBuffers) = 0;
	virtual	void				SetPixelShaderSamplers (UInt32 startSlot, UInt32 numSamplers, ID3D11SamplerState* const *ppSamplers) = 0;
	virtual	void				SetVertexShaderAndInputLayout (ID3D11VertexShader* pVertexShader, ID3D11InputLayout* pInputLayout) = 0;
	virtual	void				SetVertexShaderResources (UInt32 startSlot, UInt32 numViews, ID3D11ShaderResourceView *const *ppShaderResourceViews) = 0;
	virtual	void				SetVertexShaderConstantBuffers (UInt32 startSlot, UInt32 numBuffers, ID3D11Buffer* const* ppConstantBuffers) = 0;
	virtual	void				SetGeometryShader (ID3D11GeometryShader* pGeometryShader) = 0;
	virtual	void				SetGeometryShaderResources (UInt32 startSlot, UInt32 numViews, ID3D11ShaderResourceView *const *ppShaderResourceViews) = 0;
	virtual	void				SetGeometryShaderConstantBuffers (UInt32 startSlot, UInt32 numBuffers, ID3D11Buffer* const* ppConstantBuffer) = 0;
	virtual	void				SetRenderTargets (UInt32 numViews, ID3D11RenderTargetView *const * ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView) = 0;
	virtual	void				SetScissorRects (UInt32 numRects, const D3D11_RECT *pRects) = 0;
	virtual	void				SetVertexBuffers (UInt32 startSlot, UInt32 numBuffers, ID3D11Buffer *const *ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets) = 0;
	virtual	void				SetIndexBuffer (ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, UInt32 offset) = 0;

	// --- Render state management functions using fast internal object caching --------------

	virtual	void				SetAlphaBlending (const D3D11_BLEND_DESC& blending, UInt32 sampleCoverage) = 0;
	virtual	void				SetDepthStencil (const D3D11_DEPTH_STENCIL_DESC& desc, UInt32 stencilRef) = 0;
	virtual	void				SetRasterizer (const D3D11_RASTERIZER_DESC& desc) = 0;

	// --- Resource copy functions ----------------------------------------------------------

	virtual	void				ResolveSubresource (ID3D11Resource* pDstResource, UInt32 dstSubresource, ID3D11Resource* pSrcResource, UInt32 srcSubresource, DXGI_FORMAT format) = 0;

	virtual	void				CopyResource (ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource) = 0;
	virtual	void				CopySubresourceRegion (ID3D11Resource* pDstResource, UInt32 dstSubresource, UInt32 dstX, UInt32 dstY, UInt32 dstZ,
														ID3D11Resource* pSrcResource, UInt32 srcSubresource, const D3D11_BOX *pSrcBox) = 0;

	virtual	void				UpdateSubresource (ID3D11Resource *pDstResource, UInt32 dstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UInt32 srcRowPitch, UInt32 srcDepthPitch) = 0;

	// --- Drawing functions -----------------------------------------------------------------

	virtual	void				ClearDepthStencilView (ID3D11DepthStencilView* pDepthStencilView, UINT clearFlags, FLOAT depth, UINT8 stencil) = 0;
	virtual	void				ClearRenderTargetView (ID3D11RenderTargetView* pRenderTargetView, const FLOAT (&colorRGBA)[4]) = 0;

	virtual	void				SetPrimitiveTopology (D3D11_PRIMITIVE_TOPOLOGY topology) = 0;
	virtual	void				Draw (UInt32 vertexCount, UInt32 startVertexLocation) = 0;
	virtual	void				DrawIndexed (UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation) = 0;
	virtual	void				DrawIndexedInstanced (UInt32 indexCountPerInstance, UInt32 instanceCount, UInt32 startIndexLocation, Int32 baseVertexLocation, UInt32 startInstanceLocation) = 0;
	virtual	void				DrawInstanced (UInt32 vertexCountPerInstance, UInt32 instanceCount, UInt32 startVertexLocation, UInt32 startInstanceLocation) = 0;

	virtual	void				Flush () = 0;

};

#endif	// ID3D11BASEDEVICECONTEXT_HPP