
// *****************************************************************************
//
//                                InterFace WinDrawableDevice
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined WINDRAWABLEDEVICE_HPP
#define WINDRAWABLEDEVICE_HPP

// --------------------------------- Includes ----------------------------------

#ifdef WINDOWS
#include "Win32GDIPlusInterface.hpp"
#endif

#include "DrawableDevice.hpp"
#include "Color.hpp"

// ============================== Class WinDrawableDevice ==============================

namespace TE {

class TE_DLL_EXPORT WinDrawableDevice : public DrawableDevice {

#ifdef WINDOWS

		private:
			HDC						hdc = nullptr;
			DeviceType				devType;
			Int32*					gdiplus_Graphics = nullptr;
			UINT					savedAlign = 0;
			Gfx::Color				plainTextColor;
			Gfx::Color				backGroundColor;

		public:
			WinDrawableDevice (void* drawContext, DeviceType deviceType = dtGDI32);
			WinDrawableDevice (void* hdc, void* graphics, DeviceType deviceType = dtGDI32);

			~WinDrawableDevice (void);

			inline HDC	GetDC (void) const { return hdc; }
			inline void*	GetGdipContext (void) const { return reinterpret_cast <void*> (gdiplus_Graphics); }

			void	SetDrawContext (void* drawContext, DeviceType deviceType = dtGDI32) override;
			virtual DeviceType GetDeviceType (void) const  override { return devType; }

			void			SetPlainTextColor (const Gfx::Color& color) { plainTextColor = color; }
			void			SetBackGroundColor (const Gfx::Color& color) { backGroundColor = color; }

			Gfx::Color		GetPlainTextColor () const { return plainTextColor; }
			Gfx::Color		GetBackGroundColor () const { return backGroundColor; }
#endif

};


}	// namespace TE
// ______________________________ Class WinDrawableDevice ______________________________


#endif
