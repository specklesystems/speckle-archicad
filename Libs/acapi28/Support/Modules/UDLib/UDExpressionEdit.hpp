#ifndef UDEXPRESSIONEDITCONTROL_HPP
#define UDEXPRESSIONEDITCONTROL_HPP
#pragma once

#include "HashTable.hpp"
#include "SkipMap.hpp"

#include "DGPanel.hpp"
#include "DGUniRichEdit.hpp"
#include "UDDefinitions.hpp"
#include "UDItemInfoTag.hpp"
#include "IConvertOnCP.hpp"
#include "Font.hpp"
#include "DGMenu.hpp"
#include "CharStyle.hpp"

namespace UD {
	class ItemInfoTagContentCreator;
namespace ExpressionEdit {


class UD_DLL_EXPORT ProtectedText {
public:
	using IndexRange			 = GS::Range<UIndex>;
	using RawTextType			 = GS::UniString;
	using FullyQualifiedTextType = GS::UniString;

	struct RangeComparatorForDescendingOrder {
		static bool IsEqual (const IndexRange& lhs, const IndexRange& rhs)		{ return lhs == rhs; }
		static bool IsLess (const IndexRange& lhs, const IndexRange& rhs)		{ return lhs.GetMin () > rhs.GetMin ();	}
	};

	using ProtectedRangeSet = GS::SkipMap<IndexRange, GS::Pair<RawTextType, FullyQualifiedTextType>, RangeComparatorForDescendingOrder>;

public:
	ProtectedText () = default;
	explicit ProtectedText (const GS::UniString& uiText);
	ProtectedText (const GS::UniString& uiText, const GS::Optional<GS::Pair<RawTextType, FullyQualifiedTextType>>& maybeRawText);
	ProtectedText (const GS::UniString& uiText, const ProtectedRangeSet& protectedRanges);
	
	bool				operator== (const ProtectedText& rhs) const;
	bool				operator!= (const ProtectedText& rhs) const;

	GS::UniString		   GetUIText () const;
	RawTextType			   GetRawText () const;
	FullyQualifiedTextType GetFullyQualifiedText () const;

	UIndex				RawTextIndexToUITextIndex (UIndex rawTextIndex) const;

	ProtectedText		GetRange (const IndexRange& uiTextRange) const;
	void				ReplaceRange (const IndexRange& uiTextRange, const ProtectedText& newProtectedText);

	ProtectedRangeSet	GetProtectedRanges () const;
	void				EnumerateSubStrings (std::function<void (const GS::UniString& uiText, const GS::Optional<GS::Pair<RawTextType, FullyQualifiedTextType>>& maybeRawText)> EnumeratorFn) const;
private:
	IndexRange			ClampToLength (const IndexRange& indexRange) const;
	IndexRange			ExtendWithOverlappingProtectedRanges (const IndexRange& indexRange) const;

	static IndexRange	OffsetIndexRange (const IndexRange& indexRange, Int32 offset);

	bool				HasZeroLengthRange () const;
	bool				HasOverlaps () const;

private:
	RawTextType				uiText;
	ProtectedRangeSet		protectedRanges;
};


class UD_DLL_EXPORT ProtectedTextProvider {
public:
	virtual ~ProtectedTextProvider ();

	virtual ProtectedText GetProtectedText (const GS::UniString& rawText) const = 0;
};


namespace InfoTag {

class UD_DLL_EXPORT InfoTagContentCreatorFactory {
public:
	virtual ~InfoTagContentCreatorFactory ();

	virtual GS::Array<ProtectedText::IndexRange>		GetRangesWithInfoTag (const ProtectedText::RawTextType& rawText, GS::Ref<ProtectedTextProvider> protectedTextProvider) = 0;
	virtual GS::Ref<ItemInfoTag::InfoTagContentCreator> CreateContentCreator (const ProtectedText& protectedText, ProtectedText::IndexRange range) = 0;
};


class UD_DLL_EXPORT DefaultInfoTagContentCreatorFactory : public InfoTagContentCreatorFactory {
public:
	virtual GS::Array<ProtectedText::IndexRange>		GetRangesWithInfoTag (const ProtectedText::RawTextType& rawText, GS::Ref<ProtectedTextProvider> protectedTextProvider) override;
	virtual GS::Ref<ItemInfoTag::InfoTagContentCreator> CreateContentCreator (const ProtectedText& protectedText, ProtectedText::IndexRange range) override;
};

}

class EditControlDecorator;
class EditControlContentObserver;

class UD_DLL_EXPORT EditControl :	public DG::UniRichEdit,
									public DG::PanelObserver,
									public DG::UniRichEditObserver,
									public DG::MenuObserver,
									public DG::IConvertOnCopyPaste
{
	friend class EditControlDecorator;
private:
	class UD_DLL_EXPORT AutoTextData {
	public:
		AutoTextData (const GS::UniString& rawText, const GS::UniString& fullyQualifiedText);
		virtual ~AutoTextData ();

		const GS::UniString& GetRawText () const;
		const GS::UniString& GetFullyQualifiedText () const;
		short GetIndex () const;

		bool operator== (const AutoTextData& other) const;
		bool operator!= (const AutoTextData& other) const;
	private:
		GS::UniString	rawText;
		GS::UniString	fullyQualifiedText;
		short			index;
	};
public:
	enum class TextFormat {
		UIText, RawText, FullyQualifiedText
	};
public:
	EditControl (DG::Dialog& dialog, short item,
				 GS::Ref<ProtectedTextProvider> protectedTextProvider,
				 GS::Ref<ItemInfoTag::SettingsProvider> infoTagSettingsProvider = new ItemInfoTag::SettingsProvider (ItemInfoTag::RegistryBasedSettingsOptions ()),
				 GS::Ref<InfoTag::InfoTagContentCreatorFactory> infoTagContentCreatorFactory = new InfoTag::DefaultInfoTagContentCreatorFactory ());
	virtual ~EditControl ();

	///DG::PanelObserver///////////////////////////////////////////////////////////////////////////////
	virtual void			PanelHotkeyPressed (const DG::PanelHotKeyEvent& ev, bool* processed) override;
	virtual void			PanelIdle (const DG::PanelIdleEvent& ev) override;

	///DG::UniRichEditObserver/////////////////////////////////////////////////////////////////////////
	virtual void			ItemContextMenuRequested (const DG::ItemContextMenuEvent& ev, bool* needHelp, bool* processed) override;
	virtual short			UniRichEditContentChanged (const DG::UniRichEditContentEvent& ev) override;
	virtual short			UniRichEditSelectionChanged (const DG::UniRichEditSelectionEvent& ev) override;

	virtual void			UniRichEditDragStarting (const DG::UniRichEditDragSourceEvent& ev, bool* canStart) override;

	///DG::MenuObserver////////////////////////////////////////////////////////////////////////////////
	virtual void			MenuTrackEntered () override;
	virtual void			MenuTrackExited () override;

	virtual double			GetSizeOnCopy (double size) override;
	virtual Gfx::Color		GetPenColorOnCopy (const Gfx::Color& color) override;
	virtual double			GetSizeOnPaste (double size) override;
	virtual Gfx::Color		GetPenColorOnPaste (const Gfx::Color& color) override;
	virtual TE::IFont&		GetBitmapFontReplacementOnPaste (void) override;
	virtual GS::UniString*	GetGroupIDOnPaste (GS::UniString* /*oldPtr*/) override;

	virtual bool			OnCutCopy () override;
	virtual bool			OnPaste () override;

	void					SetContentCreatorFactory (GS::Ref<InfoTag::InfoTagContentCreatorFactory> infoTagContentCreatorFactory);

	void					CatText (const GS::UniString& text);
	void					SetText (const GS::UniString& text);
	void					SetTextRange (const DG::CharRange& charRange, const GS::UniString& text);

	void					InsertText (const GS::UniString& rawText);

	GS::UniString			GetText (TextFormat textFormat = TextFormat::UIText) const;
	GS::UniString			GetTextRange (const DG::CharRange& charRange, TextFormat textFormat = TextFormat::UIText) const;
	ProtectedText			GetProtectedText (const GS::Optional<DG::CharRange>& maybeCharRange = GS::NoValue) const;

	void					Attach (EditControlContentObserver& observer);
	void					Detach (EditControlContentObserver& observer);

	DG::Point				GetPositionForHelp () const;

private:
	static ProtectedText::IndexRange	DGCharRangeToIndexRange (const DG::CharRange& charRange);

	void					UpdateProtectedTextWithNotification (std::function<void (ProtectedText&)> ModifyProtectedText);

	void					InsertTextInternal (const GS::UniString& uiText, const GS::Optional<GS::Pair<ProtectedText::RawTextType, ProtectedText::FullyQualifiedTextType>>& rawText/* = GS::NoValue*/);
	void					Protect (const GS::Pair<GS::UniString, GS::UniString>& rawText, const DG::CharRange& range);

	ProtectedText			RichEditContentToProtectedText () const;
	void					UpdateProtectedText ();
	void					UpdateInfoTagRanges ();

private:
	DG::Dialog&										dialogIn;
	GS::Ref<ProtectedTextProvider>					protectedTextProvider;
	GS::Ref<UD::ItemInfoTag::ItemDecorator>			decorator;
	GS::Ref<InfoTag::InfoTagContentCreatorFactory>	infoTagContentCreatorFactory;

	DG::CharRange									selection;
	ProtectedText									protectedText;
	GS::Array<ProtectedText::IndexRange>			rangesWithInfoTag;

	GS::Array<GS::Ref<AutoTextData>>				userDataArray;

	TE::Font										textFont;
	TE::CharStyle									defaultCharStyle;

	short											selectAllHotKey;
	short											undoHotKey;
#ifdef WINDOWS
	short											redoHotKey;
#endif

	GS::Ref<DG::Point>								clickedPointForContextMenu;
};


typedef GS::Ref<EditControl>	EditControlPtr;


class UD_DLL_EXPORT EditControlContentObserver: public DG::ItemObserver {
protected:
	friend class EditControl;

	virtual void	RawTextChanged (const EditControl& source);

public:
	virtual ~EditControlContentObserver ();
};

} //ExpressionEdit
} //UD

#endif //UDEXPRESSIONEDITCONTROL_HPP
