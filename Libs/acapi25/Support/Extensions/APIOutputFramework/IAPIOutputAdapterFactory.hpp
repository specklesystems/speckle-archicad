#ifndef __IAPIOUTPUTADAPTERFACTORY_HPP__
#define __IAPIOUTPUTADAPTERFACTORY_HPP__

#include "IAPIOutputManager.hpp"

#define APIOUTPUTADAPTER(type) 																									\
virtual IAPIOutputAdapter<type>* GetAdapter (const type& 						forType,										\
											 const API_DatabaseInfo& 			dbInfo,											\
											 IAttributeProxy* 					attributeProxy 		= nullptr,					\
											 GSAPI::OutputUsedAttributesType 	attributeOutputType = GSAPI::DoNotOutput) = 0;

#define APIOUTPUTADAPTERMEMO(type)																								\
virtual IAPIOutputAdapter<type>* GetAdapter (const type& 						forType,										\
											 const API_DatabaseInfo&			dbInfo,											\
											 IAttributeProxy*					attributeProxy		= nullptr,					\
											 GSAPI::OutputUsedAttributesType	attributeOutputType = GSAPI::DoNotOutput,		\
											 const API_ElementMemo*				withMemo            = nullptr) = 0;

namespace GSAPI {

// Predeclarations
template <typename APIType>
class IAPIOutputAdapter;

class IAttributeProxy;


/** @interface
 *  @stereotype abstractfactory */
class IAPIOutputAdapterFactory {
protected:
	IAPIOutputManager& outputManager;
	bool			   managedAdapters;	// factory keeps track and deletes the adapters or not

public:
	IAPIOutputAdapterFactory (IAPIOutputManager& manager, bool keepsTrackOfAdapters = false) 
		: outputManager (manager), managedAdapters (keepsTrackOfAdapters) { }

	IAPIOutputAdapterFactory (const IAPIOutputAdapterFactory& factory) 
		: outputManager (factory.outputManager), managedAdapters (factory.managedAdapters) { }

	virtual ~IAPIOutputAdapterFactory ();

	IAPIOutputAdapterFactory& operator= (const IAPIOutputAdapterFactory& factory) 
	{ 
		outputManager = factory.outputManager; 
		managedAdapters = factory.managedAdapters; 
		return (*this); 
	}

	bool GetManagedAdapters () 
	{ 
		return managedAdapters; 
	}

	template <typename APIType>
	IAPIOutputAdapter<APIType>*	GetTypeAdapter (const APIType&					forType,
												const API_DatabaseInfo&			dbInfo,
												const API_ElementMemo*			withMemo            = nullptr,
												IAttributeProxy*				attributeProxy		= nullptr,
												GSAPI::OutputUsedAttributesType	attributeOutputType = GSAPI::DoNotOutput)	
	{ 
		return GetAdapter (forType, dbInfo, attributeProxy, attributeOutputType, withMemo); 
	}

	template <typename APIType>
	IAPIOutputAdapter<APIType>*	GetTypeAdapter (const APIType&					forType,
												const API_DatabaseInfo&			dbInfo,
												IAttributeProxy*				attributeProxy		= nullptr,
												GSAPI::OutputUsedAttributesType	attributeOutputType = GSAPI::DoNotOutput)	
	{ 
		return GetAdapter (forType, dbInfo, attributeProxy, attributeOutputType); 
	}

	// API Element Types
	APIOUTPUTADAPTERMEMO (API_Element)
	APIOUTPUTADAPTER (API_BeamSegmentType)
	APIOUTPUTADAPTER (API_BeamShapeTypeID)
	APIOUTPUTADAPTER (API_ColumnSegmentType)
	APIOUTPUTADAPTER (API_Elem_Head)
	APIOUTPUTADAPTER (API_ElemTypeID)
	APIOUTPUTADAPTER (API_ElemVariationID)
	APIOUTPUTADAPTER (API_RenovationStatusType)
	APIOUTPUTADAPTER (API_ModelElemStructureType)
	APIOUTPUTADAPTER (API_PenOverrideType)
	APIOUTPUTADAPTER (API_OverriddenAttribute)
	APIOUTPUTADAPTER (API_OverriddenAttributeOrRGB)
	APIOUTPUTADAPTER (API_ExtendedPenType)
	APIOUTPUTADAPTER (API_WallType)
	APIOUTPUTADAPTER (API_WallTypeID)
	APIOUTPUTADAPTER (API_WallReferenceLineLocationID)
	APIOUTPUTADAPTER (API_ZoneRelID)
	APIOUTPUTADAPTER (API_StoryVisibility)
	APIOUTPUTADAPTER (API_LinkToSettings)
	APIOUTPUTADAPTER (API_Coord)
	APIOUTPUTADAPTER (API_Polygon)
	APIOUTPUTADAPTER (API_ElemDisplayOptionsID)
	APIOUTPUTADAPTER (API_ElemProjectionModesID)
	APIOUTPUTADAPTER (API_ElemViewDepthLimitationsID)
	APIOUTPUTADAPTER (API_ColumnType)
	APIOUTPUTADAPTER (API_BeamType)
	APIOUTPUTADAPTER (API_BHoleTypeID)
	APIOUTPUTADAPTER (API_BeamVisibleLinesID)
	APIOUTPUTADAPTER (API_WindowType)
	APIOUTPUTADAPTER (API_SkylightType)
	APIOUTPUTADAPTER (API_OpeningBaseType)
	APIOUTPUTADAPTER (API_VerticalLink)
	APIOUTPUTADAPTER (API_VerticalLinkID)
	APIOUTPUTADAPTER (API_WindowDoorRevealDepthLocationID)
	APIOUTPUTADAPTER (API_WindowDoorDirectionTypes)
	APIOUTPUTADAPTER (API_SkylightFixModeID)
	APIOUTPUTADAPTER (API_SkylightAnchorID)
	APIOUTPUTADAPTER (API_ObjectType)
	APIOUTPUTADAPTER (API_RGBColor)
	APIOUTPUTADAPTER (API_RGBAColor)
	APIOUTPUTADAPTER (API_SlabType)
	APIOUTPUTADAPTER (API_HatchOrientation)
	APIOUTPUTADAPTER (API_HatchOrientationTypeID)
	APIOUTPUTADAPTER (API_CoverFillTransformation)
	APIOUTPUTADAPTER (API_CoverFillTransformationTypeID)
	APIOUTPUTADAPTER (API_RoofType)
	APIOUTPUTADAPTER (API_PlaneRoofData)
	APIOUTPUTADAPTER (API_PolyRoofData)
	APIOUTPUTADAPTER (API_ShellType)
	APIOUTPUTADAPTER (API_ShellBaseType)
	APIOUTPUTADAPTER (API_ExtrudedShellData)
	APIOUTPUTADAPTER (API_RevolvedShellData)
	APIOUTPUTADAPTER (API_RuledShellData)
	APIOUTPUTADAPTER (API_RoofClassID)
	APIOUTPUTADAPTER (API_RoofLevelData)
	APIOUTPUTADAPTER (API_RoofOverHangTypeID)
	APIOUTPUTADAPTER (API_PolyRoofSegmentAngleTypeID)
	APIOUTPUTADAPTER (API_RoofSegmentData)
	APIOUTPUTADAPTER (API_ShellBaseContourEdgeTypeID)
	APIOUTPUTADAPTER (API_ShellBaseCutBodyTypeID)
	APIOUTPUTADAPTER (API_ShellBaseSegmentTypeID)
	APIOUTPUTADAPTER (API_ShellContourData)
	APIOUTPUTADAPTER (API_ShellClassID)
	APIOUTPUTADAPTER (API_ContourEdgeData)
	APIOUTPUTADAPTER (API_MorphingRuleID)
	APIOUTPUTADAPTER (API_LocalCoordsData)
	APIOUTPUTADAPTER (API_LocalCoordsType)
	APIOUTPUTADAPTER (API_Wrapping)
	APIOUTPUTADAPTER (API_PivotPolyEdgeData)
	APIOUTPUTADAPTER (API_ShellShapeData)
	APIOUTPUTADAPTER (API_TextureProjectionTypeID)
	APIOUTPUTADAPTER (API_MorphType)
	APIOUTPUTADAPTER (API_MorphBodyTypeID)
	APIOUTPUTADAPTER (API_MorphEdgeTypeID)
	APIOUTPUTADAPTER (API_EdgeTrimID)
	APIOUTPUTADAPTER (API_RoofEdgeTypeID)
	APIOUTPUTADAPTER (API_Sector)
	APIOUTPUTADAPTER (API_MeshType)
	APIOUTPUTADAPTER (API_MeshLevel)
	APIOUTPUTADAPTER (API_DimensionType)
	APIOUTPUTADAPTER (API_TextPosID)
	APIOUTPUTADAPTER (API_DirID)
	APIOUTPUTADAPTER (API_AppearID)
	APIOUTPUTADAPTER (API_WitnessID)
	APIOUTPUTADAPTER (API_NoteType)
	APIOUTPUTADAPTER (API_NoteContentType)
	APIOUTPUTADAPTER (API_MarkerData)
	APIOUTPUTADAPTER (API_MarkerID)
	APIOUTPUTADAPTER (API_DimLayoutID)
	APIOUTPUTADAPTER (API_DimOriginID)
	APIOUTPUTADAPTER (API_CircleLevelDimensionFillID)
	APIOUTPUTADAPTER (API_DimBase)
	APIOUTPUTADAPTER (API_Base)
	APIOUTPUTADAPTER (API_RadialDimensionType)
	APIOUTPUTADAPTER (API_LevelDimensionType)
	APIOUTPUTADAPTER (API_AngleDimensionType)
	APIOUTPUTADAPTER (API_TextType)
	APIOUTPUTADAPTER (API_AnchorID)
	APIOUTPUTADAPTER (API_JustID)
	APIOUTPUTADAPTER (API_LabelType)
	APIOUTPUTADAPTER (API_LblClassID)
	APIOUTPUTADAPTER (API_LeaderLineShapeID)
	APIOUTPUTADAPTER (API_ArrowData)
	APIOUTPUTADAPTER (API_ArrowID)
	APIOUTPUTADAPTER (API_LblAnchorID)
	APIOUTPUTADAPTER (API_ZoneType)
	APIOUTPUTADAPTER (API_VeneerTypeID)
	APIOUTPUTADAPTER (API_HatchSubType)
	APIOUTPUTADAPTER (API_HatchType)
	APIOUTPUTADAPTER (API_LineType)
	APIOUTPUTADAPTER (API_PolyLineType)
	APIOUTPUTADAPTER (API_ArcType)
	APIOUTPUTADAPTER (API_SplineType)
	APIOUTPUTADAPTER (API_HotspotType)
	APIOUTPUTADAPTER (API_PictureType)
	APIOUTPUTADAPTER (API_Box)
	APIOUTPUTADAPTER (API_ColorDepthID)
	APIOUTPUTADAPTER (API_PictureFormat)
	APIOUTPUTADAPTER (API_CutPlaneType)
	APIOUTPUTADAPTER (API_InteriorElevationType)
	APIOUTPUTADAPTER (API_CutPlaneShowType)
	APIOUTPUTADAPTER (API_CutPlaneUncutSurfaceFillID)
	APIOUTPUTADAPTER (API_DatabaseUnId)
	APIOUTPUTADAPTER (API_CutPlanePlanConn)
	APIOUTPUTADAPTER (API_StoryHandleAppearance)
	APIOUTPUTADAPTER (API_ReferringLevel)
	APIOUTPUTADAPTER (API_MarkerLinkDataType)
	APIOUTPUTADAPTER (API_CameraType)
	APIOUTPUTADAPTER (API_PerspCamPars)
	APIOUTPUTADAPTER (API_PerspPars)
	APIOUTPUTADAPTER (API_CamSetType)
	APIOUTPUTADAPTER (API_PersCamSetPars)
	APIOUTPUTADAPTER (API_DrawingType)
	APIOUTPUTADAPTER (API_NameTypeValues)
	APIOUTPUTADAPTER (API_NumberingTypeValues)
	APIOUTPUTADAPTER (API_ColorModeValues)
	APIOUTPUTADAPTER (API_PenTableUsageModeValues)
	APIOUTPUTADAPTER (API_DrawingTitle)
	APIOUTPUTADAPTER (API_TitlePreviewModes)
	APIOUTPUTADAPTER (API_SectElemType)
	APIOUTPUTADAPTER (API_DetailType)
	APIOUTPUTADAPTER (API_ChangeMarkerType)
	APIOUTPUTADAPTER (API_ChangeMarkerLinkType)
	APIOUTPUTADAPTER (API_ChangeMarkerComponentType)
	// APIOUTPUTADAPTER (API_WorksheetType) // API_WorksheetType == API_DetailType
	APIOUTPUTADAPTER (API_HotlinkType)
	APIOUTPUTADAPTER (API_HotlinkTypeID)
	APIOUTPUTADAPTER (API_CurtainWallType)
	APIOUTPUTADAPTER (API_CWSegmentType)
	APIOUTPUTADAPTER (API_CWFrameType)
	APIOUTPUTADAPTER (API_CWPanelType)
	APIOUTPUTADAPTER (API_CWJunctionType)
	APIOUTPUTADAPTER (API_CWAccessoryType)
	APIOUTPUTADAPTER (API_LinePositionID)
	APIOUTPUTADAPTER (API_StairDisplayTypeID)
	APIOUTPUTADAPTER (API_StairGridTypeID)
	APIOUTPUTADAPTER (API_BreakLineAngleTypeID)
	APIOUTPUTADAPTER (API_BreakLinePositionTypeID)
	APIOUTPUTADAPTER (API_RiserPositionID)
	APIOUTPUTADAPTER (API_RiserCrossSectID)
	APIOUTPUTADAPTER (API_StairStructBottomTypeID)
	APIOUTPUTADAPTER (API_StairPolyTypeID)
	APIOUTPUTADAPTER (API_StairPolyGeometryTypeID)
	APIOUTPUTADAPTER (API_StairNumberingID)
	APIOUTPUTADAPTER (API_StairDirectionID)
	APIOUTPUTADAPTER (API_StairSegmentTypeID)
	APIOUTPUTADAPTER (API_StairDLWinderNumTypeID)
	APIOUTPUTADAPTER (API_StairTurnTypeID)
	APIOUTPUTADAPTER (API_StairInnerWidthOffsetTypeID)
	APIOUTPUTADAPTER (API_StairWinderNumTypeID)
	APIOUTPUTADAPTER (API_StairPartRoleID)
	APIOUTPUTADAPTER (API_StairTreadNosingTypeID)
	APIOUTPUTADAPTER (API_StairStructHeightMeasureID)
	APIOUTPUTADAPTER (API_StairStructureTypeID)
	APIOUTPUTADAPTER (API_StairStructureSideID)
	APIOUTPUTADAPTER (API_StairWalkLineSymbPosID)
	APIOUTPUTADAPTER (API_StairDrainSurfaceTypeID)
	APIOUTPUTADAPTER (API_StairDrainSideID)
	APIOUTPUTADAPTER (API_StairWinderID)
	APIOUTPUTADAPTER (API_StairStructSymbTypeID)
	APIOUTPUTADAPTER (API_StairStructSymbViewID)
	APIOUTPUTADAPTER (API_StairStructSymbVisibilityID)
	APIOUTPUTADAPTER (API_StairStructSymbPartID)
	APIOUTPUTADAPTER (API_StairPolylineEdgeData)
	APIOUTPUTADAPTER (API_StairPolylineVertexData)
	APIOUTPUTADAPTER (API_StairPolylineData)
	APIOUTPUTADAPTER (API_StairBoundaryVertexData)
	APIOUTPUTADAPTER (API_StairBoundaryEdgeData)
	APIOUTPUTADAPTER (API_StairBoundaryData)
	APIOUTPUTADAPTER (API_StairLayoutData)
	APIOUTPUTADAPTER (API_StairRulesData)
	APIOUTPUTADAPTER (API_StairHeadroomData)
	APIOUTPUTADAPTER (API_HeadroomGenerationModeID)
	APIOUTPUTADAPTER (API_StairStructureDrainingData)
	APIOUTPUTADAPTER (API_SideStairStructData)
	APIOUTPUTADAPTER (API_MonolithStairStructData)
	APIOUTPUTADAPTER (API_StairStructureSymbolData)
	APIOUTPUTADAPTER (API_StairMonolithStructureSymbolData)
	APIOUTPUTADAPTER (API_MonolithPartsVisibilityData)
	APIOUTPUTADAPTER (API_StairStructureComponentSettingsVisibilityOnStory)
	APIOUTPUTADAPTER (API_StairStructureComponentSettingsVisibility)
	APIOUTPUTADAPTER (API_StairStructSymbRelevantStoriesID)
	APIOUTPUTADAPTER (API_StairType)
	APIOUTPUTADAPTER (API_StairRiserType)
	APIOUTPUTADAPTER (API_StairTreadType)
	APIOUTPUTADAPTER (API_StairStructureType)
	APIOUTPUTADAPTER (API_RailingFrameData)
	APIOUTPUTADAPTER (API_RailingDistributionData)
	APIOUTPUTADAPTER (API_DistribTypeID)
	APIOUTPUTADAPTER (API_PatternAlignID)
	APIOUTPUTADAPTER (API_RailingHorizontalPosData)
	APIOUTPUTADAPTER (API_RailingVerticalPosData)
	APIOUTPUTADAPTER (API_RailingType)
	APIOUTPUTADAPTER (API_RailingSegmentType)
	APIOUTPUTADAPTER (API_RailingRailEndType)
	APIOUTPUTADAPTER (API_RailingRailConnectionType)
	APIOUTPUTADAPTER (API_RailingPatternType)
	APIOUTPUTADAPTER (API_RailingNodeType)
	APIOUTPUTADAPTER (API_RailingToprailType)
	APIOUTPUTADAPTER (API_RailingHandrailType)
	APIOUTPUTADAPTER (API_RailingRailType)
	APIOUTPUTADAPTER (API_RailingFinishType)
	APIOUTPUTADAPTER (API_RailEndTypeID)
	APIOUTPUTADAPTER (API_RailEndBaseConnectionID)
	APIOUTPUTADAPTER (API_RailBaseBaseConnectionID)
	APIOUTPUTADAPTER (API_RailEndFixtureConnectionID)
	APIOUTPUTADAPTER (API_RailEndArcAngleModeID)
	APIOUTPUTADAPTER (API_RailEndExtrusionModeID)
	APIOUTPUTADAPTER (API_RailConnectionTypeID)
	APIOUTPUTADAPTER (API_RailingRefLineLocationID)
	APIOUTPUTADAPTER (API_StairStoryVisibilityID)
	APIOUTPUTADAPTER (API_RailingPostType)
	APIOUTPUTADAPTER (API_RailingInnerPostType)
	APIOUTPUTADAPTER (API_RailingBalusterType)
	APIOUTPUTADAPTER (API_RailingBalusterSetType)
	APIOUTPUTADAPTER (API_RailingPanelType)
	APIOUTPUTADAPTER (API_SunAngleSettings)
	APIOUTPUTADAPTER (API_SunAngleSettings_SunPositionOption)
	APIOUTPUTADAPTER (API_AxonoPars)
	APIOUTPUTADAPTER (API_Tranmat)
	APIOUTPUTADAPTER (API_CutPlaneMarkerShowType)
	APIOUTPUTADAPTER (API_CWAccessoryCategoryID)
	APIOUTPUTADAPTER (API_CWFrameObjectTypeID)
	APIOUTPUTADAPTER (API_CWJunctionCategoryID)
	APIOUTPUTADAPTER (API_CWPanelObjectTypeID)
	APIOUTPUTADAPTER (API_CWSegmentCategoryID)
	APIOUTPUTADAPTER (API_CWSegmentGridOrigPosTypeID)
	APIOUTPUTADAPTER (API_CWSegmentPatternLogicID)
	APIOUTPUTADAPTER (API_CWSegmentTypeID)
	APIOUTPUTADAPTER (API_CWBoundaryFramePosID)
	APIOUTPUTADAPTER (API_CWPlacementID)
	APIOUTPUTADAPTER (API_GridMeshHead)
	APIOUTPUTADAPTER (API_GridMeshVertex)
	APIOUTPUTADAPTER (API_GridMeshEdge)
	APIOUTPUTADAPTER (API_GridEdgeInfo)
	APIOUTPUTADAPTER (API_GridMeshLine)
	APIOUTPUTADAPTER (API_GridMeshPolygon)
	APIOUTPUTADAPTER (API_Interval)
	APIOUTPUTADAPTER (API_SubElementType)
	APIOUTPUTADAPTER (API_SubElemFlagType)
	APIOUTPUTADAPTER (API_Plane3D)
	APIOUTPUTADAPTER (API_SlabReferencePlaneLocationID)
	APIOUTPUTADAPTER (API_ActTranPars)
	APIOUTPUTADAPTER (API_BeamPart)
	APIOUTPUTADAPTER (API_ConnectionGuidItem)
	APIOUTPUTADAPTER (API_DescriptorRefType)
	APIOUTPUTADAPTER (API_EditCmdID)
	APIOUTPUTADAPTER (API_ElemInfo3D)
	APIOUTPUTADAPTER (API_ElemPartId)
	APIOUTPUTADAPTER (API_HatchFlags)
	APIOUTPUTADAPTER (API_Neig)
	APIOUTPUTADAPTER (API_NeigElemPartID)
	APIOUTPUTADAPTER (API_NeigID)
	APIOUTPUTADAPTER (API_Niche)
	APIOUTPUTADAPTER (API_Obsolete_ComponentRefType)
	APIOUTPUTADAPTER (API_PropertyObjectRefType)
	APIOUTPUTADAPTER (API_SelectionInfo)
	APIOUTPUTADAPTER (API_SelRelativePosID)
	APIOUTPUTADAPTER (API_SelTypeID)
	APIOUTPUTADAPTER (API_ShapePrimsParams)
	APIOUTPUTADAPTER (API_SolidOperationID)
	APIOUTPUTADAPTER (API_SyTran)
	APIOUTPUTADAPTER (API_ToolCmdID)
	APIOUTPUTADAPTER (API_TrimTypeID)
	APIOUTPUTADAPTER (API_UserData)
	APIOUTPUTADAPTER (API_WallPart)
	APIOUTPUTADAPTER (API_Box3D)
	APIOUTPUTADAPTER (API_Point)
	APIOUTPUTADAPTER (API_Rect)
	APIOUTPUTADAPTER (API_Region)
	APIOUTPUTADAPTER (API_UVCoord)

	// API Element Memo Types
	APIOUTPUTADAPTER (API_ElementMemo)
	APIOUTPUTADAPTER (API_AssemblySegmentCutTypeID)
	APIOUTPUTADAPTER (API_AssemblySegmentData)
	APIOUTPUTADAPTER (API_AssemblySegmentLengthTypeID)
	APIOUTPUTADAPTER (API_AssemblySegmentCutData)
	APIOUTPUTADAPTER (API_AssemblySegmentSchemeData)
	APIOUTPUTADAPTER (API_PolyArc)
	APIOUTPUTADAPTER (API_AddParType)
	APIOUTPUTADAPTER (API_AddParID)
	APIOUTPUTADAPTER (API_Gable)
	APIOUTPUTADAPTER (API_EdgeTrim)
	APIOUTPUTADAPTER (API_MeshLevelCoord)
	APIOUTPUTADAPTER (API_Coord3D)
	APIOUTPUTADAPTER (API_DimElem)
	APIOUTPUTADAPTER (API_SplineDir)
	APIOUTPUTADAPTER (API_Beam_Hole)
	APIOUTPUTADAPTER (API_LinkType)
	APIOUTPUTADAPTER (API_ParagraphType)
	APIOUTPUTADAPTER (API_TabType)
	APIOUTPUTADAPTER (API_TabID)
	APIOUTPUTADAPTER (API_RunType)
	APIOUTPUTADAPTER (API_SectionSegment)
	APIOUTPUTADAPTER (API_SegmentHorizontalRange)
	APIOUTPUTADAPTER (API_SegmentVerticalRange)
	APIOUTPUTADAPTER (API_BoundaryDisplay)
	APIOUTPUTADAPTER (API_GridMesh)
	APIOUTPUTADAPTER (API_CWContourData)
	APIOUTPUTADAPTER (API_CWSegmentPatternCellData)
	APIOUTPUTADAPTER (API_CWCellCrossingFrameTypeID)
	APIOUTPUTADAPTER (API_CWSegmentPatternData)

	// API Attribute Types
	APIOUTPUTADAPTER (API_Attribute)
	APIOUTPUTADAPTER (API_Attr_Head)
	APIOUTPUTADAPTER (API_AttrTypeID)
	APIOUTPUTADAPTER (API_PenType)
	APIOUTPUTADAPTER (API_LayerType)
	APIOUTPUTADAPTER (API_LinetypeType)
	APIOUTPUTADAPTER (API_LtypTypeID)
	APIOUTPUTADAPTER (API_FilltypeType)
	APIOUTPUTADAPTER (API_FillSubtype)
	APIOUTPUTADAPTER (API_CompWallType)
	APIOUTPUTADAPTER (API_MaterialType)
	APIOUTPUTADAPTER (API_MaterTypeID)
	APIOUTPUTADAPTER (API_Texture)
	APIOUTPUTADAPTER (API_CityType)
	APIOUTPUTADAPTER (API_LayerCombType)
	APIOUTPUTADAPTER (API_ZoneCatType)
	APIOUTPUTADAPTER (API_FontType)
	APIOUTPUTADAPTER (API_ProfileAttrType)
	APIOUTPUTADAPTER (API_PenTableType)
	APIOUTPUTADAPTER (API_LengthTypeID)
	APIOUTPUTADAPTER (API_AreaTypeID)
	APIOUTPUTADAPTER (API_VolumeTypeID)
	APIOUTPUTADAPTER (API_AngleTypeID)
	APIOUTPUTADAPTER (API_DimensionAttrType)
	APIOUTPUTADAPTER (API_DimensionPrefs)
	APIOUTPUTADAPTER (API_LengthDimFormat)
	APIOUTPUTADAPTER (API_ExtraAccuracyID)
	APIOUTPUTADAPTER (API_AngleDimFormat)
	APIOUTPUTADAPTER (API_AreaDimFormat)
	APIOUTPUTADAPTER (API_ModelViewOptionsType)
	APIOUTPUTADAPTER (API_ModelViewOptions)
	APIOUTPUTADAPTER (API_GDLModelViewOptions)
	APIOUTPUTADAPTER (API_CurtainWallModelViewOptions)
	APIOUTPUTADAPTER (API_StairModelViewOptions)
	APIOUTPUTADAPTER (API_RailingModelViewOptions)
	APIOUTPUTADAPTER (API_MEPSystemType)
	APIOUTPUTADAPTER (API_OperationProfileType)
	APIOUTPUTADAPTER (API_BuildingMaterialType)
	APIOUTPUTADAPTER (API_FillOrientationID)
	APIOUTPUTADAPTER (API_OccupancyTypeID)

	// API AttributeDefExt Types
	APIOUTPUTADAPTER (API_AttributeDefExt)
	APIOUTPUTADAPTER (API_DashItems)
	APIOUTPUTADAPTER (API_LineItems)
	APIOUTPUTADAPTER (API_LtypItemID)
	APIOUTPUTADAPTER (API_FillLine)
	APIOUTPUTADAPTER (API_SymbolHatchDef)
	APIOUTPUTADAPTER (API_SFill_Line)
	APIOUTPUTADAPTER (API_SFill_Arc)
	APIOUTPUTADAPTER (API_CWallComponent)
	APIOUTPUTADAPTER (API_CWallLineComponent)
	APIOUTPUTADAPTER (API_LayerStat)
	APIOUTPUTADAPTER (API_DailyProfile)
	APIOUTPUTADAPTER (API_DailyProfileUsage)
	APIOUTPUTADAPTER (API_HourlyProfile)

	// Primitive Element Types
	APIOUTPUTADAPTERMEMO (GSAPI::PrimElement)
	APIOUTPUTADAPTER (API_Prim_Head)
	APIOUTPUTADAPTER (API_PrimTypeID)
	APIOUTPUTADAPTER (API_PrimPoint)
	APIOUTPUTADAPTER (API_PrimLine)
	APIOUTPUTADAPTER (API_PrimArc)
	APIOUTPUTADAPTER (API_PrimText)
	APIOUTPUTADAPTER (API_PrimPLine)
	APIOUTPUTADAPTER (API_PrimTri)
	APIOUTPUTADAPTER (API_PrimPoly)
	APIOUTPUTADAPTER (API_PrimPict)
	APIOUTPUTADAPTER (API_CWallPanel)
	APIOUTPUTADAPTER (API_PrimElemRef)
	APIOUTPUTADAPTER (API_PrimHatchBorder)
	APIOUTPUTADAPTER (API_PrimHotspot)

	// API Layout Info
	APIOUTPUTADAPTER (API_LayoutInfo)

	// Categories
	APIOUTPUTADAPTER (API_ElemCategoryID)
	APIOUTPUTADAPTER (API_ElemCategory)
	APIOUTPUTADAPTER (API_ElemCategoryValue)

	// Classifications
	APIOUTPUTADAPTER (API_ClassificationItem)
	APIOUTPUTADAPTER (API_ClassificationSystem)

	// Properties
	APIOUTPUTADAPTER (API_ListVariant)
	APIOUTPUTADAPTER (API_Property)
	APIOUTPUTADAPTER (API_PropertyCollectionType)
	APIOUTPUTADAPTER (API_PropertyMeasureType)
	APIOUTPUTADAPTER (API_PropertyDefaultValue)
	APIOUTPUTADAPTER (API_PropertyDefinition)
	APIOUTPUTADAPTER (API_PropertyDefinitionType)
	APIOUTPUTADAPTER (API_PropertyGroup)
	APIOUTPUTADAPTER (API_PropertyGroupType)
	APIOUTPUTADAPTER (API_PropertyValue)
	APIOUTPUTADAPTER (API_PropertyValueStatus)
	APIOUTPUTADAPTER (API_SingleEnumerationVariant)
	APIOUTPUTADAPTER (API_SingleVariant)
	APIOUTPUTADAPTER (API_Variant)
	APIOUTPUTADAPTER (API_VariantStatus)
	APIOUTPUTADAPTER (API_VariantType)

	// Override
	APIOUTPUTADAPTER (API_OverrideRule)
	APIOUTPUTADAPTER (API_OverrideRuleStyle)
	APIOUTPUTADAPTER (API_OverriddenFillType)
	APIOUTPUTADAPTER (API_OverrideCombination)
	APIOUTPUTADAPTER (API_OverrideStyle)
	APIOUTPUTADAPTER (API_OverriddenSurfaceType)
};

}

#undef APIOUTPUTADAPTER
#undef APIOUTPUTADAPTERMEMO
#endif //__IAPIOUTPUTADAPTERFACTORY_HPP__
