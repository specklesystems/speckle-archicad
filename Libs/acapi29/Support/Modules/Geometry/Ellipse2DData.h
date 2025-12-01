// *****************************************************************************
// 2D Ellipse and its operations
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************
#if !defined (ELLIPSE_H)
#define ELLIPSE_H

#pragma once

#include "GeometricDefinitions.h"
#include "Point2D.hpp"

struct ArcDivParams;
struct Sector;

namespace Geometry
{

class Circle2D;
class GenArc;

class GEOMETRY_DLL_EXPORT Ellipse
{
public:
	Ellipse ();
	Ellipse (const Point2D& origo, double radius, double mainAxisDir);
	Ellipse (const Point2D& origo, double mainAxisLength, double axisLengthRatio, double mainAxisDir);

	const Point2D&	GetOrigo () const;
	double			GetMainAxisLength () const;
	double			GetOtherAxisLength () const;
	double			GetMainAxisDir () const;
	double			GetAxisLengthRatio () const;
	Geometry::Vector2d GetMainAxis () const;
	Geometry::Vector2d GetOtherAxis () const;
	void			GetGeometry (Point2D& f1,  Point2D& f2, double& D) const; 
	bool			IsElliptic (double eps = EPS) const;

	void			SetOrigo (const Point2D& origo);
	void			SetMainAxisLength (double mainAxisLength);
	void			SetMainAxisDir (double mainAxisDir);
	void			SetAxisLengthRatio (double axisLengthRatio);
	void			Set (const Point2D& origo, double mainAxisLength, double axisLengthRatio, double mainAxisDir);
	void			SetToCircle (const Point2D& origo, double radius, double mainAxisDir);

	bool			IsPointOn (const Point2D& point) const;
	double			CalcAngle (const Point2D& ellipsePoint) const;
	Point2D			CalcEllipsePoint (double angle) const;
	Vector2D		CalcOutNormal (double angle) const;
	void			Snap (Point2D& p) const;

	GSErrCode		Write (GS::OChannel& oc) const;
	GSErrCode		Read (GS::IChannel& ic);
	GSErrCode		WriteXML (GS::XMLOChannel& oc) const;
	GSErrCode		ReadXML (GS::XMLIChannel& ic);

	GSErrCode		Store (GS::ObjectState& os) const;
	GSErrCode		Restore (const GS::ObjectState& os);

private:
	Point2D	m_origo;
	double	m_mainAxisLength;
	double	m_axisLengthRatio;	// mainAxis / otherAxis		
	double	m_mainAxisDir;
};



	GEOMETRY_DLL_EXPORT double ComputeEllipseFi (const GenArc* pArc, const Point2D* pt);

	GEOMETRY_DLL_EXPORT double ComputeEllipse_t (const GenArc* pArc, const Point2D* pt);

	GEOMETRY_DLL_EXPORT void ComputeEllipseCoord (const GenArc* pArc, double fi, Point2D* pt);

	GEOMETRY_DLL_EXPORT Point2D ComputeEllipseCoord (const GenArc& pArc, double givenLen);

	GEOMETRY_DLL_EXPORT void GetEllipseVal (const GenArc* pArc, double	t/* parameter 0..1 */, Point2D* ptResult);

	GEOMETRY_DLL_EXPORT void GetEllipseTan (const GenArc* ell, const Point2D* c, Vector2D* tan);

	GEOMETRY_DLL_EXPORT double EllipseLen (
							double	a,									/* sm176 */
							double	b,
							double	t1,
							double	t2,
							Int32	*nDiv);

	GEOMETRY_DLL_EXPORT double EllipseLen (const GenArc& genArc);

	GEOMETRY_DLL_EXPORT double Ellipse_ax (
							double 		ax1,								/* sm176 */
							double		ax2,
							double		a,
							double		endAng,
							double		givenLen);




	GEOMETRY_DLL_EXPORT void DoAffinPt (const Sector 	*ax,			/* affinitas tengelye, egysegvektor! sm121 */
										Point2D			*c,
										double			ratio);

	GEOMETRY_DLL_EXPORT char XEllipseLineEps (
							const GenArc* elli,			/* sm065 */
							const Sector* sLin,
							Sector*       sResult,
							double		  eps);


	GEOMETRY_DLL_EXPORT char XEllipseRayEps (
							const GenArc* elli,
							const Sector* sLin,
							Sector*       sResult,
							double		  eps);


	GEOMETRY_DLL_EXPORT char XEllipseSectorEps (
							const GenArc* elli,
							const Sector* sLin,
							Sector*       sResult,
							double		  eps);


	GEOMETRY_DLL_EXPORT Int32 XEllipseCircle (const GenArc*	ell1,			/* sm120 */
											  const Circle2D*	cir2,
											  Point2D*		sect);		/* 4 koordinatanak kell hely! */

	GEOMETRY_DLL_EXPORT Int32 XEllipseEllipse (const GenArc*	ell1,		/* sm120 */
											   const GenArc*	ell2,
											   Point2D*			sect);		/* 4 koordinatanak kell hely! */

	GEOMETRY_DLL_EXPORT void GetEllipseNearPt (const GenArc*	ell1,		/* sm122 */
											   const Point2D*  basePt,		/* bazispont (innen nezzuk) */
											   double			estimDist,	/* becsult tavolsag */
											   Point2D*        nearPt);	/* eredmeny */

	GEOMETRY_DLL_EXPORT void	DistortEllipse (
							Ellipse			*ell,				/* bemenet/kimenet */			/* sm126 */
							double			factor);			/* torzitas aranya: y *= factor	*/

	GEOMETRY_DLL_EXPORT Int32	DivEllipsePart (
							const GenArc 	*pEll,					/* sm123 */
							bool			forw,
							const Point2D		*startCo,
							double			partLength,
							Point2D			**hCo);

	GEOMETRY_DLL_EXPORT Int32	DivEllipseDiff (
							const GenArc*	pEll,			/* sm123 */
							bool			forw,
							double			diff,
							Point2D**			hCo);

	GEOMETRY_DLL_EXPORT void	DivideEllArcToCo (
							const GenArc&	ellipseArc,
							double			maxArcDifference,
							Point2D**         hCo,
							USize* const    nCo);

	GEOMETRY_DLL_EXPORT void	DivideEllArcToCo (
							const GenArc&	ellipseArc,
							double			maxArcDifference,
							GS::Array<Point2D>&	co);

	GEOMETRY_DLL_EXPORT void	DivideEllArcToArcs (
							const GenArc&		ellipseArc,
							const ArcDivParams&	params,
							GS::Array<Point2D>&	co, 
							GS::Array<Point2D>&	arcCenters);

	GEOMETRY_DLL_EXPORT bool	CanArcBeReplacedWithSegment (const GenArc& ellipseArc);


	GEOMETRY_DLL_EXPORT bool	EllipseTangentCircle (const GenArc		*pEll,				/* sm123 */
													  const Point2D		*f1,
													  const Point2D		*f2,
													  Point2D			*origo,
													  double			arcDiff,
													  bool 				*exist);

	GEOMETRY_DLL_EXPORT Int32	DivEllipseDiff_Arc (const GenArc	*pEll,			/* sm123 */
													bool			forw,
													double			diff,
													Point2D			**hCo);

	GEOMETRY_DLL_EXPORT Ellipse	GetEllipse (const GenArc& arc);

	GEOMETRY_DLL_EXPORT Sector	GetAffineAxis (const GenArc& arc);

	GEOMETRY_DLL_EXPORT Point2D	AffineTransform (const Point2D& c, const Sector& axis, double ratio);

	GEOMETRY_DLL_EXPORT bool   AreSameEllipse (const Ellipse& e1, const Ellipse& e2);

	GEOMETRY_DLL_EXPORT GSErrCode	ReadXMLEllipse (GS::XMLIChannel& ic, Geometry::Ellipse& ellipse);
	GEOMETRY_DLL_EXPORT GSErrCode	WriteXMLEllipse (GS::XMLOChannel& oc, const Geometry::Ellipse& ellipse);
	inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Geometry::Ellipse& ellipse)	{ return Geometry::ReadXMLEllipse (ic, ellipse); }
	inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Geometry::Ellipse& ellipse)	{ return Geometry::WriteXMLEllipse (oc, ellipse); }

} // namespace Geometry

#endif
