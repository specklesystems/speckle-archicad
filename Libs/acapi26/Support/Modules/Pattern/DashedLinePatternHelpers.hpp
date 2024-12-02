// Contact person : NN

#ifndef DASHEDLINEPATTERN_HELPERS_HPP
#define DASHEDLINEPATTERN_HELPERS_HPP

#pragma once

// from GSRoot
#include "Array.hpp"
#include "Pair.hpp"

// from Geometry
#include "PeriodicLinearFunction.hpp"

// from Pattern
#include "PatternExport.h"
#include "IDashedLinePattern.hpp"

namespace GX {
namespace Pattern {

//================================================
//
//	ComputeCenterPositions and Helper Functions
//
//================================================

PATTERN_DLL_EXPORT GS::Array<GS::Pair<double, double>>	ComputeCenterPositions		(const GS::Array<IDashedLinePattern::DashItem>& dashItems, const double minDashLength);
PATTERN_DLL_EXPORT GS::Array<double>					GetPossibleMiddlePoints		(const GS::Array<IDashedLinePattern::DashItem>& dashItems);
PATTERN_DLL_EXPORT void									AddErrorsByGap				(Geometry::PeriodicLinearFunction& periodicFunction, double gapStartPoint, double gapLength, double minDashLength);
PATTERN_DLL_EXPORT Geometry::PeriodicLinearFunction		CalculateRightErrorFunction (const GS::Array<IDashedLinePattern::DashItem>& dashItems, const double periodLength, const double middlePoint, const double minDashLength);
PATTERN_DLL_EXPORT Geometry::PeriodicLinearFunction		CalculateLeftErrorFunction  (const GS::Array<IDashedLinePattern::DashItem>& dashItems, const double periodLength, const double middlePoint, const double minDashLength);

double	CalculatePatternLength (const GS::Array<IDashedLinePattern::DashItem>& dashItems);
}
}

#endif
