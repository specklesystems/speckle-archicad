// *****************************************************************************
// File:			DGNumericInputLimitHandling.hpp
//
// Description:
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	NN
// *****************************************************************************

#ifndef DGNUMERICINPUTLIMITHANDLING_HPP
#define DGNUMERICINPUTLIMITHANDLING_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DG.h"

// --- Class declarations ------------------------------------------------------

namespace DG {

class DG_DLL_EXPORT NumericInputLimitHandler
{
public:
	virtual ~NumericInputLimitHandler ();

	virtual double GetMinValue (const double specifiedMin) = 0;
	virtual double GetMaxValue (const double specifiedMax) = 0;

	static void InitializeHandlers	(const DGNumericInputLimitHandlers& newNumericInputLimitHandlers);

	static void RemoveHandlers		();

	static NumericInputLimitHandler& GetHandler	(const short etType);
};


}	// namespace DG

#endif
