// *****************************************************************************
//
//                                Class PDFDevice
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGPPDFDEVICE_HPP
#define QGPPDFDEVICE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------
#include "QGDrawableDevice.hpp"
#include "Location.hpp"
#include "UniString.hpp"

// ============================== class PDFDevice ==========================

namespace QG {

class IPDFDeviceImp;

class QG_DLL_EXPORT PDFDevice : public QG::DrawableDevice {
public:
	enum Orientation {oPortrait, oLandScape};
	enum ImplementationType { itDefault, itPDFNet, itMacNative };

private:
	IPDFDeviceImp*	imp;
	GSErrCode		error;
	QG::Rect		pageRect;
	QG::Rect		margins;
	Orientation		pageOrient;
	IO::Location	outputFile;

	PDFDevice (const PDFDevice&);
	PDFDevice& operator=(const PDFDevice&);

public:
	PDFDevice (ImplementationType implementationType = itDefault);
	PDFDevice (double dpiValue, ImplementationType implementationType = itDefault); 	// any virtual resolution can be set as initial value

	ImplementationType	GetImplementationType () const;
	void				Clear ();
	void				GetPage (QG::Rect* rect);
	void				SetPage (const QG::Rect& rect);
	void				SetDefaultSettings ();
	double				GetResolution ();
	void				SetVirtualResolution (double res);
	double				GetRealResolution (void) const override;
	GSErrCode			GetError () override { GSErrCode ret = error; error = NoError; return ret; }	//kzs-vs2005
	void				SetError (GSErrCode err) { error = err; }
	Orientation			GetOrientation () const { return pageOrient; }
	void				SetOrientation (Orientation orient) { pageOrient = orient; }
	void				BeginDocument (const IO::Location& fontTempFolder);
	void				EndDocument ();
	void				BeginPage ();
	void				EndPage ();
	void				GetDestination (IO::Location* oFile);
	void				SetDestination (const IO::Location& oFile);
	void				GetMargins (QG::Rect* rect);
	void				SetMargins (const QG::Rect& rect);
	Int32				InsertBookMark (Int32 parent, const GS::UniString& title);
	void				InsertHyperLink (char* bookMark);

};

}	// namespace QG
// ______________________________ class PrinterDevice __________________________

#endif	// QGPPDFDEVICE_HPP
