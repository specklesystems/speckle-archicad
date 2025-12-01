#ifndef NURBS_BODY_HPP
#define NURBS_BODY_HPP

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

#include	"Model3D/Nurbs/NurbsBodyBase.hpp"
#include	"Model3D/Nurbs/NurbsBodyPtr.hpp"
#include	"Model3D/MeshBody.hpp"
#include	"Model3D/MeshBodyPtr.hpp"
//#include	"NurbsBodyBase.hpp"

// from GSRoot
#include	"ThreadSafeLazyData.hpp"
#include	"Md5.hpp"

// from GSUtils
#include	"GSUtilsDefs.h"

// Predeclarations

// Types

namespace Modeler {

struct ModelILookup;
struct ModelOLookup;
class CandidateNurbsBody;
//class NurbsBodyBase;

////////////////////////////////////////////////////////////////////////////////
// NurbsBody
////////////////////////////////////////////////////////////////////////////////

class MODEL3D_DLL_EXPORT NurbsBody final : public Modeler::NurbsBodyBase {
	static	GS::ClassInfo	classInfo;

	// ================================
	//        Other body data
	// ================================
	mutable GS::ThreadSafeLazyData<GS::ArrayFB<ConstMeshBodyPtr, 1>>	m_defaultTessellatedMeshBodies;

	// ================================
	//       Disabled methods
	// ================================
	bool operator== (const NurbsBody&) = delete;	// Not clear if it would mean geometrical or data-structural equality.
													// Use Equals or implement geometrical comparison instead 

	// ================================
	//       Private methods
	// ================================
private:

	NurbsBody& operator= (const NurbsBody&) = default;
	NurbsBody& operator= (NurbsBody&&) = default;

	void ReadVersion1					(GS::IChannel& ic);
	void WriteVersion1					(GS::OChannel& oc) const;

	void ReadVersion2					(GS::IChannel& ic);
	void WriteVersion2					(GS::OChannel& oc) const;

	void QuickReadCoreWithoutBrep	(GS::IChannel& ic, 
											ModelILookup& lookup, 
											Modeler::Attributes::Modifier* attrModifier, 
											const Modeler::IAttributeReader* attReader);

	void QuickWriteCoreWithoutBrep	(GS::OChannel& oc,
											ModelOLookup& lookup,
											const Modeler::Attributes::Viewer* attrViewer) const;

	void Clear ();

	// for CandidateNurbsBody::MoveToNurbsBody
	friend class CandidateNurbsBody;
	NurbsBody (CandidateNurbsBody&& src);

	

	// ================================
	//       Public methods
	// ================================
public:
	NurbsBody (void) = default;	
	NurbsBody (const NurbsBody& src) = default;
	NurbsBody (NurbsBody&& src) = default;
	NurbsBody (GS::XMLIChannel& inXML) { ReadXML (inXML); }
	virtual ~NurbsBody (void);

	const GS::Array<ConstMeshBodyPtr>&	GetDefaultTessellatedBodies () const;
	const ConstMeshBodyPtr&				GetDefaultTessellatedBody (UInt32 bodyIdx) const;
	UInt32								GetDefaultTessellatedBodyCount () const;

	// Read - write
	void	Read	(GS::IChannel &ic);
	void	Write	(GS::OChannel &oc) const;

	void	QuickRead	(GS::IChannel& ic,
						ModelILookup& lookup,
						Modeler::Attributes::Modifier* attrModifier,
						const Modeler::IAttributeReader* attReader);						// no version, no check
	void	QuickReadCore	(GS::IChannel& ic,
							ModelILookup& lookup,
							Modeler::Attributes::Modifier* attrModifier,
							const Modeler::IAttributeReader* attReader);						// no version, no check

	void	QuickWrite	(GS::OChannel& oc,
						ModelOLookup& lookup,
						const Modeler::Attributes::Viewer* attrViewer) const;				// no version, no check

	void	QuickWriteCore	(GS::OChannel& oc,
							ModelOLookup& lookup,
							const Modeler::Attributes::Viewer* attrViewer) const;				// no version, no check

	void	ReadXML		(GS::XMLIChannel& inXML);
	void	WriteXML	(GS::XMLOChannel& outXML) const;

	bool	HasData () const;
		
	// Debug
	void	DebugWriteXML (GS::OChannel& oChannel) const;
	void	DebugWriteXMLToFile (const char* filename) const;
	void	DebugWriteXMLToDBChannel () const;
};

}	// namespace Modeler

#endif // NURBS_BODY_HPP
