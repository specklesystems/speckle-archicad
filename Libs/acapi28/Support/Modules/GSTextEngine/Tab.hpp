
// *****************************************************************************
//
//                                Class ITab
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined TAB_HPP
#define TAB_HPP


// --------------------------------- Includes ----------------------------------

#include "GSRoot.hpp"
#include "ObjectState.hpp"
#include "ITab.hpp"
#include <math.h>

// ============================== Class Tab ==============================

namespace TE {

class TE_DLL_EXPORT Tab : public ITab {
private:
	Int32	mType;
	double	mPosition;
	bool	mIntegrity;

public:
	inline	Tab (void);
	inline	Tab (const ITab& source);
	inline	Tab (const Tab& source);


	virtual ~Tab (void);

	inline	Tab&	operator= (const ITab& source);
	inline	Tab&	operator= (const Tab& source);

	inline	bool	operator== (const ITab& source) const;
	inline	bool	operator== (const Tab& source) const;

	inline	bool	operator!= (const ITab& source) const;
	inline	bool	operator!= (const Tab& source) const;

	virtual double	GetPosition (void) const override { return	mPosition; }
	virtual Int32	GetType		(void) const override { return mType; }

	inline void		Set (double position, Int32 type = ITab::left);
	inline void		SetPosition (double position);
	inline void		SetType (Int32 type);
	inline bool		IsIntegrate (void) const;
	inline void		SetIntegrity (bool integrate);

// Object interface
	inline	GSErrCode	Read	(GS::IChannel& ic);
	inline	GSErrCode	Write	(GS::OChannel& oc) const;

	inline GSErrCode	Store (GS::ObjectState& os) const;
};

inline	Tab::Tab (void)
: mType (-1), mPosition (0.0), mIntegrity (true)
{
}

inline	Tab::Tab (const ITab& source)
: mIntegrity (true)
{
	mPosition = source.GetPosition ();
	mType = source.GetType ();
}

inline	Tab::Tab (const Tab& source)
: mIntegrity (true)
{
	mPosition = source.mPosition;
	mType = source.mType;
}

inline	Tab&	Tab::operator= (const Tab& source)
{
	if (&source != this) {
		mPosition = source.mPosition;
		mType = source.mType;
	}
	return *this;
}

inline	Tab&	Tab::operator= (const ITab& source)
{
	if (&source != this) {
		Set (source.GetPosition (), source.GetType ());
	}
	return *this;
}

inline void	Tab::Set (double position, Int32 type)
{
	SetPosition (position);
	SetType (type);
}

inline void	Tab::SetType (Int32 type)
{
	if (mType != type) {
		mType = type;
		SetIntegrity (false);
	}
}

inline bool	Tab::IsIntegrate (void) const
{
	return mIntegrity;
}

inline void	Tab::SetIntegrity (bool integrate)
{
	mIntegrity = integrate;
}

inline void	Tab::SetPosition (double position)
{
	if (fabs (mPosition - position) > 0.0000001) {
		mPosition = position;
		SetIntegrity (false);
	}
}

inline	bool	Tab::operator== (const Tab& source) const
{
	if (&source == this)
		return true;
	if (source.mPosition == mPosition &&
		source.mType == mType)
		return true;

	return false;
}

inline	bool	Tab::operator== (const ITab& source) const
{
	if (&source == this)
		return true;
	if (source.GetPosition () == GetPosition () &&
		source.GetType () == mType)
		return true;

	return false;
}

inline	bool	Tab::operator!= (const ITab& source) const
{
	if (&source == this)
		return false;
	if (source.GetPosition () != GetPosition () ||
		source.GetType () != mType)
		return true;

	return false;
}

inline	bool	Tab::operator!= (const Tab& source) const
{
	if (&source == this)
		return false;
	if (source.mPosition != mPosition ||
		source.mType != mType)
		return true;

	return false;
}


inline	GSErrCode	Tab::Read	(GS::IChannel& ic)
{
	ic.Read (mType);
	ic.Read (mPosition);
	ic.Read (mIntegrity);

	return ic.GetInputStatus ();
}


inline	GSErrCode	Tab::Write	(GS::OChannel& oc) const
{
	oc.Write (mType);
	oc.Write (mPosition);
	oc.Write (mIntegrity);

	return oc.GetOutputStatus ();
}


GSErrCode	Tab::Store (GS::ObjectState& os) const
{
	os.Add ("type", GetType ());
	os.Add ("position", GetPosition ());
	os.Add ("integrity", IsIntegrate ());

	return NoError;
}

}	// namespace TE
// ______________________________ Class Tab ______________________________

#endif
