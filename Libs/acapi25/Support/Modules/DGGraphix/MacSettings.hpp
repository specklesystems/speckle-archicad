// *****************************************************************************
// File:			MacSettings.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef _MACSETTINGS_HPP_
#define _MACSETTINGS_HPP_

// --- Includes ----------------------------------------------------------------

#include "DGGraphixDefinitions.hpp"		// DGGRAPHIX_DLL_EXPORT

namespace	DGGraphixMac {

// --- Class declarations ------------------------------------------------------

class DGGRAPHIX_DLL_EXPORT Settings
{
	static bool	disableMSAA;
	
	static void MSAATest ();
	
private:
	bool		antialias2D;
	bool		antialias3D;
	bool		roundLineCoordinates;
	bool		useOpenGL;
	short		acceleration;

public:
	Settings();

	bool		GetAntialias2D() const;
	void		SetAntialias2D(bool);
	bool		GetAntialias3D() const;
	void		SetAntialias3D(bool);
	bool		GetRoundLineCoordinates() const;
	void		SetRoundLineCoordinates(bool);
	short		GetAcceleration() const;
	void		SetAcceleration(short);
	void		Set (const Settings& source);
	bool		UseOpenGL ();
	bool		IsMSAADisabled () const;
};

	extern	Settings		DGGRAPHIX_DLL_EXPORT	settings;
}

#endif
