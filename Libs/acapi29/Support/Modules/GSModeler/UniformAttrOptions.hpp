// *********************************************************************************************************************
// Description:		Options for Section, Elevation, Interior Elevation and 3D document presentation
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	FGY
//
// SG compatible
// *********************************************************************************************************************
#ifndef GS_MODELER_UNIFORMATTROPTIONS_HPP
#define GS_MODELER_UNIFORMATTROPTIONS_HPP
#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "Object.hpp"

// from GSModeler
#include "GSModelerExport.h"

// from GSUtils
#include "GSUtilsDefs.h"

// from CADInfrastructure
#include "ADBAttributeIndex.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace Modeler {


class GSMODELER_DLL_EXPORT UniformAttrOptions : public GS::Object
{
	DECLARE_CLASS_INFO
public:

	enum CutSurfFills {
		VectorFilles		= 1,
		UniformMaterial		= 2,
		OwnMaterial			= 3,
		OwnShadedMaterial	= 4
	};

	struct GSMODELER_DLL_EXPORT UncutSurfaceFill {
		enum class Type : short {
			UniformPenColor = 1,
			SurfaceColorShaded = 2,
			SurfaceColorNonShaded = 3,
			SurfaceTextureShaded = 4,
			SurfaceTextureNonShaded = 5
		};

		bool	isUsed		= false;
		Type	type		= Type::UniformPenColor;
		short	bkgPenIdx	= 0;

		bool IsUniformPenColored () const;
		bool IsSurfaceColored () const;
		bool IsSurfaceTextured () const;
		bool IsShaded () const;
		bool IsNonShaded () const;
	};

	enum HiddenEdgeVisibility {
		HideHiddenEdges,
		ShowHiddenEdges
	};

	enum OnCutPlaneVisibility {
		DontShowOnCutPlanes,
		ShowOnCutPlanes
	};

	CutSurfFills		fillCutSurfacesWith;


	bool	 			shouldUseUniformCutAttributes;	// or each one's own
	short				uniformLineIdx;
	short				uniformFillPenIdx;
	short				uniformFillBkgPenIdx;

	UncutSurfaceFill	uncutSurfaceFill;

	bool				shouldUseElemPen;
	short				elemPenIdx;

	ADB::AttributeIndex	shadFillIdx;
	short				shadFillPenIdx;
	short				shadFillBkgPenIdx;
	short				shadContPenIdx;

	HiddenEdgeVisibility	hiddenEdgeVisibility;
	OnCutPlaneVisibility	onCutPlaneVisibility;
	ADB::AttributeIndex		hiddenEdgeLineType;
	short					hiddenEdgeLinePen;

	UniformAttrOptions ();

	void Clear ();

	// Object I/O
	GSErrCode	Read (GS::IChannel& ic) override;
	GSErrCode	Write (GS::OChannel& oc) const override;

	GSErrCode	ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode	ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode	ReadVersion3 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode	WriteVersion3 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

	GSErrCode	ReadVersion4 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode	WriteVersion4 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

	// XML I/O
	GSErrCode	ReadXML (GS::XMLIChannel& ic);
	GSErrCode	WriteXML (GS::XMLOChannel& oc) const;

	// Legacy I/O
	GSErrCode	ReadLegacyVersion (GS::IChannel& ic);

};

}

#endif //GS_MODELER_UNIFORMATTROPTIONS_HPP
