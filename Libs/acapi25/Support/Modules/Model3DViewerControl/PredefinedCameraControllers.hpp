#ifndef MODELVIEWER_PREDEFINED_CAMERA_CONTROLLERS_HPP
#define	MODELVIEWER_PREDEFINED_CAMERA_CONTROLLERS_HPP

#include "ICameraController.hpp"
#include "Visualization/Camera.hpp"


namespace ModelViewer {


class MODELVIEWER_DLL_EXPORT FixedPerspectiveCamera : public ICameraController {
public:
	FixedPerspectiveCamera (const Geometry::Point3D& position, const Geometry::Point3D& lookAt, double fov);
	virtual ~FixedPerspectiveCamera ();

	virtual Modeler::Camera					GetDefaultCamera () override;
	virtual ICameraInteractionRef			OnMouseMoveEvent (const GS::Array<MouseButton>& buttons, const GS::Array<ModifierKey>& keys, const Vector2D& positionOffset) override;
	virtual ICameraInteractionRef			OnMouseWheelEvent (ScrollDirection direction) override;
	virtual InteractionResult				ProcessCameraInteraction (const ICameraInteractionRef& cameraInteracion, Modeler::Camera& camera) override;

private:
	Modeler::Camera	camera;
};


}


#endif