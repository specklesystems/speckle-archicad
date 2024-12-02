#ifndef GDL_GDLDICTIONARYSCHEMES_HPP
#define GDL_GDLDICTIONARYSCHEMES_HPP

#include "GDLDictionaryValidation.hpp"

namespace GDL
{
	class Dictionary;


	enum class DictionarySchemeIndex
	{
		// Common
		EmptyDictionary,
		ComponentId,
		PropertyId,
		PropertyValue,
		BoundingBox,
		Polygon2DEdge,
		Polygon2DEdgeNoEdgeInfo,
		Polygon2D,
		Polygon2DNoEdgeInfo,

		// GDL Global-specific
		NotFilledGdlGlobal,
		OpeningRelativeHeight,
		OpeningSymbolGeometry,
		LabelAssocElemGeometry,
		StairBreakMarksGeometry,
		SegmentCrossSection,
		ColumnSegmentInfoList,
		BeamSegmentInfoList,
		SymbPosFromSurveyPoint,

		// Request-specific
		InvalidRequestResult,
		ComponentIdsOfParentRequestInput,
		ComponentIdsOfParentRequestOutput,
		PropertyValuesOfParentRequestInput,
		ComponentPropertyValuesOfParentRequestInput,
		PropertyValuesRequestOutput,
		PropertyTreeOfParentRequestInput,
		ComponentPropertyTreeOfParentRequestInput,
		PropertyTreeRequestOutput,
		MEPRouteAttributeRequestOutput,
		MEPPipeFlexibleSegmentGeometryRequestOutput,
		MEPPipeFlexibleSegmentGeometryRequestInput,
		Coordinate3D,
	

		INDEXED_SCHEME_COUNT
	};

	class GDL_DLL_EXPORT IGdlDictionarySchemeInfo
	{
	public:
		IGdlDictionarySchemeInfo ();
		virtual ~IGdlDictionarySchemeInfo ();
		
		IGdlDictionarySchemeInfo (const IGdlDictionarySchemeInfo&) = delete;
		void operator= (const IGdlDictionarySchemeInfo&) = delete;

		virtual const GS::UniString&		GetName () const = 0;
		virtual bool						IsValid (const GDL::Dictionary& dict) const = 0;
		virtual GS::Optional<GS::UniString>	GetErrorMessage (const GDL::Dictionary& dict) const = 0;

		virtual void						DumpTechnicalInfo (ReportDisplayTextBuilder& display) const = 0;
	};


	class GDL_DLL_EXPORT GdlDictionarySchemeInfoBase : public IGdlDictionarySchemeInfo
	{
	public:
		GdlDictionarySchemeInfoBase (const GS::UniString& name, IDictionarySchemePtr scheme);
		virtual ~GdlDictionarySchemeInfoBase ();


		virtual const GS::UniString& GetName () const override;
		virtual bool						IsValid (const GDL::Dictionary& dict) const override;
		virtual GS::Optional<GS::UniString>	GetErrorMessage (const GDL::Dictionary& dict) const override;

		virtual void						DumpTechnicalInfo (ReportDisplayTextBuilder& display) const override;

		IDictionarySchemePtr				GetScheme () const;

	private:
		IDictionarySchemePtr scheme;
		GS::UniString name;
	};


	class GDL_DLL_EXPORT GdlDictionarySchemeInfo : public GdlDictionarySchemeInfoBase 
	{
	public:
		GdlDictionarySchemeInfo (const GS::UniString& name, IDictionarySchemePtr scheme);
		virtual ~GdlDictionarySchemeInfo ();
	};

	GDL_DLL_EXPORT const IGdlDictionarySchemeInfo*	FindGdlDictionarySchemeInfoByIndex (DictionarySchemeIndex index);
	GDL_DLL_EXPORT void								DumpTechnicalInfoOfGdlDictionarySchemes (ReportDisplayTextBuilder&);

	void											InitGdlDictionarySchemeInfos ();
	void											ExitGdlDictionarySchemeInfos ();
}

#endif