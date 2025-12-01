#ifndef JSVALUES_HPP
#define JSVALUES_HPP

// --- Includes --------------------------------------------------------------------------------------------------------

#include "JavascriptEngineDLLExport.h"
#include "Array.hpp"
#include "Ref.hpp"
#include "UniString.hpp"
#include "HashTable.hpp"

// --- Class declarations ----------------------------------------------------------------------------------------------

namespace JS {

class JAVASCRIPT_ENGINE_DLL_EXPORT Base
{
public:
	virtual ~Base ();
};

class JAVASCRIPT_ENGINE_DLL_EXPORT Function: public Base
{
friend class Object;

private:
	GS::UniString name;
	std::function<GS::Ref<Base>(GS::Ref<Base>)> callBack;

	GS::Ref<Base> CalledFromJSSide (GS::Ref<Base> params);

public:
	Function () = default;
	Function (const GS::UniString& name);
	Function (const GS::UniString& name, const std::function<GS::Ref<Base>(GS::Ref<Base>)>& callBack);
	template <typename F, typename O>
	Function (const GS::UniString& name, F function, O object);
	const GS::UniString& GetName () const;

	virtual ~Function ();
};

template <typename F, typename O>
Function::Function (const GS::UniString& name, F function, O object) : name (name)
{
	callBack = std::bind (function, object, std::placeholders::_1);
}

class JAVASCRIPT_ENGINE_DLL_EXPORT Object : public Base
{
private:
	GS::UniString name;
	GS::HashTable <GS::UniString, GS::Ref<Base>> items;

public:
	Object () = default;
	Object (const GS::UniString& name);
	const GS::UniString& GetName () const;

	void AddItem (const GS::UniString& name, GS::Ref<Base> item);
	void AddItem (GS::Ref<Function> function);
	const GS::HashTable <GS::UniString, GS::Ref<Base>>& GetItemTable () const;

	GS::Ref<Base> CalledFromJSSide (const GS::UniString& functionName, GS::Ref<Base> params);

	virtual ~Object ();
};

class JAVASCRIPT_ENGINE_DLL_EXPORT Array : public Base
{
	GS::Array <GS::Ref<Base>> items;

public:
	void AddItem (GS::Ref<Base> item);
	const GS::Array <GS::Ref<Base>>& GetItemArray () const;

	virtual ~Array ();
};

class JAVASCRIPT_ENGINE_DLL_EXPORT Value : public Base
{
public:
	enum ValueType {
		DEFAULT = 0,
		BOOL,
		INTEGER,
		UINTEGER,
		DOUBLE,
		STRING
	};

private:
	ValueType valueType = DEFAULT;

	bool boolValue = false;
	Int32 intValue = 0;
	UInt32 uintValue = 0;
	double doubleValue = 0;
	GS::UniString stringValue;

public:
	Value () = default;
	Value (bool boolValue);
	Value (Int32 intValue);
	Value (UInt32 uintValue);
	Value (double doubleValue);
	Value (const GS::UniString& stringValue);
	Value (const char* cStrValue);

	bool GetBool () const;
	Int32 GetInteger () const;
	UInt32 GetUInteger () const;
	double GetDouble () const;
	const GS::UniString& GetString () const;

	bool IsNull () const;

	ValueType GetType () const;

	virtual ~Value ();
};

}	// namespace JS

#endif // JSVALUES_HPP
