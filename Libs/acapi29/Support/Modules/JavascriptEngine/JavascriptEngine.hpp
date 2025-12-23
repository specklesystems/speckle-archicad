#ifndef JS_ENGINE_HPP
#define JS_ENGINE_HPP


// --- Includes --------------------------------------------------------------------------------------------------------
#include "Ref.hpp"
#include "JSValues.hpp"

// --- Predeclarations -------------------------------------------------------------------------------------------------
class JavascriptEngineImpl;

// --- Class declarations ----------------------------------------------------------------------------------------------


class JAVASCRIPT_ENGINE_DLL_EXPORT JavascriptEngine
{
	GS::Ref<JavascriptEngineImpl> _impl;
protected:
	virtual JavascriptEngineImpl* GetImpl ();
	virtual bool	ExecuteJSFunctionWithParameters (GS::Ref<JS::Object> onObject, GS::Ref<JS::Function> jsFunction, const GS::Array<GS::Ref<JS::Base>>& parameters);

public:
	JavascriptEngine ();
	virtual ~JavascriptEngine ();

	virtual void	LoadURL (const GS::UniString& url);
	virtual void	LoadHTML (const GS::UniString& htmlStr);

	virtual bool	ExecuteJS (const GS::UniString& jsCode);

	template<typename... Parameters>
	bool			ExecuteJSFunction (const GS::Ref<JS::Object>& onObject, const GS::Ref<JS::Function>& jsFunction, const Parameters&... parameter);
	template<>
	bool			ExecuteJSFunction (const GS::Ref<JS::Object>& onObject, const GS::Ref<JS::Function>& jsFunction);

	virtual bool	RegisterAsynchJSObject (GS::Ref<JS::Object> obj);
	virtual void	UnregisterJSObject (const GS::UniString& name);
};


template<typename ...Parameters>
inline bool JavascriptEngine::ExecuteJSFunction (const GS::Ref<JS::Object>& onObject, const GS::Ref<JS::Function>& jsFunction, const Parameters&... parameters)
{
	GS::Array<GS::Ref<JS::Base>> functionParameters{ parameters... };
	return ExecuteJSFunctionWithParameters (onObject, jsFunction, functionParameters);
}


template<>
inline bool JavascriptEngine::ExecuteJSFunction (const GS::Ref<JS::Object>& onObject, const GS::Ref<JS::Function>& jsFunction)
{
	return ExecuteJSFunctionWithParameters (onObject, jsFunction, {});
}


#endif // JS_ENGINE_HPP
