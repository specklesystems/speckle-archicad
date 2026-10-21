#if ! defined NOT_IMPLEMENTED_ATTRIBUTE_READER_HPP
#define NOT_IMPLEMENTED_ATTRIBUTE_READER_HPP


#include	"IAttributeReader.hpp"

// from Graphics
#include	"FillData.hpp"
#include	"LineData.hpp"

// from GSModeler2D
#include	"PenData.hpp"
#include	"BuildingMaterialData.hpp"
#include	"TextureData.hpp"

// from Model3D
#include	"Model3D/MaterialData.hpp"

#include	"ADBAttributeIndex.hpp"


namespace Modeler {


class MODEL3D_DLL_EXPORT NotImplementedAttributeReader : public IAttributeReader 
{
public:
	virtual GS::UniString									GetFillName (const ADB::AttributeIndex&	 /*fillInd*/) const override { DBBREAK_STR ("Not implemented!"); return ""; }
	virtual ADB::AttributeIndex								GetFillIndexByName (const GS::UniString& /*attrName*/) const override { DBBREAK_STR ("Not implemented!"); return ADB::InvalidAttributeIndex; }
	virtual ADB::AttributeIndex								GetFirstEmptyFill () const override { DBBREAK_STR ("Not implemented!"); return ADB::InvalidAttributeIndex; }
	virtual GS::Owner<GX::Pattern::FillData>				GetFillData (const ADB::AttributeIndex& /*fillInd*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; }
	virtual void											EnumerateFills (const std::function<void (const ADB::AttributeIndex&)>&) const override { DBBREAK_STR ("Not implemented!"); };

	virtual GS::UniString									GetLineName (const ADB::AttributeIndex& /*lineInd*/) const override { DBBREAK_STR ("Not implemented!"); return ""; }
	virtual ADB::AttributeIndex								GetLineIndexByName (const GS::UniString& /*attrName*/) const override { DBBREAK_STR ("Not implemented!"); return ADB::InvalidAttributeIndex; }
	virtual GX::Pattern::LineData							GetLineData (const ADB::AttributeIndex& /*lineInd*/) const override { DBBREAK_STR ("Not implemented!"); return {}; }
	virtual void											EnumerateLines (const std::function<void (const ADB::AttributeIndex&)>&) const override { DBBREAK_STR ("Not implemented!"); };

	virtual	USize											GetNumPen	() const override { DBBREAK_STR ("Not implemented!"); return 0; }
	virtual	Modeler::PenData								GetPenData	(short /*penInd*/) const override { DBBREAK_STR ("Not implemented!"); return {}; }

	virtual	Modeler::BuildingMaterialData					GetBuildingMaterialData (const ADB::AttributeIndex& /*bmatInd*/) const override { DBBREAK_STR ("Not implemented!"); return {}; }

	virtual bool											ExistsMaterial (const ADB::AttributeIndex& /*matInd*/) const override { DBBREAK_STR ("Not implemented!"); return false; }
	virtual GS::UniString									GetMaterialName (const ADB::AttributeIndex& /*matInd*/) const override { DBBREAK_STR ("Not implemented!"); return ""; }
	virtual ADB::AttributeIndex								GetMaterialIndexByName (const GS::UniString& /*attrName*/) const override { DBBREAK_STR ("Not implemented!"); return ADB::InvalidAttributeIndex; }
	virtual	GS::Owner<Modeler::MaterialData> 				GetMaterialData	(const ADB::AttributeIndex& /*matInd*/, short /*texPictIndex = -1*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; }
	virtual void											EnumerateMaterials (const std::function<void (const ADB::AttributeIndex&)>&) const override { DBBREAK_STR ("Not implemented!"); };
	virtual GS::Owner<Modeler::TextureData>					GetTextureData (const ADB::AttributeIndex& /*matInd*/, short /*texPictIndex*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; }

	virtual GS::Owner<IAttributeReader>						Clone () const override { return NewOwned<NotImplementedAttributeReader> (); }

	virtual ~NotImplementedAttributeReader (void);
};


}	// namespace Modeler


#endif // NOT_IMPLEMENTED_ATTRIBUTE_READER_HPP

