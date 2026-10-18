// *********************************************************************************************************************
// Description:		Utility functions for the Model3D.
//
// Module:			Model3D
// Namespace:		-
// Contact person:	FGY, BA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_Modeler_MODEL3DUTILS_HPP)
#define GS_Modeler_MODEL3DUTILS_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include	"Model3D/Model3D.hpp"
#include	"Polygon2D.hpp"
#include	"IrregularPolygon2D.hpp"



namespace Geometry {
	struct Polygon2DData;
}

// --- Function declarations -------------------------------------------------------------------------------------------

MODEL3D_DLL_EXPORT
void	MODEL3D_CALL DLgetPVerts (const Modeler::MeshBody& body, Int32 apedg, Int32 *vert1, Int32 *vert2);

Int32	DLLastExistingBody (const Modeler::Model3DViewer& oViewer);


MODEL3D_DLL_EXPORT
void	MODEL3D_CALL MeshBodyPolygonToPolygon2DData (const Modeler::MeshBody*	body,
													 Int32						ipgon,
													 Geometry::Polygon2DData*	poly2D,
													 const TRANMAT&				tran = Geometry::IdentityTranMat);

MODEL3D_DLL_EXPORT
Geometry::IrregularPolygon2D	MODEL3D_CALL	MeshBodyPolygonToIrregularPolygon2D (const Modeler::MeshBody*	body,
																					 Int32						ipgon,
																					 const TRANMAT&				tran = Geometry::IdentityTranMat);

MODEL3D_DLL_EXPORT
Geometry::MultiPolygon2D	MODEL3D_CALL	MeshBodyPolygonToMultiPolygon2D (const Modeler::MeshBody*	body,
																			 Int32						ipgon,
																			 const TRANMAT&				tran = Geometry::IdentityTranMat);

MODEL3D_DLL_EXPORT
Geometry::Polygon2D		MODEL3D_CALL	 MeshBodyPolygonToPolygon2D (const Modeler::MeshBody*	body,
																	 Int32						ipgon,
																	 const TRANMAT&				tran = Geometry::IdentityTranMat);

enum PolygonSelection {
	FacingPolygons = 1,
	BackFacingPolygons = 2,
	GravityPolygons = 4,
	NotGravityPolygons = 8,
	AllPolygons = 3
};

struct BodyPolygonIndex {
	UInt32 bodyIdx;
	UInt32 ipgon;

	BodyPolygonIndex (UInt32 bodyIdx, UInt32 ipgon) : bodyIdx (bodyIdx), ipgon (ipgon) {}
};

MODEL3D_DLL_EXPORT
bool   MODEL3D_CALL	GetBodyLineIntersections (const Modeler::ConstMeshBodyPtr&		bodyPtr,
											  const F_Box3D&					bodyFBbox,
											  ULong								bodyIdx,
											  const TRANMAT&					elemTrafo,
											  const Coord3D&					point,
											  const Vector3D&					dir,
											  PolygonSelection					polygonSelection,
											  GS::Array<Coord3D>*				xPoints,
											  GS::Array<BodyPolygonIndex>*		bodyPolygonIndices,
											  GS::Array<Vector3D>*				normVect);

MODEL3D_DLL_EXPORT
bool   MODEL3D_CALL	GetElemLineIntersections (const Modeler::ConstElemPtr&		elem,
											  const Coord3D&					point,
											  const Vector3D&					dir,
											  PolygonSelection					polygonSelection,
											  GS::Array<Coord3D>*				xPoints,
											  GS::Array<BodyPolygonIndex>*		bodyPolygonIndices,
											  GS::Array<Vector3D>*				normVect);


// ID manipulation 

enum UsedBitField {
	WholeRange		= 0,
	FirstByte		= 1,
	LastThreeBytes	= 2
};

template<UInt32 sizeOf>
struct GetBigEnoughUnsigned{
};
template<>	struct GetBigEnoughUnsigned<1>{	typedef unsigned char	Type;	};
template<>	struct GetBigEnoughUnsigned<2>{	typedef UInt16			Type;	};
template<>	struct GetBigEnoughUnsigned<4>{	typedef UInt32			Type;	};

template<typename T>
struct GetUnsigned {
	typedef typename GetBigEnoughUnsigned<sizeof (T)>::Type Type;
};

template <typename MaskType = UInt32, typename ShiftType = unsigned char>
class BitFieldTran {
private:
	typedef typename GetUnsigned<MaskType>::Type	UnsignedMaskType;
	typedef typename GetUnsigned<ShiftType>::Type	UnsignedShiftType;

	UnsignedMaskType		mask; // Why to force unsigned? E.g. (signed)0xFF >> 8 != (unsigned)0xFF >> 8
	UnsignedShiftType		shift;
	UnsignedMaskType		maskComplement;

	struct CheckConsitencyAfterConstruction {
		const BitFieldTran* This;
		CheckConsitencyAfterConstruction (const BitFieldTran* This) : This (This) {}
		~CheckConsitencyAfterConstruction ()
		{
			DBASSERT (  (	(This->GetMask ()) & (This->GetMaskComplement ())		)	== 0);	// orthogonal
			DBASSERT (	(	~((This->GetMask ()) | (This->GetMaskComplement ()))	)	== 0);	// complete (spans over all bits)
		}
	};

public:
	BitFieldTran () : shift (0), maskComplement (0)
	{
		CheckConsitencyAfterConstruction _check (this);
		mask = static_cast<UnsignedMaskType>(-1); // == 0xFF...FF depending on the size of MaskType
	}
	BitFieldTran (UsedBitField range) : mask (static_cast<UnsignedMaskType>(-1)), shift (0), maskComplement (0)
	{
		CheckConsitencyAfterConstruction _check (this);
		switch (range) {
		case FirstByte:
			maskComplement		= mask - 0xFF;
			mask				= 0xFF;
			shift				= 0;
			break;
		case LastThreeBytes:
			{
				const unsigned char wholeByteRange = sizeof (MaskType);
				static_assert (wholeByteRange > 3, "wholeByteRange <= 3");
				maskComplement	= mask >> (3 * 8);
				mask			= mask - maskComplement;
				shift			= (wholeByteRange - 3) * 8; // >=0 (see static_assert above)
			}
			break;
		}
	}
	MaskType	GetMask ()							const	{return static_cast<MaskType> (mask);							}
	MaskType	GetMaskComplement ()				const	{return static_cast<MaskType> (maskComplement);					}
	MaskType	Get (UnsignedMaskType bitfield)		const	{return static_cast<MaskType> ((bitfield & mask) >> shift);		}

	MaskType	Set (UnsignedMaskType originalValue, UnsignedMaskType newValue) const	
	{
		DBASSERT ( (newValue & ~(mask >> shift)) == 0); // checking possible data loss
		return static_cast<MaskType> ((originalValue & maskComplement) | ( (newValue << shift) & mask));
	};

};

template<class MeshBodyType>
Modeler::PolygonId	GetPackedPolygonId (	const MeshBodyType&										body,
											UInt32												polyIdx,
											const BitFieldTran<Modeler::PolygonId::ValueType>&	tran )
{
	return GetPackedPolygonId (body.GetPolygonId (polyIdx).GetValue (), tran);;
}

MODEL3D_DLL_EXPORT
Modeler::PolygonId	MODEL3D_CALL GetPackedPolygonId (	const Modeler::PolygonId&							polygonIdPacked,
														const BitFieldTran<Modeler::PolygonId::ValueType>&	tran );

MODEL3D_DLL_EXPORT
void				MODEL3D_CALL SetPackedPolygonId (	Modeler::PolygonId&									polygonIdPacked,
														const Modeler::PolygonId&							polygonIdToPack,
														const BitFieldTran<Modeler::PolygonId::ValueType>&	tran );

template<class MeshBodyType>
void			SetPackedPolygonId (	MeshBodyType&											body,
										UInt32												polyIdx,
										const Modeler::PolygonId&							polygonId,
										const BitFieldTran<Modeler::PolygonId::ValueType>&	tran )
{
	Modeler::PolygonId transformedId;
	SetPackedPolygonId (transformedId, polygonId, tran);
	body.SetPolygonId (polyIdx, transformedId.GetValue ());
}

#endif  // GS_Modeler_MODEL3DUTILS_HPP
