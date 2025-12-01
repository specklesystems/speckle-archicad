// *****************************************************************************
// A sight is a summary of a 3D model and its visualization from one view.
// GSModeler, platform-independent
//
// Namespaces:        Contact person:
//    Modeler          FGY, VSZG
//
// SG compatible
// *****************************************************************************

#if !defined(SIGHT_HPP)
#define SIGHT_HPP

#pragma once

// from GSModeler
#include	"SightDefs.hpp"
#include	"VGE_Defines.hpp"

// from GSRoot
#include	"GSRoot.hpp"
#include	"VA.hpp"

// from InputOutput
#include	"File.hpp"
#include	"Folder.hpp"

// from GDL
#include	"envir.h"

// from GSModeler
#include	"SightPtr.hpp"
#include	"SightBackground.hpp"
#include	"Model3D/model.h"
#include	"Model3D/ModelerAttributes.hpp"
#include	"Model3D/Model3D.hpp"
#include	"Model3D/MainContainerBase.hpp"
#include	"Model3D/Model3DSizeReport.hpp"
#include	"Visualization/Camera.hpp"

#include	"GSModelerPrivExp.h"

#include	"SunSettings.hpp"

#include	"QuadTree.hpp"

// from Geometry
#include	"Polygon2DOperations.h"

class VGEStatus;
class VectorGraphicEngineData;
class DisplayPolygons;
class AlgStatus;
struct ULGHT;
struct UCOL;
struct UPOINTCLOUD;
struct UBODY;
struct UPGON;
struct UEDGE;
struct HEDGE;
struct HVERT;
struct HPGON;
struct HPVER;
struct HPOINTCLOUD;

namespace Geometry {
	struct PGRESPOLYEXT;
}

namespace VectorGraphicEngine {
	class AlgBase;
}


/*================================	CONSTANTS	============================*/


/*--------------------------------------------------------------------------*/
/*----------------------------- STATUS BITS FOR SIGHT ----------------------*/
/*--------------------------------------------------------------------------*/

/*	For SIGHT				Sxxxx != &xxxx									*/
#define	DIFFERENTBIT	0x0001					/*	0b0000000000000001		*/

// from DNI.h
GSMODELER_PRIVATE_EXPORT
void	DNReport3DDataSize (GS::OChannel&);

namespace Modeler {

	typedef struct {
		short	transformation;
		short	perspect_cut;

		short	free_perspective;			/* moresun_shadow_bo */

		short	projection;

		//	short	voca_exist;
	} SightConditions;

	struct SightState {					// for DT	(no Memento yet; partially restore)
		PEAXDEF							lastpeaxDat;
		short							lastshowtype;
		STATW							lastdrawMode;
	};

	class SightViewer;
	class SightOnlyModifier;

	class ElimBody;


	class GSMODELER_DLL_EXPORT ISightObserver : public GS::EventObserver {
	public:
		virtual	void CameraChanged (const Modeler::Camera &/*newCamera*/) {}
		virtual void VectorShadowSettingsChanged (const VESHSETS &/*newVeshSets*/) {}
		virtual	void SunSettingsChanged (const Modeler::SunSettings &/*newSunSets*/) {}
		virtual	void ZoomDefChanged (const ZOOMDEF &/*newZoomDef*/) {}

		virtual		~ISightObserver ();	// hogy legyen RTTI Macen is...
	};


	class GSMODELER_DLL_EXPORT Sight : public MainContainerBase, private IModel3DObserver
	{
	public:
		class SunVGEDataGuard { //puts sunVGEData to VGEData, then on destroy it restores the original
		public:
			SunVGEDataGuard (Modeler::SightPtr theSight_init) : theSight (theSight_init)	{ DBASSERT_STR (theSight->VGEData != theSight->sunVGEData, "Critical Error!"); origVGEData = theSight->VGEData, theSight->VGEData = theSight->sunVGEData; }
			~SunVGEDataGuard ()																{ theSight->VGEData = origVGEData; }
		private:
			Modeler::SightPtr theSight;
			VectorGraphicEngineData* origVGEData;
		};

		friend class VectorGraphicEngine::AlgBase;
		friend class SightViewer;
		friend class SightOnlyModifier;
		friend class GS::SharedPtr<Sight>;
		friend class GS::ConstSharedPtr<Sight>;
		class ElemQuery;

	private:
		class GSMODELER_DLL_EXPORT SightEventSource : public GS::EventSource
		{
		public:
			void	Attach (ISightObserver& observer);
			void	Detach (ISightObserver& observer);

			void	SendCameraChanged (const Modeler::Camera &newCamera);
			void	SendVectorShadowSettingsChanged (const VESHSETS &newVeshSets);
			void	SendSunSettingsChanged (const Modeler::SunSettings &newSunSets);
			void	SendZoomDefChanged (const ZOOMDEF &newZoomDef);

			virtual ~SightEventSource ();
		};

		mutable SightEventSource	m_sightEventSource;

		SunSettings			m_sunSettings;

		Model3DPtr			mainModel;
		//Model3DViewer		mainModel3DViewer;	//ToDo AACS: Meg kell szuntetni, VGE Data-bol kell venni!


		VectorGraphicEngineData*	VGEData;
		VectorGraphicEngineData*	sunVGEData;
		DisplayPolygons*			currentDisplayPolys;	//either visiblePolys or sortedPolys
		AlgStatus*					currentDisplayPolysStatus;

		ElimBody*			elimBody;		// VSZG-D043: forditasi ido csokkentese miatt *

		GS::Array <UCOL>	shcol;

		mutable SightBackground		m_background;

		VESHSETS			m_vectorShadowSettings;

		TRANMAT				localCoordSys;

		Sight (DiskCachingMethod cachingMethodIn,
			   Model3DPtr mainModelIn,
			   const Modeler::Camera &camera,
			   const VESHSETS &veshSets,
			   const Modeler::SunSettings &sunSettings);

		Sight (const Sight& source) = delete;
		Sight& operator= (const Sight& source) = delete;

		void					Init (void);

		bool					AreHiddensOverlapped () const;
		bool					AreHiddensClipped () const;

		void					ResetClippedModelViewer (void);

		USize			GetProjectedPointCloudCount () const;
		USize			GetHiddenPointCloudCount () const;

	public:
		virtual ~Sight ();
		VGEStatus&								GetVGEStatus ();	//special access, at least may be debugged! AACS
		const VGEStatus&						GetVGEStatus () const;	//special access, at least may be debugged! AACS
		inline const VectorGraphicEngineData&	GetConstVGEData () const { return *VGEData; }
		inline VectorGraphicEngineData&			GetVGEData () { return *VGEData; }
		Geometry::PGRESPOLYEXT&					GetOnePlaneShadowReceiver (const double levelSetValue);
		const DisplayPolygons*					GetCurrentDisplayPolys () const { return currentDisplayPolys; }
		bool									IsSunViewActive () const { return VGEData == sunVGEData; }
		void									ClearSight ();
		void									ClearInternalEngine ();

		static	SightPtr						New (DiskCachingMethod cachingMethodIn,
													 Model3DPtr	mainModelIn,
													 const Modeler::Camera &camera,
													 const VESHSETS &veshSets,
													 const Modeler::SunSettings &sunSettings,
													 const GS::Optional<GS::UniString>& forcedName = GS::NoValue);

		static void* operator					new      (size_t size) { return new char[size]; }
		static void  operator					delete   (void* ptr) { delete[] reinterpret_cast<char*>(ptr); }

		static void* operator					new[]	   (size_t size);
		static void  operator					delete[] (void* ptr) { delete[] reinterpret_cast<char*>(ptr); }

		void									DetachClippedModelFromMain ();	// throw exception
		void									RemoveClipFromClippedModel ();

		void									DetachMainModel ();

		Model3DPtr								GetMainModelPtr () const;
		ConstModel3DPtr							GetConstMainModelPtr () const;
		void									SetMainModelPtr (const Model3DPtr& newMainModel);
		Model3DPtr								GetClippedModelPtr () const;

		Box3D									GetProjectedBounds () const;
		void									SetProjectedBounds (const Box3D& newBounds);

		const ModStamp&							GetLastTransformationStamp () const;
		bool									IsTransformModelFullValid () const;
		VectorGraphicEngine::UpdateSwitch		CalcTransformModelUpdateSwitch () const;
		void									SetTransformModelFullValid ();
		void									SetTransformModelInvalid ();
		ULong									AllocateProjectedLightSource (ULong num);
		ULong									GetProjectedLightSourceCount () const;
		ULGHT*									GetProjectedLightSourceRecPtr (ULong index);
		void									DeleteProjectedLightSourceRec (ULong index);
		bool									IsTransformLightsFullValid () const;
		VectorGraphicEngine::UpdateSwitch		CalcTransformLightsUpdateSwitch () const;
		void									SetTransformLightsFullValid ();
		void									SetTransformLightsInvalid ();
		void									SetTransformInProgress ();
		void									ResetTransformInProgress ();


		bool									IsProgressFullValid (const ProgressType progressType) const;
		void									SetProgressFullValid (const ProgressType progressType);
		void									SetProgressInvalid (const ProgressType progressType);
		void									SetInProgress (const ProgressType progressType);
		bool									IsInProgress (const ProgressType progressType) const;


		bool									IsStampMoreRecentThanLastTransform (const Modeler::ModStamp & stamp) const;

		ULong									GetFirstNewElem () const;
		void									SetFirstNewElem (ULong firstNewElem);
		void									ResetVGE ();
		void									ResetVGEViews ();

		ElimBody*								GetElimBodyPtr ();
		const ElimBody&							GetConstElimBody () const;
		void									ClearElimBody ();

		void									ClearAllConditions ();
		void									PrintConditions ();

		void									GetHiddenViewConditions (short hiddenCond[3]) const;
		void									SetHiddenViewConditions (const short hiddenCond[3]);

		bool									IsCameraAllignedModelFullValid () const;
		bool									Model3DChangedSinceLastConversion () const;
		bool									ShouldFullRebuildDepthSort () const;

		bool									IsClippedModelExists () const;
		void									SetClippedModelExistence (bool isExists);
		bool									IsHiddenViewExists () const;
		short									GetMarkedStatusBits (short mask) const;
		void									ClearMarkedStatusBits (short mask);
		void									SetMarkedStatusBits (short newVal);

		void									SwitchToOverlappedHiddenPolygons ();
		void									SwitchToClippedHiddenPolygons ();

		void									GetBackgroundTexture (const RENDSETS& rendSets, RTXT *rtxt) const;
		short									LoadBackgroundRGB (const RENDSETS& rendSets, short hor, short ver, RGBfloat *bRgb);
		void									ChangeConvertState (ULong fromElemIdx, ULong fromBodyIdx);


		const Camera&							GetCamera () const;
		void									SetCamera (const Camera&);

		const SunSettings&						GetSunSettings () const;
		void									SetSunSettings (const SunSettings&);

		ULong									GetAllItemsCount ()				const;
		ULong									GetUsedBytes ()					const;
		ULong									GetAllocatedBytes ()			const;

		CompositeContainerSizeReport			ReportSize (const GS::UniString& name) const;

		void									Purge ();

		const Model3DViewer*					GetConstMainModel3DViewerPtr (void) const;
		const Model3DViewer*					GetConstClippedModel3DViewerPtr (void) const;

		bool									IsSightInvalid () const;	//AACS: should be eliminated
		bool									AreDisplayPolysFullValid () const;

		const VESHSETS&							GetVectorShadowSettings (void)	const;
		void									SetVectorShadowSettings (const VESHSETS& vectorShadowSettings);

#ifdef DEBUVERS
		bool									CheckSightModels () const;
#endif
		// IModel3DObserver

		virtual void	SyncDeletedElems (const Model3D& model3D, ULong fElemIdx, ULong lElemIdx, ULong  ndel) override;
		virtual void	ElemsTruncated (const Model3D& model3D, ULong newElemCount) override;
		virtual void	ElemDeleted (const Model3D& model3D, ULong elemIdx, const Modeler::ConstElemPtr& deletedElem) override;
		bool			ElemDeleted (VectorGraphicEngineData* vge, const Model3D& model3D, ULong elemIdx);
		virtual void	RestartDelBoundsBuilding (const Model3D& model3D) override;
		virtual void	ConvertStateChanged (const Model3D& model3D, ULong fromElemIdx, ULong fromBodyIdx) override;
		virtual void	ModelChanged (const Model3D& model3D) override;
		virtual void	ModelCleared (const Model3D& model3D) override;
		virtual void	ColorShadesChanged (const Model3D& model3D) override;
		virtual void	AllConditionsCleared (const Model3D& model3D) override;
		virtual void	EventBeforeClear (const Model3D& model3D) override;
		virtual void	ConvertStarted (const Model3D& model3D) override;
		virtual void	ModelCompressed (const Model3D& model3D, const GS::Array<CompressElemData>& compressInfos) override;

		// ISightObserver
		void	Attach (ISightObserver& observer) const;
		void	Detach (ISightObserver& observer) const;

		void	SendCameraChanged (const Modeler::Camera &newCamera);
		void	SendVectorShadowSettingsChanged (const VESHSETS &newVeshSets);
		void	SendSunSettingsChanged (const Modeler::SunSettings &newSunSets);
		void	SendZoomDefChanged (const ZOOMDEF &newZoomDef);
	};	//Sight


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class GSMODELER_DLL_EXPORT SightViewer : public MainContainerBase::Viewer {
	protected:
		friend class	Sight;
		ConstSightPtr	sight;

		SightViewer ();		// disabled

	public:

		SightViewer  (const ConstSightPtr sight);
		SightViewer	(const SightViewer& src_viewer);
		~SightViewer ();

		SightViewer&	operator= (const SightViewer& src);
		bool			operator== (const SightViewer& src) const;
		bool			operator!= (const SightViewer& src) const;

		const VectorGraphicEngineData& GetConstVGEData () const;
		const Sight & GetConstSight () const;

		ULong	GetProjectedBodyCount () const;
		ULong	GetProjectedPolygonCount () const;
		ULong	GetProjectedEdgeCount () const;
		ULong	GetProjectedLightSourceCount () const {return sight->GetProjectedLightSourceCount ();}
		ULong	GetHiddenLineEdgeCount () const;
		ULong	GetHiddenLineVertexCount () const;
		ULong	GetClippedHiddenPolygonCount () const;
		ULong	GetHiddenPolygonCount () const;
		ULong	GetHiddenLinePolygonCount () const;
		ULong	GetHiddenLineTriangleCount () const;
		ULong	GetShadingColorCount () const;

		USize						GetProjectedPointCloudCount			() const;
		USize						GetHiddenPointCloudCount			() const;
		PointCloud::ConstViewPtr	GetConstHiddenPointCloud			(UIndex index) const;
		const HPOINTCLOUD*			GetConstHiddenPointCloudRecPtr		(UIndex index) const;
		const UPOINTCLOUD*			GetConstProjectedPointCloudRecPtr	(UIndex index) const;

		const UBODY*	GetConstProjectedBodyRecPtr (ULong index) const;
		const UPGON*	GetConstProjectedPolygonRecPtr (ULong index) const;
		const UEDGE*	GetConstProjectedEdgeRecPtr (ULong index) const;
		const ULGHT*	GetConstProjectedLightSourceRecPtr (ULong index) const;
		const HEDGE*	GetConstHiddenLineEdgeRecPtr (ULong index) const;
		const HVERT*	GetConstHiddenLineVertexRecPtr (ULong index) const;
		const HPGON*	GetConstClippedHiddenPolygonRecPtr (ULong index) const;
		const HPVER*	GetConstClippedHiddenPolygonVertexRecPtr (ULong index) const;
		const HPGON*	GetConstHiddenPolygonRecPtr (ULong index) const;
		const HPVER*	GetConstHiddenPolygonVertexRecPtr (ULong index) const;
		const UCOL*		GetConstShadingColorRecPtr (ULong index) const;

		bool			AreHiddensOverlapped () const;
		bool			AreHiddensClipped () const;

		bool			HasClippedModel () const;
		bool			HasHiddenView () const;
		bool			IsSightInvalid () const;
		bool			IsTransformModelFullValid () const;
		bool			IsTransformLightsFullValid () const;

		short			GetMarkedStatusBits (short mask) const;
		ConstModel3DPtr	GetConstMainModelPtr () const;

		const Model3DViewer*	GetConstMainModel3DViewerPtr () const;
		const Model3DViewer*	GetConstClippedModel3DViewerPtr () const;

		const Camera&		GetCamera () const;
		const SunSettings&	GetSunSettings () const;

		Box3D			GetProjectedBounds () const;

		ULong			GetAllItemsCount ()				const;
		ULong			GetUsedBytes ()					const;
		ULong			GetAllocatedBytes ()			const;

		void	GetShadeRGB (GSAttributeIndex iumat, short illuminationIndex, GS_RGBColor *rgb) const;

		const ElimBody&		GetConstElimBody (void) const;
		const VESHSETS&		GetVectorShadowSettings (void)	const;

		const TRANMAT&				GetLocalCoordSys () const;
	};

	class SightOnlyModifier : MainContainerBase::OnlyModifier {
	private:
		friend class	Sight;
		SightPtr		sight;

		SightOnlyModifier ();		// disabled

	public:
		SightOnlyModifier (const SightPtr sight);
		SightOnlyModifier (const SightOnlyModifier& src);

		~SightOnlyModifier ();

		SightOnlyModifier&	operator= (const SightOnlyModifier& src);
		bool				operator== (const SightOnlyModifier& src) const;
		bool				operator!= (const SightOnlyModifier& src) const;

		VectorGraphicEngineData	& GetVGEData ();

		UBODY*	GetProjectedBodyRecPtr (ULong index);
		UPGON*	GetProjectedPolygonRecPtr (ULong index);
		UEDGE*	GetProjectedEdgeRecPtr (ULong index);
		ULGHT*	GetProjectedLightSourceRecPtr (ULong index) { return sight->GetProjectedLightSourceRecPtr (index); }
		HEDGE*	GetHiddenLineEdgeRecPtr (ULong index);
		HVERT*	GetHiddenLineVertexRecPtr (ULong index);

		UIndex			AllocateProjectedPointClouds		(USize num);
		void			ReallocateProjectedPointClouds		(USize size);

		UPOINTCLOUD*	GetProjectedPointCloudRecPtr		(UIndex index);
		HPOINTCLOUD*	GetHiddenPointCloudRecPtr			(UIndex index);

		ULong	AllocateProjectedPolygons (ULong num);
		ULong	AllocateProjectedEdges (ULong num);

		void	ReAllProjectedBodies (ULong index);
		void	ReAllProjectedPolygons (ULong index);
		void	ReAllProjectedEdges (ULong index);
		void	ReAllProjectedLightSources (ULong index);

		void	CompressHiddenBodies (Int32 fromInd, Int32 offset, Int32 num);
		void	CompressHiddenLinePolygons (Int32 fromInd, Int32 offset, Int32 num);
		void	CompressHiddenLineTriangles (Int32 fromInd, Int32 offset, Int32 num);

		void	InitShadingColors (Int32 num);

		void	FreeShadingColors ();

		void	SetCamera (const Camera&);
		void	SetSunSettings (const SunSettings&);

		void	ClearMarkedStatusBits (short mask);
		void	SetMarkedStatusBits (short newVal);
		void	GetBackgroundTexture (const RENDSETS& rendSets, RTXT *rtxt);

		ElimBody*	GetElimBodyPtr ();
		void		ClearElimBody ();

		void	SetLocalCoordSys	 (const TRANMAT &localCoordSys);
	};

	class SightModifier : public SightViewer, public SightOnlyModifier {
	private:
		friend class	Sight;

		SightModifier();		// disabled

	public:
		SightModifier (const SightPtr src_sight);
		SightModifier (const SightModifier& src);
		~SightModifier () {}

		SightModifier&	operator= (const SightModifier& src);
		bool			operator== (const SightModifier& src) const;
		bool			operator!= (const SightModifier& src) const;
	};



#define		SIGHTVERSION		1010		/* If you change sight record ==>
	increment this value	*/
	/* 1001 bab015 B_SHADOWSIZE + more_shadow_bo kiirtasa	*/
	/* 1002 bab035 OBODYP real pointer	*/
	/* 1003 bab040 kill BEXT	*/
	/* 1004 bab060 TRANMAT	*/
	/* 1005 bab062 TEVE	*/
	/* 1006 bab062 TEVE	*/
	/* 1007 bab612 pal3D remove	*/
	/* 1008 fgy 2003.02.25. begin removing elements */
	/* 1009 fgy 2003.02.28. begin removing elements */
	/* 1010 fgy 2003.03.07. begin removing elements */


	namespace CameraUtils {
		// Sight base
		void	SetShowType (SightPtr sight, short method);
		short	GetShowType	(ConstSightPtr sight);

		void	SetDrawMode (SightPtr sight, short mode);
		short	GetDrawMode	(ConstSightPtr sight);

		void	SetDrawMode (SightPtr sight, short mode);
		short	GetDrawMode	(ConstSightPtr sight);

		void	SetPixelSize (SightPtr sight, short pixsize);
		short	GetPixelSize (ConstSightPtr sight);

		void	SetMonoColor (SightPtr sight, bool mono);
		bool	GetMonoColor (ConstSightPtr sight);

		void	SetAllEdges (SightPtr sight, bool alledges);
		bool	GetAllEdges (ConstSightPtr sight);

		void	SetPerspRect (SightPtr sight, bool prect);
		bool	GetPerspRect (ConstSightPtr sight);

		void	SetBackGround3D (SightPtr sight, const GS_RGBColor& rgb);
		void	GetBackGround3D (ConstSightPtr sight, GS_RGBColor *rgb);

		void	Set3DBackgroundSkyColor (SightPtr sight, const GS_RGBColor& rgb);
		void	Get3DBackgroundSkyColor (ConstSightPtr sight, GS_RGBColor *rgb);

		void	Set3DBackgroundEarthColor (SightPtr sight, const GS_RGBColor& rgb);
		void	Get3DBackgroundEarthColor (ConstSightPtr sight, GS_RGBColor *rgb);

		void	SetBackGround3DasR (SightPtr sight, bool asr);
		bool	GetBackGround3DasR (ConstSightPtr sight);

		void	Set3DWindowSize (SightPtr sight, short hor, short ver);
		void	Get3DWindowSize (ConstSightPtr sight, short *hor, short *ver);

		void	SwitchShadowOnOff (SightPtr sight, bool switchOn);

		bool	MustVectShadow (ConstSightPtr sight);
		void	GetEffects (ConstSightPtr sight, short *effects);
		void	SetEffects (SightPtr sight, short effects);

		// SightViewer/Modifier base
		void	SetShowType (SightModifier& uModifier, short method);
		short	GetShowType (const SightViewer& uViewer);

		void	SetDrawMode (Modeler::SightModifier& uModifier, short mode);
		short	GetDrawMode	(const Modeler::SightViewer& uViewer);

		void	SetPixelSize (SightModifier& uModifier, short pixsize);
		short	GetPixelSize (const SightViewer& uViewer);

		void	SetMonoColor (SightModifier& uModifier, bool mono);
		bool	GetMonoColor (const SightViewer& uViewer);

		void	SetAllEdges (SightModifier& uModifier, bool alledges);
		bool	GetAllEdges (const SightViewer& uViewer);

		void	SetPerspRect (SightModifier& uModifier, bool prect);
		bool	GetPerspRect (const SightViewer& uViewer);

		void	SetBackGround3D (SightModifier& uModifier, const GS_RGBColor& rgb);
		void	GetBackGround3D (const SightViewer& uViewer, GS_RGBColor *rgb);

		void	Set3DBackgroundSkyColor (SightModifier& uModifier, const GS_RGBColor& rgb);
		void	Get3DBackgroundSkyColor (const SightViewer& uViewer, GS_RGBColor *rgb);

		void	Set3DBackgroundEarthColor (SightModifier& uModifier, const GS_RGBColor& rgb);
		void	Get3DBackgroundEarthColor (const SightViewer& uViewer, GS_RGBColor *rgb);

		void	SetBackGround3DasR (SightModifier& uModifier, bool asr);
		bool	GetBackGround3DasR (const SightViewer& uViewer);

		void	Set3DWindowSize (SightModifier& uModifier, short hor, short ver);
		void	Get3DWindowSize (const SightViewer& uViewer, short *hor, short *ver);

		GSMODELER_DLL_EXPORT
			void	SwitchShadowOnOff (SightModifier& uModifier, bool switchOn);

		bool	MustVectShadow (const SightViewer& uViewer);
		void	GetEffects (const SightViewer& uViewer, short *effects);
		void	SetEffects (SightModifier& uModifier, short effects);
	}


	namespace SunSettingUtils {

		// Sight base
		void	SetSunSettings (const SightPtr& sight, const SunSettingsRec* sunSets);
		void	SetSunPosition (const SightPtr& sight, double sunAngXY, double sunAngZ);
	}



}// namespace Modeler


class RenderingSightGuard
{
public:
	RenderingSightGuard (Modeler::SightPtr sight, const RENDSETS& rendSets);
	~RenderingSightGuard ();

private:
	Modeler::SightPtr sight;
	Modeler::Camera oldCam;
};


#include	"SightImp.hpp"


#endif
