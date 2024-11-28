// *********************************************************************************************************************
// API definitions - automation functions
//
// Module:			API
// Namespace:		-
// Contact person:	archicadapi@graphisoft.com
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_AUTOMATION_H)
#define	APIDEFS_AUTOMATION_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "APIdefs_Base.h"
#include "APIdefs_Attributes.h"
#include "APIdefs_Elements.h"

namespace IO { class Location; }


// --- Compiler settings -----------------------------------------------------------------------------------------------


// --- Type definitions	------------------------------------------------------------------------------------------------


// =============================================================================
// Function codes and parameter descriptions
//
// =============================================================================

typedef enum {			// Codes for Automate functions
	APIDo_NewProjectID				= 'NEWP',					// par1: API_NewProjectPars*					par2: ---
	APIDo_OpenID					= 'OPEN',					// par1: API_FileOpenPars*						par2: ---
	APIDo_CloseID					= 'CLOS',					// par1: ---									par2: ---
	APIDo_SaveID					= 'SAVE',					// par1: [API_FileSavePars*]					par2: [API_SavePars_...*]
	APIDo_ReloadLibrariesID 		= 'RLIB',					// par1: ---									par2: ---
	APIDo_PrintID					= 'PRNT',					// par1: API_PrintPars*							par2: ---
	APIDo_QuitID					= 'QUIT',					// par1: ---									par2: ---

	APIDo_RedrawID					= 'RDRW',					// par1: ---									par2: ---
	APIDo_RebuildID					= 'RBLD',					// par1: [bool*]								par2: ---
	APIDo_ZoomID					= 'ZOOM',					// par1: [API_Box*]								par2: [API_Rect*]					par3: [API_Tranmat*]
	APIDo_ZoomToSelectedID			= 'DOOM',					// par1: ---									par2: ---
	APIDo_ZoomToElementsID			= 'ZTEL',					// par1: const GS::Array<API_Guid>*				par2: ---

	APIDo_ChangeWindowID			= 'CHWD',					// par1: API_WindowInfo*						par2: ---
	APIDo_GoToViewID				= 'GOVW',					// par1: const char*							par2: ---

	APIDo_PhotoRenderID				= 'REND',					// par1: API_PhotoRenderPars*					par2: [API_PrintPars*]
	APIDo_SaveAsModuleFileID		= 'SMOD',					// par1: IO::Location*							par2: [API_Elem_Head**]

	APIDo_PublishID					= 'PUBL',					// par1: API_PublishPars						par2: [GS::Array<API_Guid>*] (selected links)

	APIDo_OpenLibraryPartID			= 'OPLP'					// par1: API_OpenLibPartInfo					par2: ---
} API_AutomateID;


// =============================================================================
// New command
//
// =============================================================================

/**
 * @brief Parameters to open a new project.
 * @struct API_NewProjectPars
 * @ingroup ProjectOperation
 * @remarks For the utilization of this structure, see the @ref ACAPI_ProjectOperation_NewProject automation function.
 */
struct API_NewProjectPars {

/**
 * @brief Performs New and Reset or just a simple New command
 * @var newAndReset
 */
	bool							newAndReset;

/**
 * @brief Show the "Save the current document before closing" alert or automatically save it before closing.
 * @var enableSaveAlert
 */
	bool							enableSaveAlert;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	char							filler_1[6];

};


// =============================================================================
// Open command
//
// =============================================================================

/**
 * @brief Available file format identifiers for automated functions.
 * @enum API_FTypeID
 * @ingroup ProjectOperation
 * @since Archicad 25
 * @remarks For the utilization of this structure see the @ref ACAPI_ProjectOperation_Open and @ref ACAPI_ProjectOperation_Save automation functions.
 */
typedef enum {
	APIFType_None,												// unknown file type

		// plan files
	APIFType_PlanFile,											// ARCHICAD Solo Project File
	APIFType_A_PlanFile,										// ARCHICAD Archive File
	APIFType_Bak_PlanFile,										// ARCHICAD Backup File

	APIFType_PlanFile600,										// ARCHICAD 6.0 Plan File
	APIFType_A_PlanFile600,										// ARCHICAD 6.0 Archive File
	APIFType_PlanFile650,										// ARCHICAD 6.5 Plan File
	APIFType_A_PlanFile650,										// ARCHICAD 6.5 Archive File
	APIFType_PlanFile700,										// ARCHICAD 7.0 Plan File
	APIFType_A_PlanFile700,										// ARCHICAD 7.0 Archive File

		// other internal types
	APIFType_TabListFile,										// ARCHICAD List File with Tabs
	APIFType_ObjectFile,										// ARCHICAD Object File
	APIFType_DoorFile,											// ARCHICAD Door File
	APIFType_WindowFile,										// ARCHICAD Window File
	APIFType_GDLFile,											// ARCHICAD GDL File
	APIFType_2DLinesFile,										// 2D Lines File

		// picture files
	APIFType_PNGFile,											// PNG File
	APIFType_BMPFile,											// Bitmap File
	APIFType_TIFFFile,											// TIFF File
	APIFType_JPEGFile,											// JPEG File
	APIFType_GIFFile,											// GIF File

		// other external types
	APIFType_EMFFile,											// Windows Enhanced Metafile
	APIFType_WMFFile,											// Windows Metafile

		// new file types
	APIFType_PlanFile800,										// ARCHICAD 8.0 Plan File
	APIFType_A_PlanFile800,										// ARCHICAD 8.0 Archive File

	APIFType_PlanFile810,										// ARCHICAD 8.1 Plan File
	APIFType_A_PlanFile810,										// ARCHICAD 8.1 Archive File

	APIFType_PlanFile900,										// ARCHICAD 9.0 Plan File
	APIFType_A_PlanFile900,										// ARCHICAD 9.0 Archive File

	APIFType_PlanFile1000,										// ARCHICAD 10.0 Plan File
	APIFType_A_PlanFile1000,									// ARCHICAD 10.0 Archive File

	APIFType_PlanFile1100,										// ARCHICAD 11.0 Plan File
	APIFType_A_PlanFile1100,									// ARCHICAD 11.0 Archive File

	APIFType_PlanFile1200,										// ARCHICAD 12.0 Plan File
	APIFType_A_PlanFile1200,									// ARCHICAD 12.0 Archive File

	APIFType_IfcFile,											// Ifc file -- save only

	APIFType_PlanFile1300,										// ARCHICAD 13.0 Plan File
	APIFType_A_PlanFile1300,									// ARCHICAD 13.0 Archive File

	APIFType_PlanFile1400,										// ARCHICAD 14.0 Plan File
	APIFType_A_PlanFile1400,									// ARCHICAD 14.0 Archive File

	APIFType_PlanFile1500,										// ARCHICAD 15.0 Plan File
	APIFType_A_PlanFile1500,									// ARCHICAD 15.0 Archive File

	APIFType_PlanFile1600,										// ARCHICAD 16.0 Plan File
	APIFType_A_PlanFile1600,									// ARCHICAD 16.0 Archive File

	APIFType_PlanFile1700,										// ARCHICAD 17.0 Plan File
	APIFType_A_PlanFile1700,									// ARCHICAD 17.0 Archive File

	APIFType_PlanFile1800,										// ARCHICAD 18.0 Plan File
	APIFType_A_PlanFile1800,									// ARCHICAD 18.0 Archive File

	APIFType_PdfFile,											// PDF file

	APIFType_PlanFile1900,										// ARCHICAD 19.0 Plan File
	APIFType_A_PlanFile1900,									// ARCHICAD 19.0 Archive File

	APIFType_PlanFile2000,										// ARCHICAD 20.0 Plan File
	APIFType_A_PlanFile2000,									// ARCHICAD 20.0 Archive File

	APIFType_PlanFile2100,										// ARCHICAD 21.0 Plan File
	APIFType_A_PlanFile2100,									// ARCHICAD 21.0 Archive File

	APIFType_PlanFile2200,										// ARCHICAD 22.0 Plan File
	APIFType_A_PlanFile2200,									// ARCHICAD 22.0 Archive File

	APIFType_PlanFile2300,										// ARCHICAD 23.0 Plan File
	APIFType_A_PlanFile2300,									// ARCHICAD 23.0 Archive File

	APIFType_PlanFile2400,										// ARCHICAD 24.0 Plan File
	APIFType_A_PlanFile2400,									// ARCHICAD 24.0 Archive File

	APIFType_PlanFile2500,										// ARCHICAD 25.0 Plan File
	APIFType_A_PlanFile2500,									// ARCHICAD 25.0 Archive File

	APIFType_PlanFile2600,										// ARCHICAD 26.0 Plan File
	APIFType_A_PlanFile2600,									// ARCHICAD 26.0 Archive File

	APIFType_PlanFile2700,										// ARCHICAD 27.0 Plan File
	APIFType_A_PlanFile2700,									// ARCHICAD 27.0 Archive File		// OpenSaveasOLDVersion

	APIFType_SafFile											// SAF file


} API_FTypeID;


/**
 * @brief Parameters to open a new project file.
 * @struct API_FileOpenPars
 * @ingroup ProjectOperation
 * @remarks For the utilization of this structure, see the @ref ACAPI_ProjectOperation_Open automation function.
 */
struct API_FileOpenPars {

/**
 * @brief file format to open
 * @var fileTypeID
 */
	API_FTypeID						fileTypeID;

/**
 * @brief @c archiveLibSpec is passed or not
 * @var libGiven
 */
	bool							libGiven;

/**
 * @brief try to load the libraries specified in the project file. If the stored paths do not exist, the Library Manager dialog appears. In the Archive project file, the folder chooser dialog appears for selecting the appropriate library folder. This field is ignored if @c libGiven is @c true.
 * @var useStoredLib
 */
	bool							useStoredLib;

/**
 * @brief Show the "Save the current document before closing" alert or automatically save it before closing.
 * @var enableSaveAlert
 */
	bool							enableSaveAlert;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief specification of the target file to open
 * @var file
 */
	IO::Location					*file;

/**
 * @brief library folder to create if archive open (optional), @c nullptr otherwise
 * @var archiveLib
 */
	IO::Location					*archiveLib;

};


// =============================================================================
// SaveAs command
//
// =============================================================================

/**
 * @brief Parameters to save the current project as archive file.
 * @struct API_SavePars_Archive
 * @ingroup ProjectOperation
 * @remarks: To utilize this structure, see the @ref ACAPI_ProjectOperation_Save automation function.
 */
struct API_SavePars_Archive {

/**
 * @brief Save pict/bmp files for readable on both (Mac/Win) platforms
 * @var picturesInTIFF
 */
	bool							picturesInTIFF;

/**
 * @brief Include linked Textures while saving the archive
 * @var texturesOn
 */
	bool							texturesOn;

/**
 * @brief Include Background Picture while saving archive
 * @var backgroundPictOn
 */
	bool							backgroundPictOn;

/**
 * @brief Include All Properties Library Parts while saving the archive
 * @var propertiesOn
 */
	bool							propertiesOn;

/**
 * @brief Include Full Library while saving the archive
 * @var libraryPartsOn
 */
	bool							libraryPartsOn;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	bool							filler_3;

/**
 * @brief Reserved for later use.
 * @var filler_4
 */
	Int32							filler_4[8];

};


/**
 * @brief Contains the different options for saving a plan dump from Archicad.
 * @struct API_SavePars_PlanDump
 * @ingroup ProjectOperation
 * @remarks These options correspond to the different settings in the File/Save dialogs.
 */
struct API_SavePars_PlanDump {

/**
 * @brief Include all elements in the plan dump file.
 * @var elementsOn
 */
	bool							elementsOn;

/**
 * @brief Include all attributes in the plan dump file.
 * @var attributesOn
 */
	bool							attributesOn;

/**
 * @brief Include properties in the plan dump file.
 * @var propertiesOn
 */
	bool							propertiesOn;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[9];

};


/**
 * @brief Represents the type of the Archicad object to be saved.
 * @enum API_ConvModID
 * @ingroup ProjectOperation
 * @remarks These options correspond to the formats you can choose while saving something as an Archicad object, both from the plan and the 3D window.
 */
typedef enum {
	APIConvMod_TextGDL,											// write GDL Text in file
	APIConvMod_MemGDL,											// convert into 3D model
	APIConvMod_SymTxtGDL,										// write as GDL Text in symbol file
	APIConvMod_SymBinGDL,										// write as BINARY in symbol file
	APIConvMod_SideGDL,											// convert to side view
	APIConvMod_DragGDL											// create GDL script to drag-and-drop

} API_ConvModID;

/**
 * @brief Contains the different options for saving an Archicad object, lamp, door, or window.
 * @struct API_SavePars_Object
 * @ingroup ProjectOperation
 * @remarks If you want to save the plan view of an element or the selected elements (this is controlled by
 * 			the `saveSelOnly` field), then set view2D to `true`. In this case, the type of the file (`fileTypeID` in
 * @ref API_FileSavePars should be set to `APIFType_ObjectFile`.
 * 		When you want to save the 3D view, then clear the `view2D` field. In this case the `fileTypeID` can be
 * 		`@ref APIFType_ObjectFile`, `APIFType_DoorFile`, or `APIFType_WindowFile`. The `libItMode` field controls whether the
 * 		file should become an editable text or a non-editable binary file. The `removeLine` field effects only objects
 * 		saved from the 3D view.
 */
struct API_SavePars_Object {

/**
 * @brief: The place to put the GDL text/binary information (only when saving from the 3D view). Can be either @c API_ConvMod_SymTxtGDL or @c API_ConvMod_SymBinGDL.
 * @var libItMode
 */
	API_ConvModID					libItMode;

/**
 * @brief Remove redundant lines (only when saving from the 3D view).
 * @var removeLine
 */
	bool							removeLine;

/**
 * @brief Save selection only when the file type is object file (only when saving from a 2D view).
 * @var saveSelOnly
 */
	bool							saveSelOnly;

/**
 * @brief Save 2D or 3D view (when the file type is object file).
 * @var view2D
 */
	bool							view2D;

/**
 * @brief The saved library part is placeable.
 * @var isPlaceable
 */
	bool							isPlaceable;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[8];

};


/**
 * @brief Contains the different options for saving pictures from Archicad.
 * @struct API_SavePars_Picture
 * @ingroup ProjectOperation
 * @remarks These options correspond to the different settings in the File/Save dialogs.
 */
struct API_SavePars_Picture {

/**
 * @brief The bit depth of the picture (see @c API_ColorDepthID).
 * @var colorDepth
 */
	API_ColorDepthID				colorDepth;

/**
 * @brief dithered picture (if less than or equal to 256 colors or grays)
 * @var dithered
 */
	bool							dithered;

/**
 * @brief Save 2D or 3D view.
 * @var view2D
 */
	bool							view2D;

/**
 * @brief Save the picture with cropping to the current zoom (2D only).
 * @var crop
 */
	bool							crop;

/**
 * @brief Save the picture with keeping the selection on.
 * @var keepSelectionHighlight
 */
	bool							keepSelectionHighlight;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[8];

};


/**
 * @brief Defines type of file format for IFC Export.
 * @enum API_IfcTypeID
 * @ingroup ProjectOperation
 * @since Archicad 26
 * @remarks This structure is used only by @ref API_SavePars_Ifc.
 */
typedef enum {
	API_IFC,													// write IFC file
	API_IFCZIP													// write IFC ZIP file

} API_IfcTypeID;


/**
 * @brief Selected elements for IFC export.
 * @enum API_ElementsToIfcExportID
 * @ingroup ProjectOperation
 * @remarks This type specifies in @ref API_SavePars_Ifc.
 */
typedef enum {
	API_EntireProject = 1,
	API_VisibleElementsOnAllStories,
	API_AllElementsOnCurrentStorey,
	API_VisibleElementsOnCurrentStorey,
	API_SelectedElementsOnly,
	API_FilteredElements

} API_ElementsToIfcExportID;


/**
 * @brief IFC Translator Identifier.
 * @struct API_IFCTranslatorIdentifier
 * @ingroup ProjectOperation
 * @since Archicad 26
 * @remarks This structure is used in @ref ACAPI_IFC_GetIFCExportTranslatorsList.
 */
struct API_IFCTranslatorIdentifier {

/**
 * @brief Internal reference.
 * @var innerReference
 */
	GSHandle		innerReference;

/**
 * @brief IFC Translator name.
 * @var name
 */
	GS::UniString	name;

	API_IFCTranslatorIdentifier ():
		innerReference (nullptr),
		name ("")
	{
	}

/**
 * @brief Copy constructor.
 * @param that The other API_IFCTranslatorIdentifier object.
 */
	API_IFCTranslatorIdentifier (const API_IFCTranslatorIdentifier& that):
		innerReference (nullptr),
		name (that.name)
	{
		BMHandleToHandle (that.innerReference, &innerReference);
	}

/**
 * @brief Move constructor.
 * @param that The other API_IFCTranslatorIdentifier object.
 */
	API_IFCTranslatorIdentifier (API_IFCTranslatorIdentifier&& that):
		API_IFCTranslatorIdentifier ()
	{
		Swap (that);
	}

	~API_IFCTranslatorIdentifier ()
	{
		BMKillHandle (&innerReference);
	}

/**
 * @brief Assignment operator.
 * @param other Another object to use as the source.
 * @return Returns with *this.
 */
	API_IFCTranslatorIdentifier&		operator=(API_IFCTranslatorIdentifier other)
	{
		Swap (other);
		return *this;
	}

/**
 * @brief Swap the object with the parameter.
 * @param other The parameter to be swapped.
 */
	void	Swap (API_IFCTranslatorIdentifier& other)
	{
		std::swap (innerReference, other.innerReference);
		name.Swap (other.name);
	}

/**
 * @brief Swap the first and second parameters.
 * @param left The first parameter to be swapped.
 * @param right The second parameter to be swapped.
 */
	friend void		Swap (API_IFCTranslatorIdentifier& left, API_IFCTranslatorIdentifier& right)
	{
		left.Swap (right);
	}

};


/**
 * @brief Contains IFC Entity relations which are specific for the IFC. The IFC Entities are represented by their GlobalId.
 * @struct API_IFCRelationshipData
 * @ingroup IFC
 * @remarks This structure is used in @ref ACAPI_ProjectOperation_Save.
 * 			The IFC containment tree (containmentTable) is in "child ->parent" format. Example: IfcBuilding ->IfcProject IfcSite ->IfcBuilding IfcBuildingStorey ->IfcBuilding IfcWall ->IfcBuildingStorey IfcBuildingElementPart ->IfcWall.
 * 			The IFC assignmentTable set (assignmentTable) is in "child ->parent" format. Example: IfcWall ->IfcRelAssignsToGroup IfcRelAssignsToGroup ->IfcGroup.
 * 			The IFC Type Products (typeProductTable) is in "child ->parent" format. Example: IfcWall ->IfcWallType.
 */
struct API_IFCRelationshipData {

	/**
	 * @brief IFC containment tree in "child->parent" format.
	 * @var containmentTable
	 */
	GS::HashTable<GS::UniString, GS::UniString>			containmentTable;

	/**
	 * @brief Relationships between openings (Doors/Windows/Skylights) and IfcOpeningElements (voids).
	 * @var relFillsTable
	 */
	GS::HashTable<GS::UniString, GS::UniString>			relFillsTable;

	/**
	 * @brief Relationships between IfcOpeningElements (voids) and their parent IfcWall or IfcSlab.
	 * @var relVoidsTable
	 */
	GS::HashTable<GS::UniString, GS::UniString>			relVoidsTable;

	/**
	 * @brief IFC Assigment links, IfcGroup, IfcZone, IfcSystem, IfcRelAssignsToGroup and IfcRelServicesBuildings.
	 * @var assignmentTable
	 */
	GS::HashSet<GS::Pair<GS::UniString, GS::UniString>>	assignmentTable;

	/**
	 * @brief IFC Type Products tree.
	 * @var typeProductTable
	 */
	GS::HashTable<GS::UniString, GS::UniString>			typeProductTable;

};



/**
 * @brief Parameters to save the current project as an Ifc file.
 * @struct API_SavePars_Ifc
 * @ingroup ProjectOperation
 * @since Archicad 26
 * @remarks You'll have to pass this structure to the @ref ACAPI_ProjectOperation_Save function.
 */
struct API_SavePars_Ifc {

/**
 * @brief Defines whether to save IFC or IFC ZIP format.
 * @var subType
 */
	API_IfcTypeID					subType;

/**
 * @brief Define the translator identifier, for IFC save.
 * @var translatorIdentifier
 */
	API_IFCTranslatorIdentifier		translatorIdentifier;

/**
 * @brief Define type of elements which will be exported.
 * @var elementsToIfcExport
 */
	API_ElementsToIfcExportID		elementsToIfcExport;

/**
 * @brief Define the elements set (which elements will be saved into the file) or leave nullptr to save all elements.
 * @var elementsSet
 */
	const GS::Array<API_Guid>*		elementsSet;

/**
 * @brief Defines whether to calculate and save the corresponding IfcBoundingBox.
 * @var includeBoundingBoxGeometry
 */
	bool							includeBoundingBoxGeometry;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	void*							filler_1;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	void*							filler_2;

};


/**
 * @brief Contains the different page options for saving to pdf file.
 * @struct API_SavePars_Pdf
 * @ingroup ProjectOperation
 * @remarks If you want to save the content of a window, the type of the file fileTypeID in @ref API_FileSavePars should be set to @c APIFType_PdfFile. In case of 3D and Master Layout Archicad will export the floor plan.
 */
struct API_SavePars_Pdf {

/**
 * @brief The size of the left margin of the page in mms.
 * @var leftMargin
 */
	float							leftMargin;

/**
 * @brief The size of the top margin of the page in mms.
 * @var topMargin
 */
	float							topMargin;

/**
 * @brief The size of the right margin of the page in mms.
 * @var rightMargin
 */
	float							rightMargin;

/**
 * @brief The size of the bottom margin of the page in mms.
 * @var bottomMargin
 */
	float							bottomMargin;

/**
 * @brief The horizontal size of the page in mms.
 * @var sizeX
 */
	float							sizeX;

/**
 * @brief The vertical size of the page in mms.
 * @var sizeY
 */
	float							sizeY;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[4];

};


/**
 * @brief Selected elements for SAF export.
 * @enum API_ElementsToSAFExportID
 * @ingroup ProjectOperation
 * @since Archicad 25
 * @remarks This type specifies in @c API_SavePars_Saf.
 */
typedef enum {
	API_SAFSelectedElementsOnly = 1,
	API_SAFEntireProject,
	API_SAFVisibleElements

} API_ElementsToSAFExportID;


/**
 * @brief Contains the export filter type for the SAF file.
 * @struct API_SavePars_Saf
 * @ingroup ProjectOperation
 * @since Archicad 26
 * @remarks If you want to save the content of a window, the type of the file fileTypeID in @ref API_FileSavePars should be set to @c APIFType_SafFile. In case of 3D and Master Layout Archicad will export the floor plan.
 */
struct API_SavePars_Saf {

/**
 * @brief Type of export filter for the SAF Export. It affects the elements to be exported: whether the whole project, only visible elements or only selected elements are exported.
 * @var elementsToSAFExport
 */
	API_ElementsToSAFExportID		elementsToSAFExport;

/**
 * @brief Name of SAF Translator used for the SAF Export. It is one of the names listed on the SAF Translators dialog. It affects the profiles and materials of elements, output version, etc.
 * @var selectedSAFTranslatorName
 */
	GS::UniString					selectedSAFTranslatorName;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1[3];

};


/**
 * @brief Parameters to save the current project file.
 * @struct API_FileSavePars
 * @ingroup ProjectOperation
 * @remarks: To utilize this structure, see the @ref ACAPI_ProjectOperation_Save automation function.
 */
struct API_FileSavePars {

/**
 * @brief The output format
 * @var fileTypeID
 */
	API_FTypeID						fileTypeID;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief The specification of the target file
 * @var file
 */
	IO::Location					*file;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	Int32							filler_2[15];

};

// =============================================================================
// Print command
//
// =============================================================================

#define	PrintArea_CurrentView		0
#define	PrintArea_EntireDrawing		1
#define	PrintArea_Marquee			2

/**
 * @brief Printing header/footer parameters.
 * @struct API_PrintStampType
 * @ingroup ProjectOperation
 * @remarks To utilize this structure, see the @ref API_PrintPars structure.
 */
struct API_PrintStampType {

/**
 * @brief Add project's name to stamp
 * @var addProjectName
 */
	bool							addProjectName;

/**
 * @brief Add project's path to stamp
 * @var addProjectPath
 */
	bool							addProjectPath;

/**
 * @brief Add view's name to stamp
 * @var addViewName
 */
	bool							addViewName;

/**
 * @brief Add layer combination to stamp
 * @var addLayerComb
 */
	bool							addLayerComb;

/**
 * @brief Add display options combination to stamp
 * @var addDispOptComb
 */
	bool							addDispOptComb;

/**
 * @brief Add scale value to stamp
 * @var addPrintingScale
 */
	bool							addPrintingScale;

/**
 * @brief Add login name to stamp
 * @var addLoginName
 */
	bool							addLoginName;

/**
 * @brief Add current date and time to stamp
 * @var addDateTime
 */
	bool							addDateTime;

/**
 * @brief Add page number to stamp
 * @var addPageNumber
 */
	bool							addPageNumber;

/**
 * @brief Add custom text to stamp
 * @var addCustomText
 */
	bool							addCustomText;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[6];

/**
 * @brief User text
 * @var customText
 */
	char							customText[256];

/**
 * @brief Position of the stamp. Invalid positions: @c APIAnc_LM, @c APIAnc_MM, @c APIAnc_RM
 * @var position
 */
	API_AnchorID					position;

/**
 * @brief Index of the stamp's font
 * @var fontID
 */
	short							fontID;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

/**
 * @brief Height of the stamp's font in paper mms
 * @var fontHeight
 */
	double							fontHeight;

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[8];

};


/**
 * @brief Printing parameters.
 * @struct API_PrintPars
 * @ingroup ProjectOperation
 * @remarks For the utilization of this structure see the @ref ACAPI_ProjectOperation_Print and the @c ACAPI_Rendering_PhotoRender automation functions.
 * 			You can retrieve the current printer settings with the @ref ACAPI_ProjectOperation_GetPrinterPars function.
 */
struct API_PrintPars {

/**
 * @brief Printing scale [1..30000]. Ignored if @c printArea or @c scaleToPaper is @c true
 * @var scale
 */
	short							scale;

/**
 * @brief Print also the construction grid lines
 * @var grid
 */
	bool							grid;

/**
 * @brief Print text, arrowheads, and scale-independent dashed lines and fills at the actual size defined in their settings dialogs or proportionally enlarged or reduced to the printing scale
 * @var fixText
 */
	bool							fixText;

/**
 * @brief Print the whole drawing or 3D projection fitting onto a page or print the current zoom or the content of the current marquee area only
 * 		  | Value | Description |
 * 		  |-------|-------------|
 * 		  | PrintArea_CurrentView | Print current zoom |
 * 		  | PrintArea_EntireDrawing | Print entire drawing |
 * 		  | PrintArea_Marquee | Print current marquee area |
 * @var printArea
 */
	char							printArea;

/**
 * @brief Print ghost story as well.
 * @var printGhost
 */
	bool							printGhost;

/**
 * @brief Scale output to paper width
 * @var scaleToPaper
 */
	bool							scaleToPaper;

/**
 * @brief Print every zone / page on new sheet.
 * @var newSheet
 *
 */
	bool							newSheet;

/**
 * @brief Print everything in black (Windows only)
 * @var allColorsToBlack
 */
	bool							allColorsToBlack;

/**
 * @brief Dither on black-and-white printers (Windows only)
 * @var ditherOnPrinter
 */
	bool							ditherOnPrinter;

/**
 * @brief Use printer resolution for pictures (Windows only)
 * @var usePrinterRes
 */
	bool							usePrinterRes;

/**
 * @brief Scale output to fit page.
 * @var scaleFitToPage
 */
	bool							scaleFitToPage;

/**
 * @brief Align print area on paper.
 * @var printAlignment
 */
	API_AnchorID					printAlignment;

/**
 * @brief Is this a stamp?
 * @var isStamp
 */
	bool							isStamp;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[31];

/**
 * @brief The stamp if @c isStamp is true.
 * @var stamp
 */
	API_PrintStampType				stamp;

/**
 * @brief Top print margin.
 * @var top
 */
	double							top;

/**
 * @brief Left print margin.
 * @var left
 */
	double							left;

/**
 * @brief Bottom print margin.
 * @var bottom
 */
	double							bottom;

/**
 * @brief Right print margin.
 * @var right
 */
	double							right;

};


// =============================================================================
// PhotoRender parameters
//
// =============================================================================

/**
 * @brief Parameters for saving photo rendered picture into an image file.
 * @ingroup Rendering
 * @struct API_PhotoRenderPars
 * @remarks The @c ACAPI_Rendering_PhotoRender automation function uses this structure.
 */
struct API_PhotoRenderPars {

/**
 * @brief Image file format for saving the picture. Valid values are: @c APIFType_PictFile, @c APIFType_BMPFile, @c APIFType_TIFFFile, @c APIFType_JPEGFile and @c APIFType_GIFFile
 * @var fileTypeID
 */
	API_FTypeID						fileTypeID;

/**
 * @brief Reserved for further use
 * @var filler_1
 */

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief File specification for saving the picture
 * @var file
 */
	IO::Location					*file;

/**
 * @brief Color depth of the picture to be saved
 * @var colorDepth
 */
	API_ColorDepthID				colorDepth;

/**
 * @brief Use dithering when saving the picture
 * @var dithered
 */
	bool							dithered;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	bool							filler_2[7];

/**
 * @brief Reserved for later use.
 * @var filler_3
 */
	Int32							filler_3[30];

};


// =============================================================================
// Publishing parameters
//
// =============================================================================

/**
 * @brief Publishing parameters.
 * @struct API_PublishPars
 * @ingroup ProjectOperation
 * @remarks For an example please see the @c PublishTest() function in the Navigator_Test example.
 */
struct API_PublishPars {

/**
 * @brief Identifies the publisher set. Its value comes from the @ref ACAPI_Navigator_GetNavigatorChildrenItems call.
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief Full path for local/LAN publishing.
 * @var path
 */
	IO::Location					*path;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

};


// =============================================================================
// Publishing parameters
//
// =============================================================================
/**
 * @brief The information of a library part required for opening the library part with @ref ACAPI_LibraryManagement_OpenLibraryPart.
 * @struct API_OpenLibPartInfo
 * @ingroup LibraryPart
 */
struct API_OpenLibPartInfo {
/**
 * @brief Full path of the library part to open.
 * @var libPartLoc
 */
	IO::Location					*libPartLoc;

/**
 * @brief Document/symbol name (Unicode format) of the library part to open.
 * @var docName
 */
	const GS::uchar_t				*docName;

/**
 * @brief GDL File indicator.
 * @var debugGDL
 */
	bool							debugGDL;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	char							filler [3];
};


// ---------------------------------------------------------------------------------------------------------------------

#endif
