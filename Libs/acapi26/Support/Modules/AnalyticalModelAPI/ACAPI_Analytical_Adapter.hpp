#ifndef ACAPI_ANALYTICAL_HPP_ADAPTER
#define ACAPI_ANALYTICAL_HPP_ADAPTER

#pragma once

#include "ACAPI_Analytical.hpp"
#include "ACAPinc.h"

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetCurrentAnalyticalModel	(API_Guid&			amGuid)
{
	return ACAPI_AnalyticalModel_GetCurrentAnalyticalModel (ACAPI_GetToken (), amGuid);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_UpdateAnalyticalModel		(const API_Guid&	amGuid)
{
	return ACAPI_AnalyticalModel_UpdateAnalyticalModel (ACAPI_GetToken (), amGuid);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalModelVariation	(const API_Guid&				amGuid,
																					 API_AnalyticalModelVariation&	api_modelVariation)
{
	return ACAPI_AnalyticalModel_GetAnalyticalModelVariation (ACAPI_GetToken (), amGuid, api_modelVariation);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalModel			(const API_AnalyticalModelVariation&	api_modelVariation,
																					 API_Guid&								amGuid)
{
	return ACAPI_AnalyticalModel_GetAnalyticalModel (ACAPI_GetToken (), api_modelVariation, amGuid);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetGenerationSettingsToNoRule ()
{
	return ACAPI_AnalyticalModel_SetGenerationSettingsToNoRule (ACAPI_GetToken ());
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetVisibilitySettings		(API_AM_VisibilitySettings&	api_visibilitySettings)
{
	return ACAPI_AnalyticalModel_GetVisibilitySettings (ACAPI_GetToken (), api_visibilitySettings);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetVisibilitySettings		(const API_AM_VisibilitySettings&	api_visibilitySettings)
{
	return ACAPI_AnalyticalModel_SetVisibilitySettings (ACAPI_GetToken (), api_visibilitySettings);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalRelease	(const API_Guid&					amGuid,
																			 const API_Guid&					elemGuid,
																			 API_AnalyticalReleaseType&			api_analyticalRelease)
{
	return ACAPI_AnalyticalModel_GetAnalyticalRelease (ACAPI_GetToken (), amGuid, elemGuid, api_analyticalRelease);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetAnalyticalRelease	(const API_Guid&					elemGuid,
																			 const API_AnalyticalReleaseType&	api_analyticalRelease)
{
	return ACAPI_AnalyticalModel_SetAnalyticalRelease (ACAPI_GetToken (), elemGuid, api_analyticalRelease);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetCurveElements			(const API_Guid&		amGuid,
																				 GS::Array<API_Guid>&	curveElements)
{
	return ACAPI_AnalyticalModel_GetCurveElements (ACAPI_GetToken (), amGuid, curveElements);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetCurveMember			(const API_Guid&				amGuid,
																				 const API_Guid&				elemGuid,
																				 API_AnalyticalCurveMember&		api_curveMember)
{
	return ACAPI_AnalyticalModel_GetCurveMember (ACAPI_GetToken (), amGuid, elemGuid, api_curveMember);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetSurfaceElements			(const API_Guid&		amGuid,
																					 GS::Array<API_Guid>&	surfaceElements)
{
	return ACAPI_AnalyticalModel_GetSurfaceElements (ACAPI_GetToken (), amGuid, surfaceElements);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetSurfaceMember				(const API_Guid&				amGuid,
																					 const API_Guid&				elemGuid,
																					 API_AnalyticalSurfaceMember&	api_surfaceMember,
																					 API_ExportIdMappingType&		idMapping)
{
	return ACAPI_AnalyticalModel_GetSurfaceMember (ACAPI_GetToken (), amGuid, elemGuid, api_surfaceMember, idMapping);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetSegmentedSurfaceMember		(const API_Guid& 							mGuid,
																						 const API_Guid&							elemGuid,
																						 GS::Array<API_AnalyticalSurfaceMember>&	api_surfaceMember,
																						 double										centralAngle,
																						 API_ExportIdMappingType&					api_surfaceIdMapping)
{
	return ACAPI_AnalyticalModel_GetSegmentedSurfaceMember (ACAPI_GetToken (), mGuid, elemGuid, api_surfaceMember, centralAngle, api_surfaceIdMapping);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_CreateElementFromCurveMember	(API_AnalyticalCurveMember&				api_curveMember,
																					 const GS::Optional<GS::UniString>&		favoriteName)
{
	return ACAPI_AnalyticalModel_CreateElementFromCurveMember (ACAPI_GetToken (), api_curveMember, favoriteName);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_CreateElementFromSurfaceMember	(API_AnalyticalSurfaceMember&			api_surfaceMember,
																						 const GS::Optional<GS::UniString>&		favoriteName,
																						 API_ImportIdMappingType*				idMapping)
{
	return ACAPI_AnalyticalModel_CreateElementFromSurfaceMember (ACAPI_GetToken (), api_surfaceMember, favoriteName, idMapping);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_CreateElementFromSegmentedSurfaceMember	(GS::Array<API_AnalyticalSurfaceMember>&	api_surfaceMember,
																								 const GS::Optional<GS::UniString>&			favoriteName,
																								 API_ImportIdMappingType*					idMapping)
{
	return ACAPI_AnalyticalModel_CreateElementFromSegmentedSurfaceMember (ACAPI_GetToken (), api_surfaceMember, favoriteName, idMapping);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetLCSOfAnalyticalMember				(const API_AnalyticalMemberPartRef&		api_memberPartRef,
																							 API_CoordinateSystem&					localCoordinateSystem)
{
	return ACAPI_AnalyticalModel_GetLCSOfAnalyticalMember (ACAPI_GetToken (), api_memberPartRef, localCoordinateSystem);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetLCSOfAnalyticalMemberInIntersection	(const API_AnalyticalMemberPartRef&	api_memberPartRef1,
																								 const API_AnalyticalMemberPartRef&	api_memberPartRef2,
																								 API_CoordinateSystem&				localCoordinateSystem)
{
	return ACAPI_AnalyticalModel_GetLCSOfAnalyticalMemberInIntersection (ACAPI_GetToken (), api_memberPartRef1, api_memberPartRef2, localCoordinateSystem);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalMemberConnections	(const API_Guid&			amGuid,
																						 const API_Guid&			elemGuid,
																						 GS::HashSet<API_Guid>&		api_connections)
{
	return ACAPI_AnalyticalModel_GetAnalyticalMemberConnections (ACAPI_GetToken (), amGuid, elemGuid, api_connections);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalMemberPartRefCoord	(const API_Guid&						amGuid,
																						 const API_AnalyticalMemberPartRef&		api_memberPartRef,
																						 API_AnalyticalNode&					api_analyticalNode)
{
	return ACAPI_AnalyticalModel_GetAnalyticalMemberPartRefCoord (ACAPI_GetToken (), amGuid, api_memberPartRef, api_analyticalNode);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalMemberPartRefCurve	(const API_Guid&					amGuid,
																						 const API_AnalyticalMemberPartRef&	api_memberPartRef,
																						 API_AnalyticalCurve&				api_analyticalCurve)
{
	return ACAPI_AnalyticalModel_GetAnalyticalMemberPartRefCurve (ACAPI_GetToken (), amGuid, api_memberPartRef, api_analyticalCurve);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetComplementaryProjectMemberType	(const API_Guid&			elemGuid,
																							 API_AnalyticalMemberType&	membertType)
{
	return ACAPI_AnalyticalModel_GetComplementaryProjectMemberType (ACAPI_GetToken (), elemGuid, membertType);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetElementFromLink	(const API_AnalyticalLinkType&	link,
																			 API_Element&					element)
{
	return ACAPI_AnalyticalModel_SetElementFromLink (ACAPI_GetToken (), link, element);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetLinkFromElement	(const API_Element&			element,
																			 API_AnalyticalLinkType&	link)
{
	return ACAPI_AnalyticalModel_GetLinkFromElement (ACAPI_GetToken (), element, link);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLinkGeometry		(const API_Guid&				amGuid,
																						 const API_Guid&				elemGuid,
																						 API_AnalyticalLinkGeometry&	analyticalLinkGeometry)
{
	return ACAPI_AnalyticalModel_GetAnalyticalLinkGeometry (ACAPI_GetToken (), amGuid, elemGuid, analyticalLinkGeometry);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_ConvertAnalyticalLinkToNonShortest	(const API_Guid&			amGuid,
																							 const API_Guid&			elemGuid,
																							 API_AnalyticalLinkType&	api_analyticalLink)
{
	return ACAPI_AnalyticalModel_ConvertAnalyticalLinkToNonShortest (ACAPI_GetToken (), amGuid, elemGuid, api_analyticalLink);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetElementFromSupport	(const API_AnalyticalSupportType&	support,
																				 API_Element&						element)
{
	return ACAPI_AnalyticalModel_SetElementFromSupport (ACAPI_GetToken (), support, element);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetSupportFromElement	(const API_Element&			element,
																				 API_AnalyticalSupportType&	support)
{
	return ACAPI_AnalyticalModel_GetSupportFromElement (ACAPI_GetToken (), element, support);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalSupportGeometry	(const API_Guid&					amGuid,
																					 const API_Guid&					elemGuid,
																					 API_AnalyticalSupportGeometry&		analyticalSupportGeometry)
{
	return ACAPI_AnalyticalModel_GetAnalyticalSupportGeometry (ACAPI_GetToken (), amGuid, elemGuid, analyticalSupportGeometry);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetElementFromPointLoad	(const API_AnalyticalPointLoadType&	pointLoad,
																				 API_Element&						element)
{
	return ACAPI_AnalyticalModel_SetElementFromPointLoad (ACAPI_GetToken (), pointLoad, element);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetPointLoadFromElement	(const API_Element&				element,
																				 API_AnalyticalPointLoadType&	pointLoad)
{
	return ACAPI_AnalyticalModel_GetPointLoadFromElement (ACAPI_GetToken (), element, pointLoad);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalPointLoadGeometry	(const API_Guid&					amGuid,
																						 const API_Guid&					elemGuid,
																						 API_AnalyticalPointLoadGeometry&	analyticalPointLoadGeometry)
{
	return ACAPI_AnalyticalModel_GetAnalyticalPointLoadGeometry (ACAPI_GetToken (), amGuid, elemGuid, analyticalPointLoadGeometry);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetElementFromEdgeLoad		(const API_AnalyticalEdgeLoadType&	edgeLoad,
																					 API_Element&						element)
{
	return ACAPI_AnalyticalModel_SetElementFromEdgeLoad (ACAPI_GetToken (), edgeLoad, element);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetEdgeLoadFromElement		(const API_Element&				element,
																					 API_AnalyticalEdgeLoadType&	edgeLoad)
{
	return ACAPI_AnalyticalModel_GetEdgeLoadFromElement (ACAPI_GetToken (), element, edgeLoad);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetEdgeLoadGeometry			(const API_Guid&			amGuid,
																					 const API_Guid&			elemGuid,
																					 API_EdgeLoadCustomData&	edgeLoadCustomData)
{
	return ACAPI_AnalyticalModel_GetEdgeLoadGeometry (ACAPI_GetToken (), amGuid, elemGuid, edgeLoadCustomData);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetMemoFromEdgeLoadCustomData	(const API_EdgeLoadCustomData&	edgeLoadCustomData,
																						 API_ElementMemo&				memo)
{
	return ACAPI_AnalyticalModel_SetMemoFromEdgeLoadCustomData (ACAPI_GetToken (), edgeLoadCustomData, memo);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetEdgeLoadCustomDataFromMemo	(const API_ElementMemo&		memo,
																						 API_EdgeLoadCustomData&	edgeLoadCustomData)
{
	return ACAPI_AnalyticalModel_SetEdgeLoadCustomDataFromMemo (ACAPI_GetToken (), memo, edgeLoadCustomData);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetElementFromSurfaceLoad		(const API_AnalyticalSurfaceLoadType&	surfaceLoad,
																						 API_Element&							element)
{
	return ACAPI_AnalyticalModel_SetElementFromSurfaceLoad (ACAPI_GetToken (), surfaceLoad, element);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetSurfaceLoadFromElement		(const API_Element&				element,
																						 API_AnalyticalSurfaceLoadType&	surfaceLoad)
{
	return ACAPI_AnalyticalModel_GetSurfaceLoadFromElement (ACAPI_GetToken (), element, surfaceLoad);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetSurfaceLoadGeometry			(const API_Guid&			amGuid,
																						 const API_Guid&			elemGuid,
																						 API_SurfaceLoadCustomData&	edgeLoadCustomData)
{
	return ACAPI_AnalyticalModel_GetSurfaceLoadGeometry (ACAPI_GetToken (), amGuid, elemGuid, edgeLoadCustomData);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetMemoFromSurfaceLoadCustomData	(const API_SurfaceLoadCustomData&	customData,
																						 API_ElementMemo&					memo)
{
	return ACAPI_AnalyticalModel_SetMemoFromSurfaceLoadCustomData (ACAPI_GetToken (), customData, memo);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_SetSurfaceLoadCustomDataFromMemo	(const API_ElementMemo&		memo,
																						 API_SurfaceLoadCustomData&	customData)
{
	return ACAPI_AnalyticalModel_SetSurfaceLoadCustomDataFromMemo (ACAPI_GetToken (), memo, customData);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLoadGroups	(GS::Array<API_Guid>&	analyticalLoadGroups)
{
	return ACAPI_AnalyticalModel_GetAnalyticalLoadGroups (ACAPI_GetToken (), analyticalLoadGroups);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLoadGroup	(const API_Guid&			analyticalLoadGroupGuid,
																				 API_AnalyticalLoadGroup&	analyticalLoadGroup)
{
	return ACAPI_AnalyticalModel_GetAnalyticalLoadGroup (ACAPI_GetToken (), analyticalLoadGroupGuid, analyticalLoadGroup);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_CreateAnalyticalLoadGroup	(API_AnalyticalLoadGroup&	analyticalLoadGroup)
{
	return ACAPI_AnalyticalModel_CreateAnalyticalLoadGroup (ACAPI_GetToken (), analyticalLoadGroup);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_DeleteAnalyticalLoadGroup	(const API_Guid&	analyticalLoadGroupGuid)
{
	return ACAPI_AnalyticalModel_DeleteAnalyticalLoadGroup (ACAPI_GetToken (), analyticalLoadGroupGuid);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAllAnalyticalLoadCases	(GS::Array<API_Guid>&	analyticalLoadCases)
{
	return ACAPI_AnalyticalModel_GetAllAnalyticalLoadCases (ACAPI_GetToken (), analyticalLoadCases);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLoadCases	(const API_Guid&		analyticalLoadGroupGuid,
																				 GS::Array<API_Guid>&	analyticalLoadCases)
{
	return ACAPI_AnalyticalModel_GetAnalyticalLoadCases (ACAPI_GetToken (), analyticalLoadGroupGuid, analyticalLoadCases);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLoadCase	(const API_Guid&			analyticalLoadCaseGuid,
																				 API_AnalyticalLoadCase&	analyticalLoadCase)
{
	return ACAPI_AnalyticalModel_GetAnalyticalLoadCase (ACAPI_GetToken (), analyticalLoadCaseGuid, analyticalLoadCase);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_CreateAnalyticalLoadCase	(API_AnalyticalLoadCase&	analyticalLoadCase)
{
	return ACAPI_AnalyticalModel_CreateAnalyticalLoadCase (ACAPI_GetToken (), analyticalLoadCase);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_DeleteAnalyticalLoadCase	(const API_Guid&	analyticalLoadCaseGuid)
{
	return ACAPI_AnalyticalModel_DeleteAnalyticalLoadCase (ACAPI_GetToken (), analyticalLoadCaseGuid);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLoadCombinations	(GS::Array<API_Guid>&	analyticalLoadCombinations)
{
	return ACAPI_AnalyticalModel_GetAnalyticalLoadCombinations (ACAPI_GetToken (), analyticalLoadCombinations);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_GetAnalyticalLoadCombination	(const API_Guid&				analyticalLoadCombinationGuid,
																					 API_AnalyticalLoadCombination&	analyticalLoadCombination)
{
	return ACAPI_AnalyticalModel_GetAnalyticalLoadCombination (ACAPI_GetToken (), analyticalLoadCombinationGuid, analyticalLoadCombination);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_CreateAnalyticalLoadCombination	(API_AnalyticalLoadCombination&		analyticalLoadCombination)
{
	return ACAPI_AnalyticalModel_CreateAnalyticalLoadCombination (ACAPI_GetToken (), analyticalLoadCombination);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_AddLoadCaseToLoadCombination	(const API_AnalyticalLoadFactor&	analyticalLoadFactor,
																					 const API_Guid&					analyticalLoadCombinationGuid)
{
	return ACAPI_AnalyticalModel_AddLoadCaseToLoadCombination (ACAPI_GetToken (), analyticalLoadFactor, analyticalLoadCombinationGuid);
}

inline GSErrCode	__ACENV_CALL ACAPI_AnalyticalModel_DeleteAnalyticalLoadCombination	(const API_Guid&	analyticalLoadCombinationGuid)
{
	return ACAPI_AnalyticalModel_DeleteAnalyticalLoadCombination (ACAPI_GetToken (), analyticalLoadCombinationGuid);
}



#endif