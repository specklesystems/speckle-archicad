#if !defined GS_MODEL3D_SUNSETTINGS_HPP
#define GS_MODEL3D_SUNSETTINGS_HPP


// -------------------------------- Includes ---------------------------------
#include	"envir.h"
#include	"Vector3D.hpp"
#include	"GSModelerExport.h"

#include	"EventObserver.hpp"

// includes for inline implementation


// ---------------------------- Predeclarations ------------------------------

struct SunSettingsRec;

// ----------------------- Class declaration -----------------------------------

namespace Modeler {

// The horizontal coordinate system is a celestial coordinate system that uses the observer's local horizon as the
// fundamental plane. Currently it is used to describe the visible position of the Sun from the model origin.
// See https://en.wikipedia.org/wiki/Horizontal_coordinate_system
class GSMODELER_DLL_EXPORT HorizontalCoord {
public:
	HorizontalCoord ();
	HorizontalCoord (double azimuth, double altitude);
	HorizontalCoord (const Vector3D& direction);

	double			GetAzimuth		() const	{ return azimuth;	}
	double			GetAltitude		() const	{ return altitude;	}
	const Vector3D&	GetDirection	() const	{ return dir;		}

private:
	static Vector3D			HorizontalToDescartes (double sunAngxy, double sunAngz);
	static HorizontalCoord	DescartesToHorizontal (const Vector3D& direction);

	// angles are given in degrees (NOT radian):
	double		azimuth;	// 0 => East, 90 degreees => North, 180 degrees => West, 270 degrees => South (CCW)
	double		altitude;	// 0 => on the horizon, > 0 => over the horizon, 90 degrees => zenith ("top of the sky")
							//						< 0 => below the horizon, -90 degrees => nadir
	Vector3D	dir;		// unit vector, calculated from @azimuth and @altitude
};

class GSMODELER_DLL_EXPORT SunSettings {
private:
	// Sun geometry
	HorizontalCoord	sunPosition;

	// Sun light
	GS_RGBColor		sunRGB;
	GS_RGBColor		ambientRGB;

	void SetFromSunDialogSettings (const SunSettingsRec& sunDialogSets);
public:
	SunSettings ();
	SunSettings (const SUNGSETS& sungSets, const SUNLSETS& sunlSets);
	SunSettings (const SunSettingsRec& sunDialogSets);

	void				SetPosition (double azimuth, double altitude);

	const Vector3D&		GetDirection () const;
	void				SetDirection (const Vector3D& dir);

	double				GetAngleXY () const;
	double				GetAngleZ () const;

	// Sun light
	const GS_RGBColor&	GetColor () const;
	void				SetColor (const GS_RGBColor& rgb);

	const GS_RGBColor&	GetAmbientColor () const;
	void				SetAmbientColor (const GS_RGBColor& rgb);
};

namespace SunSettingUtils {

	GSMODELER_DLL_EXPORT
	void	SunSettingsToSUNGSETS (const SunSettings& src, SUNGSETS* dst);

	GSMODELER_DLL_EXPORT
	void	SunSettingsToSUNLSETS (const SunSettings& src, SUNLSETS* dst);

	GSMODELER_DLL_EXPORT
	void	SetSunSettings (const SunSettingsRec*	sunDialogSets,
							Modeler::SunSettings*	outSunSettings);

	GSMODELER_DLL_EXPORT
	void	GetSunSettings (SunSettingsRec*				sunDialogSets,
							const Modeler::SunSettings&	inSunSettings);
}

}	// namespace Modeler

#endif
