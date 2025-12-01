#ifndef PROFILEVECTORIMAGEBUILDER_HPP
#define PROFILEVECTORIMAGEBUILDER_HPP

#pragma once

// from GSRoot
#include "GSRoot.hpp"

// from VectorImage
#include "VectorImageTypedefs.hpp"
#include "IVectorImageBuilder.hpp"

class Sy_HatchType;
class HatchObject;
class Sy_LinType;;
class ProfileVectorImage;
class IPolygonDrawingDirection;

namespace VI {
namespace HatchPriority {
	class HatchPriorityComparer;
}
}

namespace PVI {
	class ProfileVectorImageParameter;
	class EdgeOverrideData;
	class Anchor;
	class AssociatedEdge;
	class DimensionControlTool;
	enum class DimProjectionType;
}

namespace VI {

class VI_DLL_CLASS_EXPORT ProfileVectorImageBuilder : public IVectorImageBuilder
{
public:
	ProfileVectorImageBuilder (ProfileVectorImage& inImage);
	virtual ~ProfileVectorImageBuilder ();

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

	//Member functions
	GSErrCode	AddAnchor (const PVI::ProfileAnchorId& id, const PVI::Anchor& a);
	GSErrCode	AddDimControlTool (const PVI::ProfileDimControlToolId& dimToolID, const PVI::DimensionControlTool& tool);

	GSErrCode	AddProfileParameter (const PVI::ProfileParameterId& parID);
	GSErrCode	AddOffsetParameterSetup (const PVI::ProfileParameterId& paramID,
										 const GS::Array<PVI::AssociatedEdge>& offsetEdgeDefs,
										 const PVI::Anchor&		begAnchor, 
										 const PVI::Anchor&		endAnchor,
										 const PVI::DimProjectionType projType,
										 const double			projAngleRad,
										 PVI::ProfileDimControlToolId* dimId = nullptr);



	void		AddEdgeOverrideData (const PVI::EdgeOverrideData& edgeOverrideData);
	void		Finalize (const VI::HatchPriority::HatchPriorityComparer& comparer);



private:
	ProfileVectorImage&		image;
	GS::Optional<double>	verticalStretchLineFirstLimit;
	GS::Optional<double>	horizontalStretchLineFirstLimit;
	bool					verticalStretchZoneSet;
	bool					horizontalStretchZoneSet;
};

}

#endif
