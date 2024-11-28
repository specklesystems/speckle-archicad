
// *****************************************************************************
//
//                               Class BinIProtocol
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined BINIPROTOCOL_HPP
#define BINIPROTOCOL_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Protocol.hpp"


// ============================ Class BinIProtocol =============================

namespace GS {

class GSROOT_DLL_EXPORT BinIProtocol: public IProtocol {
private:
	inline GSErrCode	ReadData (IChannel& input, char* destination, USize charCount);

public:
		// User interface

	virtual	GSErrCode	Read (IChannel& input, char& c) override;
	virtual GSErrCode	Read (IChannel& input, unsigned char& c) override;
	virtual GSErrCode	Read (IChannel& input, bool& b) override;
	virtual GSErrCode	Read (IChannel& input, short& s) override;
	virtual GSErrCode	Read (IChannel& input, unsigned short& s) override;
	virtual GSErrCode	Read (IChannel& input, int& i) override;
	virtual GSErrCode	Read (IChannel& input, unsigned int& i) override;
	virtual GSErrCode	Read (IChannel& input, long& l) override;
	virtual GSErrCode	Read (IChannel& input, unsigned long& l) override;
	virtual GSErrCode	Read (IChannel& input, Int64& l) override;
	virtual GSErrCode	Read (IChannel& input, UInt64& l) override;
	virtual GSErrCode	Read (IChannel& input, float& f) override;
	virtual GSErrCode	Read (IChannel& input, double& d) override;
	virtual GSErrCode	Read (IChannel& input, long double& d) override;
	virtual GSErrCode	Read (IChannel& input, char* cStr) override;

	virtual GSErrCode	Read (IChannel& input, GS::Object& obj) override;

	virtual GSErrCode	Read (IChannel& input, GS::Guid& guid) override;
};


GSROOT_DLL_EXPORT extern BinIProtocol	binIProtocol;	// default BinIProtocol instance
													// (BinIProtocol has no internal state so this single instance is sufficient)
}	// namespace GS

// ____________________________ Class BinIProtocol _____________________________

#endif
