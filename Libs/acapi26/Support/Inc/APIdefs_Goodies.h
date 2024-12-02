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

	APIAny_ActivateSessionReportID			= 'ASRP'
} API_GoodiesID;


// =============================================================================
// Search for elements
//
// =============================================================================

typedef struct {
	API_ElemType					type;						// element type to search
	API_ElemFilterFlags				filterBits;					// APIFilt_xxxx values
	API_Coord						loc;						// the location
	double							z;							// level to search down from
} API_ElemSearchPars;


// =============================================================================
// Picture conversion
//
// =============================================================================

typedef struct {
	API_PictureFormat				storageFormat;
	GSHandle						pictHdl;
} API_PictureHandle;

typedef struct {
	const char						*mimeIn;					// input MIME type, e.g. "image/png" (@c nullptr-terminated C string)
	GSHandle						inputHdl;					// contains the input image handle
	const char						*mimeOut;					// output MIME type, e.g. "image/jpeg" (@c nullptr-terminated C string)
	GSHandle						outputHdl;					// on return contains the output image
	bool							inContainsMime;				// for library part preview pictures, where the handle starts with a MIME type
	bool							filler_0 [3];
	API_ColorDepthID				outDepth;					// the requested output pixel depth; may be @c APIColorDepth_FromSourceImage, in this case the source pixel depth will be used
	Int32							filler_1 [4];
} API_MimePicture;


// =============================================================================
// LibPart parameter utilities
//
// =============================================================================

typedef struct {
	API_Guid						guid;						// element guid
	Int32							libInd;						// library part index
	API_ElemType					type;						// element type
	Int32							filler_1;
} API_ParamOwnerType;

#define	APIVLVal_LowerLimit			1
#define	APIVLVal_LowerEqual			2
#define	APIVLVal_UpperLimit			4
#define	APIVLVal_UpperEqual			8
#define	APIVLVal_Step				16

typedef struct {
	double							value;						// used when no limits defined
	double							lowerLimit;					// used when APIVLVal_LowerLimit is set
	double							upperLimit;					// used when APIVLVal_UpperLimit is set
	double							stepBeg;					// used when APIVLVal_Step is set
	double							stepVal;					// used when APIVLVal_Step is set
	UInt32							flags;
	Int32							filler_1;
	GS::uchar_t						valueDescription [API_UAddParNumDescLen];	// value description for numerical values
} API_VLNumType;

typedef struct {
	char							name [API_NameLen];
	short							index;
	bool							locked;						// the parameter is locked
	bool							custom;						// the parameter may have custom values
	Int32							nVals;						// number of values
	GS::uchar_t						**uStrValues;				// string values
	API_VLNumType					**realValues;				// numeric values
	Int32							filler_1[4];
} API_GetParamValuesType;

typedef struct {
	char							name [API_NameLen];
	short							index;
	short							filler_1;
	Int32							ind1;						// 1st dimension of array (in case of array modifier)
	Int32							ind2;						// 2nd dimension of array (in case of array modifier)
	GS::uchar_t						*uStrValue;					// ParT_CString parameter
	double							realValue;					// numeric parameters
	GS::uchar_t						valueDescription [API_UAddParNumDescLen];	// value description for numerical values
} API_ChangeParamType;

typedef struct {
	double							a;							// value of 'A'
	double							b;							// value of 'B'
	API_AddParType					**params;					// additional parameters
	Int32							filler_1;
} API_GetParamsType;


// =============================================================================
// Spline approximation
//
// =============================================================================

typedef struct {
	API_Coord						**splCoords;				// fit point coordinates of the spline
	API_SplineDir					**splDirs;					// direction vectors in the fit points
	Int32							nFit;						// number of fit points
	Int32							segment;					// segment of the spline to be tested [1 ... nFit-1]

	API_Coord						**polyCoords;				// coordinates to test
	Int32							nCoords;					// number of coordinates
} API_TestSplineFit;


// =============================================================================
// MDCL Parameter list
//
// =============================================================================

#define MDCLPar_string				1
#define MDCLPar_int					2
#define MDCLPar_float				3
#define MDCLPar_pointer				4

typedef struct {
	Int32							index;						// parameter index (just for APIAny_GetMDCLParameterID)
	const char						*name;						// parameter name
	Int32							type;						// parameter type
	bool							modified;					// the parameter is modified
	bool							filler_1[3];
	union {
		Int32						int_par;					// the integer or pointer parameter
		void*						ptr_par;
	};
	double							float_par;					// the float parameter
	const char						*string_par;				// the string parameter
} API_MDCLParameter;


// =============================================================================
// TextLine parameters
//
// =============================================================================

typedef struct {
	short							index;						// -1: last line, 0: longest line, 1...: nth line
	bool							drvScaleCorr;				// true: scaled to model, false: in mms
	bool							wantsLongestIndex;			// if index is 0 :: true: return longest line's index, false: don't return longest line's index
	short							wFont;						// font attribute index
	short							wFace;						// face bits (bold, italic, underline)
	double							wSlant;
	double							wSize;						// font height in mms
	char							*lineStr;					// text to measure
	GS::UniString					*lineUniStr;				// Unicode text to measure
} API_TextLinePars;


// =============================================================================
// TextureCoord parameters
//
// =============================================================================

typedef struct {
	UInt32							elemIdx;
	UInt32							bodyIdx;
	UInt32							pgonIndex;
	UInt32							filler_1;
	API_Coord3D						surfacePoint;
} API_TexCoordPars;


// =============================================================================
// Change the content of a Word or Label element
//
// =============================================================================

typedef struct  {
	API_Elem_Head					head;
	Int32							*from;						// (GSPtr) byte offset(s)
	Int32							*range;						// (GSPtr) range(s)
	char							*content;					// (GSPtr) new content(s)
	Int32							*separator;					// (GSPtr) end position(s) in the content string
	double							filler[2];
} API_ContentPars;


// =============================================================================
// Different types of autotexts
//
// The first parameter of the Get function will return a list of array of
//	three UniStrings: (localized name, database key, value)
// =============================================================================

typedef enum {
	APIAutoText_Fixed  = 0x00000001,
	APIAutoText_Custom = 0x00000002,
	APIAutoText_Other  = 0x00000004,

	APIAutoText_All    = APIAutoText_Fixed + APIAutoText_Custom + APIAutoText_Other
} API_AutotextType;


// =============================================================================
// Use this poly to regularize as polygon or as polyline
// =============================================================================
typedef struct {
	API_Coord						**coords;
	Int32							**pends;
	API_PolyArc						**parcs;
	UInt32							**vertexIDs;
	UInt32							**edgeIDs;
	UInt32							**contourIDs;
	bool							needVertexAncestry;
	Int32							**vertexAncestry;
	bool							needEdgeAncestry;
	Int32							**edgeAncestry;
	bool							needContourAncestry;
	Int32							**contourAncestry;
} API_RegularizedPoly;


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


typedef enum {
	API_MergeConflictingSystems,
	API_ReplaceConflictingSystems,
	API_SkipConflictingSystems
} API_ClassificationSystemNameConflictResolutionPolicy;


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
typedef struct {
	API_Guid			collidedElemGuid;
	bool				hasBodyCollision;
	bool				hasClearenceCollision;
	bool				filler[6];
} API_CollisionElem;


typedef struct {
	double				volumeTolerance;
	bool				performSurfaceCheck;
	bool				filler[7];
	double				surfaceTolerance;
} API_CollisionDetectionSettings;


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
