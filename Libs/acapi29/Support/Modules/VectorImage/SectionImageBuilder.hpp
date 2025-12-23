#ifndef GS_SECTIONIMAGEBUILDER_HPP
#define GS_SECTIONIMAGEBUILDER_HPP

// from GSRoot
#include "GSRoot.hpp"

// from VectorImage
#include "SectionImage.hpp"
#include "IVectorImageBuilder.hpp"

namespace VI {

class VI_DLL_CLASS_EXPORT SectionImageBuilder : public IVectorImageBuilder
{
public:
	SectionImageBuilder (VI::SectionImage& inImage);
	virtual ~SectionImageBuilder ();

	//IVectorImageBuilder functions
	virtual GSErrCode	AddArc (const Sy_ArcType& arc) override;
	virtual GSErrCode	AddFont (const Sy_FontType& font, const GS::UniString& fontName) override;
	virtual GSErrCode	AddHatch (Sy_HatchType& hatchRef, HatchObject& hatch, const Geometry::Vector2d* offsCo) override;
	virtual GSErrCode	AddHatchFromPolygon (Sy_HatchType&												hatchRef,
											 HatchObject&												syHatch,
											 const Geometry::IrregularPolygon2D&						polygon,
											 const IPolygonDrawingDirection*							drawingDirection,
											 const Geometry::Vector2d*									offsCo,
											 const ProfileItem*											profileItem,
											 const ProfileEdgeDataTable*	profileEdgeData) override;
	virtual GSErrCode	AddHotspot (const Sy_HotType& hotspot) override;
	virtual GSErrCode	AddLine (const Sy_LinType& line) override;
	virtual GSErrCode	AddPixMap (const Sy_PixMapType& pixHeader, GSConstHandle pixMemoHdl, const char* mimeType) override;
	virtual GSErrCode	AddPolyLine (const Sy_PolyLinType& syPolyLine, const Geometry::Polyline2D& polyline) override;
	virtual GSErrCode	AddRichText (const Sy_RichTextType* richtext) override;
	virtual GSErrCode	AddSpline (const Sy_SplineType& spline, const char* pCoordPtr, const char* pSDirsPtr, const Geometry::Vector2d* offsCo) override;
	
	virtual void		SetDrawQueueUsing () override;
	virtual void		SetScale (Int32 defScaleIn) override;

private:
	VI::SectionImage&		image;
};

}

#endif
