// *****************************************************************************
//
//                                Class BitmapDevice
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGBITMAPDEVICE_HPP
#define QGBITMAPDEVICE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------
#include "QGDrawableDevice.hpp"

// ============================== class BitmapDevice ==============================

namespace QG {

class Bitmap;

class QG_DLL_EXPORT BitmapDevice : public QG::DrawableDevice {
private:

	BitmapDevice (const BitmapDevice&);
	BitmapDevice& operator=(const BitmapDevice&);

public:
#ifdef XPSPrinting
	BitmapDevice (QG::Bitmap& inBitmap, DrawableDevice::DeviceType deviceType = DrawableDevice::dtOSDefault);
	BitmapDevice (QG::Bitmap& inBitmap, double dpiValue, DrawableDevice::DeviceType deviceType = DrawableDevice::dtOSDefault); 	// any virtual resolution can be set as initial value
#else
	BitmapDevice (QG::Bitmap& inBitmap);
	BitmapDevice (QG::Bitmap& inBitmap, double dpiValue); 	// any virtual resolution can be set as initial value
#endif
	virtual	double	GetRealResolution (void) const override;
};

}	// namespace QG
// ______________________________ class BitmapDevice ______________________________

#endif	// QGBITMAPDEVICE_HPP
