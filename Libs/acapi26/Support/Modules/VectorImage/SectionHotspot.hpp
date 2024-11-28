#ifndef GS_VI_SECTIONHOTSPOT_HPP
#define GS_VI_SECTIONHOTSPOT_HPP

#include "VectorImageExport.h"
#include "ClassInfo.hpp"
#include "Definitions.hpp"

class Sy_HotType;

namespace VI {

class VI_DLL_CLASS_EXPORT SectionHotspot {
private:
	DECLARE_ROOT_CLASS_INFO

	short			hottype;
	short			subtype;
	short			pen;
	short			layer;
	UInt32			supplUnId;
	Int32			connectionId;
	bool			isOutOfModel;
	Coord			coord;
	double			z;
	double			arcDivParam;
	
public:
	SectionHotspot ();
	SectionHotspot (short hottype, short subtype, UInt32 supplUnId, Coord coord, double z);

	Sy_HotType ToHotType () const;
	static SectionHotspot FromHotType (const Sy_HotType& syHotspot);

	inline short	GetHotType ()		const { return hottype; }
	inline short	GetSubType ()		const { return subtype; }
	inline UInt32	GetSuppUnId ()		const { return supplUnId; }
	inline Coord	GetCoord ()			const { return coord; }
	inline double	GetZ ()				const { return z; }
	inline short	GetPen ()			const { return pen; }
	inline short	GetLayer ()			const { return layer; }
	inline Int32	GetConnectionId ()	const { return connectionId; }
	inline short	IsOutOfMode ()		const { return isOutOfModel; }
	inline double	GetArcDivParam ()	const { return arcDivParam; }

	inline void	SetHotType		(short newHotType)		{ hottype = newHotType; }
	inline void	SetSubType		(short newSubType)		{ subtype = newSubType; }
	inline void	SetSuppUnId		(UInt32 newSuppUnId)	{ supplUnId = newSuppUnId; }
	inline void	SetPen			(short newPen)			{ pen = newPen; }
	inline void	SetLayer		(short newLayer)		{ layer = newLayer; }
	inline void	SetOutOfModel	(short newIsOutOfModel) { isOutOfModel = newIsOutOfModel; }
	inline void	SetConnectionId (Int32 newConnectionId) { connectionId = newConnectionId; }
	inline void	SetArcDivParam	(double newArcDivParam) { arcDivParam = newArcDivParam; }

	virtual ~SectionHotspot ();
};

}
#endif