#if !defined (GRAPHICSATTRIBUTES_H)
#define GRAPHICSATTRIBUTES_H

#include	"GSModeler2DExport.h"

#include	"IAttributeReader.hpp"

namespace GX {
	namespace Pattern {
		class FillData; 
		class LineData; 
	}
}

struct RGBfloat;

/*==========================		PROTOTYPES		========================*/

// =============================================================================
//
// Pen attribute
//
// =============================================================================

GSMODELER2D_DLL_EXPORT
GSErr	GSM2D_CALL	AGXgenPenAttrs (const Modeler::IAttributeReader& attReader, short npen);

GSMODELER2D_DLL_EXPORT
short	GSM2D_CALL	AGXnumPenAttr (const Modeler::IAttributeReader& attReader);

GSMODELER2D_DLL_EXPORT
GSErr	GSM2D_CALL	AGXgetPenRGB (const Modeler::IAttributeReader& attReader, short ipen, GS_RGBColor *penRGB);

GSMODELER2D_DLL_EXPORT
GSErr	GSM2D_CALL	AGXPen2RGBfloat (const Modeler::IAttributeReader& attReader, short ipen, RGBfloat *rgbf);

GSMODELER2D_DLL_EXPORT
GSErr	GSM2D_CALL	AGXgetPenWidth (const Modeler::IAttributeReader& attReader, short ipen, double& width);

// =============================================================================
//
// Line type attribute
//
// =============================================================================

GSMODELER2D_DLL_EXPORT
GSAttributeIndex	GSM2D_CALL	AGXindexLtypeAttr (const Modeler::IAttributeReader& attReader, const GS::UniString& name);

GSMODELER2D_DLL_EXPORT
GSAttributeIndex	GSM2D_CALL	AGXnumLtypeAttr (const Modeler::IAttributeReader& attReader);

Int32	AGXGetLineItemSize (short itemType);

GSMODELER2D_DLL_EXPORT
GSErr	GSM2D_CALL	AGXnameLtypeAttr (const Modeler::IAttributeReader& attReader, short iltype, GS::UniString& name);


// =============================================================================
//
// Fill attribute
//
// =============================================================================

GSMODELER2D_DLL_EXPORT
GSAttributeIndex	GSM2D_CALL	AGXnumFillAttr (const Modeler::IAttributeReader& attReader);

GSMODELER2D_DLL_EXPORT
GSErr	GSM2D_CALL	AGXnameFillAttr (const Modeler::IAttributeReader& attReader, GSAttributeIndex ifattr, GS::UniString& name);

GSMODELER2D_DLL_EXPORT
GSAttributeIndex	GSM2D_CALL	AGXindexFillAttr (const Modeler::IAttributeReader& attReader, const GS::UniString& name);

GSMODELER2D_DLL_EXPORT
void	GSM2D_CALL	AGXFillDefType (const GX::Pattern::FillData* fillPtr, bool *ishatch, bool *isempty);

GSMODELER2D_DLL_EXPORT
GSErr	GSM2D_CALL	AGXgetFillClass (const GX::Pattern::FillData* fillPtr, short& iClass);

GSMODELER2D_DLL_EXPORT
GSErr	GSM2D_CALL	AGXgetFillClass (const Modeler::IAttributeReader& attReader, GSAttributeIndex ifill, short& iClass);

GSMODELER2D_DLL_EXPORT
	GSErr	GSM2D_CALL	AGXgetFillAttr (const Modeler::IAttributeReader& attReader, GSAttributeIndex ifattr, GX::Pattern::FillData** filldef);

GSMODELER2D_DLL_EXPORT
bool	GSM2D_CALL	 AGXIsScaledHatch (const Modeler::IAttributeReader& attReader, GSAttributeIndex ifill);

#endif
