/****************************************************************
*  Description:	Functions to draw fill patterns					*
*																*
*  Contact person:	KiP											*
****************************************************************/

#ifndef FILLPATTERN_H
#define FILLPATTERN_H

#pragma once

// Geometry
#include	"Polygon2D.hpp"
#include	"IrregularPolygon2D.hpp"
#include	"Matrix.hpp"

// Pattern
#include	"PatternExport.h"
#include	"FillData.hpp"
#include	"GSPix.h"
#include	"HatchTran.hpp"
#include	"PatternTypeDefinitions.hpp"

#include	"FillPatternPrimitivesDrawer.hpp"


#if !defined (DrawTask_DEFINED)
#define	DrawTask_DEFINED
enum DrawTask { RebuildOnScreen, DrawOnDevice };
#endif

namespace Geometry {
	struct Polygon2DData;
}

//--------------------------------- Defines ------------------------------------

enum class HatchDensityValue {		/* HatchDensity return values */
	TooDense		= -1,
	ZeroSpacing		= 0,
	NormalDensity	= 1
};

//============================= HatchInfo Class ================================

namespace GX {
namespace Pattern {

class PATTERN_DLL_EXPORT HatchInfo {
// ... type definitions ................................................
public:
	enum DataMemberFlag {
		ClipBoxMember		= 0x0001,
		HatchTrafoMember	= 0x0002,
		FillMember			= 0x0004,
		FactorMember		= 0x0008,
		ScaleMember			= 0x0010,
		ArcDiffMember		= 0x0020,
		BgColorMember		= 0x0040,
		FgColorMember		= 0x0080,
		TransBgMember		= 0x0100,
		GradOrigoMember		= 0x0200,
		GradDataMember		= 0x0400,
		PolygonMember		= 0x0800
	};

// ... data members ....................................................
private:
	UInt32								filledDataMember;
	FillDataRef							fillData;
	GX::Pattern::HatchTran				hatchTrafo;
	double								factor;
	double								scalePaperToModel;	/* AC: currEn->dScale, PM: currDrawHead.drawScale */
	GS_RGBColor							backgroundRGB;
	GS_RGBColor							foregroundRGB;
	bool								transparentBg;
	GS::Ref<GS::Object>					additionalData;
		
// ... constructors and destructor .....................................
public:
	inline HatchInfo (FillDataRef actFillData);
	inline HatchInfo (const HatchInfo& source);
	inline ~HatchInfo ();

// ... comparison ......................................................
public:
	bool		operator==	(const HatchInfo& other) const;	
	bool		IsNear		(const HatchInfo& other) const;	

// ... assignment ......................................................
private:
	inline HatchInfo& operator= (const HatchInfo& source);

// ... get/set functions ...............................................
public:
	UInt32					GetFilledDataMember () const { return filledDataMember; }

	FillTypes				GetFillType (void) const { return fillData->GetType (); }
	const FillDataRef&		GetFillData	(void) const { return fillData; }

	void						SetHatchTran (const GX::Pattern::HatchTran& hatchTran) { hatchTrafo = hatchTran; filledDataMember |= HatchTrafoMember; }
	void						SetGlobalHatchTran (void) { hatchTrafo.SetGlobal (); filledDataMember |= HatchTrafoMember; }
	const GX::Pattern::HatchTran&	GetHatchTran (void) const { return hatchTrafo; }
	GX::Pattern::HatchTran&			GetHatchTran (void) { return hatchTrafo; }

	void			SetFactor (double aFactor) { factor = aFactor; filledDataMember |= FactorMember; }
	double			GetFactor (void) const { return factor; }

	void			SetScalePaperToModel (double aScalePaperToModel) { scalePaperToModel = aScalePaperToModel; filledDataMember |= ScaleMember; }
	double			GetScalePaperToModel (void) const { return scalePaperToModel; }

	void				SetColor (const GS_RGBColor& bgColor, const GS_RGBColor& fgColor) { SetBackgroundColor (bgColor); SetForegroundColor (fgColor); }
	void				SetBackgroundColor (const GS_RGBColor& bgColor) { backgroundRGB = bgColor; filledDataMember |= BgColorMember; }
	const GS_RGBColor&	GetBackgroundColor (void) const { return backgroundRGB; }
	void				SetForegroundColor (const GS_RGBColor& fgColor) { foregroundRGB = fgColor; filledDataMember |= FgColorMember; }
	const GS_RGBColor&	GetForegroundColor (void) const { return foregroundRGB; }
	void				SetTransparentBg (bool transBg) { transparentBg = transBg; filledDataMember |= TransBgMember; }
	bool				GetTransparentBg (void) const { return transparentBg; }
	
	void						SetAdditionalData (const GS::Ref<GS::Object>& additionalDataP) { additionalData = additionalDataP; }
	const GS::Ref<GS::Object>&	GetAdditionalData (void) const { return additionalData; }

	void				LeaveThread ();

	bool Check () const;
	bool DataMemberFilled (DataMemberFlag memberId) const { return ((filledDataMember & memberId) != 0); }

	GSErrCode				WriteXML (GS::XMLOChannel& oc) const;
	static HatchInfo*		CreateFromXML (GS::XMLIChannel& ic);

	GSErrCode		Read	(GS::IChannel& ic);
	GSErrCode		Write	(GS::OChannel& oc) const;
};

inline	HatchInfo::HatchInfo (FillDataRef actFillData):
	fillData (actFillData)
{
	filledDataMember = 0;
	filledDataMember |= FillMember;
	factor = 1.0;
	scalePaperToModel = 1.0;
	backgroundRGB.red = backgroundRGB.green = backgroundRGB.blue = 0;
	foregroundRGB.red = foregroundRGB.green = foregroundRGB.blue = 0;
	transparentBg = false;
}

inline	HatchInfo::HatchInfo (const HatchInfo& source) :
	fillData (source.fillData)
{
	filledDataMember = 0;
	operator= (source);
}

inline	HatchInfo::~HatchInfo ()
{
}

inline	HatchInfo&	HatchInfo::operator= (const HatchInfo& source)
{
	DBASSERT(&source != nullptr);

	if (this != &source) {
		filledDataMember = source.filledDataMember;
		fillData = source.fillData;
		hatchTrafo = source.hatchTrafo;
		factor = source.factor;
		scalePaperToModel = source.scalePaperToModel;
		backgroundRGB = source.backgroundRGB;
		foregroundRGB = source.foregroundRGB;
		transparentBg = source.transparentBg;
		additionalData = source.additionalData;
	}

	return *this;
}

//============================  Function prototypes ============================

PATTERN_DLL_EXPORT
GSErrCode	DrawHatch (const GX::Pattern::HatchInfo&				hatchInfo,
					   const Geometry::IrregularPolygon2D&			polygon,
					   const Box2DData&								clipBox,
					   double										maxArcDiff,
					   GX::Pattern::FillPatternPrimitivesDrawer*	drawHatch,
					   GS::AbortInterfaceBase*						breaker = nullptr,
					   GS::Optional<Int32>							maxDrawableFillUnitNumber = GS::NoValue);

PATTERN_DLL_EXPORT
GSErrCode	DrawHatch (const GX::Pattern::HatchInfo&				hatchInfo,
					   const GX::Pattern::HatchTran&				hatchTran,
					   const Geometry::IrregularPolygon2D&			polygon,
					   const Box2DData&								clipBox,
					   double										maxArcDiff,
					   GX::Pattern::FillPatternPrimitivesDrawer*	drawHatch,
					   GS::AbortInterfaceBase*						breaker = nullptr,
					   GS::Optional<Int32>							maxDrawableFillUnitNumber = GS::NoValue);


PATTERN_DLL_EXPORT
GSErrCode	GetHatchToModelSpaceTransformation (const GX::Pattern::HatchInfo&	hatchInfo,
												Geometry::Matrix33&				transformation);

class PATTERN_DLL_EXPORT TransformedFillBoundsClass {	//template method
public:
	explicit TransformedFillBoundsClass (const GX::Pattern::FillData* fillData);
	virtual ~TransformedFillBoundsClass ();
	GSErrCode GetBounds (Box2DData* motifBox) const;

private:
	virtual bool IsValid () const = 0;
	virtual Coord GetTransformedCoord (const Coord& coord) const = 0;
	virtual GSErrCode AddGenArcBoundingBox (const GenArc& genArc, Box2DData* motifBox) const = 0;
	virtual GSErrCode AddSubFillArcBoundingBox (SymbolFillDetailsIterator& iterator, const SFFill& sffill, Box2DData* motifBox) const = 0;

	GSErrCode AddFillHotspotBounds (Box2DData* motifBox) const;
	GSErrCode AddFillLineBounds (Box2DData* motifBox) const;
	GSErrCode AddFillArcBounds (Box2DData* motifBox) const;
	GSErrCode AddFillSubFillBounds (Box2DData* motifBox) const;

protected:
	const GX::Pattern::FillData& fillDataRef;
};


class PATTERN_DLL_EXPORT TransformedFillBoundsClass_NoTran : public TransformedFillBoundsClass {
public:
	explicit TransformedFillBoundsClass_NoTran (const GX::Pattern::FillData* fillData);

private:
	virtual bool IsValid () const override;
	virtual Coord GetTransformedCoord (const Coord& coord) const override;
	virtual GSErrCode AddGenArcBoundingBox (const GenArc& genArc, Box2DData* motifBox) const override;
	virtual GSErrCode AddSubFillArcBoundingBox (SymbolFillDetailsIterator& iterator, const SFFill& sffill, Box2DData* motifBox) const override;
};


}}	// namespace GX::Pattern 

PATTERN_DLL_EXPORT
HatchDensityValue	HatchDensity (const GX::Pattern::FillData& fillData, double scalePaperToModel, double minSpac, const Geometry::Matrix<2,2,double>& matrix);

PATTERN_DLL_EXPORT
HatchDensityValue	HatchDensityOnPixelSize (const GX::Pattern::FillDataRef& fillData, double scalePaperToModel, double meterToPixel, const Geometry::Matrix<2,2,double>& matrix);

PATTERN_DLL_EXPORT
short	GetHatchDensityChangePixelSize (const GX::Pattern::FillDataRef& fillData, double scalePaperToModel);

PATTERN_DLL_EXPORT
GX::Pattern::FillData*	AskDenseFillAttrib (double spac, const GSPattern& fullPat, double scalePaperToModel, double minSpacing);

PATTERN_DLL_EXPORT
GSErrCode	GetHatchTran4FitToPoly (const Geometry::IrregularPolygon2D& poly, bool FitToPoly, bool& straightPoly, GX::Pattern::HatchTran& hatchTrafo);

PATTERN_DLL_EXPORT
GSErrCode	GetAttr4FitToPoly (const Coord* polyCoords, Int32 polyCoordsNum, const UInt32* subPolyEnds, Int32 subPolyEndsNum, bool& straightPoly, Coord& fillOrigin, double& skinThick, Vector& direction);

PATTERN_DLL_EXPORT
void	GetHatchLongestEdgeAndSkinThickWithDirection (const Geometry::IrregularPolygon2D& poly, Sector& longestEdge, Vector& skinThickWithDirection);

#endif
