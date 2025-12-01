// *****************************************************************************
// File:			BlitEffects.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef FILLEFFECTS_HPP
#define FILLEFFECTS_HPP

// --- Includes ----------------------------------------------------------------

#include "GraphixDefinitions.hpp"					// GRAPHIX_DLL_EXPORT
#include "Color.hpp"
#include "Point.hpp"
#include "Rect.hpp"
#include "CountedPtr.hpp"
#include "Cloneable.hpp"
#include "BlitEffects.hpp"

// --- Defines -----------------------------------------------------------------

namespace NewDisplay {

// --- Predeclarations ---------------------------------------------------------

class NativeImage;

// --- Fill effect classes -----------------------------------------------------

class GRAPHIX_DLL_EXPORT FillEffect
{
protected:
	FillEffect ();

public:
	virtual ~FillEffect ();
};


// --- Linear Gradient effect --------------------------------------------------

class GRAPHIX_DLL_EXPORT LinearGradientFillEffect: public FillEffect
{
public:
	Gfx::Color			foreColor;
	Gfx::Color			backColor;
	GS::Point<float>	startPoint;
	GS::Point<float>	endPoint;

public:
	LinearGradientFillEffect (const Gfx::Color foreColor, const Gfx::Color backColor, const GS::Point<float>& startPoint,
							  const GS::Point<float>& endPoint);
	virtual ~LinearGradientFillEffect ();

	bool	IsEqual (const LinearGradientFillEffect& other) const;
};


// --- Radial Gradient effect --------------------------------------------------

class GRAPHIX_DLL_EXPORT RadialGradientFillEffect: public FillEffect
{
public:
	Gfx::Color			foreColor;
	Gfx::Color			backColor;
	GS::Point<float>	centerPoint;
	double				innerRadius;
	double				outerRadius;

public:
	RadialGradientFillEffect (const Gfx::Color foreColor, const Gfx::Color backColor, const GS::Point<float>& centerPoint,
							  const double innerRadius, const double outerRadius);
	virtual ~RadialGradientFillEffect ();

	bool	IsEqual (const RadialGradientFillEffect& other) const;
};

// --- Image effect ------------------------------------------------------------

class GRAPHIX_DLL_EXPORT ImageFillEffect: public FillEffect
{
public:
	enum WrapMode {
		Wrap		=	0,
		MirrorWrap,

		LastValue = MirrorWrap
	};

public:
	NativeImage*		image;
	double				matrix[6];
	WrapMode			wrapModeHorizontal;
	WrapMode			wrapModeVertical;
	GS::Cloneable<BlitEffect>	blitEffect;

public:
	ImageFillEffect (NativeImage& image, const double (&matrix)[6], WrapMode wrapModeHorizontal, WrapMode wrapModeVertical);
	ImageFillEffect () : image (nullptr), wrapModeHorizontal (Wrap), wrapModeVertical (Wrap), blitEffect ()
	{
		matrix[0] = matrix[1] = matrix[2] = matrix[3] = matrix[4] = matrix[5] = 0.0;
	}

	void	SetBlitEffect (GS::Owner<BlitEffect> newBlitEffect);
	bool	IsEqual (const ImageFillEffect& other) const;

	virtual ~ImageFillEffect ();
};


// --- Vectorial hatch effect --------------------------------------------------

class GRAPHIX_DLL_EXPORT IVectorialHatchDescriptorImpl
{
public:
	virtual ~IVectorialHatchDescriptorImpl ();

	virtual	void		AddLine		(const GS::Point<double>& offset,
									 const GS::Array<double>* pPatternElems,
									 double direction,
									 double spacing,
									 double patternOffset) = 0;
	
	virtual	void		AddLine		(const GS::Point<double>& offset,
									 const double* pPatternElems,
									 UInt32 numOfPatternElems,
									 double direction,
									 double spacing,
									 double patternOffset) = 0;

	virtual void		Finalize	() = 0;

	virtual bool		IsEqual		(const IVectorialHatchDescriptorImpl& other) const = 0;
};


typedef		GS::CountedPtr<IVectorialHatchDescriptorImpl, GS::AtomicCounter> VectorialHatchDescriptorRef;


// Transformation for a hatch line: rotate(line direction) * translate(line offset) * hatchMatrix * drawMatrix
// (Line offset results from the cumulated spacing and pattern offset defined in line direction)
// A matrix pointer can be null, indicating identity matrix

class GRAPHIX_DLL_EXPORT VectorialHatchFillEffect: public FillEffect
{
public:
	enum BackgroundFillMode
	{
		FillBackground		=	0,
		OmitFillBackground,

		LastValue = OmitFillBackground
	};

public:
	VectorialHatchDescriptorRef		vectorialHatchDescriptor;
	double							drawMatrix[6];
	double							lineWidthScale;
	BackgroundFillMode				backgroundFillMode;

public:
	VectorialHatchFillEffect (VectorialHatchDescriptorRef vectorialHatchDescriptor, double scaleX, double scaleY,
							  double rotate, const GS::Point<double>& translate, double lineWidthScale,
							  BackgroundFillMode backgroundFillMode = FillBackground);
	
	VectorialHatchFillEffect (VectorialHatchDescriptorRef vectorialHatchDescriptor, const double (*pDrawTransformationMatrix)[6],
							  double lineWidthScale, BackgroundFillMode backgroundFillMode = FillBackground);
	
	virtual ~VectorialHatchFillEffect ();

	bool	IsEqual (const VectorialHatchFillEffect& other) const;
};


// --- Symbol hatch effect -----------------------------------------------------

class GRAPHIX_DLL_EXPORT ISymbolHatchDescriptorImpl
{
public:
	virtual ~ISymbolHatchDescriptorImpl ();

	virtual	void		AddPoint (const GS::Point<double>& pt) = 0;
	virtual	void		AddPointList (const GS::Array<GS::Point<double>>& pointList) = 0;

	virtual void		AddLine (const GS::Point<double>& pt0, const GS::Point<double>& pt1) = 0;
	virtual void		AddLineTo (const GS::Point<double>& pt) = 0;
	virtual void		AddLineList (const GS::Array<GS::Point<double> >& lineEndPoints) = 0;
	virtual void		AddLineListTo (const GS::Array<GS::Point<double> >& lineEndPoints) = 0;
	virtual void		AddLineStrip (const GS::Array<GS::Point<double> >& lineStripPoints) = 0;
	virtual void		AddLineStripTo (const GS::Array<GS::Point<double> >& lineStripPoints) = 0;

	virtual void		AddArc (const GS::Point<double>& ptCenter, const GS::Point<double>& ptBeg, double deltaAngle) = 0;
	virtual void		AddArcTo (const GS::Point<double>& ptCenter, const GS::Point<double>& ptBeg, double deltaAngle) = 0;
	virtual void		AddArc (const GS::Point<double>& ptCenter, double radius, double begAng, double deltaAngle) = 0;
	virtual void		AddArcTo (const GS::Point<double>& ptCenter, double radius, double begAng, double deltaAngle) = 0;
	virtual void		AddArcSegment (const GS::Point<double>& ptBeg, const GS::Point<double>& ptEnd, double deltaAngle) = 0;
	virtual void		AddArcSegmentTo (const GS::Point<double>& ptBeg, const GS::Point<double>& ptEnd, double deltaAngle) = 0;

	virtual bool		BeginAddPolygon () = 0;
	virtual void		NewContour () = 0;
	virtual void		EndAddPolygon () = 0;

	virtual void		AppendGeometryFrom (const ISymbolHatchDescriptorImpl& hatchImpl) = 0;
	virtual bool		IsEqual (const ISymbolHatchDescriptorImpl& hatchImpl) const = 0;

	virtual void		Finalize () = 0;
};

typedef		GS::CountedPtr<ISymbolHatchDescriptorImpl, GS::AtomicCounter> SymbolHatchDescriptorRef;

// Transformation for a hatch primitive: tileScale * tilingVect * hatchMatrix * drawMatrix

class GRAPHIX_DLL_EXPORT SymbolHatchFillEffect: public FillEffect
{
public:
	enum BackgroundFillMode
	{
		FillBackground		=	0,
		OmitFillBackground,

		LastValue = OmitFillBackground
	};

public:
	SymbolHatchDescriptorRef	symbolHatchDescriptor;
	double						drawMatrix[6];
	double						lineWidthScale;
	BackgroundFillMode			backgroundFillMode;

public:
	SymbolHatchFillEffect (SymbolHatchDescriptorRef	symbolHatchDescriptor, double scaleX, double scaleY, double rotate,
						   const GS::Point<double>& translate, double lineWidthScale, BackgroundFillMode backgroundFillMode = FillBackground);

	SymbolHatchFillEffect (SymbolHatchDescriptorRef	symbolHatchDescriptor, const double (*pDrawTransformationMatrix)[6],
						   float lineWidthScale, BackgroundFillMode backgroundFillMode = FillBackground);
	
	virtual ~SymbolHatchFillEffect ();

	bool	IsEqual (const SymbolHatchFillEffect& other) const;
};


// --- Fill effect factoring ---------------------------------------------------

// A hatch matrix pointer can be null, indicating identity matrix

class GRAPHIX_DLL_EXPORT FillEffectFactory
{
public:

	static	VectorialHatchDescriptorRef		CreateVectorialHatchDescriptor (const double (*pHatchMatrix)[6], double lineWidth);
	static	SymbolHatchDescriptorRef		CreateSymbolHatchDescriptor (const GS::Point<double>& tilingVectX, const GS::Point<double>& tilingVectY, double tileScaleX, double tileScaleY,
																		 const double (*pHatchMatrix)[6], double lineWidth);
};

}

#endif	// namespace NewDisplay
