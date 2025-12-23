#ifndef MODELVIEWER_SIMPLEPERSPECTIVECAMERA_HPP
#define	MODELVIEWER_SIMPLEPERSPECTIVECAMERA_HPP

#include "ICameraController.hpp"

// from GSModeler
#include "Visualization/Camera.hpp"


namespace ModelViewer {


class MODELVIEWER_DLL_EXPORT SimplePerspectiveCamera : public ICameraController {
public:
	SimplePerspectiveCamera (const Geometry::Point3D& position, const Geometry::Point3D& lookAt, double fov);
	virtual ~SimplePerspectiveCamera ();

	virtual Modeler::Camera					GetDefaultCamera () override;
	virtual ICameraInteractionRef			OnMouseMoveEvent (const GS::Array<MouseButton>& buttons, const GS::Array<ModifierKey>& keys, const Vector2D& positionOffset) override;
	virtual ICameraInteractionRef			OnMouseWheelEvent (ScrollDirection direction) override;
	virtual InteractionResult				ProcessCameraInteraction (const ICameraInteractionRef& cameraInteracion, Modeler::Camera& camera) override;
	virtual ICameraInteractionRef			OnMouseDoubleClicked (const MouseButton& button) override;

	ModelViewer::ICameraInteractionRef		ResetCamera ();

	void	SetRotationCenter (const Geometry::Point3D& rotationCenter);

private:
	Modeler::Camera		camera;
	Geometry::Point3D	rotationCenter;
};


}


#endif