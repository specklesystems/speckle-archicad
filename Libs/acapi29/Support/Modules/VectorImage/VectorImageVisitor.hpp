#ifndef GS_VI_VECTORIMAGEVISITOR_HPP
#define GS_VI_VECTORIMAGEVISITOR_HPP

#include "ISymbol.hpp"
#include "VectorImageExport.h"

#include "Variant.hpp"
#include "Optional.hpp"
#include "Array.hpp"
#include "HashTable.hpp"

#include <functional>

class VectorImage;
class Sy_EndType;
class Sy_HeadType;
class Sy_HotType;
class Sy_LinType;
class Sy_ArcType;
class Sy_TextType;
class Sy_HatchType;
class Sy_SplineType;
class Sy_FontType;
class Sy_PictureType;
class Sy_PixMapType;
class Sy_RichTextType;
class Sy_PolyLinType;
class Sy_PointCloudType;

namespace VI {

class VI_DLL_CLASS_EXPORT VectorImageVisitor {
public:
	using EndHandler		= ::std::function<bool (Sy_EndType&)>;
	using HeadHandler		= ::std::function<bool (Sy_HeadType&)>;
	using HotsHandler		= ::std::function<bool (Sy_HotType&)>;
	using LineHandler		= ::std::function<bool (Sy_LinType&)>;
	using ArcHandler		= ::std::function<bool (Sy_ArcType&)>;
	using TextHandler		= ::std::function<bool (Sy_TextType&)>;
	using HatchHandler		= ::std::function<bool (Sy_HatchType&)>;
	using SplineHandler		= ::std::function<bool (Sy_SplineType&)>;
	using FontHandler		= ::std::function<bool (Sy_FontType&)>;
	using PictureHandler	= ::std::function<bool (Sy_PictureType&)>;
	using PixMapHandler		= ::std::function<bool (Sy_PixMapType&)>;
	using RichTextHandler	= ::std::function<bool (Sy_RichTextType&)>;
	using PolyLineHandler	= ::std::function<bool (Sy_PolyLinType&)>;
	using PointCloudHandler = ::std::function<bool (Sy_PointCloudType&)>;
	using Handler = GS::Variant<
		EndHandler,
		HeadHandler,
		HotsHandler,
		LineHandler,
		ArcHandler,
		TextHandler,
		HatchHandler,
		SplineHandler,
		FontHandler,
		PictureHandler,
		PixMapHandler,
		RichTextHandler,
		PolyLineHandler,
		PointCloudHandler>;
	using EndConstHandler			= ::std::function<bool (const Sy_EndType&)>;
	using HeadConstHandler			= ::std::function<bool (const Sy_HeadType&)>;
	using HotsConstHandler			= ::std::function<bool (const Sy_HotType&)>;
	using LineConstHandler			= ::std::function<bool (const Sy_LinType&)>;
	using ArcConstHandler			= ::std::function<bool (const Sy_ArcType&)>;
	using TextConstHandler			= ::std::function<bool (const Sy_TextType&)>;
	using HatchConstHandler			= ::std::function<bool (const Sy_HatchType&)>;
	using SplineConstHandler		= ::std::function<bool (const Sy_SplineType&)>;
	using FontConstHandler			= ::std::function<bool (const Sy_FontType&)>;
	using PictureConstHandler		= ::std::function<bool (const Sy_PictureType&)>;
	using PixMapConstHandler		= ::std::function<bool (const Sy_PixMapType&)>;
	using RichTextConstHandler		= ::std::function<bool (const Sy_RichTextType&)>;
	using PolyLineConstHandler		= ::std::function<bool (const Sy_PolyLinType&)>;
	using PointCloudConstHandler	= ::std::function<bool (const Sy_PointCloudType&)>;
	using ConstHandler = GS::Variant<
		EndConstHandler,
		HeadConstHandler,
		HotsConstHandler,
		LineConstHandler,
		ArcConstHandler,
		TextConstHandler,
		HatchConstHandler,
		SplineConstHandler,
		FontConstHandler,
		PictureConstHandler,
		PixMapConstHandler,
		RichTextConstHandler,
		PolyLineConstHandler,
		PointCloudConstHandler>;

	explicit VectorImageVisitor (VectorImage& vectorImage, const GS::Array<Handler>& handlers);
	explicit VectorImageVisitor (const VectorImage& vectorImage, const GS::Array<ConstHandler>& handlers);

	bool WasSuccessful () const;

private:
	void VisitAll (VectorImage& vectorImage);
	void VisitAll (const VectorImage& vectorImage);

	GS::HashTable<SyEnum, Handler>		mHandlers;
	GS::HashTable<SyEnum, ConstHandler>	mConstHandlers;
	bool								mSuccessfulRun = true;
};

}

#endif
