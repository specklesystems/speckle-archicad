// *********************************************************************************************************************
// Error codes for the API module
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_ERRORCODES_H)
#define APIDEFS_ERRORCODES_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"


// --- Constant definitions	--------------------------------------------------------------------------------------------

const Int32 API_ModuleId = 262;
const Int32 APIErrorStart = GS::ErrorFlagMask | (API_ModuleId << 16);


/**
 * @brief This enum contains the possible errors that can occur while using Archicad API
 * @ingroup APIInfrastructure
 */
enum APIErrCodes {
	
	/** General error code. */
	APIERR_GENERAL					= APIErrorStart + 1,
	
	/** Insufficient memory. */
	APIERR_MEMFULL					= APIErrorStart + 2,
	
	/** The operation has been canceled by the user, in case of a long process. */
	APIERR_CANCEL					= APIErrorStart + 3,

	
	/** The passed identifier is not a valid one, or valid, but not proper for the given operation. */
	APIERR_BADID					= APIErrorStart + 101,
	
	/** The passed index is out of range. */
	APIERR_BADINDEX					= APIErrorStart + 102,
	
	/** The passed name is not proper or not found in the existing list. */
	APIERR_BADNAME					= APIErrorStart + 103,
	
	/** The passed parameters are inconsistent. */
	APIERR_BADPARS					= APIErrorStart + 104,
	
	/** The passed polygon cannot be interpreted. */
	APIERR_BADPOLY					= APIErrorStart + 105,
	
	/** The command cannot be executed on the current database. */
	APIERR_BADDATABASE				= APIErrorStart + 106,
	
	/** The command cannot be executed while the current window is active. */
	APIERR_BADWINDOW				= APIErrorStart + 107,
	
	/** The key code cannot be found in the listing database. */
	APIERR_BADKEYCODE				= APIErrorStart + 108,
	
	/** The passed platform sign is not valid. See @ref ACAPI_ModulData_Store. */
	APIERR_BADPLATFORMSIGN			= APIErrorStart + 109,
	
	/** The plane equation is incorrect. */
	APIERR_BADPLANE					= APIErrorStart + 110,
	
	/** The passed user ID (TeamWork client) is not valid. */
	APIERR_BADUSERID				= APIErrorStart + 111,
	
	/** The passed autotext value is not valid. See @ref ACAPI_AutoText_SetAnAutoText. */
	APIERR_BADVALUE					= APIErrorStart + 112,
	
	/** The function cannot be applied to the passed element type. See @ref ACAPI_Element_Trim_Elements. */
	APIERR_BADELEMENTTYPE			= APIErrorStart + 113,
	
	/** The passed polygon or polyline is irregular. See @ref API_RegularizedPoly. */
	APIERR_IRREGULARPOLY			= APIErrorStart + 114,
	
	/** The passed expression string is syntactically incorrect. */
	APIERR_BADEXPRESSION			= APIErrorStart + 115,
	
	/** The passed guid is invalid or valid, but not proper for the given operation. */
	APIERR_BADGUID					= APIErrorStart + 116,
	
	/** The passed token is invalid. See @ref ACAPI_GetToken. */
	APIERR_BADTOKEN					= APIErrorStart + 117,

	
	/** There is no 3D information assigned to the passed element. */
	APIERR_NO3D						= APIErrorStart + 201,
	
	/** No more database items can be returned. */
	APIERR_NOMORE					= APIErrorStart + 202,
	
	/** There is no open project. The operation cannot be executed without an open project. */
	APIERR_NOPLAN					= APIErrorStart + 203,
	
	/** No library was loaded. The operation cannot be executed without a loaded library. Can be returned by @ref ACAPI_LibraryPart_Create. */
	APIERR_NOLIB					= APIErrorStart + 204,
	
	/** The requested LibPart section is not found. */
	APIERR_NOLIBSECT				= APIErrorStart + 205,
	
	/** No selection. The operation cannot be executed without any element selected. */
	APIERR_NOSEL					= APIErrorStart + 206,
	
	/** The referenced element is not editable. */
	APIERR_NOTEDITABLE				= APIErrorStart + 207,
	
	/** The specified first library part unique ID does not refer to a subtype of the second unique ID. See @ref ACAPI_LibraryPart_CheckLibPartSubtypeOf. */
	APIERR_NOTSUBTYPEOF				= APIErrorStart + 208,
	
	/** The main GUID parts of the specified two library part unique IDs are not equal. See @ref ACAPI_LibraryPart_CompareLibPartUnIds. */
	APIERR_NOTEQUALMAIN				= APIErrorStart + 209,
	
	/** The main GUID parts of the specified two library part unique IDs are equal but their revision IDs differ. See @ref ACAPI_LibraryPart_CompareLibPartUnIds. */
	APIERR_NOTEQUALREVISION			= APIErrorStart + 210,
	
	/** There is no open project, or not in Teamwork mode. */
	APIERR_NOTEAMWORKPROJECT		= APIErrorStart + 211,

	
	/** Attempt to get user data assigned to an element, but there isn't any. */
	APIERR_NOUSERDATA				= APIErrorStart + 220,
	
	/** The user data cannot be assigned to the element, since there is no free storage block avaliable. */
	APIERR_MOREUSER					= APIErrorStart + 221,
	
	/** The link already exists. */
	APIERR_LINKEXIST				= APIErrorStart + 222,
	
	/** The link doesn't exist. */
	APIERR_LINKNOTEXIST				= APIErrorStart + 223,
	
	/** The window to be opened already exists. */
	APIERR_WINDEXIST				= APIErrorStart + 224,
	
	/** The referenced window does not exist. */
	APIERR_WINDNOTEXIST				= APIErrorStart + 225,
	
	/** No undoable entry has got into the opened undo operation. */
	APIERR_UNDOEMPTY				= APIErrorStart + 226,
	
	/** The reference already exists. */
	APIERR_REFERENCEEXIST			= APIErrorStart + 227,
	
	/** The resource must have a unique name but the specified one is already taken. */
	APIERR_NAMEALREADYUSED			= APIErrorStart + 228,

	
	/** The attribute already exists. */
	APIERR_ATTREXIST				= APIErrorStart + 301,
	
	/** Reference to a deleted, purged or non-existent database item. */
	APIERR_DELETED					= APIErrorStart + 302,
	
	/** The referenced layer is locked. */
	APIERR_LOCKEDLAY				= APIErrorStart + 303,
	
	/** The referenced layer is hidden. */
	APIERR_HIDDENLAY				= APIErrorStart + 304,
	
	/** The passed floor index is out of range. */
	APIERR_INVALFLOOR				= APIErrorStart + 305,
	
	/** The database item is not in the user's workspace. */
	APIERR_NOTMINE					= APIErrorStart + 306,
	
	/** Can't access / create / modify / delete an item in a teamwork server. */
	APIERR_NOACCESSRIGHT			= APIErrorStart + 307,
	
	/** The property for the passed element or attribute is not available. */
	APIERR_BADPROPERTY				= APIErrorStart + 308,
	
	/** Can't set the classification for the passed element or attribute. */
	APIERR_BADCLASSIFICATION		= APIErrorStart + 309,
	
	/** Given layer parameter index is not an existing one. */
	APIERR_NOTEXISTINGLAYER			= APIErrorStart + 310,
	
	/** No current attributeset */
	APIERR_NOCURRATTRSET			= APIErrorStart + 311,

	
	/** The referenced add-on is not installed. For more details see the [Communication Manager](#AddOnAddOnCommunication). */
	APIERR_MODULNOTINSTALLED		= APIErrorStart + 401,
	
	/** The target add-on is the caller add-on. For more details see the [Communication Manager](#AddOnAddOnCommunication). */
	APIERR_MODULCMDMINE				= APIErrorStart + 402,
	
	/** The referenced command is not supported by the target add-on. For more details see the [Communication Manager](#AddOnAddOnCommunication). */
	APIERR_MODULCMDNOTSUPPORTED		= APIErrorStart + 403,
	
	/** The requested command version is newer than the version of the command that the target add-on can support. For more details see the [Communication Manager](#AddOnAddOnCommunication). */
	APIERR_MODULCMDVERSNOTSUPPORTED	= APIErrorStart + 404,
	
	/** No custom data section is saved into the project file identified by the add-on's unique ID. See @ref ACAPI_ModulData_GetInfo. */
	APIERR_NOMODULEDATA				= APIErrorStart + 405,
	
	/** 
	 * The command (for this element type) is implemented on the C++ API in ArchicadAPI module and it is no longer available via the Old API. 
	 * The function where it occured can be called for compatibility reasons but it takes no effect. 
	 * For further information you can search the corresponding functionality in the API Documentation. 
	 */
	APIERR_DEPRECATEDCALL			= APIErrorStart + 406,

	
	/** Two or more paragraphs are overlapped. The end offset of one is greater than the beginner offset of the next one. */
	APIERR_PAROVERLAP				= APIErrorStart + 501,
	
	/** Number of paragraphs - the size of @c paragraphs handle - is zero. */
	APIERR_PARMISSING				= APIErrorStart + 502,
	
	/** Paragraph end offset is run over the content length. */
	APIERR_PAROVERFLOW				= APIErrorStart + 503,
	
	/** The content string contains line end character (CR) at invalid position (inside the paragraph range). */
	APIERR_PARIMPLICIT				= APIErrorStart + 504,

	
	/** Two or more runs are overlapped. The end offset of one is greater than the beginner offset of the next one. */
	APIERR_RUNOVERLAP				= APIErrorStart + 510,
	
	/** Number of runs - the size of @c run pointer - is zero. */
	APIERR_RUNMISSING				= APIErrorStart + 511,
	
	/** Run end offset is run over the content length. */
	APIERR_RUNOVERFLOW				= APIErrorStart + 512,
	
	/** The beginner offset of one is greater than the end offset of the previous one. */
	APIERR_RUNIMPLICIT				= APIErrorStart + 513,
	
	/** Attempted to overwrite a protected text run (not used yet). */
	APIERR_RUNPROTECTED				= APIErrorStart + 514,

	
	/** The EOL array is not a monotonous ascendant sequence. */
	APIERR_EOLOVERLAP				= APIErrorStart + 520,

	
	/** The tabulator array is not a monotonous ascendant sequence. */
	APIERR_TABOVERLAP				= APIErrorStart + 530,

	
	/** The command needs initialization by an other API call. */
	APIERR_NOTINIT					= APIErrorStart + 901,
	
	/** The API function is not reentrant. Nesting occurred. */
	APIERR_NESTING					= APIErrorStart + 902,
	
	/** The command is not supported by the server application. It is not environment dependent. The server application cannot execute the command generally. */
	APIERR_NOTSUPPORTED				= APIErrorStart + 903,
	
	/** The passed identifier is not subject to the operation. */
	APIERR_REFUSEDCMD				= APIErrorStart + 904,
	
	/** The command cannot be executed with the passed parameters. */
	APIERR_REFUSEDPAR				= APIErrorStart + 905,
	
	/** The specified location is read-only. Can be returned by @ref ACAPI_LibraryPart_Create. */
	APIERR_READONLY					= APIErrorStart + 906,
	
	/** The invoked Teamwork service has failed. */
	APIERR_SERVICEFAILED			= APIErrorStart + 907,
	
	/** The invoked undoable command threw an exception. Can be returned by @ref ACAPI_CallUndoableCommand. */
	APIERR_COMMANDFAILED			= APIErrorStart + 908,
	
	/** The called command should be encapsulated in a @ref ACAPI_CallUndoableCommand scope. */
	APIERR_NEEDSUNDOSCOPE			= APIErrorStart + 909,
	
	/** The called command shouldn't be encapsulated in a @ref ACAPI_CallUndoableCommand scope. */
	APIERR_UNDOSCOPEMISUSE			= APIErrorStart + 910,

	
	/** The function is not implemented yet. */
	APIERR_MISSINGCODE				= APIErrorStart + 1001,
	
	/** The originating library part file is missing. The document name is still filled. */
	APIERR_MISSINGDEF				= APIErrorStart + 1002
};


// ---------------------------------------------------------------------------------------------------------------------

#endif
