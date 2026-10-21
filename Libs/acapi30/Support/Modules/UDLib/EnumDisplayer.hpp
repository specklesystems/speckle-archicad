#ifndef ENUM_DISPLAYER_HPP
#define ENUM_DISPLAYER_HPP

// from UD
#include "UDDefinitions.hpp"

namespace UD {

class UD_DLL_EXPORT EnumDisplayer
{
public:
	virtual ~EnumDisplayer ();
	virtual void SetEnumItem (UInt32 index) = 0;
	virtual void DisableEnumItem (UInt32 index) = 0;
	virtual void EnableEnumItem (UInt32 index) = 0;
	virtual void SetFullDisable () = 0;
	virtual void ReleaseFullDisable () = 0;
};

}

#endif