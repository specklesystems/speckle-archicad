// *****************************************************************************
// Main file for VectorImage module
// VectorImage, Platform independent
//
// Namespaces:        Contact person:
//                         DBE
//
// SG compatible
// *****************************************************************************

#ifndef	VECTORIMAGEMAIN_HPP
#define	VECTORIMAGEMAIN_HPP

#include "VectorImageExport.h"

typedef GSErr	VI_CALL	GetPictureInfoProc (GSHandle hPict,
												short *pixelSizeX,
												short *pixelSizeY,
												short *colorDepth);

typedef struct
{
	GetPictureInfoProc		*getPictureInfo;
} VIInitEnv;

extern VIInitEnv gVIInitEnv;

VI_DLL_EXPORT GSErr	VI_CALL	VIInit (VIInitEnv *viinitenv);

#endif	// VECTORIMAGEMAIN_HPP
