#if !defined (GENARC2DDATA_H)
#define GENARC2DDATA_H

#pragma once

#include "GeometricDefinitions.h"
#include "Box2DData.h"
#include "Ellipse2DData.h"
#include "AngleData.h"
#include "Sector2DData.h"
#include "UnitVector2DClassDeclaration.hpp"

/****************************************************************************/

namespace GS {
template <class Type> class Array;
}

/****************************************************************************/
/*																			*/
/*				2D Generic Arc and its operations							*/
/*																			*/
/****************************************************************************/

namespace Geometry
{

class Direction2D;

enum SetArcResult
{
	ArcCanNotBeCreatedFromParameters,
	ArcIsCreated
};

class Transformation2D;

class GEOMETRY_DLL_EXPORT GenArc final {
public:
	GenArc ();

	virtual ~GenArc ();

	static GenArc	CreateFullCircle	(const Point2D& origo, double radius, bool reflected = false);
	static GenArc	CreateCircleArc		(const Point2D& origo, const Point2D& begC, const Point2D& endC, bool reflected = false);
	static GenArc	CreateCircleArc		(const Point2D& begC, const Point2D& endC, double angle);
	static GenArc	CreateCircleArc		(const Point2D& origo, double radius, double begAng, double endAng, bool reflected = false);
	static GenArc	CreateFullEllipse	(const Ellipse& ellipse, bool reflected = false);
	static GenArc	CreateEllipseArc	(const Ellipse& ellipse, const Point2D& begC, const Point2D& endC, bool reflected = false);
	static GenArc	CreateEllipseArc	(const Ellipse& ellipse, double begAng, double endAng, bool reflected = false);
	static GenArc	CreateEllipseArc	(const Point2D& origo, const Point2D& begC, const Point2D& endC, double mainAxisDir, double axisLengthRatio, bool reflected = false);

	static bool		IsValidEllipseArc	(const Point2D& origo, const Point2D& begC, const Point2D& endC, double mainAxisDir, double axisLengthRatio);

	// getters
	const Ellipse&	GetEllipse			() const { return m_ellipse; }
	const Point2D&	GetOrigo			() const { return m_ellipse.GetOrigo (); }
	double			GetMainAxisLength	() const { return m_ellipse.GetMainAxisLength (); }
	double			GetOtherAxisLength	() const { return m_ellipse.GetOtherAxisLength (); }
	double			GetMainAxisDir		() const { return m_ellipse.GetMainAxisDir (); }
	double			GetAxisLengthRatio	() const { return m_ellipse.GetAxisLengthRatio (); }
	bool			IsElliptic			() const { return m_ellipse.IsElliptic (); }
	const Point2D&	GetBegC				() const { return m_begC; }
	const Point2D&	GetEndC				() const { return m_endC; }
	double			GetBegAng			() const { return m_begAng; }
	double			GetEndAng			() const { return m_endAng; }
	double			GetArcAngle			() const;
	bool			IsReflected			() const { return m_reflected; }
	bool			IsWhole				() const { return m_whole; }

	SetArcResult	SetToFullCircle		(const Point2D& origo, double radius, double mainAxisDir = 0.0, bool reflected = false);
	SetArcResult	SetToCircleArc		(const Point2D& origo, const Point2D& begC, const Point2D& endC, bool reflected = false);
	SetArcResult	SetToCircleArc		(const Point2D& begC, const Point2D& endC, double angle);
	SetArcResult	SetToCircleArc		(const Point2D& origo, double radius, double begAng, double endAng, bool reflected = false);

	SetArcResult	SetToFullEllipse	(const Ellipse& ellipse, bool reflected = false);
	SetArcResult	SetToEllipseArc		(const Ellipse& ellipse, const Point2D& begC, const Point2D& endC, bool reflected = false);
	SetArcResult	SetToEllipseArc		(const Ellipse& ellipse, double begAng, double endAng, bool reflected = false);
	SetArcResult	SetToEllipseArc		(const Point2D& origo, const Point2D& begC, const Point2D& endC, double mainAxisDir, double axisLengthRatio, bool reflected = false);

	// other modifiers
	void			Reflect ();
	void			Offset (const Vector2D& offset);		// modifies begC and endC
	void			Resize (double newMainAxisLength);	// modifies begC and endC

	bool			IsEqual (const GenArc& other) const;

	// calculations
	void			Snap (Point2D& p) const;

	// I/O
	GSErrCode		Write (GS::OChannel& oc) const;
	GSErrCode		Read (GS::IChannel& ic);
	GSErrCode		WriteXML (GS::XMLOChannel& oc) const;
	GSErrCode		ReadXML (GS::XMLIChannel& ic);
private:
	GSErrCode		WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode		ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

private:
	Ellipse		m_ellipse;
	Point2D		m_begC;
	Point2D		m_endC;
	double		m_begAng;		// derived data	
	double		m_endAng;		// derived data
	bool		m_reflected;
	bool		m_whole;

	void RecalcBegCoord ();
	void RecalcEndCoord ();
	void RecalcBegAng ();
	void RecalcEndAng ();
};

}

using Geometry::GenArc;

struct GEOMETRY_DLL_EXPORT ArcDivParams {
	bool				preferSegmentedArcEnds;
	bool				preferCircArcsOverStraightSegments;
	bool				preferArcsBasedSegmentation;
	bool				preferStaticSegmentation;		//only when preferArcsBasedSegmentation is true!

	double				maxDifference;
	const Box2DData*	boxToKeepMaxDifferenceIn;

	ArcDivParams ();
	ArcDivParams (double maxDifference);
	ArcDivParams (double maxDifference, const Box2DData* boxToKeepMaxDifferenceIn);
};

namespace Geometry {

	GEOMETRY_DLL_EXPORT double GetMinEndAng (const GenArc& arc);

	GEOMETRY_DLL_EXPORT double GetMaxEndAng (const GenArc& arc);

	GEOMETRY_DLL_EXPORT Coord GetMinEndC (const GenArc& arc);

	GEOMETRY_DLL_EXPORT Coord GetMaxEndC (const GenArc& arc);

	GEOMETRY_DLL_EXPORT Circle2D GetCircleOfArc (const GenArc& arc);

	GEOMETRY_DLL_EXPORT bool IsLessByXYOfOriginRadius (const Circle2D& circ1, const Circle2D& circ2);

	GEOMETRY_DLL_EXPORT bool IsNear (const Circle2D& circ1, const Circle2D& circ2);

	GEOMETRY_DLL_EXPORT bool IsLessByCircleAngles (const GenArc& arc1, const GenArc& arc2);

	GEOMETRY_DLL_EXPORT bool DoArcsOverlap (const GenArc& arc1, const GenArc& arc2);


	GEOMETRY_DLL_EXPORT GenArc* SetGenArcPtr (
							GenArc	*arc,
							const Point2D&	begC,
							const Point2D&	endC,
							double	arcAngle);

	GEOMETRY_DLL_EXPORT GenArc	SetGenArc (const Point2D&	begC,
					   const Point2D&	endC,
					   double	arcAngle);



	GEOMETRY_DLL_EXPORT	SetArcResult	SetArc (const Point2D& origo, const Point2D& begC, const Point2D& endC, GenArc& resultArc);

	GEOMETRY_DLL_EXPORT GenArc	SetGenArcCircle (const Point2D& origoC, double radius);
	GEOMETRY_DLL_EXPORT GenArc	SetGenArcEllipse (const Ellipse& ell);

	
	GEOMETRY_DLL_EXPORT void	ArcToBox (
						Box2DData*		box,
						const Point2D*	begC,
						const Point2D*	endC,
						const Point2D*	origC);

	GEOMETRY_DLL_EXPORT Box2DData	GetGenArcBoundBox (const GenArc& genArc);

	GEOMETRY_DLL_EXPORT bool	FindAngArc (const Point2D&		orientC,
											const Point2D&		begC,
											const Point2D&		endC,
											bool				*pIsArc,
											Point2D				*pOrigC,
											Point2D				*pOrientC,
											bool				*pnegArc);

	GEOMETRY_DLL_EXPORT bool	ArcGetOrigo (const Point2D	*begC,
													const Point2D	*endC,
													double			angle,
													Point2D			*origo);

	GEOMETRY_DLL_EXPORT bool	ArcGetOrigo (const Point2D	&begC,
													const Point2D	&endC,
													double			angle,
													Point2D			&origo);

	GEOMETRY_DLL_EXPORT GS::Optional<Point2D>	ArcGetOrigo (const Point2D&		beg,
															 const Point2D&		end,
															 double				angle);

	GEOMETRY_DLL_EXPORT double	GetArcAngle (const Point2D		*origo,		/* sm031 */
											 const Point2D		*begC,
											 const Point2D		*midCArc,
											 const Point2D		*endC);

	GEOMETRY_DLL_EXPORT void	ReflectGenArc (GenArc& arc);

	GEOMETRY_DLL_EXPORT GenArc	GetGenArcComplement (const GenArc& arc);

	GEOMETRY_DLL_EXPORT void	GetViewAngle (const Point2D 	*corig,				/* RJ003 */
											  const Point2D 	*cbeg,
											  const Point2D 	*cend,
											  double			orifi,
											  Int32				ind,
											  double			*newfi);

	GEOMETRY_DLL_EXPORT bool	GetCornerFilletCentre (
				Point2D 		*cprev,			/* RJ003 */
				Point2D 		*c0,
				Point2D 		*cnext,
				Int32		indf,
				Point2D		*oprev,
				double		fprev,
				Int32		inds,
				Point2D		*onext,
				double		fnext,
				bool 		d1,
				bool 		d2,
				double 		disp,
				bool     	dflag,
				Point2D		*newc,
				bool		*degen = nullptr);

	GEOMETRY_DLL_EXPORT double	CalcAngleRelToGenArcBeg (const GenArc	*arc,		/* sm038 */
														 double			ang);

	GEOMETRY_DLL_EXPORT void	TraBackToGenArcSys (const GenArc	*a,
													Point2D			*c);

	GEOMETRY_DLL_EXPORT void	TraBackToGenArcSys (double mainAxisDir, const Point2D& origo, double axisLengthRatio, Point2D*  c);

	GEOMETRY_DLL_EXPORT bool	ValidGenArcPoint (const GenArc	*a,
												  const Point2D	*c);

	GEOMETRY_DLL_EXPORT bool	ValidGenArcPoint (const GenArc&		a,
												  const Point2D&	c);

	GEOMETRY_DLL_EXPORT bool	ValidGenArcPointEps (const GenArc	*a,
													 const Point2D	*c,
													 double			eps);

	GEOMETRY_DLL_EXPORT UnitVector_2D	GetGenArcBegDirection (const GenArc& genArc);

	GEOMETRY_DLL_EXPORT UnitVector_2D	GetGenArcEndDirection (const GenArc& genArc);

//	GEOMETRY_DLL_EXPORT GSErr	TransformArc (const TRANMAT* tran, GenArc* pArc, bool scaleArc);
	GEOMETRY_DLL_EXPORT bool	TransformArc (const Transformation2D& trafo, GenArc& arc, Sector& s);
	GEOMETRY_DLL_EXPORT bool	TransformArc (const TRANMAT& tran, GenArc& arc, Sector& s);

	GEOMETRY_DLL_EXPORT void	CalcWithSectorArc (Sector& s, double angle, double width);

	GEOMETRY_DLL_EXPORT bool	GenArcContainsGenArc (const GenArc& arc, 
															 const GenArc& otherArc);

	GEOMETRY_DLL_EXPORT char	XGenArcLineEps (const 	GenArc	*a,
												const 	Sector	*s,
												Sector			*xs,
												double			eps);

	GEOMETRY_DLL_EXPORT char	XGenArcSectorEps (
							const 	GenArc*	a,
							const 	Sector*	s,
							Sector*			xs,
							double			eps);

	GEOMETRY_DLL_EXPORT Int32	XLineArc (
							const Sector*	s1,
							const Sector*	s2,
							double			ang2,
							Point2D*			xc);

	GEOMETRY_DLL_EXPORT short	PGSectArcInt (
							const Point2D*	sb,
							const Point2D*	se,
							const Point2D*	ab,
							const Point2D*	ae,
							Point2D*			qint1,
							Point2D*			qint2,
							const Point2D*	arcOrigo,
							double			arcRadius,
							Geometry::Orientation arcStatus,
							bool			wholeArc,
							double			pgEps);

	GEOMETRY_DLL_EXPORT short	SectorGenArcIntEps (
							const Point2D& sectBeg, const Point2D& sectEnd,
							const GenArc& genArc,
							Point2D& qint1, Point2D& qint2,
							double	pgEps);

	GEOMETRY_DLL_EXPORT char	XGenArcRayEps (const 	GenArc	*a,
											  const 	Sector	*s,
											  Sector	*xs,
											  double	eps);

	GEOMETRY_DLL_EXPORT char	XGenArcCircleEps (const GenArc	*a1,
												  const Circle2D	*a2,
												  Point2D			xs[4],
												  double		eps);			/* sm061 */

	GEOMETRY_DLL_EXPORT Int32	XGenArcs (
							const GenArc*	a1,
							const GenArc*	a2,
							Point2D			xs[4]);			/* sm061 */

	GEOMETRY_DLL_EXPORT Int32	XGenArcsEps (
							const GenArc*	a1,
							const GenArc*	a2,
							Point2D			xs[4],
							double			eps);

	GEOMETRY_DLL_EXPORT Int32	XArcsOverLap (
								const Sector* s1,
								double        ang1,
								const Sector* s2,
								double        ang2,
								Point2D*		  xc);

	GEOMETRY_DLL_EXPORT void	CutArcWithOtherArc (
								const GenArc&		target,
								const GenArc& 		cutter,
								GenArc&				intersection,
								GS::Array<GenArc>&	remainders);

	GEOMETRY_DLL_EXPORT void	DivideArcToCo (
							const Point2D*		pOrigC,
							const Point2D*		pBegC,
							double				arcAngle,
							const ArcDivParams& arcDivParams,
							Point2D**				hCo,
							Int32*				nCo);

	GEOMETRY_DLL_EXPORT void	DivideArcToCo (
							const Point2D*		pOrigC,
							const Point2D*		pBegC,
							double				arcAngle,
							const ArcDivParams& arcDivParams,
							GS::Array<Point2D>&	co);

	GEOMETRY_DLL_EXPORT void	DivideArcToCo (
							const GenArc&		arc,
							const ArcDivParams& arcDivParams,
							GS::Array<Point2D>&	co);

	GEOMETRY_DLL_EXPORT double	CalcGenArcAngle (const GenArc* pArc);

	GEOMETRY_DLL_EXPORT double	LenGenArc (const GenArc& arc);

	GEOMETRY_DLL_EXPORT bool	IsOnSameArc (const GenArc& arc1, const GenArc& arc2);
	GEOMETRY_DLL_EXPORT GSErrCode	ReadGenArcXML (GS::XMLIChannel& ic, GenArc& genArc);
	GEOMETRY_DLL_EXPORT GSErrCode	WriteGenArcXML (GS::XMLOChannel& oc, const GenArc& genArc);
	inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const GenArc& genarc)	{ return Geometry::WriteGenArcXML (oc, genarc); }
	inline GSErrCode	ReadXML (GS::XMLIChannel& ic, GenArc& genarc)	{ return Geometry::ReadGenArcXML (ic, genarc); }


	GEOMETRY_DLL_EXPORT GenArc	CreateExtendedCurve (const GenArc& arc);
	
	GEOMETRY_DLL_EXPORT void	TangentLines (const Point2D& p, const GenArc& arc, SectorResultFn fn);
	GEOMETRY_DLL_EXPORT void	TangentLines (const Sector& s, const GenArc& arc, SectorResultFn fn);
	GEOMETRY_DLL_EXPORT void	TangentLines (const GenArc& arc1, const GenArc& arc2, SectorResultFn fn);
	GEOMETRY_DLL_EXPORT void	NormalLines (const Point2D& p, const GenArc& arc, SectorResultFn fn);
	GEOMETRY_DLL_EXPORT void	NormalLines (const Sector& s, const GenArc& arc, SectorResultFn fn);

	GEOMETRY_DLL_EXPORT double SpecDistPointToArc (const Point2D& c, const GenArc& arc, double* overHang = nullptr);

	GEOMETRY_DLL_EXPORT void GetTangentPointsByDirection (const GenArc& arc, const Vector2D& direction, GS::Array<Point2D>& resultPoints);
	
}
	
#endif
