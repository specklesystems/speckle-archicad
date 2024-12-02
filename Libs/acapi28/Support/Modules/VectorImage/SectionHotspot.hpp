#ifndef GS_VI_SECTIONHOTSPOT_HPP
#define GS_VI_SECTIONHOTSPOT_HPP

#include "VectorImageExport.h"
#include "Definitions.hpp"

class Sy_HotType;

namespace VI {

class VI_DLL_CLASS_EXPORT SectionHotspot {
private:
	short			hottype;
	short			subtype;
	short			pen;
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

	short	GetHotType ()		const { return hottype; }
	short	GetSubType ()		const { return subtype; }
	UInt32	GetSuppUnId ()		const { return supplUnId; }
	Coord	GetCoord ()			const { return coord; }
	double	GetZ ()				const { return z; }
	short	GetPen ()			const { return pen; }
	Int32	GetConnectionId ()	const { return connectionId; }
	bool	IsOutOfModel ()		const { return isOutOfModel; }
	double	GetArcDivParam ()	const { return arcDivParam; }

	void	SetHotType		(short newHotType)		{ hottype = newHotType; }
	void	SetSubType		(short newSubType)		{ subtype = newSubType; }
	void	SetSuppUnId		(UInt32 newSuppUnId)	{ supplUnId = newSuppUnId; }
	void	SetPen			(short newPen)			{ pen = newPen; }
	void	SetOutOfModel	(bool newIsOutOfModel)	{ isOutOfModel = newIsOutOfModel; }
	void	SetConnectionId (Int32 newConnectionId)	{ connectionId = newConnectionId; }
	void	SetArcDivParam	(double newArcDivParam)	{ arcDivParam = newArcDivParam; }
};

}
#endif
