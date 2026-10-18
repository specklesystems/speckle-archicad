#ifndef	GS_COMMONUI_MULTIPLECHOICELISTBOX_HPP
#define	GS_COMMONUI_MULTIPLECHOICELISTBOX_HPP


#include "UDDefinitions.hpp"
#include "DGListBox.hpp"
#include "MultipleChoiceData.hpp"


namespace UD {


class UD_DLL_EXPORT MultipleChoiceListBox : public DG::ListBoxObserver,
											public MultipleChoiceDataObserver
{
private:
	enum {
		IconColumn	= 1,
		TextColumn	= 2
	};

	DG::MultiSelListBox	multiSelListBox;
	MultipleChoiceData&	multipleChoiceData;

	void	InitializeListBox (void);
	void	FillListBox (void);

	virtual void	ListBoxClicked (const DG::ListBoxClickEvent& ev) override;

	virtual void	SelectionChanged (const MultipleChoiceData& source) override;

public:
	MultipleChoiceListBox (const DG::Panel& panel, short item, MultipleChoiceData& multipleChoiceData);

	short	GetItemCount (void) const;

	short	GetRequiredWidth (void) const;
	short	GetRequiredHeight (void) const;

	void	SetWidth (short width);
	void	SetHeight (short height);

	void	Hide (void);
	void	Resize (short hGrow, short vGrow);

	void	UpdateColumnsSize (void);
};


} // namespace UD


#endif