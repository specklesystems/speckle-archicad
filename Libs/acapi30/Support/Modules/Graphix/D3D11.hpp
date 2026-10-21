// ******************************************************************************
// File:			D3D11.hpp
//
// Description:		Main functions for Direct3D11 support
//
// Contact person:	DG
//
// SG compatible
// ******************************************************************************

// --- Includes -----------------------------------------------------------------

#include "GraphixDefinitions.hpp"
#include "D3D11Interface.h"

// --- Predeclarations ----------------------------------------------------------

class	ID3D11Core;
class	ID3D11Blitter;
class	ID3D11BaseDeviceContext;

namespace	NewDisplay	{

class	INativeContextImpl;

}


namespace	Graphix	{

class	LowLevelContext;

};

// --- D3D11 functions ---------------------------------------------------------

namespace D3D11	{

	// --- General functions
	
	GRAPHIX_DLL_EXPORT		bool								IsD3D11Enabled ();

	GRAPHIX_DLL_EXPORT		bool								AreThereAcquiredResources (UInt32 deviceIndex);
	GRAPHIX_DLL_EXPORT		void								ReleaseAllCachedResources (UInt32 deviceIndex);
	GRAPHIX_DLL_EXPORT		void								ReleaseAllCachedResources ();

	
	// --- Singleton objects ---
	
	// D3D 11 Core (threadsafe for factoring, non-threadsafe for rendering)
	GRAPHIX_DLL_EXPORT		ID3D11Core*							GetD3D11Core ();
	
	// Built-in renderers
	GRAPHIX_DLL_EXPORT		ID3D11Blitter*						GetD3D11Blitter ();


	// --- Instantable objects ---

	// --- D3D11 Device contexts

	// ImmediateDeviceContext (non-threadsafe)
	GRAPHIX_DLL_EXPORT		ID3D11BaseDeviceContext*			CreateImmediateDeviceContext (UInt32 deviceIndex);
	
	// SafeDeviceContext (conditionally threadsafe)
	GRAPHIX_DLL_EXPORT		ID3D11BaseDeviceContext*			CreateSafeDeviceContext (UInt32 deviceIndex);
	
	// --- Built-in renderers
	
	// NativeContext (conditionally threadsafe)
	GRAPHIX_DLL_EXPORT		NewDisplay::INativeContextImpl*		CreateD3D11Context (ID3D11BaseDeviceContext* deviceContext, float scaleFactor,
																					UInt32 deviceIndex, const RECT& fullRect, const RECT& subRect, HRGN dirtyRegion,
																					ID3D11RenderTargetView*	pRenderTargetView, ID3D11ShaderResourceView* pTextureView, ID3D11DepthStencilView* pDepthStencilView,
																					const RECT& stencilDirtyRect, UInt8 maxStencil,
																					const RECT* defaultClipRect, bool defaultClipIsRect,
																					bool usingPerPixelAlpha, bool usingAntialias,
																					bool roundedLineCoordsByDefault, UInt32 clearColor);

	// LowLevelContext (conditionally threadsafe)
	GRAPHIX_DLL_EXPORT		Graphix::LowLevelContext*			CreateD3D11LowLevelContext (ID3D11BaseDeviceContext* context, ID3D11RenderTargetView* pRenderTargetView, ID3D11DepthStencilView* pDepthStencilView,
																							const RECT& fullRect, const RECT& subRect, float resolutionFactor);

};