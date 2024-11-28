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

/**
 * @brief Library Part types. From Archicad 8 these categories are obsolete due to the introduction of library part subtypes.
 * @enum API_LibTypeID
 * @ingroup LibraryPart
 * @remarks The values correspond to a given type of Library Part.
 * 			Generally this value is referenced from the @ref API_LibPart structure.
 */
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

/**
 * @brief Definition of a Library Part.
 * @struct API_LibPart
 * @ingroup LibraryPart
 * @remarks This structure is definition of the library part.
 * 			Note, that it is strongly advised to define the file and document name to the same one, because of the Windows/Mac compatibility. The document name terminology was introduced when the Windows platform restricted the filenames to be in 8.3 form.
 * 			Do not forget to delete the dynamically allocated location pointer after library part operations.
 * @warning *Legacy data structure - to be deleted in future versions, use ACAPI::Library::LibPart and ACAPI::Library::GSMObject instead*
 */
struct API_LibPart {

/**
 * @brief Type of the Library Part
 * @var typeID
 */
	API_LibTypeID					typeID;

/**
 * @brief Index of the Library Part, contains the current database index of the given Library Part.
 * 		  Note that this number is not constant for a particular Library Part through the whole life of the project.
 * @var index
 */
	Int32							index;

/**
 * @brief Unique document name of the Library Part.
 * 		  If more than one Library Part has the same name, only the newest one is registered. Refer to the
 * @ref ACAPI_LibraryManagement_OverwriteLibPart function to modify this behavior.
 * @var docu_UName
 */
	GS::uchar_t						docu_UName [API_UniLongNameLen];

/**
 * @brief File name of the Library Part
 * @var file_UName
 */
	GS::uchar_t						file_UName [API_UniLongNameLen];

/**
 * @brief The definition is missing
 * @var missingDef
 */
	bool							missingDef;


/**
 * @brief Tells whether this library part is a template.
 * @var isTemplate
 */
	bool							isTemplate;

/**
 * @brief Tells whether this library part can be placed.
 * @var isPlaceable
 */
	bool							isPlaceable;

/**
 * @brief Signature of the owner; used by external objects;
 * @var ownerID
 */
	GSType							ownerID;

/**
 * @brief Library Part version
 * @var version
 */
	short							version;


/**
 * @brief Location of the library part (GSM) file in the file system
 * @var location
 */
	IO::Location*					location;


/**
 * @brief The unique ID string of the library part.
 * @var ownUnID
 */
	char							ownUnID [128];

/**
 * @brief the unique ID string of the ancestor library part.
 * @var parentUnID
 */
	char							parentUnID [128];

};


// =============================================================================
// LibraryPart detail data
//
// =============================================================================

#define API_Orient_Default			1							// orientation
#define API_Orient_Reverse			2
#define API_Orient_Custom			3

/**
 * @brief Library part's details of object, light, label and zone. Used in @ref API_LibPartDetails.
 * @struct API_LibPartObjectDetails
 * @ingroup LibraryPart
 */
struct API_LibPartObjectDetails {

/**
 * @brief Store fix values rather than the ratio of current/default A/B sizes
 * @var fixSize
 */
	bool						fixSize;

/**
 * @brief Place hotspots on the bounding box
 * @var autoHotspot
 */
	bool						autoHotspot;

/**
 * @brief Open the dialog with the User Interface tab page as the default.
 * @var uiTabDefault
 */
	bool						uiTabDefault;

/**
 * @brief Adjust parameters A and B to the bounding box of the 2D symbol
 * @var sizeTo2D
 */
	bool						sizeTo2D;

/**
 * @brief Use the new hierarchycal UI page system in object settings dialog
 * @var uiUseHierarchicalPages
 */
	bool						uiUseHierarchicalPages;

/**
 * @brief Run the parameter script of the library only once.
 * @var runVLScriptOnlyOnce
 */
	bool						runVLScriptOnlyOnce;

/**
 * @brief Enable or disable fixed name library part parameters.
 * @var enableHideFixNamedParams
 */
	bool						enableHideFixNamedParams;

/**
 * @brief Drawing order follows order of commands in 2D Script.
 * @var enable2DScriptDrawingOrder
 */
	bool						enable2DScriptDrawingOrder;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32						filler_2[6];

};

/**
 * @brief Library part's details of window and door. Used in @ref API_LibPartDetails.
 * @struct API_LibPartDoorWindowDetails
 * @ingroup LibraryPart
 */
struct API_LibPartDoorWindowDetails {
	/**
	 * @brief Window/door draw mirror thickness expression.
	 * @var mirThickExpr
	 */
	char mirThickExpr[512];

	/**
	 * @brief Window/door parapet wall inset expression.
	 * @var wallInsetExpr
	 */
	char wallInsetExpr[512];

	/**
	 * @brief Window/door left frame expression.
	 * @var leftFramExpr
	 */
	char leftFramExpr[512];

	/**
	 * @brief Window/door right frame expression.
	 * @var righFramExpr
	 */
	char righFramExpr[512];

	/**
	 * @brief Window/door top frame expression.
	 * @var topFramExpr
	 */
	char topFramExpr[512];

	/**
	 * @brief Window/door bottom frame expression.
	 * @var botFramExpr
	 */
	char botFramExpr[512];


	/**
	 * @brief Window/door draw mirror thickness if not expression.
	 * @var mirThick
	 */
	float mirThick;

	/**
	 * @brief Window/door parapet wall inset if not expression.
	 * @var wallInset
	 */
	float wallInset;

	/**
	 * @brief Window/door left frame if not expression.
	 * @var leftFram
	 */
	float leftFram;

	/**
	 * @brief Window/door right frame if not expression.
	 * @var righFram
	 */
	float righFram;

	/**
	 * @brief Window/door top frame if not expression.
	 * @var topFram
	 */
	float topFram;

	/**
	 * @brief Window/door bottom frame if not expression.
	 * @var botFram
	 */
	float botFram;


	/**
	 * @brief Defines the way the opening's orientation is displayed:
	 * 		  |Value|Meaning|
	 * 		  |--- |--- |
	 * 		  |API_Orient_Default|Display Door/Window opening orientation as a standard default setting|
	 * 		  |API_Orient_Reverse|Display Door/Window opening orientation in reverse as a standard default setting|
	 * 		  |API_Orient_Custom|Use customized display of Door/Window opening orientation|
	 *
	 * @var orientation
	 */
	char orientation;

	/**
	 * @brief Reserved for later use.
	 * @var filler_3
	 */
	char filler_3;

	/**
	 * @brief 3D image is framed (wind/door).
	 * @var contours_3D
	 */
	bool contours_3D;

	/**
	 * @brief Open the dialog with the User Interface tab page as the default.
	 * @var uiTabDefault
	 */
	bool uiTabDefault;

	/**
	 * @brief Use the new hierarchical UI page system in object settings dialog.
	 * @var uiUseHierarchicalPages
	 */
	bool uiUseHierarchicalPages;

	/**
	 * @brief Run the parameter script of the library only once (until any change happens).
	 * @var runVLScriptOnlyOnce
	 */
	bool runVLScriptOnlyOnce;

	/**
	 * @brief Drawing order follows order of commands in 2D Script.
	 * @var enable2DScriptDrawingOrder
	 */
	bool enable2DScriptDrawingOrder;

	/**
	 * @brief Reserved for later use.
	 * @var filler_1
	 */
	char filler_1[1];

	/**
	 * @brief Default position label.
	 * @var defaultLabel
	 */
	char defaultLabel[32];

	/**
	 * @brief Mirrored position label.
	 * @var mirroredLabel
	 */
	char mirroredLabel[32];

	/**
	 * @brief Reserved for later use.
	 * @var filler_2
	 */
	Int32 filler_2[8];
};

/**
 * @brief Detail parameters of a Library Part.
 * @union API_LibPartDetails
 * @ingroup LibraryPart
 * @remarks This structure contains the detail parameters of the library part. These parameters can be edited in Archicad by clicking the Details button on the parameter list editor dialog box.
 * 			Note, that the parameters depend on the type of the Library Part. These parameters are coded in the parameter section (API_SectParamDef) of the Library Part.
 * 			Refer to the @ref ACAPI_LibraryPart_GetDetails and @ref ACAPI_LibraryPart_SetDetails_ParamDef functions to get or modify such parameters of a Library Part.
 * 			In Archicad 10 the contours_2D field has been removed from the structure.
 */
union API_LibPartDetails {
/**
 * @brief Library part's details of an object.
 * @var object
 */
	API_LibPartObjectDetails object;

/**
 * @brief Library part's details of a light.
 * @var light
 */
	API_LibPartObjectDetails light;

/**
 * @brief Library part's details of a label.
 * @var label
 */
	API_LibPartObjectDetails label;

/**
 * @brief Library part's details of a zone.
 * @var zone
 */
	API_LibPartObjectDetails zone;

/**
 * @brief Library part's details of a window.
 * @var wind
 */
	API_LibPartDoorWindowDetails wind;

/**
 * @brief Library part's details of a door.
 * @var door
 */
	API_LibPartDoorWindowDetails door;
};


// =============================================================================
// LibraryPart data sections
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

/**
 * @brief Definition of a Library Part section.
 * @struct API_LibPartSection
 * @ingroup LibraryPart
 * @remarks A Library Part is composed of several sections. Each section has an owner, a signature versioning information and data bytes. This data structure is designed to hold the available section headers.
 * 			The built in section types (that can be interpreted by Archicad) are:
 * 			|Section type|Meaning|
 * 			|--- |--- |
 * 			| `API_SectParamDef` | Parameter section type |
 * 			| `API_Sect1DScript` | 1D script section type |
 * 			| `API_Sect2DDraw` | 2D binary (draw) section type |
 * 			| `API_Sect2DScript` | 2D script section type |
 * 			| `API_Sect3DScript` | 3D script section type |
 * 			| `API_SectPRScript` | Properties script section type |
 * 			| `API_SectUIScript` | User Interface script section type |
 * 			| `API_SectVLScript` | Value List script section type |
 * 			| `API_Sect3DBinData` | 3D binary section type |
 * 			| `API_SectPropData` | Properties section type |
 * 			| `API_SectComText` | Comment text section type |
 * 			| `API_SectInfoPict` | Info picture section type (PICT format) |
 * 			| `API_SectInfoGIF` | Info picture section type (GIF format) |
 * 			|||
 * 			| `API_SectGDLPict` | Pictures referenced from the GDL (GIF format) |
 * 			| `API_SectSubKind` | Symbol SubKind data section type |
 * 			| `API_SectCompDef` | Component section type |
 * 			| `API_SectDescDef` | Descriptor section type |
 * 			|||
 * 			| `API_SectCalledMacros` | Called macros section type |
 * 			| `API_SectAncestors` | Ancestor for subtyping |
 * 			|||
 * 			| `API_SectFWMScript` | Forward migration script section type |
 * 			| `API_SectBWMScript` | Backward migration script section type |
 * 			| `API_SectMigrTable` | Migration table section type |
 * 			| `API_SectLibPartURL` | BIMcomponents.com URL |
 * 			| `API_SectCopyright` | Copyright information for BIMcomponents.com elements |
 * 			| `API_SectKeywords` | Lists keywords for searching |
 * 			If the sectType field (a four-character case-sensitive identifier) does not match any types listed above, it is interpreted as a custom type. In this case the owner application is responsible for the content and the management of the section data.
 * 			This structure is used by many Library Part Manager functions as a parameter.
 * 			More detailed information on the standard Library Part sections can be found in the Archicad Reference Manual.
 * @warning *Legacy data structure - to be deleted in future versions, use ACAPI::Library::GSMObject instead*
 */
struct API_LibPartSection {

/**
 * @brief Section type
 * @var sectType
 */
	GSType			sectType;

/**
 * @brief Section secondary identifier. Became unsigned short in v13.
 * @var subIdent
 */
	unsigned short	subIdent;

/**
 * @brief Version of section data (not used for custom sections)
 * @var version
 */
	short			version;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32			filler_2;

};


// =============================================================================
// LibraryPart parameters
//
// =============================================================================

/**
 * @brief Possible types of a Library Part additive parameter.
 * @enum API_AddParID
 * @ingroup Dialog
 * @remarks This identifier is mainly referenced from the @ref API_AddParType structure.
 */
enum API_AddParID:Int32 {
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

};

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


/**
 * @brief Describes a parameter of a Library Part.
 * @struct API_AddParType
 * @ingroup Dialog
 * @remarks This structure describes the additional parameters for a Library Part. It is also used for Library
 * 			Part-based element (objects, windows, doors, etc.) and attribute types (zone category). For parameters with
 * 			array modifier, you can change the dimensions of the array on the fly when you create or modify an element.
 * 			This enables you to put just a placeholder for an array into the library part parameter, and adjust that
 * 			when you actually place the library part. It is strongly advised to use the @ref
 * 			ACAPI_LibraryPart_OpenParameters, @ref ACAPI_LibraryPart_ChangeAParameter, @ref
 * 			ACAPI_LibraryPart_GetActParameters, @ref ACAPI_LibraryPart_CloseParameters functions to modify a parameter
 * 			in the parameter list. Dictionary parameters are currently inaccessible with this structure.
 * @par Example
 * 		@snippet API_Examples.cpp API_AddParType-Example-Snippet
 */
struct API_AddParType {

/**
 * @brief The type of the additional parameter (`ParT_Integer`, `ParT_Length`, etc.)
 * @var typeID
 */
	API_AddParID					typeID;

/**
 * @brief The index of the additional parameter inside the additional parameter list.
 * @var index
 */
	short							index;

/**
 * @brief Type modifier; the variable is a simple instance or an array with the type typeID.
 * @var typeMod
 */
	short							typeMod;

/**
 * @brief The name of the parameter — should be ASCII only.
 * @var name
 */
	char							name [API_NameLen];

/**
 * @brief The description of the parameter as a Unicode string.
 * @var uDescname
 */
	GS::uchar_t						uDescname [API_UAddParDescLen];


/**
 * @brief The description of the value for simple numerical parameter types as a Unicode string.
 * @var valueDescription
 */
	GS::uchar_t valueDescription[API_UAddParNumDescLen];

/**
 * @brief The first dimension of the array; in case of array modifier
 * @var dim1
 */
	Int32							dim1;

/**
 * @brief The second dimension of the array; in case of array modifier
 * @var dim2
 */
	Int32							dim2;

/**
 * @brief Modifier flags.
 * 		  |Value|Description|
 * 		  |--- |--- |
 * 		  |API_ParFlg_Child|This parameter is a child of the preceding title.|
 * 		  |API_ParFlg_BoldName|Show the name of the parameter in bold.|
 * 		  |API_ParFlg_Open|Show the child parameters of this parameter.|
 * 		  |API_ParFlg_Disabled|Disable this parameter; mainly used for separator lines|
 * 		  |API_ParFlg_Hidden|Hidden parameter; does not appear in the Settings dialogs.|
 * 		  |API_ParFlg_SHidden|Hidden parameter from scripts.|
 *
 * @var flags
 */
	unsigned short					flags;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2;

/**
 * @brief Unicode description string values of an array parameter in UTF-16 encoding. Values are stored immediately
 * 		  after each other to conserve space.
 * @var arrayDescriptions
 */
	GSHandle						arrayDescriptions;

/**
 * @brief Contains numeric, string or array parameter values.
 * @var value
 */
	union {
		/**
		 * @brief Numeric parameter value.
		 * @var real
		 */
		double						real;

		/**
		 * @brief String parameter (`ParT_CString`) value (Unicode, UTF-16 encoded).
		 * @var uStr
		 */
		GS::uchar_t					uStr[API_UAddParStrLen];

		/**
		 * @brief Array parameter values.
		 * @var array
		 */
		GSHandle					array;

	} value;
};


// ---------------------------------------------------------------------------------------------------------------------

#endif
