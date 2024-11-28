#ifndef LIMITED_TIMES_HPP
#define LIMITED_TIMES_HPP

#pragma once

#include <functional>

#include "GSRootExport.hpp"
#include "String.hpp"


namespace GS {

class GSException;

typedef const std::function<void (const char*)>& ReportFn;

GSROOT_DLL_EXPORT void CallLimitedTimes (const char* GUIDString, unsigned char maxNTimes, ReportFn reportFn);
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

#endif