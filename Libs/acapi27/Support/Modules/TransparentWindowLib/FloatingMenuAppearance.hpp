#ifndef GS_FLOATINGWINDOW_FLOATINGMENUAPPEARANCE_HPP
#define GS_FLOATINGWINDOW_FLOATINGMENUAPPEARANCE_HPP
#pragma once

#include "TransparentWindowLibDefinitions.hpp"
#include "FloatingMenuDefinitions.hpp"


namespace FloatingWindow {
class TRANSPARENTWINDOWLIB_DLL_EXPORT FloatingMenuAppearance {
private:
	Gfx::Color			foregroundColor		= DG::Utils::GetSystemColor (DG::Utils::SystemColorType::TrackerTextColorType);
	Gfx::Color			backgroundColor		= DG::Utils::GetSystemColor (DG::Utils::SystemColorType::TrackerBackgroundColorType);
	Gfx::Color			frameColor			= DG::Utils::GetSystemColor (DG::Utils::SystemColorType::TrackerFrameColorType);
	bool				smallFont			= false;
	unsigned char		alpha				= 128;
	bool				contourIsVisible	= true;
	BoundingRectStyle	boundingRectStyle	= BoundingRectStyle::NORMALSTYLE;
	float				cornerRadius		= 6.5f;
	ArrowStyle			arrowStyle			= ArrowStyle::NOARROW;
	unsigned short		arrowSize			= 6;
	float				arrowOffset			= 0.0f;
	short				offsetX				= 0;

public:
	void SetForegroundColor (const Gfx::Color& foregroundColor);
	const Gfx::Color& GetForegroundColor () const;

	void SetBackgroundColor (const Gfx::Color& backgroundColor);
	const Gfx::Color& GetBackgroundColor () const;

	void SetFrameColor (const Gfx::Color& frameColor);
	const Gfx::Color& GetFrameColor () const;

	void SetSmallFont (bool smallFont);
	bool IsSmallFont () const;

	void SetAlpha (unsigned char alpha);
	unsigned char GetAlpha () const;

	void SetContourVisibility (bool	contourIsVisible);
	bool IsContourVisible () const;

	void SetBoundingRectStyle (BoundingRectStyle boundingRectStyle);
	BoundingRectStyle GetBoundingRectStyle () const;

	void SetCornerRadius (float cornerRadius);
	float GetCornerRadius () const;

	void SetArrowStyle (ArrowStyle arrowStyle);
	ArrowStyle GetArrowStyle () const;

	void SetArrowSize (unsigned short arrowSize);
	unsigned short GetArrowSize () const;

	void	SetArrowOffset (float arrowOffset);
	float	GetArrowOffset () const;

	void SetOffsetX (short offsetX);
	short GetOffsetX () const;
};

}
#endif
