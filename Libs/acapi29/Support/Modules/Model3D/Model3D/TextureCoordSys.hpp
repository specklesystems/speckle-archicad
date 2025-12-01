// *********************************************************************************************************************
// Description:		TextureCoordSys
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	boB
//
// SG compatible
// *********************************************************************************************************************

#if !defined(TEXTURECOORDSYS_HPP)
#define TEXTURECOORDSYS_HPP

// from Model3D
#include	"Model3D/Model3DPrivExp.h"

// from Geometry
#include	"Vector3D.hpp"

const GS::USize NCOOR = 4;

struct TRANMAT;

namespace Modeler {


// ---------------------------------------------------------------------------------------------------------------------
// Represents a coordinate system that describes the position and orientation of a texture mapping primitive.
// @origin is the origin of the coordinate system and
// @point[XYZ] are the ENDPOINTS of x, y and z axes respectively.
// 
// Note. Endpoint-based representation is historical here. Many newer parts of the code work with an origin
// point and 3 unit vectors for axes (using different data structures).
// ---------------------------------------------------------------------------------------------------------------------
struct MODEL3D_PRIVATE_EXPORT TextureCoordSys {
	static const TextureCoordSys AxisAligned;

	Geometry::Coord3D origin;
	Geometry::Coord3D pointX;
	Geometry::Coord3D pointY;
	Geometry::Coord3D pointZ;

	TextureCoordSys ()
		: origin ()
		, pointX ()
		, pointY ()
		, pointZ ()
	{
		// do nothing
	}

	TextureCoordSys (const Coord3D& o, const Coord3D& px, const Coord3D& py, const Coord3D& pz)
		: origin (o)
		, pointX (px)
		, pointY (py)
		, pointZ (pz)
	{
		// do nothing
	}

	bool operator== (const TextureCoordSys& coordSys) const noexcept;

	GSErrCode Read	(GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	void ReadXML	(GS::XMLIChannel& inXML);
	void WriteXML	(GS::XMLOChannel& outXML) const;
};


MODEL3D_PRIVATE_EXPORT
bool	MOD3D_PRIV	AreTextureCoordSysEqual (const Modeler::TextureCoordSys& tcs1, const Modeler::TextureCoordSys& tcs2, double eps = SmallEps);

MODEL3D_PRIVATE_EXPORT
void	MOD3D_PRIV	TransformTextureCoordSys (Modeler::TextureCoordSys& coords, const TRANMAT& tran);

}

#endif // TEXTURECOORDSYS_HPP
