// *****************************************************************************
//
//                                Class Metafile
//
// Module:			QGDrawing
// Namespace:		QG
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************

#if !defined QGMETAFILE_HPP
#define QGMETAFILE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------
#include "QGBase.hpp"
#include "QGTypes.hpp"
#include "FileTypeManager.hpp"

// ============================== class Metafile ==============================

namespace QG {

class IMetafile;
class MetafileDevice;
class Context;

class QG_DLL_EXPORT Metafile {

friend class Context;
friend class MetafileDevice;

public:
	enum MetafileType { mtUnknown = -1, mtNewFormat = 1, mtCompatible = 2 };

private:
	IMetafile*		imp;
	MetafileType	mType;

	Metafile (const Metafile&);
	Metafile& operator=(const Metafile &);

public:
	Metafile (MetafileType	metaType = mtNewFormat);
	virtual	~Metafile ();

	virtual	USize			GetDataLength (void) const;
	virtual	FTM::TypeID		GetFileType (void) const;
	virtual MetafileType	GetMetaType (void) const { return mType; }

	virtual	void			CopyToClipBoard (void) const;
	virtual	void			CopyData (void *buffer, USize length) const;
};


}	// namespace QG
// ______________________________ class Metafile ______________________________

#endif	// QGMETAFILE_HPP
