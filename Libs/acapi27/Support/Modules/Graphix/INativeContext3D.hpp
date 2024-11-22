// *****************************************************************************
// File:			INativeContext3D.hpp
//
// Description:
//
// Project:
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	INATIVECONTEXT3D
#define	INATIVECONTEXT3D

#include "NativeContext3D.hpp"

namespace NewDisplay { class NativeImage; }


namespace NewDisplay {


class	GRAPHIX_DLL_EXPORT	INativeContext3D
{
public:
	INativeContext3D () {}
	virtual	~INativeContext3D ();

	virtual	bool		IsNull () const { return true; }
	
	virtual double		GetResolutionFactor () const = 0;

	virtual	NativeImage	GetDashImage (const GS::Array<float>& dash, float scale = 1.0f, UInt32 maxImageWidth = 4096, UInt32 dashColorArgb = 0xFFFFFFFF, UInt32 spaceColorArgb = 0x0) = 0;
	virtual	NativeImage	GetPatternImage (Gfx::Pattern pattern, float scale = 1.0f, UInt32 foreColorArgb = 0xFFFFFFFF, UInt32 backColorArgb = 0x0) = 0;

	virtual	void		EnableUsingZBuffer (bool enable) = 0;
	virtual void		EnableWriteZBuffer (bool enable) = 0;
	virtual void		SetZBufferDepthRange (float zNear, float zFar) = 0;
	virtual	void		SetColorWriteMask (UInt32 mask) = 0;

	virtual void		SetProjectionMatrix (const NativeContext3D::Matrix& matrix) = 0;
	virtual void		SetTransformationMatrix (const NativeContext3D::Matrix& matrix) = 0;

	virtual	void		SetShading (NativeContext3D::Shading shading) = 0;
	virtual	void		SetTexture (const NativeImage& image) = 0;
	virtual	void		SetFiltering (Filtering filtering) = 0;
	virtual	void		SetBaseZOffset (float units) = 0;
	virtual	void		SetPolygonOffset (bool enable, float factor, float units) = 0;
	virtual	void		EnablePerspectiveCorrection (bool enable) = 0;

	virtual	void		Set3DLineWidth (float width) = 0;

	virtual	void		DrawLine (const NativeContext3D::Vertex& v0, const NativeContext3D::Vertex& v1) = 0;
	virtual	void		DrawTriangle (const NativeContext3D::Vertex& v0, const NativeContext3D::Vertex& v1, const NativeContext3D::Vertex& v2) = 0;

	virtual	void		BeginPlanarPolygon () = 0;
	virtual	void		MoveTo (const NativeContext3D::Vertex& v) = 0;
	virtual	void		LineTo (const NativeContext3D::Vertex& v) = 0;
	virtual	void		EndPlanarPolygon () = 0;

	virtual bool		CopyZBuffer (const BlitSource& blitSource) = 0;

	virtual void		Flush () = 0;
};

}

#endif
