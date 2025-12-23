#if !defined (ATTRIBUTECONVERTER_H)
#define ATTRIBUTECONVERTER_H

#include	"GSRoot.hpp"
#include	"GSModeler2DExport.h"
#include	"ISymbol2D.hpp"
#include	"Owner.hpp"
#include	"LineData.hpp"

namespace GX {
	namespace Pattern {
		class FillData; 
	}
}

GSMODELER2D_DLL_EXPORT
Int32	GSM2D_CALL	AGXDab2Ltype (const GS::UniString& name, short method, Int32 npar, const double **pars, ISymbol2D::ConstRef symbol2D, GS::Owner<GX::Pattern::LineData>& ltypdef);

GSMODELER2D_DLL_EXPORT
Int32	GSM2D_CALL	AGXDab2Fill (const GS::UniString& name, short method,
								 const GS::UniString& imageName,
								 Int32 npar, const double *const* pars, ISymbol2D::ConstRef symbol2D, GX::Pattern::FillData** filldef);

#endif
