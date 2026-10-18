#ifndef HATCH_COMPARE_UTILS_HPP
#define HATCH_COMPARE_UTILS_HPP

#pragma once

// from GSRoot
#include "Owner.hpp"

// from VectorImage
#include "VectorImageExport.h"

class VectorImage;

namespace VI {
namespace HatchPriority {
	class ComparerEnvironment;
}
}

namespace VI {

VI_DLL_EXPORT GS::Owner<HatchPriority::ComparerEnvironment> CreateComparerEnvironmentFromImage (const VectorImage& image);

}

#endif
