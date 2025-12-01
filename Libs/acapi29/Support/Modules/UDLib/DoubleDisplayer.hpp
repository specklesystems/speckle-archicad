#ifndef DOUBLE_DISPLAYER_HPP
#define DOUBLE_DISPLAYER_HPP

// from UD
#include "UDDefinitions.hpp"

namespace UD {

class UD_DLL_EXPORT DoubleDisplayer
{
public:
	virtual ~DoubleDisplayer ();
	virtual void SetValue (double newValue) = 0;
	virtual void EnableDisplayer () = 0;
	virtual void DisableDisplayer () = 0;
	virtual void SetValueToNotAvailable () = 0;
	virtual void SetValueToNotAvailable (const GS::UniString& notAvailableText) = 0;
};

}

#endif