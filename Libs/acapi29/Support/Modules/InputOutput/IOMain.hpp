
// *****************************************************************************
//
//	                        Entry point of the IO module
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined IOMAIN_HPP
#define IOMAIN_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"
#include "UniString.hpp"



// -----------------------------------------------------------------------------

namespace IO {

enum class LogLevel {
	NoLog = 0,
	Basic,
	Extended
};

IO_DLL_EXPORT	Int32 	CCALL Init (bool startReflectionService = true, const GS::UniString& programName = "", LogLevel logLevel = LogLevel::Basic);
IO_DLL_EXPORT	bool	CCALL StartReflectionService (const GS::UniString& programName);
IO_DLL_EXPORT	Int32	CCALL End (void);

IO_DLL_EXPORT	void 	CCALL RestrictLinkExtensions (void);

IO_DLL_EXPORT	void			CCALL SetLogOutput (GS::OChannel* lo);
IO_DLL_EXPORT	GS::OChannel*	CCALL GetLogOutput (void);
	
IO_DLL_EXPORT	void			CCALL SetBasicVolumeHandlingMode (void);
IO_DLL_EXPORT	void			CCALL SetMountingEnabled (bool enabled);
IO_DLL_EXPORT	void			CCALL SetSMBOnlyMode (bool smbOnly);

IO_DLL_EXPORT	void			CCALL SetLogLevel (LogLevel logLevel); // mac only!

}	// namespace IO



// ============================= Class Initializer =============================

namespace IO {

class Initializer {

private:
	Initializer (const Initializer&); // Disabled
	const Initializer&	operator = (const Initializer&); // Disabled

public:
	explicit Initializer (bool startReflectionService = true, const GS::UniString& programName = "");
			~Initializer ();

};


inline Initializer::Initializer (bool startReflectionService /*= true*/, const GS::UniString& programName /*= ""*/)
{
	Init (startReflectionService, programName);
}


inline Initializer::~Initializer ()
{
	End ();
}

}

#endif
