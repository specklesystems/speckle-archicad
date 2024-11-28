#ifndef ENUM_VALUE_APPLIER_HPP
#define ENUM_VALUE_APPLIER_HPP

// from UD
#include "UDDefinitions.hpp"

namespace UD {

class UD_DLL_EXPORT EnumValueApplier
{
public:
	virtual ~EnumValueApplier ();

	virtual void ApplyNewValue (UInt32 index) const = 0;
};

}

#endif