// *****************************************************************************
// File:			DrawingBridge.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef DRAWINGBRIDGE_HPP
#define DRAWINGBRIDGE_HPP

// --- Includes ----------------------------------------------------------------

#include "NativeContext.hpp"
#include "NativeContext3D.hpp"
#include "Color.hpp"
#include "NativeImage.hpp"
#include "DisplayArc.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace Graphix {
	class LowLevelContext;
}

// --- Function declarations ---------------------------------------------------

namespace NewDisplay {

class GRAPHIX_DLL_EXPORT	NativeContextImpl: public INativeContextImpl
{
public:
	virtual						~NativeContextImpl ();

	virtual void*				GetContextForExternalDraw (NativeContext::ExternalType type) = 0;
	virtual void				ReleaseContextForExternalDraw (void*) = 0;

	virtual	Graphix::LowLevelContext*	CreateLowLevelContext (bool depthStencilBufferNeeded) = 0;

	// 2D drawing functions
	virtual void				SetForeColor (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) = 0;
	virtual void				SetBackColor (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) = 0;
	virtual void				SetLineWidth (float lineWidth) = 0;
	virtual void				SetLineCap (LineCapType lineCapType) = 0;
	virtual void				SetLineDashPattern (const GS::Array<float>& pattern) = 0;
	virtual void				SetLinePatternOffset (float offset) = 0;
	virtual void				SetBlendMode (BlendMode blendMode) = 0;

	virtual void				SetFillPattern (const Gfx::Pattern& pattern) = 0;

	virtual void				FillRect (float left, float top, float right, float bottom, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) = 0;

	virtual void				MoveTo (float x, float y) = 0;
	virtual void				LineTo (float x, float y) = 0;
	virtual void				ArcTo (const DisplayArc& arc) = 0;
	virtual void				Arc (const DisplayArc& arc) = 0;
	virtual void				FrameRect (float left, float top, float right, float bottom) = 0;

	virtual void				DrawImage (const NativeImage& image, float scaleX, float scaleY, float rotation, float translationX, float translationY, bool transparent,
										   double alpha, NewDisplay::Filtering filtering, const BlitEffect* blitEffect) = 0;

	virtual void				DrawUIText (const GS::UniString& uString, const TE::IFont& iFont, Int32 just, double left, double top, double right, double bottom,
											bool singleLine) = 0;
	virtual void				DrawPlainText (const GS::UniString& uString, const TE::IFont& iFont, double baseLineX, double baseLineY, double angle) = 0;
	virtual void				DrawPlainMLText (const GS::UniString& uString, const TE::IFont& iFont, Int32 just,
												 double top, double left, double width, double height, double angle) = 0;
	virtual void				DrawPlainMLTextSafe (const GS::UniString& uString, const TE::IFont& iFont, Int32 just,
												double top, double left, double width, double height, double angle, NewDisplay::TextQuality textQuality) = 0;
	virtual void				DrawRichText (const TE::IRichText& rText, double left, double top, double width, Int32 options, double zoom) = 0;
	virtual void				GreekDrawRichText (const TE::IRichText& rText, double left, double top, double width, Int32 options, double zoom) = 0;

	virtual void				BeginPolygon (const FillEffect* effect) = 0;
	virtual void				EndPolygon () = 0;

	virtual void				SaveClip () = 0;
	virtual void				RestoreClip () = 0;
	virtual void				BeginClip () = 0;
	virtual void				EndClip () = 0;
	virtual void				SetClipToRect (const GS::Rect<float>& rect) = 0;
	virtual bool				IsClipEmpty () const = 0;

	virtual void				Blit (const BlitSource& src, float scaleX, float scaleY, float rotation,
									  float translationX, float translationY, double alpha, Filtering filtering, const BlitEffect* blitEffect) = 0;

	virtual void				Clear () = 0;

	virtual GS::Point<float>	GetCurrentPos () const = 0;
	virtual GS::Rect<float>		GetDirtyRect () const = 0;

	virtual Int32				GetCaps () const = 0;
	virtual double				GetResolutionFactor () const = 0;

	virtual bool				IsAntialiasEnabled () const = 0;
	virtual void				SetAntialiasEnabled (bool enabled) = 0;

	virtual bool				GetRoundLineCoordinates () const = 0;
	virtual void				SetRoundLineCoordinates (bool enabled) = 0;


	// 3D drawing functions
	virtual void				ClearBuffer (NativeContext3D::Buffers buffers, float zVal) = 0;
	virtual	bool				CopyZBuffer (const BlitSource& src) = 0;
	virtual void				EnableUsingZBuffer (bool enable) = 0;
	virtual void				EnableWriteZBuffer (bool enable) = 0;
	virtual	void				SetZBufferDepthRange (float zNear, float zFar) = 0;
	virtual void				SetColorWriteMask (UInt32 /*mask*/) {}

	virtual void				SetProjectionMatrix (const NativeContext3D::Matrix& matrix) = 0;
	virtual void				SetTransformationMatrix (const NativeContext3D::Matrix& matrix) = 0;

	virtual void				SetShading (NativeContext3D::Shading shading) = 0;
	virtual void				SetTexture (const NativeImage& image) = 0;
	virtual	void				SetFiltering (Filtering filtering) = 0;
	virtual	void				SetBaseZOffset (float units) = 0;
	virtual void				SetPolygonOffset (bool enable, float factor, float units) = 0;
	virtual void				EnablePerspectiveCorrection (bool enable) = 0;

	virtual	void				Set3DLineWidth (float width) = 0;

	virtual	void				DrawPoints (const GS::Array<NativeContext3D::Vertex>& /*points*/) {};//= 0;
	virtual void				DrawLine (const NativeContext3D::Vertex& v0, const NativeContext3D::Vertex& v1) = 0;
	virtual void				DrawTriangle (const NativeContext3D::Vertex& v0, const NativeContext3D::Vertex& v1, const NativeContext3D::Vertex& v2) = 0;
	virtual	void				DrawPointSprites (const GS::Array<NativeContext3D::Vertex>& points, UInt32 size) = 0;

	virtual void				BeginPlanarPolygon () = 0;
	virtual void				MoveTo (const NativeContext3D::Vertex& v) = 0;
	virtual void				LineTo (const NativeContext3D::Vertex& v) = 0;
	virtual void				EndPlanarPolygon () = 0;

	virtual void				BeginOcclusionQuery () {}; //= 0;
	virtual	UInt32				EndOcclusionQuery () { return 0; }; //= 0;

	virtual	void				LeaveThread () {}
};


class GRAPHIX_DLL_EXPORT NativeImageImpl: public INativeImageImpl
{
public:
			 NativeImageImpl () {}
	virtual ~NativeImageImpl ();

	virtual	UInt32				GetWidth () const = 0;
	virtual	UInt32				GetHeight () const = 0;
	virtual void				GetColorKey (unsigned char& red, unsigned char& green, unsigned char& blue) const = 0;

	virtual double				GetResolutionFactor () const = 0;

	virtual	void				SetColorKey (unsigned char red, unsigned char green, unsigned char blue) = 0;
	virtual bool				IsPerPixelAlpha () const = 0;

	virtual	NativeContext		GetContext () = 0;
	virtual	void				ReleaseContext () = 0;

	virtual bool				Encode (GS::OChannel& outputChannel, NativeImage::Encoding format) const = 0;

#ifdef WINDOWS
	virtual	void*				GetBitPtr () = 0;
	virtual	void				ReleaseBitPtr (void* ptr) = 0;
#endif
};


class GRAPHIX_DLL_EXPORT NativeImageObserver
{
public:
	NativeImageObserver ();
	virtual ~NativeImageObserver ();

	virtual void	ImageUpdated (NativeImageImpl& impl, float left, float top, float right, float bottom) = 0;
	virtual void	ImageReleased (NativeImageImpl& impl) = 0;

	static void		NotifyUpdate (NativeImageImpl& impl, float left, float top, float right, float bottom);
	static void		NotifyRelease (NativeImageImpl& impl);
};


#ifdef macintosh
NativeImage::ImplRef	CreateNativeImage (CGImageRef image, bool perPixelAlpha);
CGImageRef				GetNativeImageData (const NativeImage& image);
void					ReleaseNativeImageData (const NativeImage& image, CGImageRef nativeImageData);

#else
NativeImage::ImplRef	CreateNativeImage (HBITMAP bitmap, double resolutionFactor);
NativeImage::ImplRef	GRAPHIX_DLL_EXPORT CreateNativeImage (HICON icon, double resolutionFactor);
NativeImage::ImplRef	CreateNativeImage (HENHMETAFILE metaFile, UInt32 width, UInt32 height);
HBITMAP					GRAPHIX_DLL_EXPORT GetNativeImageData (const NativeImage& image);
bool					IsPerPixelAlphaed (const NativeImage& image);
#endif

void*					GetBitPtrOfImage (const NewDisplay::NativeImageImpl* imageImpl, GS::IntPtr* rowStrideInBytes = nullptr);
void					ReleaseBitPtrOfImage (const NewDisplay::NativeImageImpl* imageImpl, void* ptr);
void					CopyPixelsOfImage (const NewDisplay::NativeImageImpl* imageImpl, char** pixels, GS::IntPtr* rowStrideInBytes = nullptr);

NativeImageImpl*		CreateNativeImageImpl (UInt32 width, UInt32 height, UInt32 bitDepth, const void* bits, bool perPixelAlpha, double resolutionFactor = 1.0);
NativeImage::ImplRef	CreateNativeImage (UInt32 width, UInt32 height, const NativeImage& imageForColorData, double resolutionFactor = 1.0);
NativeImage::ImplRef	CreateNativeImage (UInt32 width, UInt32 height, UInt32 bitDepth, const void* bits, bool perPixelAlpha, bool enableMemoryOptimization, double resolutionFactor = 1.0);
NativeImage::ImplRef	CreateNativeImage (const char* data, UInt32 size, NativeImage::Encoding format);

void					ReleaseNativeImageData (const NativeImage& image);

}

NewDisplay::NativeContext::ImplRef	CreateImplFromExternalContext (void* context, double resolutionFactor, short itemXPosInDial, short itemYPosInDial);

#ifdef WINDOWS
NewDisplay::NativeContext::ImplRef	CreateImplFromHDC (void* hdc);
NewDisplay::NativeContext::ImplRef	CreateImplFromGraphics (void* graphics);
#endif
#ifdef macintosh
NewDisplay::NativeContext::ImplRef	CreateImplFromCGContext (void* context, double resolutionFactor);
#endif

void*					BeginHardwareAcceleratedOffscreenSessionForImage (NewDisplay::NativeImageImpl* forImageImpl, bool isAntialiasEnabled);
void					EndHardwareAcceleratedOffscreenSessionForImage (void* session, NewDisplay::NativeContextImpl& contextToDrawTo);

#endif
