// *****************************************************************************
// File:			IStringProperty.hpp
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

#ifndef ISTRINGPROPERTY_HPP
#define ISTRINGPROPERTY_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "UniString.hpp"
#include "Hint.hpp"


namespace Tracking {

// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT IStringProperty
{
public:
	IStringProperty () {}
	virtual ~IStringProperty ();

	virtual	GS::UniString	GetValue () const = 0;
	virtual void			SetValue (const GS::UniString& value, Hint hint) = 0;
};

}	//namespace Tracker

#endif
