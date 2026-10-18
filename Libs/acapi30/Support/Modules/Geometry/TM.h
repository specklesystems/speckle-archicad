// *****************************************************************************
// GLOBAL CONSTANTS AND PROTOTYPES, FOR TM... ROUTINES
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************

#ifndef	TM_H
#define	TM_H

#pragma once

#include	"GeometricDefinitions.h"
#include	"Point3DData.h"
#include	"TRANMAT.h"

struct PlaneEq;

enum TMTranCode {
		TM_ADD_X,
		TM_ADD_Y,
		TM_ADD_Z,
		TM_ROT_X,
		TM_ROT_Y,
		TM_ROT_Z,
		TM_SCA_X,
		TM_SCA_Y,
		TM_SCA_Z
};

/*================================	PROTOTYPES	============================*/

namespace Geometry {

class Transformation2D;

GEOMETRY_DLL_EXPORT void	TMScale3D (TRANMAT *tran, double scaleFactor);

GEOMETRY_DLL_EXPORT void	TMCompute (TRANMAT* tran, Int32 ntran, const TRANMAT* trans);

GEOMETRY_DLL_EXPORT TRANMAT	CreateTransformationFromCodes	(Int32 ntran, const TMTranCode* code, const double* value);
GEOMETRY_DLL_EXPORT TRANMAT	TMComposeTransformations		(const TRANMAT& tranLeft, const TRANMAT& tranRight);

GEOMETRY_DLL_EXPORT TRANMAT	TransformCoordinateSystem (const Point3D &e1, const Point3D &e2, const Point3D &e3);

GEOMETRY_DLL_EXPORT TRANMAT	WorldToLocalTrafo	(const Point3D& start, const Point3D& xAxis, const Point3D& yAxis);
GEOMETRY_DLL_EXPORT TRANMAT	LocalToWorldTrafo	(const Point3D& start, const Point3D& xAxis, const Point3D& yAxis);

GEOMETRY_DLL_EXPORT TRANMAT	WorldToLocalTrafo2D	(const Point2D& start, const Vector2D& xAxis);
GEOMETRY_DLL_EXPORT TRANMAT	LocalToWorldTrafo2D	(const Point2D& start, const Vector2D& xAxis);
GEOMETRY_DLL_EXPORT TRANMAT	MirrorTrafo2D		(const Point2D& axisPoint, const Vector2D& axisDir);

GEOMETRY_DLL_EXPORT TRANMAT	ProjectionToPlaneTrafo	(const Vector3D& direction, const PlaneEq& plane);

GEOMETRY_DLL_EXPORT GSErrCode	TMFit2D (TRANMAT* tr,
										const Point2D& originalPoint1,
										const Point2D& originalPoint2,
										const Point2D& originalPoint3,
										const Point2D& transformedPoint1,
										const Point2D& transformedPoint2,
										const Point2D& transformedPoint3);

GEOMETRY_DLL_EXPORT Point3D		TransformPoint	(const TRANMAT& tran, const Point3D& point);
GEOMETRY_DLL_EXPORT Vector3D	TransformUnitNormalVector (const TRANMAT& tran, const Vector3D& vector);
GEOMETRY_DLL_EXPORT void		TMBackVector	(const TRANMAT *tran, double *x, double *y, double *z);

GEOMETRY_DLL_EXPORT void		TMPlaneWithInverse (
												const TRANMAT& tran,
												const TRANMAT& inverse,
												double& pa,
												double& pb,
												double& pc,
												double& pd);

GEOMETRY_DLL_EXPORT void		TMPlane (
												const TRANMAT& tran,
												double& pa,
												double& pb,
												double& pc,
												double& pd);
	
GEOMETRY_DLL_EXPORT void		TMPlaneWithInverse (
												const TRANMAT& tran,
												const TRANMAT& inverse,
												PlaneEq& plane);
	
GEOMETRY_DLL_EXPORT void		TMPlane (const TRANMAT& tran, PlaneEq& plane);

GEOMETRY_DLL_EXPORT Vector3D	TransformUnitVectorWithoutShift (const TRANMAT& tran, const Vector3D& vector);
GEOMETRY_DLL_EXPORT Vector2D	TransformUnitVectorWithoutShift (const TRANMAT& tran, const Vector2D& vector);
GEOMETRY_DLL_EXPORT Vector3D	TransformVectorWithoutShift (const TRANMAT& tran, const Vector3D& vector);

GEOMETRY_DLL_EXPORT void		TMPosDir2Tran (
												short axis,
												double posx, double posy, double posz,
												double dirx, double diry, double dirz,
												TRANMAT *tran);

GEOMETRY_DLL_EXPORT void		TM2dPoint (const TRANMAT *tran, double *x, double *y);
GEOMETRY_DLL_EXPORT Point2D		Transform2dPoint (const TRANMAT &tran, const Point2D& point);


GEOMETRY_DLL_EXPORT void		TM2dDecompose (
												const TRANMAT *tran,
												double *angle,
												double *xs, double *ys,
												double *xd, double *yd);

GEOMETRY_DLL_EXPORT GSErr		TMDecomposeMat2 (const TRANMAT *tran, double *c1, double *c2, double *alpha, double *beta);

GEOMETRY_DLL_EXPORT void		TMCalcArc (
												double x0, double y0,
												double r1, double r2,
												double alpha, double beta,
												Int32 *ncs,
												const TRANMAT& tran,
												double *coords);

//Use this if GetTrScale needed
GEOMETRY_DLL_EXPORT double 	GetTrScale (const Transformation2D& tran);
//Don't use this, instead use the upper one
GEOMETRY_DLL_EXPORT double	GetTrScale (const TRANMAT* tran);

//Use this if TranAngle needed
GEOMETRY_DLL_EXPORT void		TranAngle	(const Transformation2D& tran, double* angle);
//Don't use this, instead use the upper one
GEOMETRY_DLL_EXPORT void		TranAngle	(const TRANMAT* tran, double* angle);


GEOMETRY_DLL_EXPORT void		TranVectxy	(const TRANMAT* tran, double* vx, double* vy);


//Use this if TranDecompose needed
GEOMETRY_DLL_EXPORT bool		TranDecompose (
												const Transformation2D&	tran,
												double			*angle,
												double			*xs,
												double			*ys,
												double			*xt,
												double			*yt,
												double			eps = EPS);

//Don't use this, instead of this use the upper one
GEOMETRY_DLL_EXPORT bool		TranDecompose (
												const TRANMAT	*tran,
												double			*angle,
												double			*xs,
												double			*ys,
												double			*xt,
												double			*yt,
												double			eps = EPS);

GEOMETRY_DLL_EXPORT bool		TranValid (const TRANMAT& tran);

GEOMETRY_DLL_EXPORT	bool		IsUnitaryTransformation (const TRANMAT& tran);

GEOMETRY_DLL_EXPORT bool		TMIsPreserveArc (const TRANMAT& tran);

//compares T1 and T2 with tolerance (EPS), geomSize must be the typical size of your geometry.
GEOMETRY_DLL_EXPORT bool		TMAreIdentical	(const TRANMAT &T1, const TRANMAT &T2, double geomSize);
GEOMETRY_DLL_EXPORT bool		TMConjug		(TRANMAT *ctran, TRANMAT *atran, TRANMAT *btran, bool avers);
GEOMETRY_DLL_EXPORT bool		TMComplementer	(TRANMAT *ctran, const TRANMAT *atran, const TRANMAT *btran, const bool avers);
GEOMETRY_DLL_EXPORT bool		TMInvert		(TRANMAT *btran, const TRANMAT *atran);

//Instead of this use Geometry::*Transformation*D Add() or operator* functions
GEOMETRY_DLL_EXPORT void		TMMatProduct	(TRANMAT *ctran, const TRANMAT *atran, const TRANMAT *btran);

GEOMETRY_DLL_EXPORT void		Def_SyTranMatrix (const Vector2D*		loc,
												 double					angle,
												 double					xs,
												 double					ys,
												 TRANMAT*				tran);

GEOMETRY_DLL_EXPORT GSErrCode	ReadTRANMATXML (GS::XMLIChannel& ic, TRANMAT& tran, const char* tagName = nullptr);
GEOMETRY_DLL_EXPORT GSErrCode	WriteTRANMATXML (GS::XMLOChannel& oc, const TRANMAT& tran, const char* tagName = nullptr);
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, TRANMAT& tran)	{ return Geometry::ReadTRANMATXML (ic, tran); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const TRANMAT& tran)	{ return Geometry::WriteTRANMATXML (oc, tran); }

#ifdef DEBUVERS
inline void								TMDBPrintf (const TRANMAT &tran);
#endif
}



#ifdef DEBUVERS
inline void Geometry::TMDBPrintf (const TRANMAT &tran)
{
	DBPRINTF ("tran\n");
	DBPRINTF ("\t.status=%x -> ", static_cast<int>(tran.status));
	if (tran.status & TR_IDENT)			DBPRINTF ("TR_IDENT ");
	if (tran.status & TR_DET_1)			DBPRINTF ("TR_DET_1 ");
	if (tran.status & TR_SINGULAR)		DBPRINTF ("TR_SINGULAR ");
	if (tran.status & TR_MIRROR)		DBPRINTF ("TR_MIRROR ");
	if (tran.status & TR_TRANSL_ONLY)	DBPRINTF ("TR_TRANSL_ONLY ");
	if (tran.status & TR_SCALE_ONLY)	DBPRINTF ("TR_SCALE_ONLY ");
	if (tran.status & TR_ROTATE_ONLY)	DBPRINTF ("TR_ROTATE_ONLY ");
	if (tran.status & TR_TRANSL_INCL)	DBPRINTF ("TR_TRANSL_INCL ");
	if (tran.status & TR_SCALE_INCL)	DBPRINTF ("TR_SCALE_INCL ");
	if (tran.status & TR_UNDECOMPOSED)	DBPRINTF ("TR_UNDECOMPOSED");
	DBPRINTF ("\n");
	DBPRINTF ("\t.dummy1=%x\n", static_cast<int>(tran.dummy1));
	DBPRINTF ("\t.dummy2=%x\n", static_cast<int>(tran.dummy2));
	DBPRINTF ("\t.dummy3=%x\n", static_cast<int>(tran.dummy3));
		DBPRINTF (\
		"\t.tmx={{%f, %f, %f, %f}, {%f, %f, %f, %f}, {%f, %f, %f, %f}}\n", \
		tran.GetMatrix ().Get (0,0), tran.GetMatrix ().Get (0,1), tran.GetMatrix ().Get (0,2), tran.GetMatrix ().Get (0,3), \
		tran.GetMatrix ().Get (1,0), tran.GetMatrix ().Get (1,1), tran.GetMatrix ().Get (1,2), tran.GetMatrix ().Get (1,3), \
		tran.GetMatrix ().Get (2,0), tran.GetMatrix ().Get (2,1), tran.GetMatrix ().Get (2,2), tran.GetMatrix ().Get (2,3)\
		);

	DBPRINTF ("end tran\n");
}
#endif

#endif
