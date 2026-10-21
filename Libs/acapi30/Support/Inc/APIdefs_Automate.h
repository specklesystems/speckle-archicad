// *********************************************************************************************************************
// API definitions - automation functions
//
// Module:			API
// Namespace:		-
// *********************************************************************************************************************

#if !defined (APIDEFS_AUTOMATION_H)
#define	APIDEFS_AUTOMATION_H

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// GSRoot
#include "HashTable.hpp"
#include "UniString.hpp"

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
 * @ingroup ProjectOperation
 * @remarks For the utilization of this structure see the @ref ACAPI_ProjectOperation_Open and @ref ACAPI_ProjectOperation_Save automation functions.
 */
typedef enum {
	/** unknown file type */
	APIFType_None,

	/** Archicad Solo Project File */
	APIFType_PlanFile,

	/** Archicad Archive File */
	APIFType_A_PlanFile,

	/** Archicad Backup File */
	APIFType_Bak_PlanFile,

	/** Archicad 6.0 Plan File */
	APIFType_PlanFile600,

	/** Archicad 6.0 Archive File */
	APIFType_A_PlanFile600,

	/** Archicad 6.5 Plan File */
	APIFType_PlanFile650,

	/** Archicad 6.5 Archive File */
	APIFType_A_PlanFile650,

	/** Archicad 7.0 Plan File */
	APIFType_PlanFile700,

	/** Archicad 7.0 Archive File */
	APIFType_A_PlanFile700,

	/** Archicad List File with Tabs */
	APIFType_TabListFile,

	/** Archicad Object File */
	APIFType_ObjectFile,

	/** Archicad Door File */
	APIFType_DoorFile,

	/** Archicad Window File */
	APIFType_WindowFile,

	/** Archicad GDL File */
	APIFType_GDLFile,

	/** 2D Lines File */
	APIFType_2DLinesFile,

	/** PNG File */
	APIFType_PNGFile,

	/** Bitmap File */
	APIFType_BMPFile,

	/** TIFF File */
	APIFType_TIFFFile,

	/** JPEG File */
	APIFType_JPEGFile,

	/** GIF File */
	APIFType_GIFFile,

	/** Windows Enhanced Metafile */
	APIFType_EMFFile,

	/** Windows Metafile */
	APIFType_WMFFile,

	/** Archicad 8 Plan File */
	APIFType_PlanFile800,

	/** Archicad 8 Archive File */
	APIFType_A_PlanFile800,

	/** Archicad 8.1 Plan File */
	APIFType_PlanFile810,

	/** Archicad 8.1 Archive File */
	APIFType_A_PlanFile810,

	/** Archicad 9.0 Plan File */
	APIFType_PlanFile900,

	/** Archicad 9.0 Archive File */
	APIFType_A_PlanFile900,

	/** Archicad 10.0 Plan File */
	APIFType_PlanFile1000,

	/** Archicad 10.0 Archive File */
	APIFType_A_PlanFile1000,

	/** Archicad 11.0 Plan File */
	APIFType_PlanFile1100,

	/** Archicad 11.0 Archive File */
	APIFType_A_PlanFile1100,

	/** Archicad 12.0 Plan File */
	APIFType_PlanFile1200,

	/** Archicad 12.0 Archive File */
	APIFType_A_PlanFile1200,

	/** IFC File */
	APIFType_IfcFile,

	/** Archicad 13 Plan File */
	APIFType_PlanFile1300,

	/** Archicad 13 Archive File */
	APIFType_A_PlanFile1300,

	/** Archicad 14 Plan File */
	APIFType_PlanFile1400,

	/** Archicad 14 Archive File */
	APIFType_A_PlanFile1400,

	/** Archicad 15 Plan File */
	APIFType_PlanFile1500,

	/** Archicad 15 Archive File */
	APIFType_A_PlanFile1500,

	/** Archicad 16 Plan File */
	APIFType_PlanFile1600,

	/** Archicad 16 Archive File */
	APIFType_A_PlanFile1600,

	/** Archicad 17 Plan File */
	APIFType_PlanFile1700,

	/** Archicad 17 Archive File */
	APIFType_A_PlanFile1700,

	/** Archicad 18 Plan File */
	APIFType_PlanFile1800,

	/** Archicad 18 Archive File */
	APIFType_A_PlanFile1800,

	/** PDF File */
	APIFType_PdfFile,

	/** Archicad 19 Plan File */
	APIFType_PlanFile1900,

	/** Archicad 19 Archive File */
	APIFType_A_PlanFile1900,

	/** Archicad 20 Plan File */
	APIFType_PlanFile2000,

	/** Archicad 20 Archive File */
	APIFType_A_PlanFile2000,

	/** Archicad 21 Plan File */
	APIFType_PlanFile2100,

	/** Archicad 21 Archive File */
	APIFType_A_PlanFile2100,

	/** Archicad 22 Plan File */
	APIFType_PlanFile2200,

	/** Archicad 22 Archive File */
	APIFType_A_PlanFile2200,

	/** Archicad 23 Plan File */
	APIFType_PlanFile2300,

	/** Archicad 23 Archive File */
	APIFType_A_PlanFile2300,

	/** Archicad 24 Plan File */
	APIFType_PlanFile2400,

	/** Archicad 24 Archive File */
	APIFType_A_PlanFile2400,

	/** Archicad 25 Plan File */
	APIFType_PlanFile2500,

	/** Archicad 25 Archive File */
	APIFType_A_PlanFile2500,

	/** Archicad 26 Plan File */
	APIFType_PlanFile2600,

	/** Archicad 26 Archive File */
	APIFType_A_PlanFile2600,

	/** Archicad 27 Plan File */
	APIFType_PlanFile2700,

	/** Archicad 27 Archive File */
	APIFType_A_PlanFile2700,

	/** Archicad 28 Plan File */
	APIFType_PlanFile2800,

	/** Archicad 28 Archive File */
	APIFType_A_PlanFile2800,

	/** Archicad 29 Plan File */
	APIFType_PlanFile2900,

	/** Archicad 29 Archive File */
	APIFType_A_PlanFile2900,		// OpenSaveasOLDVersion

	/** SAF File */
	APIFType_SafFile

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
 * @brief Save pict/bmp files readable on both (Mac/Win) platforms
 * @var picturesInTIFF
 */
	bool							picturesInTIFF;

/**
 * @brief Include linked textures while saving the archive
 * @var texturesOn
 */
	bool							texturesOn;

/**
 * @brief Include background picture while saving the archive
 * @var backgroundPictOn
 */
	bool							backgroundPictOn;

/**
 * @brief Include all Properties Library Parts while saving the archive
 * @var propertiesOn
 */
	bool							propertiesOn;

/**
 * @brief Include full library while saving the archive
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
 * @ingroup ProjectOperation
 * @remarks These options correspond to the formats you can choose while saving something as an Archicad object, both from the plan and the 3D window.
 */
typedef enum {
	/** Write GDL Text in file (as a macro). */
	APIConvMod_TextGDL,

	/** Convert into 3D model. */
	APIConvMod_MemGDL,

	/** Write as GDL Text in a symbol file. */
	APIConvMod_SymTxtGDL,

	/** Write as BINARY in a symbol file. */
	APIConvMod_SymBinGDL,

	/** Convert to side view. */
	APIConvMod_SideGDL,

	/** Create GDL script to drag-and-drop. */
	APIConvMod_DragGDL

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
 * 		file should become an editable text or a non-editable binary file. The `removeLine` field affects only objects
 * 		saved from the 3D view.
 */
struct API_SavePars_Object {

/**
 * @brief The place to put the GDL text/binary information (only when saving from the 3D view). Can be either @c API_ConvMod_SymTxtGDL or @c API_ConvMod_SymBinGDL.
 * @var libItMode
 */
	API_ConvModID					libItMode;

/**
 * @brief Remove redundant lines (only when saving from the 3D view).
 * @var removeLine
 * @remarks This affects only objects saved from the 3D view.
 */
	bool							removeLine;

/**
 * @brief Save selection only when the file type is an object file (only when saving from a 2D view).
 * @var saveSelOnly
 */
	bool							saveSelOnly;

/**
 * @brief Save 2D or 3D view (when the file type is an object file).
 * @var view2D
 */
	bool							view2D;

/**
 * @brief Indicates if the saved library part is placeable.
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
 * @ingroup ProjectOperation
 * @since Archicad 26
 * @remarks This structure is used only by @ref API_SavePars_Ifc.
 */
typedef enum {
	/** Defines IFC file format. */
	API_IFC,

	/** Defines IFC ZIP file format. */
	API_IFCZIP

} API_IfcTypeID;


/**
 * @brief Selected elements for IFC export.
 * @ingroup ProjectOperation
 * @remarks This type specifies in @ref API_SavePars_Ifc.
 */
typedef enum {
	/** All elements in the current project. */
	API_EntireProject = 1,

	/** Visible elements on all stories */
	API_VisibleElementsOnAllStories,

	/** All elements on current storey */
	API_AllElementsOnCurrentStorey,

	/** Visible elements on current storey */
	API_VisibleElementsOnCurrentStorey,

	/** Selected elements only */
	API_SelectedElementsOnly,

	/** Filtered elements */
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
 * 			The IFC assignmentTable set (assignmentTable) is in "child ->parent" format. Example: IfcWall ->IfcRelAssignsToGroup ->IfcGroup.
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
 * @ingroup ProjectOperation
 * @remarks This type specifies in @c API_SavePars_Saf.
 */
typedef enum {
	/** Selected elements only. */
	API_SAFSelectedElementsOnly = 1,

	/** Entire project. */
	API_SAFEntireProject,

	/** Visible elements. */
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
 * @remarks To utilize this structure, see the @ref ACAPI_ProjectOperation_Save automation function.
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
 * @brief Add the project's name to the stamp
 * @var addProjectName
 */
	bool							addProjectName;

/**
 * @brief Add the project's path to the stamp
 * @var addProjectPath
 */
	bool							addProjectPath;

/**
 * @brief Add the view's name to the stamp
 * @var addViewName
 */
	bool							addViewName;

/**
 * @brief Add the layer combination to the stamp
 * @var addLayerComb
 */
	bool							addLayerComb;

/**
 * @brief Add the display options combination to the stamp
 * @var addDispOptComb
 */
	bool							addDispOptComb;

/**
 * @brief Add the scale value to the stamp
 * @var addPrintingScale
 */
	bool							addPrintingScale;

/**
 * @brief Add the login name to the stamp
 * @var addLoginName
 */
	bool							addLoginName;

/**
 * @brief Add the current date and time to the stamp
 * @var addDateTime
 */
	bool							addDateTime;

/**
 * @brief Add the page number to the stamp
 * @var addPageNumber
 */
	bool							addPageNumber;

/**
 * @brief Add custom text to the stamp
 * @var addCustomText
 */
	bool							addCustomText;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[6];

/**
 * @brief User-defined text
 * @var customText
 */
	char							customText[256];

/**
 * @brief Position of the stamp. Invalid positions are: @c APIAnc_LM, @c APIAnc_MM, @c APIAnc_RM
 * @var position
 */
	API_AnchorID					position;

/**
 * @brief Index of the stamp font
 * @var fontID
 */
	short							fontID;

/**
 * @brief Reserved for later use.
 * @var filler_2
 */
	short							filler_2;

/**
 * @brief Height of the stamp font in paper millimeters
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
 * @brief Also print the construction grid lines
 * @var grid
 */
	bool							grid;

/**
 * @brief Print text, arrowheads, and scale-independent dashed lines and fills at the actual size defined in their settings dialogs, or proportionally enlarged or reduced to the printing scale
 * @var fixText
 */
	bool							fixText;

/**
 * @brief Print the whole drawing or 3D projection fitting onto a page, or print the current zoom or the content of the current marquee area only
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
 * @brief Scale output to paper width.
 * @var scaleToPaper
 */
	bool							scaleToPaper;

/**
 * @brief Print every zone/page on a new sheet.
 * @var newSheet
 *
 */
	bool							newSheet;

/**
 * @brief Print everything in black (Windows only).
 * @var allColorsToBlack
 */
	bool							allColorsToBlack;

/**
 * @brief Dither on black-and-white printers (Windows only).
 * @var ditherOnPrinter
 */
	bool							ditherOnPrinter;

/**
 * @brief Use printer resolution for pictures (Windows only).
 * @var usePrinterRes
 */
	bool							usePrinterRes;

/**
 * @brief Scale output to fit the page.
 * @var scaleFitToPage
 */
	bool							scaleFitToPage;

/**
 * @brief Align the print area on the paper.
 * @var printAlignment
 */
	API_AnchorID					printAlignment;

/**
 * @brief Indicates if this is a stamp.
 * @var isStamp
 */
	bool							isStamp;

/**
 * @brief Reserved for later use.
 * @var filler_1
 */
	bool							filler_1[31];

/**
 * @brief The stamp, if @c isStamp is true.
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
 * @brief Parameters for saving a photo-rendered picture into an image file.
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
 * @brief Reserved for later use.
 * @var filler_1
 */
	Int32							filler_1;

/**
 * @brief File specification for saving the picture.
 * @var file
 */
	IO::Location					*file;

/**
 * @brief Color depth of the picture to be saved.
 * @var colorDepth
 */
	API_ColorDepthID				colorDepth;

/**
 * @brief Use dithering when saving the picture.
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
 * @brief The information of a library part required for opening it with @ref ACAPI_LibraryManagement_OpenLibraryPart.
 * @struct API_OpenLibPartInfo
 * @ingroup LibraryPart
 */
struct API_OpenLibPartInfo {
/**
 * @brief Full path to the library part to open.
 * @var libPartLoc
 */
	IO::Location					*libPartLoc;

/**
 * @brief Document/symbol name (Unicode format) of the library part to open.
 * @var docName
 */
	const GS::uchar_t				*docName;

/**
 * @brief GDL file indicator.
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
