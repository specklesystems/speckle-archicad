// *********************************************************************************************************************
// Description:		PenData
//
// Module:			GSModeler2D
// Namespace:		Modeler
// Contact person:	AACS
//
// SG compatible
// *********************************************************************************************************************

#if !defined (PenData_HPP)
#define PenData_HPP

#pragma once
// from Pattern
#include	"GSPix.h"
//#include	"GSModeler2DExport.h" 

namespace Modeler {

	class PenData 
	{
	public: 
		PenData () 
		{
			penRGB.red   = 65535;
			penRGB.green = 65535;
			penRGB.blue  = 65535;

			penWidth = 0.0;
		}

		PenData (
			const GS_RGBColor&	penRGB,
			double				penWidth) :
			penRGB (penRGB),
			penWidth (penWidth)
		{
		}

		GS_RGBColor	penRGB;
		double		penWidth;
	};

} //Modeler
#endif

