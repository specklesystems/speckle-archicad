
#ifndef NURBSBODYGDLWRITE_HPP
#define NURBSBODYGDLWRITE_HPP

#include	"Model3D/Model3DExport.h"

namespace Modeler {

struct NurbsGDLWriteControl {

	enum WriteLayout {
		WriteAsUStr = 0,
		WriteAsCStr 
	};

	enum ColorMode {
		DontWriteColors				= 0,
		WriteEdgeColor				= 1,
		WriteFaceSegmentationPen	= 2,

		WriteEveryColor = WriteEdgeColor | WriteFaceSegmentationPen
	};

	enum MaterialMode {
		DontWriteMaterial = 0,
		WriteMaterial
	};

	WriteLayout		layout;
	ColorMode		colorMode;
	MaterialMode	materialMode;
	GS::UniString	smoothnessOverwrite;

};

class OChannel;
class NurbsBodyBase;

MODEL3D_DLL_EXPORT
void WriteNurbsBodyAsGDL (GS::OChannel& oc, const NurbsBodyBase& body, NurbsGDLWriteControl writeControl, bool enableReadNurbsFlag = false);

} // namespace Modeler
#endif
