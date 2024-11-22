// =============================================================================
// Description:		  Model View Settings
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (MODELVIEWSETTINGS_HPP)
#define MODELVIEWSETTINGS_HPP

// ----------------------- Includes --------------------------------------------
#include "ModelColor.hpp"
#include "GSModelerExport.h"
#include "SharedPtr.hpp"
#include "GSPix.h"

// ----------------------- Predeclaration --------------------------------------
class IExtras;

namespace ModelerAPI {
	class ParameterList;
	class ModelViewSettingsRelay;
};

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {


class GSMODELER_DLL_EXPORT ModelViewSettings {
	friend class ModelViewSettingsRelay;

private:
	GS::ConstSharedPtr<ModelerAPI::ModelViewSettingsRelay>	relay;

public:
	enum ViewMode {
		BlockMode		= 0,
		WireframeMode	= 1,
		HiddenLineMode	= 2,
		ShadingMode		= 3
	};

	enum DrawMode {
		Analitic			= 0,
		UndefinedDrawMode	= 2
	};

	enum ContourMode {
		ContourOff		= 0,
		ContourDraft	= 1,
		ContourBest		= 2
	};

	enum ShadowMode {
		ShadowOff			= 0,
		ShadowContoursOff	= 1,
		ShadowContoursOn	= 2
	};

	enum BackGroundType {
		MonochromBackGround	= 0,
		HorizonBackGround	= 1,
		PictureBackGround	= 2
	};

	ModelViewSettings ();
	ModelViewSettings (const ModelViewSettings& other);
	~ModelViewSettings ();

	ViewMode			GetViewMode () const;
	DrawMode			GetDrawMode () const;
	ContourMode			GetContourMode () const;
	bool				HatchingIsOn () const;
	bool				TransparencyIsOn () const;
	ShadowMode			GetSunShadowMode () const;
	bool				SingleLevelShadowIsOn () const;
	double				GetShadowLevel () const;
	short				GetLineWidth () const;
	BackGroundType		GetBackGroundType () const;
	Color				GetSkyColor () const;
	Color				GetEarthColor () const;
	Int32				GetBackGroundPictureIndex () const;
	const IExtras*		GetExtras () const;
	Color				GetSelectionColor () const;
	double				GetSelectionAlpha () const;
	Int32				GetExtraSettings (void* extraSettings, Int32 dataSize) const;
	void				SetExtraSettings (const void* extraSettings, Int32 dataSize);
	void				GetProperties (ParameterList* properties) const;
	void				SetProperties (ParameterList* properties);
	bool				IsMonochromeModeEnabled () const;
	GS_RGBColor			GetMonochromeSurfaceRGB () const;
	GS_RGBColor			GetMonochromeContourRGB () const;
};


} // namespace ModelerAPI


#endif
