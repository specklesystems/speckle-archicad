#ifndef ACAPI_ANALYTICAL_HPP_ADAPTER
#define ACAPI_ANALYTICAL_HPP_ADAPTER

#pragma once

#include "ACAPI_Analytical.hpp"
#include "ACAPinc.h"

/**
 * @brief Returns the Structural Analytical Model created for the current view.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [out] The unique identifier of the internal Structural Analytical Model.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetCurrentAnalyticalModel	(API_Guid&			amGuid)
{
	return ACAPI_Analytical_GetCurrentAnalyticalModel (ACAPI_GetToken (), amGuid);
}

/**
 * @brief Triggers an update of the Structural Analytical Model specified.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in/out] The Structural Analytical Model identifier.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_UpdateAnalyticalModel		(const API_Guid&	amGuid)
{
	return ACAPI_Analytical_UpdateAnalyticalModel (ACAPI_GetToken (), amGuid);
}

/**
 * @brief Returns the Model Variation used for creating the specified Structural Analytical Model.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the Structural Analytical Model.
 * @param api_modelVariation [out] The Model Variation specification.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalModelVariation	(const API_Guid&				amGuid,
																					 API_AnalyticalModelVariation&	api_modelVariation)
{
	return ACAPI_Analytical_GetAnalyticalModelVariation (ACAPI_GetToken (), amGuid, api_modelVariation);
}

/**
 * @brief Returns the Structural Analytical Model created for the specified Model Variation.
 * @ingroup Analytical
 * @since Archicad 26
 * @param api_modelVariation [in] The Model Variation specification.
 * @param amGuid [out] The unique identifier for the Structural Analytical Model created for the specified Model Variation.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalModel			(const API_AnalyticalModelVariation&	api_modelVariation,
																					 API_Guid&								amGuid)
{
	return ACAPI_Analytical_GetAnalyticalModel (ACAPI_GetToken (), api_modelVariation, amGuid);
}

/**
 * @brief Sets the current analytical model's generation settings to no rules.
 * @ingroup Analytical
 * @since Archicad 26
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_SetGenerationSettingsToNoRule ()
{
	return ACAPI_Analytical_SetGenerationSettingsToNoRule (ACAPI_GetToken ());
}

/**
 * @brief Returns the Visibility Settings of the analytical model.
 * @ingroup Analytical
 * @since Archicad 26
 * @param api_am_visiblitySettings [out] The visibility settings of the analytical model.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetVisibilitySettings		(API_AM_VisibilitySettings&	api_am_visiblitySettings)
{
	return ACAPI_Analytical_GetVisibilitySettings (ACAPI_GetToken (), api_am_visiblitySettings);
}

/**
 * @brief Sets the Visibility Settings of the analytical model.
 * @ingroup Analytical
 * @since Archicad 26
 * @param api_am_visiblitySettings [in] The visibility settings of the analytical model.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_SetVisibilitySettings		(const API_AM_VisibilitySettings&	api_am_visiblitySettings)
{
	return ACAPI_Analytical_SetVisibilitySettings (ACAPI_GetToken (), api_am_visiblitySettings);
}

/**
 * @brief Returns the Structural Analytical Model Member Relase associated with the selected Curve Element.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param elemGuid [in] The unique identifier of the internal Curve Element.
 * @param api_analyticalRelease [out] The Structural Analytical Model Member Release data.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalRelease	(const API_Guid&					amGuid,
																			 const API_Guid&					elemGuid,
																			 API_AnalyticalReleaseType&			api_analyticalRelease)
{
	return ACAPI_Analytical_GetAnalyticalRelease (ACAPI_GetToken (), amGuid, elemGuid, api_analyticalRelease);
}

/**
 * @brief Sets the Structural Analytical Model Member Release to the selected Curve Element.
 * @ingroup Analytical
 * @since Archicad 26
 * @param elemGuid [in] The unique identifier of the internal Curve Element.
 * @param api_analyticalRelease [in] The Structural Analytical Model Member Release data.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_SetAnalyticalRelease	(const API_Guid&					elemGuid,
																			 const API_AnalyticalReleaseType&	api_analyticalRelease)
{
	return ACAPI_Analytical_SetAnalyticalRelease (ACAPI_GetToken (), elemGuid, api_analyticalRelease);
}

/**
 * @brief Returns the elements that have Structural Analytical Model Curve Member associated.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param curveElements [out] The list of Curve Element unique identifiers.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetCurveElements			(const API_Guid&		amGuid,
																				 GS::Array<API_Guid>&	curveElements)
{
	return ACAPI_Analytical_GetCurveElements (ACAPI_GetToken (), amGuid, curveElements);
}

/**
 * @brief Returns the Structural Analytical Model Curve Member associated with the selected Curve Element.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param elemGuid [in] The unique identifier of the internal Curve Element.
 * @param cm [out] The Structural Analytical Model Curve Member data.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetCurveMember			(const API_Guid&				amGuid,
																				 const API_Guid&				elemGuid,
																				 API_AnalyticalCurveMember&		cm)
{
	return ACAPI_Analytical_GetCurveMember (ACAPI_GetToken (), amGuid, elemGuid, cm);
}

/**
 * @brief Returns the elements that have Structural Analytical Model Surface Member associated.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param surfaceElements [out] The list of Surface Element unique identifiers.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetSurfaceElements			(const API_Guid&		amGuid,
																					 GS::Array<API_Guid>&	surfaceElements)
{
	return ACAPI_Analytical_GetSurfaceElements (ACAPI_GetToken (), amGuid, surfaceElements);
}

/**
 * @brief Returns the Structural Analytical Model Surface Member associated with the selected Surface Element.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param elemGuid [in] The unique identifier of the internal Surface Element.
 * @param surfaceMember [out] The Structural Analytical Model Surface Member data.
 * @param idMapping [out] The mapping between support/link/release partID and member's edge/vertex.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetSurfaceMember				(const API_Guid&				amGuid,
																					 const API_Guid&				elemGuid,
																					 API_AnalyticalSurfaceMember&	surfaceMember,
																					 API_ExportIdMappingType&		idMapping)
{
	return ACAPI_Analytical_GetSurfaceMember (ACAPI_GetToken (), amGuid, elemGuid, surfaceMember, idMapping);
}

/**
 * @brief Returns the Structural Analytical Model Surface Member segmented version associated with the selected Surface Element.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param elemGuid [in] The unique identifier of the internal Surface Element.
 * @param surfaceMember [out] The array of Structural Analytical Model Surface Member segments representing the Structural Analytical Model Surface Member data.
 * @param centralAngle [in] The angle of segmentation for curved walls given in degrees.
 * @param surfaceIdMapping [out] The mapping between Surface Elements edge/vertex ID and segments edge/vertex IDs
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetSegmentedSurfaceMember		(const API_Guid& 							amGuid,
																						 const API_Guid&							elemGuid,
																						 GS::Array<API_AnalyticalSurfaceMember>&	surfaceMember,
																						 double										centralAngle,
																						 API_ExportIdMappingType&					surfaceIdMapping)
{
	return ACAPI_Analytical_GetSegmentedSurfaceMember (ACAPI_GetToken (), amGuid, elemGuid, surfaceMember, centralAngle, surfaceIdMapping);
}

/**
 * @brief Creates an element from the Structural Analytical Model Curve Member.
 * @ingroup Analytical
 * @since Archicad 26
 * @param api_curveMember [in/out] The Curve Member to create the element from. After a successful creation, it is filled with the unique identifier of the created element.
 * @param favoriteName [in] The name of the Favorite Element which contains the settings for the new element, otherwise the settings are taken from the element default.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks The ProfileVectorImage parameter for Custom Profiles has been moved into API_AnalyticalCrossSection
 */
inline  GSErrCode ACAPI_Analytical_CreateElementFromCurveMember	(API_AnalyticalCurveMember&				api_curveMember,
																					 const GS::Optional<GS::UniString>&		favoriteName)
{
	return ACAPI_Analytical_CreateElementFromCurveMember (ACAPI_GetToken (), api_curveMember, favoriteName);
}

/**
 * @brief Creates an element from the Structural Analytical Model Surface Member.
 * @ingroup Analytical
 * @since Archicad 26
 * @param api_surfaceMember [in/out] The Surface Member to create the element from. After a successful creation, it is filled with the unique identifier of the created element.
 * @param favoriteName [in] The name of the Favorite Element which contains the settings for the new element, otherwise the settings are taken from the element default.
 * @param idMapping [out] An optional paramter which stores the mapping table for the edges and vertices of the member.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_CreateElementFromSurfaceMember	(API_AnalyticalSurfaceMember&			api_surfaceMember,
																						 const GS::Optional<GS::UniString>&		favoriteName,
																						 API_ImportIdMappingType*				idMapping)
{
	return ACAPI_Analytical_CreateElementFromSurfaceMember (ACAPI_GetToken (), api_surfaceMember, favoriteName, idMapping);
}

/**
 * @brief Creates an element from the Structural Analytical Model Surface Member segments.
 * @ingroup Analytical
 * @since Archicad 26
 * @param api_surfaceMember [in/out] The Surface Member to create the element from. After a successful creation, the first segment from the array is filled with the unique identifier of the created element.
 * @param favoriteName [in] The name of the Favorite Element which contains the settings for the new element, otherwise the settings are taken from the element default.
 * @param idMapping [out] An optional parameter for the mapping between Segment Surface Member edge&amp;vertex ID and generated Surface Element Member Part Reference.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_CreateElementFromSegmentedSurfaceMember	(GS::Array<API_AnalyticalSurfaceMember>&	api_surfaceMember,
																								 const GS::Optional<GS::UniString>&			favoriteName,
																								 API_ImportIdMappingType*					idMapping)
{
	return ACAPI_Analytical_CreateElementFromSegmentedSurfaceMember (ACAPI_GetToken (), api_surfaceMember, favoriteName, idMapping);
}

/**
 * @brief Get the local coordinate system of a member from AnalyticalMemberPartRef
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalMemberPartRef [in] The member part ref of an analytical element.
 * @param coordinateSystem [out] Local coordinate system of the member
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetLCSOfAnalyticalMember				(const API_AnalyticalMemberPartRef&		analyticalMemberPartRef,
																							 API_CoordinateSystem&					coordinateSystem)
{
	return ACAPI_Analytical_GetLCSOfAnalyticalMember (ACAPI_GetToken (), analyticalMemberPartRef, coordinateSystem);
}

/**
 * @brief Get the local coordinate system of a member in intersection of AnalyticalMemberPartRefs
 * @ingroup Analytical
 * @since Archicad 26
 * @param firstAnalyticalMemberPartRef [in] The member part ref of an analytical element.
 * @param secondAnalyticalMemberPartRef [in] The member part ref of an analytical element.
 * @param coordinateSystem [out] Local coordinate system of the member
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetLCSOfAnalyticalMemberInIntersection	(const API_AnalyticalMemberPartRef&	firstAnalyticalMemberPartRef,
																								 const API_AnalyticalMemberPartRef&	secondAnalyticalMemberPartRef,
																								 API_CoordinateSystem&				coordinateSystem)
{
	return ACAPI_Analytical_GetLCSOfAnalyticalMemberInIntersection (ACAPI_GetToken (), firstAnalyticalMemberPartRef, secondAnalyticalMemberPartRef, coordinateSystem);
}

/**
 * @brief Returns the guids of elements which are connected to a Structural Analytical Member, given by it's guid. Includes elements which are connected by Structural Analytical Links.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural   Analytical Model.
 * @param elemGuid [in] The unique identifier of the Structural Analytical   Member.
 * @param api_connections [out] The elements connected to the given Structural   Analytical Member.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalMemberConnections	(const API_Guid&			amGuid,
																						 const API_Guid&			elemGuid,
																						 GS::HashSet<API_Guid>&		api_connections)
{
	return ACAPI_Analytical_GetAnalyticalMemberConnections (ACAPI_GetToken (), amGuid, elemGuid, api_connections);
}

/**
 * @brief Returns the coord of the given Structural Analytical Model's Analytical Member part if it identifies an edge.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param api_memberPartRef [in] The member part ref of an analytical element.
 * @param api_analyticalNode [out] The Structural Analytical Node.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalMemberPartRefCoord	(const API_Guid&						amGuid,
																						 const API_AnalyticalMemberPartRef&		api_memberPartRef,
																						 API_AnalyticalNode&					api_analyticalNode)
{
	return ACAPI_Analytical_GetAnalyticalMemberPartRefCoord (ACAPI_GetToken (), amGuid, api_memberPartRef, api_analyticalNode);
}

/**
 * @brief Returns the curve of the given Structural Analytical Model's Analytical Member part if it identifies a vertex.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param api_memberPartRef [in] The member part ref of an analytical element.
 * @param api_analyticalCurve [out] The Structural Analytical Model Curve.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalMemberPartRefCurve	(const API_Guid&					amGuid,
																						 const API_AnalyticalMemberPartRef&	api_memberPartRef,
																						 API_AnalyticalCurve&				api_analyticalCurve)
{
	return ACAPI_Analytical_GetAnalyticalMemberPartRefCurve (ACAPI_GetToken (), amGuid, api_memberPartRef, api_analyticalCurve);
}

/**
 * @brief Returns the Analytical Member Type of a certain element from the Complementary Project.
 * @ingroup Analytical
 * @since Archicad 26
 * @param elemGuid [in] The unique identifier of the Analytical Member element.
 * @param analyticalMemberType [out] The type of the Analytical Member element from the Complementary Project.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks It is recommended to call this function before creating any Analytical Member and use its analyticalMemberType value if it is different than API_AnalyticalMember_UnknownType.
 */
inline  GSErrCode ACAPI_Analytical_GetComplementaryProjectMemberType	(const API_Guid&			elemGuid,
																							 API_AnalyticalMemberType&	analyticalMemberType)
{
	return ACAPI_Analytical_GetComplementaryProjectMemberType (ACAPI_GetToken (), elemGuid, analyticalMemberType);
}

/**
 * @brief Sets element.type to API_AnalyticalLinkID , and element.externalElemData to link .
 * @ingroup Analytical
 * @since Archicad 26
 * @param link [in] The source for the element.
 * @param element [out] The element to be set.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_SetElementFromLink	(const API_AnalyticalLinkType&	link,
																			 API_Element&					element)
{
	return ACAPI_Analytical_SetElementFromLink (ACAPI_GetToken (), link, element);
}

/**
 * @brief Obtains the API_AnalyticalLinkType from
 * @ingroup Analytical
 * @since Archicad 26
 * @param element [in] The source for the link.
 * @param link [out] The link to be set.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetLinkFromElement	(const API_Element&			element,
																			 API_AnalyticalLinkType&	link)
{
	return ACAPI_Analytical_GetLinkFromElement (ACAPI_GetToken (), element, link);
}

/**
 * @brief Returns the Structural Analytical Link %Geometry.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param elemGuid [in] The unique identifier of the internal Curve Element.
 * @param api_analyticalLinkGeometry [out] The Structural Analytical Link geometry.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalLinkGeometry		(const API_Guid&				amGuid,
																						 const API_Guid&				elemGuid,
																						 API_AnalyticalLinkGeometry&	api_analyticalLinkGeometry)
{
	return ACAPI_Analytical_GetAnalyticalLinkGeometry (ACAPI_GetToken (), amGuid, elemGuid, api_analyticalLinkGeometry);
}

/**
 * @brief Converts an Analytical Link that is associative to a Curve Member or an edge of a Surface Member (known as a "shortest" Analytical Link) to an Analytical Link that is connected to a fixed coordinate.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param elemGuid [in] The unique identifier of the Analytical Link element.
 * @param api_analyticalLink [out] The converted Analytical Link.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_ConvertAnalyticalLinkToNonShortest	(const API_Guid&			amGuid,
																							 const API_Guid&			elemGuid,
																							 API_AnalyticalLinkType&	api_analyticalLink)
{
	return ACAPI_Analytical_ConvertAnalyticalLinkToNonShortest (ACAPI_GetToken (), amGuid, elemGuid, api_analyticalLink);
}

/**
 * @brief Sets element.type to API_AnalyticalSupportID , and element.externalElemData to support .
 * @ingroup Analytical
 * @since Archicad 26
 * @param support [in] The source for the element.
 * @param element [out] The element to be set.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_SetElementFromSupport	(const API_AnalyticalSupportType&	support,
																				 API_Element&						element)
{
	return ACAPI_Analytical_SetElementFromSupport (ACAPI_GetToken (), support, element);
}

/**
 * @brief Obtains the API_AnalyticalSupportType from element , if it is a valid API_AnalyticalSupportType .
 * @ingroup Analytical
 * @since Archicad 26
 * @param element [in] The source for the support.
 * @param support [out] The support to be set.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetSupportFromElement	(const API_Element&			element,
																				 API_AnalyticalSupportType&	support)
{
	return ACAPI_Analytical_GetSupportFromElement (ACAPI_GetToken (), element, support);
}

/**
 * @brief Returns the Structural AnalyticalSupport %Geometry.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param elemGuid [in] The unique identifier of the internal Curve Element.
 * @param api_analyticalSupportGeometry [out] The Structural Analytical Support geometry.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalSupportGeometry	(const API_Guid&					amGuid,
																					 const API_Guid&					elemGuid,
																					 API_AnalyticalSupportGeometry&		api_analyticalSupportGeometry)
{
	return ACAPI_Analytical_GetAnalyticalSupportGeometry (ACAPI_GetToken (), amGuid, elemGuid, api_analyticalSupportGeometry);
}

/**
 * @brief Sets element.type to API_AnalyticalPointLoadID , and element.externalElemData to pointLoad .
 * @ingroup Analytical
 * @since Archicad 26
 * @param pointLoad [in] The source for the element.
 * @param element [out] The element to be set.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_SetElementFromPointLoad	(const API_AnalyticalPointLoadType&	pointLoad,
																				 API_Element&						element)
{
	return ACAPI_Analytical_SetElementFromPointLoad (ACAPI_GetToken (), pointLoad, element);
}

/**
 * @brief Obtains the API_AnalyticalPointLoadType from element , if it is a valid API_AnalyticalPointLoadType .
 * @ingroup Analytical
 * @since Archicad 26
 * @param element [in] The source for the pointLoad.
 * @param pointLoad [out] The pointLoad to be set.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetPointLoadFromElement	(const API_Element&				element,
																				 API_AnalyticalPointLoadType&	pointLoad)
{
	return ACAPI_Analytical_GetPointLoadFromElement (ACAPI_GetToken (), element, pointLoad);
}

/**
 * @brief Returns the Structural Analytical Point Load %Geometry.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural   Analytical Model.
 * @param elemGuid [in] The unique identifier of the internal Curve Element.
 * @param api_analyticalPointLoadGeometry [out] The Structural Analytical Point Load geometry.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalPointLoadGeometry	(const API_Guid&					amGuid,
																						 const API_Guid&					elemGuid,
																						 API_AnalyticalPointLoadGeometry&	api_analyticalPointLoadGeometry)
{
	return ACAPI_Analytical_GetAnalyticalPointLoadGeometry (ACAPI_GetToken (), amGuid, elemGuid, api_analyticalPointLoadGeometry);
}

/**
 * @brief Sets element.type to API_AnalyticalEdgeLoadID , and element.externalElemData to edgeLoad .
 * @ingroup Analytical
 * @since Archicad 26
 * @param edgeLoad [in] The source for the element.
 * @param element [out] The element to be set.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_SetElementFromEdgeLoad		(const API_AnalyticalEdgeLoadType&	edgeLoad,
																					 API_Element&						element)
{
	return ACAPI_Analytical_SetElementFromEdgeLoad (ACAPI_GetToken (), edgeLoad, element);
}

/**
 * @brief Obtains the API_AnalyticalEdgeLoadType from element , if it is a valid API_AnalyticalEdgeLoadType .
 * @ingroup Analytical
 * @since Archicad 26
 * @param element [in] The source for the edgeLoad.
 * @param edgeLoad [out] The edgeLoad to be set.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetEdgeLoadFromElement		(const API_Element&				element,
																					 API_AnalyticalEdgeLoadType&	edgeLoad)
{
	return ACAPI_Analytical_GetEdgeLoadFromElement (ACAPI_GetToken (), element, edgeLoad);
}

/**
 * @brief Returns the Structural Analytical Model's Analytical Edge Load %Geometry.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param elemGuid [in] The unique identifier of the Structural Analytical Member.
 * @param edgeLoadCustomData [out] The Analytical Edge Load %Geometry.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetEdgeLoadGeometry			(const API_Guid&			amGuid,
																					 const API_Guid&			elemGuid,
																					 API_EdgeLoadCustomData&	edgeLoadCustomData)
{
	return ACAPI_Analytical_GetEdgeLoadGeometry (ACAPI_GetToken (), amGuid, elemGuid, edgeLoadCustomData);
}

/**
 * @brief Set Structural Analytical Model's Analytical Edge Load %Geometry in the given memo.
 * @ingroup Analytical
 * @since Archicad 26
 * @param edgeLoadCustomData [in] The Analytical Edge Load %Geometry.
 * @param memo [out] Element memo.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_SetMemoFromEdgeLoadCustomData	(const API_EdgeLoadCustomData&	edgeLoadCustomData,
																						 API_ElementMemo&				memo)
{
	return ACAPI_Analytical_SetMemoFromEdgeLoadCustomData (ACAPI_GetToken (), edgeLoadCustomData, memo);
}

/**
 * @brief Get Structural Analytical Model's Analytical Edge Load %Geometry from the given memo.
 * @ingroup Analytical
 * @since Archicad 26
 * @param memo [in] Element memo.
 * @param edgeLoadCustomData [out] The Analytical Edge Load %Geometry.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_SetEdgeLoadCustomDataFromMemo	(const API_ElementMemo&		memo,
																						 API_EdgeLoadCustomData&	edgeLoadCustomData)
{
	return ACAPI_Analytical_SetEdgeLoadCustomDataFromMemo (ACAPI_GetToken (), memo, edgeLoadCustomData);
}

/**
 * @brief Sets element.type to API_AnalyticalSurfaceLoadID , and element.externalElemData to surfaceLoad .
 * @ingroup Analytical
 * @since Archicad 26
 * @param surfaceLoad [in] The source for the element.
 * @param element [out] The element to be set.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_SetElementFromSurfaceLoad		(const API_AnalyticalSurfaceLoadType&	surfaceLoad,
																						 API_Element&							element)
{
	return ACAPI_Analytical_SetElementFromSurfaceLoad (ACAPI_GetToken (), surfaceLoad, element);
}

/**
 * @brief Obtains the API_AnalyticalSurfaceLoadType from element , if it is a valid API_AnalyticalSurfaceLoadType .
 * @ingroup Analytical
 * @since Archicad 26
 * @param element [in] The source for the surfaceLoad.
 * @param surfaceLoad [out] The surfaceLoad to be set.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetSurfaceLoadFromElement		(const API_Element&				element,
																						 API_AnalyticalSurfaceLoadType&	surfaceLoad)
{
	return ACAPI_Analytical_GetSurfaceLoadFromElement (ACAPI_GetToken (), element, surfaceLoad);
}

/**
 * @brief Returns the Structural Analytical Model's Custom Surface Coordinates for Surface Load.
 * @ingroup Analytical
 * @since Archicad 26
 * @param amGuid [in] The unique identifier of the internal Structural Analytical Model.
 * @param elemGuid [in] The unique identifier of the Structural Analytical Member.
 * @param edgeLoadCustomData [out] The Custom Surface Coordinates for Surface Load.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetSurfaceLoadGeometry			(const API_Guid&			amGuid,
																						 const API_Guid&			elemGuid,
																						 API_SurfaceLoadCustomData&	edgeLoadCustomData)
{
	return ACAPI_Analytical_GetSurfaceLoadGeometry (ACAPI_GetToken (), amGuid, elemGuid, edgeLoadCustomData);
}

/**
 * @brief Set Structural Analytical Model's Custom Surface Coordinates for Surface Load in the given memo.
 * @ingroup Analytical
 * @since Archicad 26
 * @param customData [in] The Custom Surface Coordinates for Surface Load.
 * @param memo [out] Element memo.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_SetMemoFromSurfaceLoadCustomData	(const API_SurfaceLoadCustomData&	customData,
																						 API_ElementMemo&					memo)
{
	return ACAPI_Analytical_SetMemoFromSurfaceLoadCustomData (ACAPI_GetToken (), customData, memo);
}

/**
 * @brief Get Structural Analytical Model's Custom Surface Coordinates for Surface Load from the given memo.
 * @ingroup Analytical
 * @since Archicad 26
 * @param memo [in] Element memo.
 * @param customData [out] The Custom Surface Coordinates for Surface Load.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_SetSurfaceLoadCustomDataFromMemo	(const API_ElementMemo&		memo,
																						 API_SurfaceLoadCustomData&	customData)
{
	return ACAPI_Analytical_SetSurfaceLoadCustomDataFromMemo (ACAPI_GetToken (), memo, customData);
}

/**
 * @brief Returns an array of unique identifiers of the existing Load Groups.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadGroups [out] Array of unique identifiers.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalLoadGroups	(GS::Array<API_Guid>&	analyticalLoadGroups)
{
	return ACAPI_Analytical_GetAnalyticalLoadGroups (ACAPI_GetToken (), analyticalLoadGroups);
}

/**
 * @brief Returns the Load Group with the given unique identifier.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadGroupGuid [in] Unique identifier of the Load Group.
 * @param analyticalLoadGroup [out] The Structural Analytical Load Group.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- Error - There is no load group with the given unique identifier.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalLoadGroup	(const API_Guid&			analyticalLoadGroupGuid,
																				 API_AnalyticalLoadGroup&	analyticalLoadGroup)
{
	return ACAPI_Analytical_GetAnalyticalLoadGroup (ACAPI_GetToken (), analyticalLoadGroupGuid, analyticalLoadGroup);
}

/**
 * @brief Creates an Analytical Load Group.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadGroup [in/out] The Load Group data to create the Load Group from. Initially if the guid field is given, we will use it at the time of creation (if does not already exist), otherwise we will generate one and return it through this parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- Error - The creation was not successful (most probably due to already existing guid).
 */
inline  GSErrCode ACAPI_Analytical_CreateAnalyticalLoadGroup	(API_AnalyticalLoadGroup&	analyticalLoadGroup)
{
	return ACAPI_Analytical_CreateAnalyticalLoadGroup (ACAPI_GetToken (), analyticalLoadGroup);
}

/**
 * @brief Deletes an Analytical Load Group.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadGroupGuid [in] The unique identifier of the desired Load Group to be deleted.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_DeleteAnalyticalLoadGroup	(const API_Guid&	analyticalLoadGroupGuid)
{
	return ACAPI_Analytical_DeleteAnalyticalLoadGroup (ACAPI_GetToken (), analyticalLoadGroupGuid);
}

/**
 * @brief Returns an array of unique identifiers of all the existing Load Cases from every Load Group.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadCases [out] Array of unique identifiers.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAllAnalyticalLoadCases	(GS::Array<API_Guid>&	analyticalLoadCases)
{
	return ACAPI_Analytical_GetAllAnalyticalLoadCases (ACAPI_GetToken (), analyticalLoadCases);
}

/**
 * @brief Returns an array of unique identifiers of the existing Load Cases from a Load Group.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadGroupGuid [in] The unique identifier of the Load Group.
 * @param analyticalLoadCases [out] Array of unique identifiers.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalLoadCases	(const API_Guid&		analyticalLoadGroupGuid,
																				 GS::Array<API_Guid>&	analyticalLoadCases)
{
	return ACAPI_Analytical_GetAnalyticalLoadCases (ACAPI_GetToken (), analyticalLoadGroupGuid, analyticalLoadCases);
}

/**
 * @brief Returns the Load Case with the given unique identifier.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadCaseGuid [in] Unique identifier of the Load Case.
 * @param analyticalLoadCase [out] The Structural Analytical Load Case.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- Error - There is no load case with the given unique identifier.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalLoadCase	(const API_Guid&			analyticalLoadCaseGuid,
																				 API_AnalyticalLoadCase&	analyticalLoadCase)
{
	return ACAPI_Analytical_GetAnalyticalLoadCase (ACAPI_GetToken (), analyticalLoadCaseGuid, analyticalLoadCase);
}

/**
 * @brief Creates an Analytical Load Group.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadCase [in/out] The Load Case data to create the Load Case from. Initially if the guid field is given, we will use it at the time of creation (if does not already exist), otherwise we will generate one and return it through this parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- Error - The creation was not successful (most probably due to already existing guid).
 */
inline  GSErrCode ACAPI_Analytical_CreateAnalyticalLoadCase	(API_AnalyticalLoadCase&	analyticalLoadCase)
{
	return ACAPI_Analytical_CreateAnalyticalLoadCase (ACAPI_GetToken (), analyticalLoadCase);
}

/**
 * @brief Deletes an Analytical Load Group.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadCaseGuid [in] The unique identifier of the desired Load Case to be deleted.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_DeleteAnalyticalLoadCase	(const API_Guid&	analyticalLoadCaseGuid)
{
	return ACAPI_Analytical_DeleteAnalyticalLoadCase (ACAPI_GetToken (), analyticalLoadCaseGuid);
}

/**
 * @brief Returns an array of unique identifiers of the existing Load Combinations.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadCombinations [out] Array of unique identifiers.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalLoadCombinations	(GS::Array<API_Guid>&	analyticalLoadCombinations)
{
	return ACAPI_Analytical_GetAnalyticalLoadCombinations (ACAPI_GetToken (), analyticalLoadCombinations);
}

/**
 * @brief Returns the Load Combination with the given unique identifier.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadCombinationGuid [in] Unique identifier of the Load combination.
 * @param analyticalLoadCombination [out] The Structural Analytical Load combination.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- Error - There is no load combination with the given unique identifier.
 */
inline  GSErrCode ACAPI_Analytical_GetAnalyticalLoadCombination	(const API_Guid&				analyticalLoadCombinationGuid,
																					 API_AnalyticalLoadCombination&	analyticalLoadCombination)
{
	return ACAPI_Analytical_GetAnalyticalLoadCombination (ACAPI_GetToken (), analyticalLoadCombinationGuid, analyticalLoadCombination);
}

/**
 * @brief Creates an Analytical Load Combination.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadCombination [in/out] The Load Combination data to create the Load Combination from. Initially if the guid field is given, we will use it at the time of creation (if does not already exist), otherwise we will generate one and return it through this parameter.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- Error - The creation was not successful (most probably due to already existing guid).
 */
inline  GSErrCode ACAPI_Analytical_CreateAnalyticalLoadCombination	(API_AnalyticalLoadCombination&		analyticalLoadCombination)
{
	return ACAPI_Analytical_CreateAnalyticalLoadCombination (ACAPI_GetToken (), analyticalLoadCombination);
}

/**
 * @brief Adds a Load Case (with its adherent coefficients) to a Load Combination identified with guid.
 * @ingroup Analytical
 * @since Archicad 26
 * @param loadFactor [in] Analytical Load Factor (load case guid, load factor and multiplier) which will be added to the Load combination.
 * @param analyticalLoadCombinationGuid [in] Unique identifier of the Load combination.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_AddLoadCaseToLoadCombination	(const API_AnalyticalLoadFactor&	loadFactor,
																					 const API_Guid&					analyticalLoadCombinationGuid)
{
	return ACAPI_Analytical_AddLoadCaseToLoadCombination (ACAPI_GetToken (), loadFactor, analyticalLoadCombinationGuid);
}

/**
 * @brief Deletes an Analytical Load Combination.
 * @ingroup Analytical
 * @since Archicad 26
 * @param analyticalLoadCombinationGuid [in] The unique identifier of the desired Load Combination to be deleted.
 * @return
 * 			- NoError - The function has completed with success.
 */
inline  GSErrCode ACAPI_Analytical_DeleteAnalyticalLoadCombination	(const API_Guid&	analyticalLoadCombinationGuid)
{
	return ACAPI_Analytical_DeleteAnalyticalLoadCombination (ACAPI_GetToken (), analyticalLoadCombinationGuid);
}



#endif