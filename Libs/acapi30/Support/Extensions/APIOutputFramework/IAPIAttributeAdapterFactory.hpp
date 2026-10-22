#ifndef __IAPIATTRIBUTEADAPTERFACTORY_HPP__
#define __IAPIATTRIBUTEADAPTERFACTORY_HPP__

#include "IAttributeProxy.hpp"

#define APIATTRIBADAPTER(type)																				\
virtual IAPIAttributeAdapter<type>* GetAdapter (const type& forType, const API_DatabaseInfo& dbInfo) = 0;

#define APIATTRIBADAPTERMEMO(type)																			\
virtual IAPIAttributeAdapter<type>* GetAdapter (const type& forType, const API_DatabaseInfo& dbInfo, 		\
												const API_ElementMemo* withMemo = nullptr) = 0;

namespace GSAPI {

// predeclarations
template <typename APIType>
class IAPIAttributeAdapter;


/**
 * @interface
 */
class IAPIAttributeAdapterFactory {
protected:
    IAttributeProxy& attributeProxy;
	bool			 managedAdapters;	// factory keeps track and deletes the adapters or not

public:
    IAPIAttributeAdapterFactory (IAttributeProxy& proxy, bool keepsTrackOfAdapters = false) 
    	: attributeProxy (proxy), managedAdapters (keepsTrackOfAdapters) { }

	IAPIAttributeAdapterFactory (const IAPIAttributeAdapterFactory& factory) 
		: attributeProxy (factory.attributeProxy), managedAdapters (factory.managedAdapters) { }

	virtual ~IAPIAttributeAdapterFactory ();

    IAPIAttributeAdapterFactory& operator= (const IAPIAttributeAdapterFactory& factory) 
    { 
    	attributeProxy = factory.attributeProxy; 
    	managedAdapters = factory.managedAdapters; 
    	return (*this); 
    }

	bool GetManagedAdapters () 
	{ 
		return managedAdapters; 
	}

	template <typename APIType>
	IAPIAttributeAdapter<APIType>*	GetTypeAdapter (const APIType&					forType,
													const API_DatabaseInfo&			dbInfo,
													const API_ElementMemo*			withMemo)	
	{ 
		return GetAdapter (forType, dbInfo, withMemo); 
	}

	template <typename APIType>
	IAPIAttributeAdapter<APIType>*	GetTypeAdapter (const APIType&					forType,
													const API_DatabaseInfo&			dbInfo)		
	{ 
		return GetAdapter (forType, dbInfo);
	}

	// API Element Types
    APIATTRIBADAPTERMEMO (API_Element)
	APIATTRIBADAPTER (API_ElemType)
	APIATTRIBADAPTER (API_BeamSegmentType)
	APIATTRIBADAPTER (API_ColumnSegmentType)
	APIATTRIBADAPTER (API_Elem_Head)
	APIATTRIBADAPTER (API_WallType)
	APIATTRIBADAPTER (API_StoryVisibility)
	APIATTRIBADAPTER (API_LinkToSettings)
	APIATTRIBADAPTER (API_Coord)
	APIATTRIBADAPTER (API_Polygon)
	APIATTRIBADAPTER (API_ColumnType)
	APIATTRIBADAPTER (API_BeamType)
	APIATTRIBADAPTER (API_WindowType)
	APIATTRIBADAPTER (API_SkylightType)
	APIATTRIBADAPTER (API_OpeningBaseType)
	APIATTRIBADAPTER (API_VerticalLink)
	APIATTRIBADAPTER (API_ObjectType)
	APIATTRIBADAPTER (API_RGBColor)
	APIATTRIBADAPTER (API_RGBAColor)
	APIATTRIBADAPTER (API_SlabType)
	APIATTRIBADAPTER (API_HatchOrientation)
	APIATTRIBADAPTER (API_CoverFillTransformation)
	APIATTRIBADAPTER (API_RoofType)
	APIATTRIBADAPTER (API_PlaneRoofData)
	APIATTRIBADAPTER (API_PolyRoofData)
	APIATTRIBADAPTER (API_Sector)
	APIATTRIBADAPTER (API_RoofSegmentData)
	APIATTRIBADAPTER (API_ShellContourData)
	APIATTRIBADAPTER (API_ShellBaseType)
	APIATTRIBADAPTER (API_ShellType)
	APIATTRIBADAPTER (API_ExtrudedShellData)
	APIATTRIBADAPTER (API_RevolvedShellData)
	APIATTRIBADAPTER (API_RuledShellData)
	APIATTRIBADAPTER (API_ContourEdgeData)
	APIATTRIBADAPTER (API_LocalCoordsData)
	APIATTRIBADAPTER (API_LocalCoordsType)
	APIATTRIBADAPTER (API_PivotPolyEdgeData)
	APIATTRIBADAPTER (API_ShellShapeData)
	APIATTRIBADAPTER (API_MorphType)
	APIATTRIBADAPTER (API_MeshType)
	APIATTRIBADAPTER (API_MeshLevel)
	APIATTRIBADAPTER (API_DimensionType)
	APIATTRIBADAPTER (API_NoteType)
	APIATTRIBADAPTER (API_DimBase)
	APIATTRIBADAPTER (API_Base)
	APIATTRIBADAPTER (API_RadialDimensionType)
	APIATTRIBADAPTER (API_LevelDimensionType)
	APIATTRIBADAPTER (API_AngleDimensionType)
	APIATTRIBADAPTER (API_TextType)
	APIATTRIBADAPTER (API_LabelType)
	APIATTRIBADAPTER (API_ZoneType)
	APIATTRIBADAPTER (API_HatchType)
	APIATTRIBADAPTER (API_LineType)
	APIATTRIBADAPTER (API_PolyLineType)
	APIATTRIBADAPTER (API_ArcType)
	APIATTRIBADAPTER (API_SplineType)
	APIATTRIBADAPTER (API_HotspotType)
	APIATTRIBADAPTER (API_PictureType)
	APIATTRIBADAPTER (API_Box)
	APIATTRIBADAPTER (API_CutPlaneType)
	APIATTRIBADAPTER (API_InteriorElevationType)
	APIATTRIBADAPTER (API_DatabaseUnId)
	APIATTRIBADAPTER (API_CameraType)
	APIATTRIBADAPTER (API_PerspCamPars)
	APIATTRIBADAPTER (API_PerspPars)
	APIATTRIBADAPTER (API_CamSetType)
	APIATTRIBADAPTER (API_DrawingType)
	APIATTRIBADAPTER (API_SectElemType)
	APIATTRIBADAPTER (API_DetailType)
	APIATTRIBADAPTER (API_ChangeMarkerType)
	// APIATTRIBADAPTER (API_WorksheetType) // API_WorksheetType == API_DetailType
	APIATTRIBADAPTER (API_HotlinkType)
	APIATTRIBADAPTER (API_CurtainWallType)
	APIATTRIBADAPTER (API_CWSegmentType)
	APIATTRIBADAPTER (API_CWFrameType)
	APIATTRIBADAPTER (API_CWPanelType)
	APIATTRIBADAPTER (API_CWJunctionType)
	APIATTRIBADAPTER (API_CWAccessoryType)
	APIATTRIBADAPTER (API_StairType)
	APIATTRIBADAPTER (API_StairRiserType)
	APIATTRIBADAPTER (API_StairTreadType)
	APIATTRIBADAPTER (API_StairStructureType)
	APIATTRIBADAPTER (API_StairMonolithStructureSymbolData)
	APIATTRIBADAPTER (API_StairStructureComponentSettingsVisibilityOnStory)
	APIATTRIBADAPTER (API_StairStructureComponentSettingsVisibility)
	APIATTRIBADAPTER (API_RailingType)
	APIATTRIBADAPTER (API_RailingSegmentType)
	APIATTRIBADAPTER (API_RailingRailEndType)
	APIATTRIBADAPTER (API_RailingRailConnectionType)
	APIATTRIBADAPTER (API_RailingPatternType)
	APIATTRIBADAPTER (API_RailingNodeType)
	APIATTRIBADAPTER (API_RailingToprailType)
	APIATTRIBADAPTER (API_RailingHandrailType)
	APIATTRIBADAPTER (API_RailingRailType)
	APIATTRIBADAPTER (API_RailingFinishType)
	APIATTRIBADAPTER (API_RailingPostType)
	APIATTRIBADAPTER (API_RailingInnerPostType)
	APIATTRIBADAPTER (API_RailingBalusterType)
	APIATTRIBADAPTER (API_RailingBalusterSetType)
	APIATTRIBADAPTER (API_RailingPanelType)
	APIATTRIBADAPTER (API_AxonoPars)
	APIATTRIBADAPTER (API_Tranmat)
	APIATTRIBADAPTER (API_CutPlaneMarkerShowType)
	APIATTRIBADAPTER (API_CWAccessoryCategoryID)
	APIATTRIBADAPTER (API_CWFrameObjectTypeID)
	APIATTRIBADAPTER (API_CWJunctionCategoryID)
	APIATTRIBADAPTER (API_CWPanelObjectTypeID)
	APIATTRIBADAPTER (API_CWSegmentCategoryID)
	APIATTRIBADAPTER (API_CWSegmentGridOrigPosTypeID)
	APIATTRIBADAPTER (API_CWSegmentTypeID)
	APIATTRIBADAPTER (API_CWBoundaryFramePosID)
	APIATTRIBADAPTER (API_CWPlacementID)
	APIATTRIBADAPTER (API_GridMeshHead)
	APIATTRIBADAPTER (API_GridMeshVertex)
	APIATTRIBADAPTER (API_GridMeshEdge)
	APIATTRIBADAPTER (API_GridEdgeInfo)
	APIATTRIBADAPTER (API_GridMeshLine)
	APIATTRIBADAPTER (API_GridMeshPolygon)
	APIATTRIBADAPTER (API_Interval)
	APIATTRIBADAPTER (API_SubElementType)
	APIATTRIBADAPTER (API_SubElemFlagType)
	APIATTRIBADAPTER (API_Plane3D)
	APIATTRIBADAPTER (API_ActTranPars)
	APIATTRIBADAPTER (API_Region)
	APIATTRIBADAPTER (API_SelectionInfo)

	// API Element Memo Types
	APIATTRIBADAPTER (API_ElementMemo)
	APIATTRIBADAPTER (API_AssemblySegmentData)
	APIATTRIBADAPTER (API_PolyArc)
	APIATTRIBADAPTER (API_AddParType)
	APIATTRIBADAPTER (API_Gable)
	APIATTRIBADAPTER (API_EdgeTrim)
	APIATTRIBADAPTER (API_MeshLevelCoord)
	APIATTRIBADAPTER (API_Wrapping)
	APIATTRIBADAPTER (API_Coord3D)
	APIATTRIBADAPTER (API_DimElem)
	APIATTRIBADAPTER (API_SplineDir)
	APIATTRIBADAPTER (API_Beam_Hole)
	APIATTRIBADAPTER (API_LinkType)
	APIATTRIBADAPTER (API_ParagraphType)
	APIATTRIBADAPTER (API_TabType)
	APIATTRIBADAPTER (API_SectionSegment)
	APIATTRIBADAPTER (API_GridMesh)
	APIATTRIBADAPTER (API_CWSegmentPatternCellData)
	APIATTRIBADAPTER (API_CWSegmentPatternData)
	APIATTRIBADAPTER (API_CWContourData)

	// Primitive Element Types
	APIATTRIBADAPTERMEMO (GSAPI::PrimElement)
	APIATTRIBADAPTER (API_Prim_Head)
	APIATTRIBADAPTER (API_PrimPoint)
	APIATTRIBADAPTER (API_PrimLine)
	APIATTRIBADAPTER (API_PrimArc)
	APIATTRIBADAPTER (API_PrimText)
	APIATTRIBADAPTER (API_PrimPLine)
	APIATTRIBADAPTER (API_PrimTri)
	APIATTRIBADAPTER (API_PrimPoly)
	APIATTRIBADAPTER (API_PrimPict)
	APIATTRIBADAPTER (API_PrimHatchBorder)
	APIATTRIBADAPTER (API_PrimHotspot)

	// Other API Types
	APIATTRIBADAPTER (API_GDLModelViewOptions)

	// Categories
	APIATTRIBADAPTER (API_ElemCategory)
	APIATTRIBADAPTER (API_ElemCategoryValue)

	// Properties
	APIATTRIBADAPTER (API_ListVariant)
	APIATTRIBADAPTER (API_Property)
	APIATTRIBADAPTER (API_PropertyDefaultValue)
	APIATTRIBADAPTER (API_PropertyDefinition)
	APIATTRIBADAPTER (API_PropertyValue)
	APIATTRIBADAPTER (API_SingleEnumerationVariant)
	APIATTRIBADAPTER (API_SingleVariant)
	APIATTRIBADAPTER (API_Variant)

	// Override
	APIATTRIBADAPTER (API_OverrideRule)
	APIATTRIBADAPTER (API_OverrideRuleStyle)
	APIATTRIBADAPTER (API_OverrideStyle)
};

}	// namespace GSAPI

#undef APIATTRIBADAPTER
#undef APIATTRIBADAPTERMEMO
#endif //__IAPIATTRIBUTEADAPTERFACTORY_HPP__
