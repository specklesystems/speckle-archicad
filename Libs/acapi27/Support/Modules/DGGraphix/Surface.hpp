// *****************************************************************************
// File:			Surface.hpp
//
// Description:
//
// Project:
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef SURFACE_HPP
#define SURFACE_HPP

// --- Includes ----------------------------------------------------------------

#include "CountedPtr.hpp"
#include "Ref.hpp"
#include "NativeContext.hpp"
#include "DGGraphixDefinitions.hpp"					// DGGRAPHIX_DLL_EXPORT

// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class Point;
	class Rect;
}

namespace NewDisplay {
	class OffscreenSurface;
	class BlitEffect;
}


// --- Class declarations ------------------------------------------------------

namespace NewDisplay {

class DGGRAPHIX_DLL_EXPORT Surface:	public BlitSource
{
protected:
	virtual	bool	BlitTo (BlitTarget& target, float scaleX, float scaleY, float rotation, float translationX, float translationY,
							float alpha, BlendMode blendMode, Filtering filtering, const BlitEffect* blitEffect) const override;

	virtual bool	CopyZBuffer (BlitTarget& target) const override;

public:
	class Impl
	{
	public:
		virtual ~Impl ();
	};
	typedef GS::Ref<Impl>	ImplRef;

	class DGGRAPHIX_DLL_EXPORT GuardedContext
	{
	private:
		Surface*		surface;
		ImplRef			surfaceImpl;

	public:
		NativeContext	nativeContext;

	public:
		GuardedContext (Surface* surface);
		virtual ~GuardedContext ();

		void Release ();
	};
	typedef GS::CountedPtr<GuardedContext> ContextGuard;

public:
	ImplRef					implRef;

private:
	virtual	NativeContext	GetContext () = 0;
	virtual void			ReleaseContext () = 0;

protected:
	Surface (ImplRef implRef);

public:
	virtual ~Surface ();

	virtual UInt32			GetWidth () const = 0;
	virtual UInt32			GetHeight () const = 0;

	bool					IsContentValid () const;
	bool					IsCalmAndCool () const;

	ContextGuard			GetContextGuard ();
	NativeContext			GetContext_INTERNAL ();		// use GetContextGuard instead
	void					ReleaseContext_INTERNAL ();	// use GetContextGuard instead

};

}

#endif
