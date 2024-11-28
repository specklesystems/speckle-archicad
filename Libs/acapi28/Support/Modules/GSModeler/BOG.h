// *****************************************************************************
//
//						Public Functions for Model Generation
//
// Contact person:	BA
//
// *****************************************************************************

#ifndef	_BOG_H_
#define	_BOG_H_

#include	"GSModelerExport.h"
#include	"GSModelerVers.h"
#include	"GDLProc.h"	// GDL3DComponent
#include	"GDLWrapping.hpp"
#include	"SharedPtr.hpp"

namespace Modeler {
	class Model3D;
	typedef GS::SharedPtr<Model3D>		Model3DPtr;
	typedef GS::ConstSharedPtr<Model3D>	ConstModel3DPtr;
	class Sight;
	typedef GS::SharedPtr<Sight>		SightPtr;
	typedef GS::ConstSharedPtr<Sight>	ConstSightPtr;
	class Model3DViewer;
	class Model3DModifier;
	class Attributes;
	typedef GS::SharedPtr<Attributes>		AttributesPtr;
	typedef GS::ConstSharedPtr<Attributes>	ConstAttributesPtr;
	class Elem;
	typedef GS::ConstSharedPtr<Elem>	ConstElemPtr;
	class IAttributeReader;
}


namespace ModelerAPI {
	class Model;
}

namespace Modeler {
	struct	VOCA;
	class	MeshBody;
	class	BaseUserData;
	class	UserDataContainer;
}

namespace GS {
	class ProcessControl;
}

struct CUT_RECORD;
class Model3DGeneratorState;

GSMODELER_DLL_EXPORT
GDL3DComponent	BOGGetGeneratorComponent (GS::ProcessControl& processControl, const Modeler::IAttributeReader* attReader);

GSMODELER_DLL_EXPORT
GDL3DComponent	BOGGetGeneratorComponent (GS::ProcessControl& processControl, const Modeler::ConstAttributesPtr& targetAttributes, const Modeler::IAttributeReader* attReader);

GSMODELER_DLL_EXPORT
void	BOGReleaseGeneratorComponent (GDL3DComponent* genStateComponent);

GSMODELER_DLL_EXPORT
GDLAttributeComponent	BOGGetAttributeGeneratorComponent (GDL3DComponent* genStateComponent);

GSMODELER_DLL_EXPORT
void	BOGBeginModelGeneration (Modeler::Model3DModifier&	modelModifier);

GSMODELER_DLL_EXPORT
void	BOGEndModelGeneration (Modeler::Model3DModifier&	modelModifier,
							   ULong						firstNewElemIdx);

GSMODELER_DLL_EXPORT
void		BOGCutSection (GS::ProcessControl&				processControl, 
						   const Modeler::IAttributeReader& attReader,
						   Modeler::SightPtr				sight,
						   Modeler::Model3DModifier&		modelModifier,
						   const GS::Array<CUT_RECORD>&		cutrecs);

namespace Modeler {
	enum class UpdateAttributesFromParent {
		Enabled,
		Disabled
	};

	enum class AttributesUpdateResult;
}

GSMODELER_DLL_EXPORT
Modeler::AttributesUpdateResult BOGElemBegin (GDL3DComponent component, 
									 Modeler::UpdateAttributesFromParent updateAttributesFromParent = Modeler::UpdateAttributesFromParent::Disabled);

GSMODELER_DLL_EXPORT
void		BOGBeginDebugElem (GDL3DComponent component);

GSMODELER_DLL_EXPORT
Int32		BOGElemEnd (GDL3DComponent component, const Modeler::VOCA& voca, Modeler::Model3DModifier& modifier);

GSMODELER_DLL_EXPORT
Modeler::ConstElemPtr BOGElemEnd (GDL3DComponent component, const Modeler::VOCA& voca, Modeler::AttributesPtr attributes);

GSMODELER_DLL_EXPORT
void		BOGElemAbort (GDL3DComponent component); // You want to BOGReleaseGeneratorComponent without BOGElemEnd

GSMODELER_DLL_EXPORT
void		BOGCreateDebugElem (GDL3DComponent component, Modeler::Model3DModifier& modelModifier);

GSMODELER_DLL_EXPORT
void		BOGBodyEnd (GDL3DComponent component);

GSMODELER_DLL_EXPORT
void		BOGCopySightEntity (
						Modeler::Model3DViewer& sourceModelViewer,
						Modeler::Model3DModifier& destModelModifier,
						const Modeler::VOCA *newVoca, ULong elemIdx);

GSMODELER_DLL_EXPORT
void		BOGMode (GDL3DComponent&	component,
					 short				mode);


GSMODELER_DLL_EXPORT
short	BOGetCandElemSolidState (GDL3DComponent component);
GSMODELER_DLL_EXPORT
GSErr	BOSetCandElemCutplanes (GDL3DComponent component, const GS::Array<CUT_RECORD>* cutplanes);
GSMODELER_DLL_EXPORT
void	BOSetCandElemShapeType (GDL3DComponent component, short btype);
GSMODELER_DLL_EXPORT
void	BOSetCandElemWrapping (GDL3DComponent component, Wrapping wrapping);
GSMODELER_DLL_EXPORT
Wrapping	BOGetCandElemWrapping (GDL3DComponent component);
GSMODELER_DLL_EXPORT
void	BOGGetCandElemInfo (GDL3DComponent component, TRANMAT& tran);

GSMODELER_DLL_EXPORT
void BOGBody (
		GDL3DComponent component, const Modeler::MeshBody& baseElem, const TRANMAT& tran, short defaultColor, const GlimaIdx& defaultGlima, Int32 defaultEdgeStatus,
		const GS::Array<GlimaIdx> *glimaPerPoly = nullptr, const GS::Array<short> *colorPerEdge = nullptr, const GS::Array<Int32> *statusPerEdge = nullptr
	);

GSMODELER_DLL_EXPORT
void BOGSetBodyUserData (GDL3DComponent component, const GS::Guid& guid, const Modeler::BaseUserData* bodyUserData);

GSMODELER_DLL_EXPORT
void BOGSetElemUserData (GDL3DComponent component, const GS::Guid& guid, const Modeler::BaseUserData* elemUserData);

GSMODELER_DLL_EXPORT
void BOGSetElemUserDataContainer (GDL3DComponent component, const Modeler::UserDataContainer* elemUserDataContainer);

GSMODELER_DLL_EXPORT
void BOGSetElemGuidForReport (GDL3DComponent component, const GS::Guid& guid);


#endif
