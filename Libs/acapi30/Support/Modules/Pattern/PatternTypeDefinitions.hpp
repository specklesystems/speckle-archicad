// Contact person : KiP
// Common type definitions in Pattern module

#ifndef PATTERN_TYPE_DEFINITIONS_HPP
#define PATTERN_TYPE_DEFINITIONS_HPP

#pragma once

// from GSRoot
#include "Ref.hpp"
#include "NonThreadSafeCounter.hpp"


namespace GX
{
namespace Pattern
{

class FillData;
typedef GS::Ref<FillData, GS::NonThreadSafeCounter> FillDataRef;

class VectorFillPatternData;
typedef GS::Ref<VectorFillPatternData, GS::NonThreadSafeCounter> VectorFillPatternDataRef;

}
}

#endif