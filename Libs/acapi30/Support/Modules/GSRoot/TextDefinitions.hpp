// *****************************************************************************
//
// Contact person: MB, PR
//
// *****************************************************************************

#ifndef GS_TEXTDEFINITIONS_HPP
#define GS_TEXTDEFINITIONS_HPP

#include "Definitions.hpp"

#ifndef GS_BUILD_MODULE
// from Standard Library
#include <string_view>
#endif


namespace GS {


enum class CaseComparison : UInt16 {
	Sensitive, Insensitive
};

inline constexpr CaseComparison CaseSensitive = CaseComparison::Sensitive;
inline constexpr CaseComparison CaseInsensitive = CaseComparison::Insensitive;


} // namespace GS


using namespace std::string_view_literals;


#endif /* GS_TEXTDEFINITIONS_HPP */