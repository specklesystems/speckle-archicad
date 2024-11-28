#if !defined BODY_LEVEL_ATTRS_H
#define BODY_LEVEL_ATTRS_H

#include	"Model3DPrivExp.h"
#include	"UserDataContainer.hpp"
#include	"TextureCoordSys.hpp"
#include	"Nurbs/NurbsSmoothnessInterval.hpp"

// from GSRoot
#include	"Definitions.hpp"
#include	"OptionalOnHeap.hpp"

// from GSUtils
#include	"GSUtilsDefs.h"

// from GDL
#include	"GDLWrapping.hpp"
#include	"BodyTypes.hpp"


namespace Modeler
{

using OptionalUserDataContainer = GS::OptionalOnHeap<UserDataContainer>;
struct MeshBodyLevelAttrs;

enum class LineEliminationBehaviour {
	Automatic = 0,
	Exclude
};

struct BodyLevelAttrs {
	Int32						materialIdx;		// material index. can be used: for surfaces (polygons) created by cut
	short						edgePenIdx;			// can be used: for edges created by cut; for hatch line drawing if material has no pen	
	Wrapping					wrap;			
	TextureCoordSys				textureCoordSys;
	OptionalUserDataContainer	bodyUserDataContainer;
	LineEliminationBehaviour	lineEliminationBehaviour;

public:
	BodyLevelAttrs () :
		materialIdx (0),
		edgePenIdx (0),
		wrap (W_UNKNOWN),
		textureCoordSys {},
		bodyUserDataContainer {},
		lineEliminationBehaviour (LineEliminationBehaviour::Automatic)
	{}

	BodyLevelAttrs (GSAttributeIndex materialIdx, 
					short edgePenIdx, 
					const Wrapping& wrap, 
					const TextureCoordSys& textureCoordSys, 
					const OptionalUserDataContainer& bodyUserDataContainer, 
					LineEliminationBehaviour lineEliminationBehaviour) : 
		materialIdx (materialIdx),
		edgePenIdx (edgePenIdx),
		wrap (wrap),
		textureCoordSys (textureCoordSys),
		bodyUserDataContainer (bodyUserDataContainer),
		lineEliminationBehaviour (lineEliminationBehaviour)
	{}
};


struct MODEL3D_PRIVATE_EXPORT NurbsBodyLevelAttrs : public BodyLevelAttrs {
	NurbsSmoothnessInterval smoothness;

public:
	NurbsBodyLevelAttrs () : smoothness {} {}

	NurbsBodyLevelAttrs (GSAttributeIndex materialIdx, 
						 short edgePenIdx, 
						 const Wrapping& wrap, 
						 const TextureCoordSys& textureCoordSys, 
						 const OptionalUserDataContainer& bodyUserDataContainer, 
						 LineEliminationBehaviour lineEliminationBehaviour, 
						 const NurbsSmoothnessInterval& smoothness) :
		BodyLevelAttrs {materialIdx, 
						edgePenIdx, 
						wrap, 
						textureCoordSys,
						bodyUserDataContainer, 
						lineEliminationBehaviour},
		smoothness {smoothness}
	{}

	Modeler::MeshBodyLevelAttrs ToMeshBLA () const; 
};


struct MODEL3D_PRIVATE_EXPORT MeshBodyLevelAttrs : public BodyLevelAttrs {
	short				btype;
	UInt32				fatherBind; // absolute father body index, if (m_btype == B_SHADOW || m_btype == B_VECTSHADOW)	

public:
	MeshBodyLevelAttrs () : btype (B_PRIMITIVE), fatherBind (0) {}

	MeshBodyLevelAttrs (GSAttributeIndex materialIdx, 
						short edgePenIdx, 
						const Wrapping& wrap, 
						const TextureCoordSys& textureCoordSys, 
						const OptionalUserDataContainer& bodyUserDataContainer, 
						LineEliminationBehaviour lineEliminationBehaviour, 
						short btype, 
						UInt32 fatherBind) :
		BodyLevelAttrs { materialIdx, 
						 edgePenIdx,
						 wrap, 
						 textureCoordSys, 
						 bodyUserDataContainer, 
						 lineEliminationBehaviour },
		btype (btype),
		fatherBind (fatherBind)
	{}

	NurbsBodyLevelAttrs ToNurbsBLA () const;
};


}


#endif
