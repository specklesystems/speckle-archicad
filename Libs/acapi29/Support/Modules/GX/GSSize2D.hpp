#ifndef GSSize2D_HEADER
#define GSSize2D_HEADER

#pragma once

#include "GXExport.h"

class GX_DLL_EXPORT_NOT_C GSSize2D
{
public:
	GSSize2D ();
	GSSize2D (UInt32 size);
	GSSize2D (UInt32 width, UInt32 height);

	UInt32 GetWidth () const;
	UInt32 GetHeight () const;

private:
	UInt32 width;
	UInt32 height;
};

#endif
