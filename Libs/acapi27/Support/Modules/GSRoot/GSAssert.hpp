
// *****************************************************************************
//
//	                  Asserts for the ObjectDatabase module
//
// Module:		   ObjectDatabase
// Namespace:	   GS
// Contact person: MB
//
// *****************************************************************************


#ifndef GSASSERT_HPP
#define GSASSERT_HPP


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"

#include "FastLogger.hpp"
#include "String.hpp"

// from STL
#include <cstdio>


namespace GS { class ErrorLogLine; }
namespace GS { class ErrorStatus; }


// GST... asserts are tested by GS unit test (both their control branches) so they should be compiled even when coverage is used (GS_COVERAGE_TEST is defined)
// they may play role in control flow (eg. they return error codes which are tested by the unit test)

#define GSTASSERT(assertion, ...)			if (!EvaulateAssert (assertion)) { GS::AssertFailedWithNoAction (AssertErrorLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }
#define GSTASSERT_R(assertion, ...)			if (!EvaulateAssert (assertion)) { return GS::AssertFailed (AssertErrorLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }
#define GSTASSERT_RNULL(assertion, ...)     if (!EvaulateAssert (assertion)) { GS::AssertFailed (AssertErrorLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); return nullptr; }
#define GSTASSERT_F(assertion, ...)			if (!EvaulateAssert (assertion)) { GS::AssertFailed (AssertErrorLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__) (); }
#define GSTASSERT_FAILED(...)			    { GS::AssertFailed (AssertErrorLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }
#define GSTASSERT_FAILED_STR(str)		    GSTASSERT_FAILED (GS::Subject (GS::String (str)))

#define	GSTASSERT_NOERROR(errorCode)				  GSTASSERT   (errorCode == NoError,  GS::CreateSubject (errorCode));
#define	GSTASSERT_NOERROR_R(errorCode)				  GSTASSERT_R (errorCode == NoError,  GS::CreateSubject (errorCode), errorCode);
#define GSTASSERT_NOERROR_R2(errorCode1, errorCode2)  GSTASSERT_R (errorCode1 == NoError, GS::CreateSubject (errorCode1), errorCode2);

#define	GSTRETURN_ON_ERROR(errorCode, errorCode1)					if (errorCode == errorCode1) return errorCode;
#define	GSTRETURN_ON_ERROR_R2(errorCode, errorCode1, errorCode2)	if (errorCode == errorCode1) return errorCode2;

#define GSTWASSERT(assertion, ...)			if (!EvaulateAssert (assertion)) { GS::AssertFailedWithNoAction (AssertWarningLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }
#define GSTWASSERT_R(assertion, ...)		if (!EvaulateAssert (assertion)) { return GS::AssertFailed (AssertWarningLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }
#define GSTWASSERT_RNULL(assertion, ...)	if (!EvaulateAssert (assertion)) { GS::AssertFailed (AssertWarningLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); return nullptr; }
#define GSTWASSERT_F(assertion, ...)		if (!EvaulateAssert (assertion)) { GS::AssertFailed (AssertWarningLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__) (); }
#define GSTWASSERT_FAILED(...)			    { GS::AssertFailed (AssertWarningLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }
#define GSTWASSERT_FAILED_STR(str)		    GSTWASSERT_FAILED (GS::Subject (GS::String (str)))

#define	GSTWASSERT_NOERROR(errorCode)				  GSTWASSERT   (errorCode == NoError,  GS::CreateSubject (errorCode));
#define	GSTWASSERT_NOERROR_R(errorCode)				  GSTWASSERT_R (errorCode == NoError,  GS::CreateSubject (errorCode), errorCode);
#define GSTWASSERT_NOERROR_R2(errorCode1, errorCode2) GSTWASSERT_R (errorCode1 == NoError, GS::CreateSubject (errorCode1), errorCode2);


#ifndef GS_BUILD_CTC

#define GSASSERT				GSTASSERT
#define GSASSERT_R				GSTASSERT_R
#define GSASSERT_RNULL			GSTASSERT_RNULL
#define GSASSERT_F				GSTASSERT_F
#define GSASSERT_FAILED			GSTASSERT_FAILED
#define GSASSERT_FAILED_STR		GSTASSERT_FAILED_STR

#define	GSASSERT_NOERROR		GSTASSERT_NOERROR
#define	GSASSERT_NOERROR_R		GSTASSERT_NOERROR_R
#define	GSASSERT_NOERROR_R2		GSTASSERT_NOERROR_R2

#define	GSRETURN_ON_ERROR		GSTRETURN_ON_ERROR
#define	GSRETURN_ON_ERROR_R2	GSTRETURN_ON_ERROR_R2

#define GSWASSERT				GSTWASSERT
#define GSWASSERT_R				GSTWASSERT_R
#define GSWASSERT_RNULL			GSTWASSERT_RNULL
#define GSWASSERT_F				GSTWASSERT_F
#define GSWASSERT_FAILED		GSTWASSERT_FAILED
#define GSWASSERT_FAILED_STR	GSTWASSERT_FAILED_STR

#define	GSWASSERT_NOERROR		GSTWASSERT_NOERROR
#define	GSWASSERT_NOERROR_R		GSTWASSERT_NOERROR_R
#define	GSWASSERT_NOERROR_R2	GSTWASSERT_NOERROR_R2


#else

#define GSASSERT(assertion, ...)
#define GSASSERT_R(assertion, ...)
#define GSASSERT_RNULL(assertion, ...)
#define GSASSERT_F(assertion, ...)
#define GSASSERT_FAILED(...)
#define GSASSERT_FAILED_STR(str)

#define	GSASSERT_NOERROR(errorCode)
#define	GSASSERT_NOERROR_R(errorCode)
#define GSASSERT_NOERROR_R2(errorCode1, errorCode2)

#define	GSRETURN_ON_ERROR(errorCode, errorCode1)
#define	GSRETURN_ON_ERROR_R2(errorCode, errorCode1, errorCode2)

#define GSWASSERT(assertion, ...)		
#define GSWASSERT_R(assertion, ...)	
#define GSWASSERT_RNULL(assertion, ...)
#define GSWASSERT_F(assertion, ...)	
#define GSWASSERT_FAILED(...)			   
#define GSWASSERT_FAILED_STR(str)

#define	GSWASSERT_NOERROR(errorCode)
#define	GSWASSERT_NOERROR_R(errorCode)
#define GSWASSERT_NOERROR_R2(errorCode1, errorCode2)


#endif

namespace GS {

GSROOT_DLL_EXPORT extern const char*	ModuleName;

constexpr GS::LogLine::Level	MinBugReportLogLevel = GS::LogLine::Level::Error;

}

#define DEFINE_GSAssertLogLine  static GS::ErrorLogLine		AssertErrorLogLine		("GS error assertion failed at " __FILE__ " %", GS::LogLine::ParameterTypes ("UInt32"), GS::ModuleName, "Assert");
#define DEFINE_GSWAssertLogLine static GS::WarningLogLine	AssertWarningLogLine	("GS warning assertion failed at " __FILE__ " %", GS::LogLine::ParameterTypes ("UInt32"), GS::ModuleName, "Assert");

namespace GS {

template<class Subject>
struct AssertSubject {
	Subject subject;
	explicit AssertSubject (const Subject& subject) : subject (subject) {}
};

template <class S>
AssertSubject<S>	Subject (const S& subject)
{
	return AssertSubject<S> (subject);
}

template <class S>
AssertSubject<S>	CreateSubject (const S& subject)
{
	return Subject (subject);
}

struct StringAssertSubject {
	GS::String	object;

	StringAssertSubject (const GS::String& object) : object (object) {}
};


struct AssertDescription {
	const char*  id;
	const char*  description;
};


GSROOT_DLL_EXPORT void		LogToBugReport (const char* module, const char* event, const char* file, int line, const char* data = nullptr);

GSROOT_DLL_EXPORT void		EnableAssert	(void);
GSROOT_DLL_EXPORT void		EnableAssert	(const char* module);
GSROOT_DLL_EXPORT void		DisableAssert   (void);
GSROOT_DLL_EXPORT void		DisableAssert   (const char* module);
GSROOT_DLL_EXPORT bool		IsAssertEnabled (void);
GSROOT_DLL_EXPORT bool		IsAssertEnabled (const char* module);

GSROOT_DLL_EXPORT void		AssertFailed				(const char* module);
GSROOT_DLL_EXPORT bool		IsAssertFailed				(void);
GSROOT_DLL_EXPORT bool		IsAssertFailed				(const char* module);
GSROOT_DLL_EXPORT UInt32	GetAssertFailureCount		(void);
GSROOT_DLL_EXPORT UInt32	GetAssertFailureCount		(const char* module);
GSROOT_DLL_EXPORT void		ClearAssertFailureCounter	(void);
GSROOT_DLL_EXPORT void		ClearAssertFailureCounter	(const char* module);

GSROOT_DLL_EXPORT void		AssertFailed				(const char* file, int line, const char* function, const char* assertText);

GSROOT_DLL_EXPORT void		AssertFailed				(GS::EventLogLine& eventLog, const char* file, int line, const char* function);
GSROOT_DLL_EXPORT void		AssertFailed				(GS::EventLogLine& eventLog, const char* file, int line, const char* function, const AssertDescription& description);
GSROOT_DLL_EXPORT void		AssertFailedWithNoAction	(GS::EventLogLine& eventLog, const char* file, int line, const char* function);
GSROOT_DLL_EXPORT void		AssertFailedWithNoAction	(GS::EventLogLine& eventLog, const char* file, int line, const char* function, const AssertDescription& description);

GSROOT_DLL_EXPORT void			AppendDescription (GS::FastLogger::LogComposer& logComposer, const AssertDescription& description);
GSROOT_DLL_EXPORT GS::String	LogAssertSubject  (GS::FastLogger::LogComposer& logComposer, const GSErrCode& subject);
GSROOT_DLL_EXPORT GS::String	LogAssertSubject  (GS::FastLogger::LogComposer& logComposer, const GS::ErrorStatus& subject);
GSROOT_DLL_EXPORT GS::String	LogAssertSubject  (GS::FastLogger::LogComposer& logComposer, const GS::String& subject);
GSROOT_DLL_EXPORT GS::String	LogAssertSubject  (GS::FastLogger::LogComposer& logComposer, const GS::StringAssertSubject& subject);
GSROOT_DLL_EXPORT GS::String	GetEvent		  (GS::EventLogLine& eventLog);

GSROOT_DLL_EXPORT void		EnableAssertMessage		(void);
GSROOT_DLL_EXPORT void		DisableAssertMessage	(void);
GSROOT_DLL_EXPORT bool		IsAssertMessageEnabled	(void);


template <class Subject>
void	AssertFailed (GS::EventLogLine& eventLog, const char* file, int line, const char* function, const AssertSubject<Subject>& subject)
{
	const char* module = eventLog.GetOwner ();

	AssertFailed (module);

	if (!IsAssertEnabled (module))
		return;
	
	GS::FastLogger::LogComposer logComposer;
	GS::logger.Append (eventLog, static_cast<UInt32> (line), &logComposer);
	GS::String assertSubject = LogAssertSubject (logComposer, subject.subject);

	GS::String event = GetEvent (eventLog);

	if (eventLog.GetLevel () >= MinBugReportLogLevel)
		LogToBugReport (eventLog.GetOwner (), event.ToCStr (), file, line, assertSubject.ToCStr ());

	AssertFailed (file, line, function, assertSubject.ToCStr ());
}


template <class Subject>
void	AssertFailed (GS::EventLogLine& eventLog, const char* file, int line, const char* function, const AssertDescription& description, const AssertSubject<Subject>& subject)
{
	const char* module = eventLog.GetOwner ();

	AssertFailed (module);

	if (!IsAssertEnabled (module))
		return;
	
	GS::FastLogger::LogComposer logComposer;
	GS::logger.Append (eventLog, static_cast<UInt32> (line), &logComposer);
	AppendDescription (logComposer, description);
	GS::String assertSubject = LogAssertSubject (logComposer, subject.subject);

	GS::String event = GetEvent (eventLog);

	char dataText[4096];
	std::snprintf (dataText, sizeof (dataText), "    assert id: %s%s    description: %s%s%s", description.id, GS::EOL, description.description, GS::EOL, assertSubject.ToCStr ());

	if (eventLog.GetLevel () >= MinBugReportLogLevel)
		LogToBugReport (eventLog.GetOwner (), event.ToCStr (), file, line, dataText);

	AssertFailed (file, line, function, assertSubject.ToCStr ());
}


template <class Subject>
void	AssertFailedWithNoAction (GS::EventLogLine& eventLog, const char* file, int line, const char* function, const AssertSubject<Subject>& subject)
{
	AssertFailed (eventLog, file, line, function, subject);
}


template <class Subject>
void	AssertFailedWithNoAction (GS::EventLogLine& eventLog, const char* file, int line, const char* function, const AssertDescription& description, const AssertSubject<Subject>& subject)
{
	AssertFailed (eventLog, file, line, function, description, subject);
}


template <class Action>
const Action& AssertFailed (GS::EventLogLine& eventLog, const char* file, int line, const char* function, const Action& action)
{
	AssertFailed (eventLog, file, line, function);

	return action;
}


template <class Action>
const Action&	AssertFailed (GS::EventLogLine& eventLog, const char* file, int line, const char* function, const AssertDescription& description, const Action& action)
{
	AssertFailed (eventLog, file, line, function, description);

	return action;
}


template <class Subject, class Action>
const Action&	AssertFailed (GS::EventLogLine& eventLog, const char* file, int line, const char* function, const AssertSubject<Subject>& subject, const Action& action)
{
	AssertFailed (eventLog, file, line, function, subject);

	return action;
}


template <class Subject, class Action>
const Action&	AssertFailed (GS::EventLogLine& eventLog, const char* file, int line, const char* function, const AssertDescription& description, const AssertSubject<Subject>& subject, const Action& action)
{
	AssertFailed (eventLog, file, line, function, description, subject);

	return action;
}


GS_FORCE_INLINE bool	EvaulateAssert (bool assertion)
{
	return assertion;
}


GS_FORCE_INLINE bool	EvaulateAssert (GSErrCode errorCode)
{
	return (errorCode == NoError);
}

} // namespace GS


using GS::EvaulateAssert;


inline auto		Subject (const GS::String& object)
{
	return GS::Subject (GS::StringAssertSubject (object));
}


#endif // GSASSERT_HPP
