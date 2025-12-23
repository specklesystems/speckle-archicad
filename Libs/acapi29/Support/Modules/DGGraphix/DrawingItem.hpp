// *****************************************************************************
// File:			DrawingItem.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef DRAWINGITEM_HPP
#define DRAWINGITEM_HPP

// --- Includes ----------------------------------------------------------------

#include "CountedPtr.hpp"
#include "DGUserItem.hpp"
#include "DGGraphixDrawingLayer.hpp"
#include "DGGraphixDefinitions.hpp"					// DGGRAPHIX_DLL_EXPORT
#include "Color.hpp"
#include "Ref.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace NewDisplay {
	class Overlay;
	class NativeImage;
}


// --- Class declarations ------------------------------------------------------

namespace NewDisplay {

class DGGRAPHIX_DLL_EXPORT DrawingItem:	public DG::UserItem,
										public DrawingLayer
{
public:
	enum AccelerationStatus
	{
		AS_Unknown		=	0,
		AS_Software,
		AS_Mixed,
		AS_Hardware
	};

	struct StatusInformation
	{
		AccelerationStatus	currentAccelerationStatus;
	};

public:

	class DGGRAPHIX_DLL_EXPORT GuardedUpdate
	{
	private:
		DrawingItem*	drawingItem;
		ImplRef			drawingItemImpl;

	public:
		GuardedUpdate (DrawingItem* drawingItem);
		virtual ~GuardedUpdate ();

		void Release ();
	};
	typedef GS::CountedPtr<GuardedUpdate> UpdateGuard;

private:
	DrawingItem (const DrawingItem&);				// disabled
	DrawingItem& operator= (const DrawingItem&);	// disabled

protected:
	DrawingItem (const DG::Panel& panel, short item, bool acceleration);
	DrawingItem (const DG::Panel& panel, const DG::Rect& rect, bool acceleration);

public:
	DrawingItem (const DG::Panel& panel, short item);
	DrawingItem (const DG::Panel& panel, const DG::Rect& rect);
	virtual ~DrawingItem ();

	Overlay*			CreateOverlay (bool createOnTop = true);
	NativeImage			CreateCompatibleImage (UInt32 width, UInt32 height) const;

	UpdateGuard			GetUpdateGuard ();

	void				CompactResources ();

	void				SettingsChanged ();

	// the return value true indicates that BeginDraw-EndDraw would restore the whole content of the drawing
	bool				IsCompositedContentValid () const;

	void				BeginFPSMeasure ();
	float				EndFPSMeasure ();

	virtual NewDisplay::NativeImage CaptureToNativeImage () const override;

#ifdef WINDOWS
	StatusInformation	GetStatusInformation () const;
#endif

	void				Scroll (Int32 horizontalScroll, Int32 verticalScroll, const NewDisplay::NativeImage& verticalImage, const NewDisplay::NativeImage& horizontalImage);

};

class DGGRAPHIX_DLL_EXPORT DrawingItem3D : public DrawingItem
{
public:
	virtual ~DrawingItem3D ();

	DrawingItem3D (const DG::Panel& panel, short item, bool acceleration);
	DrawingItem3D (const DG::Panel& panel, const DG::Rect& rect, bool acceleration);

	void				SetAcceleration (bool acceleration);


};


}

#endif
