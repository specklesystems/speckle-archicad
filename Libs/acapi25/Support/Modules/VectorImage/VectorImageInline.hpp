#ifndef VECTORIMAGEINLINE_HPP
#define VECTORIMAGEINLINE_HPP


GS_FORCE_INLINE Sy_EndType* VectorImage::Element (ULong offset)
{
	return (Sy_EndType*) (imageData + offset);
}


GS_FORCE_INLINE const Sy_EndType* VectorImage::Element (ULong offset) const
{
	return (const Sy_EndType*) (imageData + offset);
}


GS_FORCE_INLINE VectorImage::VectorImage ()
{
	EmptyVectorImage ();
}


GS_FORCE_INLINE bool VectorImage::operator!= (const VectorImage& op) const
{
	return !operator== (op);
}


GS_FORCE_INLINE void VectorImage::Clear ()
{
	delete [] imageData;
	EmptyVectorImage ();
}


GS_FORCE_INLINE GSErrCode VectorImage::SetCapacity (ULong capacity)
{
	return ReallocBytes (capacity, AllocationType (ExactAllocSize | MakeACopy));
}


GS_FORCE_INLINE GSErrCode VectorImage::GrowCapacity (ULong capacity)
{
	return SetCapacity (imageDataLen + capacity);
}


GS_FORCE_INLINE Int32 VectorImage::GetScale () const
{
	return defScale;
}


inline void VectorImage::SetScale (Int32 defScaleIn)
{
	if (defScale != defScaleIn) {
		defScale = defScaleIn;
		InvalidateBounds ();
	}
}


GS_FORCE_INLINE bool VectorImage::IsUsingDrawQueue () const
{
	return useDrawQueue;
}


GS_FORCE_INLINE bool VectorImage::IsUsingSortQueue () const
{
	return sortDrawQueue;
}


GS_FORCE_INLINE bool VectorImage::AreThereAnyHotspotsOutOfModel () const
{
	return GetVectorImageBounds ().hangOutOfBox;
}


GS_FORCE_INLINE bool VectorImage::WasGeneratedWithOverrides () const
{
	return generatedWithOverrides;
}


GS_FORCE_INLINE void VectorImage::SetDrawQueueUsing ()
{
	useDrawQueue = true;
}


GS_FORCE_INLINE void VectorImage::SetSortQueueUsing ()
{
	sortDrawQueue = true;
}


GS_FORCE_INLINE	void VectorImage::SetGeneratedWithOverrides (bool generatedWithOverrides)
{
	this->generatedWithOverrides = generatedWithOverrides;
}


GS_FORCE_INLINE bool VectorImage::IsFontsMapped () const
{
	return fontsMapped;
}


GS_FORCE_INLINE void VectorImage::SetFontMappingComplete ()
{
	fontsMapped = true;
}


GS_FORCE_INLINE bool VectorImage::IsEmpty () const
{
	return nElements == 0;
}


GS_FORCE_INLINE ULong VectorImage::GetItemCount (bool withoutHotspots /* = false */) const
{
	return withoutHotspots ? nElements - nHots : nElements;
}


inline ULong VectorImage::GetItemCountOfType (SyEnum typeID) const
{
	switch (typeID) {
		case SyHots:		return nHots;
		case SyLine:		return nLine;
		case SyPolyLine:	return nPolyLine;
		case SyArc:			return nArc;
		case SyText:		return nText;
		case SyRichText:	return nRichText;
		case SyHatch:		return nHatc;
		case SySpline:		return nSpline;
		case SyFont:		return nFonts;
		case SyPicture:		return nPicture;
		case SyPixMap:		return nPixMap;
		case SyPointCloud:	return nPointCloud;
		default:
			DBBREAK ();
			return 0;
	}
}


inline GSErrCode VectorImage::GetItemFramePoints (const Box2DData& frame, GS::Array<Coord>& points, bool withoutHotspots /* = false */) const
{
	return GetItemPoints_Common (&frame, points, SyEnd, withoutHotspots);
}


inline GSErrCode VectorImage::GetItemPointsOfType (SyEnum typeID, GS::Array<Coord>& points) const
{
	return GetItemPoints_Common (nullptr, points, typeID, false);
}


inline void VectorImage::AddHotspotRec (const Sy_HotType& hotspot)				// can throw
{
	AddRecord (&hotspot);
}


inline void VectorImage::AddLineRec (const Sy_LinType& line)			// can throw
{
	AddRecord (&line);
}


inline void VectorImage::AddArcRec (const Sy_ArcType& arc)				// can throw
{
	if (arc.r < Eps)
		return;
	AddRecord (&arc);
}


inline void VectorImage::AddTextRec (const Sy_TextType& text, const char* conPtr, const char* lstPtr)		// can throw
{
	AddRecord (&text, conPtr, text.conOff, text.conLen, lstPtr, text.lStOff, text.lStLen);
}


inline void VectorImage::AddRichTextRec (const Sy_RichTextType* richtext)			// can throw
{
	AddRecord (richtext);
}


inline void VectorImage::AddPixMapRec (const Sy_PixMapType& pixHeader, GSConstHandle pixMemoHdl, const char* mimeType /* = nullptr */)		// can throw
{
	AddRecord (&pixHeader, *pixMemoHdl, pixHeader.pixHdlOff, pixHeader.pixHdlLen, mimeType, pixHeader.mimeTypeOff, pixHeader.mimeTypeLen);
}


inline void VectorImage::AddSyElement (const Sy_EndType& elem)			// can throw
{
	DBASSERT_STR (elem.item_Typ != SyHatch, "Appending hatch this way will not copy the HatchObject!");
	DBASSERT_STR (elem.item_Typ != SyPointCloud, "Appending point cloud this way will not copy the PointCloudObject!");
	AddRecord (&elem);
}

#endif
