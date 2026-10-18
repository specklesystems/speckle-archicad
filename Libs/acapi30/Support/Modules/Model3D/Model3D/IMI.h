/****************************************************************************/
/*																			*/
/*							PROTOTYPES FOR IM... ROUTINES					*/
/*																USED IN {I}	*/
/****************************************************************************/

#ifndef _IMI_H_
#define _IMI_H_

#pragma once

#include	"Model3D/Model3DExport.h"
#include	"Model3D/Model3DPrivExp.h"
#include	"GSPix.h"

namespace Modeler {
	class MaterialData;
	class Model3D;
	class Model3DViewer;
	class Model3DModifier;
	class IAttributeReader;
	class IAttributeReader;
}

class GSUserData;

/*================================	CONSTANTS	============================*/

#define	SPEC_GLIMA_OFFS		32000

/*================================	PROTOTYPES	============================*/

// This class serves caching purposes. It should not be reused across color
// index changes, but it is always safe to use a fresh, "empty" one.
class RGBColorTable {
private:
	GS::Array<GS_RGBColor> colorCache;

public:
	void InitIfNeeded (const Modeler::IAttributeReader& attReader);
	inline void Get (short colInd, GS_RGBColor *color)
	{
		*color = colorCache[colInd - 1];
	}
};

MODEL3D_DLL_EXPORT
short	STDCALL	IMSearchSimilar (const Modeler::IAttributeReader& attReader, const GS_RGBColor *rgb, RGBColorTable* colorTable = nullptr);

MODEL3D_DLL_EXPORT
short	STDCALL	IMSearchSimilar (const Modeler::IAttributeReader& attReader, double width);

#endif
