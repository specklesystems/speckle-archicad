// *****************************************************************************
// File:			DGFontFavorites.hpp
//
// Description:		Favorite font for text editing
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BL
//
// SG compatible
// *****************************************************************************

#ifndef DGFONTFAVORITES_HPP
#define DGFONTFAVORITES_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSPref.hpp"
#include "Font.hpp"
#include "EventObserver.hpp"
#include "EventSource.hpp"


namespace DG {
	class FontFavorites;
}

namespace DG {

// --- Class declarations ------------------------------------------------------


// ============================== Class FontFavoritesObserver =============================


class FontFavoritesObserver : public GS::EventObserver {

protected:
	FontFavoritesObserver () {}
   ~FontFavoritesObserver () {}

public:
	virtual void FontFavoritesChanged (void);
};


// ================================== Class FontFavorites =================================

class FontFavorites : private GS::EventSource {

#define MAX_FONTFAVORITES_COUNT 5

private:
	GS::Array<TE::FontFamily>		fontFamilies;
	GS::Array<GSTime>				selectionTimes;

	bool IsFontInFavorites (const TE::FontFamily& fontFamily, UIndex* itemIndex = nullptr)
	{
		if (itemIndex != nullptr)
			*itemIndex = 0;
		for (UIndex i = 0; i < fontFamilies.GetSize (); ++i) {
#if defined (macintosh)
			if (fontFamilies [i].GetFamilyGroupName () == fontFamily.GetFamilyGroupName ()) {
				if (itemIndex != nullptr)
					*itemIndex = i;
				return true;
			}
#else
			if (fontFamilies [i] == fontFamily) {
				if (itemIndex != nullptr)
					*itemIndex = i;
				return true;
			}
#endif
		}
		return false;
	}

	void SendFontFavoritesChanged (void) const
	{
		for (ObserverEnumerator oe = EnumerateObservers (); oe != nullptr; ++oe)
			static_cast<FontFavoritesObserver&> (*oe).FontFavoritesChanged ();
	}

public:

	FontFavorites () {}

	FontFavorites (const DG::FontFavorites& source):
		fontFamilies (source.fontFamilies),
		selectionTimes (source.selectionTimes)
		{ }

	virtual		~FontFavorites ();

	FontFavorites& operator= (const DG::FontFavorites& source)
	{
		fontFamilies = source.fontFamilies;
		selectionTimes = source.selectionTimes;
		return *this;
	}

	bool AddFontToFavorites (const TE::FontFamily& fontFamily)
	{
		UIndex itemIndex = 0;
		if (IsFontInFavorites (fontFamily, &itemIndex)) {
			if (itemIndex == 0) {
				selectionTimes [itemIndex] = TIGetTime ();
				return false;
			}
			fontFamilies.Delete (itemIndex);
			selectionTimes.Delete (itemIndex);
			fontFamilies.Insert (0, fontFamily);
			selectionTimes.Insert (0, TIGetTime ());
			SendFontFavoritesChanged ();
			return true;
		}

		if (fontFamilies.GetSize () < MAX_FONTFAVORITES_COUNT) {
			fontFamilies.Insert (0, fontFamily);
			selectionTimes.Insert (0, TIGetTime ());
			SendFontFavoritesChanged ();
			return true;
		}

		fontFamilies.Delete (MAX_FONTFAVORITES_COUNT - 1);
		selectionTimes.Delete (MAX_FONTFAVORITES_COUNT - 1);
		fontFamilies.Insert (0, fontFamily);
		selectionTimes.Insert (0, TIGetTime ());
		SendFontFavoritesChanged ();
		return true;
	}

	const GS::Array<TE::FontFamily>& GetFavorites (void) { return fontFamilies; }

	void Attach (FontFavoritesObserver& observer)
	{
		if (DBERROR (&observer == nullptr))
			return;

		EventSource::Attach (observer);
	}

	void Detach (FontFavoritesObserver& observer)
	{
		if (DBERROR (&observer == nullptr))
			return;

		EventSource::Detach (observer);
	}

	void WriteToPrefs (void)
	{
		char favoriteNameId [128];
		char favoriteEncodingId [128];
		char favoriteTimeId [128];
		GSPref::FixPathSession	session ("FontFavorites");
		session.SetLongValue ("FavoriteNumber", fontFamilies.GetSize ());
		for (UIndex i = 0; i < fontFamilies.GetSize (); ++i) {
			sprintf (favoriteNameId, "FavoriteName_%ld", (GS::LongForStdio) i);
			session.SetStringValue (favoriteNameId, fontFamilies [i].GetLocalName ());
			sprintf (favoriteEncodingId, "FavoriteEncoding_%ld", (GS::LongForStdio) i);
			session.SetLongValue (favoriteEncodingId, fontFamilies [i].GetEncoding (0));
			sprintf (favoriteTimeId, "FavoriteTime_%ld", (GS::LongForStdio) i);
			session.SetLongValue (favoriteTimeId, selectionTimes [i]);
		}
	}

	void ReadFromPrefs (void)
	{
		GSErrCode error;
		char favoriteNameId [128];
		char favoriteEncodingId [128];
		char favoriteTimeId [128];
		GSPref::FixPathSession	session ("FontFavorites");
		Int32 favoriteNumber = 0;
		error = session.GetLongValue ("FavoriteNumber", &favoriteNumber, 0, GSPref::IRoot::DontWriteBack);
		if (error != GS::NoError)
			return;
		for (Int32 i = 0; i < favoriteNumber; ++i) {
			sprintf (favoriteNameId, "FavoriteName_%ld", (GS::LongForStdio) i);
			GS::UniString favoriteLocalName;
			error = session.GetStringValue (favoriteNameId, &favoriteLocalName, GS::EmptyUniString, GSPref::IRoot::DontWriteBack);
			if (error != GS::NoError)
				return;
			sprintf (favoriteEncodingId, "FavoriteEncoding_%ld", (GS::LongForStdio) i);
			Int32 favoriteEncoding = CC_Default;
			session.GetLongValue (favoriteEncodingId, &favoriteEncoding, CC_Default, GSPref::IRoot::DontWriteBack);
			if (error != GS::NoError)
				return;
			sprintf (favoriteTimeId, "FavoriteTime_%ld", (GS::LongForStdio) i);
			Int32 favoriteTime = 0;
			session.GetLongValue (favoriteTimeId, &favoriteTime, 0, GSPref::IRoot::DontWriteBack);
			if (error != GS::NoError)
				return;
			TE::FontFamily fontFamily (favoriteLocalName, (GSCharCode) favoriteEncoding);
			fontFamilies.Push (fontFamily);
			selectionTimes.Push ((GSTime)favoriteTime);
		}
	}
};

}

extern DG::FontFavorites*		dgFontFavorites;

#endif
