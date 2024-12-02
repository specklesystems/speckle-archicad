#ifndef LEARNINGCONTENT_TOOLTIPUTILS_HPP
#define LEARNINGCONTENT_TOOLTIPUTILS_HPP

#include "TransparentWindowLibDefinitions.hpp"
#include "Tooltip.hpp"

namespace LearningContent {

TRANSPARENTWINDOWLIB_DLL_EXPORT TooltipGeometry CalcTooltipGeometry (const DG::NativeRect&		 screenRect,
																	 const DG::NativeRect&		 parentRect,
																	 const DG::NativeRect&		 objectRect,
																	 const DG::NativeUnit&		 contentWidth,
																	 const DG::NativeUnit&		 contentHeight,
																	 const VisualizerParameters& setups,
																	 const GS::Optional<short>&  itemType);
}

#endif
