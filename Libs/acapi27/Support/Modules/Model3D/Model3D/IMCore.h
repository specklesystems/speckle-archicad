/****************************************************************************/
/*																			*/
/*							PROTOTYPES FOR IM... ROUTINES					*/
/*																			*/
/****************************************************************************/
#ifndef _IMCORE_H_
#define _IMCORE_H_

#pragma once

#include	"Model3D/Model3DPrivExp.h"
#include	"Model3D/ModelerAttributes.hpp"
#include	"UMAT.hpp"

namespace GDL
{
	class IFileRef;
	class IFileServices;
}

namespace Modeler {
	class MaterialData;
	class IAttributeReader;
}

typedef enum {
	BodyData,
//	LghtData,
	PgonData,
	VertData,
	VectData,
	TeveData,
	EdgeData,
	PedgData,
	HotsData,
	TranData
//	VocaData
} ID_3DData;


#define ATTRIBUTENAMELENGTH		256


/*==============================	GLOBALS	============================*/

extern  MODEL3D_DLL_EXPORT char	gGDLMatFormat[256];									/* 2 "GDL_MATERIAL%d" */
extern  MODEL3D_DLL_EXPORT char	gPenMatFormat[256];									/* 3 "PEN_MATERIAL%d" */
 //static	char	gFloatMatFormat[256];											/* 4 "FLOAT_MATERIAL#%d" */
extern  MODEL3D_DLL_EXPORT char	gErrorMatName[ATTRIBUTENAMELENGTH];			/* 5 "ERROR_MATERIAL "*/
extern  MODEL3D_DLL_EXPORT char	gGDLFillFormat[256];								/* 6 "GDL_FILL%d" */
extern  MODEL3D_DLL_EXPORT char	gErrorFillFormat[256];								/* 7 "ERROR_FILL%d" */
extern 	MODEL3D_DLL_EXPORT char	gShadowMatName[ATTRIBUTENAMELENGTH];			/* 8  "SHADOW_MATERIAL" */
 //static	char	gMasterGDLName[32];												/* 9  "MASTER_GDL" */
extern  MODEL3D_DLL_EXPORT char	gGDLMatDefFormat[256];								/* 10 "GDLM%d_%s" */
extern  MODEL3D_DLL_EXPORT char	gImportMatFormat[256];								/* 11 "IMPORT_MATERIAL_%d" */
extern  MODEL3D_DLL_EXPORT char	gACStyleFormat[256];								/* 12 "AC_STYLE_%d" */
 //static	char	gMasterEndGDLName[32];											/* 13 "MASTEREND_GDL" */


MODEL3D_PRIVATE_EXPORT
void	MOD3D_PRIV	IMCreateSummedAreaTableFromPixmap (GSConstPtr pixmap, Int32 xSize, Int32 ySize,
										   UInt32* summedAreaTable);								/*pzs9.02.99*/

MODEL3D_PRIVATE_EXPORT
void	MOD3D_PRIV	IMLoadAGSPixMap (const GDL::IFileRef* fileRef, Int32 pictIndex, GSPixMapHandle *pixhandle, GSPixelType outputFormat = GSPT_Unknown);

MODEL3D_PRIVATE_EXPORT
void	MOD3D_PRIV	IMGetPictFileDef (const GS::UniString& name, Int32 pictIndex, GDL::IFileServices* fileServices, GDL::IFileRef** fileRef, bool* isExist = nullptr);

MODEL3D_PRIVATE_EXPORT
void	MOD3D_PRIV	IMGetPictSize (GDL::IFileRef* fileRef, Int32 pictIndex, Int32 *hsiz, Int32 *vsiz);

MODEL3D_PRIVATE_EXPORT
void	MOD3D_PRIV	IMAdjustUfilsInBinary (const Modeler::IAttributeReader& attReader, Modeler::Attributes::Modifier& attrModifier, short matmode,
							   const GSAttributeIndex *mufil, GSAttributeIndex *iifil, GSAttributeIndex iufil, UFIL *uufil);	// ufide: C style structures (function is used just in FL.c)

MODEL3D_PRIVATE_EXPORT
void	MOD3D_PRIV	IMPenToUMAT (const Modeler::IAttributeReader& attReader, short color, UMAT* aumat);


MODEL3D_PRIVATE_EXPORT
Int32	MOD3D_PRIV IMFindUMat (const Modeler::Attributes::Viewer* viewer, const UMatGenFrom& index);

MODEL3D_PRIVATE_EXPORT
void	MOD3D_PRIV	IMErrorMater (GS::Owner<Modeler::MaterialData>& mater);

MODEL3D_DLL_EXPORT
void	MODEL3D_CALL IMUmatNoName (GSAttributeIndex iumat, GS::UniString& mname);

MODEL3D_DLL_EXPORT
void	MODEL3D_CALL IMSetupMater (GS::Owner<Modeler::MaterialData>& mater);

#endif
