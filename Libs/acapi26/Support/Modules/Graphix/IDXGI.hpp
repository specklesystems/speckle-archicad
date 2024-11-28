// *****************************************************************************
// File:			IDXGI.hpp
//
// Description:
//
// Project:			GRAPHISOFT DXGI Core interface
//
// Contact person:	DG
//
// SG compatible
// ***************************************************************************** 


#ifndef	IDXGI_HPP
#define	IDXGI_HPP

#include "GraphixDefinitions.hpp"		// GRAPHIX_DLL_EXPORT
#include <windows.h>

// --- DXGI Core observer interface (must be threadsafe) -------------------------------

class	IDXGICoreObserver
{
public:
	virtual		bool	CanReleaseAllocatedDXGIResources () = 0;
	virtual		bool	ReleaseAllocatedDXGIResources () = 0;
};

// --- Forward declarations ------------------------------------------------------------

interface IDXGIAdapter1;
interface IDXGIOutput;
interface IDXGISwapChain;
struct DXGI_SWAP_CHAIN_DESC;

// --- DXGI Core interface ------------------------------------------------------------

class GRAPHIX_DLL_EXPORT	IDXGI
{
public:

	// --- Core management functions --------------------------------------------------

	virtual		bool				CanBeReinitialized () const = 0;
	virtual		bool				Reinitialize () = 0;
	
	// --- Adapter related functions --------------------------------------------------
	
	virtual		bool				IsCurrent () const = 0;
	virtual		UInt32				GetNumberOfAdapters () const = 0;
	virtual		IDXGIAdapter1*		GetAdapter (UInt32 adapterIdx) const = 0;
	virtual		UInt32				GetNumberOfOutputs (UInt32 adapterIdx) const = 0;
	virtual		IDXGIOutput*		GetOutput (UInt32 adapterIdx, UInt32 outputIdx) const = 0;

	// --- Swapchain related functions -------------------------------------------------

	virtual		IDXGISwapChain*		CreateSwapchain (IUnknown *pDevice, const DXGI_SWAP_CHAIN_DESC& pDesc) const = 0;
	virtual		void				ReleaseSwapchain (IDXGISwapChain* pSwapChain) const = 0;

	// --- Misc ------------------------------------------------------------------------

	virtual		void				RegisterObserver (IDXGICoreObserver* observer) = 0;
	virtual		void				UnregisterObserver (IDXGICoreObserver* observer) = 0;
};


// --- DXGI Core functions -------------------------------------------------------------

namespace	DXGI	{

GRAPHIX_DLL_EXPORT			IDXGI*		GetIDXGI ();

}


#endif	IDXGI_HPP