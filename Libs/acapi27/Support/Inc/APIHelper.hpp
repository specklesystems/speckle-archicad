#ifndef	_APIHelper_HPP_
#define	_APIHelper_HPP_

#if defined (_MSC_VER)
#pragma once
#endif

#include	<map>

#include	"APIdefs.h"
#include	"APICalls.h"
#include	"UniString.hpp"
#include	"RS.hpp"

class MDID;
class NeigData;
class NeigStore;
namespace Localization {
	class PoDictionary;
}

namespace EDB {
	class IElemDatabase;
}

namespace Geometry {
	template<typename T> class Point2;
	typedef Point2<double> Coord;
	template<typename T> class Vector3;
	typedef Vector3<double> Coord3D;
}

// ==============================================================================
// General purpose calls
//
// ==============================================================================

typedef enum {		/* Codes for non-public functions */
	// for Grid Tool
	APIInternal_BadLayerDialogID						= 'BADL',		// RZN

	// for Construction Simulation
	APIInternal_GetSlideShowID							= 'SLSH',		// long* camSetIndex,			API_PerspPars*** perspPars
	APIInternal_GetCurrentImageID						= 'CIMG',		// GSPixMapHandle* pixMapHdl	bool*	is3Dw
	APIInternal_DrawLibPartToPixMapID					= 'DLPM',		// GSPixMapHandle* pixMapHdl,	const API_MoviePars* moviePars
	APIInternal_SetElementChangeFlagID					= 'SECF',		// bool* isReplaceMode

	APIInternal_IsAffectedByMarkupID					= 'MAPI',		// const API_Elem_Head* elemHead, API_ModifiersByMarkup* modifiers

	APIInternal_GetGDLGlobalDescriptionID				= 'TXSF',		// (char *) par1, (char *) par2

	APIInternal_GetLengthUnitSymbolID					= 'GLSY',		// (API_LengthTypeID) par1, (GS::UniString*) par2
	APIInternal_GetAreaUnitSymbolID						= 'GASY',		// (API_AreaTypeID) par1, (GS::UniString*) par2
	APIInternal_GetVolumeUnitSymbolID					= 'GVSY',		// (API_VolumeTypeID) par1, (GS::UniString*) par2

	APIInternal_CreateFileRefID							= 'CRFP',		// (IO::Location *) par1, (GSPtr *) par2
	APIInternal_CloneFileRefID							= 'CLFP',		// (GSPtr) par1, (GSPtr *) par2
	APIInternal_GetFileRefLocationID					= 'GFRL',		// (GSPtr *) par1, (IO::Location *) par2				/* 9.0+ */
	APIInternal_DestroyFileRefID						= 'DTFP',		// (GSPtr *) par1

	APIInternal_IsNewAndResetID							= 'INAR',		// (bool *) par1

	// for Dxf
	APIInternal_SetInXrefID								= 'SXRF',		// (bool) (long) par1, (bool*) par2	/* 8.2+*/
	APIInternal_GetHatchDensityID						= 'GHDE',		// (API_HatchDensity *) par1, (API_HatchDensityValue *) par2		/* 9.0+ */
	APIInternal_GetDrawingTransformationID				= 'GDTR',		// (API_Tranmat *) par1 (out), (API_Elem_Head *) par2 (in)			/* 10.0+ */
	APIInternal_IsPercentFillID							= 'IPCF',		// (API_IsPercentFillPars *) par1									/* 10.0+ */
	APIInternal_IsVisibleByChangeID						= 'IVBC',		// (const API_Guid* guid) par1, (const API_DatabaseUnId* apiDbUnId) par2, (bool* result) par3		/* 18.0+ */

	APIInternal_RegisterHotlinkConverterID				= 'RHLC',		// (GSType) par1
	APIInternal_InstallHotlinkConverterID				= 'IHLC',		// (GSType) par1, API_HotlinkConverterProcs* par2
	APIInternal_AllowIrregpolyForDWG					= 'IRPL',

	APIInternal_GetPrimitiveElemTypesID					= 'PRET',		//

	// for QuickLayers
	APIInternal_AttributeModifyID						= 'AMID',		// (API_Attribute *) par1, (API_AttributeDef *) par2	/* 9.0+ */

	// general
	APIInternal_GetElementID							= 'GETE',		// (API_Element *) par1, (API_ElementMemo *) par2, (double[2] *) par3 /* 9.0+ */
	APIInternal_GetDetailedTextParsID					= 'GDTP',		// (API_Elem_Head *) par1, (API_DetailedTextPars *) par2 /* 9.0+ */

	APIInternal_CheckDrawingStatusID					= 'CKDS',		// par1: const API_Guid* - guid of the drawing	par2: long* return drawing status here (-1, 0, 1)

	APIInternal_GetStandaloneVisibleMaterialsID			= 'GTVS',		// (const API_Guid *) par1, (GS::HashSet<short>*) par2

	// obsolete, use LibpartCacheHelper object instead!
	APIInternal_RefreshLibPartCacheID					= 'RLPC',		// (bool) (long) par1	/* 10.0+ */, (bool) (long) par2, (const EDB::IElemDatabase*) par3

	APIInternal_SetStoredParentTypeID					= 'SSPT',		// (bool) (const API_Guid*) par1	(API_ElemTypeID*) par2

	APIInternal_EnableNonPlaceableID					= 'ENNP',		// par1: [bool*] (oldEnable)		par2: const bool* (enable)

	// for Automatic_Dimensioning
	APIInternal_IsWindowVisibleOnFloorID				= 'IWVF',		// (const API_IsWindowVisibleOnFloorPars *) par1, (bool *) par2
	APIInternal_GetCWFrameStatusPointsID				= 'GCWS',		// (const API_Guid *) par1, (API_StatusPoints *) par2
	APIInternal_GetCWCutPanelStatusPointsID				= 'GCPP',		// (const API_Guid *) par1, (API_StatusPoints *) par2
	APIInternal_FreeStatusPointsID						= 'FSPT',		// (API_StatusPoints *) par1
	APIInternal_GetCWCutPanelStatusSectorsID			= 'GCWP',		// (const API_Guid *) par1, (API_StatusSectors *) par2
	APIInternal_FreeStatusSectorsID						= 'FSSE',		// (API_StatusSectors *) par1

	APIInternal_GetProfileSkinsID						= 'GPSK',		// (API_Elem_Head *) par1, (API_AttributeDef *) par2
	APIInternal_CreateClipboardSessionID				= 'CCBS',

	// for 7---Test/Conversion_Test
	APIInternal_GetMainAttributeSetID					= 'GTMA',		// (ADB::AttributeSetRef *) par1

	// for IFC
	APIInternal_GetIFCDataID							= 'IFGD',		// (API_IFCData*) par1
	APIInternal_SetIFCDataID							= 'IFSD',		// (API_IFCData*) par2
	APIInternal_GetIFCProjectGuidID						= 'IFPG',		// (API_Guid*) par1, (GS::UniString*) par2

	// for XREF
	APIInternal_IsReservedOrReferrableWithoutReservationXrefNodeID = 'XRRN',
	APIInternal_GetRefElemCacheManagementMutexIdID		= 'GCMI',

	APIInternal_GetVectorImageID						= 'GVIM',
	APIInternal_GetHotlinkParentNodesID					= 'HLPN',		// (const API_Guid *) par1, (GS::Array<API_Guid> *) par2
	// temporary!!!
	APIInternal_ACAlertID								= 'ACAL',		// (bool*) par1, (bool*) par2

	// Teamwork functionality
	APIInternal_CreateReservationInterfaceTWPageID		= 'CTWP',
	APIInternal_DeleteReservationInterfaceTWPageID		= 'DTWP',
	APIInternal_SendReleaseCommentMailID				= 'SRCM',

	// for EcoDesigner
	APIInternal_LocationSettingsWithoutSurveyPointID	= 'LSNS',		// (API_PlaceInfo *) par1
	APIInternal_GetTopWindowTypeID						= 'GTWT',		// (Int32*) par1
	APIInternal_SetWorkDBID								= 'SWDB',		// (bool*) par1
	APIInternal_GetEcoDesignerDataID					= 'EDGD',		// (API_EcoDesignerData*) par1
	APIInternal_SetEcoDesignerDataID					= 'EDSD',		// (API_EcoDesignerData*) par2
	APIInternal_GetEnergyEvaluationDataID				= 'ESGD',		// (API_EnergyEvaluationData*) par1, (short*) par2 /* API_EnergyEvaluationDataType */
	APIInternal_SetEnergyEvaluationDataID				= 'ESSD',		// (API_EnergyEvaluationData*) par1, (short*) par2 /* API_EnergyEvaluationDataType */, (ACP::ProjectData*) par3
	APIInternal_GetEcoDesignerStarThBridgeDataID		= 'ESGT',		// (API_EcoDesignerStarThBridgeData*) par1
	APIInternal_SetEcoDesignerStarThBridgeDataID		= 'ESST',		// (API_EcoDesignerStarThBridgeData*) par2
	APIInternal_GetEnergyEvaluationDataThPropertiesID	= 'EETP',		// (GS::HashTable<short, CutFillThermalPropertyTable>*) par1
	APIInternal_UpdateRoomsID							= 'UPDR',		// (API_RoomUpdateParams*) par1
	APIInternal_OpenProjectInfoID						= 'OPPI',		// (const GS::HashSet<GS::UniString>*) par1
	APIInternal_OperationProfileHumidityUpdateID		= 'OPHU',		// (GS::HashTable<short, double> *) opProfilesWithNewHumidityValues

	APIInternal_GeneratePatchesID						= 'GENP',		// (GS::Array<GS::Guid>*) par1
	APIInternal_GetPatchRoomIdTableID					= 'GPRT',		// (Modeler::Elem*) (par1), (GS::HashTable<Int32, GS::Guid>*) par2
	APIInternal_SetPatchColorsID						= 'SPCo',		// (GS::Array<GS_RGBColor>*) par1, (GS::HashTable<GS::Guid, EDPatchColor>*) par2
	APIInternal_Set3DEngineID							= 'ESEC',		// Returns the current 3Dengine (par1), and changes the 3D Engine to (par2) if it is given
	APIInternal_OperationProfileDlgID					= 'ESOP',		// Reaching the Operation Profile dialog from the EcoDesignerStar
	APIInternal_PostCommandIdID							= 'ESPC',		// Posting a CommandId in ARCHICAD -> used for invoking Dialogs with their CommandIds

	APIInternal_GetAutoTextGroupID						= 'GATG',		// Get the group of the given autot text db key
	APIInternal_CheckIfZonesUpToDateID					= 'CZUD',		// Checks if zones are up to date or not
	APIInternal_IsSymbolTypeOfID						= 'IsST',		// (const API_Guid*) par1, (GSFlags) par2

	// for performance
	APIInternal_RoomRelationCacheID						= 'RRCA',		// (bool) par1 [true / false 		=> Init / Destroy]

	// for dimension saving to dwg
	APIInternal_GetAutoTextFlagID						= 'GATF',		// not the same as the APIAny_GetAutoTextFlagID - the parameters are the same
	APIInternal_ChangeAutoTextFlagID					= 'CATF',		// not the same as the APIAny_ChangeAutoTextFlagID - the parameters are the same

	// layout order in layout map
	APIInternal_GetLayoutIndexID						= 'GLIX',		// (const API_DatabaseUnId*) par1, (ULong*) par2
	APIInternal_SetLayoutPageIndexID					= 'SLPI',		// (const API_DatabaseUnId*) par1, (ULong*) par2, (ULong*) par3

	// install handler for converting dxf translators back to the format used in the previous AC version
	APIInternal_RegisterTranslatorConverterID			= 'RTRC',		// (GSType) par1
	APIInternal_InstallTranslatorConverterID			= 'ITRC',		// (GSType) par1, API_TranslatorConverterProcs* par2

	// more general functions
	APIInternal_GetWallOffsetsFromOutsideID				= 'GWOO',		// (const API_Guid*) par1, (double*) par2, (double*) par3

	// force access to userdata of elements
	APIInternal_UserDataSkipNotMineID					= 'SSNM',		// Ignore (bool par1) if element is not editable when setting user data returning the previous state (bool* par2)

	// get Issue
	APIInternal_GetRVMIssueID							= 'GISU',		// (API_RVMIssue*) par1

	// get document revision
	APIInternal_GetRVMIssueDocumentRevisionID			= 'GIDR',		// (API_RVMDocumentRevision*) par1

	// get last issue
	APIInternal_GetRVMLastIssueID						= 'GLIS',		// (API_Guid*) par1

	// create and destroy GDL::FileOperations
	APIInternal_CreateGDLFileOperationsID				= 'CGFO',		// (GDL::FileOperations**) par1
	APIInternal_DestroyGDLFileOperationsID				= 'DGFO',		// (GDL::FileOperations**) par1

	// GDL Save Selection As
	APIInternal_GDLSaveSelectionAsID					= 'GSSA',		// (GS::Array<API_Guid>*) par1, (API_FileSavePars*) par2, (API_SaveSelectionAsGDLSupportPars*) par3

	// executing command function
	APIInternal_ExecuteCommandFunctionID				= 'EXFC',		// (APICommandFunctionProc*) par1, (void*) par2

	// get CID_CheckGDLWarnings command IsChecked () value
	APIInternal_GetCheckGDLWarningsIsCheckedID			= 'GDLW',		// (bool*) par1

	APIInternal_InstallTranslatorID						= 'ITTP',		// (APITranslatorProc*) par1

	APIInternal_UndoForTestID							= 'UNFT',

	APIInternal_StoreCurrentElemDefaultsID				= 'SCED',		// (EDB::IElemDefaults**) par1
	APIInternal_RestoreCurrentElemDefaultsID			= 'RCED',		// (EDB::IElemDefaults**) par1

	APIInternal_SetTWReserveCrashEnumID					= 'SCEN',		// (Int64) par1
	APIInternal_GenerateGlobalSerializerFingerPrintID	= 'GSFP',		// (MD5::FingerPrint*) par1
	APIInternal_PolygonToApiMemoID						= 'PTAM',		// (API_Polygon*) par1, (API_ElementMemo*) par2, (const Geometry::Polygon2D*) par3

	APIInternal_GetLibrariesID							= 'SELL',		// (GS::HashSet<ODB::ObjectRef>*) par1, (GS::HashSet<IO::Location>*) par2
	APIInternal_SetLibrariesID							= 'RELL',		// (GS::HashSet<ODB::ObjectRef>*) par1, (GS::HashSet<IO::Location>*) par2

	APIInternal_ClearCachedParamsUpdaterID				= 'CCPU',

	APIInternal_CalcWidoFrameThicknessID				= 'CWFT',		// (const API_Guid*) element, (double *) thickness
	APIInternal_GetHoleDimElemPositionsID				= 'GHDP',		// (const API_Guid*) element, (GS::Array<UIndex> *) dimElemPositions

	APIInternal_GetParamsID								= 'GPHD',		// (GDL::Parameters*) par1
	APIInternal_GetCWSubElemParamsID					= 'CWHD',		// (const API_Guid *) par1, (GDL::Parameters*) par2, (const char*) par3
	APIInternal_SetColorShiftID							= 'SCSH',
	APIInternal_CurrSelDisableNotificationID			= 'CSDN',
	APIInternal_CurrSelEnableNotificationID				= 'CSEN',

	APIInternal_GetAddOnObjectContentFromFile			= 'AOFF',

	APIInternal_RebuildCurrentDatabaseImmediatelyID		= 'RCDI',
	APIInternal_UpdateProfileIdentifierID				= 'UPID',
	APIInternal_UpdateAttributesInTranslatorFromFileID	= 'UPTF',

	APIInternal_ShowVisualOverrideFromPropertyDialogID	= 'SVOP',
} API_InternalID;


#if defined (ACExtension)
#ifdef __cplusplus
extern "C" {
#endif
	__APIEXPORT GSErrCode	__ACENV_CALL		ACAPI_Internal (API_InternalID code, void *par1 = nullptr, void *par2 = nullptr, void *par3 = nullptr);

	class LibraryHelper
	{
	public:
		LibraryHelper (bool needsRefresh, bool disable = true, const EDB::IElemDatabase* elemDB = nullptr) :
			needsRefresh 	(needsRefresh),
			disable 		(disable),
			elemDB			(elemDB)
		{
			if (disable)
				EnableCache (false);
		}

		~LibraryHelper ()
		{
			if (disable)
				EnableCache (true);
		}

	private:
		void EnableCache (bool enable)
		{
			ACAPI_Internal (APIInternal_RefreshLibPartCacheID, (void*)(GS::IntPtr)enable, (void*)(GS::IntPtr)(enable && needsRefresh), (void*)elemDB);
		}

		bool needsRefresh;
		bool disable;
		const EDB::IElemDatabase* elemDB;
	};
#ifdef __cplusplus
}
#endif
#endif

typedef struct {						// for APIInternal_DrawLibPartToPixMap			##VV nem ide kellene
	Int32			customFigureLibInd;
	API_AddParType	**customFigureParams;
	Int32			actFrame;
	Int32			firsFrame;
	Int32			lastFrame;
} API_MoviePars;

typedef GSErrCode	__ACENV_CALL	APICommandFunctionProc (void*);



// ==============================================================================
// Link
//
// ==============================================================================


struct API_AddOnFileOpenParameters {
	IO::Location	fileLocation;
	bool			enableCommercialFileInEDUAndTrialMode;
	GSHandle		translatorDataHandle;

	API_AddOnFileOpenParameters () :
		enableCommercialFileInEDUAndTrialMode (false),
		translatorDataHandle (nullptr)
	{
	}
};

namespace EDB {
	class Project;
}

namespace BL {
	enum class BuiltInLibPartID;
}

class IAPIAddonFileTypeHandler
{
protected:
	IAPIAddonFileTypeHandler ();
	virtual ~IAPIAddonFileTypeHandler ();
public:
	virtual GSErrCode	ConvertFile				(const API_AddOnFileOpenParameters& addOnFileOpenParameters) const = 0;
	virtual bool		HasTemplateFileLocation () const = 0;

	enum BaseProjectKind {FromCurrentProject, FromTemplateFile};
	virtual GSErrCode	GetBaseProjectInformation (const GSHandle& additionalData, IAPIAddonFileTypeHandler::BaseProjectKind& baseProjectKind, IO::Location& templateFileLocation) const = 0;
	virtual GSErrCode	TransferProjectSettings (const EDB::Project* sourceProject, EDB::Project* targetProject) const = 0;
};

namespace GS {
	class ProcessControl;
}

namespace REM {
	class Project;
}

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Link_CreateHotlinkSourceProject	(const API_AddOnFileOpenParameters&								addOnFileOpenParameters,
																				GS::ProcessControl*												processControl,
																				REM::Project*&													remSourceProject,
																				Int32*															sourcePlVersion,
																				const IAPIAddonFileTypeHandler*									handler);


// ==============================================================================
// Template
//
// ==============================================================================


struct API_TemplateManagerParameters {
	Int32 						commandId;
	bool						withPopup;
	short						dialogId;
	short						popupId;
	IO::Location*				selectLocationPtr;
	GS::Array<IO::Location>*	resultLocationsPtr;
	GSPtr 						templateManagerPtr;
};


// ==============================================================================
// Subtype
//
// ==============================================================================
#if defined (CALLBACKPROCTYPES_HPP)
typedef struct {
	CBMakeNewElemProc	makeNewElemCBProc;
	CBDrawSProc			nullLevelCBDrawProc;
	Int32				filler[4];
} APISubtypeCBProcTbl;
#else
typedef struct {
	void*				makeNewElemCBProc;
	void*				nullLevelCBDrawProc;
	void*				filler[4];
} APISubtypeCBProcTbl;
#endif

#if defined (ACExtension) && defined (CALLBACKPROCTYPES_HPP)
#ifdef __cplusplus
extern "C" {
#endif
	__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_SubtypeHandlers (
												GSType					signature,
												CBMakeNewElemProc		makeNewElemCBProc,
												CBDrawSProc				nullLevelCBDrawProc);
#ifdef __cplusplus
}
#endif
#endif

#if defined (ACExtension)
#ifdef __cplusplus
extern "C" {
#endif
	__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_SubtypeX	(GSType				signature,
																	 short				templateFileResID,
																	 bool				transparentNode,
																	 short				stringResID,
																	 short				smallIconResID,
																	 short				largeIconResID,
																	 API_TBoxGroup		toolGroupId,
																	 API_TBoxEnabled	enableFlags,
																	 short				defaultsResID,
																	 GSType*			removedPanelArray,
																	 GSSize				nRemovedPanels,
																	 MDID*				addOnID = nullptr,
																	 const API_Guid&	guid = APINULLGuid);

	__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_BuiltInSubtype	(GSType				signature,
																			 BL::BuiltInLibPartID	builtInLibPartID,
																		 	 bool				transparentNode,
																		 	 short				stringResID,
																		 	 short				smallIconResID,
																		 	 short				largeIconResID,
																		 	 API_TBoxGroup		toolGroupId,
																		 	 API_TBoxEnabled	enableFlags,
																		 	 short				defaultsResID,
																		 	 GSType*			removedPanelArray,
																		 	 GSSize				nRemovedPanels,
																		 	 bool				mountSelfResourceVFS = false,
																			 const API_Guid&	guid = APINULLGuid);

#ifdef __cplusplus
}
#endif
#endif



// ==============================================================================
// Access to the Database Manager
//
// ==============================================================================
#if defined (IELEMDATABASE_H) || defined (_ACAPLIB_TRANSL_)	/* [ */
#define DATABASE_ACCESS_SUPPORTED

// ----- Native Element ----------------------------------------------------

#if defined (ACExtension)

class APIExtendedSymbolInterface;

#ifdef __cplusplus
extern "C" {
#endif
	__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_Tool (GSType signature);		// interface description

	__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_ToolHandler (GSType						signature,
																	   APIExtendedSymbolInterface*	toolInterface);
#ifdef __cplusplus
}
#endif
#endif


// ----- Database Access -----------------------------------------------------

typedef enum {
	APIElemDB_Current	= 0,
	APIElemDB_Plan		= 1,
	APIElemDB_Section	= 2
} API_ElemDatabaseID;


#if defined (ACExtension)
#include	"Neig.hpp"

#ifdef __cplusplus
extern "C" {
#endif
	__APIEXPORT EDB::IElemRegistry*	__ACENV_CALL	ACAPI_EDB_GetElemRegistry (void);
	__APIEXPORT EDB::IElemDefaults*	__ACENV_CALL	ACAPI_EDB_GetElemDefaults (void);
	__APIEXPORT EDB::IElemDatabase*	__ACENV_CALL	ACAPI_EDB_GetElemDatabase (API_ElemDatabaseID type, Int32 id);
	__APIEXPORT short				__ACENV_CALL	ACAPI_PStatus  (Geometry::Coord*	cc,				//PT
																	Geometry::Coord3D*	c3D,
																	const NeigStore&	filter,
																	NeigData*			neigData,
																	bool				priorLastSel,
																	bool				chkLayer,
																	bool				ghostelem,
																	bool				circlingMode = false);
#ifdef __cplusplus
}
#endif
#endif
#endif	/* ] */


// ==============================================================================
// Access to the Input Level Manager and FeedBack
// (definitions in InputInterface.hpp)
// ==============================================================================
#if defined (_InputInterface_H_) || defined (_ACAPLIB_TRANSL_)	/* [ */
#define INPUTINTERFACE_ACCESS_SUPPORTED

#if defined (ACExtension)
#ifdef __cplusplus
extern "C" {
#endif
	__APIEXPORT ILMInterface*		__ACENV_CALL	ACAPI_InputInterface_GetInputLevelManager (void);
	__APIEXPORT IFeedBack*			__ACENV_CALL	ACAPI_InputInterface_GetFeedBack (void);
#ifdef __cplusplus
}
#endif
#endif

#endif	/* ] */

// ==============================================================================
// for ACAPI_Internal
//
// ==============================================================================

typedef struct {
	bool		disableDraw;				// The queried element isn't drawn due to the markup
	short 		filler_1;
											// - 0 if not affected or no markup
} API_ModifiersByMarkup;

typedef struct {
	API_HatchType	hatch;
	double			density;
} API_HatchDensity;

typedef enum {
	APIHatchDens_TooDense,
	APIHatchDens_ZeroSpacing,
	APIHatchDens_NormalDensity
} API_HatchDensityValue;

typedef struct {
	double			fBaseLine;		/* vertical distance of the top left corner and the first row's base line in mm */
	double			fHighestPos;	/* vertical distance of the the first row's base line and the top of the highest character of the first row in mm */
	double			fHighestCapI;	/* the capisize of the first row's highest character */
	double			lBaseLine;		/* vertical distance of the top left corner and the last row's base line in mm */
	double			lLowestPos;		/* vertical distance of the the last row's base line and the bottom of the lowest character of the last row in mm */
	double			filler_1;
	double			filler_2;
	double			filler_3;
} API_DetailedTextPars;				/* 9.0+ */

typedef struct {
	API_AttributeIndex		fillAttributeIndex;	/* input */
	bool					isPercentFill;		/* output */
	bool					filler_1;			/* set to 0 */
	short					filler_2;			/* set to 0 */
	double					percent;			/* output - valid only if isPercentFill == true */
} API_IsPercentFillPars;				/* 10.0+ */

typedef struct {
	API_Guid		wallGuid;		// in this wall
	API_Guid		widoGuid;		// is this window/door
	short			filler_1[3];
	short			onStory;		// on this story visible in any way?
} API_IsWindowVisibleOnFloorPars;

typedef struct {
	UInt32			numDimBases;	// number of API_DimBase instances in dimBases
	API_DimBase*	dimBases;		// the API_DimBase instances
} API_StatusPoints;

typedef struct {
	UInt32			numSectors;		// number of line status sectors in sectors
	API_Sector*		sectors;		// the API_Sector instances
} API_StatusSectors;


struct API_IFCData {
	Int32							dataVersion;				// data version
	unsigned short					platformSign;				// byte ordering in data storage
	GSHandle						dataHdl;					// user specified data
};


struct API_SaveSelectionAsGDLSupportPars {
	bool			only2D;				// create 2D only
	API_Coord3D		libpartOrigin;		// return the created libpart origin point
	bool			mepSave;
	API_Coord3D		mepOrigin;
	char			mepSubtypeUnId [128];
};


struct API_ProfileWithModifiers {
	GSIndex													index;
	std::map<API_Guid, std::pair<GS::UniString, double>>	profileParams;
	double													nominalWidth;
	double													nominalHeight;
	double													totalWidth;
	double													totalHeight;
	API_Box													coreBox;
};


struct API_SAFTranslatorProperty {
	bool			hasValue;
	API_Guid		guid;
	GS::UniString	name;
};


// ==============================================================================
// Custom parameters for DXF/DWG for Drawing Element creation
//
// ==============================================================================

typedef struct {
	API_DrawingLinkTypeID	linkType;				// drawing link type
	GS::UniString			*infoStr;				// information string (for Custom node)
	GS::UniString			*fileName;				// source file's last local name (for API/Dxf node)
	GS::UniString			*pspaceName;			// paper space name (for Dxf node)
	Int32					vportNumber;			// viewport number (for Dxf node)
	short					iconResId[4 /* = DrwLink::IconForm_end */];	// icon resource id (for API/Custom node)
	short					filler_1;
	Int32					filler_2[6];
} API_CustomDrawingPars;

// ==============================================================================
// Custom parameters for DXF/DWG for Drawing Element creation
//
// ==============================================================================

struct API_RoomUpdateParams {
	bool					keepStampPos;
	bool					undoTopTrim;
	bool					undoBotTrim;
	bool					filler_1[5];

	API_RoomUpdateParams () : keepStampPos (true), undoTopTrim (false), undoBotTrim (false)
	{}

};


// ==============================================================================
// Callback function for DXF/DWG for converting XRef Group Memo to Hotlink userdata
// and from/to pre-Vitruvius format
//
// ==============================================================================

#define	APIGroup_TrackTransformation	0x01L

#define	APIGroupOwner_ACModFile		'ACMF'

typedef struct {
	GSType							ownerId;
	Int32							flags;
} API_GroupHead;

typedef struct {
	double							x0;							// base coordinate
	double							y0;
	double							z0;
	double							xs;							// scale parameters
	double							ys;							// scale parameters
	double							zs;							// scale parameters
	double							angle;						// rotation angle
} API_GroupTrafo;

typedef GSErrCode	__ACENV_CALL	APIConvertGroupMemoToHotlinkNodeProc (GSType ownerId, const API_GroupHead** groupData, API_HotlinkNode* hotlinkNode, double& drawingUnit);
typedef GSErrCode	__ACENV_CALL	APIConvertHotlinkNodeToGroupMemoProc (GSType ownerId, const API_HotlinkNode* hotlinkNode, API_GroupHead*** groupData);
typedef GSErrCode	__ACENV_CALL	APIConvertHotlinkNodeProc (GSType ownerId, API_HotlinkNode* newhotlinkNode, const API_HotlinkNode* oldhotlinkNode);	// hotlinkNode is In/Out parameter!!!
typedef GSErrCode	__ACENV_CALL	APIGetOldVersionCompatibleUserDataProc (GSType ownerId, GSPtr* userData, const API_HotlinkNode* hotlinkNode);	// the addon allocates 'userData'...

typedef struct {
		APIConvertGroupMemoToHotlinkNodeProc*	convertGroupMemoToHotlinkNodeProc;	// convert from xref group data to hotlink userdata (from pre-AC12 versions)
		APIConvertHotlinkNodeToGroupMemoProc*	convertHotlinkNodeToGroupMemoProc;	// convert from hotlink userdata to xref group data (to pre-AC12 versions)
		APIConvertHotlinkNodeProc*				convertFromOldHotlinkNode;			// upgrade hotlink userdata to current version
		APIConvertHotlinkNodeProc*				convertBackToOldHotlinkNode;		// convert hotlink userdata back to old format
		APIGetOldVersionCompatibleUserDataProc*	getOldVersionCompatibleUserData;
} API_HotlinkConverterProcs;

// ==============================================================================
// Callback function for DXF/DWG for converting translators back to
// pre-Vitruvius format
//
// ==============================================================================

typedef GSErrCode	__ACENV_CALL	APIConvertTranslatorToOldVersionProc (GSType ownerId, const GSPtr actver_content, GSPtr* oldver_content);

typedef struct {
		APIConvertTranslatorToOldVersionProc*	convertTranslatorToOldVersion;
} API_TranslatorConverterProcs;

typedef GSErrCode	__ACENV_CALL	APITranslatorProc (Localization::PoDictionary& dictionary);

// ==============================================================================
// Interactive Element Schedule
//
// ==============================================================================
#if defined (_IIESUTIL_H_) || defined (_ACAPLIB_TRANSL_) /* [ */

namespace IES {
	class IIESUtil;
	class ACUtil;
	class IESCommonDBManager;
	class IESLinkManager;
}

#ifdef __cplusplus
extern "C" {
#endif
	__APIEXPORT GSErrCode					__ACENV_CALL	ACAPI_Register_IESUtil (IES::IIESUtil* iesutil);
	__APIEXPORT IES::ACUtil*				__ACENV_CALL	ACAPI_GetACUtil (void);
	__APIEXPORT IES::IESCommonDBManager*	__ACENV_CALL	ACAPI_GetIESDBManager (void);
	__APIEXPORT IES::IESLinkManager*		__ACENV_CALL	ACAPI_GetIESLinkManager (void);
#ifdef __cplusplus
}
#endif

#endif

// ==============================================================================
// EcoDesigner
//
// ==============================================================================

#define APIST_EmptyOpenings		1	// for APIInternal_IsSymbolTypeOfID
#define APIST_EmptySkylight		2	// for APIInternal_IsSymbolTypeOfID
#define APIST_WallExtraWindow	4	// for APIInternal_IsSymbolTypeOfID

// ==============================================================================
//
//
// ==============================================================================

class UtilityFunctionSet;
class IProductRegistry;

#ifdef __cplusplus
extern "C" {
#endif
	__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_SetUnloadable (bool unloadable);
	__APIEXPORT UtilityFunctionSet*	__ACENV_CALL	ACAPI_GetUtilityFunctionSet (void);
	__APIEXPORT IProductRegistry*	__ACENV_CALL	ACAPI_GetProductRegistry (void);
#ifdef __cplusplus
}
#endif

#endif // _APIHelper_HPP_
