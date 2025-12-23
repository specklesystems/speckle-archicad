#ifndef TESSELLATENURBSBODY_HPP
#define TESSELLATENURBSBODY_HPP

#include "Model3D/Model3DExport.h"
#include "Model3D/CandidateMeshBody.hpp"
#include "Model3D/Nurbs/NurbsBody.hpp"

namespace Modeler {

struct MODEL3D_DLL_EXPORT NurbsTesselationParams {
	double chordHeightTolerance;
	double tangentAngleTolerance;

	static NurbsTesselationParams FromSmoothness (double smoothness);
};

MODEL3D_DLL_EXPORT
Modeler::NurbsTesselationParams GetTesselationParameters (const Modeler::NurbsSmoothnessInterval& smoothnessLimits);

MODEL3D_DLL_EXPORT
GS::Array<Modeler::CandidateMeshBodyPtr> TessellateNurbsBody (const Modeler::NurbsBody& nurbsBody,
															  const Modeler::NurbsTesselationParams& params);

}

#endif // TESSELLATENURBSBODY_HPP