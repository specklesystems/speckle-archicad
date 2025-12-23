// *********************************************************************************************************************
// Description:		IBubble
//
// Module:			DG
// Namespace:
// Contact person:	DGY
//
// SG compatible
// *********************************************************************************************************************

#ifndef _IBUBBLE_HPP_
#define _IBUBBLE_HPP_

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "ITransparentWindow.hpp"
#include "DGUtility.hpp"
#include "Color.hpp"
#include "NativeImage.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace DG {
	class BrowserBase;
}

// --- Class declarations ----------------------------------------------------------------------------------------------

namespace ITracker {


class TRANSPARENTWINDOWLIB_DLL_EXPORT IBubble
{

public:
	struct TextItem
	{
		GS::UniString	text;
		DG::Rect		rect;
		DG::Font::Size	size;
		DG::Font::Style	style;
		Gfx::Color		color;
	};

	struct ImageItem
	{
		NewDisplay::NativeImage	image;
		DG::Rect				rect;
	};

	struct IconItem
	{
		DG::Icon	icon;
		DG::Rect	rect;
	};


public:
	virtual ~IBubble ();

	virtual void					Clear () = 0;

	virtual void					AddText (const GS::UniString& text, const DG::Rect& rect, DG::Font::Size size, DG::Font::Style style, const Gfx::Color& color = Gfx::Color (0, 0, 0)) = 0;
	virtual GS::Array<TextItem>		GetTexts () const = 0;
	virtual void					AddImage (const NewDisplay::NativeImage& image, const DG::Rect& rect)  = 0;
	virtual GS::Array<ImageItem>	GetImages () const = 0;
	virtual void					AddIcon (const DG::Icon& icon, const DG::Rect& rect) = 0;
	virtual GS::Array<IconItem>		GetIcons () const  = 0;
	virtual void					SetAutoRemove (bool autoRemove) = 0;
	virtual bool					IsAutoRemove () const = 0;
	virtual DG::Icon				GetBackGroundImage () const = 0;
	virtual DG::Rect				GetCloseRect () const = 0;
	virtual DG::Rect				GetMoveRect () const = 0;
	virtual void					ShowBubble () = 0;
	virtual void					Hide () = 0;
	virtual void					Update () = 0;
};

class TRANSPARENTWINDOWLIB_DLL_EXPORT IBubbleWebView
{
public:

	virtual ~IBubbleWebView ();
	virtual void					AddBrowser (DG::BrowserBase& browser, const DG::Rect& rect, const float cornerRadius = 0.0) = 0;
};

class TRANSPARENTWINDOWLIB_DLL_EXPORT IBubbleImpl : public IBubble, public ITransparentWindowImpl
{
private:
	IBubble* impl;

protected:
	IBubbleImpl ();

	void SetImpl (IBubble* impl);

public:
	IBubbleImpl (const DG::Icon* backgroundImage, const DG::Rect& backgroundImageRect, const DG::Rect& closeRect, const DG::Rect& moveRect, bool autoRemove);
	virtual ~IBubbleImpl ();

	virtual void					Clear () override;

	virtual void					AddText (const GS::UniString& text, const DG::Rect& rect, DG::Font::Size size, DG::Font::Style style, const Gfx::Color& color = Gfx::Color (0, 0, 0))  override;
	virtual GS::Array<TextItem>		GetTexts () const  override;
	virtual void					AddImage (const NewDisplay::NativeImage& image, const DG::Rect& rect)   override;
	virtual GS::Array<ImageItem>	GetImages () const  override;
	virtual void					AddIcon (const DG::Icon& icon, const DG::Rect& rect)  override;
	virtual GS::Array<IconItem>		GetIcons () const   override;
	virtual void					SetAutoRemove (bool autoRemove)  override;
	virtual bool					IsAutoRemove () const  override;
	virtual DG::Icon				GetBackGroundImage () const  override;
	virtual DG::Rect				GetCloseRect () const  override;
	virtual DG::Rect				GetMoveRect () const  override;
	virtual void					ShowBubble ()  override;
	virtual void					Hide ()  override;
	virtual void					Update ()  override;
};


class TRANSPARENTWINDOWLIB_DLL_EXPORT IBubbleWebViewImpl : public IBubbleWebView, public IBubbleImpl
{
private:
	IBubbleWebView* impl;

protected:
	IBubbleWebViewImpl ();

public:
	IBubbleWebViewImpl (const GS::UniString& url, const DG::Rect& backgroundImageRect, const DG::Rect& closeRect, const DG::Rect& moveRect, bool autoRemove);
	virtual ~IBubbleWebViewImpl ();

	virtual void					AddBrowser (DG::BrowserBase& browser, const DG::Rect& rect, const float cornerRadius = 0.0) override;

};

}

#endif	//
