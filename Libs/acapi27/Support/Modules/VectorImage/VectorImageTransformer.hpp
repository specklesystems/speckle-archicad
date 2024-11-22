#ifndef VECTORIMAGETRANSFORMER_HPP
#define VECTORIMAGETRANSFORMER_HPP

#pragma once

// from Geometry
#include "TRANMAT.h"
#include "TM.h"
#include "Point2D.hpp"
#include "BezierDetails.hpp"
#include "Transformation2D.hpp"

// from VectorImage
#include "SyHot.hpp"
#include "SyLine.hpp"
#include "SyArc.hpp"
#include "SyText.hpp"
#include "SyRichText.hpp"
#include "SyPixMap.hpp"
#include "SySpline.hpp"
#include "ProfileVectorImageParameter.hpp"
#include "Anchor.hpp"
#include "StretchData.hpp"

// from Pattern
#include "PolygonDrawingDirection.hpp"

namespace Geometry {
	class Transformation2D;
}


namespace VI {

class VI_DLL_CLASS_EXPORT Transformer {
private:
	Geometry::Transformation2D	tran;
	bool						changeHatchTypeToKeepAppearance;
public:

	Transformer () : tran (), changeHatchTypeToKeepAppearance (false){}
	Transformer (const Geometry::Transformation2D& tran);
	virtual ~Transformer ();

	TRANMAT GetTranMat () const;
	Geometry::Transformation2D GetTransformation () const {return tran;}
	bool ChangeHatchTypeToKeepAppearance () const{return changeHatchTypeToKeepAppearance;};
	void ChangeHatchTypeToKeepAppearance (bool changeHatchType){changeHatchTypeToKeepAppearance = changeHatchType;};

	virtual void Transform (Sy_HotType& hots)													const { hots.Transform (tran);}	//done
	virtual void Transform (Sy_LinType& line)													const { line.Transform (tran);}	//done
	virtual void Transform (Sy_ArcType& arc)													const { arc.Transform (tran);} //done
	virtual void Transform (Sy_TextType& text, double textScale)								const { text.Transform (tran, textScale);} //done
	virtual void Transform (Sy_RichTextType& richText)											const { richText.Transform (tran);}	//Done
	virtual void Transform (Sy_SplineType& spline, Coord* pCoords, Geometry::DirType* pDirs)	const { spline.Transform (tran, pCoords, pDirs);} //done
	virtual void TransformInVectorImage (Sy_SplineType& spline)									const { spline.TransformInVectorImage (tran);}	//done
	virtual void Transform (Sy_PixMapType& pixMap)												const { pixMap.Transform (tran);}	//done
	virtual void Transform (PVI::ProfileVectorImageParameter& /*profileParameter*/)				const {}	//That does nothing
	virtual void Transform (PVI::Anchor& anchor)												const { anchor.Transform (tran);} //done
	virtual void Transform (PVI::StretchData& stretchData)										const { stretchData.Transform (tran);} //done

// transform the base arc of the curved curtain wall
	virtual	void TransformCWBaseArc (Sy_HotType& hots1, Sy_HotType& hots2) const;
};

}

#endif
