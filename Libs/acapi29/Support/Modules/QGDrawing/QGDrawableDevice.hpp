// *****************************************************************************
//
//                                Class DrawableDevice
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGDRAWABLEDEVICE_HPP
#define QGDRAWABLEDEVICE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------
#include "QGBase.hpp"
#include "QGContextAttribs.hpp"
#include "QGContext.hpp"

// ============================== class DrawableDevice =========================

namespace QG {

class	IConcreteDeviceImp;

enum DeviceProperty {
	CapableDrawSymbolFill							= 0x0001,
	IncapableDrawGradientFill						= 0x0002,
	IncapableDrawTransparentGradientFill			= 0x0004,
	OnlyCapableToDrawBlackToTransparentGradientFill = 0x0008	//AEAS-3986
};

class QG_DLL_EXPORT DrawableDevice {
private:
	IConcreteDeviceImp*		deviceImp;
	Context					qgContext;
	double					virtualResolution;
	bool					contextInUse;

protected:
	void					SetVirtualResolution (double dpiValue);
	void					SetDeviceImp (IConcreteDeviceImp* icDeviceImp);
	IConcreteDeviceImp* 	GetDeviceImp (void) const;

public:
#ifdef XPSPrinting
	enum DeviceType
	{
		dtOSDefault = 0,
		dtWPF = 1
	};
#endif
	DrawableDevice ();
	virtual ~DrawableDevice ();

	virtual	double			GetVirtualResolution (void) const;
	virtual	double			GetRealResolution (void) const = 0;
	virtual	QG::Context*	GetQGContext (const ContextAttribs& contextAttribs);
	virtual	void			ReleaseQGContext (Context**	context);

	// TT 131644: Apple does not retain some objects that would be needed for the delayed drawing.
	void						ReleaseObjectsFromPool (void);
	const GS::ExtraReleasePool*	GetReleasePool (void) const;

	void						SetProperty (DeviceProperty prop);
	void						ClearProperty (DeviceProperty prop);
	bool						IsProperty (DeviceProperty prop);

	virtual	GSErrCode			GetError ();
};

}	// namespace QG
// ______________________________ class DrawableDevice _________________________

#endif	// QGDRAWABLEDEVICE_HPP
