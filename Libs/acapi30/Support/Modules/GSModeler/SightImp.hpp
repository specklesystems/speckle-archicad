// *****************************************************************************
// Sight inline implementation.
// GSModeler, platform-independent
//
// Namespaces:        Contact person:
//    Modeler          FGY, VSZG
//
// SG compatible
// *****************************************************************************

#if !defined(SIGHTIMP_HPP)
#define SIGHTIMP_HPP

#pragma once

#include	"Model3D/ModStamp.hpp"
#include	"Model3D/image.h"	// Attribute types
#include	"Visualization/Camera.hpp"


/////////////////////////////////
///  Sight
/////////////////////////////////

inline 	Modeler::Model3DPtr	Modeler::Sight::GetMainModelPtr () const
{
	return mainModel;
}

inline 	Modeler::ConstModel3DPtr	Modeler::Sight::GetConstMainModelPtr () const
{
	return mainModel;
}

inline 	void Modeler::Sight::SetMainModelPtr (const Model3DPtr& newMainModel)
{
	mainModel = newMainModel;
	if (newMainModel != nullptr)
		ColorShadesChanged (*newMainModel);
}




////////////////////
///  Sight, other
////////////////////

inline RenderingSightGuard::RenderingSightGuard (Modeler::SightPtr sight, const RENDSETS& rendSets)
	: sight (sight)
{
	oldCam = sight->GetCamera ();
	Modeler::Camera cam = oldCam;
	GSRect	outputRect = {0, 0, rendSets.vSize, rendSets.hSize};
	cam.SetOutputRect (outputRect);

	sight->SetCamera (cam);
}


inline RenderingSightGuard::~RenderingSightGuard ()
{
	sight->SetCamera (oldCam);
}


inline void Modeler::Sight::GetBackgroundTexture (const RENDSETS& rendSets, RTXT *rtxt) const
{
	ShortRect outputRect = GetCamera ().GetOutputRect ();

	m_background.Update (rendSets, outputRect.right  - outputRect.left, outputRect.bottom - outputRect.top);

	*rtxt = m_background.GetBackgroundTexture ();
}


inline short Modeler::Sight::GetMarkedStatusBits (short mask) const
{
	return static_cast<short> (status & mask);
}


inline void Modeler::Sight::ClearMarkedStatusBits (short clrMask)
{
	status &= ~clrMask;
}


inline void Modeler::Sight::SetMarkedStatusBits (short newVal)
{
	status |= newVal;
}

inline const Modeler::SunSettings&	Modeler::Sight::GetSunSettings () const
{
	return m_sunSettings;
}

inline bool	Modeler::Sight::IsSightInvalid () const
{
	return (GetMarkedStatusBits (INVALIDBIT) != 0);
}

inline const VESHSETS&	Modeler::Sight::GetVectorShadowSettings (void)	const {
	return m_vectorShadowSettings;
}

inline void				Modeler::Sight::SetVectorShadowSettings (const VESHSETS& vectorShadowSettings) {
	m_vectorShadowSettings = vectorShadowSettings;
	SendVectorShadowSettingsChanged (m_vectorShadowSettings);
}

  //////////////
 ///  Viewer
//////////////

inline Modeler::SightViewer::SightViewer (const ConstSightPtr sight) :
	MainContainerBase::Viewer (*reinterpret_cast<const ConstMainContainerBasePtr*> (&sight))
{
	this->sight = sight;
}

inline Modeler::SightViewer::SightViewer (const SightViewer& src_viewer) :
	MainContainerBase::Viewer (src_viewer),
	sight (src_viewer.sight)
{
}

inline Modeler::SightViewer::~SightViewer ()
{
}

inline Modeler::SightViewer&		Modeler::SightViewer::operator= (const Modeler::SightViewer& src)
{
	MainContainerBase::Viewer::operator= (src);
	sight = src.sight;
	return *this;
}


inline bool		Modeler::SightViewer::operator== (const SightViewer& src) const
{
	return sight == src.sight;
}


inline bool		Modeler::SightViewer::operator!= (const SightViewer& src) const
{
	return !operator== (src);
}



  ////////////////////////////
 ///  Viewer::Get...Count
////////////////////////////

inline const VectorGraphicEngineData& Modeler::SightViewer::GetConstVGEData () const
{
	return *(sight->VGEData);
}

inline const Modeler::Sight & Modeler::SightViewer::GetConstSight () const
{
	return *sight;
}





inline ULong	Modeler::SightViewer::GetShadingColorCount () const
{
	return sight->shcol.GetSize ();
}

inline USize	Modeler::SightViewer::GetProjectedPointCloudCount () const
{
	return sight->GetProjectedPointCloudCount ();
}

inline USize	Modeler::SightViewer::GetHiddenPointCloudCount () const
{
	return sight->GetHiddenPointCloudCount ();
}

/////////////////////////////////
//  Viewer::GetConst...RecPtr
/////////////////////////////////


inline const UCOL*	Modeler::SightViewer::GetConstShadingColorRecPtr (ULong index) const
{
	DBASSERT (1 <= (Int32)index && (Int32)index <= sight->shcol.GetSize ());
	return &sight->shcol[index - 1];
}


inline bool	Modeler::SightViewer::AreHiddensOverlapped () const
{
	return sight->AreHiddensOverlapped ();
}


inline bool	Modeler::SightViewer::AreHiddensClipped () const
{
	return sight->AreHiddensClipped ();
}


inline bool	Modeler::SightViewer::HasClippedModel () const
{
	return sight->IsClippedModelExists ();
}


inline bool	Modeler::SightViewer::HasHiddenView () const
{
	return sight->IsHiddenViewExists ();
}


inline bool	Modeler::SightViewer::IsSightInvalid () const
{
	bool	isSightInvalid = (sight->GetMarkedStatusBits (INVALIDBIT) != 0);
	return isSightInvalid;
}

inline bool	Modeler::SightViewer::IsTransformModelFullValid () const
{
	return sight->IsTransformModelFullValid ();
}

inline bool	Modeler::SightViewer::IsTransformLightsFullValid () const
{
	return sight->IsTransformLightsFullValid ();
}


inline short	Modeler::SightViewer::GetMarkedStatusBits (short mask) const
{
	return sight->GetMarkedStatusBits (mask);
}


inline Modeler::ConstModel3DPtr	Modeler::SightViewer::GetConstMainModelPtr () const
{
	return sight->GetConstMainModelPtr ();
}


inline const Modeler::Model3DViewer*	Modeler::SightViewer::GetConstMainModel3DViewerPtr () const
{
	return sight->GetConstMainModel3DViewerPtr ();
}


inline const Modeler::Model3DViewer*	Modeler::SightViewer::GetConstClippedModel3DViewerPtr () const
{
	return sight->GetConstClippedModel3DViewerPtr ();
}

inline const Modeler::Camera&		Modeler::SightViewer::GetCamera () const
{
	return sight->GetCamera ();
}

inline const Modeler::SunSettings&	Modeler::SightViewer::GetSunSettings () const
{
	return sight->GetSunSettings ();
}

inline Box3D	Modeler::SightViewer::GetProjectedBounds () const
{
	return sight->GetProjectedBounds ();
}

inline ULong	Modeler::SightViewer::GetAllItemsCount ()	const
{
	return sight->GetAllItemsCount ();
}

inline ULong	Modeler::SightViewer::GetUsedBytes ()	const
{
	return sight->GetUsedBytes ();
}

inline ULong	Modeler::SightViewer::GetAllocatedBytes () const
{
	return sight->GetAllocatedBytes();
}

inline const VESHSETS&	Modeler::SightViewer::GetVectorShadowSettings (void)	const
{
	return sight->GetVectorShadowSettings ();
}

inline const TRANMAT& Modeler::SightViewer::GetLocalCoordSys () const
{
	return sight->localCoordSys;
}

  ///////////////////////////
 ///  SightOnlyModifier
///////////////////////////

inline Modeler::SightOnlyModifier::SightOnlyModifier (const SightPtr sight) :
	MainContainerBase::OnlyModifier (sight)
{
	this->sight = sight;
}

inline Modeler::SightOnlyModifier::SightOnlyModifier (const SightOnlyModifier& src) :
	MainContainerBase::OnlyModifier (src)
{
	sight = src.sight;
}

inline Modeler::SightOnlyModifier::~SightOnlyModifier ()
{
}


inline Modeler::SightOnlyModifier&	Modeler::SightOnlyModifier::operator= (const Modeler::SightOnlyModifier& src)
{
	MainContainerBase::OnlyModifier::operator= (src);
	sight = src.sight;
	return *this;
}


inline bool		Modeler::SightOnlyModifier::operator== (const Modeler::SightOnlyModifier& src) const
{
	return sight == src.sight;
}


inline bool		Modeler::SightOnlyModifier::operator!= (const Modeler::SightOnlyModifier& src) const
{
	return !operator== (src);
}


  //////////////////////////////////
 ///  OnlyModifier::Get...
//////////////////////////////////

inline VectorGraphicEngineData & Modeler::SightOnlyModifier::GetVGEData ()

{
	return *(sight->VGEData);
}

//////////////////////////////////
///  OnlyModifier::Get...RecPtr
//////////////////////////////////

inline void Modeler::SightOnlyModifier::SetLocalCoordSys (const TRANMAT& localCoordSys)
{
	sight->localCoordSys = localCoordSys;
}

  //////////////////////////////////
 ///  OnlyModifier::ReAll...
//////////////////////////////////




  //////////////////////////////////
 ///  OnlyModifier::Delete...Rec
//////////////////////////////////



  //////////////////////////////////
 ///  OnlyModifier::Allocate...
//////////////////////////////////


inline void	Modeler::SightOnlyModifier::InitShadingColors (Int32 num)
{
	sight->shcol.SetCapacity (num);
}

inline void	Modeler::SightOnlyModifier::FreeShadingColors ()
{
	sight->shcol.Clear ();
}

  ///////////////////
 ///
///////////////////


inline void	Modeler::SightOnlyModifier::SetCamera (const Modeler::Camera& cam)
{
	sight->SetCamera (cam);
}

inline void	Modeler::SightOnlyModifier::SetSunSettings (const Modeler::SunSettings& sun)
{
	sight->SetSunSettings (sun);
}

inline void	Modeler::SightOnlyModifier::ClearMarkedStatusBits (short mask)
{
	sight->ClearMarkedStatusBits (mask);
}


inline void	Modeler::SightOnlyModifier::SetMarkedStatusBits (short newVal)
{
	sight->SetMarkedStatusBits (newVal);
}


inline void		Modeler::SightOnlyModifier::GetBackgroundTexture (const RENDSETS& rendSets, RTXT *rtxt)
{
	sight->GetBackgroundTexture (rendSets, rtxt);
}


  ////////////////////////
 ///  SightModifier
////////////////////////


inline Modeler::SightModifier::SightModifier (const Modeler::SightPtr sight):
	SightViewer (sight), SightOnlyModifier (sight)
{
}

inline Modeler::SightModifier::SightModifier (const Modeler::SightModifier& src) :
	SightViewer (src), SightOnlyModifier (src)
{
}

inline Modeler::SightModifier&	Modeler::SightModifier::operator= (const Modeler::SightModifier& src)
{
	Modeler::SightViewer::operator= (src);
	Modeler::SightOnlyModifier::operator= (src);
	return *this;
}

inline bool		Modeler::SightModifier::operator== (const Modeler::SightModifier& src) const
{
	return Modeler::SightViewer::operator== (src) && Modeler::SightOnlyModifier::operator== (src);
}


inline bool		Modeler::SightModifier::operator!= (const Modeler::SightModifier& src) const
{
	return !operator== (src);
}


  ////////////////////////
 ///  CameraUtils
////////////////////////


// To avoid code duplication we use a SightViewer/Modifier object in Sight-based functions.
// Thus the Viewer/Modifier calls sight->GetCamera () member function (that can be seem redundant),
// but we can not get a Sight object from a Viewer/Modifier to do the another way.


inline void		Modeler::CameraUtils::SetShowType (Modeler::SightPtr sight, short method)
{
	Modeler::Camera	cam = sight->GetCamera ();
	cam.SetShowType (method);
	sight->SetCamera (cam);
}


inline short	Modeler::CameraUtils::GetShowType (Modeler::ConstSightPtr sight)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	return cam.GetShowType ();
}


inline void		Modeler::CameraUtils::SetDrawMode (SightPtr sight, short mode)
{
	Modeler::Camera	cam = sight->GetCamera ();
	cam.SetDrawMode (mode);
	sight->SetCamera (cam);
}


inline short	Modeler::CameraUtils::GetDrawMode	(ConstSightPtr sight)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	return cam.GetDrawMode ();
}


inline void		Modeler::CameraUtils::SetPixelSize (Modeler::SightPtr sight, short pixsize)
{
	Modeler::SightModifier	uModifier (sight);
	SetPixelSize (uModifier, pixsize);
}


inline short	Modeler::CameraUtils::GetPixelSize (Modeler::ConstSightPtr sight)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	return cam.GetPixelSize ();
}


inline void		Modeler::CameraUtils::SetMonoColor (Modeler::SightPtr sight, bool mono)
{
	Modeler::SightModifier	uModifier (sight);
	SetMonoColor (uModifier, mono);
}


inline bool		Modeler::CameraUtils::GetMonoColor (Modeler::ConstSightPtr sight)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	return cam.GetMonoColor ();
}


inline void		Modeler::CameraUtils::SetAllEdges (Modeler::SightPtr sight, bool alledges)
{
	Modeler::SightModifier	uModifier (sight);
	SetAllEdges (uModifier, alledges);
}


inline bool		Modeler::CameraUtils::GetAllEdges (Modeler::ConstSightPtr sight)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	return cam.GetAllEdges ();
}


inline void		Modeler::CameraUtils::SetPerspRect (Modeler::SightPtr sight, bool prect)
{
	Modeler::SightModifier	uModifier (sight);
	SetPerspRect (uModifier, prect);
}


inline bool		Modeler::CameraUtils::GetPerspRect (Modeler::ConstSightPtr sight)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	return cam.GetPerspRect ();
}


inline void		Modeler::CameraUtils::SetBackGround3D (Modeler::SightPtr sight, const GS_RGBColor& rgb)
{
	Modeler::SightModifier	uModifier (sight);
	SetBackGround3D (uModifier, rgb);
}


inline void		Modeler::CameraUtils::GetBackGround3D (Modeler::ConstSightPtr sight, GS_RGBColor *rgb)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	*rgb = cam.GetBackgroundColor ();
}

inline void		Modeler::CameraUtils::Set3DBackgroundSkyColor (Modeler::SightPtr sight, const GS_RGBColor& rgb)
{
	Modeler::SightModifier	uModifier (sight);
	Set3DBackgroundSkyColor (uModifier, rgb);
}


inline void		Modeler::CameraUtils::Get3DBackgroundSkyColor (Modeler::ConstSightPtr sight, GS_RGBColor *rgb)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	*rgb = cam.GetBackgroundSkyColor ();
}

inline void		Modeler::CameraUtils::Set3DBackgroundEarthColor (Modeler::SightPtr sight, const GS_RGBColor& rgb)
{
	Modeler::SightModifier	uModifier (sight);
	Set3DBackgroundEarthColor (uModifier, rgb);
}


inline void		Modeler::CameraUtils::Get3DBackgroundEarthColor (Modeler::ConstSightPtr sight, GS_RGBColor *rgb)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	*rgb = cam.GetBackgroundEarthColor ();
}


inline void		Modeler::CameraUtils::SetBackGround3DasR (Modeler::SightPtr sight, bool asr)
{
	Modeler::SightModifier	uModifier (sight);
	SetBackGround3DasR (uModifier, asr);
}


inline bool		Modeler::CameraUtils::GetBackGround3DasR (Modeler::ConstSightPtr sight)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	return cam.GetBackGround3DasR ();
}


inline void		Modeler::CameraUtils::Set3DWindowSize (SightPtr sight, short hor, short ver)
{
	Modeler::SightModifier	uModifier (sight);
	Set3DWindowSize (uModifier, hor, ver);
}


inline void		Modeler::CameraUtils::Get3DWindowSize (ConstSightPtr sight, short *hor, short *ver)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	cam.Get3DWindowSize (hor, ver);
}


inline void		Modeler::CameraUtils::SwitchShadowOnOff (SightPtr sight, bool switchOn)
{
	Modeler::SightModifier	uModifier (sight);
	SwitchShadowOnOff (uModifier, switchOn);
}


inline bool		Modeler::CameraUtils::MustVectShadow (ConstSightPtr sight)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	return cam.MustVectShadow ();
}


inline void		Modeler::CameraUtils::GetEffects (ConstSightPtr sight, short *effects)
{
	const Modeler::Camera& cam = sight->GetCamera ();
	cam.GetEffects (effects);
}


inline void		Modeler::CameraUtils::SetEffects (SightPtr sight, short effects)
{
	Modeler::Camera	cam = sight->GetCamera ();
	cam.SetEffects (effects);
	sight->SetCamera (cam);
}


//	SightViewer/Modifier-based functions

inline void		Modeler::CameraUtils::SetShowType (Modeler::SightModifier& uModifier, short method)
{
	Modeler::Camera	cam = uModifier.GetCamera ();
	cam.SetShowType (method);
	uModifier.SetCamera (cam);
}

inline short	Modeler::CameraUtils::GetShowType (const Modeler::SightViewer& uViewer)
{
	const Modeler::Camera& cam = uViewer.GetCamera ();
	return cam.GetShowType ();
}


inline void		Modeler::CameraUtils::SetDrawMode (Modeler::SightModifier& uModifier, short mode)
{
	Modeler::Camera	cam = uModifier.GetCamera ();
	cam.SetDrawMode (mode);
	uModifier.SetCamera (cam);
}


inline short	Modeler::CameraUtils::GetDrawMode	(const Modeler::SightViewer& uViewer)
{
	const Modeler::Camera& cam = uViewer.GetCamera ();
	return cam.GetDrawMode ();
}


inline void		Modeler::CameraUtils::SetPixelSize (Modeler::SightModifier& uModifier, short pixsize)
{
	Modeler::Camera	cam = uModifier.GetCamera ();
	if (pixsize > 0)
		cam.SetDrawMode (cam.GetDrawMode () | THICK_BIT);
	else
		cam.SetDrawMode (cam.GetDrawMode () & ~THICK_BIT);
	uModifier.SetCamera (cam);
}


inline short	Modeler::CameraUtils::GetPixelSize (const Modeler::SightViewer& uViewer)
{
	const Modeler::Camera&	cam = uViewer.GetCamera ();
	return cam.GetPixelSize ();
}


inline void		Modeler::CameraUtils::SetMonoColor (Modeler::SightModifier& uModifier, bool mono)
{
	Modeler::Camera	cam = uModifier.GetCamera ();
	if (mono)
		cam.SetDrawMode (cam.GetDrawMode () |  UNIFORMBIT);
	else
		cam.SetDrawMode (cam.GetDrawMode () & ~UNIFORMBIT);
	uModifier.SetCamera (cam);
}


inline bool		Modeler::CameraUtils::GetMonoColor (const Modeler::SightViewer& uViewer)
{
	const Modeler::Camera&	cam = uViewer.GetCamera ();
	return cam.GetMonoColor ();
}


inline void		Modeler::CameraUtils::SetAllEdges (Modeler::SightModifier& uModifier, bool alledges)
{
	Modeler::Camera	cam = uModifier.GetCamera ();
	if (alledges)
		cam.SetDrawMode (cam.GetDrawMode () |  ALLEDGESBIT);
	else
		cam.SetDrawMode (cam.GetDrawMode () & ~ALLEDGESBIT);
	uModifier.SetCamera (cam);
}


inline bool		Modeler::CameraUtils::GetAllEdges (const Modeler::SightViewer& uViewer)
{
	const Modeler::Camera&	cam = uViewer.GetCamera ();
	return cam.GetAllEdges ();
}


inline void		Modeler::CameraUtils::SetPerspRect (Modeler::SightModifier& uModifier, bool prect)
{
	Modeler::Camera	cam = uModifier.GetCamera ();
	if (prect)
		cam.SetDrawMode (cam.GetDrawMode () |  PERSPRECTBIT);
	else
		cam.SetDrawMode (cam.GetDrawMode () & ~PERSPRECTBIT);
	uModifier.SetCamera (cam);
}


inline bool		Modeler::CameraUtils::GetPerspRect (const Modeler::SightViewer& uViewer)
{
	const Modeler::Camera&	cam = uViewer.GetCamera ();
	return cam.GetPerspRect ();
}


inline void		Modeler::CameraUtils::SetBackGround3D (Modeler::SightModifier& uModifier, const GS_RGBColor& rgb)
{
	Modeler::Camera	cam = uModifier.GetCamera ();
	cam.SetBackgroundColor (rgb);
	uModifier.SetCamera (cam);
}


inline void		Modeler::CameraUtils::GetBackGround3D (const Modeler::SightViewer& uViewer, GS_RGBColor *rgb)
{
	const Modeler::Camera&	cam = uViewer.GetCamera ();
	*rgb = cam.GetBackgroundColor ();
}


inline void		Modeler::CameraUtils::Set3DBackgroundSkyColor (Modeler::SightModifier& uModifier, const GS_RGBColor& rgb)
{
	Modeler::Camera	cam = uModifier.GetCamera ();
	cam.SetBackgroundSkyColor (rgb);
	uModifier.SetCamera (cam);
}


inline void		Modeler::CameraUtils::Get3DBackgroundSkyColor (const Modeler::SightViewer& uViewer, GS_RGBColor *rgb)
{
	const Modeler::Camera&	cam = uViewer.GetCamera ();
	*rgb = cam.GetBackgroundSkyColor ();
}


inline void		Modeler::CameraUtils::Set3DBackgroundEarthColor (Modeler::SightModifier& uModifier, const GS_RGBColor& rgb)
{
	Modeler::Camera	cam = uModifier.GetCamera ();
	cam.SetBackgroundEarthColor (rgb);
	uModifier.SetCamera (cam);
}


inline void		Modeler::CameraUtils::Get3DBackgroundEarthColor (const Modeler::SightViewer& uViewer, GS_RGBColor *rgb)
{
	const Modeler::Camera&	cam = uViewer.GetCamera ();
	*rgb = cam.GetBackgroundEarthColor ();
}


inline void		Modeler::CameraUtils::SetBackGround3DasR (Modeler::SightModifier& uModifier, bool asr)
{
	Modeler::Camera	cam = uModifier.GetCamera ();
	if (asr)
		cam.SetBackgroundIndex (1);
	else
		cam.SetBackgroundIndex (0);
	uModifier.SetCamera (cam);
}


inline bool		Modeler::CameraUtils::GetBackGround3DasR (const Modeler::SightViewer& uViewer)
{
	const Modeler::Camera&	cam = uViewer.GetCamera ();
	return cam.GetBackGround3DasR ();
}


inline void		Modeler::CameraUtils::Set3DWindowSize (SightModifier& uModifier, short hor, short ver)
{
	Modeler::Camera	cam = uModifier.GetCamera ();
	ShortRect	drawRect;
	drawRect.right  = hor;
	drawRect.left   = 0;
	drawRect.bottom = ver;
	drawRect.top    = 0;
	cam.SetDrawRect (drawRect);
	uModifier.SetCamera (cam);
}


inline void		Modeler::CameraUtils::Get3DWindowSize (const SightViewer& uViewer, short *hor, short *ver)
{
	const Modeler::Camera&	cam = uViewer.GetCamera ();
	cam.Get3DWindowSize (hor, ver);
}


inline bool		Modeler::CameraUtils::MustVectShadow (const SightViewer& uViewer)
{
	const Modeler::Camera&	cam = uViewer.GetCamera ();
	return cam.MustVectShadow ();
}


inline void		Modeler::CameraUtils::GetEffects (const SightViewer& uViewer, short *effects)
{
	const Modeler::Camera&	cam = uViewer.GetCamera ();
	cam.GetEffects (effects);
}


inline void		Modeler::CameraUtils::SetEffects (SightModifier& uModifier, short effects)
{
	Modeler::Camera	cam = uModifier.GetCamera ();
	cam.SetEffects (effects);
	uModifier.SetCamera (cam);
}


//////////// SunSettingUtils


inline void		Modeler::SunSettingUtils::SetSunSettings (const SightPtr& sight, const SunSettingsRec* sunSets)
{
	if (DBVERIFY (sunSets != nullptr)) {
		sight->SetSunSettings (Modeler::SunSettings (*sunSets));
	}
}


inline void		Modeler::SunSettingUtils::SetSunPosition (const SightPtr& sight, double sunAngXY, double sunAngZ)
{
	Modeler::SunSettings	sun = sight->GetSunSettings ();
	sun.SetPosition (sunAngXY, sunAngZ);
	sight->SetSunSettings (sun);
}

#endif // !defined(SIGHTIMP_HPP)
