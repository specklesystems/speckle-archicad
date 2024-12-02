#ifndef STRING_DISPLAYER_HPP
#define STRING_DISPLAYER_HPP

// from UD
#include "UDDefinitions.hpp"

namespace UD {

class UD_DLL_EXPORT StringDisplayer
{
public:
	virtual ~StringDisplayer ();
	virtual void SetValue (GS::UniString newValue) = 0;
	virtual void EnableDisplayer () = 0;
	virtual void DisableDisplayer () = 0;
	virtual void ShowDisplayer () = 0;
	virtual void HideDisplayer () = 0;
};

}

#endif