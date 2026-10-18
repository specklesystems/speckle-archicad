
// *****************************************************************************
//
//                                PDFDrawableDevice
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined PDFDRAWABLEDEVICE_HPP
#define PDFDRAWABLEDEVICE_HPP

// --------------------------------- Includes ----------------------------------

#include "DrawableDevice.hpp"
#include "Color.hpp"

#if defined (macintosh)
#include "MacUtils/CGUtil.hpp"
#endif

// ----------------------------- Predeclarations -------------------------------

namespace TE {
	class FontFamily;
	class IFont;
	class PDFFontObjBase;
}

// ============================== Class IPDFTextOut ==================================

namespace TE {

class TE_DLL_EXPORT IPDFTextOut {
public:
#ifdef WINDOWS
	virtual void PutString (DrawableDevice* pdfDrawableDevice, const TE::FontFamily* fontFamily, double x, double y,
							const unsigned short* uStr, double fontSize, double widthFactor, double charSpaceFactor,
							const unsigned short *glyphs, double *dAdv, unsigned int gNum) = 0;
#else
	virtual void PutGlyphsAtPositions (void* pdfContext, const CGGlyph glyphs[], const CGPoint positions[], size_t count, TE::PDFFontObjBase pdfFontObjBase, CGColorRef cgColor);
	virtual void* GetPDFContext (void* pdfContext) const;		// return CGContextRef
#endif
};

// ============================== Class PDFDrawableDevice ==============================

class TE_DLL_EXPORT PDFDrawableDevice : public DrawableDevice {

		private:
#ifdef WINDOWS
			HDC						hdc;
#endif
			DeviceType				devType;
			void*					pdfContext;
			Gfx::Color				plainTextColor;
			IPDFTextOut*			textOutput;

		public:
			PDFDrawableDevice (IPDFTextOut* pdfTextOut, void* pdfInfo = nullptr);
			~PDFDrawableDevice (void);

#ifdef WINDOWS
			inline HDC			GetDC (void) const { return hdc; }
#endif
			inline void*		GetPdfContext (void) const { return pdfContext; }
			inline void*		GetPdfContext (void) { return pdfContext; }

			void				GetPlainTextColor (Gfx::Color* txtColor) const;
			double				GetDeviceResolution () const;
#ifdef WINDOWS
	double						GetTextScale () const { return 3.0; }
#else
	double						GetTextScale () const { return 1.0; }
#endif
			const IPDFTextOut*	GetPDFTextOut () const { return textOutput; }
			IPDFTextOut*		GetPDFTextOut () { return textOutput; }

			void				SetPlainTextColor () const;

			void				SetPlainTextColor (const Gfx::Color& txtColor);
			virtual DeviceType	GetDeviceType (void) const  override { return devType; }
			void				SetDrawContext (void* drawContext, DeviceType deviceType) override;
			bool				VectorialDraw (void) const override { return true; }

};

}	// namespace TE
// ______________________________ Class PDFDrawableDevice ______________________________


#endif
