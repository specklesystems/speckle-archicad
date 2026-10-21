// *****************************************************************************
// Library Part old functions. PJ252.99.12.09.
// LibPart / SectOld.h
//
// Contact person: PJ
//
// *****************************************************************************

#ifndef	_VectorImageIO_H_
#define	_VectorImageIO_H_

#pragma once

#include "GSRoot.hpp"
#include "VectorImageExport.h"
#define StoreAsDefault		0
#define EmptyHdl			-1003

class VectorImage;

// -----------------------------------------------------------------------------
// Prototypes
// -----------------------------------------------------------------------------

VI_DLL_EXPORT
GSErr VI_CALL	SwapLP_2DDrawPartPtr (GS::PlatformSign inplatform, GSPtr sy2DPtr, Int32 syLen, GS::PlatformSign toplatform);

VI_DLL_EXPORT
GSErr VI_CALL	SwapLP_2DDrawPart (GS::PlatformSign inplatform, GSHandle sy2DHdl, GS::PlatformSign toplatform);

VI_DLL_EXPORT
GSErr VI_CALL	ConvertOldsSy2D_To_NewSy2D (GSHandle oldSyHdl, VectorImage* vectorImage);

#endif
