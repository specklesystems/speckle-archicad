
// *****************************************************************************
//
//                                InterFace MacDrawableDevice
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined MACDRAWABLEDEVICE_HPP
#define MACDRAWABLEDEVICE_HPP


// --------------------------------- Includes ----------------------------------

#ifdef macintosh
#include <ApplicationServices/ApplicationServices.h>
#endif

#include "DrawableDevice.hpp"

// ============================== Class MacDrawableDevice ==============================

namespace TE {


class TE_DLL_EXPORT MacDrawableDevice : public DrawableDevice  {
#ifdef macintosh
		private:
			CGContextRef	cgContext;
			DeviceType		devType;

		public:
			MacDrawableDevice (void* drawContext, DeviceType deviceType = dtQuartz);
			~MacDrawableDevice (void);

			inline CGContextRef	GetCGContext (void) const { return cgContext; }
			inline DeviceType GetDeviceType (void) const { return devType; }
			void SetDrawContext (void* drawContext, DeviceType deviceType = dtQuartz);
#endif
};

}	// namespace TE
// ______________________________ Class MacDrawableDevice ______________________________

#endif
