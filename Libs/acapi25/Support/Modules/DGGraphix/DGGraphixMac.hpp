// *****************************************************************************
// File:			DGGraphixMac.hpp
//
// Description:		DG Graphix public interface for configuration and diagnostic
//
// Contact person:	DGY
//
// SG compatible
// *****************************************************************************

#ifndef	DGGRAPHIXMAC_HPP
#define	DGGRAPHIXMAC_HPP

#include "DGGraphixDefinitions.hpp"
#include "MacSettings.hpp"

// --- Initializing functions --------------------------------------------------


// --- Configuration class -----------------------------------------------------

namespace	DGGraphixMac	{

class	DGGRAPHIX_DLL_EXPORT	Config
{
private:
	DGGraphixMac::Settings			currConfig;

public:
	Config ();
	~Config ();
	
	bool			IsEqual2DOptions (const DGGraphixMac::Settings& newSettings);
	void			ApplyDrawingConfig (const DGGraphixMac::Settings& newSettings);
	
};


extern	Config		DGGRAPHIX_DLL_EXPORT	dgGraphixConfig;


}

#endif
