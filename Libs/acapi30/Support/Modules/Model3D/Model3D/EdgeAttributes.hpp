// EdgeAttributes

#ifndef EDGE_ATTRIBUTES_HPP
#define EDGE_ATTRIBUTES_HPP
#pragma once

#include "GSUtilsDefs.h"

#include "Model3D/Model3DExport.h"
#include "Model3D/model.h"

/*	For ----- EDGEs	sharp edge in rendering										*/
#define	REND_SHARP_EDGE	0x00040000		/*	0b00000000000001000000000000000000	*/

namespace GS {
	class IChannel;
	class OChannel;
}

namespace Modeler {
class MODEL3D_DLL_EXPORT EdgeAttributes {
private:
	STATL	status;	
	short	color;

	void SetOrClearStatusMask (STATL mask, bool set)
	{
		if (set)
			SET_FLAGS (status, mask);
		else
			CLR_FLAGS (status, mask);
	}

public:
	EdgeAttributes () : status (0), color (0)
	{
	}

	EdgeAttributes (STATL status, short color) : status (status), color (color)
	{
	}

	STATL GetStatus () const
	{
		return status;
	}

	void SetStatus (STATL status)
	{
		this->status = status;
	}

	short GetColor () const
	{
		return color;
	}

	void SetColor (short color)
	{
		this->color = color;
	}

	bool IsVisibleIfContour () const
	{
		return HAS_ANY_FLAGS (status, VISIBLEIFCONTOURBIT);
	}

	void SetVisibleIfContour (bool visibleIfContour)
	{
		SetOrClearStatusMask (VISIBLEIFCONTOURBIT, visibleIfContour);
	}

	bool IsInvisible () const
	{
		return HAS_ANY_FLAGS (status, INVISBIT);
	}

	void SetInvisible (bool invisible)
	{
		SetOrClearStatusMask (INVISBIT, invisible);
	}

	bool IsSharp () const
	{
		return HAS_ANY_FLAGS(status, REND_SHARP_EDGE);
	}

	void SetSharp (bool sharp)
	{
		SetOrClearStatusMask (REND_SHARP_EDGE, sharp);
	}

	void SetCurvedBeg (bool curvedBeg)
	{
		SetOrClearStatusMask (CURVEDBEG, curvedBeg);
	}

	bool IsCurvedBeg () const
	{
		return HAS_ANY_FLAGS (status, CURVEDBEG);
	}

	void SetCurvedEnd (bool curvedEnd)
	{
		SetOrClearStatusMask (CURVEDEND, curvedEnd);
	}

	bool IsCurvedEnd () const
	{
		return HAS_ANY_FLAGS (status, CURVEDEND);
	}

	bool IsCut () const
	{
		return HAS_ANY_FLAGS (status, ON_CUT_BIT | ON_MODEL_CUT_BIT | ON_SECT_CUT_SPEC_BIT);
	}

	bool operator== (const EdgeAttributes& other) const;
	bool operator!= (const EdgeAttributes& other) const;

	GSErrCode QuickWrite (GS::OChannel& oc) const;	// no versioning, no checking
	GSErrCode QuickRead (GS::IChannel& ic);			// no versioning, no checking
};
} // namespace Modeler


#endif // EDGE_ATTRIBUTES_HPP
