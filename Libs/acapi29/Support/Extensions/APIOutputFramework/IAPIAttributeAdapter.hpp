#ifndef __APIATTRIBUTEADAPTER_HPP__
#define __APIATTRIBUTEADAPTER_HPP__

#include "GSAPIWrappers.hpp"
#include "Channel.hpp"


namespace GSAPI {

// predeclarations
class IAttributeProxy;
class IAPIAttributeAdapterFactory;


/**
 * @interface
 * @stereotype adapter
 */
class IAPIAttributeAdapterBase {
protected:
	IAttributeProxy*				attributeProxy;
	IAPIAttributeAdapterFactory*	attributeAdapterFactory;
    const API_DatabaseInfo*			dbInfo;

public:
    IAPIAttributeAdapterBase (IAttributeProxy* proxy, IAPIAttributeAdapterFactory* factory) :
		attributeProxy (proxy),
		attributeAdapterFactory (factory),
		dbInfo (nullptr)
	{
		DBASSERT (attributeProxy != nullptr);
		DBASSERT (attributeAdapterFactory != nullptr);
	}

	IAPIAttributeAdapterBase (const IAPIAttributeAdapterBase& adapter) :
		attributeProxy			(adapter.attributeProxy),
		attributeAdapterFactory	(adapter.attributeAdapterFactory),
		dbInfo					(adapter.dbInfo)
	{}

	virtual ~IAPIAttributeAdapterBase ();


    IAPIAttributeAdapterBase& operator= (const IAPIAttributeAdapterBase& adapter)
	{
		attributeProxy			= adapter.attributeProxy;
		attributeAdapterFactory	= adapter.attributeAdapterFactory;
		dbInfo					= adapter.dbInfo;
		return (*this);
	}

	virtual void SetAttributeProxy			(IAttributeProxy* proxy)				{ if (DBVERIFY (proxy != nullptr)) { attributeProxy = proxy; } }
	virtual void SetAttributeAdapterFactory	(IAPIAttributeAdapterFactory* factory)	{ if (DBVERIFY (factory != nullptr)) { attributeAdapterFactory = factory; } }
	virtual void SetDatabaseInfo			(const API_DatabaseInfo* apiDBInfo)		{ if (DBVERIFY (apiDBInfo != nullptr)) { dbInfo = apiDBInfo; } }

	virtual void CacheAttributes () = 0;
};


template <typename APIType>
class IAPIAttributeAdapter : public IAPIAttributeAdapterBase {
protected:
	const APIType*		   element;
	const API_ElementMemo* memo;

public:
			IAPIAttributeAdapter (IAttributeProxy* proxy, IAPIAttributeAdapterFactory* factory) : IAPIAttributeAdapterBase (proxy, factory), element (nullptr), memo (nullptr) {}
			IAPIAttributeAdapter (const IAPIAttributeAdapter& adapter) : IAPIAttributeAdapterBase (adapter), element (adapter.element), memo (adapter.memo) {}
	virtual ~IAPIAttributeAdapter () { element = nullptr; memo = nullptr; }

    IAPIAttributeAdapter& operator= (const IAPIAttributeAdapter& adapter)
	{
		static_cast<IAPIAttributeAdapterBase&> (*this) = adapter;
		element = adapter.element;
		memo = adapter.memo;
		return (*this);
	}

	virtual void SetElement     (const APIType* apiType)		  { if (DBVERIFY (apiType != nullptr)) { element = apiType; } }
	virtual void SetElementMemo (const API_ElementMemo* elemMemo) { memo = elemMemo; }

	virtual void SetParameters (const APIType* apiType,
								const API_DatabaseInfo* apiDBInfo,
								const API_ElementMemo*	elemMemo = nullptr)
	{
		SetElement (apiType);
		SetDatabaseInfo (apiDBInfo);
		SetElementMemo (elemMemo);
	}
};

}	// namespace GSAPI

#endif //__APIATTRIBUTEADAPTER_HPP__
