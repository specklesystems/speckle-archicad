
// *****************************************************************************
//
//                            Class TemlateClassInfo
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined TEMPLATECLASSINFO_HPP
#define TEMPLATECLASSINFO_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "ParameterPackTraits.hpp"


// =============================================================================

namespace GS {

class NoType {};

template <class TemplateParameter1, class... TemplateParameters>
struct TemlateClassInfo {
	template <UInt32 Index>
	using	TemplateParameter = typename ParameterPack<TemplateParameter1, TemplateParameters...>::template Type<Index>;

	static constexpr UInt32 TemplateParameterCount = ParameterPack<TemplateParameter1, TemplateParameters...>::Size;

	const UInt32 templateParameterCount = TemplateParameterCount;
	const char*	 name	   = nullptr;	// full name (e.g. with full namespace path)
	const char*  shortName = nullptr;	// simpler name (e.g. without namespace)
	const char*  id		   = nullptr;

	TemlateClassInfo (const char* name, const char* id) : name (name), id (id) {}
	TemlateClassInfo (const char* name, const char* shortName, const char* id) : name (name), shortName (shortName), id (id) {}
};

}	// namespace GS


#endif
