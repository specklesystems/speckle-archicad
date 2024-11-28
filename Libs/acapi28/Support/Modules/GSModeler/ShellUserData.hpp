// *********************************************************************************************************************
// Description:		ShellUserData.hpp
//
// Module:			Generator
// Namespace:		Modeler
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (SHELLUSERDATA_HPP)
#define SHELLUSERDATA_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSModeler
#include	"GSModelerPrivExp.h"
#include	"Model3D/Elem.hpp"

// from GSRoot
#include	"Array.hpp"

// from Geometry
#include	"Sector3DData.h"
#include	"TRANMAT.h"


// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Modeler {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


class GSMODELER_PRIVATE_EXPORT ShellUserData : public BaseUserData
{
	DECLARE_DYNAMIC_CLASS_INFO (ShellUserData)

public:
	enum StatusType {
		BegShapePolygon		= 1,
		EndShapePolygon,
		ExtrudedEdge,
		RevolvedEdge		= ExtrudedEdge,
		RuledEdge			= ExtrudedEdge,
		ThickeningEdge,							// sector starts from the surface
		GeneralCutting,
		CutPolygonVertexCutting
	};

	enum StructuralType {
		Surface				= 0,
		Thickening			= 1
	};

	struct StatusPoint {
		Coord3D		coord;
		UInt8		statusType;
		UInt8		structuralType;
		UInt32		id1;
		UInt32		id2;
		UInt32		auxiliaryId;				// determined by the generator algorithm

		StatusPoint ():
			statusType		(0),
			structuralType	(0),
			id1				(0),
			id2				(0),
			auxiliaryId		(0)
		{
			coord.x			= 0.0;
			coord.y			= 0.0;
			coord.z			= 0.0;
		}

		bool	operator== (const StatusPoint &rOp) const {
			return statusType		== rOp.statusType &&
				   structuralType	== rOp.structuralType &&
				   id1				== rOp.id1 &&
				   id2				== rOp.id2 &&
				   auxiliaryId		== rOp.auxiliaryId &&
				   Geometry::LenVector3D (coord - rOp.coord) < SmallEps;
		}
		bool	operator!= (const StatusPoint &rOp) const {
			return !(*this == rOp);
		}
	};

	struct StatusEdge {
		Sector3D	sector;
		bool		arcSegment;
		UInt8		statusType;
		UInt8		structuralType;
		UInt8		parentType;					// statusType of the parent
		UInt32		id1;
		UInt32		id2;
		UInt32		auxiliaryId;				// determined by the generator algorithm

		StatusEdge ():
			arcSegment		(false),
			statusType		(0),
			structuralType	(0),
			parentType		(0),
			id1				(0),
			id2				(0),
			auxiliaryId		(0)
		{
			sector.c1.x		= 0.0;
			sector.c1.y		= 0.0;
			sector.c1.z		= 0.0;
			sector.c2.x		= 0.0;
			sector.c2.y		= 0.0;
			sector.c2.z		= 0.0;
		}

		bool	operator== (const StatusEdge &rOp) const {
			return arcSegment		== rOp.arcSegment &&
				   statusType		== rOp.statusType &&
				   structuralType	== rOp.structuralType &&
				   parentType		== rOp.parentType &&
				   id1				== rOp.id1 &&
				   id2				== rOp.id2 &&
				   auxiliaryId		== rOp.auxiliaryId &&
				   Geometry::LenVector3D (sector.c1 - rOp.sector.c1) < SmallEps &&
				   Geometry::LenVector3D (sector.c2 - rOp.sector.c2) < SmallEps;
		}
		bool	operator!= (const StatusEdge &rOp) const {
			return !(*this == rOp);
		}
	};

	GS::Array<StatusPoint>	sPoints;
	GS::Array<StatusEdge>	sLines;

	bool					isSurfaceOffsetable;

	ShellUserData ()
	: BaseUserData ()
	{
		isSurfaceOffsetable = false;
	}

	virtual	~ShellUserData (void);

	virtual	ShellUserData*	Clone (void) const override;
	virtual void			Print(GS::OChannel& oc) const override;
	virtual bool			operator== (const BaseUserData& rhs) const override;
	virtual ULong			GenerateHashValue (void) const override;
	virtual GSErrCode		QuickWrite (GS::OChannel& oc) const override;
	virtual GSErrCode		QuickRead (GS::IChannel& ic) override;
	virtual void			PrintAsTestCase (GS::OChannel& oc, const char* iVarName) const override;
	virtual void			WriteXML (GS::XMLOChannel& outXML) const override;
	virtual void			ReadXML (GS::XMLIChannel& inXML) override;

	virtual ShellUserData*	Clone (const TRANMAT& trafo) const override;

	void					Transform (const TRANMAT *tran);

	static GS::Guid			shellUserDataId;
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace Modeler

#endif
