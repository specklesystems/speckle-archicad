// *********************************************************************************************************************
// File:			DGEventArgs.hpp
//
// Description:		Dialog manager event handling.
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	SZM
// *********************************************************************************************************************

#ifndef DGEVENTARGS_HPP
#define DGEVENTARGS_HPP

#include "DGDLLExport.h"

namespace DG {

class DG_DLL_EXPORT EventArg
{
public:
	virtual		~EventArg ();

	virtual		operator Int64() const;
	virtual		operator Int32() const;
	virtual		operator short() const;
	virtual		operator UShort() const;
	virtual		operator ULong() const;
	virtual		operator double() const;

	virtual bool	operator== (short data) const;
	virtual bool	operator== (Int32 data) const;
	virtual bool	operator== (UInt64 data) const;
	virtual bool	operator== (Int64 data) const;

	virtual bool	operator!= (short data) const;
	virtual bool	operator!= (Int32 data) const;
	virtual bool	operator!= (Int64 data) const;

	virtual bool	operator< (short data) const;
	virtual bool	operator< (Int32 data) const;
	virtual bool	operator< (Int64 data) const;

	virtual bool	operator> (short data) const;
	virtual bool	operator> (Int32 data) const;
	virtual bool	operator> (Int64 data) const;
};

}

#endif // DGEVENTARGS_HPP
