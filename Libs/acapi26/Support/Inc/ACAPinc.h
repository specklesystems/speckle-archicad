// *********************************************************************************************************************
// API functions
//
// Module:			API
// Namespace:		-
// Contact person:
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (ACAPINC_H)
#define	ACAPINC_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

#if defined (WINDOWS)
#include "Win32Interface.hpp"
#endif

// STL
#include <unordered_set>
#include <unordered_map>

// GSRoot
#include "GSRoot.hpp"
#include "Array.hpp"
#include "PagedArray.hpp"
#include "UniString.hpp"
#include "Owner.hpp"

// own
#include "APICalls.h"
#include "APIdefs.h"

// --- Predeclarations -------------------------------------------------------------------------------------------

namespace Geometry {
	class PolyId;

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData> class CustomMultiPolygon2D;
	typedef CustomMultiPolygon2D<PolyId, PolyId, PolyId, PolyId> MultiPolygon2D;
}


// --- Compiler settings -----------------------------------------------------------------------------------------------

#if defined (_MSC_VER)
	#pragma pack(push, 8)
#endif


// --- Predeclarations -------------------------------------------------------------------------------------------

namespace Modeler {
	class MeshBody;
	class IAttributeReader;
}

// --- Function declarations -------------------------------------------------------------------------------------------

// =============================================================================
// Functions must be supported by the addon
//
// Following functions must be implemented in each extension.
// They are called from ARCHICAD.
// For detailed description refer to the enclosed documentation.
//
// =============================================================================

extern "C" {

API_AddonType	__ACDLL_CALL	CheckEnvironment (API_EnvirParams* envirParams);
GSErrCode		__ACDLL_CALL	RegisterInterface (void);
GSErrCode		__ACDLL_CALL	Initialize (void);
GSErrCode		__ACDLL_CALL	FreeData (void);

}



#if defined (ACExtension)
/* [ --> */
// =============================================================================
// Function supported by the API
//
// Following functions are supported by the ACAP library.
// For detailed description refer to the enclosed documentation.
//
// =============================================================================

/* -- Server ------------------------------ */
#define	ServerMainVers_600			0x0001			// Package 6.00:  (ARCHICAD 6.0, PlotMaker 2.1)
#define	ServerMainVers_650			0x0002			// Package 6.50:  (ARCHICAD 6.5, PlotMaker 2.2)
#define	ServerMainVers_700			0x0003			// Package 7.00:  (ARCHICAD 7.0, PlotMaker 2.3)
#define	ServerMainVers_800			0x0004			// Package 8.00:  (ARCHICAD 8,   PlotMaker 3)
#define	ServerMainVers_810			0x0005			// Package 8.10:  (ARCHICAD 8.1, PlotMaker 3.1)
#define	ServerMainVers_900			0x0006			// Package 9.00:  (ARCHICAD 9,   PlotMaker 9)
#define	ServerMainVers_1000			0x000A			// ARCHICAD 10
#define	ServerMainVers_1100			0x000B			// ARCHICAD 11
#define	ServerMainVers_1200			0x000C			// ARCHICAD 12
#define	ServerMainVers_1300			0x000D			// ARCHICAD 13
#define	ServerMainVers_1400			0x000E			// ARCHICAD 14
#define	ServerMainVers_1500			0x000F			// ARCHICAD 15
#define	ServerMainVers_1600			0x0010			// ARCHICAD 16
#define	ServerMainVers_1700			0x0011			// ARCHICAD 17
#define	ServerMainVers_1800			0x0012			// ARCHICAD 18
#define	ServerMainVers_1900			0x0013			// ARCHICAD 19
#define	ServerMainVers_2000			0x0014			// ARCHICAD 20
#define	ServerMainVers_2100			0x0015			// ARCHICAD 21
#define	ServerMainVers_2200		    0x0016			// ARCHICAD 22
#define	ServerMainVers_2300		    0x0017			// ARCHICAD 23
#define	ServerMainVers_2400		    0x0018			// ARCHICAD 24
#define	ServerMainVers_2500		    0x0019			// ARCHICAD 25
#define	ServerMainVers_2600		    0x001A			// ARCHICAD 26

#define	ServerReleaseVers_R1		1



__APIEXPORT void		__ACENV_CALL	ACAPI_GetReleaseNumber (API_ServerApplicationInfo	*serverApplicationInfo);

/* -- System ------------------------------ */

#if defined (WINDOWS)
__APIEXPORT HINSTANCE	__ACENV_CALL	ACAPI_GetExtensionInstance (void);

__APIEXPORT HWND		__ACENV_CALL	ACAPI_GetMainWindow (void);
#endif
__APIEXPORT GSResModule	__ACENV_CALL	ACAPI_GetOwnResModule (void);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_GetOwnLocation (IO::Location *ownFileLoc);

__APIEXPORT void		__ACENV_CALL	ACAPI_SetDllTermHookProc (APIDllTermHookProc* dllTermHookProc);


/* -- Registration ------------------ */

	// CheckEnvironment
__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_SupportedService (GSType cmdID, Int32 cmdVersion);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_RequiredService (const API_ModulID	*modulID,
																		GSType				cmdID,
																		Int32				cmdVersion);

	// RegisterInterface
__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_Menu		(short			menuStrResID,
																 short			promptStrResID,
																 APIMenuCodeID	menuPosCode,
																 GSFlags		menuFlags);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_FileType (Int32			refCon,
																 GSType			ftype,
																 GSType			fcreator,
																 const char		*extname,
																 short			iconResID,
																 short			descStrResID,
																 short			descStrResItemID,
																 API_IOMethod	methodFlags);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_Subtype	(GSType				signature,				// identifier
																 short				templateFileResID,		// subtype template (FILE resource ID)
																 bool				transparentNode,		// allow ancestor tools to place object instances
																 short				stringResID,			// tool descriptions (STR# resource ID)
																 short				smallIconResID,			// toolbar icon
																 short				largeIconResID,			// toolbox icon
																 API_TBoxGroup		toolGroupId,			// toolbar group
																 API_TBoxEnabled	enableFlags,			// toolbar enable flags
																 short				defaultsResID);			// factory defaults (ACP0 resource ID)

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_SettingsPanel	(Int32					refCon,
																		 const API_ElemType&	tool,
																		 short					iconId,
																		 short					stringId,
																		 short					pageId,
																		 short					growType = 0,	// means NoGrow
																		 bool					visibleByDefault = false);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_AttributePanel	(Int32					refCon,
																		 API_AttrTypeID			attr,
																		 short					iconId,
																		 short					stringId,
																		 short					pageId,
																		 short					growType = 0);	// means NoGrow

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_InfoBoxPanel		(Int32					refCon,
																		 const API_ElemType&	tool,
																		 short					stringId,
																		 short					pageId,
																		 bool					visibleByDefault = false);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_ESYM		(GSType			signature,				// LibPart owner ID
																 API_LibTypeID	typeID,					// LibPart base type (Window, Door, Object, Lamp)
																 short			stringResID);			// description

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_PropertyObjectHandler (short assignStrResID);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_BuiltInLibrary (void);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_ModulDataHandler (void);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_ClassificationVisibilityHandler (void);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_PropertyVisibilityHandler (void);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_AddOnObjectHandler (void);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_NavigatorAddOnViewPointDataHandler (void);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_SettingsObserver (const API_ElemType& tool);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_AttributeImportFormat (const API_AttributeManagerFormat& formatData);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Register_PublishFormat (const API_PublishFormatData& formatData);

	// Initialize
__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_ModulCommandHandler  (GSType					cmdID,
																			Int32					cmdVersion,
																			APIModulCommandProc*	handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_MenuHandler		   (short					menuStrResID,
																			APIMenuCommandProc*		handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_FileTypeHandler	   (GSType					cmdID,
																			APIIOCommandProc*		handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_FileTypeHandler3D	   (GSType					cmdID,
																			APIIO3DCommandProc*		handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_PanelHandler (Int32					refCon,
																	APIPanelCreateProc*		handlerCreateProc,
																	APIPanelDestroyProc*	handlerDestroyProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_AddOnCommandHandler (GS::Owner<API_AddOnCommand> addOnCommand);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_ESYMHandler		   (GSType					signature,
																			APIESYMCommandProc*		handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_PropertyObjectHandler	(short					 		strResID,
																			 APIPropertyObjectCommandProc*  propertyCommandProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_ModulDataMergeHandler	(APIModulDataMergeHandlerProc* mergeHandlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_ModulDataSaveOldFormatHandler (APIModulDataSaveOldFormatHandlerProc* modulDataSaveOldFormatProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_ElemSetSaveOldFormatHandler (APIElemSetSaveOldFormatHandlerProc* elemSetSaveOldFormatProc);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_AddOnObjectMergeHandler			(APIAddonObjectMergeHandlerProc*				mergeHandlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_AddOnObjectSaveOldFormatHandler	(APIAddonObjectSaveOldFormatHandlerProc*		saveOldFormatProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_AddOnObjectConvertNewFormatHandler (APIAddonObjectConvertNewFormatHandlerProc*	convertNewFormatProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_NavigatorAddOnViewPointDataMergeHandler			 (APINavigatorAddOnViewPointDataMergeHandlerProc*				mergeHandlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_NavigatorAddOnViewPointDataSaveOldFormatHandler	 (APINavigatorAddOnViewPointDataSaveOldFormatHandlerProc*		saveOldFormatProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_NavigatorAddOnViewPointDataConvertNewFormatHandler (APINavigatorAddOnViewPointDataConvertNewFormatHandlerProc*	convertNewFormatProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_SettingsHandler (const API_ElemType&			tool,
																	   APISettingsCreateProc*		handlerCreateProc,
																	   APISettingsDestroyProc*		handlerDestroyProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_ClassificationVisibilityHandler (APIClassificationVisibilityHandlerProc* handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_PropertyVisibilityHandler (APIPropertyVisibilityHandlerProc* handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_PublisherSaveMethod (const char* mimeType, SaveProc* saveProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_PublisherSaveOption (const char* mimeType, SaveOptionProc* saveOptionProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_PublisherTranslatorGetter (const char* mimeType, TranslatorGetterProc* translatorGetterProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_PublisherDefaultTranslatorGetter (const char* mimeType, DefaultTranslatorGetterProc* defaultTranslatorGetterProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Install_AttrManagerImportMethod (const GS::UniString& fileExtension, ImportAttrProc* importProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Inform_AdditionalFileWasCreated (const IO::Location& path);


/* -- Memory Manager ---------------------- */
/**
 * @defgroup MemMgr Memory Manager
 */
/*@{*/

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_DisposeAddParHdl (API_AddParType ***addPars);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_DisposeParagraphsHdl (API_ParagraphType ***paragraphs);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_DisposeElemMemoHdls (API_ElementMemo *memo);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_DisposeAttrDefsHdls (API_AttributeDef *defs);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_DisposeAttrDefsHdlsExt (API_AttributeDefExt *defs);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_DisposeRoomRelationHdls (API_RoomRelation *roomInfo);

__APIEXPORT void		__ACENV_CALL	ACAPI_DisposeWallRelationHdls (API_WallRelation *wallInfo);

__APIEXPORT void		__ACENV_CALL	ACAPI_DisposeBeamSegmentRelationHdls (API_BeamSegmentRelation *segmentInfo);

__APIEXPORT void		__ACENV_CALL	ACAPI_DisposeBeamRelationHdls (API_BeamRelation *beamInfo);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_FreeCWContourPtr (API_CWContourData **contours);

__APIEXPORT void		__ACENV_CALL	ACAPI_FreeGDLModelViewOptionsPtr (API_GDLModelViewOptions **gdlModelViewOptions);

/*@}*/

/* -- Resource Manager -------------------- */
/**
 * @defgroup ResMgr Resource Manager
 */
/*@{*/

__APIEXPORT bool		__ACENV_CALL	ACAPI_Resource_GetLocStr (char *str, short resID, short index, GSResModule resModule = ACAPI_GetOwnResModule ());

__APIEXPORT bool		__ACENV_CALL	ACAPI_Resource_GetLocUStr (GS::uchar_t *str, short resID, short index, GSResModule resModule = ACAPI_GetOwnResModule ());

__APIEXPORT bool		__ACENV_CALL	ACAPI_Resource_GetFixStr (char *str, short resID, short index, GSResModule resModule = ACAPI_GetOwnResModule ());

/*@}*/

/* -- Client Manager ---------------------- */
__APIEXPORT void		__ACENV_CALL	ACAPI_KeepInMemory (bool keepIn);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_SetPreferences (Int32 version, GSSize nByte, const void *data);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_GetPreferences (Int32 *version, GSSize *nByte, void *data);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_GetPreferences_Platform (Int32			*version,
																	   GSSize			*nByte,
																	   void				*data,
																	   unsigned short	*platformSign);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_SetPreferences_OldVersion (Int32				version,
																		 GSSize				nByte,
																		 const void*		data,
																		 unsigned short		platformSign,
																		 API_FTypeID		oldPlanFileID);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_RegisterModelessWindow (Int32							referenceID,
																	  APIPaletteControlCallBackProc	*callBackProc,
																	  GSFlags						controlFlags,
																	  const API_Guid&				paletteGuid = APINULLGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_UnregisterModelessWindow (Int32 referenceID);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_CallUndoableCommand (const GS::UniString& undoString, const std::function<GSErrCode ()>& command);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_CallCommand (const GS::UniString& commandName, const std::function<GSErrCode ()>& command);

__APIEXPORT API_Token	__ACENV_CALL	ACAPI_GetToken (void);

__APIEXPORT void		__ACENV_CALL	ACAPI_WriteReport (const GS::UniString& format, bool withDial, ...);


/* -- General Manager --------------------- */
/**
 * @defgroup GenFunc General Functions
 */
/*@{*/

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Database		(API_DatabaseID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Environment	(API_EnvironmentID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Interface		(API_InterfaceID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr, void* par4 = nullptr, void* par5 = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Goodies		(API_GoodiesID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr, void* par4 = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Automate		(API_AutomateID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Navigator		(API_NavigatorID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr, void* par4 = nullptr);

/*@}*/


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Goodies_GetMarkerParent	(const API_ElemType& elemType, API_LibPart& libPart);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Goodies_GetElemTypeName	(const API_ElemType& elemType, GS::UniString& name);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Goodies_NeigIDToElemType	(API_NeigID neigID, API_ElemType& elemType);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Goodies_ElemTypeToNeigID	(const API_ElemType& elemType, API_NeigID& neigID);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Database_GetLast3DDefLevels	(const GS::Array<API_ElemType>& elemTypes, GS::Array<double>& levels);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Database_SetLast3DDefLevels	(const GS::Array<API_ElemType>& elemTypes, const GS::Array<double>& levels);


/* -- Interface Manager --------------------- */
/**
 * @defgroup InterMan Interface Manager
 */
 /*@{*/
__APIEXPORT void		__ACENV_CALL	ACAPI_Interface_SetElementHighlight (const GS::HashTable<API_Guid, API_RGBAColor>& highlightedElems, const GS::Optional<bool>& wireframe3D = GS::NoValue, const GS::Optional<API_RGBAColor>& nonHighlightedElemsColor = GS::NoValue);
__APIEXPORT void		__ACENV_CALL	ACAPI_Interface_ClearElementHighlight ();

__APIEXPORT void		__ACENV_CALL	ACAPI_Interface_InvokeForwardDialog	();


/* -- Override Manager --------------------- */
/**
 * @defgroup OverMan Override manager
 */
/*@{*/

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Override_GetOverrideCombinationList (GS::Array<API_Guid>& combinationList);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Override_GetOverrideRuleList		  (GS::Array<API_Guid>& ruleList);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Override_GetOverrideCombination	  (API_OverrideCombination& combination,
																				   GS::Array<API_Guid>* ruleList = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Override_GetOverrideRule			  (API_OverrideRule& rule);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Override_CreateOverrideCombination  (API_OverrideCombination& combination,
																				   const GS::Array<API_Guid>& ruleList);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Override_CreateOverrideRule		  (API_OverrideRule& rule);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Override_ChangeOverrideCombination  (const API_OverrideCombination& combination,
																				   const GS::Array<API_Guid>* const ruleList = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Override_ChangeOverrideRule		  (const API_OverrideRule& rule);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Override_DeleteOverrideCombination  (const API_Guid& combination);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Override_DeleteOverrideRule		  (const API_Guid& rule);

/*@}*/

/* -- Attribute Manager ------------------- */

/**
 * @defgroup AttrMan Attribute Manager
 */
/*@{*/

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_GetNum (API_AttrTypeID typeID, API_AttributeIndex *count);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_Get (API_Attribute *attribute);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_GetDef (API_AttrTypeID typeID, API_AttributeIndex index, API_AttributeDef *defs);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_GetDefExt (API_AttrTypeID		typeID,
																   API_AttributeIndex	index,
																   API_AttributeDefExt	*defs);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_Create (API_Attribute *attribute, API_AttributeDef *defs);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_CreateExt (API_Attribute *attribute, API_AttributeDefExt *defs);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_Modify (API_Attribute *attribute, API_AttributeDef *defs);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_ModifyExt (API_Attribute *attribute, API_AttributeDefExt *defs);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_Search (API_Attr_Head *attrHead);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_Delete (const API_Attr_Head& attrHead);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_DeleteMore (API_AttrTypeID attrTypeID, const GS::Array<API_AttributeIndex>& attrIndexList);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_GetUserData (API_Attr_Head			*attrHead,
																	 API_AttributeUserData	*userData);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_SetUserData (API_Attr_Head					*attrHead,
																	 const API_AttributeUserData	*userData);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_GetAttributesFromProject (const IO::Location&										location,
																				  API_AttrTypeID											typeID,
																				  GS::Array<GS::Pair<API_Attribute, API_AttributeDefExt>>*	resultArray);

__APIEXPORT Modeler::IAttributeReader*	__ACENV_CALL	ACAPI_Attribute_GetCurrentAttributeSetReader ();

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_GetFolder	(API_AttributeFolder& folder);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_CreateFolder (API_AttributeFolder& folder);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_Move (const GS::Array<API_AttributeFolder>&	foldersToMove,
															  const GS::Array<GS::Guid>&			attributesToMove,
															  const API_AttributeFolder&			targetFolder);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_GetFolderContent	(const API_AttributeFolder& folder,
																			API_AttributeFolderContent& result);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_DeleteFolder (const API_AttributeFolder& folder);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_RenameFolder (const API_AttributeFolder& folder, const GS::UniString& newName);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Interface_CreateAttributePicker (const API_AttributePickerParams& attributePickerParams,
																			   GS::Owner<API_AttributePicker>& attributePicker);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_CreateAttributeFolderPicker	(const API_AttributeFolderPickerParams& attributeFolderPickerParams,
																					GS::Owner<API_AttributeFolderPicker>& attributeFolderPicker);
/*@}*/

/* -- Library Part Manager ---------------- */

/**
 * \defgroup LPMan Library Part Manager
 */
/*@{*/

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_GetNum (Int32 *count);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_Search (API_LibPart *ancestor, bool createIfMissing, bool onlyPlaceable = false);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_PatternSearch (const API_LibPart *ancestor, const GS::UniString& pattern, API_LibPart result[50], Int32* numFound);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_Get (API_LibPart *libPart);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_GetParams (Int32			libInd,
																 double			*a,
																 double			*b,
																 Int32			*addParNum,
																 API_AddParType	***addPars);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_GetSection (Int32					libInd,
																  API_LibPartSection	*section,
																  GSHandle				*sectionHdl,
																  GS::UniString			*sectionStr,
																  GS::UniString			*password = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_UpdateSection (Int32						libInd,
																	 const API_LibPartSection	*section,
																	 GSHandle					sectionHdl,
																	 GS::UniString				*sectionStr,
																	 GS::UniString				*password = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_SetUpSect_2DDrawHdl (void);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_GetSect_2DDrawHdl (GSHandle *sectionHdl);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_GetSect_ParamDef (const API_LibPart	*libPart,
																		API_AddParType		**addPars,
																		double				*a,
																		double				*b,
																		GSHandle			sect2DDrawHdl,
																		GSHandle			*sectionHdl,
																		GS::UniString		*password = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_Create (const API_LibPart *libPart);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_AddSection (const API_LibPartSection	*section,
																  GSHandle					sectionHdl,
																  GS::UniString				*sectionStr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_NewSection (const API_LibPartSection *section);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_WriteSection (Int32 nByte, GSConstPtr data);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_EndSection (void);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_Save (API_LibPart *libPart);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_ShapePrims (Int32				libInd,
																  const API_Guid&	instanceElemGuid,
																  short				gdlContext,
																  ShapePrimsProc	*shapePrimsProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_GetHotspots (Int32				libInd,
																   const API_Guid&		instanceElemGuid,
																   Int32*				nHotspots,
																   API_PrimHotspot***	hotspots);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_Register (API_LibPart *libPart);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_RegisterAll (GS::Array<API_LibPart>* libParts);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_GetSectionList (Int32					libInd,
																	  Int32					*nSection,
																	  API_LibPartSection	***sections);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_GetDetails (Int32					libInd,
																  API_LibPartDetails	*details);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_LibPart_SetDetails_ParamDef (const API_LibPart		*libPart,
																		   GSHandle					paramHdl,
																		   const API_LibPartDetails	*details);

/*@}*/

/* -- Element Manager --------------------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetDefaults (API_Element *element, API_ElementMemo *memo);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetDefaultsExt (API_Element			*element,
																	  API_ElementMemo		*memo,
																	  UInt32				nSubElems,
																	  API_SubElement		*subElems);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_ChangeDefaults (API_Element		*element,
																	  API_ElementMemo	*memo,
																	  const API_Element	*mask);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_ChangeDefaultsExt (API_Element			*element,
																		 API_ElementMemo		*memo,
																		 const API_Element		*mask,
																		 UInt32					nSubElems,
																		 API_SubElement			*subElems);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetElemList (const API_ElemType&	type,
																   GS::Array<API_Guid>*	elemList,
																   API_ElemFilterFlags	filterBits = APIFilt_None,
																   const API_Guid&		renovationFilterGuid = APINULLGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetConnectedElements (const API_Guid&			guid,
																			const API_ElemType&		connectedElemType,
																			GS::Array<API_Guid>*	connectedElements,
																			API_ElemFilterFlags		filterBits = APIFilt_None,
																			const API_Guid&			renovationFilterGuid = APINULLGuid);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Element_Filter (const API_Guid&		guid,
															  API_ElemFilterFlags	filterBits,
															  API_ElemVariationID	variationID = APIVarId_Generic,
															  const API_Guid&		renovationFilterGuid = APINULLGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Get (API_Element *element,
														   UInt32		mask = 0);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetHeader (API_Elem_Head *elementHead,
																 UInt32			mask = 0);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetMemo	(const API_Guid&			guid,
																 API_ElementMemo*			memo,
																 UInt64						mask = APIMemoMask_All);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_ChangeMemo (API_Guid&				guid,
																  UInt64				mask,
											   					  const API_ElementMemo	*memo);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetRelations (const API_Guid&		guid,
																	const API_ElemType&	otherType,
																	void*				relData,
																	UInt32				mask = 0);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetSyTran (const API_Elem_Head *elemHead, API_SyTran *syTran);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetHotspots (const API_Guid&					guid,
																   GS::Array<API_ElementHotspot>*	hotspotArray);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Create (API_Element *element, API_ElementMemo *memo);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_CreateExt (API_Element			*element,
																 API_ElementMemo		*memo,
																 UInt32					nSubElems,
																 API_SubElement			*subElems);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_ChangeParameters (const GS::Array<API_Guid>&	elemGuids,
							   											const API_Element			*defPars,
																		const API_ElementMemo		*defMemo,
												   						const API_Element			*mask);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Change (API_Element			*element,
															  const API_Element		*mask,
															  const API_ElementMemo	*memo,
															  UInt64				memoMask,
															  bool					withdel);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_ChangeMore (GS::Array<API_Guid>&	elemGuids,
							   									  const API_Element		*defPars,
																  const API_ElementMemo	*defMemo,
												   				  const API_Element		*mask,
																  UInt64				memoMask,
																  bool					withdel);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_ChangeExt (API_Element			*element,
																 const API_Element		*mask,
																 API_ElementMemo		*memo,
																 UInt64					memoMask,
																 UInt32					nSubElems,
																 API_SubElement			*subElems,
																 bool					withdel,
																 Int32					subIndex);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Delete (const GS::Array<API_Guid>& elemGuids);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_DeleteSelected ();

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Edit (GS::Array<API_Neig>* elemNeigs, const API_EditPars& pars);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Tool (const GS::Array<API_Guid>&	elemGuids,
															API_ToolCmdID				typeID,
															void						*pars);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Select (const GS::Array<API_Neig>& selNeigs, bool add);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_DeselectAll ();


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetUserData	(API_Elem_Head				*elemHead,
																	 API_ElementUserData		*userData,
																	 UInt32						mask = 0);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SetUserData	(API_Elem_Head				*elemHead,
																	 const API_ElementUserData	*userData);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_DeleteUserData (API_Elem_Head *elemHead);

__APIEXPORT API_Guid	__ACENV_CALL	ACAPI_Element_UnIdToGuid (API_DatabaseUnId databaseUnId, UInt32 elemUnId);

__APIEXPORT API_Guid	__ACENV_CALL	ACAPI_Element_LinkIdToDrwGuid (Int32 linkId);

__APIEXPORT Int32		__ACENV_CALL	ACAPI_Element_DrwGuidToLinkId (API_Guid drwGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Link (const API_Guid&	guid_linkFrom,
															const API_Guid&	guid_linkTo,
															GSFlags			linkFlags);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Unlink (const API_Guid&	guid_linkFrom,
															  const API_Guid&	guid_linkTo);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetLinks (const API_Guid&			guid_linkFrom,
																GS::Array<API_Guid>*	guids_linkTo);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetLinkFlags (const API_Guid&	guid_linkFrom,
																	const API_Guid&	guid_linkTo,
																	GSFlags			*linkFlags);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_AttachObserver (const API_Guid& elemGuid, GSFlags notifyFlags = 0);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_DetachObserver (const API_Guid& elemGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetObservedElements (GS::Array<API_Elem_Head> *elemHeads);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SolidOperation_Create (API_Guid				guid_Target,
																			 API_Guid				guid_Operator,
																			 API_SolidOperationID	operation,
																			 GS::Array<API_Guid>*	guid_Results = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SolidLink_Create (API_Guid				guid_Target,
																		API_Guid				guid_Operator,
																		API_SolidOperationID	operation,
																		GSFlags					linkFlags);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SolidLink_Remove (API_Guid	guid_Target,
																		API_Guid	guid_Operator);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SolidLink_GetTime (API_Guid		guid_Target,
																		 API_Guid		guid_Operator,
																		 GSTime			*linkTime,
																		 UInt32			*linkSubTime);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SolidLink_GetOperation (API_Guid				guid_Target,
																			  API_Guid				guid_Operator,
																			  API_SolidOperationID	*operation);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SolidLink_GetFlags (API_Guid	guid_Target,
																		  API_Guid	guid_Operator,
																		  GSFlags	*linkFlags);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SolidLink_GetTargets (API_Guid			guid_Operator,
																			GS::Array<API_Guid>	*guid_Targets);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SolidLink_GetOperators (API_Guid				guid_Target,
																			  GS::Array<API_Guid>	*guid_Operators);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Get3DInfo			(const API_Elem_Head&	elemHead,
																		 API_ElemInfo3D			*info3D);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetQuantities		(API_Guid							elemGuid,
								  										 const API_QuantityPar				*params,
																		 API_Quantities						*quantities,
																		 const API_QuantitiesMask			*mask = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetMoreQuantities	(const GS::Array<API_Guid>			*elemGuids,
								  										 const API_QuantityPar				*params,
																		 GS::Array<API_Quantities>			*quantities,
																		 const API_QuantitiesMask			*mask = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetSurfaceQuantities	(const GS::Array<API_Guid>				*elemGuids,
								  											 const GS::Array<API_Guid>				*coverElemGuids,
																			 GS::Array<API_ElemPartSurfaceQuantity>	*quantities);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetPropertyObjects	(const API_Elem_Head		*elemHead,
																			 API_PropertyObjectRefType	***propRefs,
																			 Int32						*nProp);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetComponents_Obsolete	(const API_Elem_Head			*elemHead,
																				 API_Obsolete_ComponentRefType	***compRefs,
																				 Int32							*nComp);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetDescriptors			(const API_Elem_Head		*elemHead,
																				 API_DescriptorRefType		***descRef,
																				 Int32						*nDesc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_ShapePrims				(const API_Elem_Head&	elemHead,
																				 ShapePrimsProc			*shapePrimsProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_ShapePrimsExt (const API_Elem_Head&	elemHead,
																	 ShapePrimsProc			*shapePrimsProc,
																	 API_ShapePrimsParams*	shapePrimsParams);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetLinkedPropertyObjects (const API_Elem_Head		*head,
																				bool					*criteria,
																				Int32					*inviduallyLibInd,
																				Int32					**critLibInds,
																				Int32					*nCrits);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SetLinkedPropertyObjects (API_Elem_Head		*head,
																				bool				criteria,
																				Int32				inviduallyLibInd);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetCategoryValue (const API_Guid&					elemGuid,
																		const API_ElemCategory&			elemCategory,
																		API_ElemCategoryValue*			elemCategoryValue);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetCategoryValueDefault (const API_ElemType&			type,
																			   const API_ElemCategory&		elemCategory,
																			   API_ElemCategoryValue*		elemCategoryValue);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SetCategoryValue (const API_Guid&					elemGuid,
																		const API_ElemCategory&			elemCategory,
																		const API_ElemCategoryValue&	elemCategoryValue);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SetCategoryValueDefault (const API_ElemType&				type,
																			   const API_ElemCategory&			elemCategory,
																			   const API_ElemCategoryValue&		elemCategoryValue);

/* -- Element Composition ----------------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Trim_Elements			(const GS::Array<API_Guid>&	guid_ElementsToTrim);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Trim_ElementsWith		(const GS::Array<API_Guid>&	guid_ElementsToTrim,
																			 const API_Guid&			guid_Element,
																			 API_TrimTypeID				trimType);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Trim_Remove			(const API_Guid&			guid_Element1,
																			 const API_Guid&			guid_Element2);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Trim_GetTrimType		(const API_Guid&			guid_Element1,
																			 const API_Guid&			guid_Element2,
																			 API_TrimTypeID*			trimType);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Trim_GetTrimmedElements	(const API_Guid&		guid_Element,
																				 GS::Array<API_Guid>*	guid_TrimmedElements);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Trim_GetTrimmingElements	(const API_Guid&		guid_Element,
																				 GS::Array<API_Guid>*	guid_TrimmingElements);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Merge_Elements			(const GS::Array<API_Guid>&	guid_ElementsToMerge);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Merge_GetMergedElements	(const API_Guid&		guid_Element,
																				 GS::Array<API_Guid>*	guid_MergedElements);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Merge_Remove				(const API_Guid&	guid_Element1,
																				 const API_Guid&	guid_Element2);

/* -- IFC --------------------------------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetIFCIdentifier		(const API_Guid&				elementID,
																			 API_Guid&						archicadIFCID,
																			 API_Guid&						externalIFCID);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetElemListByIFCIdentifier	(const API_Guid*				archicadIFCID,
																					 const API_Guid*				externalIFCID,
																					 GS::Array<API_Guid>&			elements);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetIFCType			(const API_Guid&				elementID,
																			GS::UniString*					ifcType,
																			GS::UniString*					typeObjectIFCType);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetIFCProperties		(const API_Guid&				guid_Element,
																			 bool							storedOnly,
																			 GS::Array<API_IFCProperty>*	properties);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SetIFCProperty		(const API_Guid&				guid_Element,
																			 const API_IFCProperty&			property);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_RemoveIFCProperty		(const API_Guid&				guid_Element,
																			 const API_IFCProperty&			property);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetIFCAttributes		(const API_Guid&				guid_Element,
																			 bool							storedOnly,
																			 GS::Array<API_IFCAttribute>*	attributes);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SetIFCAttribute		(const API_Guid&				guid_Element,
																			 const API_IFCAttribute&		attribute);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetIFCClassificationReferences	(const API_Guid&							guid_Element,
																						 bool										storedOnly,
																						 GS::Array<API_IFCClassificationReference>*	classificationReferences);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SetIFCClassificationReference		(const API_Guid&						guid_Element,
																						 const API_IFCClassificationReference&	classificationReference);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_RemoveIFCClassificationReference	(const API_Guid&						guid_Element,
																						 const API_IFCClassificationReference&	classificationReference);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetIFCPropertyValuePrimitiveType	(const GS::UniString&					valueType,
																						 API_IFCPropertyValuePrimitiveType*		primitiveType);

/* -- Classification related functions ----------------- */

__APIEXPORT GSErrCode 	__ACENV_CALL	ACAPI_Element_GetClassificationItems	(const API_Guid& elemGuid, GS::Array<GS::Pair<API_Guid, API_Guid>>& systemItemPairs);

__APIEXPORT GSErrCode 	__ACENV_CALL	ACAPI_Element_GetClassificationItemsDefault		(const API_ElemType&						type,
																						 GS::Array<GS::Pair<API_Guid, API_Guid>>&	systemItemPairs);

__APIEXPORT GSErrCode 	__ACENV_CALL	ACAPI_Attribute_GetClassificationItems (const API_Attr_Head& attrHead, GS::Array<GS::Pair<API_Guid, API_Guid>>& systemItemPairs);


__APIEXPORT GSErrCode 	__ACENV_CALL	ACAPI_Element_GetClassificationInSystem (const API_Guid& elemGuid, const API_Guid& systemGuid, API_ClassificationItem& item);

__APIEXPORT GSErrCode 	__ACENV_CALL	ACAPI_Element_GetClassificationInSystemDefault	(const API_ElemType&		type,
																						 const API_Guid&			systemGuid,
																						 API_ClassificationItem&	item);

__APIEXPORT GSErrCode 	__ACENV_CALL	ACAPI_Attribute_GetClassificationInSystem (const API_Attr_Head& attrHead, const API_Guid& systemGuid, API_ClassificationItem& item);

__APIEXPORT GSErrCode 	__ACENV_CALL	ACAPI_Element_AddClassificationItem		(const API_Guid& elemGuid, const API_Guid& itemGuid);

__APIEXPORT GSErrCode 	__ACENV_CALL	ACAPI_Element_AddClassificationItemDefault	  (const API_ElemType& type, const API_Guid& itemGuid);

__APIEXPORT GSErrCode 	__ACENV_CALL	ACAPI_Attribute_AddClassificationItem (const API_Attr_Head& attrHead, const API_Guid& itemGuid);

__APIEXPORT GSErrCode 	__ACENV_CALL	ACAPI_Element_RemoveClassificationItem	(const API_Guid& elemGuid, const API_Guid& itemGuid);

__APIEXPORT GSErrCode 	__ACENV_CALL	ACAPI_Element_RemoveClassificationItemDefault (const API_ElemType& type, const API_Guid& itemGuid);

__APIEXPORT GSErrCode 	__ACENV_CALL	ACAPI_Attribute_RemoveClassificationItem (const API_Attr_Head& attrHead, const API_Guid& itemGuid);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Element_IsClassificationItemVisible	(const API_Guid&						elemGuid,
																					 const API_Guid&						classificationGuid);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Element_IsClassificationItemVisibleDefault   (const API_ElemType&				type,
																							const API_Guid&					classificationGuid);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Attribute_IsClassificationItemVisible (const API_Attr_Head& attrHead, const API_Guid& classificationGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetElementsWithClassification (const API_Guid&		classificationItemGuid,
																					 GS::Array<API_Guid>&	elemGuids);

/* -- Property related functions ----------------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetPropertyDefinitions		(const API_Guid&							elemGuid,
																					 API_PropertyDefinitionFilter				filter,
																					 GS::Array<API_PropertyDefinition>&			propertyDefinitions);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_GetPropertyDefinitions		(const API_Attr_Head&						attrHead,
																					 API_PropertyDefinitionFilter				filter,
																					 GS::Array<API_PropertyDefinition>&			definitions);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetPropertyValue				(const API_Guid&							elemGuid,
																					 const API_Guid&							propertyDefinitionGuid,
																					 API_Property&								property);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_GetPropertyValue			(const API_Attr_Head&						attrHead,
																					 const API_Guid&							propertyDefinitionGuid,
																					 API_Property&								property);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetPropertyValues				(const API_Guid&							elemGuid,
																					 const GS::Array<API_PropertyDefinition>&	propertyDefinitions,
																					 GS::Array<API_Property>&					properties);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_GetPropertyValues			(const API_Attr_Head&						attrHead,
																					 const GS::Array<API_PropertyDefinition>&	propertyDefinitions,
																					 GS::Array<API_Property>&					properties);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetPropertyValuesByGuid		(const API_Guid&							elemGuid,
																					 const GS::Array<API_Guid>&					propertyDefinitions,
																					 GS::Array<API_Property>&					properties);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_GetPropertyValuesByGuid		(const API_Attr_Head&						attrHead,
																					 const GS::Array<API_Guid>&					propertyDefinitions,
																					 GS::Array<API_Property>&					properties);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SetProperty					(const API_Guid&							elemGuid,
																					 const API_Property&						property);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_SetProperty					(const API_Attr_Head&						attrHead,
																					 const API_Property&						property);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SetProperties					(const API_Guid&							elemGuid,
																					 const GS::Array<API_Property>&				properties);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Attribute_SetProperties				(const API_Attr_Head&						attrHead,
																					 const GS::Array<API_Property>&				properties);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetPropertyDefinitionsOfDefaultElem	(const API_ElemType&				type,
																							 API_PropertyDefinitionFilter		filter,
																							 GS::Array<API_PropertyDefinition>&	definitions);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetPropertyValueOfDefaultElem			(const API_ElemType&				type,
																							 const API_Guid&					propertyDefinitionGuid,
																							 API_Property&						property);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetPropertyValuesOfDefaultElem		(const API_ElemType&						type,
																							 const GS::Array<API_PropertyDefinition>&	propertyDefinitions,
																							 GS::Array<API_Property>&					properties);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetPropertyValuesOfDefaultElemByGuid	(const API_ElemType&				type,
																							 const GS::Array<API_Guid>&			propertyDefinitions,
																							 GS::Array<API_Property>&			properties);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SetPropertyOfDefaultElem				(const API_ElemType&				type,
																							 const API_Property&				property);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_SetPropertiesOfDefaultElem			(const API_ElemType&				type,
																							 const GS::Array<API_Property>&		properties);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Element_IsPropertyDefinitionValueEditable		(const API_Guid&					elemGuid,
																							 const API_Guid&					propertyGuid);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Element_IsPropertyDefinitionValueEditableDefault (const API_ElemType&				type,
																							 	const API_Guid&					propertyGuid);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Attribute_IsPropertyDefinitionValueEditable	(const API_Attr_Head&				attrHead,
																							 const API_Guid&					propertyGuid);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Element_IsPropertyDefinitionAvailable			(const API_Guid&					elemGuid,
																							 const API_Guid&					propertyGuid);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Element_IsPropertyDefinitionAvailableDefault (const API_ElemType&					type,
																							const API_Guid&						propertyGuid);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Attribute_IsPropertyDefinitionAvailable		(const API_Attr_Head&				attrHead,
																							 const API_Guid&					propertyGuid);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Element_IsPropertyDefinitionVisible			(const API_Guid&					elemGuid,
																							 const API_Guid&					propertyGuid);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Element_IsPropertyDefinitionVisibleDefault	(const API_ElemType&				type,
																							 const API_Guid&					propertyGuid);

__APIEXPORT bool		__ACENV_CALL	ACAPI_Attribute_IsPropertyDefinitionVisible			(const API_Attr_Head&				attrHead,
																							 const API_Guid&					propertyGuid);

__APIEXPORT GSErrCode	__ACENV_CALL    ACAPI_Element_GetCollisions (const GS::Array<API_Guid>&					apiGuidSet1,
																	 const GS::Array<API_Guid>&					apiGuidSet2,
																	 GS::Array<GS::Pair<API_CollisionElem, API_CollisionElem>>&	apiResultArray,
																	 const API_CollisionDetectionSettings&		apiColDetSettings);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementList_AddProperty (API_PropertyDefinition& definition, const GS::Array<API_Guid>& elemGuids);

__APIEXPORT GSErrCode   __ACENV_CALL	ACAPI_ElementList_ModifyPropertyValue (const API_Property& property, const GS::Array<API_Guid>& elemGuids);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementList_DeleteProperty (const API_Guid& definitionGuid, const GS::Array<API_Guid>& elemGuids);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AttributeList_AddProperty (API_PropertyDefinition& definition, const GS::Array<API_Attr_Head>& attrHeaders);

__APIEXPORT GSErrCode   __ACENV_CALL	ACAPI_AttributeList_ModifyPropertyValue (const API_Property& property, const GS::Array<API_Attr_Head>& attrHeaders);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AttributeList_DeleteProperty (const API_Guid& definitionGuid, const GS::Array<API_Attr_Head>& attrHeaders);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GrantElements (const GS::Array<API_Guid>& elemGuids, short toUserId);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetComponents (const API_Guid&					elemGuid,
																	 GS::Array<API_ElemComponentID>&	elemComponents);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElemComponent_GetPropertyDefinitions	(const API_ElemComponentID&			elemComponent,
																					 API_PropertyDefinitionFilter		filter,
																					 GS::Array<API_PropertyDefinition>&	propertyDefinitions);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElemComponent_GetPropertyValue		(const API_ElemComponentID& elemComponent,
																					 const API_Guid&			propertyDefinitionGuid,
																					 API_Property&				property);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElemComponent_GetPropertyValues		(const API_ElemComponentID&					elemComponent,
																					 const GS::Array<API_PropertyDefinition>&	propertyDefinitions,
																					 GS::Array<API_Property>&					properties);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElemComponent_GetPropertyValuesByGuid	(const API_ElemComponentID&	elemComponent,
																					 const GS::Array<API_Guid>&	propertyDefinitions,
																					 GS::Array<API_Property>&	properties);

/* -- Element Difference Generator -------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElemDifferenceGenerator_GetState (API_ElemDifferenceGeneratorTypeID	type,
																				API_ElemDifferenceGeneratorState*	diffGeneratorState);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElemDifferenceGenerator_GenerateDifference (API_ElemDifferenceGeneratorTypeID		type,
																						  API_ElemDifferenceGeneratorState*		diffState1,
																						  API_ElemDifferenceGeneratorState*		diffState2,
																						  API_ElemDifference&					difference);


__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetActualOverrideStyle				(const API_Guid&					guid_Element,
																							 API_OverrideStyle&					elemOverrideStyle);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetVisualOverriddenImage (const API_Guid&				elemGuid,
																				API_VisualOverriddenImage	*image);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetNoteAutotexts (const API_ElemType& noteOwnerType,
																		std::unordered_map<API_NoteAutotextID, std::unordered_set<API_ElemType>>& elemTypesForAutotextIDs,
																		const GS::Optional<API_AppearID>& dimAppear = GS::NoValue);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_GetNoteKeywordForAutotextID (API_NoteAutotextID autotextID,
																				   GS::UniString& keyword);


/* -- Markup Management ------------------ */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_MarkUp_Create					(API_MarkUpType&			markUp);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_MarkUp_GetList				(const API_Guid&			elemGuid,
																			 GS::Array<API_MarkUpType>*	markUpList,
																			 bool*						asCorrected = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_MarkUp_Delete					(const API_Guid&			markUpGuid,
																			 bool						acceptAllElements = false);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_MarkUp_AttachElements			(const API_Guid&					markUpGuid,
																			 const GS::Array<API_Guid>&			elemList,
																			 API_MarkUpComponentTypeID			type,
																			 GS::HashTable<API_Guid, API_Guid>*	modificationElemTable = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_MarkUp_DetachElements			(const API_Guid&			markUpGuid,
																			 const GS::Array<API_Guid>&	elemList);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_MarkUp_GetAttachedElements	(const API_Guid&			markUpGuid,
																			 API_MarkUpComponentTypeID	type,
																			 GS::Array<API_Guid>&		attachedElements);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_MarkUp_AddComment				(const API_Guid&			markUpGuid,
																			 API_MarkUpCommentType&		comment);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_MarkUp_GetComments			(const API_Guid&					markUpGuid,
																			 GS::Array<API_MarkUpCommentType>*	commentList);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_MarkUp_ExportToBCF			(const IO::Location&				fileLoc,
																			 const GS::Array<API_Guid>&			markupEntryIds,
																			 const bool							useExternalId = false,
																			 const bool							alignBySurveyPoint = true);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_MarkUp_ImportFromBCF			(const IO::Location&				fileLoc,
																			 const bool							silentMode,
																			 APIIFCRelationshipDataProc*		ifcRelationshipDataProc,
																			 const void*						par1,
																			 const bool							openMarkUpPalette = false,
																			 const bool							alignBySurveyPoint = true);

/* -- Body Editing ------------------------ */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Body_Create			(const Modeler::MeshBody*		body,
																	 const API_OverriddenAttribute*	bodyMaterialMapTable,
																	 void**							bodyData);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Body_Finish			(void*							bodyData,
																	 Modeler::MeshBody**			body,
																	 API_OverriddenAttribute**		bodyMaterialMapTable);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Body_Dispose			(void**					bodyData);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Body_AddVertex		(void*					bodyData,
																	 const API_Coord3D&		coord,
																	 UInt32&				index);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Body_AddEdge			(void*					bodyData,
																	 const UInt32			vertex1,
																	 const UInt32			vertex2,
																	 Int32&					index);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Body_AddPolyNormal	(void*					bodyData,
																	 const API_Vector3D&	normal,
																	 Int32&					index);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Body_AddPolygon		(void*							bodyData,
																	 const GS::Array<Int32>&		edges,
																	 const Int32					polyNormal,
																	 const API_OverriddenAttribute&	material,
																	 UInt32&						index);


/* -- PolyRoof Decomposer ----------------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Element_Decompose	(const API_Guid&					elemGuid,
																 API_ElementDecomposerInterface*	elementDecomposer);

/* -- ElementSet Manager ------------------ */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementSet_Create (GS::Array<API_Guid>	*guids,
																 const API_UserData		*userData,
																 API_Guid				*setGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementSet_Delete (API_Guid setGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementSet_GetData (API_Guid				setGuid,
																  GS::Array<API_Guid>	*elemGuids,
																  API_UserData			*data);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementSet_Identify (API_Guid elemGuid, GS::Array<API_Guid> *setGuids);


/* -- Group Manager ------------------ */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementGroup_Create (const GS::Array<API_Guid>&	elemGuids,
																   API_Guid*					groupGuid = nullptr,
																   const API_Guid*				parentGroupGuid = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementGroup_GetGroup (const API_Guid&		elemGuid,
																     API_Guid*				groupGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementGroup_GetRootGroup (const API_Guid&		elemGuid,
																		 API_Guid*				rootGroupGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementGroup_GetGroupedElems (const API_Guid&		 groupGuid,
																		    GS::Array<API_Guid>* elemGuids);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementGroup_GetAllGroupedElems (const API_Guid&		groupGuid,
																		       GS::Array<API_Guid>*	elemGuids);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementGroup_GetUserData (const API_Guid&		groupGuid,
																		API_UserData*		userData);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ElementGroup_SetUserData (const API_Guid&		groupGuid,
																		const API_UserData*	userData);

/* -- Selection Manager ------------------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Selection_Get (API_SelectionInfo*		selectionInfo,
															 GS::Array<API_Neig>*	selNeigs,
															 bool					onlyEditable,
															 bool					ignorePartialSelection = true,
															 API_SelRelativePosID	relativePosToMarquee = API_InsidePartially);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Selection_SetMarquee (API_SelectionInfo *selectionInfo);


/* -- 3D Manager -------------------------- */

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_3D_GetNum (API_3DTypeID typeID, Int32 *count);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_3D_GetComponent (API_Component3D *component);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_3D_DecomposePgon (Int32 ipgon, Int32 ***cpoly);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_3D_CreateSight (void** newSightPtr);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_3D_SelectSight (void* sight, void** oldSightPtr);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_3D_DeleteSight (void* sight);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_3D_GetCurrentWindowSight (void** sightPtr);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_3D_GetCutPolygonInfo (Int32 									bodyIndex,
																			const API_Plane3D& 						cutPlane,
																			GS::Array<Geometry::MultiPolygon2D>* 	resPolygons = nullptr,
																			double* 								area		= nullptr);

/* -- ListData Manager -------------------- */

__APIEXPORT Int32		__ACENV_CALL	ACAPI_ListData_GetSetNum (void);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ListData_GetSet (API_ListDataSetType *listdataSet);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ListData_GetNum (Int32 setIndex, API_ListDataID typeID, Int32 *count);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ListData_Get (API_ListData *listdata);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ListData_Search (API_ListData *listdata);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ListData_GetLocal (Int32 libIndex, const API_Elem_Head *elemHead, API_ListData *listdata);


/* -- Communication Manager ------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Command_Test	(const API_ModulID*	mdid,
															 GSType				cmdID,
															 Int32				cmdVersion);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Command_Call	(const API_ModulID*	mdid,
															 GSType				cmdID,
															 Int32				cmdVersion,
															 GSHandle			params,
															 GSPtr				resultData,
															 bool				silentMode);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Command_ExternalCall	(const IO::Location*		projectFileLoc,
																	 const API_ModulID*			mdid,
																	 GSType						cmdID,
																	 Int32						cmdVersion,
																	 GSHandle					params,
																	 bool						silentMode,
																	 APIExternalCallBackProc*	externalCallbackProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Command_CallFromEventLoop	(const API_ModulID*			mdid,
																		 GSType						cmdID,
																		 Int32						cmdVersion,
																		 GSHandle					paramsHandle,
																		 bool						silentMode,
																		 APICommandCallBackProc*	callbackProc);

/* -- ModulData Manager ---------------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ModulData_Store (const API_ModulData* info, const GS::UniString& modulName = "");

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ModulData_GetInfo (API_ModulData* info, const GS::UniString& modulName = "");

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ModulData_Get (API_ModulData* info, const GS::UniString& modulName = "");

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ModulData_GetList (GS::Array<GS::UniString>* modulNameList);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ModulData_Delete (const GS::UniString& modulName = "");

/* -- AddOnObject Manager ---------------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_CreateObject (const GS::UniString& objectName, const GSHandle& content, API_Guid* objectGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_CreateUniqueObject (const GS::UniString& objectName, API_Guid* objectGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_CreateUniqueObjectMore (const GS::Array<GS::UniString>& objectNames, GS::Array<API_Guid>& objectGuids);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_CreateClientOnlyObject (const GS::UniString& objectName, const GSHandle& content, API_Guid* objectGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_GetObjectList (GS::Array<API_Guid>* objects);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_GetObjectContent (const API_Guid& objectGuid, GS::UniString* objectName, GSHandle* objectContent);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_ModifyObject (const API_Guid& objectGuid, const GS::UniString* newObjectName, const GSHandle* newObjectContent);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_DeleteObject (const API_Guid& objectGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_GetObjectGuidFromName (const GS::UniString& name, API_Guid* objectGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_GetUniqueObjectGuidFromName (const GS::UniString& name, API_Guid* objectGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_GetClientOnlyObjectGuidFromName (const GS::UniString& name, API_Guid* objectGuid);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_ReserveObjects (const GS::Array<API_Guid>& objectGuids, GS::HashTable<API_Guid, short>* conflicts);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_ReleaseObjects (const GS::Array<API_Guid>& objectGuids);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_RequestObjects (const GS::Array<API_Guid>& objectGuids, const GS::UniString& mailText);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_GrantObjects (const GS::Array<API_Guid>& objectGuids, short toUserId);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_GetTeamworkOwnerId (const API_Guid& objectGuid, short* ownerId);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_ExistsObject (const API_Guid& objectGuid, bool* objectExists);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_AddOnObject_SetUIProperties (const API_Guid* objectGuid, const GS::UniString* name, const GS::UniString& localisedName, short dialogMenuStringId);

/* -- Notification Manager ---------------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_CatchProjectEvent		(GSFlags						eventTypes,
																			 APIProjectEventHandlerProc		*handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_CatchViewEvent			(GSFlags						eventTypes,
																			 API_NavigatorMapID				mapId,
																			 APIViewEventHandlerProc		*handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_CatchToolChange		(APIToolChangeHandlerProc		*handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_CatchSelectionChange	(APISelectionChangeHandlerProc	*handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_CatchChangeDefaults	(const API_ToolBoxItem			*elemType,
																			 APIDefaultsChangeHandlerProc	*handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_CatchNewElement		(const API_ToolBoxItem			*elemType,
																			 APIElementEventHandlerProc		*handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_CatchAttributeReplacement	(APIAttributeReplacementHandlerProc  *handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_InstallElementObserver	(APIElementEventHandlerProc		*handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_GetTranParams			(API_ActTranPars *actTranPars);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_GetParentElement		(API_Element*			element,
																			 API_ElementMemo*		memo,
																			 UInt64					mask,
																			 API_ElementUserData*	userData);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_CatchElementReservationChange	(APIReservationChangeHandlerProc*	handlerProc,
																					 const GS::HashSet<API_Guid>*		filterElementsInterestedOnly = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_CatchLockableReservationChange	(APILockChangeHandlerProc*			handlerProc,
																					 const GS::HashSet<API_Guid>*		filterLockablesInterestedOnly = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_CatchLicenseBorrowStatusChange	(APILicenseBorrowStatusChangeHandlerProc*	handlerProc);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_ClassificationVisibilityChanged ();

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_PropertyVisibilityChanged ();

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_RegisterEventHandler (GS::Owner<API_IEventHandler> eventHandler, API_Guid& id);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Notify_UnregisterEventHandler (const API_Guid& id);


/* -- Miscellaneous ----------------------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_ActivatePropertyObjectHandler (short strResID, bool active);


/* --- Favorite Functions	--------------- */

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Favorite_Get (API_Favorite* favorite);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Favorite_Create (const API_Favorite& favorite);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Favorite_Change (const API_Favorite& favorite,
															   const API_Element*  elementMask = nullptr,
															   const UInt64		   memoMask = 0);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Favorite_Rename (const GS::UniString& oldName, const GS::UniString& newName);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Favorite_Delete (const GS::UniString& name);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Favorite_GetNum (const API_ElemType&						type,
															   short									*count,
															   GS::Array<API_FavoriteFolderHierarchy>	*folders,
															   GS::Array<GS::UniString>					*names);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Favorite_GetPreviewImage (const GS::UniString&	 name,
																		API_ImageViewID			 viewType,
																		NewDisplay::NativeImage* nativeImagePtr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Favorite_Import (const IO::Location&							location,
															   const API_FavoriteFolderHierarchy&			targetFolder,
															   bool											importFolders,
															   API_FavoriteNameConflictResolutionPolicy		conflictPolicy,
															   GS::UniString								*firstConflictName = nullptr);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Favorite_Read	  (const IO::Location&		location,
															   GS::Array<API_Favorite>*	favorites);

__APIEXPORT GSErrCode	__ACENV_CALL	ACAPI_Favorite_Export (const IO::Location&				location,
															   const GS::Array<GS::UniString>	*names = nullptr);


/* -- Teamwork Control -------------------- */

__APIEXPORT bool				__ACENV_CALL	ACAPI_TeamworkControl_HasConnection (void);

__APIEXPORT bool				__ACENV_CALL	ACAPI_TeamworkControl_IsOnline (void);

__APIEXPORT bool				__ACENV_CALL	ACAPI_TeamworkControl_IsServerLibPart (const IO::Location& location);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_TeamworkControl_GetTeamworkProjectDetails (const IO::Location&	twProjectLocation,
																								 GS::UniString*			serverUrl = nullptr,
																								 GS::UniString*			projectName = nullptr,
																								 GS::UniString*			userName = nullptr);

__APIEXPORT bool				__ACENV_CALL	ACAPI_TeamworkControl_HasCreateRight (const API_Guid& objectId);

__APIEXPORT bool				__ACENV_CALL	ACAPI_TeamworkControl_HasDeleteModifyRight (const API_Guid& objectId);

__APIEXPORT API_LockableStatus	__ACENV_CALL	ACAPI_TeamworkControl_GetLockableStatus (const API_Guid&				objectId,
																						 GS::PagedArray<short>*			conflicts = nullptr);

__APIEXPORT API_Guid			__ACENV_CALL	ACAPI_TeamworkControl_FindLockableObjectSet (const GS::UniString&		objectSetName);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_TeamworkControl_ReserveLockable (const API_Guid&					objectId,
																					   GS::PagedArray<short>*			conflicts = nullptr,
																					   bool								enableDialogs = true);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_TeamworkControl_ReleaseLockable (const API_Guid&					objectId,
																					   bool								enableDialogs = true);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_TeamworkControl_ReserveElements (const GS::Array<API_Guid>&		elements,
																					   GS::HashTable<API_Guid, short>*	conflicts = nullptr,
																					   bool								enableDialogs = true);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_TeamworkControl_ReleaseElements (const GS::Array<API_Guid>&		elements,
																					   bool								enableDialogs = true);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_TeamworkControl_ReserveHotlinkCacheManagement (short* conflict = nullptr);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_TeamworkControl_ReleaseHotlinkCacheManagement (void);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_TeamworkControl_GetHotlinkCacheManagementOwner (short* owner);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_TeamworkControl_GetUsernameFromId (short userId, GS::UniString* username);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_TeamworkControl_SendChanges (const GS::UniString&	comment = "");

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_TeamworkControl_ReceiveChanges ();

/* -- Properties -------------------- */

__APIEXPORT GSErrCode			__ACENV_CALL    ACAPI_Property_GetPropertyGroups			(GS::Array<API_PropertyGroup>& groups);

__APIEXPORT GSErrCode			__ACENV_CALL 	ACAPI_Property_GetPropertyDefinitions		(const API_Guid& groupGuid, GS::Array<API_PropertyDefinition>&	definitions);

__APIEXPORT GSErrCode			__ACENV_CALL 	ACAPI_Property_GetPropertyGroup				(API_PropertyGroup& group);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_Property_GetPropertyDefinition		(API_PropertyDefinition& definition);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_Property_CreatePropertyGroup			(API_PropertyGroup& group);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_Property_CreatePropertyDefinition		(API_PropertyDefinition& definition);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_Property_ChangePropertyGroup			(const API_PropertyGroup& group);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_Property_ChangePropertyDefinition		(const API_PropertyDefinition& definition);

__APIEXPORT bool				__ACENV_CALL	ACAPI_Property_IsValidValue					(const API_PropertyValue& value, const API_PropertyDefinition& definition);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_Property_DeletePropertyGroup			(const API_Guid& groupGuid);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_Property_DeletePropertyDefinition		(const API_Guid& propertyGuid);

__APIEXPORT GSErrCode 			__ACENV_CALL	ACAPI_Property_Import						(const GS::UniString&									propertyXML,
																							 API_PropertyDefinitionNameConflictResolutionPolicy		conflictPolicy);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_Property_GetPropertyValueString		(const API_Property&	property,
																							 GS::UniString*			displayString);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_Property_SetPropertyValueFromString	(const GS::UniString&							propertyValueString,
																							 const API_PropertyConversionUtilsInterface&	conversionUtils,
																							 API_Property*									property);

/* -- Classifications -------------------- */

__APIEXPORT GSErrCode			__ACENV_CALL    ACAPI_Classification_GetClassificationSystems			(GS::Array<API_ClassificationSystem>& systems);

__APIEXPORT GSErrCode			__ACENV_CALL    ACAPI_Classification_GetClassificationItem				(API_ClassificationItem& item);

__APIEXPORT GSErrCode			__ACENV_CALL    ACAPI_Classification_GetClassificationItemParent		(const API_Guid& itemGuid, API_ClassificationItem& parent);

__APIEXPORT GSErrCode			__ACENV_CALL    ACAPI_Classification_GetClassificationItemChildren		(const API_Guid& itemGuid, GS::Array<API_ClassificationItem>& children);

__APIEXPORT GSErrCode			__ACENV_CALL    ACAPI_Classification_GetClassificationItemSystem		(const API_Guid& itemGuid, API_ClassificationSystem& system);

__APIEXPORT GSErrCode 			__ACENV_CALL	ACAPI_Classification_GetClassificationSystem			(API_ClassificationSystem& system);

__APIEXPORT GSErrCode 			__ACENV_CALL	ACAPI_Classification_GetClassificationSystemRootItems	(const API_Guid& systemGuid, GS::Array<API_ClassificationItem>& items);

__APIEXPORT GSErrCode 			__ACENV_CALL	ACAPI_Classification_CreateClassificationItem			(API_ClassificationItem&	item,
																										 const API_Guid&			systemGuid,
																										 const API_Guid&			parentItemGuid,
																										 const API_Guid&			nextItemGuid);

__APIEXPORT GSErrCode 			__ACENV_CALL	ACAPI_Classification_CreateClassificationSystem			(API_ClassificationSystem& system);


__APIEXPORT GSErrCode 			__ACENV_CALL	ACAPI_Classification_ChangeClassificationItem			(const API_ClassificationItem& item);

__APIEXPORT GSErrCode 			__ACENV_CALL	ACAPI_Classification_ChangeClassificationSystem			(const API_ClassificationSystem& system);

__APIEXPORT GSErrCode 			__ACENV_CALL	ACAPI_Classification_DeleteClassificationItem			(const API_Guid& itemGuid);

__APIEXPORT GSErrCode 			__ACENV_CALL	ACAPI_Classification_DeleteClassificationSystem			(const API_Guid& systemGuid);

__APIEXPORT GSErrCode 			__ACENV_CALL	ACAPI_Classification_Import								(const GS::UniString&									classificationXML,
																										 API_ClassificationSystemNameConflictResolutionPolicy	systemConflictPolicy,
																										 API_ClassificationItemNameConflictResolutionPolicy		itemConflictPolicy);


/* -- Action Center -------------------- */

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_ActionCenter_Check (API_ActionCenterItemID item);


/* -- IFC ------------------------------ */

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_IFC_IFCGuidToAPIGuid (const GS::UniString& ifcGuid, API_Guid& apiGuid);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_IFC_APIGuidToIFCGuid (const API_Guid& apiGuid, GS::UniString& ifcGuid);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_IFC_GetIFCRelationshipData (const API_IFCTranslatorIdentifier& ifcTranslatorIdentifier, API_IFCRelationshipData& ifcRelationshipData);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_IFC_GetIFCExportTranslatorsList (GS::Array<API_IFCTranslatorIdentifier>& ifcExportTranslators);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_IFC_GetIFCDifferenceState (const API_Guid&					viewGuid,
																				 const API_IFCTranslatorIdentifier&	ifcTranslatorIdentifier,
																				 API_IFCDifferenceGeneratorState&	ifcDifferenceGeneratorState);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_IFC_GetIFCDifference (const API_IFCDifferenceGeneratorState&	previousIFCDifferenceGeneratorState,
																			const API_IFCDifferenceGeneratorState&	currentIFCDifferenceGeneratorState,
																			API_IFCDifference&						ifcDifference);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_IFC_ComplementIFCDifferenceAndMergeIFCRelationshipData (const API_IFCRelationshipData&	olderIfcRelationshipData,
																	   										  const API_IFCRelationshipData&	newerIfcRelationshipData,
																	   										  API_IFCDifference&				ifcDifference,
																	   										  API_IFCRelationshipData&			mergedIfcRelationshipData);

__APIEXPORT GSErrCode			__ACENV_CALL	ACAPI_IFC_InvokeIFCDifferenceExportSettingsDlg (API_Guid& selectedViewGuid, API_IFCTranslatorIdentifier& selectedIFCTranslator);


/* -- Protection ----------------------- */

__APIEXPORT UInt32			__ACENV_CALL	ACAPI_Protection_GetProtectionMode ();
__APIEXPORT UInt32          __ACENV_CALL	ACAPI_Protection_GetSerialNumber ();
__APIEXPORT UInt16          __ACENV_CALL	ACAPI_Protection_GetBoxMask ();
__APIEXPORT GS::UniString   __ACENV_CALL	ACAPI_Protection_GetConfigurationNumber ();
__APIEXPORT UInt32          __ACENV_CALL	ACAPI_Protection_GetNumberOfLicenses ();
__APIEXPORT GSTime          __ACENV_CALL	ACAPI_Protection_GetExpirationTime ();
__APIEXPORT GS::UniString   __ACENV_CALL	ACAPI_Protection_GetPartnerId ();
__APIEXPORT bool            __ACENV_CALL	ACAPI_Protection_IsSSALevelAtLeast (API_SSALevel requiredLevel);


/* --> ] */
#endif


// ---------------------------------------------------------------------------------------------------------------------

#if defined (_MSC_VER)
	#pragma pack(pop)
#endif

#endif
