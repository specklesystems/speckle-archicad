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

enum class BUILT_IN_LIBRARY_DLL_EXPORT BuiltInLibPartID {
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
	CableCarrierTeeJunctionLibPartID 			= 34,
	CableCarrierWyeJunctionLibPartID 			= 35,
	CableLadderSegmentLibPartID 				= 36,
	CableTraySegmentLibPartID 					= 37,
	ChangeMarkerLibPartID 						= 38,
	ChillersLibPartID 							= 39,
	ColumnLibPartID 							= 40,
	CommonInteriorElevationMarkerLibPartID 		= 41,
	CornerWindowLibPartID						= 42,
	CornerWindowOpeningLibPartID				= 43,
	CoveringLibPartID 							= 44,
	CurtainWallAccessoryLibPartID 				= 45,
	CurtainWallFrameLibPartID 					= 46,
	CurtainWallJunctionLibPartID 				= 47,
	CurtainWallPanelLibPartID 					= 48,
	CurtainWallLibPartID 						= 49,
	CustomComponentTemplateLibPartID 			= 50,
	CustomDuctFittingLibPartID 					= 51,
	CustomDuctFlowTerminalLibPartID 			= 52,
	CustomDuctInlineFlowDeviceLibPartID 		= 53,
	CustomFlowEquipmentLibPartID 				= 54,
	CustomPipeFittingLibPartID 					= 55,
	CustomPipeFlowTerminalLibPartID 			= 56,
	CustomPipeInlineFlowDeviceLibPartID 		= 57,
	DesignRailingLibPartID 						= 58,
	DesignStairLibPartID 						= 59,
	DetailMarkerLibPartID 						= 60,
	DiscreteAccessoryLibPartID 					= 61,
	DistributionElementLibPartID 				= 62,
	DistributionFlowElementLibPartID 			= 63,
	DocumentationElementLibPartID 				= 64,
	DoorWallLibPartID 							= 65,
	DoorMarkerLibPartID 						= 66,
	DoorOpeningLibPartID 						= 67,
	DormerLibPartID 							= 68,
	DrawingSymbolLibPartID 						= 69,
	DrawingTitleLibPartID 						= 70,
	DuctBendFittingLibPartID 					= 71,
	DuctEndcapFittingLibPartID 					= 72,
	DuctFittingLibPartID 						= 73,
	DuctFlexibleSegmentLibPartID 				= 74,
	DuctFlowTerminalLibPartID 					= 75,
	DuctInlineFlowDeviceLibPartID 				= 76,
	DuctJunctionFittingLibPartID 				= 77,
	DuctNestedJunctionLibPartID 				= 78,
	DuctObstructionFittingLibPartID 			= 79,
	DuctOffsetFittingLibPartID 					= 80,
	DuctRigidSegmentLibPartID 					= 81,
	DuctSegmentLibPartID 						= 82,
	DuctTakeoffJunctionLibPartID 				= 83,
	DuctTeeJunctionLibPartID 					= 84,
	DuctTransitionFittingLibPartID 				= 85,
	DuctVerticalObstructionFittingLibPartID 	= 86,
	DuctWyeJunctionLibPartID 					= 87,
	ElectricalElementLibPartID 					= 88,
	ElementComponentLibPartID					= 89,
	ElevationMarkerLibPartID					= 90,
	FansLibPartID 								= 91,
	FillDefinitionLibPartID 					= 92,
	FlightSideSupportedSteppedLibPartID 		= 93,
	FlightSideSupportedStraightLibPartID 		= 94,
	FlightSideSupportedLibPartID 				= 95,
	FlightStructureLibPartID 					= 96,
	FlightUnderSupportedCantileverLibPartID		= 97,
	FlightUnderSupportedSteppedLibPartID 		= 98,
	FlightUnderSupportedStraightLibPartID 		= 99,
	FlightUnderSupportedLibPartID 				= 100,
	FlowDeviceLibPartID 						= 101,
	FlowEquipmentLibPartID 						= 102,
	FlowFittingLibPartID 						= 103,
	FlowSegmentLibPartID 						= 104,
	FlowTerminalLibPartID 						= 105,
	FootingLibPartID 							= 106,
	FurnishingLibPartID 						= 107,
	GeneralGDLObjectLibPartID 					= 108,
	HeatPumpsLibPartID 							= 109,
	IndividualIEMarkerLibPartID 				= 110,
	IndividualInteriorElevationMarkerLibPartID	= 111,
	InlineFlowDeviceLibPartID					= 112,
	LabelLibPartID 								= 113,
	LandingCantileverSupportedLibPartID 		= 114,
	LandingSideSupportedLibPartID 				= 115,
	LandingStructureLibPartID 					= 116,
	LandingUnderSupportedLibPartID 				= 117,
	LibraryGlobalSettingsLibPartID 				= 118,
	LibraryMasterLibPartID 						= 119,
	LightLibPartID 								= 120,
	MarkerLibPartID 							= 121,
	ModelElementLibPartID 						= 122,
	NumberingSymbolLibPartID 					= 123,
	OpeningLibPartID							= 124,
	OrdinateDimensionLibPartID 					= 125,
	PatchLibPartID 								= 126,
	Patch_TemplateLibPartID						= 127,
	PatternDefinitionLibPartID 					= 128,
	PeopleLibPartID 							= 129,
	PipeBendFittingLibPartID 					= 130,
	PipeCombinationWyeJunctionLibPartID 		= 131,
	PipeCrossJunctionLibPartID 					= 132,
	PipeDoubleCombinationWyeJunctionLibPartID	= 133,
	PipeDoubleSanitaryTeeJunctionLibPartID		= 134,
	PipeDoubleWyeJunctionLibPartID 				= 135,
	PipeFittingLibPartID 						= 136,
	PipeFlowTerminalLibPartID 					= 137,
	PipeInlineFlowDeviceLibPartID 				= 138,
	PipeJunctionFittingLibPartID 				= 139,
	PipeRigidSegmentLibPartID 					= 140,
	PipeSanitaryTeeJunctionLibPartID 			= 141,
	PipeSegmentLibPartID 						= 142,
	PipeTakeoffJunctionLibPartID 				= 143,
	PipeTeeJunctionLibPartID 					= 144,
	PipeTransitionFittingLibPartID 				= 145,
	PipeWyeJunctionLibPartID 					= 146,
	PlantLibPartID 								= 147,
	PointCloudReplacementObjectLibPartID 		= 148,
	PointCloudLibPartID 						= 149,
	PropertyObjectsLibPartID 					= 150,
	Railing3DComponentLibPartID 				= 151,
	RailingEndComponentLibPartID 				= 152,
	RailingPanelComponentLibPartID 				= 153,
	RailingPostComponentLibPartID 				= 154,
	RailingRailComponentLibPartID 				= 155,
	RailingLibPartID 							= 156,
	RampLibPartID 								= 157,
	RiseandRunDescriptionLibPartID 				= 158,
	RiserComponentLibPartID 					= 159,
	RoofComponentLibPartID 						= 160,
	RoofOpeningLibPartID 						= 161,
	RoofLibPartID 								= 162,
	SaveAsLabelTemplateLibPartID 				= 163,
	SchematicRiserLibPartID 					= 164,
	SchematicTreadLibPartID 					= 165,
	SectionMarkerLibPartID 						= 166,
	SectionElevationMarkerLibPartID 			= 167,
	SimpleDoorOpeningLibPartID 					= 168,
	SimpleSkylightOpeningLibPartID 				= 169,
	SimpleWindowOpeningLibPartID				= 170,
	SkylightMarkerLibPartID 					= 171,
	SkylightLibPartID 							= 172,
	SlabOpeningLibPartID 						= 173,
	SlabLibPartID 								= 174,
	SolarCollectorsLibPartID 					= 175,
	SolarPVPanelsLibPartID 						= 176,
	SportFieldLibPartID 						= 177,
	Stair2DComponentLibPartID 					= 178,
	Stair3DComponentLibPartID 					= 179,
	StairGridSymbolLibPartID 					= 180,
	StairLibraryGlobalLibPartID 				= 181,
	StairLibPartID 								= 182,
	StoryMarkerLibPartID 						= 183,
	StreetFurnitureLibPartID 					= 184,
	StructureLibPartID 							= 185,
	SurfaceDefinitionLibPartID 					= 186,
	TrafficLibPartID 							= 187,
	TransportElementLibPartID 					= 188,
	TreadComponentLibPartID 					= 189,
	TrussMakerObjectLibPartID 					= 190,
	UpandDownTextLibPartID 						= 191,
	WalkingLineSymbolLibPartID 					= 192,
	WallEndLibPartID 							= 193,
	WallExtraWindowLibPartID 					= 194,
	WallOpeningLibPartID 						= 195,
	WallLibPartID 								= 196,
	WaterHeatersLibPartID 						= 197,
	WindTurbinesLibPartID 						= 198,
	WindowWallLibPartID 						= 199,
	WindowMarkerLibPartID 						= 200,
	WindowOpeningLibPartID 						= 201,
	WindowDoorSkylightMarkerLibPartID 			= 202,
	WorksheetMarkerLibPartID 					= 203,
	ZoneStampLibPartID							= 204,
	OpeningSymbolLibPartID						= 205,
	CustomCableCarrierFittingLibPartID			= 206
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
