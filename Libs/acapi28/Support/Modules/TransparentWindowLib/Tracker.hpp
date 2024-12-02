// *****************************************************************************
// File:			Tracker.hpp
//
// Description:
//
// Project:			ARCHICAD
//
// Namespace:
//
// Contact person:	NZ, DG, BL
//
// SG compatible
// *****************************************************************************

#ifndef TRACKER_HPP
#define TRACKER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "IDoubleProperty.hpp"

#include "Array.hpp"
#include "Color.hpp"

#include "DGItem.hpp"
#include "DGPanel.hpp"
#include "DGDialog.hpp"
#include "DGUtility.hpp"

#include "DGLowLevelKeyboardHandling.hpp"

#include "DisposableObject.hpp"

#include "Hint.hpp"

#include "TransparentWindow.hpp"

#if defined(_MSC_VER)
#pragma warning (disable: 4512)
#endif

// --- Predeclarations ---------------------------------------------------------

namespace Tracking {
	class TrackerEditPalette;
	class ITrackerItem;
	class LanderTracker;
}


namespace Tracking {

// --- Class declarations ------------------------------------------------------

/**
 * @brief Class for managing one specific tracker and its fields
 * @ingroup Tracker
 */
class TRANSPARENTWINDOWLIB_DLL_EXPORT Tracker:	public	TransparentWindow,
												private DG::PanelObserver,
												private DG::ItemObserver
{
friend class TrackerItemBase;
friend class ITrackerItem;

public:

	/**
	 * @brief Determines what to do with the edited field's latest value when the editing of the field needs to end
	 * @ingroup Tracker
	 */
	enum class ValueHandlingOnDeactivate {
		Accept,           /**< The edited field's latest value will be taken into account */
		Reject            /**< The edited field's latest value won't be taken into account */
	};

	/**
	 * @brief Determines how to relocate the tracker when the editing of the field needs to be ended
	 * @ingroup Tracker
	 */
	enum class PositionHandingOnDeactivate {
		KeepAsItIs,					   /**< The tracker is going to be kept at its current location */
		RemoveFromIdealPosition		   /**< The tracker is going to be moved to the position controlled by `GetTrackerPosition` */
	};

	/**
	 * @brief A constant iterator to read the items of the tracker
	 * @ingroup Tracker
	 */
	typedef GS::ConstForwardIterator<ITrackerItem*>	ConstItemIterator;

	/**
	 * @brief An iterator for accessing the items of the tracker
	 * @ingroup Tracker
	 */
	typedef GS::ForwardIterator<ITrackerItem*>		ItemIterator;

	/**
	 * @brief Helper guard class to specify a hint what to do when the editing of a field needs to be ended and possibly the reason for ending it
	 * @ingroup Tracker
	 */
	class TRANSPARENTWINDOWLIB_DLL_EXPORT [[nodiscard]] HintGuard {
	private:
		Tracker& trackerToGuard;
		Hint originalHint;

	public:
		/**
		 * @brief Starts the scope of the hint
		 * @ingroup Tracker
		 * @param[in,out] trackerToGuard  the affected tracker
		 * @param[in] newHint  the fields of `trackerToGuard` (i.e. `ITrackerItem`s) will receive this hint, which affect if the cursor should be moved or whether new Guide Lines needs to be placed
		 */
		HintGuard (Tracker& trackerToGuard, Hint newHint);

		/**
		 * @brief Finishes the scope of the hint
		 * @ingroup Tracker
		 * @post The state modified by the guard within the instance given in @ref HintGuard::HintGuard's `trackerToGuard` is restored to its original state
		 */
		~HintGuard ();
	};

	/**
	 * @brief Class to derive from, when creating custom keyboard handlers for the tracker's edit mode
	 * @ingroup Tracker
	 */
	class TRANSPARENTWINDOWLIB_DLL_EXPORT InEditKeyboardHandler: public DG::LowLevelKeyboardHandler
	{
	private:
		Tracker& tracker;

	protected:
		/**
		 * @brief Gets the parent tracker, where the events will be handled
		 * @ingroup Tracker
		 * @returns The parent tracker
		 */
		Tracker& GetTracker ();

		/**
		 * @brief Handles a regular key press event
		 * @ingroup Tracker
		 * @param[in] code	the code of the pressed key
		 * @param[out] item  Pointer to the UI item where the key press should be forwarded. nullptr by default, leave it as is to not forward the event
		 * @returns An enum to signal whether the event is processed or should be forwarded to the next handler
		 */
		virtual	DG::EventHandlerResultType	KeyPressed (const DG::Key::Code& code, DG::Item** item) override;

		/**
		 * @brief Handles a modifier key press event
		 * @ingroup Tracker
		 * @param[in] modifier	the pressed modifier
		 * @param[out] item  Pointer to the UI item where the key press should be forwarded. nullptr by default, leave it as is to not forward the event
		 * @returns An enum to signal whether the event is processed or should be forwarded to the next handler
		 */
		virtual DG::EventHandlerResultType	KeyPressed (const DG::Key::Modifier& modifier, DG::Item** item) override;

	public:
		/**
		 * @brief Constructor for the InEditKeyboardHandler
		 * @param[in] tracker	the parent tracker, where the events will be handled
		 */
		InEditKeyboardHandler (Tracker& tracker);

		virtual ~InEditKeyboardHandler (); /*!< Destructor */
	};

	/**
	 * @brief Class to derive from, when creating custom keyboard handlers for the tracker's running mode
	 * @ingroup Tracker
	 */
	class TRANSPARENTWINDOWLIB_DLL_EXPORT RunningModeKeyboardHandler: public DG::LowLevelKeyboardHandler
	{
	private:
		Tracker& tracker;

	protected:
		/**
		 * @brief Gets the parent tracker, where the events will be handled
		 * @ingroup Tracker
		 * @returns The parent tracker
		 */
		Tracker& GetTracker ();

		/**
		 * @brief Handles a regular key press event
		 * @ingroup Tracker
		 * @param[in] code	the code of the pressed key
		 * @param[out] item  Pointer to the UI item where the key press should be forwarded. nullptr by default, leave it as is to not forward the event
		 * @returns An enum to signal whether the event is processed or should be forwarded to the next handler
		 */
		virtual	DG::EventHandlerResultType	KeyPressed (const DG::Key::Code& code, DG::Item** item) override;

		/**
		 * @brief Handles a modifier key press event
		 * @ingroup Tracker
		 * @param[in] modifier	the pressed modifier
		 * @param[out] item  Pointer to the UI item where the key press should be forwarded. nullptr by default, leave it as is to not forward the event
		 * @returns An enum to signal whether the event is processed or should be forwarded to the next handler
		 */
		virtual DG::EventHandlerResultType	KeyPressed (const DG::Key::Modifier& modifier, DG::Item** item) override;

	public:
		/**
		 * @brief Constructor for the RunningModeKeyboardHandler
		 * @param[in] tracker	the parent tracker, where the events will be handled
		 */
		RunningModeKeyboardHandler (Tracker& tracker);

		virtual ~RunningModeKeyboardHandler (); /*!< Destructor */
	};

private:
	class TRANSPARENTWINDOWLIB_DLL_EXPORT IdleGuard {
	private:
		const Tracker& trackerToGuard;

	public:
		IdleGuard (const Tracker& trackerToGuard);
		virtual ~IdleGuard ();
	};

private:
	GS::Array<ITrackerItem*>	trackerItems;

	static Gfx::Color			foregroundColor;
	static Gfx::Color			backgroundColor;
	static Gfx::Color			frameColor;
	static float				opacity;
	static bool					drawFrame;
	static bool					smallFont;

	bool						useCustomBkgColor;
	bool						useCustomForeGroundColor;
	bool						useCustomFrameColor;
	bool						useCustomDrawFrame;
	Gfx::Color					customBkgColor;
	Gfx::Color					customForeGroundColor;
	Gfx::Color					customFrameColor;
	bool						customDrawFrame;

	TrackerEditPalette*			palette;
	DG::Icon					acceptInput;
	DG::Icon					returnToRunnigMode;
	DG::Icon					maximalizeTracker;

	GS::UniString				acceptInputToolTipString;
	GS::UniString				returnToRunnigModeToolTipString;
	GS::UniString				maximalizeTrackerToolTipString;
	GS::UniString				nullToolTipString;

	short						itemWidth[4];

	ITrackerItem*				activeItemPtr;
	bool						hidden;
	bool						showParameterNames;
	bool						allwaysShowParameterNames;
	DG::Rect					hoverRect;
	GS::UniString				toolTipString;
	Hint						hint;
	float						globalAlpha;

	bool						isEditTrackerMinimized;
	bool						showAll;
	DG::Rect					maximizeIconRect;
	mutable Int32				disableDeactivateOnFocusLost;
	bool						showReturnToRunningModeButton;
	ITrackerItem*				sendClickToWhileNextIdle;
	LanderTracker*				lander;

	GS::Owner<InEditKeyboardHandler>		inEditKeyboardHandler;
	GS::Owner<RunningModeKeyboardHandler>	runningModeKeyboardHandler;

protected:
	/**
	 * @brief Provides the option to force hiding the *Mark Position* button for each field of the tracker
	 * @ingroup Tracker
	 * @param[in] show
	 * 			  - when `false`, no *Mark position* button will be shown for any field
	 * 			  - when `true`, *Mark position* buttons are not forced to be hidden and its availability is determined by the field (`ITrackerItem`) it belongs to
	 * @details *Mark Postion* button: ![Mark Postion button](@ref tracker_runningModeButton.png){html: width=13px}
	 */
	void				ShowReturnToRunningModeButton (bool show);

	/**
	 * @brief Updates the size of the entire tracker based on its content such as fields, icons, etc
	 * @ingroup Tracker
	 */
	void				RefreshSize ();

private:
	GS::UniString		ToolTipTextRequested () const override;

	// from TrackerImpl
	void				MouseMoveEventHandler (const DG::Point& point);
	void				MouseClickEventHandler (const DG::Point& point);
	void				MouseRClickEventHandler (const DG::Point& point);

	DG::NativeRect		CalculatePaletteScreenRect () const;
	Tracker&			GetReference ();
	void				MoveTrackerAnimated (const DG::NativePoint& moveTo, short milliSec);
	void				Fade (const float endAlpha, short milliSec);
	void				CleanUpAfterEditMode ();
	void				DrawHoverRect (NewDisplay::NativeContext& context, const DG::Rect& hoverRect);
	void				Draw (NewDisplay::NativeContext& context, const DG::Rect& maximalizeIconRect);
	void				Draw ();
	void				AttachToAllPaletteItems ();
	void				DetachFromAllPaletteItems ();
	void				HandleActivableItemSetting ();

	// from KeyboardHandlers
	void				DeactivateActiveItemEditMode ();
	DG::Item*			ActivateActiveItemEditMode (DG::Palette& palette, short itemWidth[4]);

	// DG event handlers
	virtual void		PanelIdle (const DG::PanelIdleEvent& ev) override;
	virtual	void		PanelBackgroundPaint (const DG::PanelBackgroundPaintEvent& ev, bool* processed) override;
	virtual	short		SpecTrackEntered (const DG::ItemTrackEvent& ev) override;
	virtual	short		SpecTrackExited (const DG::ItemTrackEvent& ev) override;

	// from ITrackerItem
	bool				SelectItem (ITrackerItem* trackerItem);
	void				ItemDeleted (ITrackerItem* item);
	void				ShowAllItemsWhileEdit ();

	// from TrackerImpl
	DG::NativePoint		MapPointToScreen (const DG::Point& pointToMap) const;

	/**
	 * @brief Called when the currently edited field value is decided to be taken into account and to make its effect
	 * @ingroup Tracker
	 * @param[in] acceptedItem  the tracker item whose value got accepted
	 */
	virtual void		OnInputAccept (const ITrackerItem* acceptedItem) const;

	/**
	 * @brief Called when starting to edit a tracker field
	 * @ingroup Tracker
	 */
	virtual void		OnActivateEditMode () const;

	/**
	 * @brief Called when the editing of the tracker field is ended
	 * @ingroup Tracker
	 */
	virtual void		OnDeactivateEditMode () const;

	/**
	 * @brief Called when a context menu is required
	 * @ingroup Tracker
	 * @details Called when right clicking onto the tracker
	 */
	virtual void		OnContextMenuClicked () const;

	/**
	 * @brief Called when the hidden fields also need to be displayed
	 * @ingroup Tracker
	 * @details Called when someone clicks on the "Expand tracker" arrow near the center of the tracker's bottom edge
	 * 			| Before `OnTrackerMaximalized`                                                                  | After `OnTrackerMaximalized`                                                                 |
	 * 			| ---------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------- |
	 * 			| ![Before OnTrackerMaximalized](@ref tracker_beforeOnTrackerMaximalized.png){html: width=195px} | ![After OnTrackerMaximalized](@ref tracker_afterOnTrackerMaximalized.png){html: width=195px} |
	 */
	virtual void		OnTrackerMaximalized () const;

	/**
	 * @brief Called when the tracker needs to be placed near to a specified location but where it doesn't obstruct anything
	 * @ingroup Tracker
	 * @param[in] pos  Desired new position of the tracker's top left corner as DG::NativePoint (where values multiplied with the HiDPI factor)
	 * @param[in] width the width of the tracker as logical pixel size (not multiplied with the HiDPI factor)
	 * @param[in] height the height of the tracker as logical pixel size (not multiplied with the HiDPI factor)
	 * @returns the value of `pos`
	 * @remarks A possible overriding implementation should ensure for instance that it's not under the cursor, does not cover the petpalette or other UI elements when the cursor is outside the window
	 */
	virtual DG::NativePoint		GetIdealTrackerPosition (const DG::NativePoint& pos, short width, short height) const;

	/**
	 * @brief Called in cases where repositioning is needed after editing a field and defines the position of the tracker
	 * @ingroup Tracker
	 * @returns the value position of the tracker's TransparentWindow as DG::NativePoint (where values multiplied with the HiDPI factor)
	 */
	virtual DG::NativePoint		GetTrackerPosition (void) const;

	/**
	 * @brief Defines whether pressing numeric keys can immediately start the editing of the current default field or not
	 * @ingroup Tracker
	 * @returns true, i.e. numeric keys can immediately start the editing of the current default field (see @ref GetSelectedItem)
	 */
	virtual bool		IsDirectInputEnabled () const;

	/**
	 * @brief Returns whether the mouse event handling is enabled in running mode
	 * @ingroup Tracker
	 * @returns The state of mouse event handling in running mode
	 */
	virtual TransparentWindow::MouseEventHandlingState GetInRunningMouseEventHandlingState () const;

	/**
	 * @brief Called when the tracker field that is being edited is changed to another field
	 * @ingroup Tracker
	 */
	virtual void		OnActiveItemChanged () const;

	// Disable
	Tracker (const Tracker&);
	Tracker& operator= (const Tracker&);

public:
	/**
	 * @brief Tracker constructor
	 * @ingroup Tracker
	 * @details Side effect: Initializes tracker animation durations called "QuickAnimationTime" and "SlowAnimationTime" within system preferences in case these haven't been done yet (see also @ref ReadTrackerTimesPref)
	 */
	Tracker ();
	virtual ~Tracker ();

	/**
	 * @brief Add an item to the tracker
	 * @ingroup Tracker
	 * @param[in] trackerItem The item to be added
	 */
	void				AddItem (ITrackerItem* trackerItem);

	/**
	 * @brief Swaps the specified items
	 * @ingroup Tracker
	 * @param[in] trackerItem1 Item to be swapped with `trackerItem2`
	 * @param[in] trackerItem2 Item to be swapped with `trackerItem1`
	 * @pre Both items must already be added to the tracker and they must not be the same item
	 */
	void				SwapItems (ITrackerItem* trackerItem1, ITrackerItem* trackerItem2);

	/**
	 * @brief Provides a constant iterator to read each item of the tracker regardless whether they are visible or not
	 * @ingroup Tracker
	 * @return Returns a @ref ConstItemIterator
	 */
	ConstItemIterator	EnumerateAllItems () const;

	/**
	 * @brief Provides an iterator to access each item of the tracker regardless whether they are visible or not
	 * @ingroup Tracker
	 * @return Returns an @ref ItemIterator
	 */
	ItemIterator		EnumerateAllItems ();

	/**
	 * @brief Provides a constant iterator to read the visible items of the tracker
	 * @ingroup Tracker
	 * @return Returns a @ref ConstItemIterator
	 */
	ConstItemIterator	EnumerateVisibleItems () const;

	/**
	 * @brief Provides an iterator to access the visible items of the tracker
	 * @ingroup Tracker
	 * @return Returns an @ref ItemIterator
	 */
	ItemIterator		EnumerateVisibleItems ();

	/**
	 * @brief Provides the item for the tracker field that is currently the default one, shown with bold fonts, or is being edited
	 * @ingroup Tracker
	 * @return Returns a pointer to a const ITrackerItem
	 * @details
	 * @image html tracker_alwaysShow_ySelected.png "Here for instance, the Y row is going to be the selected item" width=195px
	 */
	const ITrackerItem*	GetSelectedItem () const;

	/**
	 * @brief Provides access to change the item that is currently the default field, shown with bold fonts, or is being edited
	 * @ingroup Tracker
	 * @return Returns a pointer to an ITrackerItem
	 * @details
	 * @image html tracker_alwaysShow_xSelected.png "Here for instance, the X row is going to be the selected item" width=195px
	 *
	 */
	ITrackerItem*		GetSelectedItem ();

	/**
	 * @brief Draws the tracker after ensuring that each field's value is consistent based on the input
	 * @ingroup Tracker
	 */
	virtual void		Synchronize ();

	/**
	 * @brief Function for updating the fade animation
	 * @ingroup Tracker
	 * @remarks Implementation detail. Not recommended for general use. Might be removed from here in the future.
	 */
	virtual void		RefreshFade ();

	/**
	 * @brief Provides the size and position of the tracker
	 * @ingroup Tracker
	 * @return Returns the rectangle as a DG::NativeRect (where values are multiplied with the HiDPI factor)
	 */
	DG::NativeRect			GetRect (void) const;

	/**
	 * @brief Repositions the tracker with the possibility of being animated
	 * @ingroup Tracker
	 * @param[in] point    	Target top left position as DG::NativePoint (where values multiplied with the HiDPI factor)
	 * @param[in] animated 	False by default. When true, the repositioning is animated.
	 * @param[in] milliSec
	 * 			  - short parameter controlling the length of the animation in milliseconds. By default -1.
	 * 			  - When less than zero, the animation length is defined by a tracker registry/preference value "QuickAnimationTime". (See also: @ref ReadTrackerTimesPref)
	 * @details The program gets blocked until the animation is completed, therefore it is not recommended to use long animation times.
	 */
	void					SetPosition (const DG::NativePoint& point, bool animated = false, short milliSec = -1);

	/**
	 * @brief Moves the tracker to near to its current location but where it doesn't obstruct anything
	 * @ingroup Tracker
	 * @remarks Implementation detail. Not recommended for general use. Might be removed from here in the future.
	 * @pre Must be called when not editing a field (i.e. @ref IsInEditMode is false)
	 * @details The location is determined by `GetIdealTrackerPosition`.
	 */
	void				MoveToVisiblePosition ();

	/**
	 * @brief Makes tracker stay at the position set by @ref MoveToVisiblePosition
	 * @ingroup Tracker
	 * @remarks Implementation detail. Not recommended for general use. Might be removed from here in the future.
	 * @details Related to the [Tracker Landing Game easter egg](https://community.graphisoft.com/t5/Getting-started/Easter-Eggs-in-Archicad/ta-p/303701#Tracker_Landing_Game.2C_ARCHICAD_10-13)
	 *
	 */
	void				StayInVisiblePosition ();

	/**
	 * @brief Starts the editing of the currently default tracker field (see @ref GetSelectedItem)
	 * @ingroup Tracker
	 * @return
	 * 			- a pointer to the DG::Item for the actual input field (e.g. a DG::RealEdit)
	 * 			- nullptr when the tracker has no fields/items
	 * @pre Must be called when not already editing a field (i.e. @ref IsInEditMode is false)
	 */
	DG::Item* 			ActivateEditMode ();

	/**
	 * @brief Stops the editing of the currently default tracker field (see @ref GetSelectedItem)
	 * @ingroup Tracker
	 * @param[in] valueHandling
	 * 			  - when `Accept`, the currently edited field value will be taken into account and will have its effect
	 * 			  - when `Reject`, the currently edited field value will be discarded
	 * @param[in] acceptedItemPtr  when the Optional has a value, the function emits an `OnInputAccept` event with the Optional's value as the argument of the event
	 * @param[in] positionHandling  determines how to relocate the tracker when the editing of the field needs to end
	 * @pre Must be called when already editing a field (i.e. @ref IsInEditMode is true)
	 */
	void				DeactivateEditMode (ValueHandlingOnDeactivate valueHandling, const GS::Optional<const ITrackerItem*>& acceptedItemPtr, PositionHandingOnDeactivate positionHandling);
	
	/**
	 * @brief Checks if any tracker field value is being edited
	 * @ingroup Tracker
	 * @return bool value, true when a field is being edited
	 */
	bool				IsInEditMode () const;

	/**
	 * @brief Checks whether the tracker's window is focused
	 * @ingroup Tracker
	 * @return bool value, true when the focused window is the tracker
	 */
	bool				IsTrackerEditWindowActive () const;

	/**
	 * @brief Activates the editing of the field following (i.e. the row below) the default or edited one
	 * @ingroup Tracker
	 * @details
	 * 			- When a field is being edited at the time of call, the function deactivates that.
	 * 			- It's cyclic, that is it activates the first editable field when the current one is the last
	 */
	void				SetNextActivableItem ();

	/**
	 * @brief Activates the editing of the field preceding (i.e. the row above) the default or edited one
	 * @ingroup Tracker
	 * @details
	 * 			- When a field is being edited at the time of call, the function deactivates that.
	 * 			- It's cyclic, that is it activates the last editable field when the current one is the first
	 */
	void				SetPrevActivableItem ();

	/**
	 * @brief Checks whether the first editable field is currently being edited or not
	 * @ingroup Tracker
	 * @return bool value, true when the currently edited field is the first of the editable ones
	 */
	bool				IsFirstActivableItemActive ();

	/**
	 * @brief Checks whether the last editable field is currently being edited or not
	 * @ingroup Tracker
	 * @return bool value, true when the currently edited field is the last of the editable ones
	 */
	bool				IsLastActivableItemActive ();
	
	/**
	 * @brief Activates the first editable field (i.e. the topmost editable row)
	 * @ingroup Tracker
	 * @details When a field is being edited at the time of call, the function deactivates that.
	 */
	void				SetFirstActivableItem ();

	/**
	 * @brief Activates the last editable field (i.e. the bottommost editable row)
	 * @ingroup Tracker
	 * @details When a field is being edited at the time of call, the function deactivates that.
	 */
	void				SetLastActivableItem ();

	/**
	 * @brief Hides the tracker
	 * @ingroup Tracker
	 * @details When called while a tracker field is being edited, the field's value is going to be rejected.
	 */
	void				Hide () override;

	/**
	 * @brief Shows the tracker
	 * @ingroup Tracker
	 */
	void				Show () override;

	/**
	 * @brief Checks whether the tracker is visible or not
	 * @ingroup Tracker
	 * @return a bool value, true when the tracker is visible
	 */
	bool				IsVisible () const override;

	/**
	 * @brief Changes the opacity of the entire tracker, with its texts and background as a single unit
	 * @ingroup Tracker
	 * @param[in] opacity a float value, fully transparent when `0.0f`, fully opaque when `1.0f`
	 * @remarks Not recommended for general use. Might be removed from here in the future.
	 * @details
	 * 			- The opacity of the field that is being edited is not affected.
	 * 			- The behavior is undefined for cases when the `opacity` value is less than 0 or greater than 1.
	 * 			| opacity = 0.0f                                                            | opacity = 0.33f                                                            | opacity = 0.66f                                                            | opacity = 1.00f                                                           |
	 * 			| ------------------------------------------------------------------------- | -------------------------------------------------------------------------- | -------------------------------------------------------------------------  | ------------------------------------------------------------------------- |
	 * 			| ![opacity=0.0f](@ref tracker_globalAlphaInEdit000.png){html: width=195px} | ![opacity=0.33f](@ref tracker_globalAlphaInEdit033.png){html: width=195px} | ![opacity=0.66f](@ref tracker_globalAlphaInEdit066.png){html: width=195px} | ![opacity=1.0f](@ref tracker_globalAlphaInEdit100.png){html: width=195px} |
	 */
	void				SetGlobalOpacity (float opacity);

	/**
	 * @brief Changes the appearance of the tracker whether to display the name of the fields or not
	 * @ingroup Tracker
	 * @param[in] showParameterNames  bool value, when `true`, field names are shown, otherwise not
	 * @remarks Not recommended for general use as changing the tracker setting in Work Environment settings also relies on this function
	 * @details Side effect: When called while editing a field, the field input might be deactivated and activated
	 * 			| showParameterNames = false                                                       | showParameterNames = true                                                        |
	 * 			| -------------------------------------------------------------------------------- | -------------------------------------------------------------------------------- |
	 * 			| ![showParameterNames = false](@ref tracker_paramnamesOff.png){html: width=195px} | ![showParameterNames = true](@ref tracker_paramnamesOn.png){html: width=195px} |
	 */
	void				SetShowParameterNames (bool showParameterNames);

	/**
	 * @brief Provides the option to override the value specified by @ref SetShowParameterNames
	 * @ingroup Tracker
	 * @param[in] allwaysShowParameterNames  bool value, when `true`, field names are forced to be shown, otherwise not
	 */
	void				SetAllwaysShowParameterNames (bool allwaysShowParameterNames);

	/**
	 * @brief Changes the behavior of the tracker whether to automatically expand and show every field each time a field is started to be edited
	 * @ingroup Tracker
	 * @param[in] isEditTrackerMinimizedParam  bool value, when `true`, some fields might not be shown immediately
	 * @remarks Not recommended for general use as changing the tracker colors in Work Environment settings also relies on this function
	 * @details
	 * 			| isEditTrackerMinimizedParam = true                                                       | isEditTrackerMinimizedParam = false                                                      |
	 * 			| ---------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------- |
	 * 			| ![isEditTrackerMinimizedParam = true](@ref tracker_autoExpandOff.png){html: width=195px} | ![isEditTrackerMinimizedParam = false](@ref tracker_autoExpandOn.png){html: width=195px} |
	 */
	void				SetEditTrackerSizePreference (bool isEditTrackerMinimizedParam);

	/**
	 * @brief Changes the color of texts and icons globally for all trackers
	 * @ingroup Tracker
	 * @param[in] foregroundColorToSet  the new color for texts and icons
	 * @remarks Not recommended for general use as changing the tracker colors in Work Environment settings also relies on this function
	 * @details
	 * @image html tracker_fgColor.png "foregroundColorToSet=Gfx::Color(255, 0, 0)" width=195px
	 * 		  - The alpha component of `foregroundColorToSet` has no visible effect except for being stored.
	 */
	static void			SetForegroundColor (const Gfx::Color& foregroundColorToSet);

	/**
	 * @brief Changes the background color (i.e. the fill behind texts and icons) globally for all trackers
	 * @ingroup Tracker
	 * @param[in] backgroundColorToSet  the new color for the background
	 * @remarks Not recommended for general use as changing the tracker colors in Work Environment settings also relies on this function
	 * @details
	 * @image html tracker_bgColor.png "backgroundColorToSet=Gfx::Color(255, 0, 0)" width=195px
	 * 		  - The alpha component of `backgroundColorToSet` has no visible effect except for being stored.
	 */
	static void			SetBackgroundColor (const Gfx::Color& backgroundColorToSet);

	/**
	 * @brief Changes the frame color globally for all trackers
	 * @ingroup Tracker
	 * @param[in] frameColorToSet  the new color for the frame
	 * @remarks Not recommended for general use as changing the tracker frame in Work Environment settings also relies on this function
	 * @details
	 * @image html tracker_frameOn_customColor.png "frameColorToSet=Gfx::Color(255, 0, 0)" width=195px
	 * 		  - The color is not reset and it is stored even when the frame turned off (see also: @ref SetDrawFrame)
	 * 		  - The alpha component of `frameColorToSet` has no visible effect except for being stored.
	 */
	static void			SetFrameColor (const Gfx::Color& frameColorToSet);

	/**
	 * @brief Retrieves the color of texts and icons used globally by all trackers
	 * @ingroup Tracker
	 * @return the color of texts and icons used by default in all trackers
	 * @details The result is defined by @ref SetForegroundColor
	 */
	static Gfx::Color	GetDefaultForegroundColor ();

	/**
	 * @brief Retrieves the background color (i.e. the fill behind texts and icons) used globally by all trackers
	 * @ingroup Tracker
	 * @return the color for the background used by default in all trackers
	 * @details The result is defined by @ref SetBackgroundColor
	 */
	static Gfx::Color	GetDefaultBackgroundColor ();

	/**
	 * @brief Retrieves the frame color used globally by all trackers
	 * @ingroup Tracker
	 * @return the frame color used by default in all trackers
	 * @details The result is defined by @ref SetFrameColor
	 */
	static Gfx::Color	GetDefaultFrameColor ();

	/**
	 * @brief Changes the opacity of the background (i.e. the fill behind texts and icons) for all trackers, globally
	 * @ingroup Tracker
	 * @param[in] opacityToSet a float value, new opacity for the background
	 * 			  - fully transparent when `0.0f`, fully opaque when `1.0f`
	 * @remarks Not recommended for general use as changing the tracker opacity in Work Environment settings also relies on this function
	 * @details The behavior is undefined for cases when the `opacity` value is less than 0 or greater than 1.
	 * 			| opacityToSet = 0.0f                                                  | opacityToSet = 0.33f                                                  | opacityToSet = 0.66f                                                  | opacityToSet = 1.00f                                                 |
	 * 			| -------------------------------------------------------------------- | --------------------------------------------------------------------- | --------------------------------------------------------------------  | -------------------------------------------------------------------- |
	 * 			| ![opacityToSet=0.0f](@ref tracker_opacity000.png){html: width=195px} | ![opacityToSet=0.33f](@ref tracker_opacity033.png){html: width=195px} | ![opacityToSet=0.66f](@ref tracker_opacity066.png){html: width=195px} | ![opacityToSet=1.0f](@ref tracker_opacity100.png){html: width=195px} |
	 */
	static void			SetOpacity (float opacityToSet);

	/**
	 * @brief Changes whether to show the tracker's frame globally for all trackers
	 * @ingroup Tracker
	 * @param[in] drawFrameToSet  bool value, when `true`, trackers will have a frame
	 * @remarks Not recommended for general use as changing the tracker opacity in Work Environment settings also relies on this function
	 * @details
	 * 			| drawFrameToSet = false                                                  | drawFrameToSet = true                                                 |
	 * 			| ----------------------------------------------------------------------- | --------------------------------------------------------------------- |
	 * 			| ![drawFrameToSet = false](@ref tracker_frameOff.png){html: width=195px} | ![drawFrameToSet = true](@ref tracker_frameOn.png){html: width=195px} |
	 */
	static void			SetDrawFrame (bool drawFrameToSet);

	/**
	 * @brief Changes whether the tracker rows should be display more compactly, globally for all trackers
	 * @ingroup Tracker
	 * @param[in] smallFontToSet  bool value, when `true`, the height of the rows will be shorter
	 * @remarks Not recommended for general use. Might be removed in the future. Remnant for supporting an old Work Environment option. (Was available until AC19)
	 * @details
	 * 			| smallFontToSet = false                                                      | smallFontToSet = true                                                     |
	 * 			| --------------------------------------------------------------------------- | ------------------------------------------------------------------------- |
	 * 			| ![smallFontToSet = false](@ref tracker_smallFontOff.png){html: width=195px} | ![smallFontToSet = true](@ref tracker_smallFontOn.png){html: width=195px} |
	 */
	static void			SetSmallFont (bool smallFontToSet);

	/**
	 * @brief Retrieves the color of texts and icons
	 * @ingroup Tracker
	 * @return the color of the tracker's texts and icons
	 * @details
	 * 			- The result is defined by @ref SetForegroundColor unless overridden by @ref SetCustomForeGroundColor
	 */
	Gfx::Color			GetForegroundColor ();

	/**
	 * @brief Retrieves the background color (i.e. the fill behind texts and icons)
	 * @ingroup Tracker
	 * @return the color of the tracker's background
	 * @details The result is be defined by @ref SetBackgroundColor unless overridden by @ref SetCustomBackgroundColor
	 */
	Gfx::Color			GetBackgroundColor ();

	/**
	 * @brief Retrieves the tracker's frame color
	 * @ingroup Tracker
	 * @return the frame color of the tracker
	 * @details The result is be defined by @ref SetFrameColor unless overridden by @ref SetCustomFrameColor
	 */
	Gfx::Color			GetFrameColor ();
	
	/**
	 * @brief Retrieves the tracker's opacity
	 * @ingroup Tracker
	 * @return the opacity of trackers, fully transparent when `0.0f`, fully opaque when `1.0f`
	 * @details The result is defined by @ref SetOpacity
	 */
	static float		GetOpacity ();

	/**
	 * @brief Retrieves whether the tracker's frame is shown
	 * @ingroup Tracker
	 * @return bool value, when `true`, the trackers frame is displayed
	 * @details The result might be defined by @ref SetDrawFrame unless overridden by @ref SetCustomDrawFrame
	 */
	bool				GetDrawFrame ();

	/**
	 * @brief Retrieves whether tracker rows are displayed more compactly
	 * @ingroup Tracker
	 * @return bool value, when `true`, the height of the rows are shorter
	 * @remarks Not recommended for general use. Might be removed in the future. Remnant for supporting an old Work Environment option. (Was available until AC19)
	 */
	static bool			GetSmallFont ();

	/**
	 * @brief Changes the background color (i.e. the fill behind texts and icons)
	 * @ingroup Tracker
	 * @param[in] color  the new color for the background
	 * @details
	 * 			- Overrides the value defined by @ref SetBackgroundColor
	 * 			- The alpha component of `color` has no visible effect except for being stored.
	 */
	void				SetCustomBackgroundColor (const Gfx::Color& color);

	/**
	 * @brief Changes the color of texts and icons
	 * @ingroup Tracker
	 * @param[in] color  the new color for texts and icons
	 * @details
	 * 			- Overrides the value defined by @ref SetForegroundColor
	 * 			- The alpha component of `color` has no visible effect except for being stored.
	 */
	void				SetCustomForeGroundColor (const Gfx::Color& color);

	/**
	 * @brief Changes the frame color
	 * @ingroup Tracker
	 * @param[in] color  the new color for the frame
	 * @details
	 * 			- Overrides the value defined by @ref SetFrameColor
	 * 			- The color is not reset and it is stored even when the frame turned off (see also: @ref SetDrawFrame)
	 * 			- The alpha component of `color` has no visible effect except for being stored.
	 */
	void				SetCustomFrameColor (const Gfx::Color& color);

	/**
	 * @brief Changes whether to show the tracker's frame
	 * @ingroup Tracker
	 * @param[in] drawFrameToSet  bool value, when `true`, trackers will have a frame
	 * @details Overrides the value defined by @ref SetDrawFrame
	 */
	void				SetCustomDrawFrame (bool drawFrameToSet);

	/**
	 * @brief Checks whether a keyboard code is for the decimal separator
	 * @ingroup Tracker
	 * @param[in] code  the code identifying the keyboard key
	 * @return a bool value, true when the keyboard code represents the decimal separator
	 */
	bool				IsDecimalSeparator (const DG::Key::Code& code) const;

	/**
	 * @brief Utility function for retrieving tracker animation durations stored in the system preferences (i.e the registry on Windows)
	 * @ingroup Tracker
	 * @param[in] name  the key's name for the duration value
	 * @param[in] defaultValue  duration in milliseconds, in case the key doesn't exist in the preferences yet
	 * @return a short value, animation duration in milliseconds
	 * @details
	 * 			- It is recommended to have `name` only contain characters representable in a C-string
	 * 			- It is recommended to set `defaultValue` only to at most a couple seconds. (0 < defaultValue < 2000)
	 * 			- The returned value is always at least 1 ms.
	 */
	static	short		ReadTrackerTimesPref (const GS::UniString& name, Int32 defaultValue);

	/**
	 * @brief Sets a keyboard handler to use in edit mode
	 * @ingroup Tracker
	 * @param[in] handler  the handler to set
	 */
	void				SetInEditKeyboardHandler (GS::Owner<InEditKeyboardHandler> handler);

	/**
	 * @brief Sets a keyboard handler to use in running mode
	 * @ingroup Tracker
	 * @param[in] handler  the handler to set
	 */
	void				SetRunningModeKeyboardHandler (GS::Owner<RunningModeKeyboardHandler> handler);
};


}	//namespace Tracker

#endif
