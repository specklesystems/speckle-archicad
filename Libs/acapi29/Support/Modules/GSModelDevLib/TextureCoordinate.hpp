// *****************************************************************************
// Texture coordinate
// GSModeler, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (TEXTURECOORDINATE_HPP)
#define TEXTURECOORDINATE_HPP

// ----------------------- Includes          -----------------------------------

#include "Vertex.hpp"
#include "ModelVector.hpp"

#include "GSModelerExport.h"

// ----------------------- Class declaration -----------------------------------

namespace ModelerAPI {


class GSMODELER_DLL_EXPORT TextureCoordinate {
public:
	double	u;
	double	v;

	void	ApplyRotationAndScale (double rotAngle, double xScale, double yScale);
	void	ApplyMaterialParameters (double rotAngle, double xSize, double ySize);
};


struct TextureCoordinateSystem {
private:

public:
	enum TransformationMode {
		InvalidMode = 0,
		BoxMode = 1,
		CylindricMode = 2,
		SphericMode = 3,
		NurbsParamMode = 7
	};

	TransformationMode	transformationMode;

	Vertex	origo;
	Vector	xAxis;
	Vector	yAxis;
	Vector	zAxis;

	TextureCoordinateSystem () : transformationMode (TransformationMode::InvalidMode) {}
	TextureCoordinateSystem (TransformationMode transformationMode,
		Vertex origo,
		Vector xAxis,
		Vector yAxis,
		Vector zAxis) : transformationMode(transformationMode), origo(origo), xAxis(xAxis), yAxis(yAxis), zAxis(zAxis) {}

};


} // namespace ModelerAPI


#endif
