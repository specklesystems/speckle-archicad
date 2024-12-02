// *********************************************************************************************************************
// File:			UDLinkText.hpp
//
// Description:		Static text with link behaviour. A temporary solution until a proper link item is implemented in DG.
//					- Can be used and observed like all DG items. The observer has a "link activated" event handler.
//					- The link can be set or cleared dynamically. The basic idea: when you call SetText (), you also
//					  call SetLink () or RemoveLink (), because when you know the text, you also know the link target.
//
// Namespace:		UD
//
// Contact person:
//
// *********************************************************************************************************************


#ifndef UDLINKTEXT_HPP
#define UDLINKTEXT_HPP

#pragma once


#include "DGStaticItem.hpp"
#include "UDDefinitions.hpp"


namespace UD {


class LinkText;


// --- LinkTextActivationEvent -----------------------------------------------------------------------------------------

class UD_DLL_EXPORT LinkTextActivationEvent : public DG::StaticTextClickEvent
{
	friend class LinkText;

public:
	~LinkTextActivationEvent ();

	LinkText*		GetSource (void) const;

protected:
	explicit LinkTextActivationEvent (const DG::StaticTextClickEvent& ev);
};


// --- LinkTextObserver ------------------------------------------------------------------------------------------------

class UD_DLL_EXPORT LinkTextObserver : public DG::StaticTextObserver
{
	friend class LinkText;

protected:
	virtual void	LinkTextActivated (const LinkTextActivationEvent& ev);
};


// --- LinkText --------------------------------------------------------------------------------------------------------

class UD_DLL_EXPORT LinkText : public  DG::StaticText,
							   private DG::StaticTextObserver
{
public:
	LinkText (const DG::Panel& panel, short itemId);

	void			Attach (LinkTextObserver& observer);
	void			Detach (LinkTextObserver& observer);

	void			SetLink (const GS::UniString& linkTarget);
	void			RemoveLink (void);
	bool			IsLink (void) const;
	GS::UniString	GetLinkTarget (void) const;

private:
	virtual void	StaticTextMouseMoved (const DG::StaticTextMouseMoveEvent& ev, bool* noDefaultCursor) override;
	virtual void	StaticTextClicked (const DG::StaticTextClickEvent& ev) override;

	bool			mIsLink;
	GS::UniString	mLinkTarget;
};


}	// namespace UD


#endif
