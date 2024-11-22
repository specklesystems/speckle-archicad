#ifndef	GS_COMMONUI_MULTIPLECHOICEDATA_HPP
#define	GS_COMMONUI_MULTIPLECHOICEDATA_HPP


#include "UDDefinitions.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"
#include "UniString.hpp"
#include "Any.hpp"


namespace UD {
	class MultipleChoiceDataObserver;
}


namespace UD {


class UD_DLL_EXPORT MultipleChoiceItem {
public:
	explicit MultipleChoiceItem ();
	explicit MultipleChoiceItem (const GS::UniString& inText, bool inIsSelected, bool inIsEnabled = true, bool inIsGroup = false);

	bool					IsSelected () const;
	void					SetSelected (bool inIsSelected);

	const GS::UniString&	GetText	() const;
	void					SetText (const GS::UniString& inText);

	bool					IsEnabled () const;
	void					Enable ();
	void					Disable ();

	bool					IsGroup () const;
	void					SetIsGroup (const bool inIsGroup);

	const GS::Any&			GetCustomData () const;
	void					SetCustomData (const GS::Any& inCustomData);

private:
	bool			isEnabled;
	bool			isSelected;
	GS::UniString	text;
	bool			isGroup;
	GS::Any			customData;
};


class UD_DLL_EXPORT MultipleChoiceData : public GS::EventSource
{
public:
	enum class SelectionMode {
		MultiSelection,
		SingleSelectionInGroup
	};

	explicit MultipleChoiceData ();
	explicit MultipleChoiceData (const SelectionMode inSelectionMode);
	virtual ~MultipleChoiceData ();

	void	Attach (MultipleChoiceDataObserver& observer);
	void	Detach (MultipleChoiceDataObserver& observer);

	const GS::Array<MultipleChoiceItem>& GetItems (void) const;

	void	Clear (void);
	void	AddItem (const MultipleChoiceItem& item);
	void	SetItemSelected (UIndex itemIndex, bool inIsSelected);

private:
	GS::HashSet<UIndex> GetSelectedSiblingIndices (const UIndex itemIndex) const;
	GS::Optional<UIndex> GetParentGroupItemIndex (const UIndex itemIndex) const;

	const SelectionMode selectionMode;
	GS::Array<MultipleChoiceItem> items;
};


class UD_DLL_EXPORT MultipleChoiceDataObserver : public GS::EventObserver
{
protected:
	friend class MultipleChoiceData;

	virtual void SelectionChanged (const MultipleChoiceData& source);

public:
	virtual ~MultipleChoiceDataObserver ();
};


class UD_DLL_EXPORT MultipleChoiceDataChanges : public MultipleChoiceDataObserver
{
private:
	bool	isSelectionChanged;

	virtual void	SelectionChanged (const MultipleChoiceData& source) override;

public:
	MultipleChoiceDataChanges (MultipleChoiceData& multipleChoicePopUpDialog);

	bool			IsSelectionChanged (void) const;
};

} // namespace UD


#endif