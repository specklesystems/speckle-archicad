
// *****************************************************************************
//
//                                Class Tab
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined VBUTILTAB_HPP
#define VBUTILTAB_HPP

// --------------------------------- Includes ----------------------------------

#include "Object.hpp"

#include "ITab.hpp"
#include "TEBase.hpp"
#include <math.h>

namespace VBUtil { class RichText; }

// ============================== Class Tab ==============================

namespace GS {
	class	XMLOChannel;
	class	XMLIChannel;
}

namespace VBUtil {

class TE_DLL_EXPORT Tab : public TE::ITab, public GS::Object {
	DECLARE_CLASS_INFO

	friend class VBUtil::RichText;

private:
	Int32	mType;
	double	mPositionInModelUnit;
	bool	mIntegrity;

	VBUtil::RichText*		mParent;

public:
	Tab (void);
	Tab (const VBUtil::Tab& source);

	~Tab (void) {}

	inline	Tab&	operator= (const VBUtil::Tab& source);

//  TE:ITab implementation [--------------------------

	virtual double	GetPosition (void) const override;
	virtual	Int32	GetType (void) const override;

// ] TE:ITab implementation --------------------------

	inline	double	GetPositionDirect (void) const;

	inline	void	Set (double positionInModelUnit, Int32 type = TE::ITab::left);
	inline	void	SetPosition (double positionInModelUnit);
	inline	void	SetType (Int32 type);
	inline  void	ScaleDown (double scale);
	inline bool		IsIntegrate (void) const;
	inline void		SetIntegrity (bool integrate);

// Object interface
	virtual	GSErrCode	Read		(GS::IChannel& ic) override;
	virtual	GSErrCode	Write		(GS::OChannel& oc) const override;
			GSErrCode	WriteXML	(GS::XMLOChannel& ox) const;
			GSErrCode	ReadXML		(GS::XMLIChannel& ix);

};

inline	Tab&	Tab::operator= (const VBUtil::Tab& source)
{
	if (&source != this) {
		Set (source.GetPositionDirect (), source.GetType ());
	}
	return *this;
}

inline	double	Tab::GetPositionDirect (void) const
{
	return mPositionInModelUnit;
}

inline	Int32	Tab::GetType (void) const
{
	return mType;
}

inline	void	Tab::Set (double positionInModelUnit, Int32 type)
{
	SetPosition (positionInModelUnit);
	SetType (type);
}

inline	void	Tab::SetPosition (double positionInModelUnit)
{
	if (fabs (mPositionInModelUnit - positionInModelUnit) > 0.0000001) {
		mPositionInModelUnit = positionInModelUnit;
		SetIntegrity (false);
	}
}

inline	void	Tab::SetType (Int32 type)
{
	if (mType != type) {
		mType = type;
		SetIntegrity (false);
	}
}

inline  void	Tab::ScaleDown (double scale)
{
	mPositionInModelUnit *= scale;
	SetIntegrity (false);
}

inline bool	Tab::IsIntegrate (void) const
{
	return mIntegrity;
}

inline void	Tab::SetIntegrity (bool integrate)
{
	mIntegrity = integrate;
}

}	// namespace VBUtil
// ______________________________ Class Tab ______________________________

#endif
