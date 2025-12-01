// *****************************************************************************
// File:			GraphixWin.hpp
//
// Description:		Graphix public interface for configuration and diagnostic
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	GRAPHIXWIN_HPP
#define	GRAPHIXWIN_HPP

// --- Includes ----------------------------------------------------------------

#include "GraphixDefinitions.hpp"

// --- Initializing functions --------------------------------------------------


// --- Configuration class -----------------------------------------------------

namespace	GraphixWin	{

class	GRAPHIX_DLL_EXPORT	Config
{
public:
	struct RConfig {
		
		struct	HWCommon
		{
			// General keys 
			bool						enableSingleDevice;
			bool						enableVerticalRetrace;
			UInt32						singleDeviceIndex;				// Adapter (graphic card) index for single devicing
			Int32						vmUsageLimit;

			// Debug keys
			Int32						debugMaxVidMemPerDevice;
			Int32						debugMaxVidMemPerDeviceForImages;
			bool						reportVMUsage;
			bool						enableWARPDevice;
		} hwCommon;
		
		
		struct D3D11
		{
			UInt32						nativeContextVertexBuffSize;
			UInt32						nativeContextIndexBuffSize;
		} d3d11;


		struct Sw
		{
		} sw;

		bool							hwAccelerationEnabled;
		bool							d3d11Enabled;
		bool							trueLineWeightEnabled;
	};

public:
	Config ();
	~Config ();

	static	RConfig					GetConfig ();

	static	void					SetConfig (const RConfig& inConfig);

	static	bool					IsTrueLineWeightEnabled();	

private:
	static	bool					isInitialized;
};


// --- Diagnostic Class --------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	Diag
{
public:

	// --- Known Driver Bugs for DX9
	enum DriverBug	{
		ATIFillAndDraw				=	0,		// Filling and drawing on an AA surface for the first time
												//  (can) fill(s) the surface with zeroes on ATIs
		StretchRectFromNAAToAA,					// StretchRect from a non-antialiased surface to an antialiased one
												//  can fail if the src surface is "too large"
		DepthStencilDiscarded,					// This one is not really clear; Z/Stencil surfaces sometimes seem to be discarded
												//  after rendering the scene, even if the "nodiscard" flag is specified for these buffers
		BlitThroughDynamicTexture,				// On some hardware (or drivers) "DrawPrimitive" commands are not flushed out before a dynamic texture
												//  (the one that is in usage during the primitive rendering in question) is updated, so a
												//  BeginScene/EndScene pair is needed to force flushing

		BlitThroughDynamicTextureTotallyWrong,  // Drawing via dynamic textures does not work at all

		ATIWrongShader,							// On some ATI hardware the shader used for drawing colorkeyed images runs
												//  incorrectly

		NumOfDriverBugs
	};

	enum Error	{
		//D3D9HwTestsFailed			=	1,		// Testing hardware capabilities did not passed (one of) the fundamental tests; TODO: for DX11?

		NumOfErrors
	};

public:
	Diag ();
	~Diag ();

	bool					IsDriverBugDetected (DriverBug bug) const;

	UInt32					GetErrorFlags () const;
	void					SetErrorFlag (UInt32 flag);

	bool					ShouldBeRestarted () const;
};

// --- Functions ---------------------------------------------------------------

void				GRAPHIX_DLL_EXPORT	Restart ();
const Config		GRAPHIX_DLL_EXPORT &GetGraphixConfig ();

// --- Publics -----------------------------------------------------------------

extern	Config		GRAPHIX_DLL_EXPORT	graphixConfig;
extern	Diag		GRAPHIX_DLL_EXPORT	graphixDiag;

extern	bool							detectedBugs[GraphixWin::Diag::NumOfDriverBugs];

}		// namespace GraphixWin

#endif	// GRAPHIXWIN_HPP
