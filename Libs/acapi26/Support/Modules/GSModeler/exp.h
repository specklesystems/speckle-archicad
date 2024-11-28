// *****************************************************************************
//
//						Public functions for GSModeler's Export
//
// Contact person:	BA
//
// *****************************************************************************

#ifndef EXP_H
#define EXP_H

#include	"GSModelerExport.h"
#include	"SharedPtr.hpp"
#include	"Model3D/PropList.hpp"

#include "envir.h"

namespace ModelerAPI {
	class Box2D;
	class Camera;
	class Model;
	class ModelProxy;
	class ModelViewFeatures;
	class RenderingFeatures;
	class RenderingSettings;
	class ParameterList;
}

namespace Modeler {
	class Camera;
	class Model3DViewer;
	class Sight;
	class Model3D;
	class SunSettings;
	typedef GS::ConstSharedPtr<Model3D>	ConstModel3DPtr;
	typedef GS::SharedPtr<Sight>		SightPtr;
	typedef GS::ConstSharedPtr<Sight>	ConstSightPtr;
}

namespace IO {
	class Location;
}

namespace GX {
	class Image;
}

struct RENDSETS;
struct HIDDSETS;
struct VESHSETS;
struct GS_RGBColor;
class MDID;


GSMODELER_DLL_EXPORT
GSErrCode	EXPRendInit (bool addOnsDisable, const IO::Location* addOnFolderDef);

GSMODELER_DLL_EXPORT
GSErrCode	EXPRendFree (void);

GSMODELER_DLL_EXPORT
bool		EXPRendFeatureIsEnabled (const MDID& mdid, Int32 enableFlags);

GSMODELER_DLL_EXPORT
GSErrCode	EXPGetModelViewFeatures (Int32 id, ModelerAPI::ModelViewFeatures* features);

GSMODELER_DLL_EXPORT
Int32		EXPGetRendCount (void);

GSMODELER_DLL_EXPORT
Int32		EXPGetModelViewerCount (void);

GSMODELER_DLL_EXPORT
void		EXPGetRendMDID (short id, MDID* mdid);

GSMODELER_DLL_EXPORT
void		EXPGetModelViewerMDID (short id, MDID* mdid);

GSMODELER_DLL_EXPORT
void		EXPGetRendMenuStr (const MDID& mdid, GS::UniString* menustr);

GSMODELER_DLL_EXPORT
void		EXPGetRendExportToMenuStr (const MDID& mdid, GS::UniString* menustr);

GSMODELER_DLL_EXPORT
void		EXPGetRendStatusBarStr (const MDID& mdid, GS::UniString* statusBarStr);

GSMODELER_DLL_EXPORT
void		EXPGetModelViewerMenuStr (short id, GS::UniString* menustr);

GSMODELER_DLL_EXPORT
void		EXPGetModelViewerStatusBarStr (short id, GS::UniString* statusBarStr);

GSMODELER_DLL_EXPORT
GSErrCode	EXPSetRendOptions (const MDID& mdid);						/*bab065*/

GSMODELER_DLL_EXPORT
GSErrCode	EXPSetModelViewOptions (ModVisualizationEngine& visEngine, short showType, const RENDSETS& rendSets, const HIDDSETS& hiddSets, short effects, const VESHSETS &veshSets, const GS_RGBColor &bkgSkyColor, const GS_RGBColor &bkgEarthColor, bool bkg3DasR, Int32 id, bool* mod);

GSMODELER_DLL_EXPORT
GSErrCode	EXPSetRendOptionsData (const MDID& mdid, Int32 dataSize, const void* data);

GSMODELER_DLL_EXPORT
GSErrCode	EXPSetModelViewOptionsData (Int32 id, Int32 dataSize, const void* data);

GSMODELER_DLL_EXPORT
GSErrCode	EXPGetRendOptionsDataSize (const MDID& mdid, Int32* dataSize);

GSMODELER_DLL_EXPORT
GSErrCode	EXPGetModelViewOptionsDataSize (Int32 id, Int32* dataSize);

GSMODELER_DLL_EXPORT
GSErrCode	EXPGetRendOptionsData (const MDID& mdid, void* data);

GSMODELER_DLL_EXPORT
GSErrCode	EXPGetModelViewOptionsData (Int32 id, void* data);

GSMODELER_DLL_EXPORT
GSErrCode	EXPSetRendProperties (const MDID& mdid, const Modeler::PropertyList& properties);

GSMODELER_DLL_EXPORT
GSErrCode	EXPSetModelViewProperties (Int32 id, const Modeler::PropertyList& properties);

GSMODELER_DLL_EXPORT
GSErrCode	EXPGetRendProperties (const MDID& mdid, Modeler::PropertyList** properties);

GSMODELER_DLL_EXPORT
GSErrCode	EXPGetModelViewProperties (Int32 id, Modeler::PropertyList** properties);

GSMODELER_DLL_EXPORT
GSErrCode	EXPGetRendUserData (const MDID& mdid, void** userData);

GSMODELER_DLL_EXPORT
GSErrCode	EXPGetModelViewUserData (Int32 id, void** userData);

GSMODELER_DLL_EXPORT
GSErrCode	EXPModelViewer_Start (short typeId, Int32* viewerId);

GSMODELER_DLL_EXPORT
GSErrCode	EXPModelViewer_End (Int32 viewerId);

GSMODELER_DLL_EXPORT
bool		EXPRegisterAddOn (const IO::Location* addOn, void* userData);

GSMODELER_DLL_EXPORT
GSErrCode	EXPGetModel (Modeler::SightPtr sight, ModelerAPI::Model* model, Modeler::IAttributeReader* attributeReaderInit/*, GDL::IFileServices* fileServices*/);

GSMODELER_DLL_EXPORT
GSErrCode	EXPGetModel (Modeler::ConstModel3DPtr model3D, ModelerAPI::Model* model, Modeler::IAttributeReader* attributeReaderInit/*, GDL::IFileServices* fileServices*/);

GSMODELER_DLL_EXPORT
const Modeler::Model3DViewer	
			EXPGetInternalModelViewer (const ModelerAPI::Model& externalModel);

GSMODELER_DLL_EXPORT
GSErrCode	EXPGetParameterList (Modeler::PropertyList* parameters, ModelerAPI::ParameterList* parameterList);

GSMODELER_DLL_EXPORT
GSErrCode	EXPRendProvideExportToMenuIcon (const MDID& mdid, GX::Image* engineIcon, UInt32 dpi = 96);

GSMODELER_DLL_EXPORT
GSErrCode	EXPRendProvideInfo (const MDID& mdid, GX::Image* engineIcon, GS::UniString* engineName, GS::UniString* devInfo, GS::UniString* linkText, double resolutionFactor = 1.0);

GSMODELER_DLL_EXPORT
GSErrCode	EXPRendProvidePictureWindowInfo (const MDID& mdid, GX::Image* engineIcon, GS::UniString* renderingText, GS::UniString* renderedText, double resolutionFactor = 1.0);

GSMODELER_DLL_EXPORT
bool		EXPDoFillMissingTextures ();

#endif
