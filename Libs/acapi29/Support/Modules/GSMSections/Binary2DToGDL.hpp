#ifndef	BINARY2DTOGDL_HPP
#define	BINARY2DTOGDL_HPP

#include "GDLProc.h"
#include "GSMSectionsExport.h"

GSMSECTIONS_DLL_EXPORT
GSErr	GSMSECTIONS_CALL	BFFragment2Prim (
								GDL2DComponent			gdl2Dcomponent,
								GDLAttributeComponent	gdlAttribComponent,
								GSUserData*				userDataPtr,
								GDL::IFileRef*			fileRef,
								short					attribflag,
								short					layer,
								short					color,
								short					drwIndex,
								const ADB::AttributeIndex&	ltype,
								short					lineProperty,
								const ADB::AttributeIndex& fillind,
								Int32					styleind,
								Hotspot2Proc*	hotspot2,			Line2Proc*		line2,
								Picture2Proc*	picture2,			Arc2Proc*		arc2,
								Circle2Proc*	circle2,			Spline2Proc*	spline2,
								Poly2Proc*		poly2,				Text2Proc*		text2,
								RichText2Proc*	richtext2,
								TextLenProc*	textlen,			StyleGenProc*	stylegen,
								const TRANMAT&	tran);

#endif	// BINARY2DTOGDL_HPP
