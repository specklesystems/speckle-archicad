
#ifndef LEARNINGCONTENT_TOOLTIPCONTROLLER_HPP
#define LEARNINGCONTENT_TOOLTIPCONTROLLER_HPP

#include "TransparentWindowLibDefinitions.hpp"
#include "ILearningTooltipController.hpp"
#include "Tooltip.hpp"
#include "Optional.hpp"

namespace LearningContent {

enum class TooltipState { Quick, Extended, Hide };

class TRANSPARENTWINDOWLIB_DLL_EXPORT TooltipController : public ITooltipController, TooltipNotifyHandler {
	friend class TooltipHandlerTask;

public:
	TooltipController ();
	virtual ~TooltipController ();

	virtual void RequestTooltip (const TooltipParameters&) override;
	virtual void HideTooltip (bool forceHide = false) override;
	virtual void RefreshStatus () override;

private:
	void ShowQuickTooltip ();
	void ExtendTooltip ();
	void HideTooltipDelayed ();

	bool IsMouseOverRefRect ();
	bool IsMouseOverTooltip ();

	void GetRegistryValues ();

	virtual void MouseMoveEventHandler (const DG::Point& point) override;
	virtual void MouseClickEventHandler (const DG::Point& point) override;
	virtual void MouseRClickEventHandler (const DG::Point& point) override;
	virtual void MouseUpEventHandler (const DG::Point& point) override;
	virtual void MouseRUpEventHandler (const DG::Point& point) override;

	void   StartTimer (GSTimer& timer);
	void   StopTimer (GSTimer& timer);
	double GetTimerValue (GSTimer& timer) const;
	bool   HasQuickTimerElapsed ();
	bool   HasExtendedTimerElapsed ();
	bool   HasHideTimerElapsed ();
	void   StartState (TooltipState stateType);
	void   ResetState ();


	Tooltip*							tooltip;
	TooltipParameters					params;
	GS::Optional<TooltipParameters> 	paramsCache;
	bool								needToShowQuickTooltip;
	bool								needToShowExtendedTooltip;
	bool								needToHideDelayed;
	GSTimer								quickTimer;
	GSTimer								extendTimer;
	GSTimer								hideTimer;
	Int32								quickTooltipDelayTime;
	Int32								extendedTooltipDelayTime;
};


TRANSPARENTWINDOWLIB_DLL_EXPORT void SetMetaInfoMode (bool enabled);

TRANSPARENTWINDOWLIB_DLL_EXPORT bool IsInMetaInfoMode ();

TRANSPARENTWINDOWLIB_DLL_EXPORT bool IsMetaInfoModeMenuEnabled ();

TRANSPARENTWINDOWLIB_DLL_EXPORT void LogTooltipMenuStates ();

}	// namespace LearningContent

#endif
