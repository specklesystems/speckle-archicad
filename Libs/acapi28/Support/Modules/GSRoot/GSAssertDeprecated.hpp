#ifndef GS_ASSERTDEPRECATED_HPP
#define GS_ASSERTDEPRECATED_HPP

#include "Definitions.hpp"
#include "FastLogger.hpp"
#include "String.hpp"


#ifndef GS_CLANG_ANALYZER_NORETURN
	#ifdef __clang__
		#if __has_feature (attribute_analyzer_noreturn)
			#define GS_CLANG_ANALYZER_NORETURN __attribute__((analyzer_noreturn))
		#else
			#define GS_CLANG_ANALYZER_NORETURN
		#endif
	#else
		#define GS_CLANG_ANALYZER_NORETURN
	#endif
#endif


namespace GS::Deprecated {


// GST... asserts are tested by GS unit test (both their control branches) so they should be compiled even when coverage is used (GS_COVERAGE_TEST is defined)
// they may play role in control flow (eg. they return error codes which are tested by the unit test)

#define GSTASSERT(assertion, ...)			if (!GS::Deprecated::EvaulateAssert (assertion)) { GS::Deprecated::AssertFailedWithNoAction (AssertErrorLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }
#define GSTASSERT_R(assertion, ...)			if (!GS::Deprecated::EvaulateAssert (assertion)) { return GS::Deprecated::AssertFailed (AssertErrorLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }
#define GSTASSERT_RNULL(assertion, ...)     if (!GS::Deprecated::EvaulateAssert (assertion)) { GS::Deprecated::AssertFailed (AssertErrorLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); return nullptr; }
#define GSTASSERT_F(assertion, ...)			if (!GS::Deprecated::EvaulateAssert (assertion)) { GS::Deprecated::AssertFailed (AssertErrorLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__) (); }
#define GSTASSERT_FAILED(...)			    { GS::Deprecated::AssertFailed (AssertErrorLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }
#define GSTASSERT_FAILED_STR(str)		    GSTASSERT_FAILED (GS::Deprecated::Subject (GS::String (str)))

#define	GSTASSERT_NOERROR(errorCode)				  GSTASSERT   (errorCode == static_cast<GS::ErrorType> (NoError),  GS::Deprecated::CreateSubject (errorCode));
#define	GSTASSERT_NOERROR_R(errorCode)				  GSTASSERT_R (errorCode == static_cast<GS::ErrorType> (NoError),  GS::Deprecated::CreateSubject (errorCode), errorCode);
#define GSTASSERT_NOERROR_R2(errorCode1, errorCode2)  GSTASSERT_R (errorCode1 == static_cast<GS::ErrorType> (NoError), GS::Deprecated::CreateSubject (errorCode1), errorCode2);

#define	GSTRETURN_ON_ERROR(errorCode, errorCode1)					if (errorCode == errorCode1) return errorCode;
#define	GSTRETURN_ON_ERROR_R2(errorCode, errorCode1, errorCode2)	if (errorCode == errorCode1) return errorCode2;

#define GSTWASSERT(assertion, ...)			if (!GS::Deprecated::EvaulateAssert (assertion)) { GS::Deprecated::AssertFailedWithNoAction (AssertWarningLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }
#define GSTWASSERT_R(assertion, ...)		if (!GS::Deprecated::EvaulateAssert (assertion)) { return GS::Deprecated::AssertFailed (AssertWarningLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }
#define GSTWASSERT_RNULL(assertion, ...)	if (!GS::Deprecated::EvaulateAssert (assertion)) { GS::Deprecated::AssertFailed (AssertWarningLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); return nullptr; }
#define GSTWASSERT_F(assertion, ...)		if (!GS::Deprecated::EvaulateAssert (assertion)) { GS::Deprecated::AssertFailed (AssertWarningLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__) (); }
#define GSTWASSERT_FAILED(...)			    { GS::Deprecated::AssertFailed (AssertWarningLogLine, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }
#define GSTWASSERT_FAILED_STR(str)		    GSTWASSERT_FAILED (GS::Deprecated::Subject (GS::String (str)))

#define	GSTWASSERT_NOERROR(errorCode)				  GSTWASSERT   (errorCode == static_cast<GS::ErrorType> (NoError),  GS::Deprecated::CreateSubject (errorCode));
#define	GSTWASSERT_NOERROR_R(errorCode)				  GSTWASSERT_R (errorCode == static_cast<GS::ErrorType> (NoError),  GS::Deprecated::CreateSubject (errorCode), errorCode);
#define GSTWASSERT_NOERROR_R2(errorCode1, errorCode2) GSTWASSERT_R (errorCode1 == static_cast<GS::ErrorType> (NoError), GS::Deprecated::CreateSubject (errorCode1), errorCode2);


#define GSASSERT_DEPRECATED					GSTASSERT
#define GSASSERT_R_DEPRECATED				GSTASSERT_R
#define GSASSERT_RNULL_DEPRECATED			GSTASSERT_RNULL
#define GSASSERT_F_DEPRECATED				GSTASSERT_F
#define GSASSERT_FAILED_DEPRECATED			GSTASSERT_FAILED
#define GSASSERT_FAILED_STR_DEPRECATED		GSTASSERT_FAILED_STR

#define	GSASSERT_NOERROR_DEPRECATED			GSTASSERT_NOERROR
#define	GSASSERT_NOERROR_R_DEPRECATED		GSTASSERT_NOERROR_R
#define	GSASSERT_NOERROR_R2_DEPRECATED		GSTASSERT_NOERROR_R2

#define	GSRETURN_ON_ERROR_R2_DEPRECATED		GSTRETURN_ON_ERROR_R2

#define GSWASSERT_DEPRECATED				GSTWASSERT
#define GSWASSERT_R_DEPRECATED				GSTWASSERT_R
#define GSWASSERT_FAILED_DEPRECATED			GSTWASSERT_FAILED
#define GSWASSERT_FAILED_STR_DEPRECATED		GSTWASSERT_FAILED_STR

#define	GSWASSERT_NOERROR_DEPRECATED		GSTWASSERT_NOERROR
#define	GSWASSERT_NOERROR_R_DEPRECATED		GSTWASSERT_NOERROR_R
#define	GSWASSERT_NOERROR_R2_DEPRECATED		GSTWASSERT_NOERROR_R2


GSROOT_DLL_EXPORT extern const char*	ModuleName;

constexpr GS::LogLine::Level	MinBugReportLogLevel = GS::LogLine::Level::Error;

#define DEFINE_GSAssertLogLine_DEPRECATED static GS::ErrorLogLine AssertErrorLogLine ("GS error assertion failed at " __FILE__ " %", GS::LogLine::ParameterTypes ("UInt32"), GS::Deprecated::ModuleName, "Assert");


template<class Subject>
struct AssertSubject {
	Subject subject;
	explicit AssertSubject (const Subject& subject) : subject (subject) {}
};

template <class S, class = std::enable_if_t<!std::is_same_v<std::decay_t<S>, char*>>>
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

// ODB es ODB teszt hasznalja sok helyen, VBAttributes par helyen
GSROOT_DLL_EXPORT void		EnableAssert	(void);
GSROOT_DLL_EXPORT void		EnableAssert	(const char* module);
GSROOT_DLL_EXPORT void		DisableAssert   (void);
GSROOT_DLL_EXPORT void		DisableAssert   (const char* module);
GSROOT_DLL_EXPORT bool		IsAssertEnabled (void);
GSROOT_DLL_EXPORT bool		IsAssertEnabled (const char* module);

// ODB teszt sok helyen
GSROOT_DLL_EXPORT bool		IsAssertFailed				(void);
GSROOT_DLL_EXPORT bool		IsAssertFailed				(const char* module);

// ODB teszt 3 helyen
GSROOT_DLL_EXPORT UInt32	GetAssertFailureCount		(void);
GSROOT_DLL_EXPORT UInt32	GetAssertFailureCount		(const char* module);

// ODB teszt sok helyen
GSROOT_DLL_EXPORT void		ClearAssertFailureCounter	(void);
GSROOT_DLL_EXPORT void		ClearAssertFailureCounter	(const char* module);

GSROOT_DLL_EXPORT void		AssertFailed				(const char* module) GS_CLANG_ANALYZER_NORETURN;
GSROOT_DLL_EXPORT void		AssertFailed				(const char* file, int line, const char* function, const char* assertText) GS_CLANG_ANALYZER_NORETURN;

GSROOT_DLL_EXPORT void		AssertFailed				(GS::EventLogLine& eventLog, const char* file, int line, const char* function) GS_CLANG_ANALYZER_NORETURN;
GSROOT_DLL_EXPORT void		AssertFailed				(GS::EventLogLine& eventLog, const char* file, int line, const char* function, const AssertDescription& description) GS_CLANG_ANALYZER_NORETURN;
GSROOT_DLL_EXPORT void		AssertFailedWithNoAction	(GS::EventLogLine& eventLog, const char* file, int line, const char* function) GS_CLANG_ANALYZER_NORETURN;
GSROOT_DLL_EXPORT void		AssertFailedWithNoAction	(GS::EventLogLine& eventLog, const char* file, int line, const char* function, const AssertDescription& description) GS_CLANG_ANALYZER_NORETURN;

GSROOT_DLL_EXPORT void			AppendDescription (GS::FastLogger::LogComposer& logComposer, const AssertDescription& description);
GSROOT_DLL_EXPORT GS::String	LogAssertSubject_Deprecated  (GS::FastLogger::LogComposer& logComposer, const GSErrCode& subject);
GSROOT_DLL_EXPORT GS::String	LogAssertSubject_Deprecated  (GS::FastLogger::LogComposer& logComposer, const GS::ErrorStatus& subject);
GSROOT_DLL_EXPORT GS::String	LogAssertSubject_Deprecated  (GS::FastLogger::LogComposer& logComposer, const GS::String& subject);
GSROOT_DLL_EXPORT GS::String	LogAssertSubject_Deprecated  (GS::FastLogger::LogComposer& logComposer, const GS::Deprecated::StringAssertSubject& subject);
GSROOT_DLL_EXPORT GS::String	GetEvent		  (GS::EventLogLine& eventLog);


template <class Subject>
void	AssertFailed (GS::EventLogLine& eventLog, const char* file, int line, const char* function, const AssertSubject<Subject>& subject)
{
	const char* module = eventLog.GetOwner ();

	AssertFailed (module);

	if (!IsAssertEnabled (module))
		return;
	
	GS::FastLogger::LogComposer logComposer;
	GS::logger.Append (eventLog, static_cast<UInt32> (line), &logComposer);
	GS::String assertSubject = LogAssertSubject_Deprecated (logComposer, subject.subject);

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
	GS::String assertSubject = LogAssertSubject_Deprecated (logComposer, subject.subject);

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


inline auto		Subject (const GS::String& object)
{
	return GS::Deprecated::Subject (GS::Deprecated::StringAssertSubject (object));
}

} // namespace GS::Deprecated




#endif /* GS_ASSERTDEPRECATED_HPP */
