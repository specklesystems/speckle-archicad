#ifndef MODELVIEWER_BACKGROUNDGRIDGENERATOR_HPP
#define	MODELVIEWER_BACKGROUNDGRIDGENERATOR_HPP

#include "IExtraModelGenerator.hpp"

// from GSRoot
#include "Ref.hpp"

// from Pattern
#include "GSPix.h"


namespace Modeler {
	class Attributes;
	typedef GS::SharedPtr<Attributes> AttributesPtr;

	class IAttributeReader;
}


namespace ModelViewer {


class MODELVIEWER_DLL_EXPORT BackgroundGridGenerator : public IExtraModelGenerator {
public:
	BackgroundGridGenerator (int cellCount, double cellSize, const GS_RGBColor& mainGridLineColor, const GS_RGBColor& auxGridLineColor);
	virtual ~BackgroundGridGenerator ();

	virtual Modeler::ConstModel3DPtr	Generate (const Modeler::AttributesPtr& attributes, const Modeler::IAttributeReader& attributeReader) const override;

	static const GS::Guid&				GetId ();

private:
	int				cellCount;
	double			cellSize;
	GS_RGBColor		mainGridLineColor;
	GS_RGBColor		auxGridLineColor;
};


using BackgroundGridGeneratorRef = GS::Ref<BackgroundGridGenerator>;


}


#endif