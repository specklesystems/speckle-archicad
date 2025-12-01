
// *****************************************************************************
//
// Declaration of FunctionCallable class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_FUNCTIONCALLABLE_HPP
#define GS_FUNCTIONCALLABLE_HPP

#pragma once


// --- Includes-----------------------------------------------------------------

#include "Callable.hpp"

#include <functional>



// --- FunctionCallable class --------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT FunctionCallable : public GS::Callable {

// Data members:
private:
	std::function<Object* ()>	m_function;

// Construction / destruction:
public:
	explicit FunctionCallable (const std::function<Object* ()>& function);
	template<class Function, class... Args>
	explicit FunctionCallable (Function&& function, Args&&... args);

// Callable interface implementation:
public:
	virtual Object*				Call () override;

};

////////////////////////////////////////////////////////////////////////////////
// FunctionCallable inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class Function, class... Args>
inline FunctionCallable::FunctionCallable (Function&& function, Args&&... args) :
	m_function ()
{
	m_function = std::bind (std::forward<Function> (function), std::forward<Args> (args)...);
}

}

#endif // GS_FUNCTIONCALLABLE_HPP