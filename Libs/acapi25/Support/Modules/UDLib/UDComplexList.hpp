#ifndef UDCOMPLEXLIST_HPP
#define UDCOMPLEXLIST_HPP

#include "UDDefinitions.hpp"

#pragma once

namespace UD {
	class UD_DLL_EXPORT ComplexList {
	public:
		enum class ViewMode {
			Small,
			Medium,
			Large
		};

		class ViewModeRadioGroupObserver;

		class UD_DLL_EXPORT ViewModeRadioGroup :	public GS::EventSource,
													public DG::RadioItemObserver
		{
		public:
			class UD_DLL_EXPORT Observer : public GS::EventObserver {
				public:
					virtual void ViewModeGroupRadioItemChanged (ViewMode newViewMode) = 0;
			};
		private:
			DG::IconPushRadio	smallImageViewModeRadio;
			DG::IconPushRadio	mediumImageViewModeRadio;
			DG::IconPushRadio	largeImageViewModeRadio;
		public:
			ViewModeRadioGroup (const DG::Panel& panel, short smallItem, short MediumItem, short largeItem);
			virtual ~ViewModeRadioGroup ();

			virtual void RadioItemChanged (const DG::RadioItemChangeEvent& ev) override;

			void	Attach (Observer& observer);
			void	Detach (Observer& observer);

			void SetViewMode (ViewMode viewMode, bool notifyObservers = false);
			ViewMode GetViewMode () const;

			void Move (short dh, short dv);

			void Show ();
			void Hide ();
			bool IsVisible () const;
			void Redraw () const;

			short GetWidth () const;
		
		private:
			void SendViewModeGroupRadioItemChanged (ViewMode viewMode);

			DG::Icon GetDefaultSmallImageViewModeIcon () const;
			DG::Icon GetDefaultMediumImageViewModeIcon () const;
			DG::Icon GetDefaultLargeImageViewModeIcon () const;
		};
};

}

#endif
