// ******************************************************************************
// File:			LowLevelObjects.hpp
//
// Description:		Common lowlevel object interfaces usable with all GPU
//                  generation models
//
// Contact person:	DG
//
// SG compatible
// ******************************************************************************

#ifndef	LOWLEVELOBJECTS_HPP
#define	LOWLEVELOBJECTS_HPP

// --- Includes -----------------------------------------------------------------

#include	"GraphixDefinitions.hpp"


namespace	Graphix	{

// --- Context ID ---------------------------------------------------------------

typedef	UInt64	ContextID;

// --- General functions and operations -----------------------------------------

enum	CmpFunction
{
	CmpNever	=	0,
	CmpLess,
	CmpEqual,
	CmpLessEqual,
	CmpGreater,
	CmpNotEqual,
	CmpGreaterEqual,
	CmpAlways,

	NumberOfFuncs
};


enum	StencilOp
{
	StencilKeep	=	0,
	StencilZero,
	StencilReplace,
	StencilIncSat,
	StencilDecSat,
	StencilInvert,
	StencilInc,
	StencilDec,

	NumberOfStencilOps
};

// --- Vertex input layout ------------------------------------------------------

enum	InputElementFormat	{
	IEF_R32F	=	0,
	IEF_RG32F,
	IEF_RGB32F,
	IEF_RGBA32F,

	IEF_RGBA8UNORM,

	NumOfInputElementFormats
};


enum InputElementSemantic	{
	IES_Position,
	IES_TexCoord,
	IES_Color
};


struct	InputElement
{
	const char*				inputElemName;
	InputElementSemantic	semantic;
	UInt32					semanticIndex;
	UInt32					format;				// InputElementFormat
	UInt32					inputSlot;
	UInt32					instanceStepRate;
	UInt32					offset;
	//UInt32					stride;
};


// --- Viewport -----------------------------------------------------------------

struct	Viewport
{
	UInt32			x;
	UInt32			y;
	UInt32			width;
	UInt32			height;
	float			zMin;
	float			zMax;
};


// --- Textures -----------------------------------------------------------------

enum	TextureFormat
{
	TF_Undefined	=	0,
	
	TF_RGB565,
	TF_ARGB1555,
	TF_XRGB8888,
	TF_ARGB8888,
	TF_RGBA8888
};


class	GRAPHIX_DLL_EXPORT	Texture
{
public:
	virtual	~Texture ();

	virtual	TextureFormat	GetFormat () const = 0;

	//virtual	bool			UpdateRect (const void* srcData, const RECT& dstRect, Int32 srcStride) = 0;
	//virtual	bool			UpdateRect (const void* srcData, const RECT& dstRect, Int32 srcStride, TextureFormat srcFormat) = 0;
};

// --- Depth/Stencil state ------------------------------------------------------

struct	DepthStencil
{
	bool			depthEnable;				// Default: false
	bool			depthWriteEnabled;			// Default: false
	CmpFunction		depthFunc;
	bool			stencilEnable;				// Default: false
	UInt8			stencilMask;
	StencilOp		stencilFailOp;				// Op if stencil test fails
	StencilOp		stencilDepthFailOp;			// Op if stencil test passes but depth test fails
	StencilOp		stencilPassOp;				// Op if stencil AND depth test pass
	CmpFunction		stencilFunc;
};


class	GRAPHIX_DLL_EXPORT	DepthStencilState
{
public:
	virtual	~DepthStencilState ();
};


// --- Blending state -----------------------------------------------------------

enum	BlendMode
{
	BM_Zero		=	0,
	BM_One,
	BM_SrcColor,
	BM_InvSrcColor,
	BM_SrcAlpha,
	BM_InvSrcAlpha,
	BM_DstColor,
	BM_InvDstColor,
	BM_DstAlpha,
	BM_InvDstAlpha
};


enum	WriteMask
{
	WM_Red		=	0x1,
	WM_Green	=	0x2,
	WM_Blue		=	0x4,
	WM_Alpha	=	0x8,

	WM_All		=	0xF,
	WM_None		=	0
};


struct Blend
{
	bool		blendEnable;					// Default: false
	BlendMode	srcBlend;
	BlendMode	dstBlend;
	BlendMode	srcBlendAlpha;
	BlendMode	dstBlendAlpha;
	UInt32		writeMask;						// Default: WM_All
};


class	GRAPHIX_DLL_EXPORT	BlendState
{
public:
	virtual ~BlendState ();
};


// --- Rasterizer state ---------------------------------------------------------

enum	LLCullMode
{
	CM_None	=	0,
	CM_Front,			// CW
	CM_Back				// CCW
};

struct Rasterizer
{
	LLCullMode	cullMode;						// Default: CM_None
	Int32		depthBias;						// Default: 0
	float		slopeScaleDepthBias;			// Default: 0.0f
	//bool		frontCounterClockwise;			// Default: false
	bool		scissorEnable;					// Default: false
};


class	GRAPHIX_DLL_EXPORT	RasterizerState
{
public:
	virtual ~RasterizerState ();
};


// --- Inputlayout --------------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	InputLayout
{

public:
	virtual	~InputLayout ();
};


// --- Pixel shader ------------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	PixelShader
{
public:
	virtual	~PixelShader ();
};


// --- Program ------------------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	Program
{
public:
	virtual	~Program ();
};


// --- Vertex buffer ------------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	VertexBuffer
{
public:
	virtual	~VertexBuffer ();

	virtual	bool	IsDynamic () const = 0;
	
	virtual	bool	UpdateRegion (const void* srcData, UInt32 offset = 0, UInt32 size = 0) = 0;

	virtual	void*	Lock (bool noOverwrite) = 0;
	virtual	void	Unlock () = 0;
};


// --- Index buffer -------------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	IndexBuffer
{
public:
	virtual	~IndexBuffer ();

	virtual	void*	Lock (bool noOverwrite) = 0;
	virtual	void	Unlock () = 0;
};


} // namespace Graphix

#endif	// LOWLEVELOBJECTS_HPP
