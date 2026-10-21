#pragma once

#ifndef UDRADIOANDTEXT_HPP
#define UDRADIOANDTEXT_HPP

#include "UDDefinitions.hpp"
#include "DGModule.hpp"


namespace UD {

class RadioAndText;
class RadioGroup;


class UD_DLL_EXPORT RadioAndTextObserver: public GS::EventObserver
{
friend class RadioAndText;

private:
	virtual void RadioChanged (const RadioAndText* source);
};


class UD_DLL_EXPORT RadioAndText:	public GS::EventSource,
									private DG::RadioItemObserver,
									private DG::StaticTextObserver
{
public:
	RadioAndText (RadioGroup& group, const DG::Panel& panel, short radioItem, short textItem);

	void Attach (RadioAndTextObserver& observer);

	void Disable ();
	void SetStatus (bool enable);
	bool IsEnabled () const;

	void SetIcon (const DG::Icon& icon);

	void Select ();
	bool IsSelected () const;

private:
	virtual void OnSelect () {}
	virtual void OnDeselect () {}

	virtual void RadioItemChanged (const DG::RadioItemChangeEvent&) override;
	virtual void StaticTextClicked (const DG::StaticTextClickEvent&) override;

	void Notify ();

	RadioGroup&			group;
	DG::IconPushRadio	radio;
	DG::CenterText		text;
};


class UD_DLL_EXPORT RadioGroup
{
	friend class RadioAndText;

public:
	bool HasMember (const RadioAndText* item) const;

private:
	GS::Array<RadioAndText*> members;
};

}

#endif