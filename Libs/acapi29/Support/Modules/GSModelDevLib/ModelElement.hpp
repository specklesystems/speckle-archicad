// =============================================================================
// Description:		  Element    
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (ELEMENT_HPP)
#define ELEMENT_HPP

// ----------------------- Includes --------------------------------------------
#include "GSGuid.hpp"
#include "GSModelerExport.h"
#include "Box3DData.h"
#include "SharedPtr.hpp"
#include "BaseElementId.hpp"
#include "CoordinateSystem.hpp"

// ----------------------- Predeclarations -------------------------------------
namespace ModelerAPI {
	class MeshBody;
	class NurbsBody;
	class PointCloud;
	class ElementRelay;
	class ModelRelay;
	class Transformation;
	class Light;
	class EliminationInfo;
}

namespace GS {
	class ProcessControl;
}

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {

class GSMODELER_DLL_EXPORT Element {
	friend class ElementRelay;		// ElementRelay::ConstructElement () uses the private member variable

public:
	enum Type {
		UndefinedElement,
		WallElement,
		SlabElement,
		RoofElement,
		CurtainWallElement,
		CWFrameElement,
		CWPanelElement,
		CWJunctionElement,
		CWAccessoryElement,
		CWSegmentElement,
		ShellElement,
		SkylightElement,
		FreeshapeElement,
		DoorElement,
		WindowElement,
		ObjectElement,
		LightElement,
		ColumnElement,
		MeshElement,
		BeamElement,
		RoomElement,
		StairElement,
		RiserElement,
		TreadElement,
		StairStructureElement,
		RailingElement,
		ToprailElement,
		HandrailElement,
		RailElement,
		RailingPostElement,
		InnerPostElement,
		BalusterElement,
		RailingPanelElement,
		RailingSegmentElement,
		RailingNodeElement,
		RailPatternElement,
		InnerTopRailEndElement,
		InnerHandRailEndElement,
		RailFinishingObjectElement,
		TopRailConnectionElement,
		HandRailConnectionElement,
		RailConnectionElement,
		RailEndElement,
		BalusterSetElement,
		Opening,
		Openingframeinfill,
		Openingpatchinfill,
		ColumnSegmentElement,
		BeamSegmentElement,
		OtherElement
	};

	// determines if override info has to be calculated into BaseElemId
	enum class EdgeColorInBaseElemId {
		Included,
		NotIncluded
	};

	// determines if mesh polygon/nurbs face texture coordinate system/texture uv has to be calculated into BaseElemId
	enum class PolygonAndFaceTextureMappingInBaseElemId {
		Included,
		NotIncluded
	};

	// determines if mesh/nurbs body texture coordinate system has to be calculated into BaseElemId
	enum class BodyTextureMappingInBaseElemId {
		Included,
		NotIncluded
	};

	// determines if elimination info has to be calculated into BaseElemId
	enum class EliminationInfoInBaseElemId {
		Included,
		NotIncluded
	};

private:
	GS::ConstSharedPtr<ModelerAPI::ElementRelay>	relay;

public:
	Element ();
	Element (const Element& other);
	~Element ();

	Element&			operator= (const Element& other);
	bool				operator== (const Element& other) const;
	bool				operator!= (const Element& other) const	{ return !(*this == other); }
	bool				operator< (const Element& other) const;
	ULong				GenerateHashValue () const;

	bool				IsInvalid (void) const;
	UInt32				GetGenId (void) const;
	Int32				GetTessellatedBodyCount (void) const;
	Int32				GetMeshBodyCount (void) const;
	Int32				GetNurbsBodyCount (void) const;
	GS::Guid			GetElemGuid (void) const;
	Type				GetType (void) const;
	Box3D				GetBounds (const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World) const;
	void				GetBaseElemId (ModelerAPI::BaseElemId*						baseElemId,
									   GS::ProcessControl&							processControl,
									   EdgeColorInBaseElemId						edgeColorInBaseElemId,
									   PolygonAndFaceTextureMappingInBaseElemId		polygonAndFaceTextureMappingInBaseElemId,
									   BodyTextureMappingInBaseElemId				bodyTextureMappingInBaseElemId,
									   EliminationInfoInBaseElemId					eliminationInfoInBaseElemId) const;
	void				GetTessellatedBody (Int32 bodyIndex, MeshBody* body) const;
	void				GetMeshBody (Int32 bodyIndex, MeshBody* body) const;
	void				GetNurbsBody (Int32 bodyIndex, NurbsBody* body) const;
	Transformation		GetElemLocalToWorldTransformation () const;
	Int32				GetPointCloudCount (void) const;
	void				GetPointCloud (Int32 pointCloudIndex, PointCloud* pointCloud) const;
	Int32				GetLightCount (void) const;
	void				GetLight (Int32 lightIndex, Light* light) const;
	void				GetEliminationInfo (GS::ProcessControl& processControl, EliminationInfo* eliminationInfo) const;
};


} // namespace ModelerAPI


#endif
