#ifndef MODELVIEWER_ICONTEXTMENUPROVIDER_HPP
#define	MODELVIEWER_ICONTEXTMENUPROVIDER_HPP


#include "UDSimpleContextMenu.hpp"
#include "Model3DViewerControlExport.hpp"


namespace ModelViewer {


class MODELVIEWER_DLL_EXPORT IContextMenuProvider {
public:
	virtual ~IContextMenuProvider ();

	virtual UD::SimpleContextMenu		GetContextMenu () = 0;
};


using IContextMenuProviderRef = GS::Ref<IContextMenuProvider>;


}


#endif