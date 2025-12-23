// *****************************************************************************
// File:			Overlay.hpp
//
// Description:
//
// Project:			GRAPHISOFT Dialog Manager test application (DGTest)
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef OVERLAY_HPP
#define OVERLAY_HPP

// --- Includes ----------------------------------------------------------------

#include "DGGraphixDrawingLayer.hpp"
#include "DrawingItem.hpp"
#include "DGGraphixDefinitions.hpp"					// DGGRAPHIX_DLL_EXPORT


// --- Class declarations ------------------------------------------------------

namespace NewDisplay {

class DGGRAPHIX_DLL_EXPORT Overlay: public DrawingLayer
{
friend class DrawingItem;

private:
	Overlay (Surface::Impl&, bool createOnTop);
	Overlay (const Overlay&);				// disabled
	Overlay& operator= (const Overlay&);	// disabled

public:
	virtual ~Overlay ();

	void	SetAlpha (double);
	void	ShowLayer (bool);
	bool	IsLayerVisible () const;
};

}

#endif
