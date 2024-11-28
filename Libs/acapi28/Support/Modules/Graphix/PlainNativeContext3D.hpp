// *****************************************************************************
// File:			PlainNativeContext3D.hpp
//
// Description:
//
// Project:
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	PLAINNATIVECONTEXT3D
#define	PLAINNATIVECONTEXT3D

#include	"INativeContext3D.hpp"

namespace NewDisplay {

class	GRAPHIX_DLL_EXPORT	PlainNativeContext3D:	public NewDisplay::INativeContext3D
{
	NewDisplay::NativeContext3D		context;

public:
	PlainNativeContext3D (NewDisplay::NativeContext3D& context3D):
		context (context3D)
	{
	}

	virtual	bool		IsNull () const override;

	virtual double		GetResolutionFactor () const override;

	virtual	NativeImage	GetDashImage (const GS::Array<float>& dash, float scale = 1.0f, UInt32 maxImageWidth = 4096, UInt32 dashColorArgb = 0xFFFFFFFF, UInt32 spaceColorArgb = 0x0) override;
	virtual	NativeImage	GetPatternImage (Gfx::Pattern pattern, float scale = 1.0f, UInt32 foreColorArgb = 0xFFFFFFFF, UInt32 backColorArgb = 0x0) override;

	virtual	void		EnableUsingZBuffer (bool enable) override;
	virtual void		EnableWriteZBuffer (bool enable) override;
	virtual void		SetZBufferDepthRange (float zNear, float zFar) override;
	virtual	void		SetColorWriteMask (UInt32 mask) override;

	virtual void		SetProjectionMatrix (const NativeContext3D::Matrix& matrix) override;
	virtual void		SetTransformationMatrix (const NativeContext3D::Matrix& matrix) override;

	virtual	void		SetShading (NativeContext3D::Shading shading) override;
	virtual	void		SetTexture (const NativeImage& image) override;
	virtual	void		SetFiltering (Filtering filtering) override;
	virtual	void		SetBaseZOffset (float units) override;
	virtual	void		SetPolygonOffset (bool enable, float factor, float units) override;
	virtual	void		EnablePerspectiveCorrection (bool enable) override;

	virtual	void		Set3DLineWidth (float width) override;

	virtual	void		DrawLine (const NativeContext3D::Vertex& v0, const NativeContext3D::Vertex& v1) override;
	virtual	void		DrawTriangle (const NativeContext3D::Vertex& v0, const NativeContext3D::Vertex& v1, const NativeContext3D::Vertex& v2) override;

	virtual	void		BeginPlanarPolygon () override;
	virtual	void		MoveTo (const NativeContext3D::Vertex& v) override;
	virtual	void		LineTo (const NativeContext3D::Vertex& v) override;
	virtual	void		EndPlanarPolygon () override;

	virtual bool		CopyZBuffer (const BlitSource& blitSource) override;

	virtual void		Flush () override;
};


extern PlainNativeContext3D		GRAPHIX_DLL_EXPORT EmptyPlainNativeContext3D;

}


#endif
