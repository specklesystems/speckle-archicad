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
	APIDo_LoadLibrariesID 			= 'LLIB',					// par1: const GS::Array<API_LibraryInfo>*		par2: ---
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

	APIDo_ShowSelectionIn3DID		= 'SS3D',					// par1: ---									par2: ---
	APIDo_ShowAllIn3DID				= 'SA3D',					// par1: ---									par2: ---

	APIDo_EditHierarchicalElemID	= 'EDHE',					// par1: API_Guid*								par2: ---
	APIDo_CancelHierarchicalElemID	= 'CAHE',					// par1: ---									par2: ---
	APIDo_OkHierarchicalElemID		= 'OKHE',					// par1: ---									par2: ---

	APIDo_PublishID					= 'PUBL'					// par1: API_PublishPars						par2: [GS::Array<API_Guid>*] (selected links)
} API_AutomateID;


// =============================================================================
// New command
//
// =============================================================================

typedef struct {
	bool							newAndReset;				// reset database
	bool							enableSaveAlert;			// enable 'Save the current document before closing' alert
	char							filler_1[6];
} API_NewProjectPars;


// =============================================================================
// Open command
//
// =============================================================================

typedef enum {
	APIFType_None,												// unknown file type

		// plan files
	APIFType_PlanFile,											// ARCHICAD Solo Project File
	APIFType_A_PlanFile,										// ARCHICAD Archive File
	APIFType_Bak_PlanFile,										// ARCHICAD Backup File
	APIFType_WGClientFile,										// ARCHICAD TeamWork Draft File
	APIFType_A_WGClientFile,									// AC TeamWork Draft Archive File
	APIFType_Bak_WGClientFile,									// AC TeamWork Draft Backup File

	APIFType_PlanFile600,										// ARCHICAD 6.0 Plan File
	APIFType_A_PlanFile600,										// ARCHICAD 6.0 Archive File
	APIFType_PlanFile650,										// ARCHICAD 6.5 Plan File
	APIFType_A_PlanFile650,										// ARCHICAD 6.5 Archive File
	APIFType_PlanFile700,										// ARCHICAD 7.0 Plan File
	APIFType_A_PlanFile700,										// ARCHICAD 7.0 Archive File

		// other internal types
	APIFType_WGProjFile,										// ARCHICAD TeamWork Project File
	APIFType_A_WGProjFile,										// AC TeamWork Project Archive
	APIFType_Bak_WGProjFile,									// AC TeamWork Project Backup File
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
	APIFType_A_PlanFile2500,									// ARCHICAD 25.0 Archive File		// OpenSaveasOLDVersion

	APIFType_SafFile											// SAF file

} API_FTypeID;


typedef struct {
	API_FTypeID						fileTypeID;					// format
	bool							libGiven;					// archiveLibSpec is passed or not
	bool							useStoredLib;				// load from the stored library path
	bool							enableSaveAlert;			// enable 'Save the current document before closing' alert
	bool							filler_1;
	IO::Location					*file;						// specification of a file to open
	IO::Location					*archiveLib;				// library folder to create if archive open (optional), nullptr otherwise
} API_FileOpenPars;


// =============================================================================
// SaveAs command
//
// =============================================================================

typedef struct {
	bool							picturesInTIFF;				// save pict/bmp files for readable on both (Mac/Win) platforms
	bool							texturesOn;					// include linked Textures while saving archive
	bool							backgroundPictOn;			// include Background Picture while saving archive
	bool							propertiesOn;				// include All Properties Library Parts while saving archive
	bool							libraryPartsOn;				// include Full Library while saving archive
	bool							filler_1;
	bool							filler_2;
	bool							filler_3;
	Int32							filler_4[8];
} API_SavePars_Archive;


typedef struct {
	bool							elementsOn;					// include all elements in plandump file
	bool							attributesOn;				// include all attributes in plandump file
	bool							propertiesOn;				// include properties in plandump file
	bool							filler_1;
	Int32							filler_2[9];
} API_SavePars_PlanDump;


typedef enum {
	APIConvMod_TextGDL,											// write GDL Text in file
	APIConvMod_MemGDL,											// convert into 3D model
	APIConvMod_SymTxtGDL,										// write as GDL Text in symbol file
	APIConvMod_SymBinGDL,										// write as BINARY in symbol file
	APIConvMod_SideGDL,											// convert to side view
	APIConvMod_DragGDL											// create GDL script to drag-and-drop
} API_ConvModID;

typedef struct {
	API_ConvModID					libItMode;					// API_ConvMod_SymTxtGDL or API_ConvMod_SymBinGDL (in 3D view)
	bool							removeLine;					// have to remove redundant lines? (in 3D view)
	bool							saveSelOnly;				// save selection only (if type is ObjectFile in 2D view)
	bool							view2D;						// save 2D or 3D view (if type is ObjectFile)
	bool							isPlaceable;				// is libpart placeable
	Int32							filler_2[8];
} API_SavePars_Object;


typedef struct {
	API_ColorDepthID				colorDepth;					// one of APIColorDepth_xxx
	bool							dithered;					// have to dither? (if less or equal than 256 colors or grays)
	bool							view2D;						// save 2D or 3D view
	bool							crop;						// crop with zoom
	bool							keepSelectionHighlight;		// keep selection
	Int32							filler_2[8];
} API_SavePars_Picture;


typedef enum {
	API_IFC,													// write IFC file
	API_IFCXML													// write IFC XML file
} API_IfcTypeID;


typedef enum {
	API_EntireProject = 1,
	API_VisibleElementsOnAllStories,
	API_AllElementsOnCurrentStorey,
	API_VisibleElementsOnCurrentStorey,
	API_SelectedElementsOnly,
	API_FilteredElements
} API_ElementsToIfcExportID;


struct API_IFCTranslatorIdentifier {
	GSHandle		innerReference;
	GS::UniString	name;

	API_IFCTranslatorIdentifier ():
		innerReference (nullptr),
		name ("")
	{
	}

	API_IFCTranslatorIdentifier (const API_IFCTranslatorIdentifier& that):
		innerReference (nullptr),
		name (that.name)
	{
		BMHandleToHandle (that.innerReference, &innerReference);
	}

	API_IFCTranslatorIdentifier (API_IFCTranslatorIdentifier&& that):
		API_IFCTranslatorIdentifier ()
	{
		Swap (that);
	}

	~API_IFCTranslatorIdentifier ()
	{
		BMKillHandle (&innerReference);
	}

	API_IFCTranslatorIdentifier&		operator=(API_IFCTranslatorIdentifier other)
	{
		Swap (other);
		return *this;
	}

	void	Swap (API_IFCTranslatorIdentifier& other)
	{
		std::swap (innerReference, other.innerReference);
		name.Swap (other.name);
	}
	
	friend void		Swap (API_IFCTranslatorIdentifier& left, API_IFCTranslatorIdentifier& right)
	{
		left.Swap (right);
	}
};


typedef struct {
	API_IfcTypeID					subType;
	API_IFCTranslatorIdentifier		translatorIdentifier;
	API_ElementsToIfcExportID		elementsToIfcExport;
	const GS::Array<API_Guid>*		elementsSet;				// use only when the elementsToIfcExport is set API_FilteredElements
	bool							includeBoundingBoxGeometry;
	void*							filler_1;
	void*							filler_2;
} API_SavePars_Ifc;


typedef struct {
	float							leftMargin;					// Page`s left-margin in mm-s
	float							topMargin;					// Page`s top-margin in mm-s
	float							rightMargin;				// Page`s right-margin in mm-s
	float							bottomMargin;				// Page`s bottom-margin in mm-s
	float							sizeX;						// Page horizontal size (mm)
	float							sizeY;						// Page vertical size (mm)
	Int32							filler_1[4];
} API_SavePars_Pdf;


typedef enum {
	API_SAFSelectedElementsOnly = 1,
	API_SAFEntireProject,
	API_SAFVisibleElements
} API_ElementsToSAFExportID;


typedef struct {
	API_ElementsToSAFExportID		elementsToSAFExport;
	GS::UniString					selectedSAFTranslatorName;
	Int32							filler_1[3];
} API_SavePars_Saf;


typedef struct {
	API_FTypeID						fileTypeID;					// output format
	Int32							filler_1;
	IO::Location					*file;						// output file
	Int32							filler_2[15];
} API_FileSavePars;

// =============================================================================
// Print command
//
// =============================================================================

#define	PrintArea_CurrentView		0
#define	PrintArea_EntireDrawing		1
#define	PrintArea_Marquee			2

typedef struct {
	bool							addProjectName;
	bool							addProjectPath;
	bool							addViewName;
	bool							addLayerComb;
	bool							addDispOptComb;
	bool							addPrintingScale;
	bool							addLoginName;
	bool							addDateTime;
	bool							addPageNumber;
	bool							addCustomText;
	bool							filler_1[6];
	char							customText[256];
	API_AnchorID					position;
	short							fontID;						// font index
	short							filler_2;
	double							fontHeight;					// vertical size of font in paper mm
	Int32							filler_3[8];
} API_PrintStampType;


typedef struct {
	short							scale;						// printing scale (1-30000)
	bool							grid;						// print grid
	bool							fixText;					// fix size or resize to printing scale
	char							printArea;					// PrintArea_YYY
	bool							printGhost;					// print Ghost Story
	bool							scaleToPaper;				// scale list to paper width
	bool							newSheet;					// every zone/page on new sheet
	bool							allColorsToBlack;			// print everything in black (Windows only)
	bool							ditherOnPrinter;			// dithering on BW printers (Windows only)
	bool							usePrinterRes;				// use printer resolution for pictures (Windows only)
	bool							scaleFitToPage;
	API_AnchorID					printAlignment;
	bool							isStamp;
	bool							filler_1[31];
	API_PrintStampType				stamp;
	double							top;
	double							left;
	double							bottom;
	double							right;
} API_PrintPars;


// =============================================================================
// PhotoRender parameters
//
// =============================================================================

typedef struct {
	API_FTypeID						fileTypeID;					// output format
	Int32							filler_1;
	IO::Location					*file;						// output file
	API_ColorDepthID				colorDepth;
	bool							dithered;
	bool							filler_2[7];
	Int32							filler_3[30];
} API_PhotoRenderPars;


// =============================================================================
// Publishing parameters
//
// =============================================================================

typedef struct {
	API_Guid						guid;						// GUID of the set to publish
	IO::Location					*path;						// output path for LAN
	Int32							filler_1;
} API_PublishPars;


// ---------------------------------------------------------------------------------------------------------------------

#endif
