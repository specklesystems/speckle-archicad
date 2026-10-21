// *****************************************************************************
// 2D POLYGON OPERATIONS
// Combination of the struct and the callback functions
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************

#if !defined (POLYGON2DOPERATIONSX_H)
#define POLYGON2DOPERATIONSX_H

#pragma once

#include "GeometricDefinitions.h"
#include "Point2DData.h"
#include "Box2DData.h"
#include "HalfPlane2DData.h"
#include "Plane3DData.h"
#include "Polygon2DOperations.h"

namespace Geometry {

DECLARE_EXCEPTION_CLASS (SelfIntersectingPGPolygonException,	GeometryIllegalArgumentException,			  PGSelfintersect,	GEOMETRY_DLL_EXPORT)


// Whole polygon operations

GEOMETRY_DLL_EXPORT double				PGXPolyAreaExt (
					const PGPOLYEXT*	polygon,
					double*				thole);

GEOMETRY_DLL_EXPORT void				PGXPolyRemoveHolesExt (
					const PGPOLYEXT*	polygon,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT void				PGXIsPolyRegularExt (
					const PGPOLYEXT*	originalPolygon,
					bool*				isPolyRegular);

GEOMETRY_DLL_EXPORT void				PGXPolyMakeRegular2Ext (
					const PGPOLYEXT*		originalPolygon,
					PGRESPOLYEXT*			newPolygons,
					bool					resolveSelfInters,
					GS::AbortInterfaceBase*	breaker = nullptr,
					PGRegulHoleHandling		holeHandling = ThrowInvalidHoles,
					PGRelPolyPosExt*		status = nullptr,
					PolyRegularizationMode	mode = PolyRegularizationMode_Default);

// Contour operations

GEOMETRY_DLL_EXPORT void				PGXPolyResizeContourExt (
					const PGPOLYEXT*	originalPolygon,
					UIndex				contourIdx,
					double				offset,
					PGRESPOLYEXT*		newPolygons);
// Vertex operations

GEOMETRY_DLL_EXPORT void				PGXPolyMoveVertexExt (
					const PGPOLYEXT*	polygon,
					UIndex				movedVertexIdx,
					const Point2D&		newVertexPosition,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT void				PGXPolyGetMaxVertexFilletExt (
					const PGPOLYEXT*	poly,
					UIndex				filletedVertexIdx,
					double*				maxFilletRadius);

GEOMETRY_DLL_EXPORT void				PGXPolyFilletVertexExt (
					const PGPOLYEXT*	polygon,
					UIndex				filletedVertexIdx,
					double				filletRadius,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT void				PGXPolyFilletContourExt (
					const PGPOLYEXT*	polygon,
					UIndex				filletedContourIdx,
					double				filletRadius,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT void				PGXPolyChamferVertexExt (
					const PGPOLYEXT*	polygon,
					UIndex				chamferedVertexIdx,
					double				chamferRadius,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT void				PGXPolyChamferContourExt (
					const PGPOLYEXT*	polygon,
					UIndex				chamferedContourIdx,
					double				chamferRadius,
					PGRESPOLYEXT*		newPolygons);

// Edge operations

GEOMETRY_DLL_EXPORT void				PGXPolyInsertVertexExt (
					const PGPOLYEXT*	polygon,
					UIndex				breakedEdgeIdx,
					const Point2D&		newVertexPosition,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT void				PGXPolySetEdgeAngleExt (
					const PGPOLYEXT*	polygon,
					UIndex				edgeIdx,
					double				viewAngle,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT void				PGXPolyOffsetEdgeExt (
					const PGPOLYEXT*	polygon,
					UIndex				edgeIdx,
					double				offset,
					PGRESPOLYEXT*		newPolygons);

GEOMETRY_DLL_EXPORT void				PGXPolyOffsetEdgeFixAreaExt (
					const PGPOLYEXT*	polygon,
					UIndex				edgeIdx,
					UIndex				vertIdx,
					double				offset,
					double				area,
					PGRESPOLYEXT*		newPolygons);

//C-018
GEOMETRY_DLL_EXPORT void				PGXPolyDeleteEdgeExt (
					const PGPOLYEXT*	polygon,
					UIndex				edgeIdx,
					bool*				deleteAble,
					PGRESPOLYEXT*		newPolygons);

// Polygon - Point operations

GEOMETRY_DLL_EXPORT PGPositionExt			PGXCoordInPolyExt (
					const PGPOLYEXT*	polygon,
					const Point2D*		p,
					bool				mainContOnly);

// Polygon - Point operations with arcs

GEOMETRY_DLL_EXPORT PGPositionExt			PGXPoint2DPosition (
					const Geometry::PGPOLYEXT*	polygon,
					const Point2D*				p,
					bool						mainContOnly);

// Polygon - Sector operations

GEOMETRY_DLL_EXPORT PGPositionExt			 PGXSegmentInPolyExt (
					const PGPOLYEXT*		polygon,
					Point2D*					bp,
					Point2D*					ep,
					bool					complement,
					PGRESSECTOREXT*			newSectors,
					GS::AbortInterfaceBase*	breaker = nullptr);

// Polygon - polygon operations

GEOMETRY_DLL_EXPORT void				PGXPolyPositionExt (
					const PGPOLYEXT*			polygon1,
					const PGPOLYEXT*			polygon2,
					PGRelPolyPosExt*			status,
					GS::AbortInterfaceBase*		breaker = nullptr);

GEOMETRY_DLL_EXPORT void				PGXPolyUnionExt (
					const PGPOLYEXT*	polygon1,
					const PGPOLYEXT*	polygon2,
					PGRESPOLYEXT*		newPolygons,
					PGRelPolyPosExt*	status);

GEOMETRY_DLL_EXPORT void				PGXPolyIntersectionExt (
					const PGPOLYEXT*	polygon1,
					const PGPOLYEXT*	polygon2,
					PGRESPOLYEXT*		newPolygons,
					PGRelPolyPosExt*	status);

GEOMETRY_DLL_EXPORT void				PGXPolyDifferenceExt (
					const PGPOLYEXT*			polygon1,
					const PGPOLYEXT*			polygon2,
					PGRESPOLYEXT*				newPolygons,
					PGRelPolyPosExt*			status,
					GS::AbortInterfaceBase*		breaker = nullptr);

GEOMETRY_DLL_EXPORT void				PGXPolyCreateCommonEdgeSectionsExt (
					const PGPOLYEXT*	polygon1,
					const PGPOLYEXT*	polygon2,
					PGRESPOLYEXT*		newPolygons);

}

#endif
