// *********************************************************************************************************************
// File:			DGWDPIScale.hpp
//
// Description:		User interface scaling functions for high DPI display modes.
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	VM
// *********************************************************************************************************************

#if !defined  DGWDPISCALE_HPP
#define  DGWDPISCALE_HPP

// Includes ------------------------------------------------------------------------------------------------------------

#include "DG.h"
#include "DGUtility.hpp"
#include "HashTable.hpp"
#include "Win32Interface.hpp"

// Predeclarations

struct DGInitData;

// --- Windows 8 types from ShellScalingApi.h --------------------------------------------------------------------------

#if !defined (_MONITOR_DPI_TYPE)
typedef enum _MONITOR_DPI_TYPE {
	MDT_EFFECTIVE_DPI	= 0,
	MDT_ANGULAR_DPI		= 1,
	MDT_RAW_DPI			= 2,
	MDT_DEFAULT			= MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;

typedef enum PROCESS_DPI_AWARENESS {
	PROCESS_DPI_UNAWARE = 0,
	PROCESS_SYSTEM_DPI_AWARE = 1,
	PROCESS_PER_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

#endif

typedef HRESULT (WINAPI* GetDpiForMonitorProc) (HMONITOR hmonitor, MONITOR_DPI_TYPE dpiType, UINT* dpiX, UINT* dpiY);
typedef HRESULT (WINAPI* SetProcessDpiAwarenessProc) (PROCESS_DPI_AWARENESS);
typedef BOOL (WINAPI* SetProcessDPIAwareProc) (VOID);
typedef HANDLE (WINAPI* SetThreadDpiAwarenessContextProc) (HANDLE dpiContext);
typedef BOOL (WINAPI* EnableNonClientDpiScalingProc) (HWND hWnd);
typedef int (WINAPI* GetSystemMetricsForDpiProc) (int nIndex, UINT dpi);
typedef BOOL (WINAPI* AdjustWindowRectExForDpiProc) (LPRECT lpRect, DWORD dwStyle, BOOL bMenu, DWORD dwExStyle, UINT dpi);


namespace DG {

// === MonitorInfo =====================================================================================================

struct MonitorInfo
{
	RECT	rect;
	UInt32	dpi;

	MonitorInfo (const RECT& rect, UInt32 dpi);

	bool	operator!= (const MonitorInfo& monitorInfo);

	RECT	GetRect (void) const;
	UInt32	GetDPI (void) const;
};


// === Font creation data ==============================================================================================

struct	FontCreationData
{
	WCHAR		largeFontName[LF_FACESIZE];
	WCHAR		smallFontName[LF_FACESIZE];
	WCHAR		xSmallFontName[LF_FACESIZE];
	LONG		largeFontSize;
	LONG		largeBoldFontWeight;
	LONG		smallFontSize;
	LONG		smallBoldFontWeight;
	LONG		xSmallFontSize;
	LONG		xSmallFontWeight;
	BYTE		fontCharSet;

	Int32		defaultLargeFontHeight;
	Int32		defaultSmallFontHeight;
	Int32		defaultXSmallFontHeight;
};

// === DPIScale ========================================================================================================

class DG_DLL_EXPORT DPIScale
{
friend UInt32	Utils::GetRawDPIForWindow (void* window);
friend void		DG::LogMonitorInformation (void);

public:
	typedef enum {
		Unaware			= 0,	// Custom scale value is ignored in Unaware mode
		SystemAware		= 1,
		MonitorAware	= 2,
		Default			= 3		// Used only to set to system or monitor aware mode depending on the OS version
	} DPIAwarenessLevel;

	class DG_DLL_EXPORT SetSystemAwareGuard
	{
	private:
		HANDLE oldContext;

	public:
		SetSystemAwareGuard ();
		~SetSystemAwareGuard ();
	};

private:
	GS::Array<MonitorInfo>			monitors;
	GS::HashTable<UInt32, HFONT>	fontCache;
	GS::HashTable<UInt32, Int32>	fontHeightCache;
	FontCreationData				fcData;

	HMODULE		hSHCoreDLL;
	HMODULE		hUser32DLL;
	GetDpiForMonitorProc				pGetDpiForMonitor;
	SetProcessDpiAwarenessProc			pSetProcessDpiAwareness;	// Used from W8.1, not available on W7
	SetProcessDPIAwareProc				pSetProcessDpiAware;		// Available from W7
	SetThreadDpiAwarenessContextProc	pSetThreadDpiAwarenessContextProc;
	EnableNonClientDpiScalingProc		pEnableNonClientDpiScalingProc;
	GetSystemMetricsForDpiProc			pGetSystemMetricsForDpiProc;
	AdjustWindowRectExForDpiProc		pAdjustWindowRectExForDpiProc;

	DPIAwarenessLevel	currentAwarenessLevel;

	static BOOL CALLBACK	UpdateMonitorInfoEnumProc (HMONITOR hMonitor, HDC hDC, LPRECT rc, LPARAM dwData);

	void	InitFontCreationData (const DGInitData* initData);
	void	ClearFontCache (void);
	static HFONT	GetDialogFont (short fontType, UInt32 dpi, bool singleLine);

	static bool		IsUIScalingEnabled (void);

public:
	DPIScale ();
	virtual ~DPIScale ();

	static void		Init (const DGInitData* initData);
	static void		Exit (void);

	static LONG		GetDefaultFontHeight (short fontSize);
	static HFONT	GetDialogFont (short fontType, UInt32 dpi);
	static short	GetDialogFontType (HFONT hFont);
	static Int32	GetDialogFontHeight (short fontType, UInt32 dpi, bool useCharHeight = false);
	static HFONT	GetMultilineDialogFont (short fontType, UInt32 dpi);

	static void		UpdateMonitorInfo (void);

	static USize	GetMonintorCount (void);
	static GS::Array<MonitorInfo>::ConstIterator	EnumerateMonitors (void);

	static UInt32	GetMainMonitorDPI (void);
	static UInt32	GetMonitorDPI (HMONITOR hMonitor);
	static UInt32	GetDPIForFrameWindow (void);
	static UInt32	GetDPIForWindow (HWND hWnd);
	static UInt32	GetDPIForDialog (HWND hDialogWnd);
	static UInt32	GetDPIForDialog (short dialId);
	static UInt32	GetDPIForDialogItem (HWND hDialogItemWnd);
	static UInt32	GetDPIForDesktopRect (const RECT& rect);

	static UInt32	GetDPIFromScaleFactor (double scaleFactor);
	static double	GetScaleFactorFromDPI (UInt32 dpi);

	static Int32	ScaleValue (Int32 value, UInt32 dpi, UInt32 baseDPI = 96);
	static Int32	ScaleValueP2L (Int32 value, UInt32 dpi);

	static RECT		ScaleRectExpl (const RECT& rectIn, UInt32 dpi, UInt32 baseDPI = 96);
	static RECT		ScaleRectP2LExpl (const RECT& rectIn, UInt32 dpi);
	static Rect		ScaleDGRectExpl (const Rect& rectIn, UInt32 dpi, UInt32 baseDPI = 96);
	static Rect		ScaleDGRectP2LExpl (const Rect& rectIn, UInt32 dpi);

	static void		ScaleRect (RECT& rect, UInt32 dpi, UInt32 baseDPI = 96);
	static void		ScaleTextRect (RECT& rect, short inFontType, UInt32 dpi, UInt32 baseDPI = 96);
	static void		ScaleRectP2L (RECT& rect, UInt32 dpi);
	static void		ScaleDGRect (Rect& rect, UInt32 dpi, UInt32 baseDPI = 96);
	static void		ScaleDGRectP2L (Rect& rect, UInt32 dpi);

	static UInt32	GetDialogDefaultDPI (short dialType, const RECT& screenRect);

	static BOOL		SetWindowPos (HWND hWnd, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags, UInt32 dpi);
	static HDWP		DeferWindowPos (HDWP hWinPosInfo, HWND hWnd, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags, UInt32 dpi);

	static DPIAwarenessLevel	GetDPIAwarenessLevel (void);

	static HANDLE	SetThreadDPIAwarenessContext (HANDLE context);
	static bool		EnableNonClientDPIScaling (HWND hWnd);
	static int		GetSystemMetricsForDpi (int nIndex, UINT dpi);
	static BOOL		AdjustWindowRectExForDpi (LPRECT lpRect, DWORD dwStyle, BOOL bMenu, DWORD dwExStyle, UINT dpi);
};

} // namespace

#endif
