// *********************************************************************************************************************
// Description:		Attribute accessing class
//
// Module:			GSModeler2D
// Namespace:		Modeler
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (ATTRIBUTEREADER_HPP)
#define ATTRIBUTEREADER_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include	"VBAttributesEnv.hpp"
// from GSModeler2D
#include	"IAttributeReader.hpp"
#include	"ODBReference.hpp" 


namespace GS {
	class UniString;
}

namespace ADB {
	class AttributeSet;
	typedef ODB::ConstRef<AttributeSet> AttributeSetConstRef; 
}

namespace VBAttr {
	class Material;
	class PenTable;
	typedef ODB::ConstRef<PenTable> PenTableConstRef;
	typedef ODB::ConstRef<Material>	MaterialConstRef;
}

namespace Modeler {
	class MaterialData; 
}

class UMAT;
struct FMAT; 

class	VBATTRIBUTES_DLL_EXPORT	AttributeReader : public Modeler::IAttributeReader
{
private:
	ADB::AttributeSetConstRef	m_attributeSet;
	VBAttr::PenTableConstRef	m_penTable;

public:
	AttributeReader (/*As if "Current Attribute Set" would be the construction parameter!*/); //try to avoid this constructor, see below for more preferred once:
	AttributeReader (const ADB::AttributeSetConstRef& attrSet);
	AttributeReader (const ADB::AttributeSetConstRef& attrSet, const VBAttr::PenTableConstRef& penTable);
	virtual ~AttributeReader (void);

	virtual GS::UniString									GetFillName (GSAttributeIndex fillInd) const override;
	virtual GSAttributeIndex								GetFillIndexByName (const GS::UniString& attrName) const override; 
	virtual	GSAttributeIndex								GetFillMaxInd () const override;			//-1 is error!
	virtual GSAttributeIndex								GetFirstEmptyFill () const override;
	virtual GS::AutoPtr <GX::Pattern::FillData>				GetFillData (GSAttributeIndex attrInd) const override;

	virtual GS::UniString									GetLineName (GSAttributeIndex lineInd) const override;
	virtual GSAttributeIndex								GetLineIndexByName (const GS::UniString& attrName) const override; 
	virtual	GSAttributeIndex								GetLineMaxInd () const override;			//-1 is error!
	virtual GS::AutoPtr <GX::Pattern::LineData>				GetLineData (GSAttributeIndex attrInd) const override; 

	virtual	USize											GetNumPen	() const override;
	virtual	GS::AutoPtr <Modeler::PenData> 					GetPenData	(short penInd) const override;
	
	virtual	GS::AutoPtr <Modeler::BuildingMaterialData>		GetBuildingMaterialData (GSAttributeIndex bmatInd) const override;
	
	virtual bool											ExistsMaterial (GSAttributeIndex matInd) const override;
	virtual GS::UniString									GetMaterialName (GSAttributeIndex matInd) const override;
	virtual GSAttributeIndex								GetMaterialIndexByName (const GS::UniString& attrName) const override; 
	virtual	GSAttributeIndex								GetMaterialMaxInd	() const override;		//-1 is error!
	virtual	GS::AutoPtr <Modeler::MaterialData> 			GetMaterialData	(GSAttributeIndex matInd, short texPictIndex = -1) const override;
	virtual GS::AutoPtr <Modeler::TextureData>				GetTextureData (GSAttributeIndex matInd, short texPictIndex) const override;

	//static:
	static GS::AutoPtr <Modeler::TextureData>				GetTextureDataFromMaterial (const VBAttr::MaterialConstRef& matAttrRef, short texPictIndex); 
	static GS::AutoPtr <Modeler::TextureData>				GetTextureDataFromMaterial (const VBAttr::Material& mater, short texPictIndex); 

	virtual GS::AutoPtr<Modeler::IAttributeReader>			Clone () const override;
};

VBATTRIBUTES_DLL_EXPORT
	void	ConvertMaterToUMAT (const VBAttr::Material& mater, UMAT &aumat, GSAttributeIndex genfrom);

VBATTRIBUTES_DLL_EXPORT
	void	ConvertMaterialDataToMater (const Modeler::MaterialData &matData, VBAttr::Material& mater);

VBATTRIBUTES_DLL_EXPORT
	void	ConvertMaterToFMAT (const VBAttr::Material& mater, FMAT &afmat);

#endif	// ATTRIBUTEREADER_HPP 
