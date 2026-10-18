#pragma once

#ifndef CPUTYPE_HPP
#define CPUTYPE_HPP

//from GSRoot
#include "GSRootExport.hpp"
#include "UniString.hpp"

namespace GS {

enum class CPUType {
	Unknown,
	x86,
	x86_64,
	ARM,
	ARM64
};

GSROOT_DLL_EXPORT GS::UniString CPUTypeToString (GS::CPUType cputype);

}

#endif