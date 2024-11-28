#if !defined GS_VI_OVERRIDDENFILLOPACITYDEBUG_HPP
#define	GS_VI_OVERRIDDENFILLOPACITYDEBUG_HPP


#include "VectorImageExport.h"
#include "EventSource.hpp"
#include "EventObserver.hpp"


namespace VI {

class VI_DLL_CLASS_EXPORT OpacityValueObserver : public GS::EventObserver
{
public:
	OpacityValueObserver ();
	virtual ~OpacityValueObserver ();
	virtual void OpacityChanged (const double newValue) = 0;
	virtual void EnableChanged (const bool newValue) = 0;
};


class VI_DLL_CLASS_EXPORT OverriddenFillOpacityDebug : public GS::EventSource {
public:
	OverriddenFillOpacityDebug (const OverriddenFillOpacityDebug&) = delete;
	OverriddenFillOpacityDebug& operator= (const OverriddenFillOpacityDebug&) = delete;

	static OverriddenFillOpacityDebug& GetInstance ();

	bool   IsEnabled () const;
	double GetOpacity () const;

	GS::Optional<double> GetOverriddenOpacity () const;

	void SetEnabled (const bool enable);
	void SetOpacity (const double newValue);

	void Attach (OpacityValueObserver& observer);

	virtual ~OverriddenFillOpacityDebug ();

private:
	OverriddenFillOpacityDebug ();

	bool   isEnabled;
	double opacity;
};


} // namespace VI


#endif
