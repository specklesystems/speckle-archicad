
// *****************************************************************************
//
//                                InterFace DrawableDevice
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined DRAWABLEDEVICE_HPP
#define DRAWABLEDEVICE_HPP


// --------------------------------- Includes ----------------------------------

#include "TEBase.hpp"

// ============================== Class DrawableDevice ==============================

namespace TE {


class TE_DLL_EXPORT DrawableDevice  {
private:
	bool	enableDraw;

public:
	enum DeviceType {dtQuartz = 1, dtGDIPlus = 3, dtGDI32 = 4, dtGSPDFContext = 5, dtWPF = 6, dtD2D = 7 };

	inline	DrawableDevice (void) : enableDraw (true) {}
	virtual ~DrawableDevice ();

	virtual void SetDrawContext (void* drawContext, DeviceType deviceType) = 0;
	virtual DeviceType GetDeviceType (void) const = 0;
	virtual bool VectorialDraw (void) const { return false; }
	inline void DisableDraw (void) { enableDraw = false; }
	inline void EnableDraw (void) { enableDraw = true; }
	inline bool IsDrawEnabled (void) const { return enableDraw; }
};

}	// namespace TE
// ______________________________ Class DrawableDevice ______________________________

#endif // DRAWABLEDEVICE_HPP
