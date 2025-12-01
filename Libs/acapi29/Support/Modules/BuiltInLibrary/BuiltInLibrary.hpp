#ifndef BUILT_IN_LIBRARY_HPP
#define BUILT_IN_LIBRARY_HPP

#include "BuiltInLibraryExport.hpp"
#include "Definitions.hpp"
#include "HashTable.hpp"
#include "Location.hpp"
#include "FileSystem.hpp"
#include "Ref.hpp"
#include "GSUnID.hpp"

#pragma once

namespace BL {

enum class BuiltInLibPartID {
	INVALIDERRORID								= 0,
	AirHandlersLibPartID 						= 1,
	AnimalLibPartID 							= 2,
	AttributeDefinitionLibPartID 				= 3,
	BasicZoneStampLibPartID 					= 4,
	BeamLibPartID 								= 5,
	BedsLibPartID 								= 6,
	BoilersLibPartID							= 7,
	BreakMarkSymbolLibPartID 					= 8,
	BuildingElementLibPartID 					= 9,
	BuiltInBreakMarkLibPartID 					= 10,
	BuiltinButtGlazedFrameLibPartID 			= 11,
	BuiltinChangeMarkerLibPartID 				= 12,
	BuiltinCWPanelLibPartID 					= 13,
	BuiltInDescriptionLibPartID 				= 14,
	BuiltinDetailMarkerLibPartID 				= 15,
	BuiltinDrawingTitleLibPartID 				= 16,
	BuiltinElevationMarkerLibPartID 			= 17,
	BuiltinFrameLibPartID 						= 18,
	BuiltInNumberingLibPartID 					= 19,
	BuiltInRiserLibPartID 						= 20,
	BuiltinSectionMarkerLibPartID 				= 21,
	BuiltInStairGridLibPartID 					= 22,
	BuiltinStoryMarkerLibPartID 				= 23,
	BuiltInTreadLibPartID 						= 24,
	BuiltInUpDownTextLibPartID 					= 25,
	BuiltInWalkingLineLibPartID 				= 26,
	BuiltinWorksheetMarkerLibPartID 			= 27,
	CableCarrierBendFittingLibPartID 			= 28,
	CableCarrierCrossJunctionLibPartID 			= 29,
	CableCarrierFittingLibPartID 				= 30,
	CableCarrierJunctionFittingLibPartID 		= 31,
	CableCarrierReducerFittingLibPartID 		= 32,
	CableCarrierSegmentLibPartID 				= 33,
	CableCarrierBranchJunctionLibPartID 		= 34,
	CableLadderSegmentLibPartID 				= 35,
	CableTraySegmentLibPartID 					= 36,
	ChangeMarkerLibPartID 						= 37,
	ChillersLibPartID 							= 38,
	ColumnLibPartID 							= 39,
	CommonInteriorElevationMarkerLibPartID 		= 40,
	CornerWindowLibPartID						= 41,
	CornerWindowOpeningLibPartID				= 42,
	CoveringLibPartID 							= 43,
	CurtainWallAccessoryLibPartID 				= 44,
	CurtainWallFrameLibPartID 					= 45,
	CurtainWallJunctionLibPartID 				= 46,
	CurtainWallPanelLibPartID 					= 47,
	CurtainWallLibPartID 						= 48,
	CustomComponentTemplateLibPartID 			= 49,
	CustomDuctFittingLibPartID 					= 50,
	CustomDuctFlowTerminalLibPartID 			= 51,
	CustomDuctInlineFlowDeviceLibPartID 		= 52,
	CustomFlowEquipmentLibPartID 				= 53,
	CustomPipeFittingLibPartID 					= 54,
	CustomPipeFlowTerminalLibPartID 			= 55,
	CustomPipeInlineFlowDeviceLibPartID 		= 56,
	DesignRailingLibPartID 						= 57,
	DesignStairLibPartID 						= 58,
	DetailMarkerLibPartID 						= 59,
	DiscreteAccessoryLibPartID 					= 60,
	DistributionElementLibPartID 				= 61,
	DistributionFlowElementLibPartID 			= 62,
	DocumentationElementLibPartID 				= 63,
	DoorWallLibPartID 							= 64,
	DoorMarkerLibPartID 						= 65,
	DoorOpeningLibPartID 						= 66,
	DormerLibPartID 							= 67,
	DrawingSymbolLibPartID 						= 68,
	DrawingTitleLibPartID 						= 69,
	DuctBendFittingLibPartID 					= 70,
	DuctEndcapFittingLibPartID 					= 71,
	DuctFittingLibPartID 						= 72,
	DuctFlexibleSegmentLibPartID 				= 73,
	DuctFlowTerminalLibPartID 					= 74,
	DuctInlineFlowDeviceLibPartID 				= 75,
	DuctJunctionFittingLibPartID 				= 76,
	DuctNestedJunctionLibPartID 				= 77,
	DuctObstructionFittingLibPartID 			= 78,
	DuctOffsetFittingLibPartID 					= 79,
	DuctRigidSegmentLibPartID 					= 80,
	DuctSegmentLibPartID 						= 81,
	DuctTakeoffJunctionLibPartID 				= 82,
	DuctBranchJunctionLibPartID 				= 83,
	DuctTransitionFittingLibPartID 				= 84,
	DuctVerticalObstructionFittingLibPartID 	= 85,
	ElectricalElementLibPartID 					= 86,
	ElementComponentLibPartID					= 87,
	ElevationMarkerLibPartID					= 88,
	FansLibPartID 								= 89,
	FillDefinitionLibPartID 					= 90,
	FlightSideSupportedSteppedLibPartID 		= 91,
	FlightSideSupportedStraightLibPartID 		= 92,
	FlightSideSupportedLibPartID 				= 93,
	FlightStructureLibPartID 					= 94,
	FlightUnderSupportedCantileverLibPartID		= 95,
	FlightUnderSupportedSteppedLibPartID 		= 96,
	FlightUnderSupportedStraightLibPartID 		= 97,
	FlightUnderSupportedLibPartID 				= 98,
	FlowDeviceLibPartID 						= 99,
	FlowEquipmentLibPartID 						= 100,
	FlowFittingLibPartID 						= 101,
	FlowSegmentLibPartID 						= 102,
	FlowTerminalLibPartID 						= 103,
	FootingLibPartID 							= 104,
	FurnishingLibPartID 						= 105,
	GeneralGDLObjectLibPartID 					= 106,
	HeatPumpsLibPartID 							= 107,
	IndividualIEMarkerLibPartID 				= 108,
	IndividualInteriorElevationMarkerLibPartID	= 109,
	InlineFlowDeviceLibPartID					= 110,
	LabelLibPartID 								= 111,
	LandingCantileverSupportedLibPartID 		= 112,
	LandingSideSupportedLibPartID 				= 113,
	LandingStructureLibPartID 					= 114,
	LandingUnderSupportedLibPartID 				= 115,
	LibraryGlobalSettingsLibPartID 				= 116,
	LibraryMasterLibPartID 						= 117,
	LightLibPartID 								= 118,
	MarkerLibPartID 							= 119,
	ModelElementLibPartID 						= 120,
	NumberingSymbolLibPartID 					= 121,
	OpeningLibPartID							= 122,
	OrdinateDimensionLibPartID 					= 123,
	PatchLibPartID 								= 124,
	Patch_TemplateLibPartID						= 125,
	PatternDefinitionLibPartID 					= 126,
	PeopleLibPartID 							= 127,
	PipeBendFittingLibPartID 					= 128,
	PipeCombinationWyeJunctionLibPartID 		= 129,
	PipeCrossJunctionLibPartID 					= 130,
	PipeDoubleCombinationWyeJunctionLibPartID	= 131,
	PipeDoubleSanitaryTeeJunctionLibPartID		= 132,
	PipeDoubleWyeJunctionLibPartID 				= 133,
	PipeFittingLibPartID 						= 134,
	PipeFlowTerminalLibPartID 					= 135,
	PipeInlineFlowDeviceLibPartID 				= 136,
	PipeJunctionFittingLibPartID 				= 137,
	PipeRigidSegmentLibPartID 					= 138,
	PipeSanitaryTeeJunctionLibPartID 			= 139,
	PipeSegmentLibPartID 						= 140,
	PipeTakeoffJunctionLibPartID 				= 141,
	PipeBranchJunctionLibPartID 				= 142,
	PipeTransitionFittingLibPartID 				= 143,
	PlantLibPartID 								= 144,
	PointCloudReplacementObjectLibPartID 		= 145,
	PointCloudLibPartID 						= 146,
	PropertyObjectsLibPartID 					= 147,
	Railing3DComponentLibPartID 				= 148,
	RailingEndComponentLibPartID 				= 149,
	RailingPanelComponentLibPartID 				= 150,
	RailingPostComponentLibPartID 				= 151,
	RailingRailComponentLibPartID 				= 152,
	RailingLibPartID 							= 153,
	RampLibPartID 								= 154,
	RiseandRunDescriptionLibPartID 				= 155,
	RiserComponentLibPartID 					= 156,
	RoofComponentLibPartID 						= 157,
	RoofOpeningLibPartID 						= 158,
	RoofLibPartID 								= 159,
	SaveAsLabelTemplateLibPartID 				= 160,
	SchematicRiserLibPartID 					= 161,
	SchematicTreadLibPartID 					= 162,
	SectionMarkerLibPartID 						= 163,
	SectionElevationMarkerLibPartID 			= 164,
	SimpleDoorOpeningLibPartID 					= 165,
	SimpleSkylightOpeningLibPartID 				= 166,
	SimpleWindowOpeningLibPartID				= 167,
	SkylightMarkerLibPartID 					= 168,
	SkylightLibPartID 							= 169,
	SlabOpeningLibPartID 						= 170,
	SlabLibPartID 								= 171,
	SolarCollectorsLibPartID 					= 172,
	SolarPVPanelsLibPartID 						= 173,
	SportFieldLibPartID 						= 174,
	Stair2DComponentLibPartID 					= 175,
	Stair3DComponentLibPartID 					= 176,
	StairGridSymbolLibPartID 					= 177,
	StairLibraryGlobalLibPartID 				= 178,
	StairLibPartID 								= 179,
	StoryMarkerLibPartID 						= 180,
	StreetFurnitureLibPartID 					= 181,
	StructureLibPartID 							= 182,
	SurfaceDefinitionLibPartID 					= 183,
	TrafficLibPartID 							= 184,
	TransportElementLibPartID 					= 185,
	TreadComponentLibPartID 					= 186,
	TrussMakerObjectLibPartID 					= 187,
	UpandDownTextLibPartID 						= 188,
	WalkingLineSymbolLibPartID 					= 189,
	WallEndLibPartID 							= 190,
	WallExtraWindowLibPartID 					= 191,
	WallOpeningLibPartID 						= 192,
	WallLibPartID 								= 193,
	WaterHeatersLibPartID 						= 194,
	WindTurbinesLibPartID 						= 195,
	WindowWallLibPartID 						= 196,
	WindowMarkerLibPartID 						= 197,
	WindowOpeningLibPartID 						= 198,
	WindowDoorSkylightMarkerLibPartID 			= 199,
	WorksheetMarkerLibPartID 					= 200,
	ZoneStampLibPartID							= 201,
	OpeningSymbolLibPartID						= 202,
	CustomCableCarrierFittingLibPartID			= 203,
	KeynoteLegendsLibPartID						= 204,
	PipeFlexibleSegmentLibPartID				= 205,
};


class BUILT_IN_LIBRARY_DLL_EXPORT BuiltInLibraryMainGuidContainer {
public:
	enum class InitializationResult {
		AlreadyInitialized,
		Success,
		Error
	};

private:
	GS::HashTable<Int32, GS::Guid>						mainGuidTable;
	bool												xmlLoaded;

private:
	BuiltInLibraryMainGuidContainer (const IO::Location* customXmlLocation, InitializationResult* initializationResult);

	GSErrCode										ReadMainGuidsFromXML (const IO::Location& xmlLocation);

	static const BuiltInLibraryMainGuidContainer&	GetInitializedInstance (const IO::Location* xmlLocation, InitializationResult* initializationResult);

public:
	virtual ~BuiltInLibraryMainGuidContainer ();


	static IO::Location								GetDefaultXMLLocation ();
	static IO::Location								GetDefaultXMLFolder ();

	static InitializationResult						Initialize (const IO::Location* customXmlLocation);
	static const BuiltInLibraryMainGuidContainer&	GetInstance ();

	
	GS::Guid										GetMainGuid (const BuiltInLibPartID& libPartID) const;
	GS::UnID										GetUnIDWithNullRevGuid (const BuiltInLibPartID& libPartID) const;
	
	bool											IsXMLLoaded () const { return xmlLoaded; }
};

}

#endif
