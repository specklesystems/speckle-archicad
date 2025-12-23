#ifndef UDUSERITEMINFOTAG_HPP
#define UDUSERITEMINFOTAG_HPP

#pragma once


#include "HashTable.hpp"

#include "FloatingMenu.hpp"

#include "UDDefinitions.hpp"

#include "DGApplicationObserver.hpp"


namespace UD {

	class UD_DLL_EXPORT UserItemInfoTag : public DG::ApplicationObserver {
	public:

		class UD_DLL_EXPORT UserItemInfoTagItem : public FloatingWindow::FloatingMenuItem {
		public:
			UserItemInfoTagItem ();

			virtual ~UserItemInfoTagItem ();

		};

		typedef FloatingWindow::FloatingMenu::MenuItemRowArray MenuItemRowArray;

	private:
		short			panelIdOfList;
		short			idOfList;
		DG::NativePoint	mousePosition;
		UInt64			elementId;
		DG::NativeRect	userItemRect;
		DG::NativeRect	taggedItemRect;
		bool			shouldStop;
		float			fadeStartAlpha;
		bool			shouldFadeOutAndStop;
		bool			windowDrawn;

		GSFineTicks		startTime;
		GSFineTicks		hoverInWaitDuration;
		GSFineTicks		hoverInDuration;
		GSFineTicks		hoverOutWaitDuration;
		GSFineTicks		hoverOutDuration;

		FloatingWindow::FloatingMenu	infoTagFloatingMenu;

		static GS::HashTable<UInt64, UserItemInfoTag*> instances;
	public:
		UserItemInfoTag (	short						panelIdOfList,
							short						idOfList,
							const DG::NativePoint&		mousePosition,
							UInt64						elementId,
							const DG::NativeRect&		userItemRect,
							const DG::NativeRect&		taggedItemRect,
							double						hoverInWaitSecs,
							double						hoverInSecs,
							double						hoverOutWaitSecs,
							double						hoverOutSecs,
							double						scaleFactor,
							const MenuItemRowArray&		menuItemRowArray = MenuItemRowArray (),
							bool						elemNumChanged = false,
							bool						fixPosition = false);

		~UserItemInfoTag ();

		static void Refresh (	short						panelIdOfList,
								short						idOfList,
								const DG::NativePoint&		mousePosition,
								UInt64						elementId,
								const DG::NativeRect&		userItemRect,
								const DG::NativeRect&		taggedItemRect,
								double						hoverInWaitSecs,
								double						hoverInSecs,
								double						hoverOutWaitSecs,
								double						hoverOutSecs,
								double						scaleFactor,
								const MenuItemRowArray&		menuItemRowArray = MenuItemRowArray (),
								bool						elemNumChanged = false,
								bool						fixPosition = false);

		bool	DoOneStep (void);

		static void	CallDoOneSteps (void);

		static void	CleanUp (void);

	private:
		void InitInfoTagFloatingMenu (const MenuItemRowArray& menuItemRowArray);

		void InitInfoTagFloatingMenuFields (const MenuItemRowArray& menuItemRowArray);

		void SwitchToFadeOutAndStopMode ();

		void SwitchBackToFadeInMode ();

		bool FadeIn ();

		bool FadeOutAndStop ();

		void Position (double scaleFactor);

		void FixPosition (double scaleFactor);

		virtual void ModalStateIncreased () override;
	};

	class UD_DLL_EXPORT UserItemInfoTagProperty
	{
	private:
		DG::Item* item;

		static	bool	registryHasRead;
				bool	useOwnTooltipDelayForHoverInWaitTime;
				Int32	hoverInWaitMillisecs;
				Int32	hoverInMillisecs;
				Int32	hoverOutWaitMillisecs;
				Int32	hoverOutMillisecs;

				bool	multipleElements;
	public:
		UserItemInfoTagProperty (DG::Item* item);

		virtual ~UserItemInfoTagProperty ();

		virtual void	DisableInfoTag ()	= 0;
		virtual void	EnableInfoTag ()	= 0;

	protected:
		void RefreshInfoTag (const DG::Dialog* dialog);

		virtual UserItemInfoTag::MenuItemRowArray	CreateMenuItemRowArray () const = 0;

		void ReadRegistry ();
	};

}

#endif //UDUSERITEMINFOTAG_HPP
