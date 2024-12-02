
// *****************************************************************************
//
// Declaration of FunctionRunnable class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_FUNCTIONRUNNABLE_HPP
#define GS_FUNCTIONRUNNABLE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Runnable.hpp"

#include <functional>



// --- FunctionRunnable class --------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT FunctionRunnable : public GS::Runnable {

private:
	std::function<void ()>	m_function;

// Construction / destruction:
public:
	explicit FunctionRunnable (const std::function<void ()>& function);
	template<class Function, class... Args>
	explicit FunctionRunnable (Function&& function, Args&&... args);

// Runnable interface implementation:
public:
	virtual void			Run () override;

};

////////////////////////////////////////////////////////////////////////////////
// FunctionRunnable inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class Function, class... Args>
inline FunctionRunnable::FunctionRunnable (Function&& function, Args&&... args) :
	m_function ()
{
	m_function = std::bind (std::forward<Function> (function), std::forward<Args> (args)...);}

}

#endif // GS_FUNCTIONRUNNABLE_HPP