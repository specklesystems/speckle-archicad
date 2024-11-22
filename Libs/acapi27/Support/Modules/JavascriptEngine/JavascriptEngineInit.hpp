#ifndef JS_ENGINE_INIT_HPP
#define JS_ENGINE_INIT_HPP


// --- Includes --------------------------------------------------------------------------------------------------------
#include "JavascriptEngineDLLExport.h"
#include "UniString.hpp"

// --- Predeclarations -------------------------------------------------------------------------------------------------


// --- Class declarations ----------------------------------------------------------------------------------------------


class JAVASCRIPT_ENGINE_DLL_EXPORT JavascriptEngineMessagePump final
{
public:
	static const unsigned long standardTickCount;
	
	enum {
		Stop,
		Continue
	};

	JavascriptEngineMessagePump ();
	~JavascriptEngineMessagePump ();

	void Run (unsigned long tickCount = standardTickCount);

	template<typename Predicate>
	void RunUntil (const Predicate& predicate) {
		while (predicate () == Continue) {
			Run (1);
		}
	}
};


class JAVASCRIPT_ENGINE_DLL_EXPORT JavascriptEngineInitializer
{
public:
	JavascriptEngineInitializer (int debugPort = 0);
	~JavascriptEngineInitializer ();
};


#endif // JS_ENGINE_HPP
