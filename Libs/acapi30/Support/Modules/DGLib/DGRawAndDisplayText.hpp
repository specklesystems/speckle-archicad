// *****************************************************************************
// File:			DGRawAndDisplayText.hpp
//
// Description:		Raw and display text related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// *****************************************************************************

#ifndef DG_RAW_AND_DISPLAY_HPP
#define DG_RAW_AND_DISPLAY_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DG.h"
#include "DGUtility.hpp"

// --- Predeclarations ---------------------------------------------------------

namespace DG {

// --- Class declarations ------------------------------------------------------

// --- RawAndDisplayText ---------------------------------------------------------------

/**
 * @class RawAndDisplayText
 * @ingroup DG
 * @brief Class contains both raw and display text, and conversion between them.
 * @details
 * 			- Windows uses raw text to specify the accelerator keys using ampersands in front of the key.
 * 			- A double ampersand in the raw text is used to display a single ampersand.
 * 			- The accelerator keys are displayed with an underline.
 * 			- For example "&Save" has an accelerator key 's' and this letter is displayed with an underscore.
 * 			- Mac does not use accelerator keys and displays text as given.
 */
class DG_DLL_EXPORT RawAndDisplayText
{
private:
	GS::UniString	rawText;
	GS::UniString	displayText;

	void	AssertFailed (const GS::UniString& message, const GS::UniString& text) const;
	void	UpdateDisplayTextFromRawText ();	// removes single &, and changes double && to single &
	void	UpdateRawTextFromDisplayText ();	// changes & to &&

protected:

public:
	/**
	 * @brief Constructor for RawAndDisplayText.
	 */
	RawAndDisplayText ();

	/**
	 * @brief Constructor for RawAndDisplayText.
	 * @param _rawText The raw text.
	 */
	RawAndDisplayText (GS::UniString _rawText);

	/**
	 * @brief Destructor for RawAndDisplayText.
	 */
	~RawAndDisplayText ();

	/**
	 * @brief Updates the raw text, and derives the associated display text.
	 * @param _rawText The new raw text.
	 * @return A reference to the object.
	 */
	RawAndDisplayText& SetRawText (const GS::UniString& _rawText);

	/**
	 * @brief Updates the display text, and derives the associated raw text.
	 * @param _displayText The new display text.
	 * @return A reference to the object.
	 */
	RawAndDisplayText& SetDisplayText (const GS::UniString& _displayText);

	/**
	 * @brief Gets the raw text.
	 * @return The raw text associated with the object.
	 */
	const GS::UniString&	GetRawText () const;

	/**
	 * @brief Gets the display text.
	 * @return The display text associated with the object.
	 */
	const GS::UniString&	GetDisplayText () const;
};

	// static methods

}	// namespace DG

#endif
