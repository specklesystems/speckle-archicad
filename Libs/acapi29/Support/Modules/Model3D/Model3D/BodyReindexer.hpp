// *********************************************************************************************************************
// Description:		Copies and reindexes the attributes of an Elem
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	KG
//
// SG compatible
// *********************************************************************************************************************

#if !defined (BODY_REINDEXER_HPP)
#define BODY_REINDEXER_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"

// from GSModeler
#include	"Model3D/Model3DExport.h"
#include	"Model3D/ModelerAttributes.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------
namespace Modeler {
	class CandidateMeshBody;
	class CandidateNurbsBody;
}
// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace Modeler {

class MODEL3D_DLL_EXPORT BodyReindexer
{
private:
	GS::Array<GSAttributeIndex>	iumatLookup;
	GS::Array<Int32>			irtxtLookup;
	GS::Array<GSAttributeIndex>	iufilLookup;

	const Attributes::Viewer&	srcAttrViewer;
	Attributes::Modifier&		dstAttrModifier;
	const IAttributeReader*		attReader;

	Attributes::CompatibilityLimits compatibilityLimits;
	Attributes::CompatibilityLevel compatibilityLevel;

	void ReindexBody (CandidateMeshBody& body);


	void ReindexBody (CandidateNurbsBody& body);
	


	GSAttributeIndex TranslateFillIdx (GSAttributeIndex iufil);

	static bool CheckTexture (const RTXT *urtxt);
	
	Int32 TranslateTextureIdx (Int32 irtxt);

	GSAttributeIndex TranslateMaterialIdx (GSAttributeIndex iumat);

public:
	BodyReindexer  (const Attributes::Viewer& srcAttrViewer,
					Attributes::Modifier& dstAttrModifier,
					const IAttributeReader* attReader);

	template<typename BodyPtrContainer>
	void ReindexBodies (const BodyPtrContainer& bodies)
	{
		if (compatibilityLevel == Attributes::FullyCompatible)
			return;

		for (const auto& body : bodies) {
			ReindexBody (*body);
		}
	}
};

}		// namespace Modeler


#endif
