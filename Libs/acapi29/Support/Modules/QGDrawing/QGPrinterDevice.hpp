// *****************************************************************************
//
//                                Class PrinterDevice
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGPRINTERDEVICE_HPP
#define QGPRINTERDEVICE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------
#include "QGDrawableDevice.hpp"

// ============================== class PrinterDevice ==========================

namespace QG {

class IPrinterDeviceImp;

class QG_DLL_EXPORT PrinterDevice : public QG::DrawableDevice {
private:
	IPrinterDeviceImp*	imp;

	PrinterDevice (const PrinterDevice&);
	PrinterDevice& operator=(const PrinterDevice&);

public:
#ifdef XPSPrinting
	PrinterDevice (void* deviceContext, void* pageInfo = nullptr, DrawableDevice::DeviceType deviceType = DrawableDevice::dtOSDefault);
	PrinterDevice (void* deviceContext, double dpiValue, void* pageInfo = nullptr, DrawableDevice::DeviceType deviceType = DrawableDevice::dtOSDefault); 	// any virtual resolution can be set as initial value
#else
	PrinterDevice (void* deviceContext, void* pageInfo = nullptr);
	PrinterDevice (void* deviceContext, double dpiValue, void* pageInfo = nullptr); 	// any virtual resolution can be set as initial value
#endif
	double			GetRealResolution (void) const override;

#ifdef XPSPrinting
	void	BeginPage ();
	void	EndPage ();
#endif
};

}	// namespace QG
// ______________________________ class PrinterDevice __________________________

#endif	// QGPRINTERDEVICE_HPP
