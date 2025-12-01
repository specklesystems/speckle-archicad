// *****************************************************************************
// File:			IDoubleProperty.hpp
//
// Description:
//
// Project:			ARCHICAD
//
// Namespace:
//
// Contact person:	NZ, DG
//
// SG compatible
// *****************************************************************************

#ifndef IDOUBLEPROPERTY_HPP
#define IDOUBLEPROPERTY_HPP

#pragma once

#include "Hint.hpp"
#include "TransparentWindowLibDefinitions.hpp"

// --- Includes ----------------------------------------------------------------


namespace Tracking {

// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT IDoubleProperty
{
public:
	IDoubleProperty ();
	virtual ~IDoubleProperty ();

	virtual	double	GetValue () const = 0;
	virtual void	SetValue (double value, Hint hint) = 0;
};


}	//namespace Tracker

#endif
