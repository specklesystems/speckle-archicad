// *********************************************************************************************************************
// Description:		Type that represents a local coordinate system with wrapping.
//
// Module:			Model3D
// Namespace:
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#if !defined (LOCALCOORDSYS_HPP)
#define LOCALCOORDSYS_HPP

// from Geometry
#include "TM.h"

// from GDL
#include "GDLWrapping.hpp"

#include "Model3D/Model3DExport.h"

// Stores a local coordinate system (origin POINT and axis VECTORS) with wrapping information.
struct MODEL3D_DLL_EXPORT LocalCoordSys {
	Wrapping			wrapping;						// short value, uninterpreted here (see GDLWrapping.hpp for wrapping values)
	Coord3D				origin;							// origin point of the LCS
	Vector3D			xaxis, yaxis, zaxis;			// 3 axis vectors

	// wrapping == 0 indicates that the stored LCS is invalid, see @IsValid
	// default constructor creates an invalid LCS
	LocalCoordSys () = default;

	// Creates a LCS with the given coordinates.
	// Warning! Does not check that @w is valid.
	LocalCoordSys (Wrapping w, Coord3D o, Vector3D x, Vector3D y, Vector3D z)
		: wrapping (w), origin (o), xaxis (x), yaxis (y), zaxis (z) 
	{
	}

	// Returns whether the LCS is valid.
	inline bool IsValid () const 
	{
		return !wrapping.HasMethod (W_UNKNOWN);
	}

	// Invalidates the LCS.
	inline void SetInvalid() 
	{
		wrapping = Wrapping::NoWrapping;
	}

	inline void Transform (const TRANMAT* tran) 
	{
		if (!IsValid ())
			return;
		
		if (tran == nullptr)
			return;

		xaxis += origin;
		yaxis += origin;
		zaxis += origin;
		
		origin = Geometry::TransformPoint (*tran, origin);
		xaxis = Geometry::TransformPoint (*tran, xaxis);
		yaxis = Geometry::TransformPoint (*tran, yaxis);
		zaxis = Geometry::TransformPoint (*tran, zaxis);

		xaxis -= origin;
		yaxis -= origin;
		zaxis -= origin;
	}

	bool operator == (const LocalCoordSys& rhs) const;

	GSErrCode WriteXML (GS::XMLOChannel& outXML, const char* tagname = nullptr) const;
	GSErrCode ReadXML (GS::XMLIChannel& inXML, const char* tagname = nullptr);
};

#endif // LOCALCOORDSYS_HPP
