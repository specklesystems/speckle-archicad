#ifndef GEOM_PPE_SOLUTIONQUALITY_HPP
#define GEOM_PPE_SOLUTIONQUALITY_HPP
#pragma once
#include "GeometricDefinitions.h"

enum class SolutionQuality
{
	ExcellentQuality,
	GoodQuality,
	AcceptableQuality,
	Failed,
	NotSolved	//e.g. when user breaks with process control...
};


GEOMETRY_DLL_EXPORT const char* SolutionQualityStr (const SolutionQuality q);

#endif //GEOM_PPE_SOLUTIONQUALITY_HPP
