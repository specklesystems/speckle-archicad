// *****************************************************************************
//
// Contact person: Antlia squad
//
// *****************************************************************************

#ifndef GS_UD_IMPROVEDSEARCHEDIT_HPP
#define GS_UD_IMPROVEDSEARCHEDIT_HPP

#include "UDDefinitions.hpp"

// from DG
#include "DGEditControl.hpp"


namespace UD {

using ImprovedSearchEditChangeEvent = DG::SearchEditChangeEvent;
using ImprovedSearchEditObserver	= DG::SearchEditObserver;


/* ================================================================================================================== */


class UD_DLL_EXPORT ImprovedSearchEdit : public DG::SearchEdit, public DG::ItemObserver {
public:

	ImprovedSearchEdit (const DG::Panel&, short item, GS::UniString hintText);
	ImprovedSearchEdit (const DG::Panel&, const DG::Rect&, GS::UniString hintText);

	void	Attach (ImprovedSearchEditObserver&);
	void	Detach (ImprovedSearchEditObserver&);

	bool	IsEmpty (void) const;
	void	Clear (void);

	void	SetFocusWithSelection (bool selectEnd = false);

	void	SetHintText (const GS::UniString&);

	void	SetToolTipText (GS::UniString);
	void	ResetToolTipText (void);

private:

// DG::ItemObserver implementation

	void	ItemToolTipRequested (const DG::ItemHelpEvent&, GS::UniString*) override final;
	void	ItemFocusLost (const DG::ItemFocusEvent& ev) override;

private:

	GS::UniString	mToolTipText;
	bool			mFocusInited;
};


} // namespace UD


#endif /* GS_UD_IMPROVEDSEARCHEDIT_HPP */
