#ifndef UDITEMINFOTAGCONTENTCREATOR_HPP
#define UDITEMINFOTAGCONTENTCREATOR_HPP

#pragma once

#include "UDDefinitions.hpp"
#include "FloatingMenu.hpp"

namespace UD {
namespace ItemInfoTag {

class UD_DLL_EXPORT InfoTagContentCreator
{
public:
	enum class EntryLayoutMethod {
		OneColumn,
		TwoColumns
	};
	class UD_DLL_EXPORT InfoTagItem : public FloatingWindow::FloatingMenuItem {
	public:
		InfoTagItem ();

		virtual ~InfoTagItem ();

	};

	typedef FloatingWindow::FloatingMenu::MenuItemRowArray MenuItemRowArray;
protected:
	class UD_DLL_EXPORT ContentEntryCreator
	{
	public:
		virtual ~ContentEntryCreator ();

		virtual MenuItemRowArray GetContent () const = 0;
	protected:
		MenuItemRowArray CreateMenuItemEntry (const GS::UniString& contentType,
											  const GS::UniString& text,
											  const DG::Font::Style style = DG::Font::Plain,
											  GS::Ref<Gfx::Color> color = nullptr,
											  EntryLayoutMethod layoutMethod = EntryLayoutMethod::OneColumn) const;
	};

private:
	GS::Array<GS::Ref<ContentEntryCreator>> entryCreators;

protected:
	void AddContentEntryCreator (GS::Ref<ContentEntryCreator> rowCreator);

public:
	MenuItemRowArray GetContent () const;

	virtual ~InfoTagContentCreator ();
};

}
}

#endif //UDITEMINFOTAGCONTENTCREATOR_HPP
