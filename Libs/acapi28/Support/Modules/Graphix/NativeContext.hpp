// *****************************************************************************
// File:			NativeContext.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef NATIVECONTEXT_HPP
#define NATIVECONTEXT_HPP

// --- Includes ----------------------------------------------------------------

#include "NativeContextBase.hpp"

#include "GraphixDefinitions.hpp"		// GRAPHIX_DLL_EXPORT
#include "Array.hpp"
#include "Point.hpp"
#include "Rect.hpp"
#include "IBlit.hpp"
#include "DisplayArc.hpp"

#include "ThreadingDebug.hpp"
#include "IFont.hpp"
#include "IRichText.hpp"
#include "UniString.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class Point;
	class Rect;
}

class Clip;

namespace NewDisplay {

class OffscreenSurface;
class BlitEffect;
class FillEffect;


// --- Constants ---------------------------------------------------------------

enum LineCapType {
	LCT_Round = 0,
	LCT_Square = 1,

	LCT_LastValue = LCT_Square
};


enum TextQuality	{
	TQ_SystemDefault = 0,

	TQ_NoAntialias	=	1,
	TQ_Antialias	=	2,
	TQ_Proof		=	3,

	TQ_LastValue	= TQ_Proof
};

// --- Class declarations ------------------------------------------------------

class GRAPHIX_DLL_EXPORT NativeContext:	public NativeContextBase,
										private NonThreadSafeClass
{
public:
	enum ExternalType {
		T_Default				=	0,
#ifdef WINDOWS
		T_HDC					=	0,
		T_HDCForThemedDrawing,
		T_Graphics,
#else
		T_CGContext				=	0,
#endif
		T_OpenGL
	};

// Operations against nullptr
public:
	bool	operator== (std::nullptr_t) const;
	bool	operator!= (std::nullptr_t) const;
	void	operator= (std::nullptr_t);

public:
	explicit NativeContext (ImplRef impl = ImplRef ());
	explicit NativeContext (const NativeContextBase&);
	virtual ~NativeContext ();

	// Drawing functions
	void	SetForeColor (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);
	void	SetForeColor (const Gfx::Color& color);
	void	SetBackColor (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);
	void	SetBackColor (const Gfx::Color& color);
	void	SetLineWidth (float lineWidth);
	void	SetLineCap (LineCapType lineCapType);
	void	SetLineDashPattern (const GS::Array<float>& pattern);
	void	SetLinePatternOffset (float offset);
	void	SetFillPattern (const Gfx::Pattern& pattern);
	void	SetBlendMode (BlendMode blendMode);

	// Line drawing
	void	MoveTo (float x, float y);
	void	LineTo (float x, float y);
	void	ArcTo (const DisplayArc& arc);
	void	Arc (const DisplayArc& arc);
	void	FrameRect (float left, float top, float right, float bottom);
	void	FrameRect (const GS::Rect<float>& rect);
	void	FrameRoundedRect (const GS::Rect<float>& rect, float cornerRadius);

	// Fill drawing
	void	FillRect (float left, float top, float right, float bottom,
					  unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);
	void	FillRect (const GS::Rect<float>& rect, const Gfx::Color& color);
	void	BeginPolygon (const FillEffect* effect = nullptr);
	void	EndPolygon ();

	// Text drawing

	void	DrawUIText (const GS::UniString& uString, const TE::IFont& iFont, Int32 just,
						double left, double top, double right, double bottom, bool singleLine);

	void	DrawPlainText (const GS::UniString& uString, const TE::IFont& iFont, double baseLineX, double baseLineY, double angle);
	void	DrawPlainMLText (	const GS::UniString& uString, const TE::IFont& iFont, Int32 just,
								double top, double left, double width, double height, double angle);

	void	DrawPlainMLTextSafe (const GS::UniString& uString, const TE::IFont& iFont, Int32 just,
									double top, double left, double width, double height, double angle, TextQuality textQuality = TQ_SystemDefault);

	void	DrawRichText (const TE::IRichText& rText, double left, double top, double width, Int32 options, double zoom = 1.0);
	void	GreekDrawRichText (const TE::IRichText& rText, double left, double top, double width, Int32 options, double zoom = 1.0);

	// Clip handling
	void	SaveClip ();
	void	RestoreClip ();
	void	BeginClip ();
	void	EndClip ();
	void	SetClipToRect (const GS::Rect<float>& rect);
	void	SetClip (const Clip& clip);
	bool	IsClipEmpty () const;

	// Bitting
	void	DrawImage (const NativeImage& image, float scaleX, float scaleY, float rotation,
					   float translationX, float translationY, bool transparent, double alpha = 1.0, Filtering filtering = DefaultFilter, const BlitEffect* blitEffect = nullptr);

	void	Blit (const BlitSource& src, float scaleX, float scaleY, float rotation,
				  float translationX, float translationY, double alpha = 1.0, Filtering filtering = DefaultFilter, const BlitEffect* blitEffect = nullptr);

	// Clear, etc.
	void				Clear ();
	GS::Point<float>	GetCurrentPos () const;
	GS::Rect<float>		GetDirtyRect () const;
	bool				GetRoundLineCoordinates () const;
	void				SetRoundLineCoordinates (bool enabled);

	// External context: returns the context in the requested type if available or nullptr
	void*	GetExternalContext (ExternalType type =  T_Default);
	void	ReleaseExternalContext (void*);

	class GRAPHIX_DLL_EXPORT SaveAndRestore {
	private:
		NativeContext& context;
	public:
		SaveAndRestore (NativeContext& context);
		~SaveAndRestore ();
		operator NativeContext& ();
		operator NativeContext* ();
	};

	// ---

	void LeaveThread ();
};

extern NativeContext GRAPHIX_DLL_EXPORT EmptyContext;

}

#endif
