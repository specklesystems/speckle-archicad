#ifndef LEARNINGCONTENT_TOOLTIP_HPP
#define LEARNINGCONTENT_TOOLTIP_HPP

#include "TransparentWindowLibDefinitions.hpp"

#include "ILearningTooltipController.hpp"
#include "ITooltipVisualizer.hpp"
#include "DGUtility.hpp"

#include "DGBrowser.hpp"

namespace LearningContent {

class TRANSPARENTWINDOWLIB_DLL_EXPORT Tooltip {
public:
	Tooltip ();
	Tooltip (const Tooltip&) = delete;
	Tooltip& operator= (const Tooltip&) = delete;
	virtual ~Tooltip ();

	void Show ();
	void ShowItemInfo ();
	void Extend ();
	void Hide ();
	void ResetStates ();

	bool IsExtended () const;
	bool IsHiding () const;
	bool IsFallbackType () const;

	GS::Optional<DG::NativeRect> GetTooltipRect () const;

	void SetParameters (const TooltipParameters&);
	void RegisterTooltipNotifyHandler (TooltipNotifyHandler* handler);

private:
	TooltipParameters				params;
	DG::FreeBrowser					browser;
	ITooltipVisualizer* const		visualizer;
	GS::Optional<DG::TRect<double>> tooltipRect;

	bool   isExtended;
	bool   isFallbackType;
	bool   isHiding;
	bool   extendedExist;
	double deltaExtendedHeight;
	bool   extendsUpwards;

	void CommunicationInterfaceRegistration ();
	void SendShowRequestToJavaScript (GS::UniString tooltipType);
	void SetGeometry (GS::Ref<JS::Base> args, const VisualizerParameters& visualSetups, bool isFallbackType);
	void LearnMore (GS::Ref<JS::Base> args);
	void Open ();
	void Close ();
	GS::Ref<JS::Base> GetCMSHostUrl () const;
};

}	// namespace LearningContent

#endif
