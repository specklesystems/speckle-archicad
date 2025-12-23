#ifndef MODELVIEWER_ICAMERACONTROLLER_HPP
#define	MODELVIEWER_ICAMERACONTROLLER_HPP

#include "ICameraInteraction.hpp"
#include "Vector2D.hpp"


namespace ModelViewer {


enum class MouseButton {
	NoButton,
	Left,
	Middle,
	Right
};


enum class ModifierKey {
	Control,
	Shift
};


enum class ScrollDirection {
	Forward,
	Backward
};


enum class InteractionResult {
	NeedRedraw,
	NothingChanged
};


class MODELVIEWER_DLL_EXPORT ICameraController {
public:
	virtual ~ICameraController ();

	virtual Modeler::Camera					GetDefaultCamera () = 0;
	virtual ICameraInteractionRef			OnMouseMoveEvent (const GS::Array<MouseButton>& buttons, const GS::Array<ModifierKey>& keys, const Vector2D& positionOffset) = 0;
	virtual ICameraInteractionRef			OnMouseWheelEvent (ScrollDirection direction) = 0;
	virtual InteractionResult				ProcessCameraInteraction (const ICameraInteractionRef& cameraInteracion, Modeler::Camera& camera) = 0;
	virtual ICameraInteractionRef			OnMouseDoubleClicked (const MouseButton& button) = 0;
};


using ICameraControllerRef = GS::Ref<ICameraController>;


}


#endif