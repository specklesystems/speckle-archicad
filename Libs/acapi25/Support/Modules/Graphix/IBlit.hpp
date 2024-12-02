#ifndef	IBLIT_HPP
#define	IBLIT_HPP

#include "NativeContextBase.hpp"
#include "Rect.hpp"

namespace NewDisplay {

enum BlendMode {
	SrcBlend		=	1,
	SrcCopy			=	2
};


class	BlitEffect;
class	NativeContextImpl;

// Low-level callback interface for general interaction and poor performance
class GRAPHIX_DLL_EXPORT BlitTarget
{
public:
	bool							blendIsDoneBySource;
	GS::Rect<float>					dirtyRect;
	NewDisplay::NativeContextImpl*	dstContext;

public:
	BlitTarget	(bool blendIsDoneBySource, NewDisplay::NativeContextImpl* dstContext = nullptr):
		blendIsDoneBySource (blendIsDoneBySource),
		dstContext			(dstContext)
	{
	}

    virtual ~BlitTarget ();

	virtual bool	GetPtrToDstRect (const GS::Rect<Int32>& /*rect*/, void** /*ptr*/, Int32* /*pitch*/)
	{
		return false;
	}

	virtual bool	MergeSrc (const void* /*srcPtr*/, Int32 /*pitch*/, bool /*srcIsPerpixelAlpha*/, UInt32 /*width*/, UInt32 /*height*/, Int32 /*dstPosX*/, Int32 /*dstPosY*/)
	{
		return false;
	}

	void			AddDirtyRect (float left, float top, float right, float bottom)
	{
		dirtyRect.Unify (GS::Rect<float> (left, top, right, bottom));
	}
};


class GRAPHIX_DLL_EXPORT BlitSource
{
public:
	virtual	bool	BlitTo (BlitTarget& target, float scaleX, float scaleY, float rotation, float translationX, float translationY,
						    float alpha = 1.0, BlendMode blendMode = SrcBlend, Filtering filtering = DefaultFilter, const BlitEffect* blitEffect = nullptr) const = 0;

	virtual bool	CopyZBuffer (BlitTarget& target) const = 0;

    virtual ~BlitSource ();
};


}

#endif
