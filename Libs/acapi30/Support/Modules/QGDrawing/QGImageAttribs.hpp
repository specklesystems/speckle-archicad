// *****************************************************************************
//
//                                Class ImageAttribs
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGIMAGEATTRIBS_HPP
#define QGIMAGEATTRIBS_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "QGBase.hpp"
#include "QGTypes.hpp"


// ============================== class ContextAttribs ==============================

namespace QG {

class QG_DLL_EXPORT ImageAttribs {

private:
	double			rotAngle;			// in radian
	Int32			anchor;
	Int32			mirror;
	bool			transparent;
	QG::Color		transparentColor;
	bool			interpolation;
	bool			drawGray;

	GS::Optional<GS::UniString>	textureFileName;

public:
	enum Anchors { aLTCentre	= 1, aMTCentre = 2, aRTCentre = 3,
				   aLMCentre	= 4, aMMCentre = 5, aRMCentre = 6,
				   aLBCentre	= 7, aMBCentre = 8, aRBCentre	= 9	};
	enum Mirror { NotMirrored = 0, LeftEdgeMirrored = 1, MiddleMirrored = 2, RightEdgeMirrored = 3 };

	ImageAttribs (void);

	void						SetInterpolation (bool switchOff);
	bool						InterpolationIsOn (void) const;

	void						Rotate (double angle);
	double						GetRotationAngle (void) const;

	void						SetMirror (QG::ImageAttribs::Mirror imgMirror);
	QG::ImageAttribs::Mirror	GetMirror (void) const;

	void						SetTransparent (const QG::Color& color);
	void						SetOpaque (void);
	bool						IsTransparent (void) const;
	QG::Color*					GetTransparentColor (void) const;

	void						SetAnchor (QG::ImageAttribs::Anchors imgAnchor);
	QG::ImageAttribs::Anchors	GetAnchor (void) const;

	void						SetDrawGray (bool inDrawGray);
	bool						DrawGrayIsOn (void) const;

	void							SetTextureFileName (const GS::Optional<GS::UniString>& textureFileName);
	GS::Optional<GS::UniString>		GetTextureFileName () const;
};

}	// namespace QG
// ______________________________ class ContextAttribs ______________________________

#endif	// QGIMAGEATTRIBS_HPP
