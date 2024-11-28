#ifndef GS_FLOATINGWINDOW_HIGHGLIGHTINFO_HPP
#define GS_FLOATINGWINDOW_HIGHGLIGHTINFO_HPP
#pragma once

#include "Optional.hpp"

#include "TransparentWindowLibDefinitions.hpp"

namespace FloatingWindow {

class TRANSPARENTWINDOWLIB_DLL_EXPORT ItemHighlightInfo {
public:
	ItemHighlightInfo (const DG::Rect&			highlightRect,
					   Int16					highlightedRowIndex,
					   Int16					highlightedColumnIndex,
					   bool						isLastRow,
					   bool						isLastColumn,
					   GS::Optional<DG::Point>	mousePosition = GS::NoValue);

	virtual ~ItemHighlightInfo ();

	const DG::Rect& GetRect () const;

	Int16 GetHighlightedRowIndex () const;
	Int16 GetHighlightedColumnIndex () const;

	bool IsLastRow () const;
	bool IsLastColumn () const;

	GS::Optional<DG::Point> GetMousePosition () const;

private:
	DG::Rect	highlightRect;
	Int16		highlightedRowIndex;
	Int16		highlightedColumnIndex;
	bool		isLastRow;
	bool		isLastColumn;
	GS::Optional<DG::Point>	mousePosition;
};

}

#endif
