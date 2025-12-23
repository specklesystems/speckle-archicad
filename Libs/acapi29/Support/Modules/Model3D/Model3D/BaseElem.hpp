// *********************************************************************************************************************
// Description:		Bodies consisting one Elem
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_BASEELEM_HPP)
#define GS_MODELER_BASEELEM_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"SharedObject.hpp"
#include	"Array.hpp"
#include	"HashTable.hpp"
#include	"GSGuid.hpp"

// from Model3D
#include	"Model3D/HOTS.hpp"
#include	"Model3D/LGHT.hpp"
#include	"Model3D/Model3DExport.h"
#include	"Model3D/MeshBody.hpp"
#include	"Model3D/MeshBodyPtr.hpp"
#include	"Model3D/Nurbs/NurbsBody.hpp"
#include	"Model3D/Nurbs/NurbsBodyPtr.hpp"

// from PointCloud
// #include	"PointCloudViewFwd.hpp" Because of MSVC2010
#include	"PointCloudView.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Modeler {

class BaseElem;
class BaseElemCache;

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

typedef GS::SharedPtr<BaseElem>			BaseElemPtr;
typedef GS::ConstSharedPtr<BaseElem>	ConstBaseElemPtr;

class MODEL3D_DLL_EXPORT BaseElem : public GS::SharedObject {
	friend class Modeler::BaseElemCache;
	friend class Modeler::Elem;
private:
	GS::Array<ConstMeshBodyPtr>				meshBodies;
	GS::Array<ConstNurbsBodyPtr>			nurbsBodies;
	GS::Array<PointCloud::ConstViewPtr>		pointClouds;
	
	GS::Array<HOTS>							hotspots;
	GS::Array<LGHT>							lightSources;
	
	mutable GS::ThreadSafeLazyData<GS::Guid>	md5ContentGuid;

	BaseElem (const BaseElem& src); // disabled
	BaseElem& operator = (const BaseElem&); // disabled

public:
	BaseElem ();
	BaseElem (	const ConstMeshBodyPtr pMeshBody,
				const GS::Array<PointCloud::ConstViewPtr>* pPointClouds,
				const GS::Array<HOTS>* pHotspots,
				const GS::Array<LGHT>* pLightSources);

	BaseElem (	const GS::Array<ConstMeshBodyPtr>* pMeshBodies,
				const GS::Array<ConstNurbsBodyPtr>* pNurbsBodies,
				const GS::Array<PointCloud::ConstViewPtr>* pPointClouds,
				const GS::Array<HOTS>* pHotspots,
				const GS::Array<LGHT>* pLightSources);

	BaseElem (	const GS::PagedArray<ConstMeshBodyPtr>* pMeshBodies,
				const GS::PagedArray<ConstNurbsBodyPtr>* pNurbsBodies,
				const GS::PagedArray<PointCloud::ConstViewPtr>* pPointClouds,
				const GS::PagedArray<HOTS>* pHotspots,
				const GS::PagedArray<LGHT>* pLightSources);

	BaseElem (GS::XMLIChannel& inXML);

   ~BaseElem ();

   class BodyReader;
   class BodyWriter;

   void			QuickWriteCommon (GS::OChannel& oc, BodyWriter& bodyWriter, ModelOLookup& lookup, const Modeler::Attributes::Viewer* attrViewer) const;	// no versioning, no checking
   void			QuickReadCommon (GS::IChannel& ic, BodyReader& bodyReader, ModelILookup& lookup, Modeler::Attributes::Modifier* attrModifier, const Modeler::IAttributeReader* attReader);  // no versioning, no checking

public:
	bool		operator== (const Modeler::BaseElem& other) const;
	bool		operator!= (const Modeler::BaseElem& other) const { return !operator== (other); }
	bool		Equals (const BaseElem& other) const;
	
	void		QuickWrite	(GS::OChannel& oc, ModelOLookup& lookup, const Modeler::Attributes::Viewer* attrViewer) const;	// no versioning, no checking
	void		QuickRead	(GS::IChannel& ic, ModelILookup& lookup, Modeler::Attributes::Modifier* attrModifier, const Modeler::IAttributeReader* attReader);  // no versioning, no checking

	void		QuickWriteCore	(GS::OChannel& oc, ModelOLookup& lookup, const Modeler::Attributes::Viewer* attrViewer) const;	// no versioning, no checking
	void		QuickReadCore	(GS::IChannel& ic, ModelILookup& lookup, Modeler::Attributes::Modifier* attrModifier, const Modeler::IAttributeReader* attReader);  // no versioning, no checking


	void		Clear ();

	ULong										GetMeshBodyCount () const;
	const MeshBody&								GetConstMeshBody (ULong bodyIndex) const;
	const GS::ConstSharedPtr<MeshBody>&			GetConstMeshBodySharedPtr (ULong bodyIndex) const;
	const GS::Array<ConstMeshBodyPtr>&			GetMeshBodies () const;

	ULong										GetNurbsBodyCount () const;
	const NurbsBody&							GetConstNurbsBody (ULong bodyIndex) const;
	const GS::ConstSharedPtr<NurbsBody>&		GetConstNurbsBodySharedPtr (ULong bodyIndex) const;
	const GS::Array<ConstNurbsBodyPtr>&			GetNurbsBodies () const;

	USize										GetPointCloudCount		() const;
	const PointCloud::ConstViewPtr&				GetPointCloud			(UIndex pointCloudIndex) const;
	const GS::Array<PointCloud::ConstViewPtr>&	GetPointClouds			() const;
	
	UInt32		GetUsedBytes (void) const;
	ULong		GetLightsourceUsedBytes (void) const;
	ULong		GetSizeofBaseElem (void) const;

	ULong						GetHotspotCount () const;
	const HOTS&					GetConstHotspot (ULong idx) const;
	void						GetHotspotCoords (ULong idx, const TRANMAT* trafo, double* x, double* y, double* z) const;
	const GS::Array<HOTS>&		GetHotspots () const;

	ULong						GetLightSourceCount () const;
	const LGHT&					GetLightSource (ULong idx) const;
	const GS::Array<LGHT>&		GetLightSources () const;

	static ConstBaseElemPtr Transform (const ConstBaseElemPtr& baseElem, const TRANMAT& tran);
	static ConstBaseElemPtr Share (const ConstBaseElemPtr& baseElem);

	ULong	GenerateHashValue (void) const;

	bool			IsContentGuidCalculated () const;
	const GS::Guid& GetContentGuid () const;

	void		WriteXML (GS::XMLOChannel& outXML) const;
	void		WriteXMLToDBChannel () const;
	void		ReadXML	 (GS::XMLIChannel& inXML);

	GSErrCode Store (GS::ObjectState& os) const;
	GSErrCode Restore (const GS::ObjectState& os);
	GSErrCode Write (GS::OChannel& oc) const;
	GSErrCode Read (GS::IChannel& ic);

private:
	static	void	Share (const BaseElem*);	// forbidden; use shared pointer!
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------

// --- Inline function implementations ----------------------------------------------------------------------------------

inline ULong BaseElem::GetMeshBodyCount () const
{
	return meshBodies.GetSize ();
}

inline const MeshBody& BaseElem::GetConstMeshBody (ULong bodyIndex) const
{
	return *meshBodies[bodyIndex];
}

inline const GS::ConstSharedPtr<MeshBody>& BaseElem::GetConstMeshBodySharedPtr (ULong bodyIndex) const
{
	return meshBodies[bodyIndex];
}


inline const GS::Array<ConstMeshBodyPtr>& Modeler::BaseElem::GetMeshBodies () const
{
	return meshBodies;
}


inline ULong BaseElem::GetNurbsBodyCount () const
{
	return nurbsBodies.GetSize ();
}


inline const NurbsBody& BaseElem::GetConstNurbsBody (ULong bodyIndex) const
{
	return *nurbsBodies[bodyIndex];
}


inline const GS::ConstSharedPtr<NurbsBody>& BaseElem::GetConstNurbsBodySharedPtr (ULong bodyIndex) const
{
	return nurbsBodies[bodyIndex];
}


inline const GS::Array<ConstNurbsBodyPtr>& Modeler::BaseElem::GetNurbsBodies () const
{
	return nurbsBodies;
}


inline USize	BaseElem::GetPointCloudCount () const
{
	return pointClouds.GetSize ();
}


inline const PointCloud::ConstViewPtr&	BaseElem::GetPointCloud (UIndex pointCloudIndex) const
{
	return pointClouds[pointCloudIndex];
}


inline const GS::Array<PointCloud::ConstViewPtr>&	BaseElem::GetPointClouds () const
{
	return pointClouds;
}

inline ULong Modeler::BaseElem::GetHotspotCount () const
{
	return hotspots.GetSize ();
}


inline const HOTS& Modeler::BaseElem::GetConstHotspot (ULong idx) const
{
	return hotspots [idx];
}

inline ULong Modeler::BaseElem::GetLightSourceCount () const
{
	return lightSources.GetSize ();
}


inline const LGHT& Modeler::BaseElem::GetLightSource (ULong idx) const
{
	return lightSources[idx];
}


inline const GS::Array<HOTS>& Modeler::BaseElem::GetHotspots () const
{
	return hotspots;
}


inline const GS::Array<LGHT>& Modeler::BaseElem::GetLightSources () const
{
	return lightSources;
}

}	// namespace Modeler

#endif
