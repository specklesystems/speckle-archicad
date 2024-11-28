// PolygonAttributes

#ifndef POLYGONATTRIBUTES_HPP
#define POLYGONATTRIBUTES_HPP
#pragma once

// from GDL
#include	"GDLWrapping.hpp"

// from ModelD
#include	"Model3D/model.h"
#include	"Model3D/Model3DExport.h"
#include	"Model3D/ModelerAttributes.hpp"


enum MPUIDCalculation {
	CalculateMPUIDs,
	PreserveMPUIDs
};

namespace Modeler {

struct ModelOLookup;
struct ModelILookup;

class MODEL3D_DLL_EXPORT PolygonAttributes {
public:
	enum Status {
		InvisiblePolygon = 0x00001,
		CurvedPolygon = 0x00002,
		ConcavePolygon = 0x00010,
		PolygonHasHole = 0x00000020,
		ComplexPolygon = 0x00030
	};

private:
	Wrapping			wrapping;			/* Texture projection type				*/
	STATL				status;
	Int32				iumat;				/* Material or light index				*/
	Int32				irtxt;				/* raster texture						*/
	Int32				mpuid;				/* Unique identifier */
	Int32				ftpar;				/* First texture projection parameter	*/

	void SetOrClearStatusMask (STATL mask, bool set)
	{
		if (set)
			SET_FLAGS (status, mask);
		else
			CLR_FLAGS (status, mask);
	}

public:

	PolygonAttributes () :
		wrapping (W_FROMBODY, W_NOFLAGS),
		status (0),
		iumat (0),
		irtxt (0),
		mpuid (0),
		ftpar (0)
	{
	}

	bool	IsCurved () const					{ return (status & CurvedPolygon) != 0; }
	void	SetCurved (bool curved)				{ SetOrClearStatusMask (CurvedPolygon, curved); }

	bool	IsConcave () const					{ return (status & ConcavePolygon) != 0; }
	void	SetConcave (bool concave)			{ SetOrClearStatusMask (ConcavePolygon, concave); }

	bool	IsComplex () const					{ return (status & ComplexPolygon) != 0; }
	void	SetComplex (bool complex)			{ SetOrClearStatusMask (ComplexPolygon, complex); }

	bool	IsInvisible () const				{ return (status & InvisiblePolygon) != 0; }
	void	SetInvisible (bool invisible)		{ SetOrClearStatusMask (InvisiblePolygon, invisible); }

	bool	HasHole () const					{ return (status & PolygonHasHole) != 0; }
	void	SetHasHole (bool hasHole)			{ SetOrClearStatusMask (PolygonHasHole, hasHole); }

	bool	IsCut () const						{ return HAS_ANY_FLAGS (status, ON_CUT_BIT | ON_MODEL_CUT_BIT | ON_SECT_CUT_SPEC_BIT); }

	void			SetWrapping (const Wrapping& wrapping) { this->wrapping = wrapping; }
	const Wrapping& GetWrapping () const { return wrapping; }

	void	SetStatus (STATL status)					{ this->status = status; }
	STATL	GetStatus () const							{ return status; }

	void	SetMaterialIndex (Int32 iumat)				{ this->iumat = iumat; }
	Int32	GetMaterialIndex () const					{ return iumat; }

	void	SetTextureIndex (Int32 irtxt)				{ this->irtxt = irtxt; }
	Int32	GetTextureIndex () const					{ return irtxt; }

	bool	HasTextureParameters () const;
	bool	HasTextureCoordinateSystem () const;
	bool	HasTextureUVs () const;

	void	SetFirstTextureParameterIndex (Int32 ftpar) { this->ftpar = ftpar; }
	Int32	GetFirstTextureParameterIndex () const;

	void	SetMpuid (Int32 mpuid) { this->mpuid = mpuid; }
	Int32	GetMpuid () const { return mpuid; }

	bool	operator== (const PolygonAttributes& rhs) const;
	bool	operator!= (const PolygonAttributes& rhs) const;

	GSErrCode		QuickRead (GS::IChannel& ic, ModelILookup& lookup, Modeler::Attributes::Modifier* attrModifier, const Modeler::IAttributeReader* attReader);
	GSErrCode		QuickWrite (GS::OChannel& oc, ModelOLookup& lookup, const Modeler::Attributes::Viewer* attrViewer) const;
};

} // namespace Modeler

#endif // POLYGONATTRIBUTES_HPP
