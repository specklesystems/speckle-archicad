/****************************************************************************/
/*																			*/
/*			GLOBAL CONSTANTS, TYPES AND MACROS FOR EN... ROUTINES			*/
/*																			*/
/****************************************************************************/

#ifndef _envir_H_
#define _envir_H_

#pragma once

#include	"GSModelerPrivExp.h"

#include	"GSPix.h"		// for GS_RGBColor
#include	"Projection.h"
#include	"GSModelerExport.h"
#include	"UniString.hpp"
#include	"SharedObject.hpp"
#include	"SightPtr.hpp"
#include	"Sector3DData.h"
#include	"Pair.hpp"

// from CADInfrastructure
#include "ADBAttributeIndex.hpp"

/* ----------------------------- Display type bits ------------------------ */

/*	For DRAW_MODE			true view(/fit to window) for perspective		*/
#define	TRUEVIEWBIT		0x0001					/*	0b0000000000000001		*/
/*	For DRAW_MODE			display rectangle of the perspective projection	*/
#define	PERSPRECTBIT	0x0002					/*	0b0000000000000010		*/
/*	For DRAW_MODE			thick lines (2 pixels)							*/
#define	THICK_BIT		0x0004					/*	0b0000000000000100		*/
/*	For DRAW_MODE			show using pen #1								*/
#define	UNIFORMBIT		0x0008					/*	0b0000000000001000		*/
/*	For DRAW_MODE			show not only contour edges						*/
#define	ALLEDGESBIT		0x0010					/*	0b0000000000010000		*/
/*	For DRAW_MODE			mask for effect bits							*/
#define	EFFECTS_MASK	0xFFE0					/*	0b1111111111100000		*/

/*================================	CONSTANTS	============================*/

// For DRAW_MODE
// EFFECTS bits:
#define	E_VECTORHATCH		0x0040				//	0b0000000001000000
#define	E_VECTORSHADOW		0x0080				//	0b0000000010000000
#define	E_CUTINCONVERT		0x0400				//	0b0000010000000000

// For HIDDDRAWBITS
#define	H_SONLYVISBODY		0x0200				//	0b0000001000000000
#define	H_SKIPCUTEDGES		0x0400				//	0b0000010000000000
#define	H_TRANSPARSHAD		0x0800				//	0b0000100000000000
// 0x1000	empty
#define	H_HIDDENLINES		0x2000				//	0b0010000000000000

namespace GS {
	class IChannel;
	class OChannel;
	class ProcessControl;
}


/*================================	 TYPES	================================*/

/* ----------------------------- VIEW DATA STRUCTURE ---------------------- */

// Data of a projection definition	// Read/Write(XML) functions implemented in PROJSETS::, use same type if needed.
struct GSMODELER_PRIVATE_EXPORT ZOOMDEF {
	double		scx, scy,				// Scale factors
				dxx, dyy;				// and offsets
										/*	Screen (x, y) --> Pixel (x', y')
										x' =   scx * x + dxx;
										y' = -(scy * y + dyy);	*/

	ZOOMDEF () : scx (0.0), scy (0.0), dxx (0.0), dyy (0.0)
		{ /* do nothing */ }
	ZOOMDEF (double scx, double scy, double dxx, double dyy) : scx (scx), scy (scy), dxx (dxx), dyy (dyy)
		{ /* do nothing*/ }
		
	bool IsNear (const ZOOMDEF& other, double eps = Eps) const;
};		/* 32 */

struct SHOWSETS {		// Read/Write(XML) functions implemented in PROJSETS::, use same type if needed.
	short		showType;			// Wire, hidden, shaded...			 (2)
	STATW		drawMode;			// Draw type bits:					 (2)
									// thick line, uniform, box...true view
									// Intersect.s, shadow lines, hatch..
};		/*  4 */

struct SUNGSETS {		// Read/Write(XML) functions implemented in VIEWSETS::, use same type if needed.
	float		sunDirx, sunDiry, sunDirz;	// Sun direction					(12)
	float		sunAngxy, sunAngz;			// Copy of the angles in View dialog (8)
};		/* 20 */

struct SUNLSETS {		// Read/Write(XML) functions implemented in VIEWSETS::, use same type if needed.
	GS_RGBColor	sunRGB;				// Sun RGB							 (6)
	GS_RGBColor	ambientRGB;			// Ambient RGB						 (6)
	GS_RGBColor	filler1;
	short		filler2;
};		/* 20 */

struct ShortRect {
	short	top;
	short	left;
	short	bottom;
	short	right;

	GSErrCode	Read		(GS::IChannel& ic);
	GSErrCode	Write		(GS::OChannel& oc) const;

	GSErrCode	ReadXML		(GS::XMLIChannel& ic);
	GSErrCode	WriteXML	(GS::XMLOChannel& oc) const;

	bool		operator==	(const ShortRect& other) const {
		return top == other.top && left == other.left && bottom == other.bottom && right == other.right;
	}

	bool		operator!=	(const ShortRect& other) const {
		return !operator== (other);
	}

	ULong		GenerateHashValue () const {
		return GS::CalculateHashValue (top, left, bottom, right);
	}
};

enum ScaleType {
	ScaleType_ToFill	= 0,
	ScaleType_ToFit		= 1
};

enum BKGScaleType {
	BKGScaleType_ToFit		= 0,
	BKGScaleType_ToFill		= 1,
	BKGScaleType_Custom		= 2
};

/* --------------------------- RENDERING PARAMETERS ----------------------- */

struct GSMODELER_DLL_EXPORT RENDSETS_AC17 {
/*0*/
	bool			transparentOn,
					smoothOn,
					shadowOn,
					emissionOn,
					highlightOn,
					decayOn,
					lightFallOn,
					textureOn;
	short			rendMethod;			/*	1: McLtd scanline method
										2: modified McLtd scanline method	*/
	short			shadowMode;			/*	Mode of shadow pre-selection
										1: ----
										2: automatic shadows
										3: all cast shadows
										4: only explicit shadows			*/
	short			lightMode;			/*	Mode of light usage
										1: sun
										2: sun shadows
										4: other lights
										8: other lights with shadows		*/
	short			rendEffects;		/*	introduced: 95.10.27
											ba95'10.27. dummy1 ==> rendEffects
											1: Use background alpha channel
											... See R_ above					*/
/*16*/
	float 			filler;
	short			fscan, lscan;		// First and last scanline to render (4)
	short			nscan;				// N.of scanlines treated together	 (2)
	short			fpixx, lpixx;		// First&last pixel along X to render(4)
	short			pixelStep;
	short			superSampling;
	short			overExpoMethod;		/*	1: cut
										2: rescale
										3: set to max
										4: error color			*/
/*36*/
	GS_RGBColor		overRGB;
	short			hSize, vSize;
	short			outRes;
	bool			proportional;
	bool			withoutTmpfile;
/*50*/
	GS_RGBColor		bkgSkyRGB;
	short			bkgSkyIndex;
	GS_RGBColor		bkgEarthRGB;
	short			bkgEarthIndex;
/*66*/
	short			bkgRes;
	short			textureAntialiasingLimit;
	short			filler1;
	short			scaleType;
	short			bkgScaleType;
	char			bkgImageName [32];		// MAXNAM == 32
	ShortRect		bkgPicRect;

	RENDSETS_AC17 ();
};

struct GSMODELER_DLL_EXPORT RENDSETS {
	DECLARE_ROOT_CLASS_INFO
public:
	short			rendMethod;			/*	1: McLtd scanline method
										2: modified McLtd scanline method	*/
	bool			useBkgAlpha;
	short			fscan, lscan;		// First and last scanline to render (4)
	short			nscan;				// N.of scanlines treated together	 (2)
	short			fpixx, lpixx;		// First&last pixel along X to render(4)
	short			hSize, vSize;
	short			outRes;
	bool			proportional;
	bool			withoutTmpfile;
	GS_RGBColor		bkgSkyRGB;
	short			bkgSkyIndex;
	GS_RGBColor		bkgEarthRGB;
	short			bkgEarthIndex;
	short			bkgRes;
	short			scaleType;
	short			bkgScaleType;
	GS::UniString	bkgImageName;

	ShortRect		bkgPicRect;

	RENDSETS ();
	RENDSETS (bool autoSave,
				short horizontalSize,
				short verticalSize,
				const GS_RGBColor& backgroundColor);
	RENDSETS (const RENDSETS& other);

	RENDSETS&	operator= (const RENDSETS& other);
	bool		operator== (const RENDSETS& other) const;
	bool		operator!= (const RENDSETS& other) const;

	void		Clear ();
	void		SetDefault ();
	void		ConvertFromOld (const RENDSETS_AC17& other);

	// paramList is for Basic Rendering engine-specific old members
	GSErrCode	Read		(GS::IChannel& ic, GS::HashTable<GS::UniString, double>* paramList);
	GSErrCode	Write		(GS::OChannel& oc) const;
	GSErrCode	Read		(GS::IChannel& ic, const short version, GS::HashTable<GS::UniString, double>* paramList);

	GSErrCode	ReadXML		(GS::XMLIChannel& ic);
	GSErrCode	WriteXML	(GS::XMLOChannel& oc) const;

	virtual ~RENDSETS ();
};

/* ------------------------- HIDDEN METHOD PARAMETERS --------------------- */

struct GSMODELER_DLL_EXPORT HIDDSETS_AC17 {
private:
	[[maybe_unused]] short filler;
public:
	short				hidd_drawBits;		// Bits for drawing of hidden methods		 ba95 02.16.
	short				hidd_lineType;		// Index of line type of hidden lines		 ba95 02.16.
	short				hidd_lineLength;	// Max lenght of special hidden lines		 ba95 02.16.

	HIDDSETS_AC17 () :
		filler				(0),
		hidd_drawBits		(0),
		hidd_lineType		(1),		// Solid line
		hidd_lineLength		(0)
	{
	}
};		/*  8 */

struct GSMODELER_DLL_EXPORT HIDDSETS {
	short				hidd_drawBits;		// Bits for drawing of hidden methods		 ba95 02.16.
	ADB::AttributeIndex	hidd_lineType;		// Index of line type of hidden lines		 ba95 02.16.
	short				hidd_lineLength;	// Max lenght of special hidden lines		 ba95 02.16.

	enum class OldReadWriteVersion
	{
		Version_1 = 1,
		Version_2 = 2
	};

	inline HIDDSETS () :
		hidd_drawBits		(0),
		hidd_lineType		(ADB::SolidLineAttributeIndex),
		hidd_lineLength		(0)
	{
	}

	void		ConvertFromOld (const HIDDSETS_AC17& other);
	
	GSErrCode	ReadOld			(GS::IChannel& ic, HIDDSETS::OldReadWriteVersion version);
	GSErrCode	WriteOld		(GS::OChannel& oc, HIDDSETS::OldReadWriteVersion version) const;

	GSErrCode	Read			(GS::IChannel& ic);
	GSErrCode	Write			(GS::OChannel& oc) const;

	GSErrCode	ReadXML			(GS::XMLIChannel& ic);
	GSErrCode	WriteXML		(GS::XMLOChannel& oc) const;

private:
	GSErrCode	ReadVersion1 (GS::IChannel& ic);
	GSErrCode	ReadVersion2 (GS::IChannel& ic);
	GSErrCode	WriteVersion2 (GS::OChannel& oc) const;
	GSErrCode	ReadVersion3 (GS::IChannel& ic);
	GSErrCode	WriteVersion3 (GS::OChannel& oc) const;

	static GS::ClassInfo classInfo;

};		/*  8 */


/* ------------------------- VECTOR SHADOW PARAMETERS --------------------- */

struct GSMODELER_DLL_EXPORT VESHSETS {
	bool			contureOff;	//	shadow conture
	unsigned char	oneplane;	//	0 - allplanes	1 - oneplane
	short			selfShad;	//	0 - off	1 - mark 2 - generate
	float			elevation;	// 	oneplane - elevation level
	Int32			dummy1, dummy2, dummy3, dummy4;
	Int32			dummy5, dummy6;

	inline VESHSETS () :
		contureOff (false),
		oneplane (0),
		selfShad	(0),
		elevation (0.0),
		dummy1 (0),
		dummy2 (0),
		dummy3 (0),
		dummy4 (0),
		dummy5 (0),
		dummy6 (0)
	{
	}

	// Object I/O
	GSErrCode	ReadVersion1  (GS::IChannel& ic);
	GSErrCode	WriteVersion1 (GS::OChannel& oc) const;

	GSErrCode	Read (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;

	GSErrCode	ReadXML (GS::XMLIChannel& ic);
	GSErrCode	WriteXML (GS::XMLOChannel& oc) const;
};		/* 32 */


/* --------------------------- CAMERA DATA STRUCTURE ---------------------- */

struct CAMERA {
	PEAXDEF		peaxDat;											// (152)
	SHOWSETS	showDat;											//	 (4)
	SUNGSETS	sungSets;											//	(20)

	double		filler[7];
	short		hor, ver;					// Window size in pixels
	Int32		dummy;
};		/* 240 */


enum class	CopyOpts_ConstructElements : short
{
	None			= 1,
	Edges			= 2,
	Polys			= 3,
	EdgePolys		= 4
};

enum class	CopyOpts_ShadowElements : short
{
	None			= 1,
	Edges			= 2,
	Polys			= 3,
	EdgePolys		= 4
};

enum class	CopyOpts_3DHatchElements : short
{
	None			= 1,
	HatchingLines	= 2,
	Polygons		= 3
};

enum class	CopyOpts_ClipPgons : short
{
	Overlap			= 1,
	Split			= 2
};

enum class	CopyOpts_FramedPgon : short
{
	Framed			= 1,
	Frameless		= 2
};

enum class	CopyOpts_PictType : short
{
	PaintScrSh		= 1,
	Drawing			= 2,
	DrawingScaled	= 3
};

struct CopyOptionRec {
	CopyOpts_ConstructElements	constructElements;
	CopyOpts_ShadowElements		shadowElements;	
	CopyOpts_3DHatchElements	threeDHatchElements;
	CopyOpts_ClipPgons			clipPgons;
	CopyOpts_FramedPgon			framedPgon;
	CopyOpts_PictType			PICTtype;
	bool						compressbit;
	bool						elimCovered;		/* elimCoveredLines */
};

struct SurfaceSelection {
	short	red;
	short	green;
	short	blue;
	short	alpha;
	bool	selEnabled;
};

struct GBVars
{
	bool		patandnotcol;
	short		maxnorm;
};


namespace Modeler {
	class IAttributeReader;
}

namespace ModelerAPI {
	class IDrawEffects3D;
}

enum ContourMode : Int32 {
	ContourModeOff = 2,		/* Because of old project files */
	ContourModeDraft = 1,
	ContourModeBest = 3
};

class ModVisualizationEngineImpl;

class GSMODELER_DLL_EXPORT ModVisualizationEngine : public GS::SharedObject {
public:
	bool								MustFillHatches () const;
	bool								Must3DHatches () const;



private:
	friend class ModVisualizationEngineImpl;	//in order to be able to construct ModVisualizationEngine

	ModVisualizationEngine ();
	virtual ~ModVisualizationEngine ();

public:
	static ModVisualizationEngine*		New ();

	CopyOptionRec						theCopyOptionRec;
	SurfaceSelection					theSurfaceSelection;
	GBVars								theGBVars;
	GSRect								cRectw;			/* Clip rectangle				*/


	virtual void						SetContourMode (ContourMode contMode, bool preview) = 0;
	virtual ContourMode			GetContourMode () const = 0;

	void								HideLinesWithModel (
		GS::ProcessControl& processControl,
		Modeler::SightPtr sight,
		bool vectShadowOn,
		bool isTransparencyOn,
		const GS::Array<Sector3D>& linesIn,
		GS::Array<GS::Pair<Sector3D, UInt32> >& linesOut,
		ModelerAPI::IDrawEffects3D* drawEffects3D = nullptr);

	virtual ModVisualizationEngineImpl&		theEngine ();

};
#endif
