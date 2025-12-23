// *****************************************************************************
//
//                                ICustomDrawObject - interface
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined IQGCUSTOMDRAWOBJECT_HPP
#define IQGCUSTOMDRAWOBJECT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------
#include "QGContext.hpp"

#ifdef XPSPrinting
#include "QGDrawableDevice.hpp"
#endif

namespace QG {

class QG_DLL_EXPORT ICustomDrawObject {
public:
	virtual ~ICustomDrawObject ();
#ifdef XPSPrinting
	virtual void Draw (const QG::Rect& dstRect, QG::Context* qgContext, void* nativeContext, const QG::Matrix* matrix, void* nativePath = nullptr/*, QG::DrawableDevice::DeviceType dt = QG::DrawableDevice::dtOSDefault*/) = 0;
#else
	virtual void Draw (const QG::Rect& dstRect, QG::Context* qgContext, void* nativeContext, const QG::Matrix* matrix, void* nativePath = nullptr) = 0;
#endif
};

}	// namespace QG

#endif	// IQGCUSTOMDRAWOBJECT_HPP
