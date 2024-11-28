// *********************************************************************************************************************
// File:			DGBrowserEventArgs.hpp
//
// Description:		Browser Control Classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	SzaM
// *********************************************************************************************************************

#ifndef DGBROWSERJSHANDLER_HPP
#define DGBROWSERJSHANDLER_HPP

// --- Includes --------------------------------------------------------------------------------------------------------

// --- Class declarations ----------------------------------------------------------------------------------------------

namespace DG {

class DG_DLL_EXPORT JSBase {
public:
	virtual ~JSBase ();
};

class DG_DLL_EXPORT JSFunction : public JSBase {
friend class JSObject;

private:
	GS::UniString name;
	std::function<GS::Ref<JSBase>(GS::Ref<JSBase>)> callBack;

	GS::Ref<JSBase> CalledFromJSSide (GS::Ref<JSBase> params); 

public:
	JSFunction () = default;
	JSFunction (const GS::UniString& name);
	JSFunction (const GS::UniString& name, const std::function<GS::Ref<JSBase>(GS::Ref<JSBase>)>& callBack);
	template <typename F, typename O>
	JSFunction (const GS::UniString& name, F function, O object);
	const GS::UniString& GetName () const;

	virtual ~JSFunction ();
};

template <typename F, typename O>
JSFunction::JSFunction (const GS::UniString& name, F function, O object) : name (name)
{
	callBack = std::bind (function, object, std::placeholders::_1);
}

class DG_DLL_EXPORT JSObject : public JSBase {
private:
	GS::UniString name;
	GS::HashTable <GS::UniString, GS::Ref<JSBase>> items;

public:
	JSObject () = default;
	JSObject (const GS::UniString& name);
	const GS::UniString& GetName () const;

	void AddItem (const GS::UniString& name, GS::Ref<JSBase> item);
	void AddItem (GS::Ref<JSFunction> function);
	const GS::HashTable <GS::UniString, GS::Ref<JSBase>>& GetItemTable () const;

	GS::Ref<JSBase> CalledFromJSSide (const GS::UniString& functionName, GS::Ref<JSBase> params);

	virtual ~JSObject ();
};

class DG_DLL_EXPORT JSArray : public JSBase {
	GS::Array <GS::Ref<JSBase>> items;

public:
	void AddItem (GS::Ref<JSBase> item);
	const GS::Array <GS::Ref<JSBase>>& GetItemArray () const;

	virtual ~JSArray ();
};

class DG_DLL_EXPORT JSValue : public JSBase {
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
	JSValue () = default;
	JSValue (bool boolValue);
	JSValue (Int32 intValue);
	JSValue (UInt32 uintValue);
	JSValue (double doubleValue);
	JSValue (const GS::UniString& stringValue);

	bool GetBool () const;
	Int32 GetInteger () const;
	UInt32 GetUInteger () const;
	double GetDouble () const;
	const GS::UniString& GetString () const;

	bool IsNull () const;

	ValueType GetType () const;

	virtual ~JSValue ();
};

}	// namespace DG

#endif // DGBROWSERJSHANDLER_HPP
