#if ! defined NURBS_SURFACE_DUMP_DEBUG_TESSELLATED_HPP
#define NURBS_SURFACE_DUMP_DEBUG_TESSELLATED_HPP

#include	"Definitions.hpp"
#include	"Model3D/Model3DExport.h"


namespace GS {
	class OChannel;
}
namespace Modeler {
	class NurbsBodyBase;
}


namespace Modeler {


MODEL3D_DLL_EXPORT
void	NurbsSurfaceDumpDebugTessellated (GS::OChannel&			oc,
										  const NurbsBodyBase&	body,
										  UInt32				surfaceIndex,
										  UInt32				uSegmentCount = 10,
										  UInt32				vSegmentCount = 10);


MODEL3D_DLL_EXPORT
void	NurbsFaceLoop2dCurvesDumpDebug (GS::OChannel&			oc,
										const NurbsBodyBase&	body,
										UInt32					faceIndex);


MODEL3D_DLL_EXPORT
void	NurbsFaceLoop3dCurvesDumpDebug (GS::OChannel&			oc,
										const NurbsBodyBase&	body,
										UInt32					faceIndex);


} // namespace Modeler

#endif
