#ifndef ICOMPARABLE_HPP
#define ICOMPARABLE_HPP
#pragma once

#include "Object.hpp"
#include "Ref.hpp"
#include "PatternExport.h"

namespace GX {
namespace Pattern {

class PATTERN_DLL_EXPORT IComparable {
public:
	virtual ~IComparable ();

public:
	virtual bool operator== (const IComparable& other) const = 0;
			bool operator!= (const IComparable& other) const;

	static bool Compare (GS::Ref<GS::Object> data1, GS::Ref<GS::Object> data2);
};

}
}


#endif
