#ifndef D2DRAWABLEDEVICE_HPP
#define D2DRAWABLEDEVICE_HPP


#include "D2DHeaders.hpp"
#include "DrawableDevice.hpp"

#include "Color.hpp"
#include "Rect.hpp"

#include <unordered_map>

template <>
struct TE_DLL_EXPORT std::hash<Gfx::Color> {
	std::size_t operator()(const Gfx::Color& color) const;
};

namespace TE {


class TE_DLL_EXPORT D2DrawableDeviceContext {
	ID2D1RenderTarget* renderTarget;
	std::unordered_map<Gfx::Color, ID2D1SolidColorBrush*>* brushes;

	ID2D1Layer* clipLayer = nullptr;
	ID2D1Geometry* clipPolygon = nullptr;
	GS::Rect<float> visibleRect;

	D2D1_ANTIALIAS_MODE GetAntialiasMode ();
public:
	D2DrawableDeviceContext (ID2D1RenderTarget* renderTarget, std::unordered_map<Gfx::Color, ID2D1SolidColorBrush*>* brushes, ID2D1Layer* clipLayer, ID2D1Geometry* clipPolygon, GS::Rect<float> visibleRect);
	ID2D1SolidColorBrush* GetOrCreateBrushForColor (const Gfx::Color& color);
	ID2D1RenderTarget* GetRenderTarget ();

	void SetTransform (const D2D1_MATRIX_3X2_F& transform);
	void DrawGlyphRun (D2D1_POINT_2F baselineOrigin,
					   const DWRITE_GLYPH_RUN* glyphRun,
					   ID2D1Brush* foregroundBrush,
					   DWRITE_MEASURING_MODE measuringMode = DWRITE_MEASURING_MODE_NATURAL);
	void FillRectangle (const D2D1_RECT_F& rect, ID2D1Brush* brush);

	D2D1_MATRIX_3X2_F GetTransform ();
	float GetPixelsPerDip ();

	GS::Rect<float> GetVisibleRect ();

	void ApplyVisibleRectClipping (const D2D1::Matrix3x2F& visibleRectTransform);
	void RemoveVisibleRectClipping ();

	void ApplyPolygonClipping (const D2D1::Matrix3x2F& clipTransform);
	void RemovePolygonClipping ();

	void BeginDraw ();
	HRESULT EndDraw ();
	HRESULT Flush ();

	void SetAntialiasMode (D2D1_ANTIALIAS_MODE antialiasMode);
	void ActualizeAntialiasMode ();
};

class TE_DLL_EXPORT D2DrawableDevice : public DrawableDevice {
private:
	static const DrawableDevice::DeviceType DEVICE_TYPE = DrawableDevice::DeviceType::dtD2D;
	D2DrawableDeviceContext deviceContext;

	Gfx::Color plainTextColor;
public:
	D2DrawableDevice (D2DrawableDeviceContext deviceContext);

	void SetDrawContext (void* drawContext, DeviceType deviceType = DEVICE_TYPE) override;
	void SetDrawContext (D2DrawableDeviceContext context);
	DeviceType GetDeviceType (void) const override;
	virtual bool VectorialDraw (void) const;
	const Gfx::Color& GetPlainTextColor () const;
	void SetPlainTextColor (const Gfx::Color& color);
	void EnableAntialias ();
	void DisableAntialias ();

	D2DrawableDeviceContext GetDeviceContext () const;
	ID2D1RenderTarget* GetRenderTarget ();
};	//-----------------------------CLASS D2DWARABLEDEVICE END------------------------------

}	//-------------------------------NAMESPACE TE END--------------------------------------

#endif // D2DRAWABLEDEVICE_HPP