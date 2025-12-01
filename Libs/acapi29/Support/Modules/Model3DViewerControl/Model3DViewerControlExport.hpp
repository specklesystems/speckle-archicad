#ifndef MODELVIEWER_EXPORT_HPP
#define MODELVIEWER_EXPORT_HPP

#pragma once

#include "PlatformDLLExport.hpp"


// --- Export/Import directives ----------------------------------------------------------------------------------------

#if defined (MODEL_3D_VIEWER_CONTROL_DLL_COMPILE)
	#define MODELVIEWER_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define MODELVIEWER_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif


#endif
