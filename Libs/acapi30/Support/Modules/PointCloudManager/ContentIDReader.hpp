// *********************************************************************************************************************
// Description:		Wrapper for IO::File that implements IChannel and collects MD5 checksum while
//					reading binary data from the file.
//
// Module:			PointCloudManager
// Namespace:		PointCloud
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#if !defined (CONTENTIDREADER_HPP)
#define CONTENTIDREADER_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "GSGuid.hpp"
#include "Md5.hpp"

// from InputOutput
#include "MD5Channel.hpp"
#include "File.hpp"
#include "IChannelAdapter.hpp"
#include "InputBuffer.hpp"

#include "PointCloudManagerDefinitions.hpp"

namespace IO {
	class Location;
}

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace PointCloud {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

class ContentIDReader :	public GS::IChannelAdapter,
						private GS::InputBuffer::BinInput
{
public:
	explicit ContentIDReader (const IO::Location& loc, GS::PlatformSign fromPlatform);
	virtual ~ContentIDReader ();

	PC::ContentId		Finish ();
	
	GSErrCode			GetDataLength		(UInt64* length) const;
	virtual GSErrCode	GetInputPosition	(UInt64* position) const override;

protected:
	virtual GSErrCode	InternalRead (char* destination, USize nOfCharToRead, USize* read) override;

private:
	virtual void		SetDefaultInputProtocol () override;

	IO::File		inputFile;
	IO::MD5Channel	md5Channel;
	PC::ContentId	contentId;
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------



}	// namespace PointCloud

#endif // CONTENTIDREADER_HPP
