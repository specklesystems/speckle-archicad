#ifndef	MODELVIEWER_EXTRAMODELGENERATOR_HPP
#define MODELVIEWER_EXTRAMODELGENERATOR_HPP

#include "Model3D/Model3DFwd.hpp"
#include "Model3DViewerControlExport.hpp"


namespace Modeler {
	class Attributes;
	typedef GS::SharedPtr<Attributes>			AttributesPtr;

	class IAttributeReader;
}


namespace ModelViewer {


class MODELVIEWER_DLL_EXPORT IExtraModelGenerator {
public:
	virtual ~IExtraModelGenerator ();

	virtual Modeler::ConstModel3DPtr Generate (const Modeler::AttributesPtr& attributes, const Modeler::IAttributeReader& attributeReader) const = 0;
};


}


#endif