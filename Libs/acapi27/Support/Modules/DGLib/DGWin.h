// *********************************************************************************************************************
// File:			DGWin.h
//
// Description:		Windows only external functions
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	BM
//
// SG compatible
// *********************************************************************************************************************

#ifndef DGWIN_H
#define DGWIN_H

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

#include "DG.h"
#include "DGWDPIScale.hpp"

#if defined (__cplusplus)
	extern "C" {
#endif


// --- Definitions & Macros --------------------------------------------------------------------------------------------

#define DG_TEST_WAITCURSOR	(WM_APP + 200)

#define WM_DGCOMMAND		(WM_APP + 0x0500)
#define WM_DGSETTOPMOST		(WM_APP + 0x0501)
#define DG_WM_DPICHANGED	(WM_APP + 0x0502)
#define DG_WM_TTMOUSEMOVE	(WM_APP + 0x0503)
#define DG_WM_TTMOUSELEAVE	(WM_APP + 0x0504)
#define DG_WM_SETFOCUS		(WM_APP + 0x0505)
#define DG_WM_KILLFOCUS		(WM_APP + 0x0506)


// --- Predefinitions --------------------------------------------------------------------------------------------------

struct DGDialData;


// --- Drawing Item callback interface ---------------------------------------------------------------------------------

class	DrawingItemCallback
{
public:
	virtual void		BeginPartialUpdate (HWND drawingItemWnd, const RECT* updateRect) = 0;
	virtual void		EndPartialUpdate (HWND drawingItemWnd) = 0;

	virtual void		BeginNormalUpdate (HWND drawingItemWnd, const RECT* updateRect) = 0;
	virtual void		EndNormalUpdate (HWND drawingItemWnd) = 0;
};


// --- User control callback definition --------------------------------------------------------------------------------

typedef		bool (CCALL UCSTYLECALLBACK)	(DWORD* wStyle, DWORD* wExStyle);


// --- Exported functions ----------------------------------------------------------------------------------------------

DG_DLL_EXPORT short CCALL	DGGetAndSetDialogRect (HWND dialWnd, GSResModule dialResModule, Int32 dialResId, short dialType, DGDialData* dialData);

DG_DLL_EXPORT void CCALL	DGSaveDialogRect (HWND dialWnd, GSResModule dialResModule, Int32 dialResId, short dialType, DGDialData* dialData);

DG_DLL_EXPORT bool CCALL	DGSetUserControlStylesCallBack (short ucId, UCSTYLECALLBACK *ucStyleCallback);

DG_DLL_EXPORT HWND CCALL	DGGetFrameWindow (void);

DG_DLL_EXPORT HWND CCALL	DGGetDialogItemWindow (short dialId, short item);

DG_DLL_EXPORT bool CCALL	DGIsThemingAvailable (void);

DG_DLL_EXPORT bool CCALL	DGIsDesktopCompositionEnabled (void);

DG_DLL_EXPORT void CCALL	DGSetPopupOpenState (bool state);

DG_DLL_EXPORT void CCALL	DGSetDrawingItemCallbackInterface (short dialId, short item, DrawingItemCallback* drawingItemCallback);

DG_DLL_EXPORT Int32 CCALL	DGScaleValue (Int32 value, UInt32 toDPI, UInt32 fromDPI = 96);

DG_DLL_EXPORT Int32 CCALL	DGScaleValueP2L (Int32 value, UInt32 fromDPI);

DG_DLL_EXPORT UInt32 CCALL	DGGetDPIForFrameWindow (void);

DG_DLL_EXPORT UInt32 CCALL	DGGetDPIForWindow (HWND hWnd);

DG_DLL_EXPORT UInt32 CCALL	DGGetDPIForDialog (HWND hDialogWnd);

DG_DLL_EXPORT UInt32 CCALL	DGGetDPIForDialogItem (HWND hDialogItemWnd);

DG_DLL_EXPORT UInt32 CCALL	DGGetDPIForDesktopRect (const RECT& rect);


// --- Inline SendMessageW32 for 32/64-bit programming -----------------------------------------------------------------

inline Int32	SendMessageW32 (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return  TruncateTo32Bit (SendMessageW (hWnd, Msg, wParam, lParam));
}

// --- class NestedMessageLoopGuard ------------------------------------------------------------------------------------

class DG_DLL_EXPORT NestedMessageLoopGuard
{
	UInt32				mOptions;
	GS::AtomicCounter	mStoredCnt;
public:
	enum Options {
		NoRestrictions		= 0x00,
		SuspendPanelIdles	= 0x01,
		ReenablePanelIdles	= 0x02
	};
	NestedMessageLoopGuard (UInt32 options);
	~NestedMessageLoopGuard (void);

private:
	NestedMessageLoopGuard (const NestedMessageLoopGuard&); // Disabled
	void operator= (const NestedMessageLoopGuard&); // Disabled
};


// --- class Offscreen -------------------------------------------------------------------------------------------------

namespace DG {

class DG_DLL_EXPORT Offscreen
{
private:
	HDC		hMemDC;
	HBITMAP	hMemBmp;
	HBITMAP	hOldBmp;
	Int32	width;
	Int32	height;

	Offscreen (const Offscreen& source);	// Disable
	bool 	operator== (const Offscreen& source);	// Disable

public:
	Offscreen ():
		hMemDC (NULL),
		hMemBmp (NULL),
		hOldBmp (NULL),
		width (0),
		height (0)
	{
	}

	~Offscreen ()
	{
		if (hMemDC != NULL && hOldBmp != NULL) {
			SelectObject (hMemDC, hOldBmp);
		}
		if (hMemBmp != NULL) {
			DeleteObject (hMemBmp);
		}
		if (hMemDC != NULL) {
			DeleteDC (hMemDC);
		}
	}

	HDC		GetDC (HDC hDC, Int32 _width, Int32 _height)
	{
		if (_width == 0 || _height == 0) {
			return hDC;
		}
		if (hMemDC == NULL) {
			hMemDC = CreateCompatibleDC (hDC);
		}
		if (hMemDC != NULL) {
			if (hMemBmp == NULL || (hMemBmp != NULL && (width != _width || height != _height))) {
				if (hMemBmp != NULL) {
					SelectObject (hMemDC, hOldBmp);
					DeleteObject (hMemBmp);
					hOldBmp = NULL;
				}
				hMemBmp = CreateCompatibleBitmap (hDC, _width, _height);
				if (hMemBmp != NULL) {
					hOldBmp = (HBITMAP) SelectObject (hMemDC, hMemBmp);
					width = _width;
					height = _height;
				} else {
					width = 0;
					height = 0;
				}
			}
			return hMemDC;
		}
		return hDC;
	}

	void	Blit (HDC hDC, Int32 left, Int32 top)
	{
		if (hMemDC != NULL && hMemBmp != NULL) {
			BitBlt (hDC, left, top, width, height, hMemDC, 0, 0, SRCCOPY);
		}
	}
};

} // namespace DG


// --- class OffscreenImage --------------------------------------------------------------------------------------------

class DG_DLL_EXPORT OffscreenImage
{
private:
	HDC		hMemDC;
	int		width;
	int		height;
	HBITMAP	hOldBmp;
	HBRUSH	hBkgBrush;
	bool	isValid;

public:
	OffscreenImage (HDC dc, int width, int height, HBRUSH hBrush);
	~OffscreenImage ();

	bool	IsValidForSize (int width, int height) const;
	void	ValidateForSize (HDC hDC, int width, int height);
	void	SetValid (void);
	void	Invalidate (void);
	void	SetBkgBrush (HBRUSH hBrush);

	HDC		GetDC (void);
};


DG_DLL_EXPORT bool IsLayeredWindowEnabled ();

#if defined (_WIN64)

typedef	LONG_PTR	WindowLong;

#else

typedef	LONG		WindowLong;

#endif

#if defined (_MSC_VER)
#pragma warning (disable: 4311)
#endif

inline WindowLong	PtrToWindowLong (void* p) {
	return  (WindowLong) p;
}

#if defined (_MSC_VER)
#pragma warning (default: 4311)
#endif

#if defined (__cplusplus)
	}
#endif

namespace DG {

DG_DLL_EXPORT DG::DPIScale&	CCALL	GetDPIScale (void);

} // DG namespace

#endif
