// *****************************************************************************
//
// Contact person: MB, PR
//
// *****************************************************************************

#ifndef GS_TEXTDEFINITIONS_HPP
#define GS_TEXTDEFINITIONS_HPP

#include "Definitions.hpp"

// from Standard Library
#include <string_view>


namespace GS {


enum class CaseComparison : UInt16 {
	Sensitive, Insensitive
};

constexpr CaseComparison CaseSensitive = CaseComparison::Sensitive;
constexpr CaseComparison CaseInsensitive = CaseComparison::Insensitive;


} // namespace GS


using namespace std::string_view_literals;


#endif /* GS_TEXTDEFINITIONS_HPP */
