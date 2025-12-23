// Contact person : KiP

#ifndef FILLDATA_HPP
#define FILLDATA_HPP

#pragma once

// GSRoot
#include "UniString.hpp"

// Pattern
#include "PatternExport.h"
#include "FillTypeDefinitions.hpp"
#include "VectorFillDetails.hpp"
#include "SymbolFillDetails.hpp"
#include "GSPix.h"


namespace GX 
{
namespace Pattern 
{

class PATTERN_DLL_EXPORT FillData 
{
	static GS::ClassInfo classInfo;

public:
	FillData ();
	FillData (const FillData& source);
	~FillData ();

	FillData&			operator=	(const FillData& source);
	bool				operator==	(const FillData& other) const;	// TODO KiP ebben mindig csak az adott FillType-nal ertelmes membereket kellene osszehasonlitani
	bool				operator!=	(const FillData& other) const;
	bool				IsNear		(const FillData& other) const;

	GS::UniString		GetName						() const { return name; }
	FillTypes			GetType						() const { return fillType; }
	short				GetFlags					() const { return flags; }
	void				GetPattern					(GSPattern* pattern) const { if (pattern != nullptr) BNCopyMemory (pattern, &bitPat, sizeof (GSPattern)); }
	double				GetXSpacingFactor			() const { return hXSpac; }
	double				GetYSpacingFactor			() const { return hYSpac; }
	double				GetAngle					() const { return hAngle; }
	const Vector&		GetFirstOffset				() const { return firstOffset; }
	const Vector&		GetSecondOffset				() const { return secondOffset; }
	double				GetPercent					() const { return percent; }
	short				GetChangeToSolidFillSize	() const { return chSolidFillSize; }
	const Box2DData&	GetSymbolMotifRect			() const { return symbolMotifRect; }
	GS::UniString		GetTextureName				() const { return textureName; }
	short				GetTextureStatus			() const { return textureStatus; }
	double				GetTextureWidth				() const { return textureXSize; }
	double				GetTextureHeight			() const { return textureYSize; }
	double				GetTextureRotationAngle		() const { return textureRotAng; }

	bool				IsVectorFill				() const { return (fillType == VectorFill); }
	bool				IsSymbolFill				() const { return (fillType == SymbolFill); }
	bool				IsImageFill					() const { return (fillType == ImageFill); }
	bool				IsSolidFill					() const { return (fillType == SolidFill); }
	bool				IsSolidFgFill				() const { return (fillType == SolidFill && fabs (percent - 1.0) < Eps); }
	bool				IsSolidBgFill				() const { return (fillType == SolidFill && fabs (percent) < Eps); }
	bool				IsGradientFill				() const { return IsLinearGradientFill () || IsRadialGradientFill (); };
	bool				IsLinearGradientFill		() const { return (fillType == LinearGradientFill); }
	bool				IsRadialGradientFill		() const { return (fillType == RadialGradientFill); }
	bool				IsScaledFill				() const { return (flags & ScaledFill) > 0; }
	bool				IsSectionFill				() const { return (flags & SectionFill) > 0; }
	bool				IsDrawingFill				() const { return (flags & DrawingFill) > 0; }
	bool				IsSurfaceFill				() const { return (flags & SurfaceFill) > 0; }	
	bool				IsPercentFill				(double *percentValue = nullptr) const;		// TODO KiP Ez egyszerre mondja meg, hogy percent fill-e illetve adja ki az erteket. Erre ket fuggveny kellene.

	const VectorFillDetails*	GetVectorFillDetails	() const { return IsVectorFill () ? &vectorFillDetails : nullptr; }
	VectorFillDetails*			GetVectorFillDetails	()		 { return IsVectorFill () ? &vectorFillDetails : nullptr; }
	const SymbolFillDetails*	GetSymbolFillDetails	() const { return IsSymbolFill () ? &symbolFillDetails : nullptr; }
	SymbolFillDetails*			GetSymbolFillDetails	()		 { return IsSymbolFill () ? &symbolFillDetails : nullptr; }


	void				SetName						(GS::UniString name)				{ this->name = name; }
	void				SetType						(FillTypes fillType)				{ this->fillType = fillType; }
	void				SetFlags					(short flags)						{ this->flags = flags; }
	void				AddPropertyToFlags			(short flag)						{ this->flags |= flag; }	// TODO KiP igy olyan flag-eket fuzunk hozza, amik nem itt vannak definialva, ez nem jo
	void				SetPattern					(const GSPattern& newPattern);
	void				SetXSpacingFactor			(double xSpacingFactor)				{ this->hXSpac = xSpacingFactor; }
	void				SetYSpacingFactor			(double ySpacingFactor)				{ this->hYSpac = ySpacingFactor; }
	void				SetAngle					(double angle)						{ this->hAngle = angle; }
	void				SetFirstOffset				(const Vector& firstOffset)			{ this->firstOffset = firstOffset; }
	void				SetSecondOffset				(const Vector& secondOffset)		{ this->secondOffset = secondOffset; }
	void				SetPercent					(double percent)					{ this->percent = percent; }
	void				SetChangeToSolidFillSize	(short chSolidFillSize)				{ this->chSolidFillSize = chSolidFillSize; }
	void				SetSymbolMotifRect			(const Box2DData& symbolMotifRect)	{ this->symbolMotifRect = symbolMotifRect; }
	void				SetTextureName				(const GS::UniString& textureName)	{ this->textureName = textureName; }
	void				SetTextureStatus			(short textureStatus)				{ this->textureStatus = textureStatus; }
	void				SetTextureWidth				(double textureWidth)				{ this->textureXSize = (textureWidth < Eps) ? 1.0 : textureWidth; }
	void				SetTextureHeight			(double textureHeight)				{ this->textureYSize = (textureHeight < Eps) ? 1.0 : textureHeight; }
	void				SetTextureRotationAngle		(double textureRotationAngle)		{ this->textureRotAng = textureRotationAngle; }

	void				SetVectorFillDetails		(const VectorFillDetails& vectorFillDetails);
	void				SetSymbolFillDetails		(const SymbolFillDetails& symbolFillDetails);

	GSErrCode			Write						(GS::OChannel& oc) const;
	GSErrCode			Read						(GS::IChannel& ic);
	GSErrCode			WriteXML					(GS::XMLOChannel& oc) const;
	GSErrCode			ReadXML						(GS::XMLIChannel& ic);

private:
	GSErrCode			WriteVersion1				(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode			ReadVersion1				(GS::IChannel& ic, const GS::InputFrame& frame);

public: 
	static short		ConvertFillTypesToShort		(FillTypes fillTypes);
	static FillTypes	ConvertShortToFillTypes		(short shortFillType);

private:
	GS::UniString		name;				// TODO KiP kiirtani
	FillTypes			fillType;
	short				flags;
	GSPattern			bitPat;				// the bitmap pattern
	double				hXSpac;				// spacing factor of the fill in the X direction
	double				hYSpac;				// spacing factor of the fill in the Y direction
	double				hAngle;				// angle of the fill pattern
	Vector				firstOffset;		// symbol fill offset
	Vector				secondOffset;		// symbol fill offset
	double				percent;			// percent for background and foreground fills
	mutable short		chSolidFillSize;	// size in pixels, when it can be substituted with solid fill
	mutable Box2DData	symbolMotifRect;	// cached bound of symbol fills
	GS::UniString		textureName;
	short				textureStatus;		// TEXMIRRORY | TEXMIRRORX
	double				textureXSize;
	double				textureYSize;
	double				textureRotAng;
	VectorFillDetails	vectorFillDetails;
	SymbolFillDetails	symbolFillDetails;
};

}  
}

#endif
