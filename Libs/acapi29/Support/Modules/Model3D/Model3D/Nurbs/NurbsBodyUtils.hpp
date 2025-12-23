#ifndef NURBSBODYUTILS_HPP
#define NURBSBODYUTILS_HPP
#pragma once

#include "Model3D/Model3DExport.h"

#include "Model3D/Nurbs/NurbsBodyBase.hpp"
#include "Model3D/ModelerAttributes.hpp"

namespace Modeler {

MODEL3D_DLL_EXPORT
bool	NurbsBodyAttributeIndicesBelowLimits (const NurbsBodyBase& body, const Attributes::CompatibilityLimits& compatibilityLimits);

}

#endif //NURBSBODYUTILS_HPP