#if !defined GS_MODEL3D_CAMERA_HPP
#define GS_MODEL3D_CAMERA_HPP


// -------------------------------- Includes ---------------------------------
#include	"envir.h"

#include	"GSModelerExport.h"

// from GSUtils
#include	"DB.h"

// from Geometry
#include	"Vector3D.hpp"
#include	"Matrix.hpp"

// includes for inline implementation

// ---------------------------- Predeclarations ------------------------------

struct TRANMAT;
struct PlaneEq;
struct CUT_RECORD;

// ----------------------- Class declaration -----------------------------------

namespace Modeler {

class GSMODELER_DLL_EXPORT Camera
{
public:
	enum  ProjectionType {
		AxonometricProjection,
		PerspectiveProjection
	};

	void		FixRealNums ();		//after io doubles can be bad.
private:
	PEAXDEF		peaxDat;			/* Data of axonometry/perspective  (152)*/
	double		projangle;			/* Copy of the angle in View dialog  (4)*/

	SHOWSETS	showDat;			/* Wire, hidden, shaded...			 (4)*/
									/* Draw type bits:						*/
									/* thick line, uniform, box...true view	*/
									/* Intersect.s, shadow lines, hatch..	*/

	ShortRect	drawRect;			/* Rect of the 3D window			 (8)*/
	ShortRect	outputRect;			/* Rect of the output				 (8)*/
	ZOOMDEF		zoomDat;			/* Data of the current projection	(32)*/

	GS_RGBColor	bkgSkyRGB;			/* Background sky color of the 3D windows(6)*/
	GS_RGBColor	bkgEarthRGB;		/* Background earth color of the 3D windows(6)*/
	short		bkgIndex;			/* Index of the background			 (2)*/

	short		hSize, vSize;		/* Window size in pixels (from envir_I.h/CAMERA)	*/

public:		//private:				will be
	void				SetProjCode (short projcode);
	const PERSDEF&		GetPerspectiveData () const;
	void				SetPerspectiveData (const PERSDEF& newPersDat);
	const AXONDEF&		GetAxonometricData () const;
	void				SetAxonometry (short projCode, double projAngle);

public:
	// Constructors
	Camera ();

	// Comparison
	bool			IsNear			 (const Camera& other, const double eps = Eps) const;
	bool			ProjectionIsNear (const Camera& other, const double eps = Eps) const;

	// Projection type query
	ProjectionType	GetProjectionType () const;
	short			GetProjCode () const;

	// Axonometric projection query
	void			GetTransformation (TRANMAT*	tr) const;
	void			GetInverseTransformation (TRANMAT* tr) const;

	// Perspective projection query
	//				later we can use 'const Coord3D&' return type, after the elimination of public member variables
	Coord3D			GetViewPoint () const;
	Coord3D			GetTargetPoint () const;
	double			GetRollAngle () const;
	double			GetFocusDistance () const;
	void			GetPerspectiveCutPlanes (GS::Array<CUT_RECORD> &cutrecs) const;
	void			GetPerspectiveCutPlanes (const Box2DData& screenBox, GS::Array<CUT_RECORD> &cutrecs) const;

	// General query
	void			GetCutPlanes (const Box2DData& screenBox, GS::Array<PlaneEq>& planes) const;
	void			GetCutPlanes (const Box2DData& screenBox, GS::Array<CUT_RECORD>& cutrecs) const;

	// Window data query
	short			GetWindowHorSize () const;
	short			GetWindowVerSize () const;

	// Mode query
	bool			IsInTrueViewMode () const;
	bool			IsInThickLineMode () const;
	bool			IsNotInAllEdgesMode () const;

	// (TR)ansformation functions
	void			PointModel2Eye		(double *x, double *y, double *z) const;
	bool			PointEye2Screen		(double *x, double *y, double *z) const;
	bool			PointModel2Screen	(double *x, double *y, double *z) const;
	void			PointScreen2Eye		(double *x, double *y, double *z) const;
	void			PointEye2Model		(double *x, double *y, double *z) const;
	void			PointScreen2Model	(double *x, double *y, double *z) const;
	void			VectorModel2Eye		(double *x, double *y, double *z) const;
	void			VectorEye2Model		(double *x, double *y, double *z) const;

	GS::Optional<Point2D>	ProjectToScreen	(const Point3D& modelPoint) const;
	GS::Optional<Point3D>	ModelToScreen	(const Point3D& modelPoint) const;
				 Point3D	ScreenToModel	(const Point3D& screenPoint) const;

	short			GetViewDirection	() const;

	void			GetModel2ScreenTransformation (Geometry::Matrix44d& tm) const;

	// Set the camera
	void	SetView (short projcode, double projAngle,
					 Coord3D* view, Coord3D* obj,
					 double rollAngle, double eyeAngle,
					 double lengthX, double angleX,
					 double lengthY, double angleY,
					 double lengthZ, double angleZ);

	Coord3D		GetViewVector () const;
	void		ToPosDir (const Coord3D& lpos, const Coord3D& ldir, double tga);
	void		ToDirection (const Coord3D& ldir);

	short		GetShowType () const;
	void		SetShowType (short method);

	STATW		GetDrawMode () const;
	void		SetDrawMode (STATW mode);

	const GS_RGBColor&	GetBackgroundColor () const;
	void				SetBackgroundColor (const GS_RGBColor& color);

	const GS_RGBColor&	GetBackgroundSkyColor () const;
	void				SetBackgroundSkyColor (const GS_RGBColor& color);

	const GS_RGBColor&	GetBackgroundEarthColor () const;
	void				SetBackgroundEarthColor (const GS_RGBColor& color);

	short				GetBackgroundIndex () const;
	void				SetBackgroundIndex (short index);

	const ShortRect&	GetDrawRect () const;
	void				SetDrawRect (const ShortRect& rect);
	void				SetDrawRect (const GSRect& rect);

	const ShortRect&	GetOutputRect () const;
	void				SetOutputRect (const ShortRect& rect);
	void				SetOutputRect (const GSRect& rect);

	double				GetProjAngle () const;
	void				SetProjAngle (const double projAngle);

	// Deceased EN functions
	short				GetPixelSize () const;
	bool				GetMonoColor () const;
	bool				GetAllEdges () const;
	bool				GetPerspRect () const;
	bool				GetBackGround3DasR () const;
	void				Get3DWindowSize (short *hor, short *ver) const;
	bool				MustVectShadow () const;
	void				GetEffects (short *effects) const;
	void				SetEffects (short effects);
	const ZOOMDEF&		GetZoomDat () const;
	void				SetZoomDat (const ZOOMDEF& newZoomDat);
	const PEAXDEF&		GetPeaxDat () const;
	void				SetPeaxDat (const PEAXDEF& newPeaxDat);

	bool				GetRay (double x, double y, Coord3D* viewPoint, Coord3D* viewDir) const;
};

// inline member functions

inline const ZOOMDEF&	Modeler::Camera::GetZoomDat () const
{
	return zoomDat;
}

inline void				Modeler::Camera::SetZoomDat (const ZOOMDEF& newZoomDat)
{
	zoomDat = newZoomDat;
}

inline const PEAXDEF&	Modeler::Camera::GetPeaxDat () const
{
	return peaxDat;
}

inline void				Modeler::Camera::SetPeaxDat (const PEAXDEF& newPeaxDat)
{
	peaxDat = newPeaxDat;
}


class GSMODELER_DLL_EXPORT HashableCamera {
public:
	explicit HashableCamera (const Modeler::Camera& camera, const double eps = EPS);

	bool  operator== (const HashableCamera& rhs) const;
	ULong GenerateHashValue () const;

private:
	const Modeler::Camera camera;
	const double		  eps;
};

}	// namespace Modeler


#endif
