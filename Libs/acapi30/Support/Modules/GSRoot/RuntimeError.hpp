// *****************************************************************************
//
// Contact person: MB, PR, BIA
//
// *****************************************************************************

#ifndef GS_RUNTIMEERROR_HPP
#define GS_RUNTIMEERROR_HPP

#include "Definitions.hpp"
#include "GSRootExport.hpp"

#ifndef GS_BUILD_MODULE
// from Standard Library
#include <exception>
#include <stdexcept>
#endif


namespace GS { class UniString; }


namespace GS {


class GSROOT_DLL_EXPORT RuntimeError : public std::runtime_error {
private:

	std::exception_ptr	mCause;
	const char*			mFile;		// TODO C++20: Use std::source_location.
	UInt32				mLine;
	GSErrCode			mErrCode;

protected:

	RuntimeError (const char* message, const char* file, UInt32 line);
	RuntimeError (const char* message, GSErrCode errCode, const char* file, UInt32 line);

	RuntimeError (const UniString& message, const char* file, UInt32 line);
	RuntimeError (const UniString& message, GSErrCode errCode, const char* file, UInt32 line);

public:

	std::exception_ptr	GetCause () const noexcept;

	const char*			GetMessage () const noexcept gs_lifebound;

	const char*			GetFile () const noexcept gs_lifebound;
	UInt32				GetLine () const noexcept;

	GSErrCode			GetErrCode () const noexcept;

// std::runtime_error implementation

	const char*			what () const noexcept gs_lifebound override;
};


} // namespace GS


#endif /* GS_RUNTIMEERROR_HPP */