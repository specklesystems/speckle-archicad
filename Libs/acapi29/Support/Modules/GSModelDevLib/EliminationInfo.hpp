// =============================================================================
// Description:		  EliminationInfo  - wrapper of ElemElimData    
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (ELIMINATIONINFO_HPP)
#define ELIMINATIONINFO_HPP

// ----------------------- Includes --------------------------------------------
#include "GSModelerExport.h"
#include "Vertex.hpp"
#include "SharedPtr.hpp"
#include "AttributeIndex.hpp"
#include "CoordinateSystem.hpp"

// ----------------------- Predeclarations -------------------------------------
namespace ModelerAPI {
	struct GSMODELER_DLL_EXPORT RemainingEdgePartAttributes {
		bool						invisible;
		bool						visibleIfContour;
		ModelerAPI::AttributeIndex	colorIndex;
	};

	struct GSMODELER_DLL_EXPORT RemainingEdgePart {	
		RemainingEdgePartAttributes	attributes;
		ModelerAPI::Vertex			vert1, vert2;
	};
}

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {

class EliminationInfoRelay;

class GSMODELER_DLL_EXPORT EliminationInfo {
	friend class EliminationInfoRelay;
	friend class ElementRelay;

private:
	GS::ConstSharedPtr<ModelerAPI::EliminationInfoRelay>	relay;

public:
	EliminationInfo ();
	EliminationInfo (const EliminationInfo& other);
	~EliminationInfo ();

	EliminationInfo&			operator= (const EliminationInfo& other);
	bool						operator== (const EliminationInfo& other) const;
	bool						operator!= (const EliminationInfo& other) const	{ return !(*this == other); }
	bool						operator< (const EliminationInfo& other) const;
	
	ULong						GenerateHashValue () const;
	bool						IsElimEdge (UInt32 bodyIdx, UInt32 edgeIdx) const;
	bool						IsElimPGON (UInt32 bodyIdx, UInt32 pgonIdx) const;
	UInt32						GetRemainingEdgePartCount () const;
	RemainingEdgePartAttributes	GetRemainingEdgePartAttributes (UInt32 index) const;
	RemainingEdgePart			GetRemainingEdgePart (UInt32 index, const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World) const;
};


} // namespace ModelerAPI


#endif
