// =============================================================================
// Description:		  Texture Proxy   
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (TEXTURE_HPP)
#define TEXTURE_HPP


// ----------------------- Includes --------------------------------------------
#include "ModelColor.hpp"
#include "GSModelerExport.h"
#include "UniString.hpp"
#include "SharedPtr.hpp"

// ----------------------- Predeclaration -----------------------------------
namespace ModelerAPI {
	class ITextureRelay;
	class TextureCoordinate;
	class Color;
}

namespace GDL
{
	class IFileRef;
}

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {


class GSMODELER_DLL_EXPORT Texture {
	friend class BackgroundTextureRelay;
	friend class FileTextureRelay;
	friend class ModelTextureRelay;

public:
	enum PixelType {
		ARGBPixelType			= 0x0001,
		Grayscale8PixelType		= 0x0002,
		BlackAndWhitePixelType	= 0x0003
	};

	enum Status {
		UseAlpha			= 0x0001,
		TransparentPattern	= 0x0008,
		BumpMapPattern		= 0x0010,
		DiffusePattern		= 0x0020,
		SpecularPattern		= 0x0040,
		AmbientPattern		= 0x0080,
		SurfacePattern		= 0x0100,
		RandomShift			= 0x0200,
		MirrorX				= 0x0400,
		MirrorY				= 0x0800,
		TextureLinkMat		= 0x1000
	};

	class ARGBPixel {
	public:
		unsigned char	alpha;
		unsigned char	red;
		unsigned char	green;
		unsigned char	blue;
	};

	class Grayscale8Pixel {
	public:
		unsigned char	value;
	};

	enum BlackAndWhitePixel {
		Black = 0x00,
		White = 0x01
	};

	struct BlackAndWhitePixel8 {
		BlackAndWhitePixel pixel1 : 1;
		BlackAndWhitePixel pixel2 : 1;
		BlackAndWhitePixel pixel3 : 1;
		BlackAndWhitePixel pixel4 : 1;
		BlackAndWhitePixel pixel5 : 1;
		BlackAndWhitePixel pixel6 : 1;
		BlackAndWhitePixel pixel7 : 1;
		BlackAndWhitePixel pixel8 : 1;
	};

	enum TextureOrigin { File, Model, SightBackground };

	typedef ARGBPixel	Pixel;

private:
	GS::ConstSharedPtr<ITextureRelay>	relay;

public:
	Texture ();
	Texture (const Texture& other);
	~Texture ();

	Texture&		operator= (const Texture& other);
	bool			operator== (const Texture& other) const;
	bool			operator!= (const Texture& other) const	{ return !(*this == other); }
	bool			operator< (const Texture& other) const;
	
	ULong					GenerateHashValue () const;
	bool					HasAlphaChannel (void) const;
	bool					IsAvailable (void) const;
	bool					IsTransparentPattern (void) const;
	bool					IsBumpMapPattern (void) const;
	bool					IsDiffusePattern (void) const;
	bool					IsSpecularPattern (void) const;
	bool					IsAmbientPattern (void) const;
	bool					IsSurfacePattern (void) const;
	bool					IsShiftedRandomly (void) const;
	bool					IsMirroredInX (void) const;
	bool					IsMirroredInY (void) const;
	Int32					GetGDLStatus (void) const;
	double					GetXSize (void) const;
	double					GetYSize (void) const;
	Int32					GetPixelMapXSize (void) const;
	Int32					GetPixelMapYSize (void) const;
	Int32					GetPixelMapSize (void) const;
	PixelType				GetPixelType (void) const;
	GS::UniString			GetName (void) const;

	void					GetPixelColor (Int32 x, Int32 y, Color* color, double* alpha = nullptr) const;
	void					GetPixel (Int32 x, Int32 y, ARGBPixel* pixel) const;
	void					GetPixel (Int32 x, Int32 y, Grayscale8Pixel* pixel) const;
	void					GetPixel (Int32 x, Int32 y, BlackAndWhitePixel* pixel) const;

	void					GetPixelColor (const TextureCoordinate* textureCoordinate, Color* color, double* alpha = nullptr) const;
	void					GetPixel (const TextureCoordinate* textureCoordinate, ARGBPixel* pixel) const;
	void					GetPixel (const TextureCoordinate* textureCoordinate, Grayscale8Pixel* pixel) const;
	void					GetPixel (const TextureCoordinate* textureCoordinate, BlackAndWhitePixel* pixel) const;

	void					GetPixelMap (ARGBPixel* pixelMap) const;
	void					GetPixelMap	(Grayscale8Pixel* pixelMap) const;
	void					GetPixelMap	(BlackAndWhitePixel8* pixelMap) const;

	Int32					GetPixelMapBufferSize (void) const;
	void					GetPixelMapCheckSum (char* checkSum, Int32 strLen) const;
	GS::UniString			GetPixelMapCheckSum () const;
	GS::UniString			GetFingerprint () const;
	const GDL::IFileRef*	GetExternalReference (void) const;
};


} //namespace ModelerAPI


#endif
