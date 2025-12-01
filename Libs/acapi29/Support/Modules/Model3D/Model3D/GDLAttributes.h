/****************************************************************************/
/*																			*/
/*						Attribute structure definitions						*/
/*																			*/
/****************************************************************************/

#ifndef	_GDLATTRIBUTES_H_
#define	_GDLATTRIBUTES_H_

#pragma once

#include "Point2D.hpp"
#include "GSPix.h"

// =============================================================================
// TYPES
// =============================================================================

typedef struct AttrHead {
		Int32			len;		/* length of attribute head && data field			*/
		char			name [32];	/* name of attribute (C string)						*/
		short			ind;		/* index of attribute - set by attribute manager	*/
		short			flags;		/* attribute flags									*/
		GSTime			modiTime;	/* time of the last modification					*/
		short			checkSum;	/* attribute checksum								*/
		short			version;	/* attribute version								*/
} AttrHead;

typedef struct FillRecord {
	AttrHead		fillHead;
	GSPattern		bitPat;				/* pattern of fill			*/
	double			hXSpac;				/* hatch spacing factor		*/
	double			hYSpac;				/* hatch spacing factor		*/
	double			hAngle;				/* hatch angle				*/
	Geometry::Vector2d	c1;					/* syhatch offset			*/
	Geometry::Vector2d	c2;					/* syhatch offset			*/
	short			fillType;			/* type of the fill	(VectorFill etc.) */
	short			percent;			/* percent of translucent fill */
	Int32			dummy2;

	Int32			hotNumb;			/* number of hatch hotspots	*/
	Int32			linNumb;			/* number of hatch lines	*/
	Int32			arcNumb;			/* number of hatch arcs		*/
	Int32			filNumb;			/* number of hatch fills	*/

	Int32			dummy3;				/* number of hatch ellarcs	*/
	Int32			dummy4;				/* number of hatch splines	*/
	Int32			dummy5;				/* number of hatch texts	*/
	Int32			dummy6;

	template <typename T>
	T*				GetVariableRecord ()					{ return reinterpret_cast<T*> (this + 1); } //a pointer right after the FillRecord!
	template <typename T>
	const T*		GetVariableRecord () const				{ return reinterpret_cast<const T*> (this + 1); } //a pointer right after the FillRecord!

	static inline 
	FillRecord*		New (Int32 fullRecSize)					{ DBASSERT (fullRecSize >= (Int32) sizeof (FillRecord)); return reinterpret_cast<FillRecord*> (new char [fullRecSize]); }
	inline void		operator delete (void* p)				{ delete [] reinterpret_cast <char*> (p); }
private: 
	inline void*	operator new (size_t /*size*/)			{ DBBREAK (); throw; }

} FillRecord;


typedef struct FillLine {
	double			lFreq;				/* frequency of the line */
	double			lDir;				/* angle of the line */
	double			lOffsetLine;		/* offset of the line (parallel...) */
	Coord			lOffset;			/* offset of the line */
	short			lPartNumb;			/* number of the line parts */
	short			dummy1;				/* not used */
	Int32			dummy2;				/* not used */
} FillLine;

#endif
