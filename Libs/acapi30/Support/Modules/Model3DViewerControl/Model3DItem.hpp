#ifndef MODELVIEWER_MODEL3DITEM_HPP
#define	MODELVIEWER_MODEL3DITEM_HPP


#include "ICameraController.hpp"
#include "IContextMenuProvider.hpp"
#include "IExtraModelGenerator.hpp"
#include "Sight.hpp"


namespace ModelViewer {


class MODELVIEWER_DLL_EXPORT Model3DItem {
public:
	Model3DItem (const DG::Panel& panel, short item, const ICameraControllerRef& cameraController, const GS::Ref<Modeler::IAttributeReader>& attributeReader);
	Model3DItem (const DG::Panel& panel, const DG::Rect& rect, const ICameraControllerRef& cameraController, const GS::Ref<Modeler::IAttributeReader>& attributeReader);
	~Model3DItem ();

	void	Redraw (bool redrawExtras = false);
	void	MoveAndResize (short hDisp, short vDisp, short hGrow, short vGrow);
	void	SetVisibility (bool show);
	bool	GetMousePositionInControl (DG::MousePosData& mousePosData) const;

	short	GetWidth () const;
	short	GetHeight () const;
	Box3D	GetModelBoundingBox () const;

	void	SetModel (const Modeler::Model3DPtr& model);
	void	SetSunSettings (const Modeler::SunSettings& sunSettings);
	void	SetContextMenuProvider (const GS::Ref<IContextMenuProvider>& contextMenuProvider);

	void	AddExtraModel (const GS::Guid& id, GS::Ref<IExtraModelGenerator> extraModel);
	void	RemoveExtraModel (const GS::Guid& id);

	void	ProcessCameraInteraction (const ICameraInteractionRef& cameraInteraction);

private:
	class Impl;
	GS::Ref<Impl> impl;
};


}


#endif