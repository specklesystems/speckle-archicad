// *********************************************************************************************************************
// Description:		Boundary representation of a body, boundary is described with NURBS curves and surfaces
//					Common base class for CandidateNurbsBody and NurbsBody. Defines their common (const) operations.
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	CsetA
//
// SG compatible
// *********************************************************************************************************************

#ifndef NURBS_BODY_BASE_HPP
#define NURBS_BODY_BASE_HPP

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------


// from GSRoot
#include	"Definitions.hpp"
#include	"SharedObject.hpp"
#include	"OptionalOnHeap.hpp"

// from Brep
#include	"NurbsBrep.hpp"

// from Modeler
#include	"Model3D/Model3DExport.h"
#include	"Model3D/TextureCoordSys.hpp"
#include	"Model3D/CheckTask.hpp"
#include	"Model3D/PrimitiveId.hpp"
#include	"Model3D/BodyLevelAttrs.hpp"
#include	"Model3D/UserDataContainer.hpp"

#include	"NurbsSmoothnessInterval.hpp"
#include	"NurbsVertexAttributes.hpp"
#include	"NurbsEdgeAttributes.hpp"
#include	"NurbsFaceAttributes.hpp"

// from Geometry
#include	"Vector3D.hpp"
#include	"Box3DData.h"
#include	"NurbsCurve2D.hpp"
#include	"NurbsCurve3D.hpp"
#include	"NurbsSurface.hpp"


// from GDL
#include	"GDLWrapping.hpp"

// Predeclarations

namespace BrepOperations {
	class NurbsBrepWithLibData;
}

namespace Modeler {

typedef PrimitiveId<Brep::NurbsVertex>				NurbsVertexId;
typedef PrimitiveId<Brep::NurbsEdge>				NurbsEdgeId;
typedef PrimitiveId<Brep::NurbsFace>				NurbsFaceId;

class ConstNurbsEdgeOfFaceIterator;
class ConstNurbsFaceOfEdgeIterator;

using OptionalUserDataContainer = GS::OptionalOnHeap<UserDataContainer>;

}

// Types

namespace Modeler {


struct MODEL3D_DLL_EXPORT NurbsVertexData {
	static	GS::ClassInfo	classInfo;

private:
	void ReadVersion1 (GS::IChannel& ic);
	void WriteVersion1 (GS::OChannel& oc) const;

public:

	NurbsVertexAttributes	vertexAttributes;
	NurbsVertexId			vertexId;

	NurbsVertexData () :
		vertexAttributes (NurbsVertexAttributes::Hardness::Soft),
		vertexId ()
	{
	}

	NurbsVertexData (const NurbsVertexAttributes& va, const NurbsVertexId& id)
		: vertexAttributes (va)
		, vertexId (id)
	{
		// do nothing
	}

	bool	operator== (const NurbsVertexData& other) const;
	bool	operator!= (const NurbsVertexData& other) const;
	void	Read (GS::IChannel& ic);
	void	Write (GS::OChannel& oc) const;
	void	QuickRead (GS::IChannel& ic);
	void	QuickWrite (GS::OChannel& oc) const;
};


struct MODEL3D_DLL_EXPORT NurbsEdgeData {
	static	GS::ClassInfo	classInfo;

private:
	void ReadVersion1 (GS::IChannel& ic);
	void WriteVersion1 (GS::OChannel& oc) const;

public:
	NurbsEdgeAttributes	edgeAttributes;
	NurbsEdgeId			edgeId;

	NurbsEdgeData () :
		edgeAttributes (),
		edgeId ()
	{
	}

	NurbsEdgeData (const NurbsEdgeAttributes& ea, const NurbsEdgeId& id)
		: edgeAttributes (ea)
		, edgeId (id)
	{
		// do nothing
	}

	bool	operator== (const NurbsEdgeData& other) const;
	bool	operator!= (const NurbsEdgeData& other) const;
	void	Read (GS::IChannel& ic);
	void	Write (GS::OChannel& oc) const;
	void	QuickRead (GS::IChannel& ic);
	void	QuickWrite (GS::OChannel& oc) const;
};


struct MODEL3D_DLL_EXPORT NurbsFaceData {
	static	GS::ClassInfo	classInfo;

private:
	void ReadVersion1 (GS::IChannel& ic);
	void WriteVersion1 (GS::OChannel& oc) const;

public:
	NurbsFaceAttributes	faceAttributes;
	NurbsFaceId			faceId;

	NurbsFaceData () :
		faceAttributes (),
		faceId ()
	{
	}

	NurbsFaceData (const NurbsFaceAttributes& fa, const NurbsFaceId& id)
		: faceAttributes	(fa)
		, faceId			(id)
	{
		// do nothing
	}

	bool	Equals (const NurbsFaceData& other, double eps) const;
	void	Read (GS::IChannel& ic);
	void	Write (GS::OChannel& oc) const;
	void	QuickRead (GS::IChannel& ic, ModelILookup& lookup, Modeler::Attributes::Modifier* attrModifier, const Modeler::IAttributeReader* attReader);			// no version, no check
	void	QuickWrite (GS::OChannel& oc, ModelOLookup& lookup, const Modeler::Attributes::Viewer* attrViewer) const;	// no version, no check

};

using  NurbsVertexDataContainerT = GS::ArrayFB<NurbsVertexData, Brep::NurbsBrep::NurbsVertexAllocCount>;
using  NurbsEdgeDataContainerT = GS::ArrayFB<NurbsEdgeData, Brep::NurbsBrep::NurbsEdgeAllocCount>;
using  NurbsFaceDataContainerT = GS::ArrayFB<NurbsFaceData, Brep::NurbsBrep::NurbsFaceAllocCount>;

////////////////////////////////////////////////////////////////////////////////
// NurbsBodyBase
////////////////////////////////////////////////////////////////////////////////

class MODEL3D_DLL_EXPORT NurbsBodyBase : public GS::SharedObject {
private:
	friend class ConstNurbsEdgeOfFaceIterator;
	friend class ConstNurbsFaceOfEdgeIterator;
	
	class MODEL3D_DLL_EXPORT NurbsBrepWithLibDataWrapper {
		Owner<BrepOperations::NurbsBrepWithLibData> nurbsBrepWithLibData;
	public:
		NurbsBrepWithLibDataWrapper ();
		NurbsBrepWithLibDataWrapper (const NurbsBrepWithLibDataWrapper& src);
		NurbsBrepWithLibDataWrapper (NurbsBrepWithLibDataWrapper&& src);
		NurbsBrepWithLibDataWrapper (BrepOperations::NurbsBrepWithLibData&& src);

		NurbsBrepWithLibDataWrapper& operator= (const NurbsBrepWithLibDataWrapper& rhs);
		NurbsBrepWithLibDataWrapper& operator= (NurbsBrepWithLibDataWrapper&& rhs);

		const Brep::NurbsBrep& GetBrep () const;
		Brep::NurbsBrep& ModifyBrep ();
		const BrepOperations::NurbsBrepWithLibData& GetBrepWithLibData () const;
		BrepOperations::NurbsBrepWithLibData& GetBrepWithLibData ();

		ULong	GetUsedBytes	() const;
		ULong	GetHeapUsedBytes() const;
	
		void	QuickRead		(GS::IChannel& ic);
		void	QuickWrite		(GS::OChannel& oc) const;
		void	QuickReadCore	(GS::IChannel& ic);
		void	QuickWriteCore	(GS::OChannel& oc) const;

		~NurbsBrepWithLibDataWrapper ();
	};

protected:

	// ================================
	//     Topological and geometrical subelements
	// ================================

	NurbsBrepWithLibDataWrapper	m_nurbsBrepWithLibData;

	// ================================
	//     Attributes for subelements
	// ================================
	NurbsVertexDataContainerT	m_vertexData;
	NurbsEdgeDataContainerT		m_edgeData;
	NurbsFaceDataContainerT		m_faceData;

	// ================================
	//     Status and attributes
	// ================================
	
	// Note. No surface status bit. A NURBS body is always a compound of solid lumps, lamina surface faces and wire edges.
	STATL	m_shadowStatus;
	
	NurbsBodyLevelAttrs m_attrs;

	// ================================
	//       Disabled methods
	// ================================
	bool operator== (const NurbsBodyBase&);			// Not clear if it would mean geometrical or data-structural equality.
													// Use Equals or implement geometrical comparison instead 

	// ================================
	//       Private methods
	// ================================
private:
	
	void CheckVertexAttributes	(const CheckControl& control, const NurbsVertexAttributes& vertexAttributes) const;
	void CheckEdgeAttributes	(const CheckControl& control, const NurbsEdgeAttributes& edgeAttributes) const;
	void CheckFaceAttributes	(const CheckControl& control, const NurbsFaceAttributes& faceAttributes, USize materialCount = 0) const;	


	// ================================
	//       Public methods
	// ================================
public:
	virtual ~NurbsBodyBase (void);

	bool Equals (const NurbsBodyBase& other, double eps = SmallEps) const;

	Box3D	GetBounds (const TRANMAT& tran = Geometry::IdentityTranMat) const;
	void	GetBounds (Box3D* bounds, const TRANMAT& tran = Geometry::IdentityTranMat) const;
	
	// Get
	const NurbsBodyLevelAttrs&		GetBodyLevelAttrs () const { return m_attrs; } 
	bool							IsEmpty				()	const	{ return GetBrep ().GetVertexCount () == 0; }
	bool							HasVisibleParts		()	const	{ return GetBrep ().GetFaceCount () != 0 || GetBrep ().GetEdgeCount () != 0; }	
	short							GetEdgePenIdx		()	const	{ return m_attrs.edgePenIdx;		}
	GSAttributeIndex				GetMaterialIdx		()	const	{ return m_attrs.materialIdx;		}

	STATL							GetShadowStatus	() const { return m_shadowStatus;		}
	NurbsSmoothnessInterval			GetSmoothness	() const { return m_attrs.smoothness;		}

	const Wrapping&					GetWrapping			()	const	{ return m_attrs.wrap;			}
	const TextureCoordSys&			GetTextureCoordSys	()	const	{ return m_attrs.textureCoordSys;	}
	TextureCoordSys					GetTextureCoordSys	(const TRANMAT& tran)	const;
	LineEliminationBehaviour		GetLineEliminationBehaviour () const { return m_attrs.lineEliminationBehaviour; }

	UInt32							GetVertexCount	()				const { return GetBrep ().GetVertexCount	();			}
	const Brep::NurbsVertex&		GetConstVertex	(UInt32 index)	const { return GetBrep ().GetConstVertex	(index);	}
	UInt32							GetEdgeCount	()				const { return GetBrep ().GetEdgeCount		();			}
	const Brep::NurbsEdge&			GetConstEdge	(UInt32 index)	const { return GetBrep ().GetConstEdge		(index);	}
	UInt32							GetTrimCount	()				const { return GetBrep ().GetTrimCount		();			}
	const Brep::NurbsTrim&			GetConstTrim	(UInt32 index)	const { return GetBrep ().GetConstTrim		(index);	}
	UInt32							GetLoopCount	()				const { return GetBrep ().GetLoopCount		();			}
	const Brep::NurbsLoop&			GetConstLoop	(UInt32 index)	const { return GetBrep ().GetConstLoop		(index);	}
	UInt32							GetFaceCount	()				const { return GetBrep ().GetFaceCount		();			}
	const Brep::NurbsFace&			GetConstFace	(UInt32 index)	const { return GetBrep ().GetConstFace		(index);	}
	UInt32							GetShellCount	()				const { return GetBrep ().GetShellCount		();			}
	const Brep::NurbsShell&			GetConstShell	(UInt32 index)	const { return GetBrep ().GetConstShell		(index);	}
	UInt32							GetLumpCount	()				const { return GetBrep ().GetLumpCount		();			}
	const Brep::NurbsLump&			GetConstLump	(UInt32 index)	const { return GetBrep ().GetConstLump		(index);	}
	UInt32							GetCurve2DCount	()				const { return GetBrep ().GetCurve2DCount	();			}
	const Geometry::NurbsCurve2D&	GetConstCurve2D	(UInt32 index)	const { return GetBrep ().GetConstCurve2D	(index);	}
	UInt32							GetCurve3DCount	()				const { return GetBrep ().GetCurve3DCount	();			}
	const Geometry::NurbsCurve3D&	GetConstCurve3D	(UInt32 index)	const { return GetBrep ().GetConstCurve3D	(index);	}
	UInt32							GetSurfaceCount	()				const { return GetBrep ().GetSurfaceCount	();			}
	const Geometry::NurbsSurface&	GetConstSurface	(UInt32 index)	const { return GetBrep ().GetConstSurface	(index);	}

	const NurbsVertexAttributes&	GetConstVertexAttributes	(UIndex index)	const { return m_vertexData[index].vertexAttributes; }
	const NurbsEdgeAttributes&		GetConstEdgeAttributes		(UIndex index)	const { return m_edgeData[index].edgeAttributes;	 }
	const NurbsFaceAttributes&		GetConstFaceAttributes		(UIndex index)	const { return m_faceData[index].faceAttributes;	 }

	const NurbsVertexData&			GetConstVertexData	(UIndex index)	const { return m_vertexData[index];	}
	const NurbsEdgeData&			GetConstEdgeData	(UIndex index)	const { return m_edgeData[index];	}
	const NurbsFaceData&			GetConstFaceData	(UIndex index)	const { return m_faceData[index];	}

	bool							HasVertexIds		() const;
	bool							HasEdgeIds			() const;
	bool							HasFaceIds			() const;
	const NurbsVertexId&			GetConstVertexId	(UIndex index) const { return m_vertexData[index].vertexId;	}
	const NurbsEdgeId&				GetConstEdgeId		(UIndex index) const { return m_edgeData[index].edgeId;		}
	const NurbsFaceId&				GetConstFaceId		(UIndex index) const { return m_faceData[index].faceId;		}
	void							SetFaceId			(UIndex index, const NurbsFaceId& id) { m_faceData[index].faceId = id; }

	const UserDataContainer*		GetBodyUserDataContainer (void) const			{ return m_attrs.bodyUserDataContainer.GetPtr (); }
	const BaseUserData*				GetBodyUserData (const GS::Guid& guid) const	{ return m_attrs.bodyUserDataContainer.HasValue () ? m_attrs.bodyUserDataContainer->GetUserData (guid) : nullptr; }

	ULong							GetUsedBytes		() const;
	ULong							GetHeapUsedBytes	() const;

	// Debug
	void	DumpNurbsGDL (GS::OChannel& oc) const;
	void	DumpNurbsGDLToDBChannel () const;
	
	const Brep::NurbsBrep& GetBrep () const { return m_nurbsBrepWithLibData.GetBrep (); }
	const BrepOperations::NurbsBrepWithLibData& GetBrepWithLibData () const;

protected:
	// instantiate NurbsBody or CandidateNurbsBody instead
	NurbsBodyBase (void);
	NurbsBodyBase (const NurbsBodyBase& src) = default;
	NurbsBodyBase (NurbsBodyBase&& src) = default;

	NurbsBodyBase (BrepOperations::NurbsBrepWithLibData&&	brepWithLibData,
				   NurbsVertexDataContainerT&&				vertexData,
				   NurbsEdgeDataContainerT&&				edgeData,
				   NurbsFaceDataContainerT&&				faceData,
				   STATL									shadowStatus,
				   const NurbsBodyLevelAttrs&				bodyLevelAttrs);

	NurbsBodyBase& operator= (const NurbsBodyBase&) = default;
	NurbsBodyBase& operator= (NurbsBodyBase&&) = default;

	void CheckBodyWithoutBrep (const CheckControl& control, USize materialCount = 0) const;

	static bool CallWithErrorReporting (const std::function<void ()>& op, const CheckReporter* reporter);
};


class ConstNurbsEdgeOfFaceIterator : public Brep::ConstNurbsEdgeOfFaceIterator {
public:
	ConstNurbsEdgeOfFaceIterator (const NurbsBodyBase& b, const Brep::NurbsFace& f) : Brep::ConstNurbsEdgeOfFaceIterator (b.GetBrep (), f) {}
	ConstNurbsEdgeOfFaceIterator (const NurbsBodyBase& b, UInt32 fIdx) : Brep::ConstNurbsEdgeOfFaceIterator (b.GetBrep (), fIdx) {}
};


class ConstNurbsFaceOfEdgeIterator : public Brep::ConstNurbsFaceOfEdgeIterator {
public:
	ConstNurbsFaceOfEdgeIterator (const NurbsBodyBase& b, const Brep::NurbsEdge& e) : Brep::ConstNurbsFaceOfEdgeIterator (b.GetBrep (), e) {}
	ConstNurbsFaceOfEdgeIterator (const NurbsBodyBase& b, UInt32 eIdx) : Brep::ConstNurbsFaceOfEdgeIterator (b.GetBrep (), eIdx) {}
};


}	// namespace Modeler


#endif // NURBS_BODY_BASE_HPP
