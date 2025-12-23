// *****************************************************************************
//
// Declaration of PermissionID
//
// Module:			TWRoot
// Namespace:		TWCB
// Contact person:	TP
//
// *****************************************************************************

#ifndef TWPERMISSIONIDS_H
#define TWPERMISSIONIDS_H


#pragma once


namespace TWCB {

// ----------------------------------------------------------------------

const short FirstACPermissionID			= 1001;		// PERMISSION_1
const short LastACPermissionID			= 1105;		// PERMISSION_105

const short FirstManagementPermissionID	= 2001;		// MPERMISSION_1
const short LastManagementPermissionID	= 2013;		// MPERMISSION_13

enum PermissionID {
	NoPermission									= 0,

	LineTypesCreate									= 1001,		// PERMISSION_1
	LineTypesDeleteModify							= 1002,		// PERMISSION_2
	FillTypesCreate									= 1003,		// PERMISSION_3
	FillTypesDeleteModify							= 1004,		// PERMISSION_4
	CompositesCreate								= 1005,		// PERMISSION_5
	CompositesDeleteModify							= 1006,		// PERMISSION_6
	PenSetsCreate									= 1007,		// PERMISSION_7
	PenSetsDeleteModify								= 1008,		// PERMISSION_8
	ProfilesCreate									= 1009,		// PERMISSION_9
	ProfilesDeleteModify							= 1010,		// PERMISSION_10
	CitiesCreate									= 1011,		// PERMISSION_11
	CitiesDeleteModify								= 1012,		// PERMISSION_12
	MarkupStylesCreate								= 1013,		// PERMISSION_13
	MarkupStylesDeleteModify						= 1014,		// PERMISSION_14
	ZoneCategoriesCreate							= 1015,		// PERMISSION_15
	ZoneCategoriesDeleteModify						= 1016,		// PERMISSION_16
	LayersCreate									= 1017,		// PERMISSION_17
	LayersDeleteModify								= 1018,		// PERMISSION_18
	MaterialsCreate									= 1019,		// PERMISSION_19
	MaterialsDeleteModify							= 1020,		// PERMISSION_20
	FavoritesCreate									= 1021,		// PERMISSION_21
	FavoritesDeleteModify							= 1022,		// PERMISSION_22
	PublicFindSelectCriteriaCreate					= 1023,		// PERMISSION_23
	PublicFindSelectCriteriaDeleteModify			= 1024,		// PERMISSION_24
	MasterLayoutsCreate								= 1025,		// PERMISSION_25
	MasterLayoutsDeleteModify						= 1026,		// PERMISSION_26
	ModelViewOptionsCreate							= 1027,		// PERMISSION_27
	ModelViewOptionsDeleteModify					= 1028,		// PERMISSION_28
	ProjectPreferences								= 1029,		// PERMISSION_29
	ProjectInfo										= 1030,		// PERMISSION_30
	StoreyCreate									= 1031,		// PERMISSION_31
	StoreyDeleteModify								= 1032,		// PERMISSION_32
	ViewsAndFoldersCreate							= 1033,		// PERMISSION_33
	ViewsAndFoldersDeleteModify						= 1034,		// PERMISSION_34
	LayoutsAndSubsetsCreate							= 1035,		// PERMISSION_35
	LayoutsAndSubsetsDeleteModify					= 1036,		// PERMISSION_36
	ProjectNotesManage								= 1037,		// PERMISSION_37
	DesignToolElements								= 1038,		// PERMISSION_38
	GridToolElements								= 1039,		// PERMISSION_39
	DocumentToolElements							= 1040,		// PERMISSION_40
	ExternalDrawingsManage							= 1041,		// PERMISSION_41
	IFCExternalPropertiesManage						= 1042,		// PERMISSION_42
	SchedulesAndIndexesCreate						= 1043,		// PERMISSION_43
	SchedulesAndIndexesDeleteModify					= 1044,		// PERMISSION_44
	SetUpListSchemesManage							= 1045,		// PERMISSION_45
	PublisherSetsCreate								= 1046,		// PERMISSION_46
	PublisherSetsDeleteModify						= 1047,		// PERMISSION_47
	PublisherSetsPublish							= 1048,		// PERMISSION_48
	ViewpointManage									= 1049,		// PERMISSION_49
	MarkupEntryCreate								= 1050,		// PERMISSION_50
	MarkupEntryDeleteModify							= 1051,		// PERMISSION_51
	XrefInstances									= 1052,		// PERMISSION_52
	HotlinkInstances								= 1053,		// PERMISSION_53
	HotlinkAndXrefManage							= 1054,		// PERMISSION_54
	LibraryAddRemove								= 1055,		// PERMISSION_55
	LibraryPartCreate								= 1056,		// PERMISSION_56
	LibraryPartDeleteModify							= 1057,		// PERMISSION_57
	AddOnsSetupManage								= 1058,		// PERMISSION_58
	MEPSystemCreate									= 1059,		// PERMISSION_59
	MEPSystemDeleteModify							= 1060,		// PERMISSION_60
	ProjectPreviewManage							= 1061,		// PERMISSION_61
	OperationProfilesCreate							= 1062,		// PERMISSION_62
	OperationProfilesDeleteModify					= 1063,		// PERMISSION_63
	RenovationFilterCreate							= 1064,		// PERMISSION_64
	RenovationFilterDeleteModify					= 1065,		// PERMISSION_65
	RenovationOverrideStyleManage					= 1066,		// PERMISSION_66
	PLNBackupCreate									= 1067,		// PERMISSION_67
	ProjectLocation									= 1068,		// PERMISSION_68
	BuildingMaterialsCreate							= 1069,		// PERMISSION_69
	BuildingMaterialsDeleteModify					= 1070,		// PERMISSION_70
	SaveAsPLNPLAMODGSM								= 1071,		// PERMISSION_71
	SaveAsDXFDWG									= 1072,		// PERMISSION_72
	SaveAsIFC										= 1073,		// PERMISSION_73
	UpgradeToLaterArchiCADBuild						= 1074,		// PERMISSION_74
	RenderingSceneCreate							= 1075,		// PERMISSION_75
	RenderingSceneDeleteModify						= 1076,		// PERMISSION_76
	ChangeCreate									= 1077,		// PERMISSION_77
	ChangeDeleteModify								= 1078,		// PERMISSION_78
	IssueManage										= 1079,		// PERMISSION_79
	IssueModifyHistory								= 1080,		// PERMISSION_80
	PropertyAndClassificationCreate					= 1081,		// PERMISSION_81
	PropertyAndClassificationDeleteModify			= 1082,		// PERMISSION_82
	GraphicOverridesCreate							= 1083,		// PERMISSION_83
	GraphicOverridesDeleteModify					= 1084,		// PERMISSION_84
	ElementTransferSettingsCreate					= 1085,		// PERMISSION_85
	ElementTransferSettingsDeleteModify				= 1086,		// PERMISSION_86
	D3WindowStyleCreate								= 1087,		// PERMISSION_87
	D3WindowStyleDeleteModify						= 1088,		// PERMISSION_88
	IFCPreferencesManage							= 1089,		// PERMISSION_89
	IssueCreateModify								= 1090,		// PERMISSION_90
	IssueDelete										= 1091,		// PERMISSION_91
	IssueTagManage									= 1092,		// PERMISSION_92
	StructuralAnalyticalToolElements				= 1093,		// PERMISSION_93
	StructuralAnalyticalModelGenerationRulesManage	= 1094,		// PERMISSION_94
	SAFTranslatorsManage							= 1095,		// PERMISSION_95
	SaveAsSAF										= 1096,		// PERMISSION_96
	SaveAsRVT										= 1097,		// PERMISSION_97
	StructuralAnalyticalLoadCombinationCreate		= 1098,		// PERMISSION_98
	StructuralAnalyticalLoadCombinationDeleteModify	= 1099,		// PERMISSION_99
	DesignOptionsCreate								= 1100,		// PERMISSION_100
	DesignOptionsDeleteModify						= 1101,		// PERMISSION_101
	MEPToolElements									= 1102,		// PERMISSION_102		
	MEPPreferences									= 1103,		// PERMISSION_103		
	KeynotesCreate									= 1104,		// PERMISSION_104		
	KeynotesDeleteModify							= 1105,		// PERMISSION_105	

	View											= 2001,		// MPERMISSION_1
	Modify											= 2002,		// MPERMISSION_2
	ViewAccess										= 2003,		// MPERMISSION_3
	ModifyAccess									= 2004,		// MPERMISSION_4
	ModifyContent									= 2005,		// MPERMISSION_5
	DeleteContent									= 2006,		// MPERMISSION_6
	EnableUser										= 2007,		// MPERMISSION_7
	LockProject										= 2008,		// MPERMISSION_8
	StartServer										= 2009,		// MPERMISSION_9
	ModifyModelServerContent						= 2010,		// MPERMISSION_10
	ManageLicenses									= 2011,		// MPERMISSION_11
	ViewTimesheet									= 2012,		// MPERMISSION_12
	ViewActivities									= 2013		// MPERMISSION_13
};

} // namespace TWCB

#endif
