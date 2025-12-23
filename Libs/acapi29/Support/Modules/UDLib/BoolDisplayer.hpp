#ifndef BOOL_DISPLAYER_HPP
#define BOOL_DISPLAYER_HPP

// from UD
#include "UDDefinitions.hpp"

namespace UD {

class UD_DLL_EXPORT BoolDisplayer
{
public:
	virtual ~BoolDisplayer ();
	virtual void SetValue (bool newValue) = 0;
	virtual void EnableDisplayer () = 0;
	virtual void DisableDisplayer () = 0;
};

}

#endif