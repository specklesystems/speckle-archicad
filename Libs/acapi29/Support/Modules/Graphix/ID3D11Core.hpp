// *****************************************************************************
// File:			ID3D11Core.hpp
//
// Description:		GRAPHISOFT D3D11 Core interface
//
// Contact person:	DG
//
// SG compatible
// ***************************************************************************** 

#ifndef	ID3D11CORE_HPP
#define	ID3D11CORE_HPP

// --- Includes ----------------------------------------------------------------

#include "GraphixDefinitions.hpp"		// GRAPHIX_DLL_EXPORT
#include <windows.h>
#include "D3D11Interface.h"

// --- Definitions -------------------------------------------------------------

#define	INVALID_D3D11_ID		0xFFFFFFFF

// --- Predeclarations ---------------------------------------------------------

class	IDXGI;

// --- D3D11 Core observer interface (must be threadsafe) ----------------------

class	ID3D11CoreObserver
{
public:
	virtual		bool	D3D11CanReleaseAllocatedResources () = 0;
	virtual		bool	D3D11CoreInitBegin () = 0;
	virtual		bool	D3D11CoreInitEnd () = 0;
	virtual		void	DeviceIsAboutToBeDeleted (UInt32 deviceIndex) = 0;
};


// --- D3D11 Core interface ----------------------------------------------------

class GRAPHIX_DLL_EXPORT	ID3D11Core
{
public:

	// --- Core management functions (main thread only) ------------------------

	virtual	bool				CanBeReinitialized (bool includeDXGI) const = 0;
	virtual	bool				Reinitialize (bool includeDXGI) = 0;

	// --- Devices and contexts related functions (threadsafe) -----------------

	virtual	UInt32				GetAdapterIndex (UInt32 deviceIdx) const = 0;
	virtual	UInt32				GetIdOfImmediateContext (UInt32 deviceIdx) const = 0;
	virtual	UInt32				GetDeviceIndexFromContextId (UInt32 contextIdx) const = 0;
	virtual	UInt32				CreateDeferredContextOnDevice (UInt32 deviceIdx) = 0;
	virtual	bool				IsDeviceUsable (UInt32 deviceIdx) = 0;
	virtual void				ExcludeDevice (UInt32 deviceIdx) = 0;

	virtual	bool				Lock (UInt32 deviceIdx, void* lockId) = 0;
	virtual	void				Unlock (UInt32 deviceIdx) = 0;
	virtual	void				ClearLockId (UInt32 deviceIdx, void* lockId) = 0;

	// --- Enumerating functions for created devices and device contexts -------

	virtual	bool				IsSingleDeviceModeUsed () const = 0;
	virtual	UInt32				GetNumberOfDevices () const = 0;
	virtual	UInt32				GetNumberOfContextsCreatedOnDevice (UInt32 deviceIdx) const = 0;
	virtual	UInt32				GetIdOfContext (UInt32 deviceIdx, UInt32 contextEnumIdx) const = 0;
	virtual	D3D_FEATURE_LEVEL	GetD3DFeatureLevelOfDevice (UInt32 deviceIdx) const = 0;
	virtual D3D_DRIVER_TYPE		GetD3DDriverTypeOfDevice (UInt32 deviceIdx) const = 0;

	// --- Device check related functions  -------------------------------------

	virtual HRESULT				CheckFormatSupport (UInt32 deviceIdx, DXGI_FORMAT format, UINT* pFormatSupport) = 0;


	// === Factoring functions (threadsafe) ====================================

	// --- Swapchain related functions -----------------------------------------

	virtual		IDXGISwapChain*		CreateSwapchain (UInt32 deviceIdx, const DXGI_SWAP_CHAIN_DESC& pDesc) = 0;
	virtual		void				ReleaseSwapchain (IDXGISwapChain* pSwapChain) = 0;

	// --- Shader management functions -----------------------------------------

	virtual	bool				CreatePixelShader (UInt32 deviceIdx, const void* shaderBinaryData, UInt32 shaderBinarySize, ID3D11PixelShader** pShader, HRESULT* pHResult = nullptr) = 0;
	virtual void				ReleasePixelShader (ID3D11PixelShader* shader) = 0;
	virtual	bool				CreateVertexShaderAndInputLayout (UInt32 deviceIdx, const void* shaderBinaryData, UInt32 shaderBinarySize,
																	const D3D11_INPUT_ELEMENT_DESC* vertexLayout, UInt32 numOfVertexElements,
																	ID3D11VertexShader** pShader, ID3D11InputLayout** pInputLayout, HRESULT* hResult = nullptr) = 0;
	virtual	void				ReleaseVertexShaderAndInputLayout (ID3D11VertexShader* shader, ID3D11InputLayout* inputLayout) = 0;
	virtual	bool				CreateGeometryShader (UInt32 deviceIdx, const void* shaderBinaryData, UInt32 shaderBinarySize, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader, HRESULT* pHResult = nullptr) = 0;
	virtual	void				ReleaseGeometryShader (ID3D11GeometryShader* shader) = 0;


	// --- Texture functions ---------------------------------------------------

	virtual	ID3D11Texture2D*	CreateTexture2D (UInt32 deviceIdx, const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, HRESULT* pHResult = nullptr) = 0;
	virtual	void				ReleaseTexture2D (ID3D11Texture2D* pTexture2D) = 0;

	virtual	UInt32				GetApproxSizeOfTexture2D (ID3D11Texture2D* pTexture2D) = 0;
	virtual	void				GetMaxTextureDimensions (UInt32 deviceIdx, UInt32& maxWidth, UInt32& maxHeight) = 0;

	// --- Buffer functions ----------------------------------------------------

	virtual	ID3D11Buffer*		CreateBuffer (UInt32 deviceIdx, const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, HRESULT* hResult = nullptr) = 0;
	virtual	void				ReleaseBuffer (ID3D11Buffer* pBuffer) = 0;

	// --- View management functions -------------------------------------------

	virtual	ID3D11RenderTargetView*		CreateRenderTargetView (UInt32 deviceIdx, ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, HRESULT* pHResult = nullptr) = 0;
	virtual	void						ReleaseRenderTargetView (ID3D11RenderTargetView* pResource) = 0;
	virtual	ID3D11DepthStencilView*		CreateDepthStencilView (UInt32 deviceIdx, ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, HRESULT* pHResult = nullptr) = 0;
	virtual	void						ReleaseDepthStencilView (ID3D11DepthStencilView* pResource) = 0;
	virtual	ID3D11ShaderResourceView*	CreateShaderResourceView (UInt32 deviceIdx, ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, HRESULT* pHResult = nullptr) = 0;
	virtual	void						ReleaseShaderResourceView (ID3D11ShaderResourceView* pResource) = 0;

	// --- Render state object management functions ----------------------------

	virtual	ID3D11BlendState*			CreateAlphaBlendingState (UInt32 deviceIdx, const D3D11_BLEND_DESC& blendingDesc, HRESULT* pHResult = nullptr) = 0;
	virtual	ID3D11DepthStencilState*	CreateDepthStencilState (UInt32 deviceIdx, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc, HRESULT* pHResult = nullptr) = 0;
	virtual	ID3D11RasterizerState*		CreateRasterizerState (UInt32 deviceIdx, const D3D11_RASTERIZER_DESC& rasterizerDesc, HRESULT* pHResult = nullptr) = 0;
	virtual ID3D11SamplerState*			CreateSamplerState (UInt32 deviceIdx, const D3D11_SAMPLER_DESC& samplerDesc, HRESULT* pHResult = nullptr) = 0;
	
	virtual	void						ReleaseAlphaBlendingState (ID3D11BlendState* pState) = 0;
	virtual	void						ReleaseDepthStencilState (ID3D11DepthStencilState* pState) = 0;
	virtual	void						ReleaseRasterizerState (ID3D11RasterizerState* pState) = 0;
	virtual	void						ReleaseSamplerState (ID3D11SamplerState*) = 0;

	// Do not release these stock instances!
	virtual	ID3D11BlendState*			GetCachedAlphaBlendingState (UInt32 deviceIdx, const D3D11_BLEND_DESC& blendingDesc) = 0;
	virtual	ID3D11DepthStencilState*	GetCachedDepthStencilState (UInt32 deviceIdx, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc) = 0;
	virtual	ID3D11RasterizerState*		GetCachedRasterizerState (UInt32 deviceIdx, const D3D11_RASTERIZER_DESC& rasterizerDesc) = 0;
	virtual ID3D11SamplerState*			GetCachedSamplerState (UInt32 deviceIdx, const D3D11_SAMPLER_DESC& samplerDesc) = 0;

	
	// === Rendering functions (non-threadsafe) ================================
	
	// --- Resource mapping functions ------------------------------------------

	virtual	bool				Map (UInt32 contextId, ID3D11Resource* pResource, UInt32 subresource, D3D11_MAP mapType, UInt32 mapFlags, D3D11_MAPPED_SUBRESOURCE* pMappedResource, HRESULT* pHResult = nullptr) = 0;
	virtual	void				Unmap (UInt32 contextId, ID3D11Resource* pResource, UInt32 subresource) = 0;

	// --- Render state management functions -----------------------------------

	virtual	void				SetAlphaBlending (UInt32 contextId, ID3D11BlendState* pAlphaBlendState, UInt32 sampleCoverage) = 0;
	virtual	void				SetDepthStencil (UInt32 contextId, ID3D11DepthStencilState* pDepthStencilState, UInt32 stencilRef) = 0;
	virtual	void				SetRasterizer (UInt32 contextId, ID3D11RasterizerState* pRasterizerState) = 0;
	virtual	void				SetViewPort (UInt32 contextId, const D3D11_VIEWPORT& desc) = 0;

	virtual	void				SetPixelShader (UInt32 contextId, ID3D11PixelShader* pPixelShader)= 0;
	virtual	void				SetPixelShaderResources (UInt32 contextId, UInt32 startSlot, UInt32 numViews, ID3D11ShaderResourceView *const *ppShaderResourceViews) = 0;
	virtual	void				SetPixelShaderConstantBuffers (UInt32 contextId, UInt32 startSlot, UInt32 numBuffers, ID3D11Buffer* const* ppConstantBuffers) = 0;
	virtual	void				SetPixelShaderSamplers (UInt32 contextId, UInt32 startSlot, UInt32 numSamplers, ID3D11SamplerState *const *ppSamplers) = 0;
	virtual	void				SetVertexShaderAndInputLayout (UInt32 contextId, ID3D11VertexShader* pVertexShader, ID3D11InputLayout* pInputLayout) = 0;
	virtual	void				SetVertexShaderResources (UInt32 contextId, UInt32 startSlot, UInt32 numViews, ID3D11ShaderResourceView *const *ppShaderResourceViews) = 0;
	virtual	void				SetVertexShaderConstantBuffers (UInt32 contextId, UInt32 startSlot, UInt32 numBuffers, ID3D11Buffer* const* ppConstantBuffers) = 0;
	virtual	void				SetGeometryShader (UInt32 contextId, ID3D11GeometryShader* pGeometryShader) = 0;
	virtual	void				SetGeometryShaderResources (UInt32 contextId, UInt32 startSlot, UInt32 numViews, ID3D11ShaderResourceView *const *ppShaderResourceViews) = 0;
	virtual	void				SetGeometryShaderConstantBuffers (UInt32 contextId, UInt32 startSlot, UInt32 numBuffers, ID3D11Buffer* const* ppConstantBuffers) = 0;
	virtual	void				SetRenderTargets (UInt32 contextId, UInt32 numViews, ID3D11RenderTargetView *const * ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView) = 0;
	virtual	void				SetScissorRects (UInt32 contextId, UInt32 numRects, const D3D11_RECT *pRects) = 0;
	virtual	void				SetVertexBuffers (UInt32 contextId, UInt32 startSlot, UInt32 numBuffers, ID3D11Buffer *const *ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets) = 0;
	virtual	void				SetIndexBuffer (UInt32 contextId, ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, UInt32 offset) = 0;

	// --- Render state management functions using fast internal object caching ----

	virtual	void				SetAlphaBlending (UInt32 contextId, const D3D11_BLEND_DESC& blending, UInt32 sampleCoverage) = 0;
	virtual	void				SetDepthStencil (UInt32 contextId, const D3D11_DEPTH_STENCIL_DESC& desc, UInt32 stencilRef) = 0;
	virtual	void				SetRasterizer (UInt32 contextId, const D3D11_RASTERIZER_DESC& desc) = 0;

	// --- Resource copy functions ---------------------------------------------

	virtual	void				ResolveSubresource (UInt32 contextId, ID3D11Resource* pDstResource, UInt32 dstSubresource, ID3D11Resource* pSrcResource, UInt32 srcSubresource, DXGI_FORMAT format) = 0;

	virtual	void				CopyResource (UInt32 contextId, ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource) = 0;
	virtual	void				CopySubresourceRegion (UInt32 contextId, ID3D11Resource* pDstResource, UInt32 dstSubresource, UInt32 dstX, UInt32 dstY, UInt32 dstZ,
														ID3D11Resource* pSrcResource, UInt32 srcSubresource, const D3D11_BOX *pSrcBox) = 0;

	virtual	void				UpdateSubresource (UInt32 contextId, ID3D11Resource *pDstResource, UInt32 dstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UInt32 srcRowPitch, UInt32 srcDepthPitch) = 0;

	// --- Drawing functions -------------------------------------------------------

	virtual	void				ClearDepthStencilView (UInt32 contextId, ID3D11DepthStencilView* pDepthStencilView, UINT clearFlags, FLOAT depth, UINT8 stencil) = 0;
	virtual	void				ClearRenderTargetView (UInt32 contextId, ID3D11RenderTargetView* pRenderTargetView, const FLOAT (&colorRGBA)[4]) = 0;

	virtual	void				SetPrimitiveTopology (UInt32 contextId, D3D11_PRIMITIVE_TOPOLOGY topology) = 0;
	virtual	void				Draw (UInt32 contextId, UInt32 vertexCount, UInt32 startVertexLocation) = 0;
	virtual	void				DrawIndexed (UInt32 contextId, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation) = 0;
	virtual	void				DrawIndexedInstanced (UInt32 contextId, UInt32 indexCountPerInstance, UInt32 instanceCount,
													  UInt32 startIndexLocation, Int32 baseVertexLocation, UInt32 startInstanceLocation) = 0;
	virtual	void				DrawInstanced (UInt32 contextId, UInt32 vertexCountPerInstance, UInt32 instanceCount, UInt32 startVertexLocation, UInt32 startInstanceLocation) = 0;

	
	// --- Misc (threadsafe) -------------------------------------------------------

	virtual void				FlushAndWait (UInt32 deviceIdx) = 0;
	virtual	void				RegisterObserver (ID3D11CoreObserver* observer) = 0;
	virtual	void				UnregisterObserver (ID3D11CoreObserver* observer) = 0;
};

#endif	// !ID3D11CORE_HPP