#include "GraphixDefinitions.hpp"
//#include "NativeContextBase.hpp"

namespace Gdiplus	{
	class	Graphics;
};

namespace NewDisplay	{
	class	NativeImage;
	class	NativeImageImpl;
	class	INativeContextImpl;
};


class	ISwCore;

namespace Sw	{

	GRAPHIX_DLL_EXPORT	ISwCore*				GetSwCore ();

	GRAPHIX_DLL_EXPORT	NewDisplay::INativeContextImpl*		CreateSwContext (HDC hdc, double scaleFactor, bool roundedLineCoordsByDefault = false,
																			 UInt32 clearColor = 0x0, NewDisplay::NativeImageImpl* imageImpl = nullptr);
	
	GRAPHIX_DLL_EXPORT	NewDisplay::INativeContextImpl*		CreateSwContext (Gdiplus::Graphics* graphics, double scaleFactor,
																			 bool roundedLineCoordsByDefault = false, UInt32 clearColor = 0x0);

	// surface must be a 32 bit DIBSection
	GRAPHIX_DLL_EXPORT	NewDisplay::INativeContextImpl*		CreateSwContext (HBITMAP surface, double scaleFactor, float originX, float originY, HRGN dirtyRegion,
																			 HRGN defaultClip, const RECT* defaultClipRect, bool defaultClipIsRect, UInt32 clearColor,
																			 bool perPixelAlpha = false, bool inverseAlpha = false, bool antialias = false,
																			 bool roundedLineCoordsByDefault = false, NewDisplay::NativeImageImpl* imageImpl = nullptr);

	void	GRAPHIX_DLL_EXPORT	UpdateLayeredWindowContent (HWND layeredWnd, NewDisplay::NativeImage& fromImage, BYTE globalAlpha,
															HBITMAP cachedLayeredWindowContent, POINT* wndPos, SIZE* wndSize);

};