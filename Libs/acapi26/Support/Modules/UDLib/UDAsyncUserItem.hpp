// *****************************************************************************
// File:			UDAsyncUserItem.hpp
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef ASYNCUSERITEM_HPP
#define ASYNCUSERITEM_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Object.hpp"
#include "Ref.hpp"
#include "DGUserItem.hpp"
#include "UDDefinitions.hpp"

namespace NewDisplay {
	class NativeContext;
}


namespace UD {

class UD_DLL_EXPORT AsyncUserItemObserver: public GS::EventObserver
{
public:
	virtual ~AsyncUserItemObserver ();

	virtual void GetUpdate (NewDisplay::NativeContext& context, bool first) = 0;
};


class UD_DLL_EXPORT AsyncUserItem: public DG::UserItem
{
	class Impl;
	GS::Ref<Impl> impl;

public:
	AsyncUserItem (DG::Panel& panel, short item);
	AsyncUserItem (DG::Panel& panel, const DG::Rect& rect);
	virtual ~AsyncUserItem ();

	void Start ();
	void Stop ();
	bool IsRunning () const;

	void Attach (AsyncUserItemObserver& observer);
	void Detach (AsyncUserItemObserver& observer);
};

}

#endif
