// *****************************************************************************
// File:			IIntProperty.hpp
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

#ifndef IINTPROPERTY_HPP
#define IINTPROPERTY_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "Hint.hpp"


namespace Tracking {

// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT IIntProperty
{
public:
	IIntProperty () {}
	virtual ~IIntProperty ();

	virtual	Int32	GetValue () const = 0;
	virtual void	SetValue (Int32 value, Hint hint) = 0;
};

}	//namespace Tracker

#endif
