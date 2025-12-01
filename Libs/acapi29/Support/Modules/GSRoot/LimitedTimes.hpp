#ifndef GS_LIMITEDTIMES_HPP
#define GS_LIMITEDTIMES_HPP

#include "FunctionRef.hpp"
#include "String.hpp"


namespace GS {


class GSException;

using ReportFn = FunctionRef<void (const char*)>;


GSROOT_DLL_EXPORT void CallLimitedTimes (const char* GUIDString, UInt8 maxNTimes, ReportFn reportFn);
GSROOT_DLL_EXPORT void ReportLimitedTimes (const char* string, const char* functionName, const char* GUIDString = nullptr);
GSROOT_DLL_EXPORT void ReportLimitedTimes (const GS::GSException& exception, const char* functionName, const char* GUIDString = nullptr);


#define CATCH_AND_REPORT_ALL																												\
	catch (GS::Exception& exception) {																										\
	GS::ReportLimitedTimes (exception, __FUNCTION__);																						\
} catch (std::exception& exception) {																										\
	GS::ReportLimitedTimes ((GS::String ("std::exception thrown: ") + GS::String (typeid (exception).name ())).ToCStr (), __FUNCTION__);	\
} catch (...) {																																\
	GS::ReportLimitedTimes ("Something other than GS::Exception or std::exception thrown", __FUNCTION__);									\
}


#define CATCH_REPORT_RETRHOW																												\
	catch (GS::Exception& exception) {																										\
	GS::ReportLimitedTimes (exception, __FUNCTION__);																						\
	throw;																																	\
} catch (std::exception& exception) {																										\
	GS::ReportLimitedTimes ((GS::String ("std::exception thrown: ") + GS::String (typeid (exception).name ())).ToCStr (), __FUNCTION__);	\
	throw;																																	\
} catch (...) {																																\
	GS::ReportLimitedTimes ("Something other than GS::Exception or std::exception thrown", __FUNCTION__);									\
	throw;																																	\
}


} // namespace GS


#endif /* GS_LIMITEDTIMES_HPP */
