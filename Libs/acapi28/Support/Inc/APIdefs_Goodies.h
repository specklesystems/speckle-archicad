// *********************************************************************************************************************
// API definitions - miscellaneous
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_GOODIES_H)
#define	APIDEFS_GOODIES_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Attributes.h"
#include "APIdefs_Automate.h"
#include "APIdefs_Base.h"
#include "APIdefs_ElementDifferenceGenerator.h"
#include "APIdefs_Elements.h"

namespace IO { class Location; }

// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Function codes and parameter descriptions
//
// =============================================================================

typedef enum {			// Codes for Goodies functions
	APIAny_UsableGDLStringID				= 'UGDL',			// par1: const char*					par2: ---

	APIAny_CalcSunOnPlaceID					= 'CSUN',			// par1: API_PlaceInfo*					par2: ---

	APIAny_SearchElementByCoordID			= 'SELM',			// par1: const API_ElemSearchPars*		par2: [API_Guid*] (found element)

	APIAny_ConvertPictureID					= 'CPIC',			// par1: API_PictureHandle*				par2: [API_PictureHandle*]
	APIAny_ConvertMimePictureID				= 'CMPI',			// par1: API_MimePicture*				par2: ---

	APIAny_OpenParametersID					= 'OPAR',			// par1: API_ParamOwnerType*			par2: ---
	APIAny_GetParamValuesID					= 'GPVL',			// par1: API_GetParamValuesType*		par2: ---
	APIAny_ChangeAParameterID				= 'CHGP',			// par1: API_ChangeParamType*			par2: ---
	APIAny_GetActParametersID				= 'GPAR',			// par1: API_GetParamsType*				par2: ---
	APIAny_CloseParametersID				= 'CPAR',			// par1: ---							par2: ---

	APIAny_InsertPolyNodeID					= 'INOD',			// par1: API_ElementMemo*				par2: Int32* (nodeIndex)			par3: API_Coord*
	APIAny_DeletePolyNodeID					= 'DNOD',			// par1: API_ElementMemo*				par2: Int32* (nodeIndex)
	APIAny_InsertSubPolyID					= 'IPOL',			// par1: API_ElementMemo*				par2: API_ElementMemo*
	APIAny_DeleteSubPolyID					= 'DPOL',			// par1: API_ElementMemo*				par2: Int32* (subPolyIndex)
	APIAny_RegularizePolygonID				= 'REPO',			// par1: API_RegularizedPoly*			par2: Int32* (nResult)				par3: API_RegularizedPoly*** (resultPolys)
	APIAny_RegularizePolylineID				= 'REPL',			// par1: API_RegularizedPoly*			par2: API_RegularizedPoly* (result)
	APIAny_DisposeRegularizedPolyID			= 'DRPL',			// par1: API_RegularizedPoly*

	APIAny_TriangulatePolyID				= 'TRIP',			// par1: API_ElementMemo*				par2: API_Coord*** (result)

	APIAny_NeigToCoordID					= 'NTOC',			// par1: API_Neig*						par2: API_Coord3D*					par3: API_Coord3D*

	APIAny_GetSplineMaxDistID				= 'GSMD',			// par1: API_TestSplineFit*				par2: double*

	APIAny_PolygonId2SurfaceTypeID			= 'PI2S',			// par1: const API_Element* elem		par2: const Int32* polygonId		par3: API_SurfaceTypeID* surfaceType

	APIAny_InitMDCLParameterListID			= 'ICLP',			// par1: GSHandle*						par2: ---
	APIAny_GetMDCLParameterNumID			= 'NCLP',			// par1: GSHandle						par2: Int32*
	APIAny_AddMDCLParameterID				= 'ACLP',			// par1: GSHandle						par2: API_MDCLParameter*
	APIAny_GetMDCLParameterID				= 'GCLP',			// par1: GSHandle						par2: API_MDCLParameter*
	APIAny_ChangeMDCLParameterID			= 'CCLP',			// par1: GSHandle						par2: API_MDCLParameter*
	APIAny_FreeMDCLParameterListID			= 'FCLP',			// par1: GSHandle*						par2: ---

	APIAny_GetTextLineLengthID				= 'GTLL',			// par1: API_TextLinePars*				par2: double*
	APIAny_GetTextSizeFactorID				= 'TXSF',			// par1: short*							par2: double*
	APIAny_GetTextureCoordID				= 'GTEX',			// par1: API_TexCoordPars*				par2: API_UVCoord*

	APIAny_GetBuiltInLibpartUnIdID			= 'GLUI',			// par1: short (resId)					par2: char* (lpfUnId)
	APIAny_GetUnloadedLibpartNameID			= 'GULN',			// par1: const API_Guid*				par2: GS::UniString*
	APIAny_CheckLibPartSubtypeOfID			= 'CLST',			// par1: char*							par2: char* (ancestor)
	APIAny_CheckLibPartSubtypeOfbyMainID	= 'CLPS',			// par1: char*							par2: char* (ancestor)
	APIAny_CompareLibPartUnIdsID			= 'COMP',			// par1: char*							par2: char*
	APIAny_GetElemCreatorToolUnIdID			= 'CRTR',			// par1: API_Elem_Head*					par2: char*
	APIAny_GetElemLibPartUnIdID				= 'GELU',			// par1: API_Elem_Head*					par2: char* (lpfUnId)
	APIAny_GetLibPartToolVariationID		= 'GLTV',			// par1: API_LibPart* (libPart)			par2: API_ToolBoxItem* (toolbox item)

	APIAny_SetEmptyHoleUnIdID				= 'EHID',			// par1: GSType*						par2: const char* (empty hole unID)		par3: const char* (empty opening subtype unID)

	APIAny_ChangeContentID					= 'CHCO',			// par1: const API_ContentPars*			par2: ---

	APIAny_GetAutoTextFlagID				= 'GATF',			// par1: bool*							par2: ---
	APIAny_ChangeAutoTextFlagID				= 'CATF',			// par1: bool*							par2: ---
	APIAny_GetAutoTextKeysID				= 'GATK',			// par1: char***						par2: char***
	APIAny_GetPropertyAutoTextKeyTableID	= 'GATT',			// par1: API_GUID*						par2: GS::HashTable<GS::UniString, GS::UniString>
	APIAny_InterpretAutoTextID				= 'IATS',			// par1: const GS::UniString *			par2: const API_Guid*					par3: GS::UniString *
	APIAny_GetAutoTextsID					= 'GATS',			// par1: GS::Array<GS::ArrayFB<GS::UniString, 3> >*	par2: API_AutotextType (-- as value)
	APIAny_SetAnAutoTextID					= 'SAAT',			// par1: const GS::UniString* (database key)		par2: [const GS::UniString *] (value)

	APIAny_GetMainGroupGuidID				= 'GMGR',			// par1: const API_Guid*				par2: API_Guid*
	APIAny_GetContainingHotlinkGuidID		= 'GHLG',			// par1: const API_Guid*				par2: API_Guid*

	APIAny_RunGDLParScriptID				= 'RPAS',			// par1: API_Elem_Head*					par2: UInt32 (mask -- as value)
	APIAny_CreateAnAutoTextID				= 'CAAT',			// par1: const API_Guid*				par2: const char*
	APIAny_DeleteAnAutoTextID				= 'DAAT',			// par1: const char*					par2: ---

	APIAny_GetCWAbsoluteBottomID			= 'GCWB',			// par1: const API_Guid*				par2: double*
	APIAny_GetCWHeightID					= 'GCWH',			// par1: const API_Guid*				par2: double*
	APIAny_GetCWSubElemParamsID				= 'GCWP',			// par1: const API_Guid*				par2: API_AddParType***

	APIAny_GetSkylightHolePolygonID			= 'GSHP',			// par1: const API_Guid*				par2: Geometry::Polygon2D*

	APIAny_EnableRenovationOverrideID		= 'ERNO',			// par1: bool* (oldOverrideVal)			par2: const bool* (newOverrideVal)
	APIAny_EnableVisualOverrideID			= 'EVIS',			// par1: bool* (oldOverrideVal)			par2: const bool* (newOverrideVal)
	APIAny_GetRenovationStatusNameID		= 'GRNN',			// par1: API_RenovationStatusType		par2: GS::UniString*
	APIAny_GetRenovationFilterNameID		= 'GRFN',			// par1: const API_Guid*				par2: GS::UniString*

	APIAny_SetMasterLayoutOnLayoutID		= 'MLOL',			// par1: API_DatabaseUnId*				par2: ---

	APIAny_UI2ElemPriorityID				= 'U2EP',			// par1: const Int32* (uiPriority)		par2: Int32* (elemPriority)
	APIAny_Elem2UIPriorityID				= 'E2UP',			// par1: const Int32* (elemPriority)	par2: Int32* (uiPriority)

	APIAny_CalcSideOffsetToCoreOffsetID		= 'SOCO',			// par1: const API_Guid*				par2: const double* (side offset)	par3: double* (core offset)
	APIAny_CalcCoreOffsetToSideOffsetID		= 'COSO',			// par1: const API_Guid*				par2: const double* (core offset)	par3: double* (side offset)

	APIAny_ElemHasVisibleSkinID				= 'EHVS',			// par1: const API_Guid*				par2: const API_StructureDisplay*	par3: bool* (result)

	APIAny_GetOpeningTransformationID		= 'GOTI',			// par1: const API_Guid* (elemGuid) 	par2: API_Tranmat* (openingTranMat)
	APIAny_GetSelectedElementID				= 'GSEL',			// par1: const API_Neig*				par2: API_Guid* (elemGuid)
	APIAny_SetSelectedElementNeigID			= 'SSEL',			// par1: const API_Guid* (elemGuid)		par2: API_Neig*

	APIAny_SolveStairID						= 'SSTR',			// par1: API_StairType* (apiStair)		par2: API_ElementMemo* (apiMemo)	par3: API_StairSolutionID*	(solution)

	APIAny_CheckPropertyExpressionStringID	= 'CPES',			// par1: GS::UniString* (expressionString)
	APIAny_GetPropertyExprReferenceStringID	= 'GPRS',			// par1: API_PropertyDefinition* (propertyDefinition)	par2: GS::UniString* (propertyReferenceString)
	APIAny_GetHierarchicalElementOwnerID	= 'GHEO',			// par1: const API_Guid* (elemGuid)		par2: const API_HierarchicalOwnerType* (hierarchicalOwnerType)		par3: API_HierarchicalElemType* (hierarchicalElemType)		par4: API_Guid* (ownerElemGuid)

	APIAny_GetRoomImageID					= 'GRIM',			// par1: API_RoomImage* (roomImage)
	APIAny_InterpretGDLScript3DID			= 'IP3D',			// par1: const GS::UniString* (script), API_AddParType** (addPar), ModelerAPI::Model* (model)

	APIAny_GetHttpConnectionPortID			= 'GHCP',			// par1: UShort*

	APIAny_ActivateSessionReportID			= 'ASRP',
} API_GoodiesID;


// =============================================================================
// Search for elements
//
// =============================================================================

/**
 * @brief Structure to search for an element by coordinate.
 * @struct API_ElemSearchPars
 * @ingroup Element
 * @since Archicad 26
 * @remarks This structure is used to search for an element by coordinate. Only polygonal elements are
 * 			accepted and supported.
 * 			The element type must be polygonal, and passed in the `type` field. Filters can also be
 * 			passed to skip instances based on specific attributes, such as visibility, floor number, layer reference etc.
 * 			Refer to the @ref ACAPI_Element_Filter function for more details. The location to be searched on should be
 * 			passed in the `loc` field. The search algorithm will ignore all the elements being on a higher level than
 * 			specified in the `z` parameter. The first element will be returned:
 * 			- matches the element type
 * 			- passes the filter
 * 			- the coordinate is an internal point of the polygon
 * 			- has the highest level below z
 * 			From version 26 the type of the `typeID` member was changed to `API_ElemType`.
 * @sa ACAPI_Element_SearchElementByCoord
 */
struct API_ElemSearchPars {

/**
 * @brief element type to search for
 * @var type
 */
	API_ElemType					type;

/**
 * @brief the flags (`APIFilt_xxx`) used for filtering (see @ref ACAPI_Element_Filter)
 * @var filterBits
 */
	API_ElemFilterFlags				filterBits;

/**
 * @brief the location on 2D plan
 * @var loc
 */
	API_Coord						loc;

/**
 * @brief level to search down from
 * @var z
 */
	double							z;

};


// =============================================================================
// Picture conversion
//
// =============================================================================

/**
 * @brief Structure for picture conversion.
 * @struct API_PictureHandle
 * @ingroup Conversion
 * @remarks This structure is used as a parameter of the @ref ACAPI_Conversion_ConvertPicture goody function to convert an image into a different format. See also @ref ACAPI_Conversion_ConvertMimePicture if you want to specify the image format using MIME types.
 */
struct API_PictureHandle {

/**
 * @brief storage format of the picture
 * @var storageFormat
 */
	API_PictureFormat				storageFormat;

/**
 * @brief handle that contains the image in the specified format
 * @var pictHdl
 */
	GSHandle						pictHdl;

};

/**
 * @brief Structure for picture conversion using MIME identifier.
 * @struct API_MimePicture
 * @ingroup Conversion
 * @remarks This structure is used as a parameter of the @ref ACAPI_Conversion_ConvertMimePicture
 * 			goody function to convert a picture from a given format into another using MIME types.
 * 			You can also set a special format on Windows in the `mimeOut` field: "vnd/DIB" results in `outputHdl`
 * 			containing a device independent bitmap.
 * 			In some cases the image handle contains the MIME type as well. For example pictures in Library Parts are stored
 * 			in a handle that begins with the '\0'-terminated MIME type string, and then follows the image itself. If
 * 			inputHdl is in this format, set the `inContainsMime` field to `true`. In this case the `mimeIn` parameter is ignored.
 */
struct API_MimePicture {

/**
 * @brief MIME type of the image to be converted (e.g. "image/png", null-terminated C string)
 * @var mimeIn
 */
	const char						*mimeIn;

/**
 * @brief contains the input image handle
 * @var inputHdl
 */
	GSHandle						inputHdl;

/**
 * @brief the requested MIME type of the output image (e.g. "image/jpeg", null-terminated C string)
 * @var mimeOut
 */
	const char						*mimeOut;

/**
 * @brief on return contains the output image
 * @var outputHdl
 */
	GSHandle						outputHdl;

/**
 * @brief for library part preview pictures, where the input handle (`inputHdl`) starts with a MIME type
 * @var inContainsMime
 */
	bool							inContainsMime;

/**
 * @brief Reserved for later use.
 * @var filler_0
 */
	bool							filler_0 [3];

/**
 * @brief the requested output pixel depth (`APIColorDepth_FromSourceImage`) means to use the same pixel depth the input image has)
 * @var outDepth
 */
	API_ColorDepthID				outDepth;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1 [4];

};


// =============================================================================
// LibPart parameter utilities
//
// =============================================================================

/**
 * @brief Parameters to specify the target parameter list to change.
 * @struct API_ParamOwnerType
 * @ingroup LibraryPart
 * @since Archicad 26
 * @remarks This structure is used to specify the target of which the parameter list should be opened to edit. Possible targets are:
 * 			- default parameters of a Library Part itself
 * 			- default parameters of an element (default tool settings)
 * 			- parameters of a placed element (Library Part instance)
 *
 * 			The required parameters for library part default:
 * 			| @ref API_ParamOwnerType | |
 * 			|----------|---------|
 * 			| guid | ignored |
 * 			| libInd | required; set to the Library Part index |
 * 			| type | ignored |
 *
 * 			The required parameters for element default:
 * 			| @ref API_ParamOwnerType | |
 * 			|----------|---------|
 * 			| guid | required; set to `APINULLGuid` |
 * 			| libInd | required; set to zero |
 * 			| type | required |
 *
 * 			The required parameters for a placed element:
 * 			| @ref API_ParamOwnerType | |
 * 			|----------|---------|
 * 			| guid | required; set to the element's unique ID |
 * 			| libInd | required; set to zero |
 * 			| type | required |
 */
struct API_ParamOwnerType {

/**
 * @brief element unique ID
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief library part index
 * @var libInd
 */
	Int32							libInd;

/**
 * @brief element type
 * @var type
 */
	API_ElemType					type;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

};

#define	APIVLVal_LowerLimit			1
#define	APIVLVal_LowerEqual			2
#define	APIVLVal_UpperLimit			4
#define	APIVLVal_UpperEqual			8
#define	APIVLVal_Step				16

/**
 * @brief The possible values for a numeric parameter.
 * @struct API_VLNumType
 * @ingroup LibraryPart
 * @remarks This structure contains the possible numeric values for the given parameter.
 * 			For more information, see the description of the `VALUES` command in the Parameter Script section of the GDL Reference Manual.
 */
struct API_VLNumType {

/**
 * @brief the value itself when no limits are defined
 * @var value
 */
	double							value;

/**
 * @brief the value when one of the `APIVLVal_LowerLimit` or `APIVLVal_LowerEqual` flags is set
 * @var lowerLimit
 */
	double							lowerLimit;

/**
 * @brief the value when one of the `APIVLVal_UpperLimit` or `APIVLVal_UpperEqual` flags is set
 * @var upperLimit
 */
	double							upperLimit;

/**
 * @brief the start value when the `APIVLVal_Step` flag is set
 * @var stepBeg
 */
	double							stepBeg;

/**
 * @brief the step value when the `APIVLVal_Step` flag is set
 * @var stepVal
 */
	double							stepVal;

/**
 * @brief the possible value range modifiers; only one of these can be set
 * 		  | modifier | meaning |
 * 		  |----------|---------|
 * 		  | @c APIVLVal_LowerLimit | the value of the parameter is greater than `lowerLimit` |
 * 		  | @c APIVLVal_LowerEqual | the value of the parameter is greater than or equal to `lowerLimit` |
 * 		  | @c APIVLVal_UpperLimit | the value of the parameter is less than `upperLimit` |
 * 		  | @c APIVLVal_UpperEqual | the value of the parameter is less than or equal to `upperLimit` |
 * 		  | @c APIVLVal_Step | the value of the parameter can be equal to any value in the form of `stepBeg+n*stepVal`, where `n ≥ 0` |
 * @var flags
 */
	UInt32							flags;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief Value descriptions for numerical values
 * @var valueDescription
 */
	GS::uchar_t						valueDescription[API_UAddParNumDescLen];

};

/**
 * @brief The possible parameter values of a non-array Library Part parameter.
 * @struct API_GetParamValuesType
 * @ingroup LibraryPart
 * @remarks The possible parameter values for the given parameter (defined by its name or index)
 * 			are returned in this structure by the @ref ACAPI_LibraryPart_GetParamValues function. For more information,
 * 			see the description of the `VALUES` command in the Parameter Script section of the GDL Reference Manual.
 * 			Remember to dispose of the `strValues` or the `realValues` handles when no longer needed.
 */
struct API_GetParamValuesType {

/**
 * @brief [in] the name of the parameter (optional if `index` is given)
 * @var name
 */
	char							name[API_NameLen];

/**
 * @brief [in] the index of the parameter ( `0`: `A`, `1`: `B`, `2..n`: other parameters); (optional if `name` is given)
 * @var index
 */
	short							index;

/**
 * @brief [out] the parameter is locked; i.e. the user cannot modify it
 * @var locked
 */
	bool							locked;

/**
 * @brief [out] the parameter may have custom values (its `VALUES` command contains the `CUSTOM` keyword)
 * @var custom
 */
	bool							custom;

/**
 * @brief [out] the number of values
 * @var nVals
 */
	Int32							nVals;

/**
 * @brief [out] the list of possible string values (Unicode strings in UTF-16 encoding)
 * @var uStrValues
 */
	GS::uchar_t						**uStrValues;

/**
 * @brief [out] the list of possible numeric values
 * @var realValues
 */
	API_VLNumType					**realValues;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[4];

};

/**
 * @brief Parameters to change a value in a Library Part parameter list.
 * @struct API_ChangeParamType
 * @ingroup LibraryPart
 * @remarks The target variable can be identified either by name or index.
 * 			In case of an array variable the `ind1` and `ind2` fields must be passed to address the array position.
 * 			The new values should be passed in the `strValue` or `realValue` fields, depending on the type of the
 * 			referenced variable. See the @ref ACAPI_LibraryPart_ChangeAParameter and @ref ACAPI_LibraryPart_OpenParameters functions for utilization.
 */
struct API_ChangeParamType {
/**
 * @brief name of the parameter to change as ASCII string (library part parameter names are always ASCII).
 * @var name
 */
	char							name[API_NameLen];

/**
 * @brief parameter index. Required if the `name` field is empty.
 * @var index
 */
	short							index;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	short							filler_1;

/**
 * @brief 1st dimension of array (in case of array modifier)
 * @var ind1
 */
	Int32							ind1;

/**
 * @brief 2nd dimension of array (in case of array modifier)
 * @var ind2
 */
	Int32							ind2;

/**
 * @brief Unicode string parameter value in UTF-16 encoding
 * @var uStrValue
 */
	GS::uchar_t						*uStrValue;

/**
 * @brief numeric parameter value
 * @var realValue
 */
	double							realValue;

/**
 * @brief Value descriptions for numerical values
 * @var valueDescription
 */
	GS::uchar_t						valueDescription [API_UAddParNumDescLen];

};

/**
 * @brief The changed parameter values of a Library Part.
 * @struct API_GetParamsType
 * @ingroup LibraryPart
 * @remarks This structure is used to get the actual parameters set by the @ref ACAPI_LibraryPart_ChangeAParameter
 * 			function. Remember to dispose the `params` handle when it is not needed anymore. Refer to the
 * @ref ACAPI_DisposeAddParHdl to do that.
 */
struct API_GetParamsType {

/**
 * @brief value of the 'A' parameter
 * @var a
 */
	double							a;

/**
 * @brief value of the 'B' parameter
 * @var b
 */
	double							b;

/**
 * @brief Additional parameters from the library part.
 * @var params
 */
	API_AddParType					**params;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

};


// =============================================================================
// Spline approximation
//
// =============================================================================

/**
 * @brief Contains parameters to calculate the maximal distance of a spline segment and a set of coordinates.
 * @struct API_TestSplineFit
 * @ingroup ProjectSetting
 * @remarks Call the @ref ACAPI_ProjectSetting_GetSplineMaxDist function to operate on this data. Refer to the
 * @ref API_ElementMemo structure to get information on the spline parameters.
 * 		Remember to dispose of `splCoords`, `splDirs`, and ` polyCoords` passed if they are not needed anymore.
 */
struct API_TestSplineFit {

/**
 * @brief Fit points of the spline.
 * @var splCoords
 */
	API_Coord						**splCoords;

/**
 * @brief Direction vectors at the fit points.
 * @var splDirs
 */
	API_SplineDir					**splDirs;

/**
 * @brief Number of fit points.
 * @var nFit
 */
	Int32							nFit;

/**
 * @brief Segment of the spline to be tested. It can be in the range of [1...`nFit`-1].
 * @var segment
 */
	Int32							segment;


/**
 * @brief Coordinates to be tested.
 * @var polyCoords
 */
	API_Coord						**polyCoords;

/**
 * @brief Number of test coordinates.
 * @var nCoords
 */
	Int32							nCoords;

};


// =============================================================================
// MDCL Parameter list
//
// =============================================================================

#define MDCLPar_string				1
#define MDCLPar_int					2
#define MDCLPar_float				3
#define MDCLPar_pointer				4

/**
 * @brief Parameter structure used for inter-addon communication.
 * @struct API_MDCLParameter
 * @ingroup AddOnAddOnCommunication
 * @remarks This structure is used for parameter passing in inter-addon communications. For further information refer to the Communication Manager.
 */
struct API_MDCLParameter {

/**
 * @brief Parameter index (used only with @ref ACAPI_AddOnAddOnCommunication_GetMDCLParameter)
 * @var index
 */
	Int32							index;

/**
 * @brief Pointer to the name of the parameter
 * @var name
 */
	const char						*name;

/**
 * @brief Type of the parameter. Can be one of the following constants:
 * 		  | Parameter type | Meaning |
 * 		  |----------------|---------|
 * 		  |`MDCLPar_string`|string type parameter|
 * 		  |`MDCLPar_int`|integer type parameter|
 * 		  |`MDCLPar_float`|floating point number type parameter|
 * 		  |`MDCLPar_pointer`|pointer type parameter|
 * @var type
 */
	Int32							type;

/**
 * @brief The parameter was modified with the @ref ACAPI_AddOnAddOnCommunication_ChangeMDCLParameter function
 * @var modified
 */
	bool							modified;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[3];

	union {

/**
 * @brief Integer or pointer parameter value (valid only if `type` is `MDCLPar_int`)
 * @var int_par
 */
		Int32						int_par;

/**
 * @brief Pointer parameter value (valid only if `type` is `MDCLPar_pointer`). Note that on 64-bit the size of pointers is 8 bytes.
 * @var ptr_par
 */
		void*						ptr_par;

	};

/**
 * @brief Floating point parameter value (valid only if `type` is `MDCLPar_float`).
 * @var float_par
 */
	double							float_par;

/**
 * @brief String parameter value (valid only if `type` is `MDCLPar_string`).
 * @var string_par
 */
	const char						*string_par;
};


// =============================================================================
// TextLine parameters
//
// =============================================================================

/**
 * @brief Represents some text to measure its length.
 * @struct API_TextLinePars
 * @ingroup Element
 * @remarks For further details see the @ref ACAPI_Element_GetTextLineLength goodie function.
 */
struct API_TextLinePars {

/**
 * @brief Line index
 * 		  | Value | Meaning |
 * 		  |-------|---------|
 * 		  | -1 | last line length |
 * 		  |  0 | longest line length |
 * 		  | &gt; 0 | length of the nth line |
 * @var index
 */
	short							index;

/**
 * @brief If `true`: scale the text to the model, if `false`: in mms.
 * @var drvScaleCorr
 */
	bool							drvScaleCorr;

/**
 * @brief If index is 0 -> `true`: return longest line's index, `false`: don't return longest line's index.
 * @var wantsLongestIndex
 */
	bool							wantsLongestIndex;

/**
 * @brief Font attribute index.
 * @var wFont
 */
	short							wFont;

/**
 * @brief Style (face) of text:
 * 		  | Face | Meaning |
 * 		  |------|---------|
 * 		  |@c APIFace_Plain| Plain text |
 * 		  |@c APIFace_Bold| Bold |
 * 		  |@c APIFace_Italic| Italic |
 * 		  |@c APIFace_Underline| Underline |
 * 		  |@c APIFace_Outline| Outlined (Macintosh only) |
 * 		  |@c APIFace_Shadow| Shadow (Macintosh only) |
 * @var wFace
 */
	short							wFace;

/**
 * @brief Slant angle [radian] (PI/2 is plain text).
 * @var wSlant
 */
	double							wSlant;

/**
 * @brief Character height in mms.
 * @var wSize
 */
	double							wSize;

/**
 * @brief The text to measure.
 * @var lineStr
 */
	char							*lineStr;

/**
 * @brief Unicode text to measure.
 * @var lineUniStr
 */
	GS::UniString					*lineUniStr;

};


// =============================================================================
// TextureCoord parameters
//
// =============================================================================

/**
 * @brief Identifies the surface point to get the texture coordinates for.
 * @struct API_TexCoordPars
 * @ingroup  ModelAccess
 */
struct API_TexCoordPars {

/**
 * @brief Element index.
 * @var elemIdx
 */
	UInt32							elemIdx;

/**
 * @brief The 3D body index.
 * @var bodyIdx
 */
	UInt32							bodyIdx;

/**
 * @brief The polygon index within this body.
 * @var pgonIndex
 */
	UInt32							pgonIndex;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	UInt32							filler_1;

/**
 * @brief The point in local coordinates where you would like to know the texture coordinate system.
 * @var surfacePoint
 */
	API_Coord3D						surfacePoint;

};


// =============================================================================
// Change the content of a Word or Label element
//
// =============================================================================

/**
 * @brief It is used at the @ref ACAPI_Element_Change goodie function.
 * @struct API_ContentPars
 * @ingroup Element
 * @remarks See an example of using this structure at the description of @ref ACAPI_Element_Change.
 */
struct API_ContentPars {

/**
 * @brief [in/out] Reference to the element (text or textual label) to be modified, filled with the appropriate new parameters.
 * @var head
 */
	API_Elem_Head					head;

/**
 * @brief The beginning byte position(s) in the original content to change.
 * @var from
 */
	Int32							*from;

/**
 * @brief The range(s) of the original content's pieces to change.
 * @var range
 */
	Int32							*range;

/**
 * @brief The new concatenated content.
 * @var content
 */
	char							*content;

/**
 * @brief The separator byte (end) positions in the concatenated new content.
 * @var separator
 */
	Int32							*separator;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	double							filler[2];

};


// =============================================================================
// Different types of autotexts
//
// The first parameter of the Get function will return a list of array of
//	three UniStrings: (localized name, database key, value)
// =============================================================================

/**
 * @brief Type of autotexts used in text and textual label elements.
 * @enum API_AutotextType
 * @ingroup AutoText
 * @remarks The @ref API_AutotextType values are used for filtering autotext types to be retrieved with the @ref ACAPI_AutoText_GetAutoTexts function.
 */
typedef enum {
	APIAutoText_Fixed  = 0x00000001,
	APIAutoText_Custom = 0x00000002,
	APIAutoText_Other  = 0x00000004,

	APIAutoText_All    = APIAutoText_Fixed + APIAutoText_Custom + APIAutoText_Other

} API_AutotextType;


/**
 * @brief Structure for regularizing polygon or polyline.
 * @struct API_RegularizedPoly
 * @ingroup Polygon
 * @remarks This structure is used to regularize a polygon or a polyline. @ref ACAPI_Polygon_RegularizePolygon and @ref ACAPI_Polygon_RegularizePolyline goody functions use this as input and output.
 */
struct API_RegularizedPoly {

/**
 * @brief Coordinate array.
 * @var coords
 */
	API_Coord						**coords;

/**
 * @brief Polygon endpoints; see @ref API_Polygon for more information.
 * @var pends
 */
	Int32							**pends;

/**
 * @brief Polygon arcs; see @ref API_PolyArc and @ref API_Polygon for more information.
 * @var parcs
 */
	API_PolyArc						**parcs;

/**
 * @brief Unique identifiers the polygon vertices (unique inside the polygon). Optional.
 * @var vertexIDs
 */
	UInt32							**vertexIDs;

/**
 * @brief Unique identifiers the polygon edges (unique inside the polygon). Optional.
 * @var edgeIDs
 */
	UInt32							**edgeIDs;

/**
 * @brief Unique identifiers the polygon contours (unique inside the polygon). Optional.
 * @var contourIDs
 */
	UInt32							**contourIDs;

/**
 * @brief Set to true if you would like to receive vertex ancestry after regularization. Input only parameter.
 * @var needVertexAncestry
 */
	bool							needVertexAncestry;

/**
 * @brief Array holding the indices of the vertices in the original polygon. Output only parameter. The array is filled only if it was requested with the `needVertexAncestry` parameter. The index value is 0 in case of new vertices. There is an index for all vertices. The array is indexed from 1.
 * @var vertexAncestry
 */
	Int32							**vertexAncestry;

/**
 * @brief Set to true if you would like to receive edge ancestry after regularization. Input only parameter.
 * @var needEdgeAncestry
 */
	bool							needEdgeAncestry;

/**
 * @brief Array holding the indices of the edges in the original polygon. Output only parameter. The array is filled only if it was requested with the `needEdgeAncestry` parameter. The index value is 0 in case of new edges. There is an index for all edges. The array is indexed from 1.
 * @var edgeAncestry
 */
	Int32							**edgeAncestry;

/**
 * @brief Set to true if you would like to receive contour ancestry after regularization. Input only parameter.
 * @var needContourAncestry
 */
	bool							needContourAncestry;

/**
 * @brief Array holding the indices of the contours in the original polygon. Output only parameter. The array is filled only if it was requested with the @c needContourAncestry parameter. The index value is 0 in case of new contours. There is an index for all contours. The array is indexed from 1.
 * @var contourAncestry
 */
	Int32							**contourAncestry;

};


// =============================================================================
// Folder hierarchy representation for the favorites
// =============================================================================
typedef GS::Array<GS::UniString> API_FavoriteFolderHierarchy;

typedef enum {
	API_FavoriteError,
	API_FavoriteSkip,
	API_FavoriteOverwrite,
	API_FavoriteAppend
} API_FavoriteNameConflictResolutionPolicy;


/**
 * @brief Enum used by @ref ACAPI_Classification_Import
 * @enum API_ClassificationSystemNameConflictResolutionPolicy
 * @ingroup Classification
 * @since Archicad 20
 */
typedef enum {
	API_MergeConflictingSystems,
	API_ReplaceConflictingSystems,
	API_SkipConflictingSystems

} API_ClassificationSystemNameConflictResolutionPolicy;


/**
 * @brief Enum used by @ref ACAPI_Classification_Import
 * @enum API_ClassificationItemNameConflictResolutionPolicy
 * @ingroup Classification
 * @since Archicad 20
 */
typedef enum  {
	API_ReplaceConflictingItems,
	API_SkipConflicitingItems

} API_ClassificationItemNameConflictResolutionPolicy;


typedef enum  {
	API_AppendConflictingProperties,
	API_ReplaceConflictingProperties,
	API_SkipConflictingProperties
} API_PropertyDefinitionNameConflictResolutionPolicy;


// =============================================================================
// Use the Stair Solver from the API on the Baseline.
// =============================================================================
typedef enum {
	APISS_Correct,
	APISS_Solved,
	APISS_NotSolved
} API_StairSolutionID;


// =============================================================================
// Collision Detection
// =============================================================================
/**
 * @brief A container for storing a collision element created by @ref ACAPI_Element_GetCollisions
 * @struct API_CollisionElem
 * @ingroup Element
 */
struct API_CollisionElem {

/**
 * @brief The GUID of the collided element.
 * @var collidedElemGuid
 */
	API_Guid			collidedElemGuid;

/**
 * @brief The element has body collision.
 * @var hasBodyCollision
 */
	bool				hasBodyCollision;

/**
 * @brief The element has clearance collision.
 * @var hasClearenceCollision
 */
	bool				hasClearenceCollision;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	bool				filler[6];

};


/**
 * @brief Collision detection settings used by @ref ACAPI_Element_GetCollisions
 * @struct API_CollisionDetectionSettings
 * @ingroup Element
 */
struct API_CollisionDetectionSettings {

/**
 * @brief Intersection body volume greater then this value will be considered as a collision.
 * @var volumeTolerance
 */
	double				volumeTolerance;

/**
 * @brief Enables surface collision check. If disabled the @c surfaceTolerance value will be ignored.
 * @var performSurfaceCheck
 */
	bool				performSurfaceCheck;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	bool				filler[7];

/**
 * @brief Intersection body surface area greater then this value will be considered as a collision.
 * @var surfaceTolerance
 */
	double				surfaceTolerance;

};


// =============================================================================
// Hierarchical Owner type
// =============================================================================
typedef enum {
	API_RootHierarchicalOwner,
	API_ParentHierarchicalOwner
} API_HierarchicalOwnerType;


// =============================================================================
// Hierarchical Elem type
// =============================================================================
typedef enum {
	API_MainElemInMultipleElem,
	API_ChildElemInMultipleElem,
	API_SingleElem,
	API_UnknownElemType
} API_HierarchicalElemType;


#endif
