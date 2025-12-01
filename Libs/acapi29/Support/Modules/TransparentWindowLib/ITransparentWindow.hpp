// *********************************************************************************************************************
// Description:		ITransparentWindow
//
// Module:			DG
// Namespace:
// Contact person:	DGY
//
// SG compatible
// *********************************************************************************************************************

#ifndef _ITRANSPARENTWINDOW_HPP_
#define _ITRANSPARENTWINDOW_HPP_

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "DGUtility.hpp"
#include "DGEventArgs.hpp"
#include "DGEventNotifier.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------
namespace DG {
	class Point;
	class NativePoint;
}

namespace ITracker {
	class ITransparentWindow;
}


// --- Class declarations ----------------------------------------------------------------------------------------------

namespace ITracker {

class TRANSPARENTWINDOWLIB_DLL_EXPORT MouseClickArg : public DG::EventArg
{
public:
	DG::Point		point;

	MouseClickArg ();
	virtual ~MouseClickArg ();
};


class TRANSPARENTWINDOWLIB_DLL_EXPORT TransptWindowEvents
{
public:

	DG::EventNotifier<ITransparentWindow, const MouseClickArg>	onMouseClick;
	DG::EventNotifier<ITransparentWindow, const MouseClickArg>	onMouseUp;
	DG::EventNotifier<ITransparentWindow, const MouseClickArg>	onMouseRClick;
	DG::EventNotifier<ITransparentWindow, const MouseClickArg>	onMouseRUp;
	DG::EventNotifier<ITransparentWindow, const MouseClickArg>	onMouseMove;
	DG::EventNotifier<ITransparentWindow, const DG::EventArg>	onClosed;
	DG::EventNotifier<ITransparentWindow, const DG::EventArg>	onFadeDone;
	DG::EventNotifier<ITransparentWindow, const DG::EventArg>	onRedrawRequested;
};


class TRANSPARENTWINDOWLIB_DLL_EXPORT ITransparentWindow
{

public:
	virtual  ~ITransparentWindow ();

	virtual void			SetPosition (const DG::NativePoint& pos, bool placeWindowBehindPalettes = true) = 0;	// pos is in the global coordinate space
	virtual DG::NativePoint	GetPosition (void) const = 0;
	virtual DG::Rect		GetCloseRect (void) const = 0;	// Client relative logical units
	virtual void			SetCloseRect (const DG::Rect& rect) = 0;

	virtual short 			GetHeight (void) const = 0;
	virtual short 			GetWidth (void) const = 0;
	virtual double			GetScaleFactor (void) const = 0;
	virtual double			GetResolutionFactor (void) const = 0;
	virtual void			PlaceInFrontOf (const short refDialId) = 0;
	virtual void			PlaceTopMost () = 0;

	virtual float			GetGlobalAlpha (void) const = 0;
	virtual void			SetGlobalAlpha (float inGlobalAlpha) = 0;

	virtual void			Hide () = 0;
	virtual void			Show () = 0;
	virtual bool			IsVisible () const = 0;

	virtual void			SetCursor (GSResModule cursorResModule, Int32 cursorId) = 0;
	virtual void			ResetCursor () = 0;

};


class TRANSPARENTWINDOWLIB_DLL_EXPORT ITransparentWindowImpl : public ITransparentWindow, public TransptWindowEvents
{
private:

	ITransparentWindow* impl;

protected:
	ITransparentWindowImpl (ITransparentWindow* impl = nullptr);

	void SetImpl (ITransparentWindow* impl);

public:
	virtual  ~ITransparentWindowImpl ();

	virtual void			SetPosition (const DG::NativePoint& pos, bool placeWindowBehindPalettes = true)  override;	// pos is in the global coordinate space
	virtual DG::NativePoint	GetPosition (void) const override;

	virtual DG::Rect		GetCloseRect (void) const  override;	// Client relative logical units
	virtual void			SetCloseRect (const DG::Rect& rect) override;

	virtual short 			GetHeight (void) const  override;
	virtual short 			GetWidth (void) const override;
	virtual double			GetScaleFactor (void) const  override;
	virtual double			GetResolutionFactor (void) const override;
	virtual void			PlaceInFrontOf (const short refDialId)  override;
	virtual void			PlaceTopMost () override;

	virtual float			GetGlobalAlpha (void) const  override;
	virtual void			SetGlobalAlpha (float inGlobalAlpha)  override;

	virtual void			Hide ()  override;
	virtual void			Show ()  override;
	virtual bool			IsVisible () const  override;

	virtual void			SetCursor (GSResModule, Int32) override;
	virtual void			ResetCursor () override;

};

}

#endif	//
