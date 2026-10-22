// =============================================================================
// Description:		  Edge    
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (MODELEDGE_HPP)
#define MODELEDGE_HPP

// ----------------------- Includes --------------------------------------------
#include "GSModelerExport.h"
#include "Definitions.hpp"
#include "SharedPtr.hpp"

// ----------------------- Predeclarations -------------------------------------
namespace ModelerAPI {
	class AttributeIndex;
	class Model; 
	class Color;
	class EdgeRelay;
}

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {


class GSMODELER_DLL_EXPORT Edge {
	friend class EdgeRelay;

private:
	GS::SharedPtr<ModelerAPI::EdgeRelay>	relay;

public:
	Edge ();
	Edge (const Edge& other);
	~Edge ();

	Edge&								operator= (const Edge& other);

	bool								IsInvisible (void) const;
	bool								IsVisibleIfContour (void) const;
	bool								HasColor () const;
	void								GetColor (ModelerAPI::Color* color) const;
	void								GetColorIndex (ModelerAPI::AttributeIndex& iCol) const;
	Int32								GetVertexIndex1 (void) const;
	Int32								GetVertexIndex2 (void) const;
	Int32								GetPolygonIndex1 (void) const;
	Int32								GetPolygonIndex2 (void) const;
};


} // namespace ModelerAPI


#endif
