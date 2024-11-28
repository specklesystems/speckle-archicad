#ifndef VECTORIMAGEITERATOR_HPP
#define VECTORIMAGEITERATOR_HPP

#pragma once

// from VectorImage
#include "VectorImageExport.h"
#include "VectorImage.hpp"
#include "ProfileVectorImage.hpp"
#include "SyEnd.hpp"
#include "SyHot.hpp"
#include "SyLine.hpp"
#include "SyPolyLine.hpp"
#include "SyArc.hpp"
#include "SyText.hpp"
#include "SyRichText.hpp"
#include "SyHatch.hpp"
#include "SySpline.hpp"
#include "SyFont.hpp"
#include "SyPicture.hpp"
#include "SyPixMap.hpp"
#include "SyPointCloud.hpp"
#include "SyHatchObject.hpp" 

class VI_DLL_CLASS_EXPORT ConstVectorImageIterator
{
public:
	struct SortRecord
	{
		short		itemType;
		short		itemPriority;
		DrawIndex	drwIndex;
		Int32		itemPositionIndex;
		ULong		itemOffset;
	};

private:
	const VectorImage*		image;
	ULong					actOffset;
	GS::Array<SortRecord>	sortQueue;
	ULong					sortQueueIndex;
	short					GetItemTypePriority (short itemType);

public:
	explicit ConstVectorImageIterator (const VectorImage& image);
	ConstVectorImageIterator (const ConstVectorImageIterator& source);						// can throw

	~ConstVectorImageIterator ();

	const ConstVectorImageIterator& operator= (const ConstVectorImageIterator& source);		// can throw

	const Sy_EndType&	operator* () const;
	const Sy_EndType*	operator-> () const;

	operator const Sy_EndType* () const;
	operator const Sy_HotType* () const;
	operator const Sy_LinType* () const;
	operator const Sy_PolyLinType* () const;
	operator const Sy_ArcType* () const;
	operator const Sy_TextType* () const;
	operator const Sy_RichTextType* () const;
	operator const Sy_HatchType* () const;
	operator const HatchObject& () const;
	operator const Sy_SplineType* () const;
	operator const Sy_PictureType* () const;
	operator const Sy_PixMapType* () const;
	operator const Sy_FontType* () const;
	operator const Sy_PointCloudType* () const;

	ConstVectorImageIterator&	operator++ ();
	void						operator++ (int);
	bool						IsEOI () const;

	GSErrCode		SetSorting (GS::CmpFunction* cmpFunction, bool setItemPriority = true);
};


class VI_DLL_CLASS_EXPORT VectorImageIterator : public ConstVectorImageIterator
{
public:
	explicit VectorImageIterator (VectorImage& image);
	VectorImageIterator (const VectorImageIterator& source);								// can throw

	const VectorImageIterator& operator= (const VectorImageIterator& source);				// can throw

	Sy_EndType&		operator* ();
	Sy_EndType*		operator-> ();

	operator Sy_EndType* ();
	operator Sy_HotType* ();
	operator Sy_LinType* ();
	operator Sy_PolyLinType* ();
	operator Sy_ArcType* ();
	operator Sy_TextType* ();
	operator Sy_RichTextType* ();
	operator Sy_HatchType* ();
	operator Sy_SplineType* ();
	operator Sy_PictureType* ();
	operator Sy_PixMapType* ();
	operator Sy_FontType* ();
	operator Sy_PointCloudType* ();

	VectorImageIterator&	operator++ ();
	void					operator++ (int);
	bool					IsEOI () const;

	GSErrCode		SetSorting (GS::CmpFunction* cmpFunction);
};


class ProfileVectorImageIterator : public VectorImageIterator
{
public:
	explicit ProfileVectorImageIterator (ProfileVectorImage& profileImage) : VectorImageIterator (profileImage.image)
	{
	}
};


class ConstProfileVectorImageIterator : public ConstVectorImageIterator
{
public:
	explicit ConstProfileVectorImageIterator (const ProfileVectorImage& profileImage) : ConstVectorImageIterator (profileImage.image)
	{
	}
};


inline ConstVectorImageIterator::ConstVectorImageIterator (const VectorImage& im) :
	image (&im),
	actOffset (0),
	sortQueueIndex (0)
{
}


GS_FORCE_INLINE ConstVectorImageIterator::~ConstVectorImageIterator ()
{
}


GS_FORCE_INLINE const Sy_EndType& ConstVectorImageIterator::operator* () const
{
	return *operator-> ();
}


inline const Sy_EndType* ConstVectorImageIterator::operator-> () const
{
	return image->Element (actOffset);
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_EndType* () const
{
	return operator-> ();
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_HotType* () const
{
	DBASSERT ((*this)->item_Typ == SyHots);
	return (const Sy_HotType*) operator-> ();
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_LinType* () const
{
	DBASSERT ((*this)->item_Typ == SyLine);
	return (const Sy_LinType*) operator-> ();
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_PolyLinType* () const
{
	DBASSERT ((*this)->item_Typ == SyPolyLine);
	return (const Sy_PolyLinType*) operator-> ();
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_ArcType* () const
{
	DBASSERT ((*this)->item_Typ == SyArc);
	return (const Sy_ArcType*) operator-> ();
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_TextType* () const
{
	DBASSERT ((*this)->item_Typ == SyText);
	return (const Sy_TextType*) operator-> ();
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_RichTextType* () const
{
	DBASSERT ((*this)->item_Typ == SyRichText);
	return (const Sy_RichTextType*) operator-> ();
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_HatchType* () const
{
	DBASSERT ((*this)->item_Typ == SyHatch);
	return (const Sy_HatchType*) operator-> ();
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const HatchObject& () const
{
	DBASSERT ((*this)->item_Typ == SyHatch);
	const Sy_HatchType* hatchRef = (const Sy_HatchType*) operator-> ();
	if (DBVERIFY (hatchRef != nullptr)) {
		return image->GetHatchObject (*hatchRef);
	}

	static const HatchObject emptyHO;
	return emptyHO;
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_SplineType* () const
{
	DBASSERT ((*this)->item_Typ == SySpline);
	return (const Sy_SplineType*) operator-> ();
}

GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_PictureType* () const
{
	DBASSERT ((*this)->item_Typ == SyPicture);
	return (const Sy_PictureType*) operator-> ();
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_PixMapType* () const
{
	DBASSERT ((*this)->item_Typ == SyPixMap);
	return (const Sy_PixMapType*) operator-> ();
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_FontType* () const
{
	DBASSERT ((*this)->item_Typ == SyFont);
	return (const Sy_FontType*) operator-> ();
}


GS_FORCE_INLINE ConstVectorImageIterator::operator const Sy_PointCloudType* () const
{
	DBASSERT ((*this)->item_Typ == SyPointCloud);
	return (const Sy_PointCloudType*) operator-> ();
}


inline ConstVectorImageIterator& ConstVectorImageIterator::operator++ ()
{
	DBASSERT (!IsEOI ());

	if (sortQueue.GetSize () == 0)
		actOffset += (*this)->item_Len;
	else if (++sortQueueIndex < sortQueue.GetSize ())
		actOffset = sortQueue[sortQueueIndex].itemOffset;
	else
		actOffset = image->imageDataLen;

	return *this;
}


GS_FORCE_INLINE void ConstVectorImageIterator::operator++ (int)
{
	++*this;
}


GS_FORCE_INLINE bool ConstVectorImageIterator::IsEOI () const
{
	return actOffset >= image->imageDataLen;
}


inline VectorImageIterator::VectorImageIterator (VectorImage& im) :
	ConstVectorImageIterator (im)
{
	im.InvalidateBounds ();
}


GS_FORCE_INLINE VectorImageIterator::VectorImageIterator (const VectorImageIterator& source) :		// can throw
	ConstVectorImageIterator (source)
{
}


GS_FORCE_INLINE const VectorImageIterator& VectorImageIterator::operator= (const VectorImageIterator& source)			// can throw
{
	ConstVectorImageIterator::operator= (source);
	return *this;
}

GS_FORCE_INLINE Sy_EndType& VectorImageIterator::operator* ()
{
	return *operator-> ();
}


GS_FORCE_INLINE Sy_EndType* VectorImageIterator::operator-> ()
{
	return const_cast<Sy_EndType*> (ConstVectorImageIterator::operator-> ());
}


GS_FORCE_INLINE VectorImageIterator::operator Sy_EndType* ()
{
	return operator-> ();
}


GS_FORCE_INLINE VectorImageIterator::operator Sy_HotType* ()
{
	DBASSERT ((*this)->item_Typ == SyHots);
	return (Sy_HotType*) operator-> ();
}

GS_FORCE_INLINE VectorImageIterator::operator Sy_LinType* ()
{
	DBASSERT ((*this)->item_Typ == SyLine);
	return (Sy_LinType*) operator-> ();
}


GS_FORCE_INLINE VectorImageIterator::operator Sy_PolyLinType* ()
{
	DBASSERT ((*this)->item_Typ == SyPolyLine);
	return (Sy_PolyLinType*) operator-> ();
}


GS_FORCE_INLINE VectorImageIterator::operator Sy_ArcType* ()
{
	DBASSERT ((*this)->item_Typ == SyArc);
	return (Sy_ArcType*) operator-> ();
}

GS_FORCE_INLINE VectorImageIterator::operator Sy_TextType* ()
{
	DBASSERT ((*this)->item_Typ == SyText);
	return (Sy_TextType*) operator-> ();
}


GS_FORCE_INLINE VectorImageIterator::operator Sy_RichTextType* ()
{
	DBASSERT ((*this)->item_Typ == SyRichText);
	return (Sy_RichTextType*) operator-> ();
}


GS_FORCE_INLINE VectorImageIterator::operator Sy_HatchType* ()
{
	DBASSERT ((*this)->item_Typ == SyHatch);
	return (Sy_HatchType*) operator-> ();
}


GS_FORCE_INLINE VectorImageIterator::operator Sy_SplineType* ()
{
	DBASSERT ((*this)->item_Typ == SySpline);
	return (Sy_SplineType*) operator-> ();
}


GS_FORCE_INLINE VectorImageIterator::operator Sy_PictureType* ()
{
	DBASSERT ((*this)->item_Typ == SyPicture);
	return (Sy_PictureType*) operator-> ();
}


GS_FORCE_INLINE VectorImageIterator::operator Sy_PixMapType* ()
{
	DBASSERT ((*this)->item_Typ == SyPixMap);
	return (Sy_PixMapType*) operator-> ();
}

GS_FORCE_INLINE VectorImageIterator::operator Sy_FontType* ()
{
	DBASSERT ((*this)->item_Typ == SyFont);
	return (Sy_FontType*) operator-> ();
}


GS_FORCE_INLINE VectorImageIterator::operator Sy_PointCloudType* ()
{
	DBASSERT ((*this)->item_Typ == SyPointCloud);
	return (Sy_PointCloudType*) operator-> ();
}


GS_FORCE_INLINE VectorImageIterator& VectorImageIterator::operator++ ()
{
	ConstVectorImageIterator::operator++ ();
	return *this;
}


GS_FORCE_INLINE bool VectorImageIterator::IsEOI () const
{
	return ConstVectorImageIterator::IsEOI ();
}


#endif
