#ifndef UDSEARCHFIELD_HPP
#define UDSEARCHFIELD_HPP

#pragma once

#include "DGEditControl.hpp"
#include "UDDefinitions.hpp"


namespace UD {

class UD_DLL_EXPORT TextEditWithHintText :	public DG::TextEdit,
											public DG::TextEditBaseObserver
{
public:
	TextEditWithHintText (const DG::Panel& panel, short item, const GS::UniString& textForEmptyNotFocusedField);

	virtual void	ItemFocusLost (const DG::ItemFocusEvent& ev) override;

	void			SetText (const GS::UniString& text);
	void			Clear (void);
};

}

#endif //UDSEARCHFIELD_HPP
