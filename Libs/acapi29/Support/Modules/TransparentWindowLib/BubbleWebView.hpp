/****************************************************************************/
/*																			*/
/*              BubbleWebView.hpp											*/
/*																			*/
/****************************************************************************/

#ifndef BUBBLE_WEBVIEW_HPP
#define BUBBLE_WEBVIEW_HPP

#pragma once

#include "TransparentWindowLibDefinitions.hpp"
#include "CountedPtr.hpp"
#include "UniString.hpp"
#include "DGItemProperty.hpp"
#include "DGUtility.hpp"
#include "Color.hpp"
#include "DGBrowser.hpp"
#include "TransparentWindow.hpp"
#include "IBubble.hpp"

class MessageDispatcher;

namespace NewDisplay { class NativeImage; }

namespace Bubble {

	class TRANSPARENTWINDOWLIB_DLL_EXPORT BubbleWebView : public ITracker::IBubbleWebView,
											 public ITracker::IBubble,
											 public TransparentWindow
	{
		friend class MessageDispatcher;


	private:
		DG::Icon				backgroundImage;
		//DG::Rect				closeRect;	// Client origin logical units
		//DG::Rect				moveRect;	// Client origin logical units

		GS::Array<TextItem>		texts;
		GS::UniString			url;

		bool					autoRemove;

	public:
		//BubbleWebView ();
		BubbleWebView (const GS::UniString& url, const DG::Rect& backgroundImageRect, const DG::Rect& closeRect, const DG::Rect& moveRect, bool autoRemove);

		virtual ~BubbleWebView ();

		void					Clear () override;

		void					SetUrl (const GS::UniString& url);

		void					AddText (const GS::UniString& text, const DG::Rect& rect, DG::Font::Size size, DG::Font::Style style, const Gfx::Color& color = Gfx::Color (0, 0, 0)) override;
		GS::Array<TextItem>		GetTexts () const override;

		void					AddImage (const NewDisplay::NativeImage& /*image*/, const DG::Rect& /*rect*/) override {}
		GS::Array<ImageItem>	GetImages () const  override { return GS::Array<ImageItem> ();  }

		void					AddIcon (const DG::Icon& /*icon*/, const DG::Rect& /*rect*/)  override {}
		GS::Array<IconItem>		GetIcons () const  override { return GS::Array<IconItem> ();  }

		void					SetAutoRemove (bool autoRemove) override;
		bool					IsAutoRemove () const override;

		DG::Icon				GetBackGroundImage () const override;
		DG::Rect				GetCloseRect (void) const override;
		DG::Rect				GetMoveRect (void) const override;

		void					ShowBubble () override;
		void					Hide () override;
		void					Update () override;

		virtual					void AddBrowser (DG::BrowserBase& browser, const DG::Rect& rect, const float cornerRadius = 0.0) override;

	};

	typedef GS::CountedPtr<BubbleWebView, GS::AtomicCounter> BubbleWebViewRef;

}
#endif
