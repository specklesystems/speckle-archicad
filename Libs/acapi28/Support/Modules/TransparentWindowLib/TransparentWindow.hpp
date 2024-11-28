// *****************************************************************************
// File:			TransparentWindow.hpp
//
// Description:
//
// Project:
//
// Namespace:
//
// Contact person:	NZ, BL
//
// SG compatible
// *****************************************************************************
#ifndef TRANSPARENTWINDOW_HPP
#define TRANSPARENTWINDOW_HPP

// --- Includes ----------------------------------------------------------------

#include "TransparentWindowLibDefinitions.hpp"
#include "NativeContexts.hpp"
#include "Optional.hpp"
#include "Pair.hpp"
#include "DGUtility.hpp"
#include "ITransparentWindow.hpp"

// --- Predeclarations ---------------------------------------------------------

class TrackerImpl;
class TransparentWindowImpl;

// --- Class declarations ------------------------------------------------------

class TRANSPARENTWINDOWLIB_DLL_EXPORT TransparentWindow : public ITracker::ITransparentWindow, public ITracker::TransptWindowEvents
{
friend class TransparentWindowImpl;

public:
	enum class MouseEventHandlingState {
		Enabled,
		Disabled
	};

private:
	bool					hidden;
	DG::NativePoint			position;
	short 					width;		// Logical units
	short 					height;		// Logical units
	MouseEventHandlingState	mouseEventHandlingState;
	DG::Rect				closeRect;	// Client relative logical units
	DG::Rect				moveRect;	// Client relative logical units

	// Disable
	TransparentWindow (const TransparentWindow&);
	TransparentWindow& operator= (const TransparentWindow&);

protected:
	TransparentWindowImpl*		transparentWindowImpl;
	float						animationProgress;
	virtual void				MouseClick (const DG::Point& point);
	virtual void				MouseUp (GS::Optional<DG::Point> clickPt, const DG::Point& releasePt);
	virtual void				MouseRClick (const DG::Point& point);
	virtual void				MouseRUp (GS::Optional<DG::Point> clickPt, const DG::Point& releasePt);
	virtual void				MouseMove (const DG::Point& point);
	virtual void				OnAnimationDone ();
	virtual void				OnClosed ();
	virtual void				OnHidden ();
	virtual void				OnShown ();
	virtual	void				OnRedrawRequested ();
	virtual GS::UniString		ToolTipTextRequested () const;

public:
	TransparentWindow (const DG::NativePoint& position, short width, short height);	// width and height have logical units
	virtual ~TransparentWindow ();

	void						SetPosition (const DG::NativePoint& pos, bool placeWindowBehindPalettes = true) override;	// pos is in the global coordinate space
	void						SetSize (short newWidth, short newHeight);	// Logical units
	void						SetGlobalAlpha (float inGlobalAlpha) override;
	DG::NativePoint				GetPosition (void) const override;	// Retrieves position with global origin
	short 						GetWidth (void) const override;
	short 						GetHeight (void) const override;
	float						GetGlobalAlpha (void) const override;
	double						GetResolutionFactor (void) const override;
	double						GetScaleFactor (void) const override;

	void						PlaceWindowInFrontOfPalettes ();
	void						PlaceWindowBehindPalettes ();
	NewDisplay::NativeContext	BeginDraw ();
	void						EndDraw (NewDisplay::NativeContext& context);
	void						Hide () override;
	void						Show () override;
	bool						IsVisible () const override;
	bool						IsWindowActive () const;
	void						ToolTipUpdateRequest () const;

	void						SetCursor (GSResModule cursorResModule, Int32 cursorId) override;
	void						ResetCursor () override;

	class TRANSPARENTWINDOWLIB_DLL_EXPORT AnimationDescriptor {
	public:
		typedef GS::Pair<float, float>	ValueForProgress;

		class TRANSPARENTWINDOWLIB_DLL_EXPORT FadeAnimation {
		public:
			virtual ~FadeAnimation ();
		};

		class TRANSPARENTWINDOWLIB_DLL_EXPORT MoveAnimation {
		public:
			typedef std::function<void (NewDisplay::NativeContext&, const DG::Rect&)> DrawFn;
		private:
			DG::Rect	startRect;
			DG::Rect	endRect;
			DrawFn		drawFn;
		public:
			MoveAnimation (const DG::Rect& startRect, const DG::Rect& endRect, const DrawFn& drawFn);
			virtual ~MoveAnimation ();

			const DG::Rect& GetStartRect	() const;
			const DG::Rect& GetEndRect		() const;

			virtual void Draw (NewDisplay::NativeContext& nativeContext, const DG::Rect& rect) final;
		};

	private:
		GS::Array<ValueForProgress>		valuesForProgress;
		GS::Optional<FadeAnimation>		optFadeAnimation;
		GS::Optional<MoveAnimation>		optMoveAnimation;
	public:
		AnimationDescriptor (const GS::Array<ValueForProgress>& valuesForProgress = {},
							 GS::Optional<FadeAnimation>		optFadeAnimation = GS::NoValue,
							 GS::Optional<MoveAnimation>		optMoveAnimation = GS::NoValue);

		const GS::Array<ValueForProgress>&	GetValuesForProgress () const;
		bool ShouldFade () const;
		
		bool ShouldMove () const;
		GS::Optional<MoveAnimation> GetMoveAnimation () const;
	};

	void						Animate (const AnimationDescriptor& animationDescriptor);
	void						StopAnimate ();

	void						SetCloseRect (const DG::Rect& rect) override;
	void						SetMoveRect (const DG::Rect& rect);

	DG::Rect					GetCloseRect (void) const override;	// Client relative logical units
	DG::Rect					GetMoveRect (void) const;	// Client relative logical units
	void						PlaceInFrontOf (const short refDialId) override;
	void						PlaceInFrontOf (const TransparentWindow& other);
	void						PlaceTopMost () override;

	bool						operator== (const void* window) const;

	void						SetMouseEventHandlingState (MouseEventHandlingState mouseEventHandlingState);
	MouseEventHandlingState		GetMouseEventHandlingState () const;

	void						SetCloseOnResignKeyWindow (bool set);

};


#endif
