// *********************************************************************************************************************
// Description:		Attribute accessing interface
//
// Module:			GSModeler2D
// Namespace:		Modeler
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (IATTRIBUTEREADER_HPP)
#define IATTRIBUTEREADER_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------


// from GSRoot
#include	"Definitions.hpp"
#include	"Owner.hpp"
#include	"GSDebug.hpp"

// from GSModeler2D
#include	"GSModeler2DExport.h"
#include	"PenData.hpp"
#include	"BuildingMaterialData.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS {
	class UniString;
}

namespace GX {
	namespace Pattern {
		class FillData; 
		class LineData; 
	}
}

namespace ADB {
	class AttributeIndex;
}

namespace Modeler {
	class TextureData;
	class MaterialData;


	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------


	class	GSMODELER2D_DLL_EXPORT	IAttributeReader 
	{
	public:
		virtual GS::UniString									GetFillName (const ADB::AttributeIndex& fillInd) const = 0;
		virtual ADB::AttributeIndex								GetFillIndexByName (const GS::UniString& attrName) const = 0;
		virtual ADB::AttributeIndex								GetFirstEmptyFill () const = 0;
		virtual GS::Owner<GX::Pattern::FillData>				GetFillData (const ADB::AttributeIndex& fillInd) const = 0;
		virtual void											EnumerateFills (const std::function<void (const ADB::AttributeIndex&)>& processor) const = 0;
		
		virtual GS::UniString									GetLineName (const ADB::AttributeIndex& lineInd) const = 0;
		virtual ADB::AttributeIndex								GetLineIndexByName (const GS::UniString& attrName) const = 0;
		virtual GX::Pattern::LineData							GetLineData (const ADB::AttributeIndex& lineInd) const = 0;
		virtual void											EnumerateLines (const std::function<void (const ADB::AttributeIndex&)>& processor) const = 0;

		virtual	USize											GetNumPen	() const = 0;
		virtual	Modeler::PenData								GetPenData	(short penInd) const = 0;

		virtual	Modeler::BuildingMaterialData					GetBuildingMaterialData (const ADB::AttributeIndex& bmatInd) const = 0;

		virtual bool											ExistsMaterial (const ADB::AttributeIndex& matInd) const = 0;
		virtual GS::UniString									GetMaterialName (const ADB::AttributeIndex& matInd) const = 0;
		virtual ADB::AttributeIndex								GetMaterialIndexByName (const GS::UniString& attrName) const = 0;
		virtual	GS::Owner<Modeler::MaterialData> 				GetMaterialData	(const ADB::AttributeIndex& matInd, short texPictIndex = -1) const = 0;
		virtual void											EnumerateMaterials (const std::function<void (const ADB::AttributeIndex&)>& processor) const = 0;
		virtual GS::Owner<Modeler::TextureData>					GetTextureData (const ADB::AttributeIndex& matInd, short texPictIndex) const = 0;

		// The AttributeReader should handle sharing the data between the cloned instances (i.e. the data members should be Refs)
		virtual GS::Owner<IAttributeReader>						Clone () const = 0;

		virtual ~IAttributeReader (void);
	};


	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace Modeler

#endif	// IATTRIBUTEREADER_HPP
