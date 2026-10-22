// *****************************************************************************
// File:			DGUserItem.hpp
//
// Description:		NavigationParameters classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// SG compatible
// *****************************************************************************

#ifndef NAVIGATIONPARAMETERS_HPP
#define NAVIGATIONPARAMETERS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Color.hpp"
#include "DGItemProperty.hpp"


// --- Predeclarations ---------------------------------------------------------

// --- Class declarations ------------------------------------------------------

namespace DG {

// --- NavigationParameters ----------------------------------------------------

class NavigationParameters
{
public:
	enum Type {
		Pan = 0,
		Pinch,
		Rotate
	};

	const double distance;
	const double xPosition;
	const double yPosition;

	const double referenceDistance;
	const double referenceXPosition;
	const double referenceYPosition;

	const Type type;

public:
	NavigationParameters (double distance, double xPosition, double yPosition, Type type, const NavigationParameters* reference):
		distance (distance),
		xPosition (xPosition),
		yPosition (yPosition),
		referenceDistance (reference != nullptr ? reference->distance : distance),
		referenceXPosition (reference != nullptr ? reference->xPosition : xPosition),
		referenceYPosition (reference != nullptr ? reference->yPosition : yPosition),
		type (type)
	{
	}
};

}	// namespace DG

#endif
