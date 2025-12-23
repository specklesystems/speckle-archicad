// *****************************************************************************
// DrawingContext
// GSModeler, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (DRAWINGCONTEXT_HPP)
#define DRAWINGCONTEXT_HPP


// ----------------------- Includes --------------------------------------------

#include "ModelRect.hpp"
#include "Ref.hpp"

// ----------------------- Class declaration -----------------------------------

namespace ModelerAPI {


class DrawingContext {
private:
	enum {
		Version8	= 2,
		Version13	= 3,
		Version15	= 4,
		Version		= 5
	};

public:
	enum Type {
		Unknown,
		OpenGL
	};

public:
	Int32					version;
	Type					type;
	void*							typeRelatedData;

	inline	DrawingContext ();
};


// ----------------------- Class implementation --------------------------------

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline	DrawingContext::DrawingContext ():
	version (Version),
	type (Unknown)
{
}


} // namespace ModelerAPI


#endif
