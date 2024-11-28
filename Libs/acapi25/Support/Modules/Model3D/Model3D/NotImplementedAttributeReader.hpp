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


namespace Modeler {


class MODEL3D_DLL_EXPORT NotImplementedAttributeReader : public IAttributeReader 
{
public:
	virtual GS::UniString									GetFillName (GSAttributeIndex /*fillInd*/) const override { DBBREAK_STR ("Not implemented!"); return ""; }
	virtual GSAttributeIndex								GetFillIndexByName (const GS::UniString& /*attrName*/) const override { DBBREAK_STR ("Not implemented!"); return -1; } 
	virtual	GSAttributeIndex								GetFillMaxInd	() const override { DBBREAK_STR ("Not implemented!"); return -1; }
	virtual GSAttributeIndex								GetFirstEmptyFill () const override { DBBREAK_STR ("Not implemented!"); return -1; }
	virtual GS::AutoPtr <GX::Pattern::FillData>				GetFillData (GSAttributeIndex /*fillInd*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; }

	virtual GS::UniString									GetLineName (GSAttributeIndex /*lineInd*/) const override { DBBREAK_STR ("Not implemented!"); return ""; }
	virtual GSAttributeIndex								GetLineIndexByName (const GS::UniString& /*attrName*/) const override { DBBREAK_STR ("Not implemented!"); return -1; } 
	virtual	GSAttributeIndex								GetLineMaxInd	() const override { DBBREAK_STR ("Not implemented!"); return -1; }
	virtual GS::AutoPtr <GX::Pattern::LineData>				GetLineData (GSAttributeIndex /*lineInd*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; } 

	virtual	USize											GetNumPen	() const override { DBBREAK_STR ("Not implemented!"); return 0; }
	virtual	GS::AutoPtr <Modeler::PenData> 					GetPenData	(short /*penInd*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; }

	virtual	GS::AutoPtr <Modeler::BuildingMaterialData>		GetBuildingMaterialData (GSAttributeIndex /*bmatInd*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; } 

	virtual bool											ExistsMaterial (GSAttributeIndex /*matInd*/) const override { DBBREAK_STR ("Not implemented!"); return false; }
	virtual GS::UniString									GetMaterialName (GSAttributeIndex /*matInd*/) const override { DBBREAK_STR ("Not implemented!"); return ""; }
	virtual GSAttributeIndex								GetMaterialIndexByName (const GS::UniString& /*attrName*/) const override { DBBREAK_STR ("Not implemented!"); return -1; } 
	virtual	GSAttributeIndex								GetMaterialMaxInd	() const override { DBBREAK_STR ("Not implemented!"); return -1; }
	virtual	GS::AutoPtr <Modeler::MaterialData> 			GetMaterialData	(GSAttributeIndex /*matInd*/, short /*texPictIndex = -1*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; }
	virtual GS::AutoPtr <Modeler::TextureData>				GetTextureData (GSAttributeIndex /*matInd*/, short /*texPictIndex*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; }

	virtual GS::AutoPtr<IAttributeReader>					Clone () const override { return GS::AutoPtr<IAttributeReader> {new NotImplementedAttributeReader}; }

	virtual ~NotImplementedAttributeReader (void);
};


}	// namespace Modeler


#endif // NOT_IMPLEMENTED_ATTRIBUTE_READER_HPP

