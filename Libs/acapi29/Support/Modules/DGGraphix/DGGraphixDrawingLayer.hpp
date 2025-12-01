// *****************************************************************************
// File:			DGGraphixDrawingLayer.hpp
//
// Description:
//
// Project:			GRAPHISOFT Dialog Manager test application (DGTest)
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef DRAWINGLAYER_HPP
#define DRAWINGLAYER_HPP

// --- Includes ----------------------------------------------------------------

#include "CountedPtr.hpp"
#include "Surface.hpp"
#include "Array.hpp"
#include "DGGraphixDefinitions.hpp"					// DGGRAPHIX_DLL_EXPORT
#include "IBlit.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class Point;
	class Rect;
}


// --- Class declarations ------------------------------------------------------

namespace NewDisplay {

class DGGRAPHIX_DLL_EXPORT DrawingLayer: public Surface
{
public:
	class DGGRAPHIX_DLL_EXPORT GuardedDraw
	{
	public:
		DrawingLayer*		layerToGuard;
		Surface::ImplRef	drawingLayerImpl;

	public:
		GuardedDraw (DrawingLayer* layerToGuard);
		virtual ~GuardedDraw ();
	};
	typedef GS::CountedPtr<GuardedDraw> DrawGuard;

private:
	DrawingLayer (const DrawingLayer&);				// disabled
	DrawingLayer& operator= (const DrawingLayer&);	// disabled

private:
	virtual	NativeContext		GetContext () override;
	virtual void				ReleaseContext () override;
	virtual	void				BeginDraw ();
	virtual void				EndDraw ();

protected:
	DrawingLayer (Surface::ImplRef implRef);

public:
	virtual ~DrawingLayer ();

	OffscreenSurface*			CreateOffscreenSurface (UInt32 width, UInt32 height, bool useZBuffer = false, bool antialiasForcedOff = false);

	virtual bool				IsInDraw ();
	DrawGuard					GetDrawGuard ();
	void						BeginDraw_INTERNAL ();
	void						EndDraw_INTERNAL ();

	virtual UInt32				GetWidth () const override;
	virtual UInt32				GetHeight () const override;
};


class DGGRAPHIX_DLL_EXPORT OffscreenSurface: public Surface
{
private:
	OffscreenSurface (const OffscreenSurface&);				// disabled
	OffscreenSurface& operator= (const OffscreenSurface&);	// disabled

private:
	virtual	NativeContext		GetContext () override;
	virtual void				ReleaseContext () override;

public:
	OffscreenSurface (Surface::Impl&, UInt32, UInt32, bool useZBuffer = false, bool antialiasForcedOff = false);
	virtual	~OffscreenSurface ();

	virtual UInt32				GetWidth () const override;
	virtual UInt32				GetHeight () const override;
};

}

#endif
