// *****************************************************************************
// File:			DGGraphixWin.hpp
//
// Description:		DG Graphix public interface for configuration and diagnostic
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	DGGRAPHIXWIN_HPP
#define	DGGRAPHIXWIN_HPP

// --- Includes ----------------------------------------------------------------

#include "DGGraphixDefinitions.hpp"

// --- Initializing functions --------------------------------------------------


// --- Configuration class -----------------------------------------------------

namespace	DGGraphixWin	{

class	DGGRAPHIX_DLL_EXPORT	Config
{

public:
	enum AccelerationType {						// Used interface for drawing acceleration
		Software			=	0,
		Direct3D11,

		NumOfInterfaceTypes
	};

	enum AccelerationLevel {					// Requested acceleration level
		PureSoftware						=	0,
		HwAndSwMultiDraw					=	1,
		PureHardware						=	2,
		PureHardwareOld						=	3	// (Now unused, needed for compatibility reasons)
	};

public:
	struct RequestedConfig {
		AccelerationLevel			hwAccLevel;
		UInt32						FSAASubPixels;
		UInt32						FSAAQuality;
		bool						enableSwAntialias;
		bool						enablevSync;
		bool						roundedLineCoordinatesByDefault;
		bool						showFps;
	};

	struct DrawingDescriptor {
		RequestedConfig				requestedConfig;

		// Current acceleration configuration
		AccelerationType			interfaceType;
		UInt32						numOfDetectedAdapters;
		bool						antialiasEnabled;

		struct PerDeviceData {
			bool					deviceIsInUse;
		};
		GS::Array<PerDeviceData>	deviceData;
	};

private:
	//bool					ApplyDefaultDrawingConfig ();

public:
	Config ();
	~Config ();

	RequestedConfig			GetDefaultConfig (bool disableHwAcceleration);
	DrawingDescriptor		GetDrawingConfig ();
	
	// Apply new drawing configuration
	bool					ApplyDrawingConfig (const RequestedConfig& requestedConfig);
	
	// Use these if one of the underlying subsystems (D3D9) must also be restarted
	void					BeginRestart ();
	bool					EndRestart (const RequestedConfig& requestedConfig);
};



// --- Diagnostic Class --------------------------------------------------------

class	DGGRAPHIX_DLL_EXPORT	Diag
{
public:

	enum Event	{
		HwAccelerationIsUnusable					=	0,			// Hardware acceleration is unusable

		HwAccAutomaticallyDisabledDueToDeviceError	=	1,			// Hardware acceleration is automatically disabled on at least one adapter,
																	// due to a device error
		AntialiasingAutomaticallyDisabled			=	2,			// Antialiasing is automatically disabled because of insufficient video memory
																	// resources
		PartialAccelerationFallbackOccured			=	3,			// At least one surface was forced to software mode because of insufficient video memory
																	// resources

		NumOfEvents
	};

public:
	Diag ();
	~Diag ();

	bool					HasNewEventHappened () const ;
	bool					HasEventHappened (Event event) const;

	UInt32					GetResetCount () const;

};


// --- Externs -----------------------------------------------------------------

extern	Config		DGGRAPHIX_DLL_EXPORT	dgGraphixConfig;
extern	Diag		DGGRAPHIX_DLL_EXPORT	dgGraphixDiag;

}	// namespace DGGraphixWin

#endif
