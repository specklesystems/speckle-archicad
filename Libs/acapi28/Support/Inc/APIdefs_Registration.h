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

/**
 * @brief The ID of the server application the add-on is called from.
 * @enum API_ApplicationTypeID
 * @ingroup AddOnLifetime
 * @remarks Use these data if you have to depend on the server application.
 * 			Call the @ref ACAPI_AddOnIdentification_Application or the @c ACAPI_GetReleaseNumber functions to get this data.
 */
typedef enum {
	APIAppl_ArchiCADID				= 1

} API_ApplicationTypeID;

/**
 * @brief This is a numeric value representing an SSA subscription level. Use the named constants from the @ref API_SSALevels namespace: NoSSA, SSA, Forward.
 * @typedef API_SSALevel
 * @ingroup LicenseInfo
 * @since Archicad 26
 * @remarks The @ref ACAPI_Licensing_IsSSALevelAtLeast function can be used to query the availability of a certain SSA subscription.
 */
using API_SSALevel = UInt32;

/**
 * @brief Constants of @ref API_SSALevel.
 * @ingroup LicenseInfo
 * @since Archicad 26
 */
namespace API_SSALevels {
	/**
	 * @brief Constant of No SSA subscription.
	 * @since Archicad 26
	 */
	const API_SSALevel NoSSA = 0;

	/**
	 * @brief Constant of SSA subscription.
	 * @since Archicad 26
	 */
	const API_SSALevel SSA = 1;

	/**
	 * @brief Constant of Forward subscription.
	 * @since Archicad 26
	 */
	const API_SSALevel Forward = 2;
}

/**
 * @brief Textual description of the add-on.
 * @struct API_AddOnInfo
 * @ingroup AddOnLifetime
 * @since Archicad 26
 * @remark This is a member of the @ref API_EnvirParams structure used in the @ref CheckEnvironment function.
 * 		   The description appears in the Add-On Manager dialog of Archicad. Both strings should come from a localizable resource.
 * 		   When set, the `requiredSSALevel` field instructs Archicad to handle this add-on as dependent on Software Service Agreements.
 * 		   Note, however, that any restrictions in functionality (e.g., disabling commands) should be implemented separately in the add-on.
 * 		   From API 21 the name and description fields are in Unicode; you shouldn't call `BNZeroMemory` or `memset`.
 */
struct API_AddOnInfo {
	API_AddOnInfo () :
		name (), description (), requiredSSALevel (API_SSALevels::NoSSA)
	{}


/**
 * @brief The name of the add-on, in Unicode.
 * @var name
 */
	GS::UniString					name;

/**
 * @brief The description of the functionality of the add-on, in Unicode.
 * @var description
 */
	GS::UniString					description;

/**
 * @brief If the add-on requires an SSA subscription in order to function, set this member to the required minimum subscription level (see
 * @var requiredSSALevel
 */
	API_SSALevel					requiredSSALevel;

};

/**
 * @brief Describes the current server application the add-on is running under.
 * @struct API_ServerApplicationInfo
 * @ingroup AddOnLifetime
 * @since Archicad 26
 * @remarks This is a read-only member of the @ref API_EnvirParams structure, passed as a parameter to the `CheckEnvironment` function. It can be also obtained with the @ref ACAPI_AddOnIdentification_Application function.
 * 			From API 21 you shouldn't call `BNZeroMemory` or `memset` on this structure.
 */
struct API_ServerApplicationInfo {
	API_ServerApplicationInfo () :
		serverApplication (APIAppl_ArchiCADID), mainVersion (0), releaseVersion (0),
		runningInBackground (false), buildNum (0), language (), partnerID ()
	{}


/**
 * @brief The server application (Archicad and/or OEM products).
 * @var serverApplication
 */
	API_ApplicationTypeID			serverApplication;

/**
 * @brief The main version of the server application.
 * @var mainVersion
 */
	UInt16							mainVersion;

/**
 * @brief The sub- (release) version of the server application.
 * @var releaseVersion
 */
	Int16							releaseVersion;

/**
 * @brief The server application was started in background mode.
 * @var runningInBackground
 */
	bool							runningInBackground;

/**
 * @brief The build number of the server application
 * @var buildNum
 */
	Int32							buildNum;

/**
 * @brief The language of the server application as a Unicode string.
 * 		  For example, it contains "@c INT" for the international version and "@c JPN" for the Japanese version.
 * @var language
 */
	GS::UniString					language;

/**
 * @brief When Archicad runs on an SSA license this field contains the internal identifier of the reseller.
 * @var partnerID
 */
	GS::UniString					partnerID;

};


/**
 * @brief Describes the different parameters of the running environment.
 * @struct API_EnvirParams
 * @ingroup AddOnLifetime
 * @remarks This is the parameter of the CheckEnvironment function. The serverInfo member is read-only, while the addOnInfo part should be filled by the add-on by return.
 * 			From API 21 you shouldn't call BNZeroMemory or memset on this structure.
 */
struct API_EnvirParams {

/**
 * @brief Read-only information about the server application the add-on is running under.
 * @var serverInfo
 */
	API_ServerApplicationInfo		serverInfo;

/**
 * @brief Textual description of the add-on; the add-on should fill this in.
 * @var addOnInfo
 */
	API_AddOnInfo					addOnInfo;

};


// =============================================================================
// Addon unique identifier
//
// =============================================================================

/**
 * @brief Unique identifier of an add-on.
 * @struct API_ModulID
 * @ingroup AddOnAddOnCommunication
 * @remarks This structure refers to the 'MDID' resource.
 * 			The data structure is used directly by the Communication Manager, to identify the target add-on.
 * 			The add-on's module ID is also used by the ModulData Manager to identify the owners of the custom data sections saved into the project files.
 */
struct API_ModulID {

/**
 * @brief The unique ID of the add-on developer. Generated by Graphisoft upon registration.
 * @var developerID
 */
	GSType							developerID;

/**
 * @brief The add-on's specific identifier. The developer is responsible to select different local IDs.
 * @var localID
 */
	GSType							localID;

};


// =============================================================================
// Addon type
//
// =============================================================================

/**
 * @brief Describes the different types of add-ons.
 * @enum API_AddonType
 * @ingroup AddOnLifetime
 * @remarks This is the return value of the CheckEnvironment function and specifies the behavior of the current add-on in the running environment.
 */
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
/**
 * @brief Defines the menu where the add-on's menu command will appear.
 * @enum APIMenuCodeID
 * @ingroup MenuItem
 * @since Archicad 26
 * @remarks This structure is used in the @ref ACAPI_MenuItem_RegisterMenu function.
 */
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
// Toolbox interface (location for subtype-based tools)
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

/**
 * @brief Represents the data of an attribute manager format.
 * @struct API_AttributeManagerFormat
 * @ingroup AddOnIntegration
 * @since Archicad 26
 */
struct API_AttributeManagerFormat {

/**
 * @brief Macintosh file type (e.g. 'TEXT').
 * @var fileType
 */
	GSType						fileType;

/**
 * @brief Creator on Macintosh (e.g. 'GSAC' for Archicad).
 * @var fileCreator
 */
	GSType						fileCreator;

/**
 * @brief Description of the file type.
 * @var popupText
 */
	GS::UniString				popupText;

/**
 * @brief The extension used on Windows (e.g. "txt").
 * @var fileExtension
 */
	GS::UniString				fileExtension;

};

// ============================================================================
// Format Registration to Publisher
//
// ============================================================================

/**
 * @brief Represents the data of a publisher format.
 * @struct API_PublishFormatData
 * @ingroup AddOnIntegration
 */
struct API_PublishFormatData {

/**
 * @brief MimeType of the new publish format. The MimeType has to be unique.
 * @var mimeType
 */
	GS::UniString				mimeType;

/**
 * @brief Popup text will be the name of the new publish format, on the publisher dialog.
 * @var popUpText
 */
	GS::UniString				popUpText;

/**
 * @brief File extension in case of 2D save.
 * @var fileExtText2D
 */
	GS::UniString				fileExtText2D;

/**
 * @brief File extension in case of 3D save.
 * @var fileExtText3D
 */
	GS::UniString				fileExtText3D;

/**
 * @brief Describes the new format in which windows is available.
 * @var windowTypes
 */
	GS::Array<API_WindowTypeID>	windowTypes;

/**
 * @brief In case of true, the new registered format gives the possibility to merge all content in one file (like PDF format).
 * @var singleFile
 */
	bool						singleFile;

/**
 * @brief Describes, the new format in which windows are available in single file mode. If singleFile bool is false, this array has to be empty.
 * @var windowTypesInSingleFile
 */
	GS::Array<API_WindowTypeID>	windowTypesInSingleFile;

/**
 * @brief The resource ID of the new publisher format’s icon.
 * @var iconID
 */
	short						iconID;

};


/**
 * @brief Represents a translator by its GUID and its name.
 * @ingroup AddOnIntegration
 * @struct API_TranslatorNameConfig
 */
struct API_TranslatorNameConfig {

/**
 * @brief Unique ID of the translator.
 * @var guid
 */
	API_Guid		guid;

/**
 * @brief Name of the translator.
 * @var translatorName
 */
	GS::UniString   translatorName;

};


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

/**
 * @brief Callback function to save the document in the newly registered publish format.
 * @ingroup Publisher
 * @param method [in] Any of
 * 				 ```
 * 				 Save2DProc,
 * 				 SaveSectionProc,
 * 				 Save3DProc, SaveRenderingProc,
 * 				 SaveTextProc, SaveReportProc,
 * 				 SaveDrawProc, SaveLayoutProc,
 * 				 SaveMovie3DProc, SaveMovieRenderingProc,
 * 				 SaveDetailDrawingProc, SaveIESProc, SaveDocumentFrom3DProc
 * 				 ```
 * @param path [in] The path where to save the published file.
 * @param userData [in] The userData contains the save options given by the Add-On.
 * @param reportStr [in] The error message if the publishing failed.
 * @return
 * 			- NoError - The function has been completed with success.
 */
typedef GSErrCode SaveProc (API_SaveMethod method,
							const char	  *path,
							API_UserData  *userData,
							GS::UniString *reportStr);


/**
 * @brief Callback function to set different options for the newly registered format.
 * @ingroup Publisher
 * @param method [in] Any of
 * 				 ```
 * 				 Save2DProc,
 * 				 SaveSectionProc,
 * 				 Save3DProc, SaveRenderingProc,
 * 				 SaveTextProc, SaveReportProc,
 * 				 SaveDrawProc, SaveLayoutProc,
 * 				 SaveMovie3DProc, SaveMovieRenderingProc,
 * 				 SaveDetailDrawingProc, SaveIESProc, SaveDocumentFrom3DProc
 * 				 ```
 * @param userData [in] The userData contains the save options given by the Add-On.
 * @return
 * 			- NoError - The function has been completed with success.
 */
typedef GSErrCode SaveOptionProc (API_SaveMethod method, API_UserData *userData);


/**
 * @brief Callback function to receive the translators for the new registered publish forma
 * @ingroup Publisher
 * @param arr [out] The array which will be filled with translator configurations.
 * @return
 * 			- NoError - The function has been completed with success.
 */
typedef GSErrCode TranslatorGetterProc (GS::Array<API_TranslatorNameConfig> &arr);


/**
 * Callback function to receive the default translator for the new registered publish format.
 * @ingroup Publisher
 * @param def [out] The output parameter of this function. This configuration will be set to hold the default
 * 			  translator of the format.
 * @return
 * 			- NoError - The function has been completed with success.
 */
typedef GSErrCode	DefaultTranslatorGetterProc (API_TranslatorNameConfig& def);


/**
 * Callback function to receive a string providing additional information about a publisher format or it's current configuration.
 * @ingroup Publisher
 * @param info [out] The info string that can be displayed by the Publisher.
 * @param general [in] Indicates that the info string should have contents for a Publisher Folder item has the same format items, but with different info
 * @return
 * 			- NoError - The function has completed with success.
 */
typedef GSErrCode	InfoGetterProc (const API_UserData* const	userData,
									GS::UniString&				info,
									bool						general);


/// @cond DISABLED
struct PublishFormatMethods {
	SaveProc*						saveProc;
	SaveOptionProc*					saveOptionProc;
	TranslatorGetterProc*			translatorGetterProc;
	DefaultTranslatorGetterProc*	defaultTranslatorGetterProc;
	InfoGetterProc*					infoGetterProc;
};
/// @endcond


// ============================================================================
// AddOn Command Registration
//
// ============================================================================

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif


/**
 * @brief Execution policy of the Add-On commands.
 * @enum API_AddOnCommandExecutionPolicy
 * @since Archicad 25
 * @remarks The @c InstantExecutionOnParallelThread is faster than the @c ScheduleForExecutionOnMainThread mode,
 * 			but cannot modify the Archicad database. Helpful in querying data.
 * 			The `ScheduleForExecutionOnMainThread` has full access to the Archicad database via the ACAPI functions.
 */
enum class API_AddOnCommandExecutionPolicy {
	InstantExecutionOnParallelThread,
	ScheduleForExecutionOnMainThread
};


/**
 * @brief Base class for the Add-On commands.
 * @ingroup AddOnAddOnCommunication
 * @class API_AddOnCommand
 * @since Archicad 26
 * @remarks Inherit from this abstract class and implement the required functions to specify an Add-On command.
 * 			Validating the "{}" string and matching all the input/output schemas.
 * 			You can install an Add-On command handler with the @c ACAPI_AddOnAddOnCommunication_InstallAddOnCommandHandler function.
 */
class API_AddOnCommand {
public:
	virtual ~API_AddOnCommand () = default;


/**
 * @brief Returns the unique name of the command. This name cannot be an empty string or contain '.' characters.
 * @return The name of the command.
 */
	virtual GS::String							GetName () const = 0;

/**
 * @brief Returns the namespace of the command. This name cannot be an empty string or contain '.' characters.
 * @return The namespace of the command.
 */
	virtual GS::String							GetNamespace () const = 0;

/**
 * @brief Returns the schema definitions. Must be a valid JSON string. Types defined in the schema definitions can be used in the input/output schemas.
 * @return The add-on command's schema definition.
 */
	virtual GS::Optional<GS::UniString>			GetSchemaDefinitions () const = 0;

/**
 * @brief This schema will be used to validate the incoming request parameters. Must be a valid JSON string.
 * @return The validation schema.
 */
	virtual GS::Optional<GS::UniString>			GetInputParametersSchema () const = 0;

/**
 * @brief This schema will be used to validate the incoming request response. Must be a valid JSON string.
 * @return The response schema for the command.
 */
	virtual GS::Optional<GS::UniString>			GetResponseSchema () const = 0;

/**
 * @brief Returns the execution policy.
 * @return The execution policy.
 */
	virtual API_AddOnCommandExecutionPolicy		GetExecutionPolicy () const = 0;

/**
 * @brief Controls the visibility of the process window during the command's execution.
 * @return Tells if the process window is currently visible.
 */
	virtual bool								IsProcessWindowVisible () const = 0;

/**
 * @brief Write the Add-On command logic inside this function.
 * @param parameters The parameters.
 * @param processControl The process window.
 * @return Tells if the process window is currently visible.
 */
	virtual GS::ObjectState						Execute (const GS::ObjectState &parameters,
														 GS::ProcessControl	   &processControl) const = 0;

/**
 * @brief This function is called when an error occurred inside the Add-On command logic and the output schema validation failed.
 * @param response The response.
 */
	virtual void								OnResponseValidationFailed (const GS::ObjectState& response) const = 0;

};

#ifdef __clang__
#pragma clang diagnostic pop
#endif


// ============================================================================
// API_Token
//
// ============================================================================


/**
 * @brief API_Token is a unique identifier associated with every AddOn.
 * @since Archicad 25
 */
using API_Token = API_Guid;

// ---------------------------------------------------------------------------------------------------------------------

#endif
