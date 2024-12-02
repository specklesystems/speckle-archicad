// *****************************************************************************
// File:			NativeContext3D.hpp
//
// Description:
//
// Project:
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef NATIVECONTEXT3D_HPP
#define NATIVECONTEXT3D_HPP

// --- Includes ----------------------------------------------------------------

#include "NativeContextBase.hpp"

#include "GraphixDefinitions.hpp"		// GRAPHIX_DLL_EXPORT
#include "Array.hpp"
#include "Point.hpp"
#include "Rect.hpp"
#include "IBlit.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace NewDisplay {

class NativeImage;
class Surface;


// --- Constants ---------------------------------------------------------------


// --- Class declarations ------------------------------------------------------

class GRAPHIX_DLL_EXPORT NativeContext3D:	public NativeContextBase
{
public:
	struct	GRAPHIX_DLL_EXPORT Vertex
	{
		float	x, y, z;		// 3D point
		unsigned char	cR, cG, cB, cA;
		float	tu, tv;			// 2D texture coordinates

		Vertex ();
		Vertex (float x, float y, float z);
		Vertex (float x, float y, float z, float tu, float tv);
		Vertex (float x, float y, float z, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		Vertex (float x, float y, float z, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float tu, float tv);
	};


	struct	GRAPHIX_DLL_EXPORT Matrix
	{
			float	data[4*4];

			Matrix ();
			//Matrix (const Matrix& matrix);
			Matrix (const float (&matrix)[4*4]);

			Matrix		operator* (const Matrix& rightOp) const;

			Vertex		Apply (const Vertex& v) const;
	};


	class	GRAPHIX_DLL_EXPORT ProjectionMatrix: public Matrix
	{
		public:
			ProjectionMatrix (float fov_h, float fov_v, float zNear, float zFar);
	};


	class	GRAPHIX_DLL_EXPORT UnitMatrix: public Matrix
	{
		public:
			UnitMatrix ();
	};

	// --- Pixel shadings ------------------------------------------
	enum	Shading	{
		DecalTexturing	=	0,			// simple texturing
		TextureModColor,				// texture * color
		VertexColor
	};

	// --- Buffer types --------------------------------------------
	enum	Buffers	{
		ZBuffer	=	0
	};

	// --- Destionation write mask bits ----------------------------
	enum	WriteMask	{
		WM_Red		=	1,
		WM_Green	=	2,
		WM_Blue		=	4,
		WM_Alpha	=	8
	};

// Operations against nullptr
public:
	bool	operator== (std::nullptr_t) const;
	bool	operator!= (std::nullptr_t) const;
	void	operator= (std::nullptr_t);

public:
	explicit	NativeContext3D (ImplRef impl = ImplRef ());
	explicit	NativeContext3D (const NativeContextBase&);
	virtual		~NativeContext3D ();

	void		ClearBuffer (Buffers buffers, float zVal);
	bool		CopyZBuffer (const BlitSource& src);
	void		EnableUsingZBuffer (bool enable);
	void		EnableWriteZBuffer (bool enable);
	void		SetZBufferDepthRange (float zNear, float zFar);
	void		SetColorWriteMask (UInt32 mask);												// OR'ed combination of WriteMask bits

	void		SetProjectionMatrix (const Matrix& matrix);
	void		SetTransformationMatrix (const Matrix& matrix);

	void		SetShading (Shading shading);
	void		SetTexture (const NativeImage& image);
	void		SetFiltering (Filtering filtering);
	void		SetBaseZOffset (float units);
	void		SetPolygonOffset (bool enable, float factor, float units);	// Adds to base z offset!
	void		EnablePerspectiveCorrection (bool enable);

	void		Set3DLineWidth (float width);

	void		DrawPoints (const GS::Array<Vertex>& points);
	void		DrawLine (const Vertex& v0, const Vertex& v1);
	void		DrawTriangle (const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void		DrawPointSprites (const GS::Array<Vertex>& points, UInt32 size);

	void		BeginOcclusionQuery ();
	UInt32		EndOcclusionQuery ();

	void		BeginPlanarPolygon ();
	void		MoveTo (const Vertex& v);
	void		LineTo (const Vertex& v);
	void		EndPlanarPolygon ();
};


extern NativeContext3D GRAPHIX_DLL_EXPORT EmptyContext3D;

}

#endif
