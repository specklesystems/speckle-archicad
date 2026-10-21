// *****************************************************************************
//
//                                Class Context
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGCONTEXT_HPP
#define QGCONTEXT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Array.hpp"

#include "QGBase.hpp"
#include "QGTypes.hpp"
#include "QGMatrix.hpp"
#include "QGImageAttribs.hpp"
#include "QGImage.hpp"
#include "QGMetafile.hpp"
#include "QGPath.hpp"
#include "QGPattern.hpp"
#include "QGContextAttribs.hpp"
#include "TextEngine.hpp"

// ============================== class Context ==============================

namespace GS {
	class ExtraReleasePool;
}

namespace QG {

class IContextImp;
class IConcreteDeviceImp;
class DrawableDevice;
class ICustomDrawObject;

class QG_DLL_EXPORT Context {

friend class DrawableDevice;

private:
	IContextImp*		imp;
	DrawableDevice*		hostDevice;

	void		CreateImp (Int32 ctType);
	bool		InitializeImp (DrawableDevice* drawDev, IConcreteDeviceImp* cDevImp, const ContextAttribs& cAttribs);
	void		ReleaseImp (IConcreteDeviceImp* cDevImp);

	IMatrix*	GetMatrixImp (const QG::Matrix* matrix);
	IPattern*	GetPatternImp (const QG::Pattern* matrix);
	IPath*		GetPathImp (const QG::Path& path);
	void		TestTEResults (Int32 res);


	Context& operator=(const Context&) {return *this;}

protected:
	Context ();
	~Context ();

public:
	// information functions
	ContextAttribs::ContextUnit GetUnit (void) const;
	ContextAttribs::ColorMode GetColorMode (void) const;
	double GetResolution (void) const;

	// drawing attributes
	void SetLinePen (const QG::Pen& pen);
	void SetFillPattern (const QG::Pattern& pattern);
	void SetTransMatrix (const QG::Matrix& matrix);

	// clip handling
	void IntersectClip (const QG::Path& path);
	void IntersectClip (const QG::Rect& rect);

	// handling graphic state
	ULong	SaveGraphicState (void);
	void	RestoreGraphicState (ULong	level);

	// drawing functions
	void	FlushDraw (void);

	void	BeginLayer (GS::UniString layerName);
	void	EndLayer ();

	void	DrawLine (const QG::Point& fromPt, const QG::Point& toPt, const QG::Pen* pen = nullptr, const QG::Matrix* matrix = nullptr);
	void	DrawLine (double fromPtX, double fromPtY, double toPtX, double toPtY, const QG::Pen* pen = nullptr, const QG::Matrix* matrix = nullptr);
	void	DrawPolyLine (const QG::Point* points, Int32 count, const QG::Pen* pen = nullptr, const QG::Matrix* matrix = nullptr);
	void	DrawPolyLine (const GS::Array<QG::Point>& points, const QG::Pen* pen = nullptr, const QG::Matrix* matrix = nullptr);
	void	DrawSegments (const QG::Point* points, Int32 count, const QG::Pen* pen = nullptr, const QG::Matrix* matrix = nullptr);
	void	DrawSegments (const GS::Array<QG::Point>& points, const QG::Pen* pen = nullptr, const QG::Matrix* matrix = nullptr);

	void	DrawArc (const QG::Rect& rect, double begAngle, double endAngle, const QG::Pen* pen = nullptr, const QG::Matrix* matrix = nullptr);
	void	DrawEllipse (const QG::Rect& rect, const QG::Pen* pen = nullptr, const QG::Matrix* matrix = nullptr);

	void	DrawRect (const QG::Rect& rect, const QG::Pen* pen = nullptr, const QG::Matrix* matrix = nullptr);
	void	DrawPath (const QG::Path& path, const QG::Pen* pen = nullptr, const QG::Matrix* matrix = nullptr);

	void	DrawImage (const QG::Image& image, const QG::Rect& dstRectInUserCoord, const QG::ImageAttribs* imageAttribs = nullptr,
						const QG::Rect* srcRectInPixels = nullptr, const QG::Matrix* matrix = nullptr);

	void	DrawMetafile (const QG::Rect& dstRectInUserCoord, const QG::Metafile& metafile, const QG::Matrix* matrix = nullptr);

	void	DrawCustomDrawObject (const QG::Rect& dstRectInUserCoord, QG::ICustomDrawObject* custDrawObject, const QG::Matrix* matrix = nullptr, const QG::Path* path = nullptr);

	// Text kiiratas

	void	DrawPlainText (const GS::UniString& uString, const TE::IFont& iFont,
							double baseLineX, double baseLineY, double angle, const QG::Color& textColor,
							const QG::Matrix* matrix = nullptr);
	void	DrawPlainMLText (const GS::UniString& uString, const TE::IFont& iFont, Int32 just,
							 double left, double top, double width, double height, double angle,
							 const QG::Color& textColor, const QG::Color& bkgColorconst,
							 const QG::Matrix* matrix = nullptr);

	void	DrawRichText (const TE::IRichText& rText, double left, double top, double width,
						  const QG::Matrix* matrix = nullptr, Int32 options = TE::TextEngine::NoOpt);
	void	GreekDrawRichText (const TE::IRichText& rText,	double left, double top, double width,
						  const QG::Matrix* matrix = nullptr, Int32 options = TE::TextEngine::NoOpt);

	void	FillRect (const QG::Rect& rect, const QG::Pattern* pattern = nullptr, const QG::Matrix* matrix = nullptr);
	bool	FillPath (const QG::Path& path, const QG::Pattern* pattern = nullptr, const QG::Matrix* matrix = nullptr);
	bool	CanDrawSymbolFill (void);

	bool	TransformPoints (ContextAttribs::CoordSpace destSpace, ContextAttribs::CoordSpace srcSpace, QG::Point* points, Int32 count);
	bool	TransformPoints (ContextAttribs::CoordSpace destSpace, ContextAttribs::CoordSpace srcSpace, GS::Array<QG::Point>* points);

	double	GetCurrentRotation (void);
	void	GetCurrentScale (double* xScale, double* yScale);
	
	// release pool functions
	void						AppendReleasePoolToReleasePool (const GS::ExtraReleasePool& pool);
	void						ReleaseObjectsFromPool (void);
	const GS::ExtraReleasePool*	GetReleasePool (void) const;
};


}	// namespace QG
// ______________________________ class Context ______________________________

#endif	// QGCONTEXT_HPP
