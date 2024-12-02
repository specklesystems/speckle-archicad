#if !defined (APIDEFS_VIEWSETTINGS_H)
#define	APIDEFS_VIEWSETTINGS_H

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include "APIdefs_Base.h"
#include "API_Guid.hpp"
#include "APIdefs_AttributeIndex.hpp"
#include "APIdefs_Environment.h"
#include "APIdefs_LibraryParts.h"

namespace GS { class UniString; }


/**
 * @brief Represents the GDL related model view options.
 * @struct API_GDLModelViewOptions
 * @ingroup Navigator
 * @remarks These settings correspond to the relevant items in the Document/Set Model View/Model View Options dialog.
 * 			Model view options are also part of the navigator view definition.
 * 			Call the @ref ACAPI_Navigator_GetViewOptions or @ref ACAPI_Navigator_ChangeViewOptions functions to operate on this data.
 * 			Do not forget to dispose the `gdlOptions` pointer when it is not needed any more. Refer to the @ref ACAPI_FreeGDLModelViewOptionsPtr to do that.
 */
struct API_GDLModelViewOptions {
/**
 * @brief Name of the options in Unicode format.
 * @var name
 */
	GS::uchar_t						name[API_UniLongNameLen];

/**
 * @brief Unique ID of the option.
 * @var guid
 */
	API_Guid						guid;

/**
 * @brief Additional parameters.
 * @var params
 */
	API_AddParType					**params;

/**
 * @brief MD5 checksum of @c params (output only).
 * @var checkSum
 */
	char							checkSum[64];

/**
 * @brief Unique ID of another GDL-related model view option which has all of the functionality of this one. If that is present, the current one is filled, but not shown in the Model View Options dialog.
 * @var supersetGuid
 */
	API_Guid						supersetGuid;

	/**
	 * @brief Reserved for later use.
	 * @var filler
	 */
	Int32							filler[4];

};


/**
 * @brief Represents the model view options of Curtain Walls made with the Curtain Wall Tool. The entire structure is Archicad only.
 * @struct API_CurtainWallModelViewOptions
 * @ingroup Navigator
 * @remarks These settings correspond to the relevant items in the Document/Model View/Model View Options dialog/Curtain Wall Options page.
 * @image html MVO_CurtainWall.png "Curtain Wall MVO" width=50%
 */
struct API_CurtainWallModelViewOptions {

/**
 * @brief Detail level of Curtain Wall Frames (`API_CurtainWallCompShow` etc.)
 * @var cwFrameDetailLevel
 */
	char							cwFrameDetailLevel;

/**
 * @brief Detail level of Curtain Wall Panels (`API_CurtainWallCompShow_None`,.`..Schematic`, `...Simplified`, `...Full`)
 * @var cwPanelDetailLevel
 */
	char							cwPanelDetailLevel;

/**
 * @brief Detail level of Curtain Wall Junctions (`API_CurtainWallCompShow_None`,.`..Schematic`, `...Simplified`, `...Full`)
 * @var cwJunctionDetailLevel
 */
	char							cwJunctionDetailLevel;

/**
 * @brief Detail level of Curtain Wall Accessories (`API_CurtainWallCompShow_None`,.`..Schematic`, `...Simplified`, `...Full`)
 * @var cwAccessoryDetailLevel
 */
	char							cwAccessoryDetailLevel;

};


/**
 * @brief Represents the model view options of Stairs made with Stair Tool. The entire structure is Archicad only.
 * @struct API_StairModelViewOptions
 * @ingroup Navigator
 * @remarks These settings correspond to the relevant items in the Document/Set Model View/Model View Options dialog/Stair Options page.
 * @image html MVO_Stair.png "Stair MVO" width=50%
 */
struct API_StairModelViewOptions {

/**
 * @brief Detail level of Stairs in 3D display. (`API_Stair3DDetail...` etc.)
 * @var stair3DDetailLevel
 */
	char							stair3DDetailLevel;

/**
 * @brief Visualization mode for Stairs in Floor Plan view (`API_StairFloorPlanVisual...` etc.)
 * @var stairFloorPlanVisualization
 */
	char							stairFloorPlanVisualization;

/**
 * @brief Show the headroom above the stair.
 * @var showStairHeadroom
 */
	bool							showStairHeadroom;
	char							filler_1[5];

/**
 * @brief Walking Line is visible in Floor Plan Visualization.
 * @var stairFloorPlanCompWalkingLine
 */
	bool							stairFloorPlanCompWalkingLine;

/**
 * @brief Numbering is visible in Floor Plan Visualization.
 * @var stairFloorPlanCompNumbering
 */
	bool							stairFloorPlanCompNumbering;

/**
 * @brief UP-DOWN Text is visible in Floor Plan Visualization.
 * @var stairFloorPlanCompUPDOWNText
 */
	bool							stairFloorPlanCompUPDOWNText;

/**
 * @brief Description is visible in Floor Plan Visualization.
 * @var stairFloorPlanCompDescription
 */
	bool							stairFloorPlanCompDescription;

/**
 * @brief Accessories of Treads are visible in Floor Plan Visualization.
 * @var stairFloorPlanCompTreadAccessories
 */
	bool							stairFloorPlanCompTreadAccessories;

/**
 * @brief Structure beams of Stairs are visible in Floor Plan Visualization.
 * @var stairFloorPlanCompStructureBeamSupport
 */
	bool							stairFloorPlanCompStructureBeamSupport;

/**
 * @brief Stringers are visible in Floor Plan Visualization.
 * @var stairFloorPlanCompStructureStringers
 */
	bool							stairFloorPlanCompStructureStringers;

/**
 * @brief Cantilevered structure is visible in Floor Plan Visualization.
 * @var stairFloorPlanCompStructureCantilevered
 */
	bool							stairFloorPlanCompStructureCantilevered;

/**
 * @brief Walking Line is visible in Reflected Ceiling Plan Display.
 * @var stairReflectedCompWalkingLine
 */
	bool							stairReflectedCompWalkingLine;

/**
 * @brief Description is visible in Reflected Ceiling Plan Display.
 * @var stairReflectedCompDescription
 */
	bool							stairReflectedCompDescription;

/**
 * @brief Structural beams of Stairs are visible in Reflected Ceiling Plan Display.
 * @var stairReflectedCompStructureBeamSupport
 */
	bool							stairReflectedCompStructureBeamSupport;

/**
 * @brief Stringers of Stairs are visible in Reflected Ceiling Plan Display.
 * @var stairReflectedCompStructureStringers
 */
	bool							stairReflectedCompStructureStringers;

/**
 * @brief Cantilevered structure is visible in Reflected Ceiling Plan Display.
 * @var stairReflectedCompStructureCantilevered
 */
	bool							stairReflectedCompStructureCantilevered;
	bool							filler_2[3];

/**
 * @brief Index of the Surface attribute to use in Schematic 3D Display Detail.
 * @var stairSchemeSurfaceIndex
 */
	API_AttributeIndex				stairSchemeSurfaceIndex;

/**
 * @brief Index of the Line attribute to use in Schematic 3D Display Detail as Cut Line.
 * @var stairSchemeCutLineIndex
 */
	API_AttributeIndex				stairSchemeCutLineIndex;

/**
 * @brief Index of the Pen in the current Pen Table to use in Schematic 3D Display Detail as the Cut Line Pen.
 * @var stairSchemeCutLinePenIndex
 */
	short							stairSchemeCutLinePenIndex;

/**
 * @brief Index of the Line attribute to use in Schematic 3D Display Detail as Uncut Line.
 * @var stairSchemeUncutLineIndex
 */
	API_AttributeIndex				stairSchemeUncutLineIndex;

/**
 * @brief Index of the Pen in the current Pen Table to use in Schematic 3D Display Detail as the Uncut Line Pen.
 * @var stairSchemeUncutLinePenIndex
 */
	short							stairSchemeUncutLinePenIndex;
	short							filler_3[3];

};


/**
 * @brief Represents the model view options of Railings made with Railing Tool. The entire structure is Archicad only.
 * @struct API_RailingModelViewOptions
 * @ingroup Navigator
 * @remarks These settings correspond to the relevant items in the Document/Set Model View/Model View Options dialog/Railing Options page.
 * @image html MVO_Railing.png "Railing MVO" width=50%
 */
struct API_RailingModelViewOptions {

/**
 * @brief Detail level of railings in 3D display.
 * @var railing3DDetailLevel
 */
	char							railing3DDetailLevel;
	char							filler_1[7];

/**
 * @brief Posts are visible in Floor Plan Visualization.
 * @var railing2DDisplayCompPosts
 */
	bool							railing2DDisplayCompPosts;

/**
 * @brief Top rails are visible in Floor Plan Visualization.
 * @var railing2DDisplayCompTopRail
 */
	bool							railing2DDisplayCompTopRail;

/**
 * @brief Handrails are visible in Floor Plan Visualization.
 * @var railing2DDisplayCompHandrails
 */
	bool							railing2DDisplayCompHandrails;

/**
 * @brief Rails are visible in Floor Plan Visualization.
 * @var railing2DDisplayCompRails
 */
	bool							railing2DDisplayCompRails;

/**
 * @brief Inner posts are visible in Floor Plan Visualization.
 * @var railing2DDisplayCompInnerPosts
 */
	bool							railing2DDisplayCompInnerPosts;

/**
 * @brief Balusters are visible in Floor Plan Visualization.
 * @var railing2DDisplayCompBalusters
 */
	bool							railing2DDisplayCompBalusters;

/**
 * @brief Panels are visible in Floor Plan Visualization.
 * @var railing2DDisplayCompPanels
 */
	bool							railing2DDisplayCompPanels;
	bool							filler_2;

/**
 * @brief Index of the Surface attribute to use in Schematic 3D Display Detail.
 * @var railingSchemeSurfaceIndex
 */
	API_AttributeIndex				railingSchemeSurfaceIndex;

/**
 * @brief Index of the Line attribute to use in Schematic 3D Display Detail as Cut Line.
 * @var railingSchemeCutLineIndex
 */
	API_AttributeIndex				railingSchemeCutLineIndex;

/**
 * @brief Index of the Pen in the current Pen Table to use in Schematic 3D Display Detail as the Cut Line Pen.
 * @var railingSchemeCutLinePenIndex
 */
	short							railingSchemeCutLinePenIndex;

/**
 * @brief Index of the Line attribute to use in Schematic 3D Display Detail as Uncut Line.
 * @var railingSchemeUncutLineIndex
 */
	API_AttributeIndex				railingSchemeUncutLineIndex;

/**
 * @brief Index of the Pen in the current Pen Table to use in Schematic 3D Display Detail as the Uncut Line Pen.
 * @var railingSchemeUncutLinePenIndex
 */
	short							railingSchemeUncutLinePenIndex;
	short							filler_3[3];

};


/**
 * @brief Represents the model view options.
 * @struct API_ModelViewOptions
 * @ingroup Navigator
 * @remarks These settings correspond to the relevant items in the Document/Set Model View/Model View Options dialog.
 * 			Model view options are also part of the navigator view definition (@ref API_NavigatorView).
 * 			Call the @ref ACAPI_Navigator_GetViewOptions or @ref ACAPI_Navigator_ChangeViewOptions function codes to operate on this data.
 * 			Remember to dispose of the `gdlOptions` pointer when it is not needed anymore. Refer to the @ref ACAPI_FreeGDLModelViewOptionsPtr to do that.
 */
struct API_ModelViewOptions {
	char							filler_0[2];

/**
 * @brief Door display definition. (`API_Hole_ShowWithDim`...`API_Hole_HideHole`)
 * @var doorMode
 */
	char							doorMode;

/**
 * @brief Window display definition. (`API_Hole_ShowWithDim`...`API_Hole_HideHole`)
 * @var windowMode
 */
	char							windowMode;

/**
 * @brief Skylight display definition. (`API_Hole_ShowWithDim`...`API_Hole_HideHole`)
 * @var skylightMode
 */
	char							skylightMode;
	char							filler_1;

	/**
	 * @brief Specifies the section markers visibility (Archicad only).
	 * |Marker|Meaning|
	 * |--- |--- |
	 * |API_Section_Marker_Normal|Section Markers are fully displayed on the floor plan.|
	 * |API_Section_Marker_KeyPlan|Section Markers are displayed with only one marker at the midpoint between the<br>two ends of the imaginary Section Line.|
	 * |API_Section_Marker_AsInSettings|Section Markers are displayed as they are set in the Section Settings dialog box.|
	 *
	 * @var sectionMarker
	 */
	char							sectionMarker;

/**
 * @brief Specifies the beam drawing style (Archicad only). (`API_Beam_Drawing_Full`, `API_Beam_Drawing_RefLine`, `API_Beam_Drawing_Contour`)
 * @var beamMethod
 */
	char							beamMethod;

/**
 * @brief Specifies the roof shell drawing style: `API_RoofShellShow_AllDetails`, `API_RoofShellShow_TopSurface`, `API_RoofShellShow_ContourDrawing`.
 * @var roofShellMode
 */
	char							roofShellMode;

/**
 * @brief Specifies whether column symbols are displayed on the floor plan (Archicad only): `API_Column_Symbol_Show`, `API_Column_Symbol_Hide`
 * @var showColumnSymbol
 */
	char							showColumnSymbol;

/**
 * @brief For adjoining slabs with the same top surface and top height: `API_Slab_ShowCommonEdges`, `API_Slab_EliminateCommonEdges`, `API_Slab_HiddenCommonEdges`
 * @var slabMethod
 */
	char							slabMethod;
	char							filler_2;

/**
 * @brief Use hidden line under slab in columns.
 * @var coluHiddenlineUnderSlabs
 */
	bool							coluHiddenlineUnderSlabs;

/**
 * @brief Use hidden line under slab in beams.
 * @var beamHiddenlineUnderSlabs
 */
	bool							beamHiddenlineUnderSlabs;

/**
 * @brief Tells whether the zone stamps should be visible.
 * @var zoneHideZoneStamp
 */
	bool							zoneHideZoneStamp;

/**
 * @brief Structure of Curtain Wall Model View Options.
 * @var curtainWallModelViewOptions
 */
	API_CurtainWallModelViewOptions	curtainWallModelViewOptions;

/**
 * @brief Structure of Stair Model View Options.
 * @var stairModelViewOptions
 */
	API_StairModelViewOptions		stairModelViewOptions;

/**
 * @brief Structure of Railing Model View Options.
 * @var railingModelViewOptions
 */
	API_RailingModelViewOptions		railingModelViewOptions;


/**
 * @brief Array of GDL related view options (GSPtr). It has an effect only on library part based elements' appearence (window, door, object, lamp).
 * @var gdlOptions
 */
	API_GDLModelViewOptions*		gdlOptions;

};

/**
 * @brief Contains common information related to API_ModelViewOptionsType types.
 * @struct API_ModelViewOptions_Head
 * @ingroup Navigator
 * @remarks This structure contains general information about an MVO.
 * 			As a general rule, before calling any of the applicable functions, clear the whole structure, fill the necessary fields, then call the function. Clearing all fields in the structure is important for future compatibility; in the next API releases the fillers may have meanings.
 * 			You can access long name in C string format (name) or in GS::UniString format (uniStringNamePtr).
 * 			You can use UniString format for MVO operations to avoid loss of information due to character conversion. To achieve this set the pointer of a GS::UniString variable in the uniStringNamePtr field of the @ref API_ModelViewOptions_Head structure. Otherwise always set this field to nullptr.
 * 			You can identify MVOs name. If you want to refer to an MVO by name, set the guid member to APINULLGuid. If you set uniStringNamePtr to point to a valid GS::UniString object, the content of the name character buffer is ignored.
 */
struct API_ModelViewOptions_Head {
/**
 * @brief The index is the current database index of the given MVO.
 * References to any MVO are done through these indices. It goes from 1 to the maximum available MVO index.
 * @var index
 */
	Int32				index;

/**
 * @brief The MVO flags.
 * | Value | Description |
 * |-------|-------------|
 * |@c APIAttr_IsClientCreated | In teamwork mode, indicates whether an MVO was created by the client and not sent with the changes yet. |
 * @var flags
 */
	short				flags;
	short				filler_0;

/**
 * @brief The name of the MVO as UTF-8 encoded C string, which appears in the appropriate dialogs.
 * @var name
 */
	char				name[API_UniLongNameLen];

/**
 * @brief The globally unique identifier (GUID) of the MVO; can be used for identifying MVO with @ref ACAPI_Navigator_ModelViewOptions_Get and @ref ACAPI_Navigator_ModelViewOptions_Search.
 * @var guid
 */
	API_Guid			guid;

	/**
	 * @brief The last time the MVO was modified as @c GSTime .
	 * @var modiTime
	 */
	UInt64				modiTime;

/**
 * @brief Optional parameter for accessing the name of the MVO in @c UniString (UTF-16 encoded) format.
 * @var uniStringNamePtr
 */
	GS::UniString*		uniStringNamePtr;

};

/**
 * @brief Representation of the model view options.
 * @struct API_ModelViewOptionsType
 * @ingroup Navigator
 * @remarks These settings correspond to the relevant items in the Model View Options menu.
 * 			Call the @ref ACAPI_Navigator_ModelViewOptions_Search or the @ref ACAPI_Navigator_ModelViewOptions_Get functions to operate on this data.
 */
struct API_ModelViewOptionsType {
/**
 * @brief general information of the given MVO
 * @var head
 */
	API_ModelViewOptions_Head	head;

/**
 * @brief details of the given MVO
 * @var modelViewOpt
 */
	API_ModelViewOptions		modelViewOpt;
	Int32						filler_2[8];
};


/**
 * @brief Representation of the display only options.
 * @struct API_OnScreenViewOptions
 * @ingroup Navigator
 * @remarks These settings correspond to the relevant items in the View/On-Screen View Options menu.
 * 			Call the @ref ACAPI_Navigator_GetViewOptions or the @ref ACAPI_Navigator_ChangeViewOptions functions to operate on this data.
 */
struct API_OnScreenViewOptions {

/**
 * @brief The wall and beam intersection display method. (`API_Drawing_Clean`, `API_Drawing_Constr`)
 * @var wallMode
 */
	char							wallMode;

/**
 * @brief Specifies whether roof pivot lines are displayed.
 * @var showRoofPivLine
 */
	bool							showRoofPivLine;

/**
 * @brief Specifies whether Fill handles are displayed.
 * @var showFillHandles
 */
	bool							showFillHandles;

/**
 * @brief Specifies whether lines are displayed with their true weight. (`API_LWeight_On`, `API_LWeight_Hairline`)
 * @var lineWeight
 */
	char							lineWeight;

/**
 * @brief Specifies whether Text block handles are displayed. (`API_TextSet_Normal`, `API_TextSet_Handles`)
 * @var textMode
 */
	char							textMode;

/**
 * @brief Specifies whether Figure handles are displayed. (`API_Figure_WithHandles`, `API_Figure_WithoutHandles`)
 * @var figureMode
 */
	char							figureMode;

/**
 * @brief Specifies to show cut bodies for shell and roof in 3D (OpenGL only).
 * @var showExtrudedBodies
 */
	bool							showExtrudedBodies;

/**
 * @brief Specifies camera path visibility (Archicad only): `API_CamPath_None`, `API_CamPath_CamerasOnly`, `API_CamPath_CamerasAndPath`, `API_CamPath_Everything`
 * @var camPathViewMode
 */
	char							camPathViewMode;

/**
 * @brief Specifies the beam drawing style (Archicad only): `API_Wall_Drawing_Contour`, `API_Wall_Drawing_RefLine`
 * @var wallMethod
 */
	char							wallMethod;

/**
 * @brief Specifies if the range of different markers is visible.
 * @var showMarkerRange
 */
	bool							showMarkerRange;

/**
 * @brief Specifies the how vector fills are displayed: `API_Fill_Vector`, `API_Fill_Bitmap`
 * @var filldrawingMode
 */
	char							filldrawingMode;

/**
 * @brief Specifies whether spline handles are visible.
 * @var splineMode
 */
	bool							splineMode;

/**
 * @brief Specifies whether drawing frames are visible.
 * @var showDrawingFrames
 */
	bool							showDrawingFrames;

/**
 * @brief Specifies whether master layout items are visible on layouts.
 * @var showMasterItems
 */
	bool							showMasterItems;

/**
 * @brief Specifies whether cut lines are displayed as bold.
 * @var boldCutLines
 */
	bool							boldCutLines;

/**
 * @brief Specifies if the bounds of markers are visible.
 * @var showSourceMarkerBound
 */
	bool							showSourceMarkerBound;

/**
 * @brief Specifies if dimensions' reference lines should be visible.
 * @var showDimensionAllLines
 */
	bool							showDimensionAllLines;

/**
 * @brief Specifies if openings' cutting bodies should be visible.
 * @var showOpeningCuttingBodies
 */
	bool							showOpeningCuttingBodies;

/**
 * @brief Specifies if openings' reference lines should be visible.
 * @var showOpeningReferences
 */
	bool							showOpeningReferences;
	char							filler_1[7];

};


/**
 * @brief Describes various display output options.
 * @struct API_ViewOptions
 * @ingroup Navigator
 * @remarks Call the @ref ACAPI_Navigator_GetViewOptions or the @ref ACAPI_Navigator_ChangeViewOptions functions to operate on this data.
 */
struct API_ViewOptions {

/**
 * @brief View options which have effect on both the display and on various outputs.
 * @var modelViewOpt
 */
	API_ModelViewOptions			modelViewOpt;

/**
 * @brief View options which have effect on the display only.
 * @var onScreenViewOpt
 */
	API_OnScreenViewOptions			onScreenViewOpt;

/**
 * @brief Reserved for later use.
 * @var filler
 */
	Int32							filler[4];

};


/**
 * @brief Contains common information related to dimension preference types.
 * @struct API_DimensionStandards_Head
 * @ingroup Navigator
 * @remarks This structure contains general information about an dimension preference.
 * 			As a general rule, before calling any of the applicable functions, clear the whole structure, fill the necessary fields, then call the function. Clearing all fields in the structure is important for future compatibility; in the next API releases the fillers may have meanings.
 * 			You can access long name in C string format (name) or in GS::UniString format (uniStringNamePtr).
 * 			You can use UniString format for dimension preference operations to avoid loss of information due to character conversion. To achieve this set the pointer of a GS::UniString variable in the uniStringNamePtr field of the @ref API_ModelViewOptions_Head structure. Otherwise always set this field to nullptr.
 * 			You can identify dimension preferences by name. If you want to refer to an dimension preference by name, set the guid member to APINULLGuid. If you set uniStringNamePtr to point to a valid GS::UniString object, the content of the name character buffer is ignored.
 */
struct API_DimensionStandards_Head {
/**
 * @brief The index is the current database index of the given dimension preference.
 * References to any dimension preference are done through these indices. It goes from 1 to the maximum available dimension preference index.
 * @var index
 */
	Int32				index;

/**
 * @brief The dimension preference flags.
 * | Value | Description |
 * |-------|-------------|
 * |@c APIAttr_IsClientCreated | In teamwork mode, indicates whether an dimension preference was created by the client and not sent with the changes yet. |
 * @var flags
 */
	short				flags;
	short				filler_0;

/**
 * @brief The name of the dimension preference as UTF-8 encoded C string, which appears in the appropriate dialogs.
 * @var name
 */
	char				name[API_UniLongNameLen];

/**
 * @brief The globally unique identifier (GUID) of the dimension preference; can be used for identifying dimension preference with @ref ACAPI_Navigator_DimStand_Get and @ref ACAPI_Navigator_DimStand_Search.
 * @var guid
 */
	API_Guid			guid;

	/**
	 * @brief The last time the dimension preference was modified as @c GSTime .
	 * @var modiTime
	 */
	UInt64				modiTime;

/**
 * @brief Optional parameter for accessing the name of the dimension preference in @c UniString (UTF-16 encoded) format.
 * @var uniStringNamePtr
 */
	GS::UniString*		uniStringNamePtr;
};


/**
 * @brief Representation of the dimension preference.
 * @struct API_DimensionStandardsType
 * @ingroup Navigator
 * @remarks These settings correspond to the relevant items in the dimension preferences menu.
 * 			Call the @ref ACAPI_Navigator_DimStand_Search or the @ref ACAPI_Navigator_DimStand_Get functions to operate on this data.
 */
struct API_DimensionStandardsType {
/**
 * @brief general information of the given dimension preference
 * @var head
 */
	API_DimensionStandards_Head		head;
/**
 * @brief details of the given dimension preference
 * @var dim
 */
	API_DimensionPrefs				dim;
	Int32							filler_2[8];
};

#endif