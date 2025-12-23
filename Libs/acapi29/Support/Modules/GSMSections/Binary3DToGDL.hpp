#if !defined (BINARY3DTOGLD_HPP)
#define BINARY3DTOGLD_HPP

#include "BMX.hpp"
#include "GSMSectionsExport.h"
#include "GDLProc.h"

namespace GDL
{
	class IFileRef;
}

struct GDL3DComponent;

struct GDLAttributeComponent;
class GSUserData;


GSMSECTIONS_DLL_EXPORT
GSErr	GSMSECTIONS_CALL BFOneBinaryBuf (GDL3DComponent component, GDLAttributeComponent attribcomp, GSUserData* userDataPtr, short color, GlimaIdx glima, short gmode,
											GDL::IFileRef* fileRef, short sectID,
											short matmode, Int32 bind1,
											short actshadow,
											VertProc		*vert, VectProc *vect, TeveProc *teve,
											EdgeProc		*edge, PgonProc *pgon,
											MaterGenProc	*matergen,
											FillGenProc		*fillgen,
											RtxtProc		*rtxt, CoorProc *coor,
											CloseBodyProc	*end,
											const TRANMAT *tran);

GSMSECTIONS_DLL_EXPORT
GSErr	GSMSECTIONS_CALL BFBinaryBuf (GDL3DComponent component, GDLAttributeComponent attribcomp, GSUserData* userDataPtr, short color, const GlimaIdx& glima, short gmode,
										 GDL::IFileRef* fileRef,
										 short matmode, short subIdent, Int32 bind,
										 short actshadow,
										 CloseBodyProc	*end,
										 VertProc		*vert, VectProc *vect,	TeveProc *teve,
										 EdgeProc		*edge, PgonProc *pgon,
										 MaterGenProc	*matergen,
										 FillGenProc	*fillgen,
										 RtxtProc		*rtxt, CoorProc *coor,
										 const TRANMAT& tran);


#endif

