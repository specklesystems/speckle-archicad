/*==========================================================================**
**								GDLDefs.h									**
**																			**
**					CONSTANTS AND TYPES FOR THE GDL LIBRARY					**
**==========================================================================*/

#ifndef _gdlDefs_H_
#define _gdlDefs_H_

#pragma once

#include	<math.h>

#include	"GSRoot.hpp"
#include	"HashTable.hpp"
#include	"SharedObject.hpp"
#include	"TRANMAT.h"
#include	"SegmentationRule.hpp"
#include	"GDLExport.h"
#include	"Owner.hpp"
#include	"UniString.hpp"
#include	"GSUtilsDefs.h"
#include	"GDLDictionary.hpp"

#include	"ADBAttributeIndex.hpp"
#include	"Variant.hpp"

/*==========================================================================**
**								Predeclarations								**
**==========================================================================*/

namespace GDL
{
	class IFileRef;
	class ParameterGetter;
	class Parameters;
}

/*==========================================================================**
**								CONSTANTS 									**
**==========================================================================*/


#define Max_AddPar_Num 1024 // Maximal number of additional parameters
#define Max_Par_Length   31 // Maximal length of parameter name

/*
Constants for GDL file types.
Only files of type TEXT_GDL can be processed by this library.
----------------------------------------------------------------------------*/

#define	UNKNOWN_GDL		0
#define	TEXT_GDL		1				/* 'TEXT','TXGL'					*/
#define	DOOR_GDL		2				/* 'DSYM'							*/
#define	WINDOW_GDL		3				/* 'WSYM'							*/
#define	LIGHT_GDL		4				/* 'LSYM'							*/
#define	OBJ_GDL			5				/* 'GSYM','RSYM'					*/
#define	PICT_GDL		6				/* 'PICT'							*/
#define	ESYM_GDL		7				/* 'ESYM'							*/

#define	GPS_GDL		   13				/* '.GPS							*/

enum GDL_ScriptType {
	GDL_UNDEF_SCRIPT = 0,
	GDL_PR_SCRIPT,
	GDL_2D_SCRIPT,
	GDL_3D_SCRIPT,
	GDL_UI_SCRIPT,
	GDL_VL_SCRIPT,
	GDL_1D_SCRIPT,
	GDL_FWM_SCRIPT,
	GDL_BWM_SCRIPT
};

static	const GDL_ScriptType GDL_FIRST_SCRIPTTYPE = GDL_PR_SCRIPT;
static	const GDL_ScriptType GDL_LAST_SCRIPTTYPE = GDL_BWM_SCRIPT;

#define	GDL_NUM_SCRIPTS	8
static_assert (1 + (Int32)GDL_LAST_SCRIPTTYPE - (Int32)GDL_FIRST_SCRIPTTYPE == GDL_NUM_SCRIPTS, "The value of this define should be kept in synch with the list of script types");

enum	BinaryCachingMode {
	DoNotCacheBinaries,
	CacheBinaries
};



#define GDL_UNDEF		0
#define GDL_GLOB		1
#define GDL_PAR			2
#define GDL_VAR			3

#define		TO_UNDEFINED		0
#define		TO_WALLS			1
#define		TO_DOORS			2
#define		TO_WINDOWS			3
#define		TO_OBJECTS			4
#define		TO_LIGHTS			5
#define		TO_HATC				6
#define		TO_CEILS			7
#define		TO_ROOFS			8
#define		TO_COLUMNS			9
#define		TO_ROOMS			10
#define		TO_MESHES			11
#define		TO_BEAMS			12
#define		TO_CURTAINWALLS		13
#define		TO_CWFRAMES			14
#define		TO_CWPANELS			15
#define		TO_CWJUNCTIONS		16
#define		TO_CWACCESSORIES	17
#define		TO_SHELLS			18
#define		TO_SKYLIGHTS		19
#define		TO_FREESHAPES		20
#define		TO_STAIR			21
#define		TO_STAIRTREAD		22
#define		TO_STAIRRISER		23
#define		TO_STAIRSTRUCTURE	24
#define		TO_RAILING			25

/*
Constants for font family types used in GDL style definitions
----------------------------------------------------------------------------*/

#define GDLFONTFAMILYNAME	0		/* name of a font family				*/
#define GDLPLOTTERFONT		1		/* PLOTTER		keyword					*/
#define GDLPLOTMAKERFONT	2		/* PLOTMAKER	keyword					*/

/*----------------------------------------------------------------------------
*/

/*
Constants for property data element codes used in Various GDL Requests
----------------------------------------------------------------------------*/

#define PR_ISCOMP			1		/* 				*/
#define PR_DBSETNAME		2		/* 				*/
#define PR_KEYCODE			3		/* 				*/
#define PR_KEYNAME			4		/* 				*/
#define PR_CODE				5		/* 				*/
#define PR_NAME				6		/* 				*/
#define PR_FULLNAME			7		/* 				*/
#define PR_QUANTITY			8		/* 				*/
#define PR_TOTQUANTITY		9		/* 				*/
#define PR_UNITCODE			10		/* 				*/
#define PR_UNITNAME			11		/* 				*/
#define PR_UNITFORMATSTR	12		/* 				*/
#define PR_PROPOBJNAME		13		/* 				*/

#define MI_PARS_FIRST_RES	16		/*	First in grc*/
#define MI_PARS_FIRST		13		/*	First MI	*/

#define MI_SURFACE_RGB		13		/*				*/
#define MI_AMBIENT			14		/*				*/
#define MI_DIFFUSE			15		/*				*/
#define MI_SPECULAR			16		/*				*/
#define MI_TRANSPARENT		17		/*				*/
#define MI_SHINING			18		/*				*/
#define MI_TRANSP_ATT		19		/*				*/
#define MI_SPECULAR_RGB		20		/*				*/
#define MI_EMISSION_RGB		21		/*				*/
#define MI_EMISSION_ATT		22		/*				*/
#define MI_FILL_IND			23		/*				*/
#define MI_FILLCOLOR_IND	24		/*				*/
#define MI_TEXTURE			25		/*				*/

#define MI_SURFACE_R		26		/*				*/
#define MI_SURFACE_G		27		/*				*/
#define MI_SURFACE_B		28		/*				*/

#define MI_SPECULAR_R		29		/*				*/
#define MI_SPECULAR_G		30		/*				*/
#define MI_SPECULAR_B		31		/*				*/

#define MI_EMISSION_R		32		/*				*/
#define MI_EMISSION_G		33		/*				*/
#define MI_EMISSION_B		34		/*				*/

#define MI_REQ_PARS_LAST		34	/*	Last MI	for request	*/
#define MI_REQ_PARS_LAST_RES	37	/*	Last in grc */

// non requestable parameters:

#define MI_TEXTURE_IND		35		/*				*/

#define MI_PARS_LAST		35		/*	Last MI		*/
#define MI_PARS_LAST_RES	38		/*	Last in grc */

#define BMI_PARS_FIRST					36		/*	First BMI for request */
#define BMI_REQ_PARS_FIRST_RES			39		/*	First in grc */

#define BMI_BMAT_ID						36		/*				*/
#define BMI_BMAT_SURFACE				37		/*				*/
#define BMI_BMAT_DESCRIPTION			38		/*				*/
#define BMI_BMAT_MANUFACTURER			39		/*				*/
#define BMI_BMAT_COLLISIONDETECTION		40		/*				*/
#define BMI_BMAT_INTERSECTIONPRIORITY	41		/*				*/
#define BMI_BMAT_CUTFILL_PROPERTIES		42		/*				*/
#define BMI_BMAT_PHYSICAL_PROPERTIES	43		/*				*/

#define BMI_PARS_LAST					43		/*	Last BMI for request */
#define BMI_REQ_PARS_LAST_RES			46		/*	Last in grc */


#define PCI_PARS_FIRST					44		/*	First Profile Component Info param string for request */
#define PCI_REQ_PARS_FIRST_RES			47		/*	First in grc */

#define PCI_COMP_SURFACES				44
#define PCI_COMP_PENS					45
#define PCI_COMP_LINETYPES				46
#define PCI_BMAT						47
#define PCI_SURFACE						48
#define PCI_SHOWOUTLINE					49
#define PCI_OUTLINETYPE					50
#define PCI_OUTLINEPEN					51

#define PCI_PARS_LAST					51		/*	Last Profile Component Info param string for request */
#define PCI_REQ_PARS_LAST_RES			54		/*	Last in grc */

#define PROP_PARS_FIRST					52		/* First POP for request */
#define PROP_REQ_PARS_FIRST_RES			55		/* First in grc */

#define PROP_ALL						52
#define PROP_CORE						53
#define PROP_AC							54
#define PROP_IFC						55
#define PROP_CLASSIFICATION				56
#define PROP_PROFILE_PARAMETER			57
#define PROP_BUILTIN					58

#define PROP_PARS_LAST					58		/* Last POP for request */
#define PROP_REQ_PARS_LAST_RES			61		/* Last in grc */

/*----------------------------------------------------------------------------
*/

/*
GdlInfoBits constants
----------------------------------------------------------------------------*/

#define	MACROUSED				(1)				// Macro used in symbol
#define	RNDUSED					(1<<1)			// RND function used in symbol
#define	SETBMATUSED				(1<<2)			// SET BUILDING_MATERIAL used in symbol
#define	N_USED		 			(1<<3)			// N_ used in symbol
#define	VIEWOBJUSED				(1<<4)			// K~...P~ used in symbol
#define	FRAGMENT2USED			(1<<5)			// FRAGMENT2 used in symbol
#define	PROJECT2USED			(1<<6)			// PROJECT2 used in symbol
//#define	FILLDEFUSED			(1<<7)			// DEFINE FILL used in symbol	// All 32 bits were used, but I had to use one more, so disabled this.
#define NONDETERMINISTICADDON	(1<<7)			// non deterministic addon used
#define	PIPGPICTUSED			(1<<8)			// PIPG statement used in symbol
#define	MATERDEFUSED			(1<<9)			// DEFINE MATERIAL used in symbol
#define	CALLBINARY				(1<<10)			// Call one or more BINARY macro(s)
#define	MODELSTATUSED			(1<<11)			// MODEL statement used in symbol
#define	LIGHTGENER				(1<<12)			// Generating Light-sources
#define	TEXTUREDEFUSED			(1<<13)			// DEFINE TEXTURE used in symbol
#define	VARMACRONAME			(1<<14)			// Macro name was defined as variable
#define	FILEOPERATION			(1<<15)			// File operations (open) used in symbol
#define	REQUESTUSED				(1<<16)			// REQUEST function used in symbol
#define	HOLEGENERED				(1<<17)			// Hole generation is used
#define	UICOMMANDUSED			(1<<18)			// User interface command used
#define STWUSED					(1<<19)			// STW used in symbol
#define SUNG_USED				(1<<20)			// SUN globals are used in symbol		// FE #31092
#define HOLE2GENERED			(1<<21)			// WALLHOLE2, WALLBLOCK2,WALLLINE2 or WALLARC2 used
#define LIBRARYGLOBALUSED		(1<<22)			// LIBRARYGLOBAL used in symbol
#define SETMIGRATIONGUIDUSED	(1<<23)			// SETMIGRATIONGUID used in symbol
#define VARPICTURENAME			(1<<24)			// Picture name was defined as variable
#define VARREQUESTNAME			(1<<25)			// Request name was defined as variable
#define TEXTENGINEUSED			(1<<26)			// Text engine used
#define	NODRAWGENER				(1<<27)			// There aren't any drawing defs.
#define	BADMACROSBIT			(1<<28)			// Could not load the bits of macros
#define	NOMODELGENER			(1<<29)			// There aren't any model defs.
#define	EMPTYGDLCODE			(1<<30)			// There isn't any valid gdl code
#define STOREDVALUE				(1u<<31)		// Reserved: the value was stored


#define	FRAME_DEP_USED	(N_USED | VIEWOBJUSED | REQUESTUSED | SUNG_USED)
#define	GENERATEALWAYS	(VARMACRONAME | VARPICTURENAME | FILEOPERATION | REQUESTUSED)
#define	NONTHREADSAFE	(VARMACRONAME | VARREQUESTNAME | NONDETERMINISTICADDON)

// MODELSTATUSED was previously in the GENERATEALWAYS macro bab800

/*----------------------------------------------------------------------------
*/


// Additional Parameter Types
#define ParT_Integer			 0 // Integer      Additional Parameter Type
#define ParT_Length				 2 // Length       Additional Parameter Type
#define ParT_Angle				 3 // Angle        Additional Parameter Type
#define ParT_RealNum			 4 // Real Number  Additional Parameter Type
#define ParT_LightSw			 5 // Light On/Off Additional Parameter Type
#define ParT_ColRGB				 6 // RGB Color    Additional Parameter Type
#define ParT_Intens				 7 // Intemsity    Additional Parameter Type
#define ParT_LineTyp			 8 // Line Type    Additional Parameter Type
#define ParT_Mater				 9 // Material     Additional Parameter Type
#define ParT_FillPat			10 // Fillpattern  Additional Parameter Type
#define ParT_PenCol				11 // Pencolor     Additional Parameter Type
#define ParT_CString			12 // C String     Additional Parameter Type
#define ParT_Boolean			13 // bool         Additional Parameter Type
#define ParT_Separator			14 // Separator Line, no value
#define ParT_Title				15 // Title text, no value
#define ParT_BuildingMaterial	16 // Building material Additional Parameter Type
#define ParT_Profile			17 // Profile	   Additional Parameter Type
#define ParT_Dictionary			18 // Dictionary   Additional Parameter Type

// par_flags status bit values
#define ParFlg_Hidden   0x80 // hidden parameter
#define ParFlg_Disabled 0x40 // disabled parameter
#define ParFlg_Open     0x20 // show child params
#define ParFlg_SHidden  0x10 // parameter hidden from script

#define	SCRIPT_CONTROLLED_PARAM_FLAGS	(ParFlg_Disabled | ParFlg_Open | ParFlg_SHidden)

#define ParFlg_Unique	0x08 // unique parameter, do not copy this parameter automatically
#define ParFlg_Fixed	0x04 // fixed param, could not delete, but can modify its value
#define ParFlg_BoldName 0x02 // bold name
#define ParFlg_Child    0x01 // child param

// ValueListNumType flags
#define Vlv_LowerLimit  1
#define Vlv_LowerEqual  2
#define Vlv_UpperLimit  4
#define Vlv_UpperEqual  8
#define Vlv_Step       16


// Gdl_GLOBALSBITS_NUM * 4 bytes for the GDL globalsbits

#define	Gdl_GLOBALSBITS_LEN		24


// ui_infield{3} thumbnail types

#define TN_VALUE		 (0)
#define TN_NUMERICVALUE	(-1)
#define TN_CUSTOM		(-2)


enum class GDL_TextAlignment {
	Invalid		= 0,
	Left		= 1,
	Center		= 2,
	Right		= 3,
	Full		= 4
};


enum GDL_FontStyleBits
{
	GDL_FontStyleBoldBit				= 0x01,
	GDL_FontStyleItalicBit				= 0x02,
	GDL_FontStyleUnderlineBit			= 0x04,
	// - - -
	GDL_FontStyleObsoleteSuperScriptBit	= 0x20,
	GDL_FontStyleObsoleteSubScriptBit	= 0x40,
	GDL_FontStyleStrikeOutBit			= 0x80
};


enum class GDL_ComponentCollectMode
{
	AllComponents					= 1,
	VisibleComponentsByCutPlane		= 2
};


enum class GDL_PropertyValueStatus
{
	Normal			= 1,
	UserUndefined	= 2,
	NotAvailable	= 3,
	NotEvaluable	= 4
};


enum class GDL_PropertyValueType
{
	Boolean		= 1,
	Integer		= 2,
	Number		= 3,
	String		= 4,
	Length		= 5,
	Area		= 6,
	Volume		= 7,
	Angle		= 8
};


enum class GDL_Poly2DEdgeType
{
	Straight	= 0,
	Curved		= 1
};


// flags types


// for fill frame
#define FILLFRAME_NOTSET			0x0000
#define FILLFRAME_CONTOUR			0x0001
#define FILLFRAME_FILL				0x0002
#define FILLFRAME_CLOSEPOLYGON		0x0004

// for fillcategory
enum GDL_FillCategory {
	FILLCATEGORY_DRAFT	= 0,
	FILLCATEGORY_CUT	= 1,
	FILLCATEGORY_COVER	= 2
};

enum GDL_HatchCompatibilityLevel {
	DONT_SCALE_HATCHING = 0,
	OLDSTYLEGRADIENTDATA = 1,
	NEWSTYLEGRADIENTDATA = 2
};

// flag values, needed by GsModeler, ARCHICAD, etc...
enum {
	GS_FLAG_NOTSET					= 0x0000,
	GS_FLAG_XAXISGLOBAL				= 0x0001,
	GS_FLAG_YAXISGLOBAL				= 0x0002,
	GS_FLAG_USEINNERRADIUS			= 0x0004,
	GS_FLAG_GLOBAL_ORIENTATION		= 0x0008,
	GS_FLAG_FITX					= 0x0010,
	GS_FLAG_FITY					= 0x0020,
	GS_FLAG_KEEPPROPORTION			= 0x0040,
	GS_FLAG_ALIGNLOCALFILL_TO_WALL  = 0x0200
};

enum GDL_VertexType {
	SOFT_VERTEX = 0,
	HARD_VERTEX = 1
};

enum GDL_NurbsEdgeVisibilityType {
	DefaultVisibility			= 0,
	Invisible_NurbsEdge			= 1,
	VisibleIfContour_NurbsEdge	= 2,
	NurbsEdgeVisibilityUsedBits = Invisible_NurbsEdge | VisibleIfContour_NurbsEdge
};

enum GDL_NurbsEdgeSmoothness {
	NonSmoothNurbsEdge = 0,
	SmoothNurbsEdge	   = 4
};

struct GDL_NurbsEdgeStatus {
	GDL_NurbsEdgeVisibilityType nurbsEdgeVisibility;
	GDL_NurbsEdgeSmoothness		nurbsEdgeSmoothness;

	bool operator== (const GDL_NurbsEdgeStatus& other) const {
		return nurbsEdgeVisibility == other.nurbsEdgeVisibility && nurbsEdgeSmoothness == other.nurbsEdgeSmoothness;
	}
	static const Int32 usedBits = GDL_NurbsEdgeVisibilityType::NurbsEdgeVisibilityUsedBits | static_cast<Int32> (GDL_NurbsEdgeSmoothness::SmoothNurbsEdge);
};


struct GDL_NurbsBodyStatus {
	enum Bits {
		AlwaysCastsShadowBit	= 32,
		NeverCastsShadowBit		= 64,
		TessellateLaterBit		= 128,
		UsedBits = AlwaysCastsShadowBit | NeverCastsShadowBit | TessellateLaterBit
	};

	bool alwaysCastsShadow;
	bool neverCastsShadow;
	bool tessellateLater;

	GDL_NurbsBodyStatus (Int32 statusIn = 0) :
		alwaysCastsShadow ((statusIn & AlwaysCastsShadowBit) != 0),
		neverCastsShadow ((statusIn & NeverCastsShadowBit) != 0),
		tessellateLater ((statusIn & TessellateLaterBit) != 0)
	{
	}

	bool	operator== (const GDL_NurbsBodyStatus& other) const
	{
		return alwaysCastsShadow == other.alwaysCastsShadow &&
			neverCastsShadow == other.neverCastsShadow &&
			tessellateLater == other.tessellateLater;
	}

	bool	IsValidShadowStat () const
	{
		return !(alwaysCastsShadow && neverCastsShadow);
	}

	UInt32	GetShadowStat () const
	{
		return (alwaysCastsShadow ? AlwaysCastsShadowBit : 0) | (neverCastsShadow ? NeverCastsShadowBit : 0);
	}

	bool	IsToTessellateLater () const
	{
		return tessellateLater;
	}
};

enum GDL_PgonStatus {
	InvisiblePolygon = 1,
	CurvedPolygon = 2,
	ConcavePolygon = 16,
	PolygonHasHole = 32,
	HolesAreConvex = 64,
	FirstPolygonOfCurvedSurface = 4,
	LastPolygonOfCurvedSurface = 8,
	PgonStatusUsedBits = InvisiblePolygon | CurvedPolygon | ConcavePolygon | PolygonHasHole | HolesAreConvex | FirstPolygonOfCurvedSurface | LastPolygonOfCurvedSurface
};


//if the fill is gradient fill, and the poly2_b version is 4, then the gradient matrix should be converted.
#define FLAG_OLDSTYLEGRADIENTDATA 0x8000


/*================================  TYPES  =================================*/

typedef short PenType;

enum GEINDEXTYPE {GDL_INDEX, AC_INDEX, D3_INDEX};

struct GEINDEX
{
	GEINDEXTYPE								type;
	GS::Variant<ADB::AttributeIndex, Int32> index;

	GEINDEX () : type(AC_INDEX), index(ADB::InvalidAttributeIndex)
	{
	}

	void SetGEINDEXValue (GEINDEXTYPE type, Int32 index)
	{
		this->type = type;
		if(this->type == AC_INDEX)
			this->index = ADB::CreateAttributeIndex (index);
		else
			this->index = index;
	}

	Int32 ToInt32 () const 
	{
		if (index.Is<Int32> ())
			return index.Get<Int32> ();
		else
			return (index.Get<ADB::AttributeIndex> ()).ToGSAttributeIndex_Deprecated ();
	}
};

enum GEMODEL {
	GEWIRE,
	GESURFACE,
	GESOLID
};

enum GESHADOW {
	GESHAUTO,
	GESHON,
	GESHOFF
};

enum GEMacFileType {
	GEMACROFILE,
	GEIMAGE2DFILE,
	GEIMAGE3DFILE
};


struct FileLocRec {
	GDL::IFileRef*	fileRef;
	Int32			beglin;
	Int32			endlin;
};


struct GdlErrDisplayData {
	GSErr			lastErr;		/* Last error code						*/
	GSErr			lastsys;		/* Last found system error code			*/
	char			*lastMsg;		/* Last error message					*/
	Int32			lastLevel;		/* Last bad source call level			*/
	FileLocRec		lastLoc;		/* Last bad source statement location	*/
	FileLocRec		lastMain;		/* Last main source statement location	*/
	GDL_ScriptType	locScriptType;	/* GDL_1D_SCRIPT or other				*/
	GDL_ScriptType	mainScriptType;	/* GDL_1D_SCRIPT or other				*/
};


struct GdlInfoBits {
	Int32	globalsBits[Gdl_GLOBALSBITS_LEN];		// Bits for used global variables
	Int32	commandsBits;							// Other information - used commands

	GdlInfoBits ()
	{
		BNZeroMemory (globalsBits, Gdl_GLOBALSBITS_LEN * sizeof (Int32));
		commandsBits = 0;
	}
};

/* Expression types */
enum GdlValueType {NONETYPE, NUMTYPE, STRTYPE, GROUPTYPE, RUNTIMEIDTABLEINDEXTYPE, CODEAREAIDINDEXTYPE, DICTTYPE};

/* Numeric expression subtypes */
enum NumSubType {NONESUBTYPE, INTSUBTYPE, REALSUBTYPE};

class GdlValueRecord {
private:
	enum Flags {
		Uninitialized  = 0x0000,
		Initialized    = 0x0001
	};

	union {
		struct {
			Int32	lng;
			Int32	filler1;
		} lng;
		double		dbl;
	} value;
	GdlValueType	type;
	NumSubType		subtype;
	GS::Int8		flags;

public:
	GdlValueRecord (void);
	GdlValueRecord (const GdlValueRecord& source);
	GdlValueRecord& operator= (const GdlValueRecord& source);
	bool operator== (const GdlValueRecord& b) const;
	bool operator!= (const GdlValueRecord& b) const;

	GdlValueType	GetType (void) const;
	NumSubType		GetNumSubType (void) const;
	void			Clear ();
	void			SetType (GdlValueType type, NumSubType subtype);
	double			GetDouble (void) const;
	void			SetDouble (double dbl);
	Int32			GetLong (void) const;
	void			SetLong (Int32 lng);
	Int32			GetString (void) const;
	void			SetString (Int32 lng);
	Int32			GetRuntimeIdTableIndex (void) const;
	void			SetRuntimeIdTableIndex (Int32 lng);
	Int32			GetCodeAreaIdIndex (void) const;
	void			SetCodeAreaIdIndex (Int32 lng);
	Int32			GetGroup (void) const;
	void			SetGroup (Int32 lng);
	Int32			GetDict (void) const;
	void			SetDict (Int32 lng);
	bool			IsInitialized () const;

	GSErrCode		Write (GS::OChannel& oc) const;
	GSErrCode		Read (GS::IChannel& ic);
};

struct GdlTextBlockData {
	double		x;
	double		y;
	double		height;	// for 3D textblock
	double		hill;	// for 3D textblock
	double		width;
	double		angle;
	double		widthFactor;
	double		charSpaceFactor;
	unsigned char	anchor;
	bool		fixedHeight;
	Int32		resolution;		// for 3D textblock
	Int32		paramInd;		// parameter index if string is parameter
	Int32		ind1;			// actual array index 1 if string is parameter array
	Int32		ind2;			// actual array index 2 if string is parameter array
};

class GdlParagraphData {
public:
	short		alignment;
	short		filler_1;
	Int32		filler_2;
	double		firstLineIndent;
	double		leftIndent;
	double		rightIndent;
	double		lineSpacing;

	Int32		firstTabData;
	Int32		lastTabData;

	Int32		firstStringData;
	Int32		lastStringData;

	GdlParagraphData (void);
};

class GdlStringData {
public:
	short				styleInd;
	Int32				materInd;
	PenType				penInd;
	short				filler_1;
	Int32				firstChar;
	Int32				lastChar;

	GdlStringData (void);
};

class GDL_DLL_EXPORT GDLRequestResult
{
private:
	GS::Array<GdlValueRecord>	values;
	GS::Array<GS::UniString>	stringvals;
	GS::Array<GDL::Dictionary>	dictionaryvals;
public:
	static const double				DefaultDoubleValue;
	static const Int32				DefaultLongValue;
	static const GS::UniString		DefaultStringValue;
	static const GDL::Dictionary	DefaultDictionaryValue;

	GDLRequestResult () = default;
	GDLRequestResult (const GDLRequestResult& other) = default;
	GDLRequestResult (GDLRequestResult&& other) = default;
	GDLRequestResult& operator= (const GDLRequestResult& other) = default;
	GDLRequestResult& operator= (GDLRequestResult&& other) = default;

	USize GetSize () const;
	bool  IsEmpty () const;

	GdlValueType GetType (UIndex index) const;
	NumSubType	 GetNumSubType (UIndex index) const;

	double					GetDouble (UIndex index) const;
	Int32					GetLong (UIndex index) const;
	const GS::UniString&	GetString (UIndex index) const;
	const GdlValueRecord&	GetValueRecord (UIndex index) const;
	const GDL::Dictionary&	GetDictionary (UIndex index) const;

	void AddDouble (double val);
	void AddLong (Int32 val);
	void AddAttr (const ADB::AttributeIndex& val);
	void AddString (const GS::UniString& val);
	void AddNumValue (const GdlValueRecord& val);
	void AddDictionary (const GDL::Dictionary& val);

	void AddDefaultDoubleValueArray (Int32 count);
	void AddDefaultLongValueArray (Int32 count);
	void AddDefaultStringValueArray (Int32 count);
	void AddDefaultDictionaryValueArray (Int32 count);

	void Append (const GDLRequestResult& other);
	void Append (const GDLRequestResult& other, UIndex index);

	void Crop (Int32 size);

	void Clear ();

	void WriteForChecksum (GS::OChannel& oc) const;

	bool operator== (const GDLRequestResult &other) const;
	bool operator!= (const GDLRequestResult &other) const;
};

/*----------------------------------------------------------------------------
*/

inline GdlValueRecord::GdlValueRecord (void)
{
	this->Clear ();
}

inline GdlValueRecord::GdlValueRecord (const GdlValueRecord& val)
{
	type = val.type;
	subtype = val.subtype;
	value = val.value;
	flags = val.flags;
}

inline GdlValueRecord& GdlValueRecord::operator= (const GdlValueRecord& source)
{
	type = source.type;
	subtype = source.subtype;
	value = source.value;
	flags = source.flags;

	return *this;
}

inline bool GdlValueRecord::operator== (const GdlValueRecord& b) const
{
	return (type			== b.type			&&
			subtype			== b.subtype		&&
			flags			== b.flags			&&
			value.lng.lng	== b.value.lng.lng	&&
			value.dbl		== b.value.dbl)	? true : false;
}

inline bool GdlValueRecord::operator!= (const GdlValueRecord& b) const
{
	return !(*this == b);

}

inline void GdlValueRecord::SetType (GdlValueType type, NumSubType subtype)
{
	if (type == NUMTYPE) {
		this->type = NUMTYPE;
		if (subtype == REALSUBTYPE) {
			this->subtype = REALSUBTYPE;
			this->value.dbl = 0.0;
		} else {
			this->subtype = subtype;
			this->value.lng.lng = 0;
		}
	} else {
		this->type = type;
		this->subtype = NONESUBTYPE;
		this->value.lng.lng = 0;
	}
}

inline GdlValueType GdlValueRecord::GetType (void) const
{
	return this->type;
}

inline NumSubType GdlValueRecord::GetNumSubType (void) const
{
	return this->subtype;
}


inline void GdlValueRecord::Clear ()
{
	this->type = NUMTYPE;
	this->subtype = INTSUBTYPE;
	this->value.lng.lng = 0;
	this->value.lng.filler1 = 0;
	this->flags = Flags::Uninitialized;
}


inline double GdlValueRecord::GetDouble (void) const
{
	DBASSERT (this->type == NUMTYPE);

	if (this->subtype == REALSUBTYPE)
		return this->value.dbl;
	else
		return (double) this->value.lng.lng;
}

inline void GdlValueRecord::SetDouble (double dbl)
{
	this->type = NUMTYPE;
	this->subtype = REALSUBTYPE;
	this->value.dbl = dbl;
	this->flags = Flags::Initialized;
}

inline Int32 GdlValueRecord::GetLong (void) const
{
	DBASSERT (this->type == NUMTYPE);

	if (this->subtype == REALSUBTYPE)
		return (Int32) (this->value.dbl + ((this->value.dbl < 0.0) ? (- 0.5) : 0.5));		// FE #31466
	else
		return this->value.lng.lng;
}

inline void GdlValueRecord::SetLong (Int32 lng)
{
	this->type = NUMTYPE;
	this->subtype = INTSUBTYPE;
	this->value.lng.lng = lng;
	this->flags = Flags::Initialized;
}

inline Int32 GdlValueRecord::GetString (void) const
{
	DBASSERT (this->type == STRTYPE);

	return this->value.lng.lng;
}


inline void GdlValueRecord::SetString (Int32 lng)
{
	this->type = STRTYPE;
	this->subtype = NONESUBTYPE;
	this->value.lng.lng = lng;
	this->flags = Flags::Initialized;
}

inline Int32 GdlValueRecord::GetRuntimeIdTableIndex (void) const
{
	DBASSERT (this->type == RUNTIMEIDTABLEINDEXTYPE);

	return this->value.lng.lng;
}


inline void GdlValueRecord::SetRuntimeIdTableIndex (Int32 lng)
{
	this->type = RUNTIMEIDTABLEINDEXTYPE;
	this->subtype = NONESUBTYPE;
	this->value.lng.lng = lng;
	this->flags = Flags::Initialized;
}

inline Int32 GdlValueRecord::GetCodeAreaIdIndex (void) const
{
	DBASSERT (this->type == CODEAREAIDINDEXTYPE);

	return this->value.lng.lng;
}


inline void GdlValueRecord::SetCodeAreaIdIndex (Int32 lng)
{
	this->type = CODEAREAIDINDEXTYPE;
	this->subtype = NONESUBTYPE;
	this->value.lng.lng = lng;
	this->flags = Flags::Initialized;
}

inline Int32 GdlValueRecord::GetGroup (void) const
{
	DBASSERT (this->type == GROUPTYPE);

	return this->value.lng.lng;
}

inline void GdlValueRecord::SetGroup (Int32 lng)
{
	this->type = GROUPTYPE;
	this->subtype = NONESUBTYPE;
	this->value.lng.lng = lng;
	this->flags = Flags::Initialized;
}

inline Int32 GdlValueRecord::GetDict (void) const
{
	DBASSERT (this->type == DICTTYPE);

	return this->value.lng.lng;
}

inline void GdlValueRecord::SetDict (Int32 lng)
{
	this->type = DICTTYPE;
	this->subtype = NONESUBTYPE;
	this->value.lng.lng = lng;
	this->flags = Flags::Initialized;
}

inline bool GdlValueRecord::IsInitialized (void) const
{
	return (this->flags & Flags::Initialized) != 0;
}

inline GSErrCode	GdlValueRecord::Write (GS::OChannel& oc) const
{
	GSErrCode err = oc.GetOutputStatus ();
	if (err == NoError) {
		err = oc.Write ((Int32)type);
	}
	if (err == NoError) {
		err = oc.Write ((Int32)subtype);
	}
	if (err == NoError) {
		if (type == NUMTYPE && subtype == REALSUBTYPE)
			err = oc.Write (value.dbl);
		else
			err = oc.Write (value.lng.lng);
	}
	return err;

}

inline GSErrCode	GdlValueRecord::Read (GS::IChannel& ic)
{
	GSErrCode err = ic.GetInputStatus ();
	if (err == NoError) {
		err = ic.Read ((Int32&)type);
	}
	if (err == NoError) {
		err = ic.Read ((Int32&)subtype);
	}
	if (err == NoError) {
		if (type == NUMTYPE && subtype == REALSUBTYPE)
			err = ic.Read (value.dbl);
		else
			err = ic.Read (value.lng.lng);
	}
	return err;

}

/*----------------------------------------------------------------------------
*/

inline GdlParagraphData::GdlParagraphData (void)
{
	this->alignment = 0;
	this->filler_1 = 0;
	this->filler_2 = 0;
	this->firstLineIndent = 0;
	this->leftIndent = 0;
	this->rightIndent = 0;
	this->lineSpacing = 0.0;
	this->firstTabData = 0;
	this->lastTabData = 0;
	this->firstStringData = 0;
	this->lastStringData = 0;
}


/*----------------------------------------------------------------------------
*/

inline GdlStringData::GdlStringData (void)
{
	this->styleInd = 0;
	this->materInd = 0;
	this->penInd = 0;
	this->filler_1 = 0;
	this->firstChar = 0;
	this->lastChar = 0;
}


class GDLAddParVarName {
	const char* str = nullptr;
	USize hashValue = 0;

	static const UInt32 HashPrime = 65587;

public:

	GDLAddParVarName () = default;

	GDLAddParVarName (const char* str, GS::Array<char>& tempBuffer) : str (str), hashValue (0)
	{
		UInt32 len = Strlen32 (str);
		tempBuffer.SetSize (GS::Max (tempBuffer.GetSize (), len + 1));
		BNCopyMemory (tempBuffer.GetContent (), str, len + 1);
		CHtoLower (tempBuffer.GetContent (), len);
		hashValue = 0;
		for (UInt32 i = 0; i < len; ++i) {
			hashValue = hashValue * HashPrime + tempBuffer [i];
		}
	}

	ULong	GenerateHashValue () const
	{
		return hashValue;
	}

	bool operator == (const GDLAddParVarName& rhs) const
	{
		if (hashValue != rhs.hashValue) {
			return false;
		}
		if (this == &rhs) {
			return true;
		}
		return CHCompareASCII (str, rhs.str, GS::CaseInsensitive) == 0;
	}
};

class GDL_DLL_EXPORT GDLAddParData : public GS::SharedObject {
private:
	GS::Owner<GDL::Parameters>					addParHdl;
	GS::HashTable<GDLAddParVarName, Int32>		nameIndexMap;
	GS::Array<GDLAddParVarName>					names;
public:
	explicit GDLAddParData (const GDL::ParameterGetter& addParHdl);
	explicit GDLAddParData (const GDL::Parameters& addParHdl);
	explicit GDLAddParData (GS::Owner<GDL::Parameters> addParHdl);
	~GDLAddParData ();

	const GDL::Parameters&		GetAddParHdl () const;
	Int32						NameToIndex (const GDLAddParVarName& name) const { Int32 i = -1; nameIndexMap.Get (name, &i); return i; }
	const GDLAddParVarName&		IndexToName (Int32 index)  const { return names [index]; }
};

typedef GS::SharedPtr<GDLAddParData> GDLAddParDataPtr;
typedef GS::ConstSharedPtr<GDLAddParData> ConstGDLAddParDataPtr;


#endif
