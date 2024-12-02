// *****************************************************************************
//
//                          Classes IProtocol, OProtocol
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"

namespace GS {

// ------------------------------ Predeclarations ------------------------------

class IChannel;
class OChannel;
class Object;
class Guid;


// ============================== Class IProtocol ==============================

class GSROOT_DLL_EXPORT IProtocol {
public:
		// Virtual destructor

	virtual ~IProtocol () {}

		// User interface

	virtual	GSErrCode	Read (IChannel& input, char& c)			  = 0;
	virtual GSErrCode	Read (IChannel& input, unsigned char& c)  = 0;
	virtual GSErrCode	Read (IChannel& input, bool& b)			  = 0;
	virtual GSErrCode	Read (IChannel& input, short& s)		  = 0;
	virtual GSErrCode	Read (IChannel& input, unsigned short& s) = 0;
	virtual GSErrCode	Read (IChannel& input, int& i)			  = 0;
	virtual GSErrCode	Read (IChannel& input, unsigned int& i)   = 0;
	virtual GSErrCode	Read (IChannel& input, long& l)			  = 0;
	virtual GSErrCode	Read (IChannel& input, unsigned long& l)  = 0;
	virtual GSErrCode	Read (IChannel& input, Int64& l)		  = 0;
	virtual GSErrCode	Read (IChannel& input, UInt64& l)		  = 0;
	virtual GSErrCode	Read (IChannel& input, float& f)		  = 0;
	virtual GSErrCode	Read (IChannel& input, double& d)		  = 0;
	virtual GSErrCode	Read (IChannel& input, long double& d)	  = 0;
	virtual GSErrCode	Read (IChannel& input, char* cStr)		  = 0;

	virtual GSErrCode	Read (IChannel& input, Object& obj)		  = 0;

	virtual GSErrCode	Read (IChannel& input, Guid& guid);
};

// ______________________________ Class IProtocol ______________________________



// ============================== Class OProtocol ==============================

class GSROOT_DLL_EXPORT OProtocol {
public:
		// Virtual destructor

	virtual ~OProtocol () {}

		// User interface

	virtual GSErrCode	Write (OChannel& output, char c)			= 0;
	virtual GSErrCode	Write (OChannel& output, unsigned char c)	= 0;
	virtual GSErrCode	Write (OChannel& output, bool b)			= 0;
	virtual GSErrCode	Write (OChannel& output, short s)			= 0;
	virtual GSErrCode	Write (OChannel& output, unsigned short s)	= 0;
	virtual GSErrCode	Write (OChannel& output, int i)				= 0;
	virtual GSErrCode	Write (OChannel& output, unsigned int i)	= 0;
	virtual GSErrCode	Write (OChannel& output, long l)			= 0;
	virtual GSErrCode	Write (OChannel& output, unsigned long l)	= 0;
	virtual GSErrCode	Write (OChannel& output, Int64 l)			= 0;
	virtual GSErrCode	Write (OChannel& output, UInt64 l)			= 0;
	virtual GSErrCode	Write (OChannel& output, float f)			= 0;
	virtual GSErrCode	Write (OChannel& output, double d)			= 0;
	virtual GSErrCode	Write (OChannel& output, long double d)		= 0;
	virtual GSErrCode	Write (OChannel& output, const void* p)		= 0;
	virtual GSErrCode	Write (OChannel& output, const char* cStr)	= 0;

	virtual	GSErrCode	Write (OChannel& output, const Object& obj)	= 0;

	virtual	GSErrCode	Write (OChannel& output, const Guid& guid);

	virtual	void		Note  (OChannel&	 /*output*/,
							   UInt32 /*protocolCode*/,
							   UInt32 /*noteCode*/,
							   const char*	 /*notePtr*/) {}
};
// ______________________________ Class OProtocol ______________________________

}	// namespace GS


#endif
