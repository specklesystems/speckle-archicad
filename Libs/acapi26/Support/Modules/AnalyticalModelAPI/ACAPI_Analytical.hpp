#ifndef GS_ACAPI_ANALYTICAL_HPP
#define GS_ACAPI_ANALYTICAL_HPP

#include "AnalyticalModelAPIExport.hpp"

#include "APIdefs_AnalyticalModel.h"
#include "APIdefs_Registration.h"


extern "C" {


ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetCurrentAnalyticalModel	(const API_Token&	token,
																			 API_Guid&			amGuid);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_UpdateAnalyticalModel		(const API_Token&	token,
																			 const API_Guid&	amGuid);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalModelVariation	(const API_Token&				token,
																			 const API_Guid&				amGuid,
																			 API_AnalyticalModelVariation&	api_modelVariation);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalModel			(const API_Token&						token,
																			 const API_AnalyticalModelVariation&	api_modelVariation,
																			 API_Guid&								amGuid);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetGenerationSettingsToNoRule (const API_Token&	token);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetVisibilitySettings		(const API_Token&			token,
																			 API_AM_VisibilitySettings&	api_visibilitySettings);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetVisibilitySettings		(const API_Token&				token,
																			 const API_AM_VisibilitySettings&	api_visibilitySettings);

	// Release

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalRelease	(const API_Token&					token,
																	 const API_Guid&					amGuid,
																	 const API_Guid&					elemGuid,
																	 API_AnalyticalReleaseType&			api_analyticalRelease);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetAnalyticalRelease	(const API_Token&					token,
																	 const API_Guid&					elemGuid,
																	 const API_AnalyticalReleaseType&	api_analyticalRelease);


	// Members

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetCurveElements			(const API_Token&		token,
																		 const API_Guid&		amGuid,
																		 GS::Array<API_Guid>&	curveElements);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetCurveMember			(const API_Token&				token,
																		 const API_Guid&				amGuid,
																		 const API_Guid&				elemGuid,
																		 API_AnalyticalCurveMember&		api_curveMember);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetSurfaceElements			(const API_Token&		token,
																			 const API_Guid&		amGuid,
																			 GS::Array<API_Guid>&	surfaceElements);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetSurfaceMember				(const API_Token&				token,
																			 const API_Guid&				amGuid,
																			 const API_Guid&				elemGuid,
																			 API_AnalyticalSurfaceMember&	api_surfaceMember,
																			 API_ExportIdMappingType&		idMapping);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetSegmentedSurfaceMember		(const API_Token&							token,
																				 const API_Guid& 							mGuid,
																				 const API_Guid&							elemGuid,
																				 GS::Array<API_AnalyticalSurfaceMember>&	api_surfaceMember,
																				 double										centralAngle,
																				 API_ExportIdMappingType&					api_surfaceIdMapping);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_CreateElementFromCurveMember	(const API_Token&						token,
																			 API_AnalyticalCurveMember&				api_curveMember,
																			 const GS::Optional<GS::UniString>&		favoriteName);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_CreateElementFromSurfaceMember	(const API_Token&						token,
																				 API_AnalyticalSurfaceMember&			api_surfaceMember,
																				 const GS::Optional<GS::UniString>&		favoriteName,
																				 API_ImportIdMappingType*				idMapping);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_CreateElementFromSegmentedSurfaceMember	(const API_Token&							token,
																						 GS::Array<API_AnalyticalSurfaceMember>&	api_surfaceMember,
																						 const GS::Optional<GS::UniString>&			favoriteName,
																						 API_ImportIdMappingType*					idMapping);


ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetLCSOfAnalyticalMember				(const API_Token&						token,
																					 const API_AnalyticalMemberPartRef&		api_memberPartRef,
																					 API_CoordinateSystem&					localCoordinateSystem);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetLCSOfAnalyticalMemberInIntersection	(const API_Token&					token,
																						 const API_AnalyticalMemberPartRef&	api_memberPartRef1,
																						 const API_AnalyticalMemberPartRef&	api_memberPartRef2,
																						 API_CoordinateSystem&				localCoordinateSystem);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalMemberConnections	(const API_Token&			token,
																				 const API_Guid&			amGuid,
																				 const API_Guid&			elemGuid,
																				 GS::HashSet<API_Guid>&		api_connections);


ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalMemberPartRefCoord	(const API_Token&						token,
																				 const API_Guid&						amGuid,
																				 const API_AnalyticalMemberPartRef&		api_memberPartRef,
																				 API_AnalyticalNode&					api_analyticalNode);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalMemberPartRefCurve	(const API_Token&					token,
																				 const API_Guid&					amGuid,
																				 const API_AnalyticalMemberPartRef&	api_memberPartRef,
																				 API_AnalyticalCurve&				api_analyticalCurve);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetComplementaryProjectMemberType	(const API_Token&			token,
																					 const API_Guid&			elemGuid,
																					 API_AnalyticalMemberType&	membertType);


	// Link

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetElementFromLink	(const API_Token&				token,
																	 const API_AnalyticalLinkType&	link,
																	 API_Element&					element);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetLinkFromElement	(const API_Token&			token,
																	 const API_Element&			element,
																	 API_AnalyticalLinkType&	link);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLinkGeometry		(const API_Token&				token,
																				 const API_Guid&				amGuid,
																				 const API_Guid&				elemGuid,
																				 API_AnalyticalLinkGeometry&	analyticalLinkGeometry);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_ConvertAnalyticalLinkToNonShortest	(const API_Token&			token,
																					 const API_Guid&			amGuid,
																					 const API_Guid&			elemGuid,
																					 API_AnalyticalLinkType&	api_analyticalLink);


	// Support

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetElementFromSupport	(const API_Token&					token,
																		 const API_AnalyticalSupportType&	support,
																		 API_Element&						element);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetSupportFromElement	(const API_Token&			token,
																		 const API_Element&			element,
																		 API_AnalyticalSupportType&	support);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalSupportGeometry	(const API_Token&					token,
																			 const API_Guid&					amGuid,
																			 const API_Guid&					elemGuid,
																			 API_AnalyticalSupportGeometry&		analyticalSupportGeometry);


	// PointLoad

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetElementFromPointLoad	(const API_Token&					token,
																		 const API_AnalyticalPointLoadType&	pointLoad,
																		 API_Element&						element);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetPointLoadFromElement	(const API_Token&				token,
																		 const API_Element&				element,
																		 API_AnalyticalPointLoadType&	pointLoad);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalPointLoadGeometry	(const API_Token&					token,
																				 const API_Guid&					amGuid,
																				 const API_Guid&					elemGuid,
																				 API_AnalyticalPointLoadGeometry&	analyticalPointLoadGeometry);


	// EdgeLoad

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetElementFromEdgeLoad		(const API_Token&					token,
																			 const API_AnalyticalEdgeLoadType&	edgeLoad,
																			 API_Element&						element);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetEdgeLoadFromElement		(const API_Token&				token,
																			 const API_Element&				element,
																			 API_AnalyticalEdgeLoadType&	edgeLoad);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetEdgeLoadGeometry			(const API_Token&			token,
																			 const API_Guid&			amGuid,
																			 const API_Guid&			elemGuid,
																			 API_EdgeLoadCustomData&	edgeLoadCustomData);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetMemoFromEdgeLoadCustomData	(const API_Token&				token,
																				 const API_EdgeLoadCustomData&	edgeLoadCustomData,
																				 API_ElementMemo&				memo);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetEdgeLoadCustomDataFromMemo	(const API_Token&			token,
																				 const API_ElementMemo&		memo,
																				 API_EdgeLoadCustomData&	edgeLoadCustomData);

	// SurfaceLoad

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetElementFromSurfaceLoad		(const API_Token&						token,
																				 const API_AnalyticalSurfaceLoadType&	surfaceLoad,
																				 API_Element&							element);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetSurfaceLoadFromElement		(const API_Token&				token,
																				 const API_Element&				element,
																				 API_AnalyticalSurfaceLoadType&	surfaceLoad);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetSurfaceLoadGeometry			(const API_Token&			token,
																				 const API_Guid&			amGuid,
																				 const API_Guid&			elemGuid,
																				 API_SurfaceLoadCustomData&	edgeLoadCustomData);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetMemoFromSurfaceLoadCustomData	(const API_Token&					token,
																				 const API_SurfaceLoadCustomData&	customData,
																				 API_ElementMemo&					memo);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetSurfaceLoadCustomDataFromMemo	(const API_Token&			token,
																				 const API_ElementMemo&		memo,
																				 API_SurfaceLoadCustomData&	customData);


// Load(Group, Case, Combination)

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLoadGroups	(const API_Token&		token,
																		 GS::Array<API_Guid>&	analyticalLoadGroups);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLoadGroup	(const API_Token&			token,
																		 const API_Guid&			analyticalLoadGroupGuid,
																		 API_AnalyticalLoadGroup&	analyticalLoadGroup);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_CreateAnalyticalLoadGroup	(const API_Token&			token,
																			 API_AnalyticalLoadGroup&	analyticalLoadGroup);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_DeleteAnalyticalLoadGroup	(const API_Token&	token,
																			 const API_Guid&	analyticalLoadGroupGuid);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAllAnalyticalLoadCases	(const API_Token&		token,
																			 GS::Array<API_Guid>&	analyticalLoadCases);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLoadCases	(const API_Token&		token,
																		 const API_Guid&		analyticalLoadGroupGuid,
																		 GS::Array<API_Guid>&	analyticalLoadCases);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLoadCase	(const API_Token&			token,
																		 const API_Guid&			analyticalLoadCaseGuid,
																		 API_AnalyticalLoadCase&	analyticalLoadCase);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_CreateAnalyticalLoadCase	(const API_Token&			token,
																		 API_AnalyticalLoadCase&	analyticalLoadCase);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_DeleteAnalyticalLoadCase	(const API_Token&	token,
																		 const API_Guid&	analyticalLoadCaseGuid);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLoadCombinations	(const API_Token&		token,
																				 GS::Array<API_Guid>&	analyticalLoadCombinations);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLoadCombination	(const API_Token&				token,
																			 const API_Guid&				analyticalLoadCombinationGuid,
																			 API_AnalyticalLoadCombination&	analyticalLoadCombination);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_CreateAnalyticalLoadCombination	(const API_Token&					token,
																				 API_AnalyticalLoadCombination&		analyticalLoadCombination);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_AddLoadCaseToLoadCombination	(const API_Token&					token,
																			 const API_AnalyticalLoadFactor&	analyticalLoadFactor,
																			 const API_Guid&					analyticalLoadCombinationGuid);

ANALYTICALMODELAPI_EXPORT
GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_DeleteAnalyticalLoadCombination	(const API_Token&	token,
																				 const API_Guid&	analyticalLoadCombinationGuid);


} // extern "C"


#endif /* GS_ACAPI_ANALYTICAL_HPP */
