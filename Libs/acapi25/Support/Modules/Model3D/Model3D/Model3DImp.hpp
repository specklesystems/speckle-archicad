// *****************************************************************************
// Model3D inline implementation.
// GSModeler, platform-independent
//
// Namespaces:        Contact person:
//    Modeler          FGY
//
// SG compatible
// *****************************************************************************

#if !defined(MODEL3DIMP_HPP)
#define MODEL3DIMP_HPP

#pragma once

//from GSRoot
#include "Guard.hpp"
#include "BitManipulation.hpp"


namespace Modeler {

class IntersectionQueryAlgorithm;


inline const Box3D& Model3D::GetBounds () const
{
	return m_bounds;
}


// inline void Model3D::SetBounds (const Box3D& newBounds)
// {
// 	m_bounds = newBounds;
// }


inline const ModStamp&	Model3D::GetInfStamp () const
{
	return m_modelInfStamp;
}


inline 	void	Model3D::SetInfStamp (const ModStamp& stamp)
{
	// if it is not the main model ask for the main model
	if (m_mainModel == nullptr) {
		m_modelInfStamp = stamp;
		if (m_modelInfStamp.IsZero ()) {
			m_modelGuid.Clear ();
		} else {
			m_modelGuid.Generate ();
		}
	} else {
		m_mainModel->SetInfStamp (stamp);
	}
}


inline 	GS::Guid	Model3D::GetGuid () const
{
	return m_modelGuid;
}


template <typename ElemQueryAdapterType>
void Model3D::QueryElems (const F_Box3D& floatBox, ElemQueryAdapterType& adapter) const
{
	LazyInitElemSearchTree ();
	m_elemTree->InterruptibleOrthogonalRangeQuery (Geometry::Box3DKey (floatBox), adapter);
}


template <typename ElemQueryAdapterType>
void Model3D::QueryElems (const IntersectionQueryAlgorithm& queryAlgorithm, ElemQueryAdapterType& adapter, GS::ProcessControl& processControl) const
{
	LazyInitElemSearchTree ();
	QueryKDTree (*m_elemTree, GetBounds (), queryAlgorithm, adapter, processControl);
}


inline	void Modeler::Model3D::GetBaseElemSet (BaseElemSet &baseElems) const
{
	baseElems.Clear ();

	const ElemArray& elems = GetElems ();
	UInt32 elemCount = elems.GetSize ();
	for (UInt32 elemIdx = 0; elemIdx < elemCount; elemIdx++) {
		const Modeler::BaseElem *constBaseElemPtr = &elems[elemIdx]->GetConstBaseElem ();
		if (baseElems.ContainsKey (constBaseElemPtr))
			++baseElems[constBaseElemPtr];
		else
			baseElems.Add (constBaseElemPtr, 1);
	}
}


inline Int32	Model3D::GetGlobPgonIdx (ULong elemIdx, ULong bodyIdx) const
{
	if (m_mainModel == nullptr) {
		return elemContainer.GetGlobPgonIdx (elemIdx, bodyIdx);
	} else {
		return m_mainModel->GetGlobPgonIdx (elemIdx, bodyIdx);
	}
}


inline AttributesPtr Model3D::GetAttributesPtr ()
{
	return m_attributes;
}

inline ConstAttributesPtr Model3D::GetConstAttributesPtr () const
{
	return m_attributes;
}


}


namespace Modeler {

inline const Box3D& Model3DViewer::GetBounds () const
{
	return model->m_bounds;
}


inline void Model3DViewer::GetBaseElemSet (BaseElemSet &baseElems) const
{
	model->GetBaseElemSet (baseElems);
}


inline GS::Guid Model3DViewer::GetGuid () const
{
	return model->m_modelGuid;
}


inline const ModStamp& Model3DViewer::GetLastConversionModStamp () const
{
	return model->m_lastConvModStamp;
}


inline const ModStamp& Model3DViewer::GetPrevConversionModStamp () const
{
	return model->m_prevConvModStamp;
}


inline Int32	Model3DViewer::GetGlobPgonIdx (ULong elemIdx, ULong bodyIdx) const
{
	return model->GetGlobPgonIdx (elemIdx, bodyIdx);
}


inline void	Model3DViewer::DetailedCheckModel () const
{
	model->DetailedCheck();

	if (model->m_mainModel != nullptr) {
		DBASSERT (model->GetBodyCount () == model->m_mainModel->GetBodyCount ());
	}
}

inline bool	Model3DViewer::HasSameModel (ConstModel3DPtr refModel) const
{
	return (model == refModel);
}

inline ConstAttributesPtr	Model3DViewer::GetConstAttributesPtr () const
{
	return model->GetConstAttributesPtr ();
}


inline void Modeler::Model3DViewer::InitElemSearchTree () const
{
	model->LazyInitElemSearchTree ();
}


template <typename ElemQueryAdapterType>
void Model3DViewer::QueryElems (const F_Box3D& floatBox, ElemQueryAdapterType& adapter) const
{
	model->QueryElems (floatBox, adapter);
}


template <typename ElemQueryAdapterType>
void Model3DViewer::QueryElems (const Box3D& box, ElemQueryAdapterType& adapter) const
{
	F_Box3D floatBox (static_cast<float> (box.xMin),
					  static_cast<float> (box.yMin),
					  static_cast<float> (box.xMax),
					  static_cast<float> (box.yMax),
					  static_cast<float> (box.zMin),
					  static_cast<float> (box.zMax));
	model->QueryElems (floatBox, adapter);
}


template <typename ElemQueryAdapterType>
void Model3DViewer::QueryElems (const IntersectionQueryAlgorithm& queryAlgorithm, ElemQueryAdapterType& adapter, GS::ProcessControl& processControl) const
{
	model->QueryElems (queryAlgorithm, adapter, processControl);
}


inline GS::Object*		Modeler::Model3DViewer::GetUserData (ULong key) const
{
	return model->GetUserData (key);
}

inline bool				Modeler::Model3DViewer::IsViewerOf (ConstModel3DPtr model) const {
	return this->model == model;
}

inline bool				Modeler::Model3DViewer::IsMainModelViewer () const {
	return this->model->m_mainModel == nullptr;
}

inline UInt32 Modeler::Model3DViewer::GetElemCount () const
{
	return model->elemContainer.GetElemCount ();
}

inline const Modeler::Elem& Modeler::Model3DViewer::GetConstElem (UIndex elemIndex) const
{
	return *model->GetElems ()[elemIndex];
}

inline Modeler::ConstElemPtr Modeler::Model3DViewer::GetConstElemPtr (UIndex elemIndex) const
{
	return model->GetElems ()[elemIndex];
}

inline ConstModel3DPtr	Modeler::Model3DViewer::GetConstModel3DPtr () const
{
	return model;
}


inline const Modeler::ElemElimData& Modeler::Model3DViewer::GetElemElimData  (GS::ProcessControl& processControl, const UInt32 elemIdx)  const
{
	return model->GetElemElimData (processControl, elemIdx);
}


inline void Modeler::ElemElimData::PushRemainingEdgePart (const RemainingEdgePart& part)
{
	remainingEdgeParts.Push (part);
}


inline void Model3DOnlyModifier::CalculateBounds (ULong firstNewElem)
{
	model->CalculateBounds (firstNewElem);
#ifdef DEBUVERS
	model->DetailedCheck ();
#endif
}

inline void	Model3DOnlyModifier::TruncateElemCount (UInt32 newElemCount)
{
	model->TruncateElemCount (newElemCount);
}

inline AttributesPtr Model3DOnlyModifier::GetAttributesPtr ()
{
	return model->GetAttributesPtr ();
}

inline void	Model3DOnlyModifier::SetUserData (ULong key, GS::Object* userData)
{
	model->SetUserData (key, userData);
}

inline const Modeler::Model3D::ElemArray& Modeler::Model3D::ElemContainer::GetElems (void) const
{
	RestoreFromDisk ();
	return elems;
}

inline GS::HashTable<GS::Guid, UInt32>&	Modeler::Model3D::ElemContainer::GetElemGuidIndexMap (void)
{
	RestoreFromDisk ();
	return elemGuidIndexMap;
}

inline GS::PagedArray<Modeler::Model3D::ElemAbsoluteIndices>&	Modeler::Model3D::ElemContainer::GetElemAbsoluteIndices (void)
{
	RestoreFromDisk ();
	return m_absoluteIndices;
}


inline GS::PagedArray<F_Box3D>&	Modeler::Model3D::ElemContainer::GetModifiedBox3DList (void)
{
	RestoreFromDisk ();
	return m_modifiedBox3DList;
}


inline Modeler::ElimDataArray& Modeler::Model3D::ElemContainer::GetElimDataArray ()
{
	RestoreFromDisk ();
	return elimData;
}


inline bool BitField::Get (UInt32 index) const
{
	DBASSERT (bits.IsEmpty () || index < bits.GetSize () * DataSize);
	return bits.IsEmpty () ? false : GS::TestBit (bits.GetContent(), index);
}


inline bool ElemElimData::IsElimEdge (UInt32 bodyIdx, UInt32 edgeIdx) const
{
	DBASSERT (edgeFlags.IsEmpty() || bodyIdx < edgeFlags.GetSize ());
	return edgeFlags.IsEmpty () ? false : edgeFlags[bodyIdx].Get (edgeIdx);
}


inline bool ElemElimData::IsElimPGON  (UInt32 bodyIdx, UInt32 pgonIdx) const
{
	DBASSERT (pgonFlags.IsEmpty() || bodyIdx < pgonFlags.GetSize ());
	return pgonFlags.IsEmpty () ? false : pgonFlags[bodyIdx].Get (pgonIdx);
}


inline UInt32 ElemElimData::GetRemainingEdgePartCount () const
{
	return remainingEdgeParts.GetSize ();
}

inline const RemainingEdgePart& ElemElimData::GetRemainingEdgePartInElemLocalCoordinateSystem (UInt32 index) const
{
	return remainingEdgeParts[index];
}

inline RemainingEdgePart ElemElimData::GetRemainingEdgePart (UInt32 index, const TRANMAT* elemLocalToWorldTrafo) const
{
	RemainingEdgePart remEdge = remainingEdgeParts[index];
	remEdge.vert1 = Geometry::TransformPoint (*elemLocalToWorldTrafo, remEdge.vert1);
	remEdge.vert2 = Geometry::TransformPoint (*elemLocalToWorldTrafo, remEdge.vert2);
	return remEdge;
}

inline void Modeler::Model3D::ElemContainer::InvalidateAbsoluteIndices ()
{
	m_isAbsoluteIndicesValid = false;
}

inline Int32	Modeler::Model3D::ElemContainer::GetElemIdx	(const GS::Guid& elemGuid)
{
	RestoreFromDisk ();

	if (elemGuid == GS::NULLGuid)
		return -1;

	UInt32 elemIdx;
	if (elemGuidIndexMap.Get (elemGuid, &elemIdx)) {
		if (elemIdx < GetElems ().GetSize () && GetElems ()[elemIdx]->GetElemId ().elemGuid == elemGuid) {
			return elemIdx;
		}
	}
	return -1;
}

inline Int32	Modeler::Model3D::ElemContainer::GetGlobPgonIdx (ULong elemIdx, ULong bodyIdx)
{
	RestoreFromDisk ();
	if (elemIdx < m_absoluteIndices.GetSize () && bodyIdx < m_absoluteIndices[elemIdx].m_absPolygonIndices.GetSize ()) {
		return m_absoluteIndices[elemIdx].m_absPolygonIndices[bodyIdx];
	} else {
		return 0;
	}
}


inline UInt32 Modeler::Model3D::ElemContainer::GetElemCount (void) {
	return elemCount;
}


inline const Modeler::Model3D::ElemArray& Modeler::Model3D::GetElems () const
{
	return elemContainer.GetElems ();
}


inline	Model3D*	Model3DModifier::GetModel3D ()
{
	return Model3DOnlyModifier::model.operator ->();
}

} // namespace Modeler

#endif // !defined(MODEL3DIMP_HPP)
