#ifndef LEARNINGCONTENT_ITOOLTIPVISUALIZER_HPP
#define LEARNINGCONTENT_ITOOLTIPVISUALIZER_HPP

#include <vector>

namespace DG {
class FreeBrowser;
class NativeRect;
class NativePoint;
class Point;
}	 // namespace DG


namespace LearningContent {


struct BorderPoint {
	DG::TPoint<double> position;
	bool			   isArcEndpoint;
	bool			   movesOnExtension;
};


struct TooltipGeometry {
	DG::TRect<double>		 tooltipRect;
	DG::TRect<double>		 contentRect;
	std::vector<BorderPoint> borderPoints;
	bool					 extendsUpwards;
};


struct VisualizerParameters {
	DG::NativeUnit cornerRadius;
	DG::NativeUnit arrowSize;
	Gfx::Color	   arrowColor;
	DG::NativeUnit frameThickness;
	Gfx::Color	   frameColor;

	static VisualizerParameters BalloonStyle ();
	static VisualizerParameters RectangleStyle ();
};

class TooltipNotifyHandler {
public:
	virtual ~TooltipNotifyHandler ();

	virtual void MouseMoveEventHandler (const DG::Point& point) = 0;
	virtual void MouseClickEventHandler (const DG::Point& point) = 0;
	virtual void MouseRClickEventHandler (const DG::Point& point) = 0;
	virtual void MouseUpEventHandler (const DG::Point& point) = 0;
	virtual void MouseRUpEventHandler (const DG::Point& point) = 0;
};

class ITooltipVisualizer {
public:
	ITooltipVisualizer (DG::FreeBrowser&);
	virtual ~ITooltipVisualizer ();

	virtual void SetParameters (const VisualizerParameters&) = 0;
	virtual void SetGeometry (const TooltipGeometry&) = 0;
	virtual void Show () = 0;
	virtual void Extend (double verticalGrowth, double animationDuration = 0.3f) = 0;
	virtual void Hide () = 0;
	virtual bool IsVisible () = 0;

	virtual void RegisterTooltipNotifyHandler (TooltipNotifyHandler* /*handler*/) = 0;

private:
	ITooltipVisualizer ();
};


}	// namespace LearningContent

#endif