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
#include	"AutoPtr.hpp"
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

namespace Modeler {
	class TextureData;
	class MaterialData;


	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------


	class	GSMODELER2D_DLL_EXPORT	IAttributeReader 
	{
	public:
		virtual GS::UniString									GetFillName (GSAttributeIndex fillInd) const = 0;
		virtual GSAttributeIndex								GetFillIndexByName (const GS::UniString& attrName) const = 0; 
		virtual	GSAttributeIndex								GetFillMaxInd	() const = 0;			//-1 is error!
		virtual GSAttributeIndex								GetFirstEmptyFill () const = 0;
		virtual GS::AutoPtr <GX::Pattern::FillData>				GetFillData (GSAttributeIndex fillInd) const = 0;
		
		virtual GS::UniString									GetLineName (GSAttributeIndex lineInd) const = 0;
		virtual GSAttributeIndex								GetLineIndexByName (const GS::UniString& attrName) const = 0; 
		virtual	GSAttributeIndex								GetLineMaxInd	() const = 0;			//-1 is error!
		virtual GS::AutoPtr <GX::Pattern::LineData>				GetLineData (GSAttributeIndex lineInd) const = 0; 

		virtual	USize											GetNumPen	() const = 0;
		virtual	GS::AutoPtr <Modeler::PenData> 					GetPenData	(short penInd) const = 0;

		virtual	GS::AutoPtr <Modeler::BuildingMaterialData>		GetBuildingMaterialData (GSAttributeIndex bmatInd) const = 0; 

		virtual bool											ExistsMaterial (GSAttributeIndex matInd) const = 0;
		virtual GS::UniString									GetMaterialName (GSAttributeIndex matInd) const = 0;
		virtual GSAttributeIndex								GetMaterialIndexByName (const GS::UniString& attrName) const = 0; 
		virtual	GSAttributeIndex								GetMaterialMaxInd	() const = 0;			//-1 is error!
		virtual	GS::AutoPtr <Modeler::MaterialData> 			GetMaterialData	(GSAttributeIndex matInd, short texPictIndex = -1) const = 0;
		virtual GS::AutoPtr <Modeler::TextureData>				GetTextureData (GSAttributeIndex matInd, short texPictIndex) const = 0;

		// The AttributeReader should handle sharing the data between the cloned instances (i.e. the data members should be Refs)
		virtual GS::AutoPtr<IAttributeReader>					Clone () const = 0;

		virtual ~IAttributeReader (void);
	};


	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace Modeler

#endif	// IATTRIBUTEREADER_HPP
