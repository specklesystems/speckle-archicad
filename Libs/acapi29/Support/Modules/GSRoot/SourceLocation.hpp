// *****************************************************************************
//
// Contact person: MB, PR
//
// *****************************************************************************

#ifndef GS_SOURCELOCATION_HPP
#define GS_SOURCELOCATION_HPP

#include "Definitions.hpp"


namespace GS {


// TODO C++20: Replace this with std::source_location.
struct SourceLocation {
	const char* file;
	const char* function;
	UInt32		line;
};


} // namespace GS


#endif /* GS_SOURCELOCATION_HPP */
