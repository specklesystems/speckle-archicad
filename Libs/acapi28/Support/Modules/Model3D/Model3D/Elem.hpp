// *********************************************************************************************************************
// Description:		Grouping of bodies and solving topological repetitions (by referencing to BaseElems)
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_ELEM_HPP)
#define GS_MODELER_ELEM_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"SharedObject.hpp"
#include	"Array.hpp"
#include	"HashTable.hpp"

// from Geometry
#include	"Box3DData.h"		// F_Box3D Box3D

// from Model3D
#include	"Model3D/ElemComparisonFlags.hpp"
#include	"Model3D/model.h" // TRANMAT
#include	"Model3D/Model3DExport.h"
#include	"Model3D/BaseElem.hpp"		// for inline function implementations
#include	"Model3D/VOCA.hpp"
#include	"Model3D/UserDataContainer.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Modeler {

class MeshBody;
class Elem;

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

typedef GS::ConstSharedPtr<Elem>		ConstElemPtr;
typedef GS::SharedPtr<Elem>				ElemPtr;


class MODEL3D_DLL_EXPORT Elem : public GS::SharedObject
{
	struct TransformedBounds;
private:
	struct StatusType {
		unsigned short	valid	: 1; /*deleted <-> !valid*/
		unsigned short	boundsCalculated : 1;
	}					m_status;

	VOCA				elemId;
	UInt32				genId;		// general unique identifier, moved here from VOCA
	TRANMAT				trafo;
	ConstBaseElemPtr 	baseElem;	// shared ownership

	

	Owner<TransformedBounds>	transformedBounds;
	F_Box3D						bounds;

	Owner<UserDataContainer>	m_elemUserDataContainer;

	mutable				GS::ThreadSafeLazyData<GS::Array<Modeler::ConstMeshBodyPtr>> tessellatedNurbsBodies;

						Elem (const Elem&); // disable
	Modeler::Elem&		operator= (const Modeler::Elem& src); // disable
	void				ShallowCopy (const Elem& src, const VOCA* elemIdIn = nullptr);
	void				EmptyCopy (const Elem& src, const VOCA* elemIdIn = nullptr);

	void				SetTrafo (const TRANMAT& newTrafo);
	void				CalculateBounds ();

	void				SetDeleted ();
	void				UpdateGenId (void);

	void				WriteXMLImpl (GS::XMLOChannel& outXML, Int64 baseElemIndex = -1) const;
	void				ReadXMLImpl	 (GS::XMLIChannel& inXML, const GS::Array<ConstBaseElemPtr>* baseElems = nullptr);

	const GS::Array<ConstMeshBodyPtr>& GetTessellatedNurbsBodies () const;

public:
	enum CopyType {
		Shallow,
		ShallowAndDeletedStatus, // shallow copy and set new elem status to deleted
		Empty
	};

				Elem (const VOCA& elemId, const TRANMAT * initTrafo, const UserDataContainer* elemUserDataContainer, const ConstBaseElemPtr& baseElem);
				Elem (const Elem& src, CopyType copyType, const VOCA* elemIdIn = nullptr);
				Elem (GS::XMLIChannel& inXML);
				Elem (GS::XMLIChannel& inXML, const GS::Array<ConstBaseElemPtr>& baseElems);

    virtual    ~Elem ();

	ULong		GetUsedBytes ()	const;
	ULong		GetSizeofElem (void) const;

	bool		Equals (const Modeler::Elem& other, ElemComparisonFlags flags = ElemComparisonFlags_WithoutGenId) const;
	bool		EqualsExactly (const Modeler::Elem& other, ElemComparisonFlags flags = ElemComparisonFlags_WithoutGenId) const;
	
	void		QuickWrite (GS::OChannel& oc, ModelOLookup& lookup, const Modeler::Attributes::Viewer* attrViewer) const;	// no versioning, no checking
	void		QuickRead (GS::IChannel& ic, ModelILookup& lookup, Modeler::Attributes::Modifier* attrModifier, const Modeler::IAttributeReader* attReader);  // no versioning, no checking

	void		WriteXML (GS::XMLOChannel& outXML) const;
	void		WriteXML (GS::XMLOChannel& outXML, ULong baseElemIndex) const;
	void		WriteXMLToDBChannel () const;
	void		ReadXML	 (GS::XMLIChannel& inXML);
	void		ReadXML	 (GS::XMLIChannel& inXML, const GS::Array<ConstBaseElemPtr>& baseElems);

	// Status
	bool		IsInvalid () const;

	// Acessors
	const VOCA&	GetElemId () const;

	UInt32		GetGenId (void) const;

	bool		HasGeometry () const;

	const TRANMAT&	GetConstTrafo () const;
	const TRANMAT*	GetConstTrafoPtr () const;

	ULong								GetMeshBodyCount () const;
	const MeshBody&						GetConstMeshBody (ULong bodyIdx) const;
	const ConstMeshBodyPtr&				GetConstMeshBodySharedPtr (ULong bodyIdx) const;

	ULong								GetNurbsBodyCount () const;
	const NurbsBody&					GetConstNurbsBody (ULong bodyIdx) const;
	const ConstNurbsBodyPtr&			GetConstNurbsBodySharedPtr (ULong bodyIdx) const;

	class TessellatedBodyIterator;
	class TessellatedBodyRange;
	ULong								GetTessellatedBodyCount () const;
	const MeshBody&						GetConstTessellatedBody (ULong bodyIdx) const;
	const ConstMeshBodyPtr&				GetConstTessellatedBodySharedPtr (ULong bodyIdx) const;
	TessellatedBodyRange				TessellatedBodies () const;

	TessellatedBodyIterator				BeginTessellatedBodies () const;
	TessellatedBodyIterator				EndTessellatedBodies () const;

	UIndex								GetPointCloudCount () const;
	const PointCloud::ConstViewPtr&		GetPointCloud (UIndex pointCloudIndex) const;

	const BaseElem&						GetConstBaseElem () const;
	const ConstBaseElemPtr&				GetConstBaseElemPtr () const;

	void			CalculateBounds (F_Box3D&				elemBoundBox,
									 GS::Array<F_Box3D>*	bodyBounds,
									 const TRANMAT*			trafo = nullptr) const;

	const F_Box3D&	GetMeshBodyBounds			(UIndex meshBodyIndex) const;
	F_Box3D			GetNurbsBodyBounds			(UIndex nurbsBodyIndex) const;
	const F_Box3D&	GetTessellatedBodyBounds	(UIndex tessellatedBodyIndex) const;

	// NURBS and mesh body bounds. Might be smaller than tessellated body bounds.
	virtual const F_Box3D&	GetBounds () const;

	ULong		GetHotspotCount () const;
	const HOTS&	GetConstHotspot (ULong idx) const;
	void		GetHotspotCoords (ULong idx, double* x, double* y, double* z) const;

	const UserDataContainer*	GetElemUserDataContainer (void) const;
	const BaseUserData*	GetElemUserData (const GS::Guid& guid) const;

	static ConstElemPtr Transform (const Modeler::ConstElemPtr& elem, const TRANMAT& newTrafo);

	GSErrCode Store (GS::ObjectState& os) const;
	GSErrCode Restore (const GS::ObjectState& os);
};




// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


// --- Inline function implementations ----------------------------------------------------------------------------------

inline bool Elem::IsInvalid () const { return !m_status.valid; }

inline const F_Box3D&	Elem::GetBounds () const { DBASSERT (m_status.boundsCalculated); return bounds; }

inline UInt32 Modeler::Elem::GetGenId (void) const { return genId; }

inline const TRANMAT& Modeler::Elem::GetConstTrafo () const { return trafo; }

inline const TRANMAT*	Modeler::Elem::GetConstTrafoPtr () const { return &trafo; }

inline ULong Modeler::Elem::GetMeshBodyCount () const { return baseElem->GetMeshBodyCount (); }

inline const Modeler::MeshBody& Modeler::Elem::GetConstMeshBody (ULong bodyIndex) const { return baseElem->GetConstMeshBody (bodyIndex); }

inline const Modeler::ConstMeshBodyPtr& Modeler::Elem::GetConstMeshBodySharedPtr (ULong bodyIndex) const { return baseElem->GetConstMeshBodySharedPtr (bodyIndex); }

inline ULong Modeler::Elem::GetNurbsBodyCount () const { return baseElem->GetNurbsBodyCount (); }

inline const Modeler::NurbsBody& Modeler::Elem::GetConstNurbsBody (ULong bodyIndex) const { return baseElem->GetConstNurbsBody (bodyIndex); }

inline const Modeler::ConstNurbsBodyPtr& Modeler::Elem::GetConstNurbsBodySharedPtr (ULong bodyIndex) const { return baseElem->GetConstNurbsBodySharedPtr (bodyIndex); }

inline UIndex Modeler::Elem::GetPointCloudCount () const { return baseElem->GetPointCloudCount (); }

inline const PointCloud::ConstViewPtr& Modeler::Elem::GetPointCloud (UIndex pointCloudIndex) const { return baseElem->GetPointCloud (pointCloudIndex); }

inline const Modeler::BaseElem& Modeler::Elem::GetConstBaseElem () const { return *baseElem; }
inline const ConstBaseElemPtr& Modeler::Elem::GetConstBaseElemPtr () const { return baseElem; }

inline ULong Modeler::Elem::GetHotspotCount () const { return baseElem->GetHotspotCount (); }

inline const HOTS& Modeler::Elem::GetConstHotspot (ULong idx) const { return baseElem->GetConstHotspot (idx); }

inline void Modeler::Elem::GetHotspotCoords (ULong idx, double* x, double* y, double* z) const
{
	return baseElem->GetHotspotCoords (idx, &trafo, x, y, z);
}


inline const UserDataContainer*	Modeler::Elem::GetElemUserDataContainer (void) const
{
	return m_elemUserDataContainer.Get ();
}

inline const BaseUserData*	Modeler::Elem::GetElemUserData (const GS::Guid& guid) const
{
	return m_elemUserDataContainer != nullptr ? dynamic_cast <const BaseUserData*> (m_elemUserDataContainer->GetUserData (guid)) : nullptr;
}


class MODEL3D_DLL_EXPORT Elem::TessellatedBodyIterator {
	const GS::Array<ConstMeshBodyPtr>* actContainer;
	const GS::Array<ConstMeshBodyPtr>* nextContainer;
	UIndex	actCurrent;
	UIndex	prevSize;

	friend class Elem;
	
	enum class InitType {
		Begin,
		End
	};
	TessellatedBodyIterator (const GS::Array<ConstMeshBodyPtr>* meshBodyContainer, 
							 const GS::Array<ConstMeshBodyPtr>* tessellatedNurbsBodyContainer,
							 InitType initType);

	void SetNextContainer ();

public:

	const MeshBody&		operator*  () const
	{
		return *(*actContainer)[actCurrent];
	}

	TessellatedBodyIterator&	operator++ ()	// prefix
	{
		DBASSERT (actCurrent < actContainer->GetSize ());
		++actCurrent;
		if (actCurrent == actContainer->GetSize ()) {
			SetNextContainer ();
		}
		return *this;
	}

	bool						operator== (std::nullptr_t) const
	{
		return actContainer == nullptr;
	}

	bool						operator!= (std::nullptr_t) const
	{
		return !operator== (nullptr);
	}

	bool operator== (const TessellatedBodyIterator& other) const
	{
		return GetIndex () == other.GetIndex ();
	}

	bool operator!= (const TessellatedBodyIterator& other) const
	{
		return !operator==(other);
	}

	UIndex						GetIndex () const
	{
		return prevSize + actCurrent;
	}
};


class Elem::TessellatedBodyRange {
	const Modeler::Elem* elem;
public:
	TessellatedBodyRange (const Modeler::Elem* elem) : elem (elem) {}
	TessellatedBodyIterator begin ()	const { return elem->BeginTessellatedBodies (); }
	TessellatedBodyIterator end ()		const { return elem->EndTessellatedBodies (); }
};


}	// namespace Modeler
#endif
