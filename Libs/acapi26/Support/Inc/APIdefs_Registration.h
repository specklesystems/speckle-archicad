// *********************************************************************************************************************
// API definitions - registration of the addon functionality
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_REGISTRATION_H)
#define	APIDEFS_REGISTRATION_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "UniString.hpp"
#include "APICalls.h"
#include "APIdefs_Elements.h"


namespace GS {
	class ProcessControl;
	class ObjectState;
}


// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Server application
//
// =============================================================================

typedef enum {
	APIAppl_ArchiCADID				= 1
} API_ApplicationTypeID;

using API_SSALevel = UInt32;

namespace API_SSALevels {
	const API_SSALevel NoSSA = 0;
	const API_SSALevel SSA = 1;
	const API_SSALevel Forward = 2;
}

struct API_AddOnInfo {
	API_AddOnInfo () :
		name (), description (), requiredSSALevel (API_SSALevels::NoSSA)
	{}

	GS::UniString					name;
	GS::UniString					description;
	API_SSALevel					requiredSSALevel;
};

struct API_ServerApplicationInfo {
	API_ServerApplicationInfo () :
		serverApplication (APIAppl_ArchiCADID), mainVersion (0), releaseVersion (0),
		runningInBackground (false), buildNum (0), language (), partnerID ()
	{}

	API_ApplicationTypeID			serverApplication;
	UInt16							mainVersion;
	Int16							releaseVersion;
	bool							runningInBackground;
	Int32							buildNum;
	GS::UniString					language;
	GS::UniString					partnerID;
};


struct API_EnvirParams {
	API_ServerApplicationInfo		serverInfo;					// read only
	API_AddOnInfo					addOnInfo;					// return parameter
};


// =============================================================================
// Addon unique identifier
//
// =============================================================================

struct API_ModulID {											// refers to the MDID resource
	GSType							developerID;				// developer registration ID
	GSType							localID;					// local add-on identifier
};


// =============================================================================
// Addon type
//
// =============================================================================

typedef enum {
	APIAddon_DontRegister			= 0,

	APIAddon_Normal					= 1,
	APIAddon_Preload				= 2,

	APIAddon_Unknown				= 9999
} API_AddonType;


// ============================================================================
// Menu interface
//
// ============================================================================

// Menu Position Codes
typedef enum {
	MenuCode_UserDef				= 0,	// configurable by the user

	MenuCode_File					= 1,	// Add-On Commands in the File menu
	MenuCode_Edit1					= 2,	// Add-On Commands in the Edit menu
	MenuCode_Edit2					= 3,	// Add-On Commands in the Edit/Reshape submenu
	MenuCode_Edit3					= 4,	// Add-On Commands in the Edit/Move submenu
	MenuCode_Tools					= 5,	// Add-On Commands in the Options menu
	MenuCode_Options1				= 6,	// Add-On Commands in the Options menu, after "Show All Layers"
	MenuCode_Options2				= 7,	// Add-On Commands in the Options/Attributes submenu
	MenuCode_Image					= 8,	// Add-On Commands in the Document/Creative Imaging submenu
	MenuCode_Calculate				= 9,	// Add-On Commands in the Document/Schedules and Lists submenu
	MenuCode_TeamWork				= 10,	// Add-On Commands in the Teamwork menu
	MenuCode_Display				= 11,	// Add-On Commands in the View/Zoom submenu
	MenuCode_Palettes				= 12,	// Add-On Commands in the Window/Palettes submenu
	MenuCode_Extras					= 13,	// Add-On Commands in the Design/Design Extras submenu
	MenuCode_Hotlink				= 14,	// Add-On Commands in the File/External Content submenu
	MenuCode_GDLObjects				= 15,	// Add-On Commands in the File/Libraries and Objects submenu
	MenuCode_3DView					= 16,	// Add-On Commands in the Document/Set 3D View submenu
	MenuCode_DocExtras				= 17,	// Add-On Commands in the Document/Document Extras submenu
	MenuCode_Interoperability		= 18,	// Add-On Commands in the File/Interoperability submenu
	MenuCode_ModelCheck				= 19	// Add-On Commands in the Design/Model Check submenu
} APIMenuCodeID;

// Menu insert flags
#define	MenuFlag_Default			0x0000
#define	MenuFlag_SeparatorBefore	0x0001						// ensure separator before
#define	MenuFlag_SeparatorAfter		0x0002						// ensure separator after
#define	MenuFlag_InsertIntoSame		0x0004						// menu items from different add-ons are inserted into the same submenu


// ============================================================================
// I/O interface
//
// ============================================================================

// File I/O operations supported
#define	Open2DSupported					0x0001
#define	Merge2DSupported				0x0002
#define	OpenLibPartSupported			0x0004
#define	SaveAs2DSupported				0x0008
#define	SaveAs3DSupported				0x0010
#define	SaveAsFlySupported				0x0020
#define	Import2DDrawingSupported		0x0040
#define	SaveAs2DOwnWindowSupported		0x0080
#define	UpdateSupported					0x0100
#define OpenAnalyticalModelSupported	0x0200


#define	IOSupportedMask				0x00ff

typedef short API_IOMethod;


// ============================================================================
// Toolbox interface (location for subtype based tools)
//
// ============================================================================

// Toolbox groups
#define	TBoxGroup_Root				0
#define	TBoxGroup_Objects			1
#define	TBoxGroup_Openings			2

typedef short API_TBoxGroup;

// Toolbox enabled flags
#define	API_TBoxEnabled_FloorPlan					0x00000001
#define	API_TBoxEnabled_ModelSection				0x00000002	// only model sections/elevations
#define	API_TBoxEnabled_3D							0x00000004
#define	API_TBoxEnabled_DrawingSection				0x00000008	// only drawing sections/elevations
#define	API_TBoxEnabled_Detail						0x00000010
#define	API_TBoxEnabled_Layout						0x00000020
#define	API_TBoxEnabled_Worksheet					0x00000040
#define	API_TBoxEnabled_ModelInteriorElevation		0x00000100	// only model interior elevations
#define	API_TBoxEnabled_3DDocument					0x00000200
#define	API_TBoxEnabled_DrawingInteriorElevation	0x00000400	// only drawing interior elevations

typedef Int32 API_TBoxEnabled;


// ============================================================================
// Settings dialog panel
//
// ============================================================================

typedef enum {
	APIPanel_None					= 0,
	APIPanel_Settings				= 1,
	APIPanel_Attribute				= 2,
	APIPanel_InfoBox				= 3
} API_PanelType;

// ============================================================================
// Format Registration to Attribute Manager
//
// ============================================================================

typedef struct {
	GSType						fileType;
	GSType						fileCreator;
	GS::UniString				popupText;
	GS::UniString				fileExtension;
} API_AttributeManagerFormat;

// ============================================================================
// Format Registration to Publisher
//
// ============================================================================

typedef struct {
	GS::UniString				mimeType;
	GS::UniString				popUpText;
	GS::UniString				fileExtText2D;
	GS::UniString				fileExtText3D;
	GS::Array<API_WindowTypeID>	windowTypes;
	bool						singleFile;
	GS::Array<API_WindowTypeID>	windowTypesInSingleFile;
	short						iconID;
} API_PublishFormatData;


typedef struct {
	API_Guid		guid;
	GS::UniString   translatorName;
} API_TranslatorNameConfig;


typedef enum {
	Save2DProc				=  0,
	SaveSectionProc			=  1,
	Save3DProc				=  2,
	SaveRenderingProc		=  3,
	SaveTextProc			=  4,
	SaveReportProc			=  5,
	SaveDrawProc			=  6,
	SaveLayoutProc			=  7,
	SaveMovie3DProc			=  8,
	SaveMovieRenderingProc	=  9,
	SaveDetailDrawingProc	= 10,
	SaveIESProc				= 11,
	SaveDocumentFrom3DProc	= 12
} API_SaveMethod;

typedef GSErrCode		__ACENV_CALL	SaveProc (API_SaveMethod method, const char* path, API_UserData* userData, GS::UniString* reportStr);
typedef GSErrCode		__ACENV_CALL	SaveOptionProc (API_SaveMethod method, API_UserData* userdata);
typedef GSErrCode		__ACENV_CALL	TranslatorGetterProc (GS::Array<API_TranslatorNameConfig>& arr);
typedef GSErrCode		__ACENV_CALL	DefaultTranslatorGetterProc (API_TranslatorNameConfig& def);

typedef struct {
	SaveProc*					 saveProc;
	SaveOptionProc*				 saveOptionProc;
	TranslatorGetterProc*		 translatorGetterProc;
	DefaultTranslatorGetterProc* defaultTranslatorGetterProc;
} PublishFormatMethods;


// ============================================================================
// AddOn Command Registration
//
// ============================================================================

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif


enum class API_AddOnCommandExecutionPolicy {
	InstantExecutionOnParallelThread,
	ScheduleForExecutionOnMainThread
};


class API_AddOnCommand {
public:
	virtual ~API_AddOnCommand () = default;

	virtual GS::String							GetName () const = 0;
	virtual GS::String							GetNamespace () const = 0;
	virtual GS::Optional<GS::UniString>			GetSchemaDefinitions () const = 0;
	virtual GS::Optional<GS::UniString>			GetInputParametersSchema () const = 0;
	virtual GS::Optional<GS::UniString>			GetResponseSchema () const = 0;

	virtual API_AddOnCommandExecutionPolicy		GetExecutionPolicy () const = 0;
	virtual bool								IsProcessWindowVisible () const = 0;

	virtual GS::ObjectState						Execute (const GS::ObjectState& parameters, GS::ProcessControl& processControl) const = 0;

	virtual void								OnResponseValidationFailed (const GS::ObjectState& response) const = 0;
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif


// ============================================================================
// API_Token
//
// ============================================================================

using API_Token = API_Guid;

// ---------------------------------------------------------------------------------------------------------------------

#endif
