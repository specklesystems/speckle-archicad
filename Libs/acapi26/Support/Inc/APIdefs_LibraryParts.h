// *********************************************************************************************************************
// API definitions - managing Library Parts
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_LIBRARYPARTS_H)
#define	APIDEFS_LIBRARYPARTS_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

#include "uchar_t.hpp"
// own
#include "APIdefs_Base.h"

namespace IO { class Location; }


// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// LibraryPart
//
// =============================================================================

#define	APILibOwner_ArchiCAD		'GSAC'

typedef enum {
	API_ZombieLibID					= 0,

	APILib_SpecID					= 1,						// virtual symbols, etc...

	APILib_WindowID					= 2,
	APILib_DoorID					= 3,
	APILib_ObjectID					= 4,
	APILib_LampID					= 5,
	APILib_RoomID					= 6,

	APILib_PropertyID				= 7,

	APILib_PlanSignID				= 8,
	APILib_LabelID					= 9,

	APILib_MacroID					= 10,
	APILib_PictID					= 11,
	APILib_ListSchemeID				= 12,
	APILib_SkylightID				= 13,
	APILib_OpeningSymbolID			= 14

} API_LibTypeID;

typedef struct {
	API_LibTypeID					typeID;
	Int32							index;								// index of the Library Part
	GS::uchar_t						docu_UName [API_UniLongNameLen];	// UTF16 name of the Library Part
	GS::uchar_t						file_UName [API_UniLongNameLen];	// UTF16 name of the file
	bool							missingDef;							// missing definition
	bool							filler_1;
	bool							isTemplate;							// can be an ancestor of other library parts
	bool							isPlaceable;						// can be placed into the project or used as macro
	GSType							ownerID;							// ESYM identifier or APIOwnerID_ArchiCAD
	short							version;							// Library Part version
	unsigned short					platformSign;						// Library Part platform
	Int32							filler_2[7];
	IO::Location*					location;							// file system location
	Int32							filler_3;
	char							ownUnID [128];						// unique ID string of the library part
	char							parentUnID [128];					// unique ID string of the ancestor library part
} API_LibPart;


// =============================================================================
// LibraryPart detail data
//
// =============================================================================

#define API_Orient_Default			1							// orientation
#define API_Orient_Reverse			2
#define API_Orient_Custom			3

typedef union {
	struct {
		bool						fixSize;
		bool						autoHotspot;
		bool						uiTabDefault;				// object settings dialog to open with user interface tabpage
		bool						sizeTo2D;					// adjust parameters A and B to the extent box of the 2D symbol
		bool						uiUseHierarchicalPages;		// use the new hierarchycal UI page system in object settings dialog
		bool						runVLScriptOnlyOnce;		// run the parameter script only one time and not until there are no changes
		bool						enableHideFixNamedParams;
		bool						enable2DScriptDrawingOrder;
		Int32						filler_2[6];
	} object, light, label, zone;
	struct {
		char						mirThickExpr[512];			// window/door draw mirror thickness expression
		char						wallInsetExpr[512];			// window/door parapet wall inset expression
		char						leftFramExpr[512];			// window/door left frame expression
		char						righFramExpr[512];			// window/door right frame expression
		char						topFramExpr[512];			// window/door top frame expression
		char						botFramExpr[512];			// window/door bottom frame expression

		float						mirThick;					// window/door draw mirror thickness if not expression
		float						wallInset;					// window/door parapet wall inset if not expression
		float						leftFram;					// window/door left frame if not expression
		float						righFram;					// window/door right frame if not expression
		float						topFram;					// window/door top frame if not expression
		float						botFram;					// window/door bottom frame if not expression

		char						orientation;
		char						filler_3;
		bool						contours_3D;				// 3D image is framed (wind/door)
		bool						uiTabDefault;				// door/window settings dialog to open with user interface tabpage
		bool						uiUseHierarchicalPages;		// use the new hierarchycal UI page system in object settings dialog
		bool						runVLScriptOnlyOnce;		// run the parameter script only one time and not until there are no changes
		bool						enable2DScriptDrawingOrder;
		char						filler_1[1];
		char						defaultLabel[32];
		char						mirroredLabel[32];
		Int32						filler_2[8];
	} wind, door;
} API_LibPartDetails;


// =============================================================================
// LibraryPart data sections
//
// sync these	\ARCHICAD\...\APIdefs_LibraryParts.h
//				\GDL\...\SymbSect.h
//				\GSMSections\...\GFG.h
//				\GSShellX\...\CLibPartHandler.cpp
//				\LibPartFile\...\LPFDefinitions.hpp
// =============================================================================

#define API_SectHeadTable			'HEAD'						// Section header table type
#define API_SectParamDef			'PARD'						// Parameter section type
#define API_SectCompDef				'COMD'						// Component section type
#define API_SectDescDef				'DESD'						// Descriptor section type
#define API_Sect1DScript			'1DSC'						// 1D script section type
#define API_Sect2DDraw				'2DDR'						// 2D draw section type
#define API_Sect2DScript			'2DSC'						// 2D script section type
#define API_Sect3DScript			'3DSC'						// 3D script section type
#define API_SectPRScript			'PRSC'						// Properties script section type
#define API_SectUIScript			'UISC'						// User Interface script section type
#define API_SectVLScript			'VLSC'						// Value List script section type
#define API_Sect3DBinData			'3DBN'						// 3D binary section type
#define API_SectPropData			'PROP'						// Property section type
#define API_SectComText				'CTXT'						// Comment text section type
#define API_SectInfoPict			'PICT'						// Info picture section type (PICT format)
#define API_SectInfoGIF				'GIFF'						// Info picture section type (GIF format)
#define API_SectGDLPict				'GDLP'						// Pictures referenced from the GDL (GIF format)
#define API_SectSubKind				'TYPE'						// Symbol SubKind data section type
#define API_SectCalledMacros		'MCRS'						// Called macros section type
#define	API_SectAncestors			'ANCS' 						// Ancestor for subtyping
#define	API_SectFWMScript			'FMSC'						// Forward migration script
#define	API_SectBWMScript			'BMSC'						// Backward migration script
#define	API_SectMigrTable			'MGRT'						// Migration table type
#define API_SectLibPartURL			'LURL'						// ObjectPortal URL
#define API_SectCopyright			'CPYR'						// Copyright information for ObjectPortal elements
#define API_SectKeywords			'KWRD'						// Keywords for searching

#define	APISubIdent_Any				0xFFFF

typedef struct {
	GSType			sectType;									// section type
	unsigned short	subIdent;									// section secondary identifier
	short			version;									// version of section data (not used for custom sections)
	Int32			filler_2;
} API_LibPartSection;


// =============================================================================
// LibraryPart parameters
//
// =============================================================================

typedef enum {
	API_ZombieParT	= 0,

	APIParT_Integer,											// Integer Additional Parameter Type
	APIParT_Length,												// Length Additional Parameter Type
	APIParT_Angle,												// Angle Additional Parameter Type
	APIParT_RealNum,											// Real Number Additional Parameter Type
	APIParT_LightSw,											// Light On/Off Additional Parameter Type
	APIParT_ColRGB,												// RGB Color Additional Parameter Type
	APIParT_Intens,												// Intensity Additional Parameter Type
	APIParT_LineTyp,											// Line Type Additional Parameter Type
	APIParT_Mater,												// Material Additional Parameter Type
	APIParT_FillPat,											// Fill pattern Additional Parameter Type
	APIParT_PenCol,												// Pen color Additional Parameter Type
	APIParT_CString,											// C String Additional Parameter Type
	APIParT_Boolean,											// Bool Additional Parameter Type
	APIParT_Separator,											// Separator Line, no value
	APIParT_Title,												// Title text, no value
	APIParT_BuildingMaterial,									// Building Material Additional Parameter Type
	APIParT_Profile,											// Profile Additional Parameter Type
	APIParT_Dictionary											// Dictionary Parameter Type
} API_AddParID;

#define APIParT_MAX_TYPE_INDEX		18

#define API_ParSimple 				0							// 	simple parameter
#define API_ParArray 				2							// 	array parameter

#define	API_ParFlg_Child			0x0001						// child param
#define	API_ParFlg_BoldName			0x0002						// bold name
#define	API_ParFlg_Fixed			0x0004 						// fixed param, could not delete, but can modify its value
#define	API_ParFlg_Unique			0x0008						// unique parameter
#define	API_ParFlg_SHidden			0x0010						// hidden from script
#define	API_ParFlg_Open				0x0020						// show child params
#define	API_ParFlg_Disabled			0x0040						// disabled parameter
#define	API_ParFlg_Hidden			0x0080						// hidden parameter


typedef struct {
	API_AddParID					typeID;						// data type (ParT_Integer, ParT_Length...	 etc.)
	short							index;
	short							typeMod;					// type modifier: simple, value list or array
	char							name [API_NameLen];			// - it is only ASCII characters
	GS::uchar_t						uDescname [API_UAddParDescLen];
	GS::uchar_t						valueDescription [API_UAddParNumDescLen];		// value description for simple numerical values
	Int32							dim1;						// 1st dimension of array (in case of array modifier)
	Int32							dim2;						// 2nd dimension of array (in case of array modifier)
	unsigned short					flags;						// modifier flags
	short							filler_1;
	Int32							filler_2;
	GSHandle						arrayDescriptions;			// list of value descriptions for numerical arrays
	union {
		double						real;						// numeric parameters
		GS::uchar_t					uStr[API_UAddParStrLen];	// ParT_CString parameter
		GSHandle					array;						// list in case of array modifier
	} value;
} API_AddParType;


// ---------------------------------------------------------------------------------------------------------------------

#endif
