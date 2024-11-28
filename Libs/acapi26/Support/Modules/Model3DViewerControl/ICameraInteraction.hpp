#ifndef MODELVIEWER_ICAMERAINTERACTION_HPP
#define MODELVIEWER_ICAMERAINTERACTION_HPP

#include "Ref.hpp"
#include "Model3DViewerControlExport.hpp"


namespace Modeler {
	class Camera;
}


namespace ModelViewer {


class MODELVIEWER_DLL_EXPORT ICameraInteraction {
public:
	virtual ~ICameraInteraction ();

	virtual void Apply (Modeler::Camera& camera) = 0;
};


using ICameraInteractionRef = GS::Ref<ICameraInteraction>;


}


#endif